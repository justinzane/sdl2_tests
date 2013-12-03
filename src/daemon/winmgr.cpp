/**
 * @file 		winmgr.cpp is part of Project winmgr
 * @author		justin
 * @date		Nov 11, 2013
 * @copyright   Copyright justin, Nov 11, 2013
 * @section		<license> License
 * > winmgr is free software: you can redistribute it and/or modify
 * > it under the terms of the GNU General Public License as published by
 * > the Free Software Foundation, either version 3 of the License, or
 * > (at your option) any later version.
 * >
 * > winmgr is distributed in the hope that it will be useful,
 * > but WITHOUT ANY WARRANTY; without even the implied warranty of
 * > MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * > GNU General Public License for more details.
 * >
 * > You should have received a copy of the GNU General Public License
 * > along with winmgr.  If not, see <a href="http://www.gnu.org/licenses/">
 * > http://www.gnu.org/licenses/</a>.
 * @brief		TODO WRITEME
 * @details		TODO WRITEME
 */

#include "winmgr.hpp"

bool winmgr::stop_listening_ = false;

winmgr::winmgr() :
    zmqcntx_(2),
    zmq_rep_sock_(zmqcntx_, ZMQ_REP),
    zmq_pull_sock_(zmqcntx_, ZMQ_PULL),
    zmq_pub_sock_(zmqcntx_, ZMQ_PUB)
{

    // Start setting up ZMQ -------------------------------------------------------------------
    int linger = ZMQ_SOCK_LINGER;
    zmq_rep_sock_.bind(SRVR_REP_ADDR);
    zmq_rep_sock_.setsockopt(ZMQ_LINGER, (void*)&linger, sizeof(linger));
    zmq_pull_sock_.bind(SRVR_PULL_ADDR);
    zmq_pull_sock_.setsockopt(ZMQ_LINGER, (void*)&linger, sizeof(linger));
    zmq_pub_sock_.bind(SRVR_PUB_ADDR);
    zmq_pub_sock_.setsockopt(ZMQ_LINGER, (void*)&linger, sizeof(linger));

    // Start SDL2 -----------------------------------------------------------------------------
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Unable to initialize SDL:  %s\n", SDL_GetError()); throw;
    }
    if (SDL_GetNumVideoDisplays() < 1) {
        fprintf(stderr, "Num displays:  %d\n", SDL_GetNumVideoDisplays()); throw;
    }
    if (SDL_GetDesktopDisplayMode(0, &disp_mode_) != 0) {
        fprintf(stderr, "\nUnable to get display into:  %s\n", SDL_GetError()); throw;
    }
    pixfmt_ = disp_mode_.format;
    disp_w_ = disp_mode_.w - 24;
    disp_h_ = disp_mode_.h - 48;
    wind_ = SDL_CreateWindow("winmgr", 0, 0, disp_w_, disp_h_,
                             (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL));
    rend_ = SDL_CreateRenderer(wind_, -1,
                               SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    SDL_SetRenderDrawColor(rend_, 31, 31, 31, 255);
    scrn_ = SDL_CreateRGBSurface(0, disp_w_, disp_h_, RGBA_consts::bpp, RGBA_consts::rmask, RGBA_consts::gmask,
                                 RGBA_consts::bmask, RGBA_consts::amask);
    txtr_ = SDL_CreateTexture(rend_, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
                              disp_w_, disp_h_);

    // Handle kill/term signals
    // TODO: moveme to daemon.
    struct sigaction quit_action;
    quit_action.sa_handler = &quit;
    sigemptyset(&quit_action.sa_mask);
    sigaddset(&quit_action.sa_mask, SIGINT);
    sigaddset(&quit_action.sa_mask, SIGQUIT);
    sigaddset(&quit_action.sa_mask, SIGKILL);
    sigaddset(&quit_action.sa_mask, SIGTERM);
    quit_action.sa_flags = 0;
    sigaction(SIGINT, &quit_action, nullptr);
    sigaction(SIGKILL, &quit_action, nullptr);
    sigaction(SIGQUIT, &quit_action, nullptr);
    sigaction(SIGTERM, &quit_action, nullptr);
}

winmgr::~winmgr() {
    stop_listening_ = true;
    zmq_rep_sock_.close();
    zmq_pull_sock_.close();
    zmq_pub_sock_.close();
    zmqcntx_.close();
    SDL_Quit();
}

void winmgr::blit_(SDL_Surface& src_surf, SDL_Rect& src_rect, SDL_Rect& dst_rect) {
    SDL_BlitSurface(&src_surf, &src_rect, scrn_, &dst_rect);
    render_();
}

void winmgr::render_() {
    SDL_UpdateTexture(txtr_, nullptr, scrn_->pixels, scrn_->pitch);  // always returns 0
    SDL_RenderClear (rend_);                                      // always returns 0
    SDL_RenderCopy(rend_, txtr_, nullptr, nullptr);                     // always returns 0
    SDL_RenderPresent(rend_);
}

void winmgr::listener_() {
    bool got_render_req = false;
    bool got_cmd_msg = false;
    while (!(stop_listening_)) {
        // Get SDL_Events and publish them.
        SDL_Event evt;
        int poll_result = SDL_PollEvent(&evt);
        if (poll_result == 1) {     // If poll_result == 0, no event, move along
            std::vector<Uint8> evt_vec = event2vec(&evt);
            msgpack::sbuffer sbuf;
            msgpack::pack(sbuf, evt_vec);
            try {
                zmq_pub_sock_.send(sbuf.data(), sbuf.size(), 0);
            } catch (zmq::error_t &e) {
                fprintf(stderr, "ZMQ Error: %d %s\n", e.num(), e.what());
            }
        }
        // Handle Rendering requests from clients. --------------------------------------------
        zmq::message_t render_req;
        got_render_req = zmq_pull_sock_.recv(&render_req, ZMQ_NOBLOCK);
        if (got_render_req) {
            msgpack::unpacked unpacked;     // Unpack the msgpacked request
            msgpack::unpack(&unpacked, reinterpret_cast<char*>(render_req.data()), render_req.size());
            msgpack::object obj = unpacked.get();
            std::vector<Uint32> bv;         // convert it back into blit params
            obj.convert(&bv);
            std::tuple<SDL_Surface, SDL_Rect, SDL_Rect> bp = vec2blitparams(bv);
            SDL_Surface src_surf = std::get<0>(bp);
            SDL_Rect src_rect = std::get<1>(bp);
            SDL_Rect dst_rect = std::get<2>(bp);
            blit_(src_surf, src_rect, dst_rect);
        }
        // Check for commands from clients ----------------------------------------------------
        zmq::message_t cmd_msg;
        got_cmd_msg = zmq_rep_sock_.recv(&cmd_msg, ZMQ_NOBLOCK);
        if (got_cmd_msg) {
            msgpack::unpacked unpacked;
            msgpack::unpack(&unpacked, reinterpret_cast<char*>(cmd_msg.data()), cmd_msg.size());
            msgpack::object obj = unpacked.get();
            std::string cmd;
            obj.convert(&cmd);
            if (cmd == "quit") {
                std::string reply = "quitting";
                msgpack::sbuffer sbuf;
                msgpack::pack(sbuf, reply);
                zmq_rep_sock_.send((void*)sbuf.data(), sbuf.size(), 0);
                stop_listening_ = true;
            }
        }
    }
}
