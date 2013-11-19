/**
 * @file 		blitmgr.cpp is part of Project winmgr
 * @author		justin
 * @date		Nov 12, 2013
 * @copyright   Copyright justin, Nov 12, 2013
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
#include "client.hpp"

void handler(const SDL_Event* evt) {
    switch (evt->type) {
        // Application events  Application events
        case SDL_QUIT:      // Send Quit to daemon
            fprintf(stderr, ">>>>    Received a Quit Event!\n");
            do_quit();
            break;
        // Android and iOS events
        case SDL_APP_TERMINATING:
            fprintf(stdout, "Received an unhandled event.\n");
            break;
        case SDL_APP_LOWMEMORY:
            fprintf(stdout, "Received an unhandled event.\n");
            break;
        case SDL_APP_WILLENTERBACKGROUND:
            fprintf(stdout, "Received an unhandled event.\n");
            break;
        case SDL_APP_DIDENTERBACKGROUND:
            fprintf(stdout, "Received an unhandled event.\n");
            break;
        case SDL_APP_WILLENTERFOREGROUND:
            fprintf(stdout, "Received an unhandled event.\n");
            break;
        case SDL_APP_DIDENTERFOREGROUND:
            fprintf(stdout, "Received an unhandled event.\n");
            break;
        // Window events   Window events
        case SDL_WINDOWEVENT:
            handle_window_event(evt);
            break;
        case SDL_SYSWMEVENT:
            fprintf(stdout, "Received an unhandled SDL_SYSWMEVENT event.\n");
            break;
        // Keyboard events Keyboard events
        case SDL_KEYDOWN:
            fprintf(stdout, "Received an unhandled SDL_KEYDOWN event.\n");
            break;
        case SDL_KEYUP:
            fprintf(stdout, "Received an unhandled SDL_KEYUP event.\n");
            break;
        case SDL_TEXTEDITING:
            fprintf(stdout, "Received an unhandled SDL_TEXTEDITING event.\n");
            break;
        case SDL_TEXTINPUT:
            fprintf(stdout, "Received an unhandled SDL_TEXTINPUT event.\n");
            break;
        // Mouse events    Mouse events
        case SDL_MOUSEMOTION:
            handle_mouse_motion(evt);
            break;
        case SDL_MOUSEBUTTONDOWN:
            fprintf(stdout, "Received an unhandled SDL_MOUSEBUTTONDOWN event.\n");
            break;
        case SDL_MOUSEBUTTONUP:
            fprintf(stdout, "Received an unhandled SDL_MOUSEBUTTONUP event.\n");
            break;
        case SDL_MOUSEWHEEL:
            fprintf(stdout, "Received an unhandled SDL_MOUSEWHEEL event.\n");
            break;
        // Joystick events Joystick events
        case SDL_JOYAXISMOTION:
            fprintf(stdout, "Received an unhandled event.\n");
            break;
        case SDL_JOYBALLMOTION:
            fprintf(stdout, "Received an unhandled event.\n");
            break;
        case SDL_JOYHATMOTION:
            fprintf(stdout, "Received an unhandled event.\n");
            break;
        case SDL_JOYBUTTONDOWN:
            fprintf(stdout, "Received an unhandled event.\n");
            break;
        case SDL_JOYBUTTONUP:
            fprintf(stdout, "Received an unhandled event.\n");
            break;
        case SDL_JOYDEVICEADDED:
            fprintf(stdout, "Received an unhandled event.\n");
            break;
        case SDL_JOYDEVICEREMOVED:
            fprintf(stdout, "Received an unhandled event.\n");
            break;
        // Controller events   Controller events
        case SDL_CONTROLLERAXISMOTION:
            fprintf(stdout, "Received an unhandled event.\n");
            break;
        case SDL_CONTROLLERBUTTONDOWN:
            fprintf(stdout, "Received an unhandled event.\n");
            break;
        case SDL_CONTROLLERBUTTONUP:
            fprintf(stdout, "Received an unhandled event.\n");
            break;
        case SDL_CONTROLLERDEVICEADDED:
            fprintf(stdout, "Received an unhandled event.\n");
            break;
        case SDL_CONTROLLERDEVICEREMOVED:
            fprintf(stdout, "Received an unhandled event.\n");
            break;
        case SDL_CONTROLLERDEVICEREMAPPED:
            fprintf(stdout, "Received an unhandled event.\n");
            break;
        // Touch events    Touch events
        case SDL_FINGERDOWN:
            fprintf(stdout, "Received an unhandled event.\n");
            break;
        case SDL_FINGERUP:
            fprintf(stdout, "Received an unhandled event.\n");
            break;
        case SDL_FINGERMOTION:
            fprintf(stdout, "Received an unhandled event.\n");
            break;
        // Gesture events  Gesture events
        case SDL_DOLLARGESTURE:
            fprintf(stdout, "Received an unhandled event.\n");
            break;
        case SDL_DOLLARRECORD:
            fprintf(stdout, "Received an unhandled event.\n");
            break;
        case SDL_MULTIGESTURE:
            fprintf(stdout, "Received an unhandled event.\n");
            break;
        // Clipboard events    Clipboard events
        case SDL_CLIPBOARDUPDATE:
            fprintf(stdout, "Received an unhandled SDL_CLIPBOARDUPDATE event.\n");
            break;
            // Drag and drop events    Drag and drop events
        case SDL_DROPFILE:
            fprintf(stdout, "Received an unhandled SDL_DROPFILE event.\n");
            break;
        // These are for your use, and should be allocated with SDL_RegisterEvents()   These are for your use, and should be allocated with SDL_RegisterEvents()
        case SDL_USEREVENT:
            fprintf(stdout, "Received an unhandled event.\n");
            break;
        case SDL_LASTEVENT:
            fprintf(stdout, "Received an unhandled event.\n");
            break;
    }
}

void handle_window_event(const SDL_Event* event) {
    if (event->type == SDL_WINDOWEVENT) {
        switch (event->window.event) {
            case SDL_WINDOWEVENT_SHOWN:
                fprintf(stdout, "Window %d shown\n", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_HIDDEN:
                fprintf(stdout, "Window %d hidden\n", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_EXPOSED:
                fprintf(stdout, "Window %d exposed\n", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_MOVED:
                fprintf(stdout, "Window %d moved to %d,%d\n", event->window.windowID,
                        event->window.data1, event->window.data2);
                break;
            case SDL_WINDOWEVENT_RESIZED:
                fprintf(stdout, "Window %d resized to %dx%d\n", event->window.windowID,
                        event->window.data1, event->window.data2);
                break;
            case SDL_WINDOWEVENT_MINIMIZED:
                fprintf(stdout, "Window %d minimized\n", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_MAXIMIZED:
                fprintf(stdout, "Window %d maximized\n", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_RESTORED:
                fprintf(stdout, "Window %d restored\n", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_ENTER:
                fprintf(stdout, "Mouse entered window %d\n", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_LEAVE:
                fprintf(stdout, "Mouse left window %d\n", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                fprintf(stdout, "Window %d gained keyboard focus\n", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_FOCUS_LOST:
                fprintf(stdout, "Window %d lost keyboard focus\n", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_CLOSE:
                fprintf(stdout, "Window %d closed\n", event->window.windowID);
                break;
            default:
                fprintf(stdout, "Window %d got unknown event %d\n", event->window.windowID,
                        event->window.event);
                break;
        }
    }
}

void handle_mouse_motion(const SDL_Event* evt) {
    SDL_MouseMotionEvent* mmevt = (SDL_MouseMotionEvent*)evt;
//    Uint32 mmevt->type;               // the event type; SDL_MOUSEMOTION
//    Uint32 mmevt->timestamp;          // timestamp of the event
//    Uint32 mmevt->windowID;           // the window with mouse focus, if any
//    Uint32 mmevt->which;              // the mouse instance id, or SDL_TOUCH_MOUSEID;
//    Uint32 mmevt->state;              // the state of the button;
//    Sint32 mmevt->x;                  // X coordinate, relative to window
//    Sint32 mmevt->y;                  // Y coordinate, relative to window
//    Sint32 mmevt->xrel;               // relative motion in the X direction
//    Sint32 mmevt->yrel;               // relative motion in the Y direction
    SDL_Rect src_rect, dst_rect;
    src_rect.x = 0;                 src_rect.y = 0;
    src_rect.h = abs(mmevt->xrel);  src_rect.w = abs(mmevt->yrel);
    dst_rect.x = mmevt->x;          dst_rect.y = mmevt->y;
    dst_rect.h = abs(mmevt->xrel);  dst_rect.w = abs(mmevt->yrel);
    SDL_Surface* src_surf = SDL_CreateRGBSurface(0, src_rect.w, src_rect.h, BPP,
                                                 RMASK, GMASK, BMASK, AMASK);
    Uint32 color = ((255 << 24) +
                    ((abs(mmevt->xrel) % 255) << 16) +
                    ((abs(mmevt->yrel) % 255) << 8) +
                    (mmevt->x % 255));
    SDL_FillRect(src_surf, &src_rect, color);
    blit(src_surf, &src_rect, &dst_rect);
}

// Image Rendering ----------------------------------------------------------------------------

bool cache_blitparam_vec(std::vector<Uint32>& bp_vec) {
    auto was_inserted = surf_cache.emplace(get_vec_hash(bp_vec), bp_vec);
    return std::get<1>(was_inserted);
}

Uint64 dup_count = 0;

void blit(SDL_Surface* src_surf, const SDL_Rect* src_rect, SDL_Rect* dst_rect) {
    std::vector<Uint32> bp_vec = blitparams2vec(src_surf, src_rect, dst_rect);
    if (!cache_blitparam_vec(bp_vec)) {
        if ((dup_count++ % 100) == 0) {
            fprintf(stderr, ">>>>    dup_count = %lu\n", dup_count);
        }
    }
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, bp_vec);
    try {
        size_t bytes_sent __attribute__((unused));
        bytes_sent = zmq_push_sock_.send(sbuf.data(), sbuf.size(), 0);
    } catch (zmq::error_t &e) {
        fprintf(stderr, "SDL Error %d %s\n", e.num(), e.what());
    }
}

// Quitting -----------------------------------------------------------------------------------
void do_quit() {
    std::string quit = "quit";
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, quit);
    bool server_quitting = false;
    while(!server_quitting) {
        zmq_req_sock_.send((void*)sbuf.data(), sbuf.size(), 0);
        zmq::message_t reply_msg;
        zmq_req_sock_.recv(&reply_msg, 0);
        msgpack::unpacked unpacked;
        msgpack::unpack(&unpacked, reinterpret_cast<char*>(reply_msg.data()), reply_msg.size());
        msgpack::object obj = unpacked.get();
        std::string reply;
        obj.convert(&reply);
        if (reply == "quitting") { server_quitting = true; }
    }
    quit_client_loop = true;
}
/*--------------------------------------------------------------------------------------------*/

