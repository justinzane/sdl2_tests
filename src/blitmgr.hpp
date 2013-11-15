/**
 * @file 		blitmgr.hpp is part of Project winmgr
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
#ifndef BLITMGR_HPP_
#define BLITMGR_HPP_

#include "defs.hpp"
#include "winmgr.hpp"

#include <zmq.hpp>
#include <msgpack.hpp>
#include <stdio.h>
#include <stdlib.h>

/**  @type blitmgrx TODO: WRITEME */
class blitmgr {
    public:
        static blitmgr& get_blitmgr() {
            static blitmgr instance_;
            return instance_;
        }

        void blit(SDL_Surface* src_surf, const SDL_Rect* src_rect, SDL_Rect* dst_rect) {
            // pack blit params into struct
            blit_params_t params = {src_surf, src_rect, dst_rect};
            // serialize struct with messagepack
            msgpack::sbuffer sbuf;
            msgpack::pack(sbuf, params);
            // create zmq message with msgpacked data
            zmq::message_t msg(sbuf.size());
            memcpy(msg.data(), sbuf.data(), sbuf.size());
            // send message
            zmqsock_.connect("tcp://127.0.0.1:19991");
            zmqsock_.send(&msg, 0);
        }

    private:
        blitmgr() :
            zmqcntx_(1),
            zmqsock_(zmqcntx_, ZMQ_PUSH)
        {
            try {
                zmqsock_.bind("tcp://127.0.0.1:19992");
            } catch (zmq::error_t &e) {
                fprintf(stderr, "ZMQ Error trying to bind to tcp:/// :19992.\n\t%d : %s",
                        e.num(), e.what());
                zmqsock_.close();
                zmqcntx_.close();
                throw;
            }
        }
        virtual ~blitmgr();
        blitmgr(const blitmgr&);
        void operator=(blitmgr const&);

        zmq::context_t zmqcntx_;
        zmq::socket_t zmqsock_;
};

#endif /* BLITMGR_HPP_ */
