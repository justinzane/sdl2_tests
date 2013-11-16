/**
 * @file 		winmgr.hpp is part of Project winmgr
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
#ifndef WINMGR_HPP_
#define WINMGR_HPP_

//#include </usr/include/c++/4.8.2/x86_64-unknown-linux-gnu/bits/stdc++.h>
//#include <stddef.h>
//#include <stdio.h>
//#include <stdlib.h>
#include <SDL2/SDL.h>
#include <zmq.hpp>

//#include <condition_variable>
#include <cstdbool>
//#include <list>
//#include <mutex>
#include <thread>
#include <atomic>

/**  @type winmgr TODO: WRITEME */
class winmgr {
    public:
        /**
         * @brief Singleton instance getter.
         * @details Provides a reference to the winmgr instance which is created on demand.
         */
        static winmgr& get_winmgr(){
            static winmgr instance_;
            return instance_;
        }

        /** ZMQ listener */
        void listener_();

        inline void quit() {
            stop_listener_.store(true);
        }

    private:
        /** Constructor */
        winmgr();
        /** Destructor */
        virtual ~winmgr();
        /** Prevent cloning */
        winmgr(winmgr const&);
        /** Prevent assignment */
        void operator=(winmgr const&);

        /**
         * @brief Blits a provided surface onto the main surface.
         * @details This is to be called by the manager's listener, not directly
         * by clients.
         * @param src_surf  Caller provided image. ARGB8888 format.
         * @param src_rect  ROI of caller image.
         * @param dst_rect  Where to blit on main surface.
         */
        void blit_(SDL_Surface& src_surf, SDL_Rect& src_rect, SDL_Rect& dst_rect, Uint64 flag);

        /**
         * @brief the actual mechanics of updating the screen
         */
        void render_();

        // sdl2 stuff
        SDL_Window*   wind_;
        SDL_Renderer* rend_;
        SDL_Surface*  scrn_;
        SDL_Texture*  txtr_;
        SDL_DisplayMode disp_mode_;
        Uint32 pixfmt_;
        int disp_w_;
        int disp_h_;

        //zmq stuff
        zmq::context_t zmqcntx_;
        zmq::socket_t zmqsock_;
        const int zmqsock_linger_ = 1000;

        // daemon thread stuff
        std::atomic<bool> stop_listener_;
        std::thread listener_thread_;
};

#endif /* WINMGR_HPP_ */