int main() {
    // Setup ZMQ PUSH for sending bitmaps to server
    zmq_req_sock_.bind(CLNT_REQ_ADDR);
    zmq_req_sock_.connect(SRVR_REP_ADDR);
    // Setup ZMQ PUSH for sending bitmaps to server
    zmq_push_sock_.bind(CLNT_PUSH_ADDR);
    zmq_push_sock_.connect(SRVR_PULL_ADDR);
    // Setup ZMQ SUB for getting events
    zmq_sub_sock_.bind(CLNT_SUB_ADDR);
    zmq_sub_sock_.setsockopt(ZMQ_SUBSCRIBE, nullptr, 0);
    zmq_sub_sock_.connect(SRVR_PUB_ADDR);
    fprintf(stdout, ">>>>    Setup Client Sockets.\n");

    // The main loop -- recv events and send bitmaps
    while (!(should_quit())) {
        // Check for events
        zmq::message_t evt_msg;
        if (zmq_sub_sock_.recv(&evt_msg, ZMQ_NOBLOCK)) {
            msgpack::unpacked unpacked;
            msgpack::unpack(&unpacked, reinterpret_cast<char*>(evt_msg.data()), evt_msg.size());
            msgpack::object obj = unpacked.get();
            std::vector<Uint8> evt_vec;
            obj.convert(&evt_vec);
            SDL_Event evt = vec2event(evt_vec);
            handler(&evt);
        }
        // Send graphics
    }

    fprintf(stdout, ">>>>    Left Main Loop, Quitting.\n");
    // Cleanup after ourselves.
    if (zmq_req_sock_.connected())  { zmq_req_sock_.disconnect(SRVR_REP_ADDR); }
    if (zmq_push_sock_.connected()) { zmq_push_sock_.disconnect(SRVR_PULL_ADDR); }
    if (zmq_sub_sock_.connected())  { zmq_sub_sock_.disconnect(SRVR_PUB_ADDR); }
    zmq_req_sock_.close();
    zmq_push_sock_.close();
    zmq_sub_sock_.close();
    zmqcntx_.close();

    return 0;
}
