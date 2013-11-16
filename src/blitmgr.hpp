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

        void blit(SDL_Surface* src_surf, const SDL_Rect* src_rect, SDL_Rect* dst_rect);

    private:
        blitmgr();
        virtual ~blitmgr();
        blitmgr(const blitmgr&);
        void operator=(blitmgr const&);

        zmq::context_t zmqcntx_;
        zmq::socket_t zmqsock_;
};

#endif /* BLITMGR_HPP_ */
