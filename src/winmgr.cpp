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

#include "defs.hpp"
#include "winmgr.hpp"
#include <msgpack.hpp>
#include <chrono>
#include <thread>
#include <atomic>

winmgr::winmgr() :
    zmqcntx_(1),
    zmqsock_(zmqcntx_, ZMQ_PULL),
    stop_listener_(false)
{
    try {
        zmqsock_.bind("tcp://127.0.0.1:19991");
    } catch (zmq::error_t &e) {
        fprintf(stderr, "ZMQ Error trying to bind to tcp://127.0.0.1:19991.\n\t%d : %s",
                e.num(), e.what());
        zmqsock_.close();
        zmqcntx_.close();
        throw;
    }

    try {
        /**
         * @note All options, except ZMQ_SUBSCRIBE, ZMQ_UNSUBSCRIBE, ZMQ_LINGER,
         * ZMQ_ROUTER_MANDATORY and ZMQ_XPUB_VERBOSE only take effect for
         * subsequent socket bind/connects.
         * - ZMQ_RCVBUF set the kernel receive buffer for the socket to the specified size in
         *   bytes. Zero means OS default. For details refer to OS docs for the SO_RCVBUF.
         * - ZMQ_LINGER Linger period determines how long pending messages yet to be sent
         *   shall linger in memory after a socket is closed with zmq_close(3), and further
         *   affects the termination of the socket's context with zmq_term(3).
         *   - -1 (Default) Infinite linger period.
         *   - 0  specifies no linger period.
         *   - >0 specify an upper bound for the linger period in milliseconds.
         * @cite http://api.zeromq.org/3-2:zmq-setsockopt
         */
        zmqsock_.setsockopt(ZMQ_LINGER, &zmqsock_linger_, sizeof (zmqsock_linger_));
    } catch (zmq::error_t &e) {
        fprintf(stderr, "ZMQ Error trying to bind to tcp://127.0.0.1:19991.\n\t%d : %s",
                e.num(), e.what());
        zmqsock_.close();
        zmqcntx_.close();
        throw;
    }

    // Start SDL2
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Unable to initialize SDL:  %s\n", SDL_GetError());
        return;
    } else {
        fprintf(stderr, "Initialized SDL.\n");
    }

    if (SDL_GetNumVideoDisplays() < 1) {
        fprintf(stderr, "Num displays:  %d\n", SDL_GetNumVideoDisplays());
        return;
    } else {
        fprintf(stderr, "Num displays:  %d\n", SDL_GetNumVideoDisplays());
    }

    // Find the current screen resolution
    if (SDL_GetDesktopDisplayMode(0, &disp_mode_) != 0) {
        fprintf(stderr, "\nUnable to get display into:  %s\n", SDL_GetError());
        return;
    }
    pixfmt_ = disp_mode_.format;
    disp_w_ = disp_mode_.w - 24;
    disp_h_ = disp_mode_.h - 48;
    wind_ = SDL_CreateWindow("winmgr", 0, 0, disp_w_, disp_h_,
                             (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL));
    printf("Window created.");
    rend_ = SDL_CreateRenderer(wind_, -1,
                               SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    printf("Renderer created.");
    scrn_ = SDL_CreateRGBSurface(0, disp_w_, disp_h_, 32, 0x00FF0000, 0x0000FF00, 0x000000FF,
                                 0xFF000000);
    printf("Surface created.");
    txtr_ = SDL_CreateTexture(rend_, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
                              disp_w_, disp_h_);
    printf("Texture created.");

    listener_thread_ = std::thread(&winmgr::listener_, std::ref(*this));
}

winmgr::~winmgr() {
    stop_listener_.store(true);
    listener_thread_.join();
    zmqsock_.close();
    zmqcntx_.close();
    SDL_Quit();
}

void winmgr::blit_(SDL_Surface* src_surf, const SDL_Rect* src_rect, SDL_Rect* dst_rect) {
    int result = SDL_BlitSurface(src_surf, src_rect, scrn_, dst_rect);
    if (result == 0) {
        render_();
    } else {
        throw;
    }
}

void winmgr::render_() {
    if (SDL_UpdateTexture(txtr_, NULL, scrn_->pixels, scrn_->pitch) != 0) {
        fprintf(stderr, "Unable to update texture.\n");
    }
    SDL_RenderClear (rend_);
    SDL_RenderCopy(rend_, txtr_, NULL, NULL);
    SDL_RenderPresent(rend_);
}

void winmgr::listener_() {
    Uint64 count = 0;
    while (!(stop_listener_.load())) {
        count++;
        zmq::message_t req;
        // Wait for next request from client
        try {
            zmqsock_.recv (&req);
        } catch (zmq::error_t &e) {
            fprintf(stderr, "Iter[%lu] ZMQ Error: %d : %s\n", count, e.num(), e.what());
            continue;
        } catch (std::exception &e) {
            fprintf(stderr, "Iter[%lu] STD Error: %d : %s\n", count, e.what());
            continue;
        }
        // Unpack the msgpacked request
        msgpack::unpacked unpacked;
        msgpack::unpack(&unpacked,
                        reinterpret_cast<char*>(req.data()),
                        req.size());
        msgpack::object obj = unpacked.get();
        // convert it back into blit params
        blit_params_t bp;
        obj.convert(&bp);
        // blit it
        void* pixels = reinterpret_cast<void*>(bp.pixdata.data());
        SDL_Surface* src_surf = SDL_CreateRGBSurfaceFrom(pixels,
                                                         bp.w,
                                                         bp.h,
                                                         BPP,
                                                         bp.w*4,
                                                         RMASK,
                                                         GMASK,
                                                         BMASK,
                                                         AMASK);
        SDL_Rect src_rect;
        src_rect.w = bp.src_w;
        src_rect.h = bp.src_h;
        src_rect.x = bp.src_x;
        src_rect.y = bp.src_y;
        SDL_Rect dst_rect;
        dst_rect.w = bp.dst_w;
        dst_rect.h = bp.dst_h;
        dst_rect.x = bp.dst_x;
        dst_rect.y = bp.src_y;
        blit_(src_surf, &src_rect, &dst_rect);
        timespec ts1, ts2;
        ts1.tv_sec = 0;
        ts1.tv_nsec = 1000;
        nanosleep(&ts1, &ts2);
    }
}
