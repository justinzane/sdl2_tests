/**
 * @file 		defs.hpp is part of Project winmgr
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
#ifndef DEFS_HPP_
#define DEFS_HPP_

#include <SDL2/SDL.h>
#include <msgpack.hpp>
#include <vector>
#include <stdlib.h>

#define AMASK 0xff000000
#define RMASK 0x00ff0000
#define GMASK 0x0000ff00
#define BMASK 0x000000ff
#define BPP   32

/** @def Address for display server pull socket. Recvs images from clients. */
#define SRVR_PULL_ADDR  "tcp://127.0.0.1:19992"
/** @def Address for display server publish socket. Sends events to clients. */
#define SRVR_PUB_ADDR   "tcp://127.0.0.1:19994"
/** @def Address for game client push socket. Sends images from clients. */
#define CLNT_PUSH_ADDR  "tcp://127.0.0.1:19991"
/** @def Address for game client subscribe socket. Recvs events from clients. */
#define CLNT_SUB_ADDR   "tcp://127.0.0.1:19993"
/** @def Millisecs to process queued messages before close. Default infinite wait.*/
#define ZMQ_SOCK_LINGER 1000

/**
 * @brief Blindly convert an SDL_Event into a vector.
 * @details Since an SDL_Event is a ~56 byte (currently) union, just put the bytes in a
 * vector for packing with msgpack. Note that this size is subject to change.
 */
std::vector<Uint8> event2vec(SDL_Event* evt);

SDL_Event vec2event(std::vector<Uint8> vec);

std::vector<Uint32> blitparams2vec(SDL_Surface*    src_surf,
                                   const SDL_Rect* src_rect,
                                   SDL_Rect*       dst_rect);

std::tuple<SDL_Surface, SDL_Rect, SDL_Rect> vec2blitparams(std::vector<Uint32> bv);

#endif /* DEFS_HPP_ */
