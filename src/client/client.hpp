/**
 * @file 		client.hpp is part of Project sdl2_tests
 * @author		justin
 * @date		Nov 18, 2013
 * @copyright   Copyright justin, Nov 18, 2013
 * @section		<license> License
 * > sdl2_tests is free software: you can redistribute it and/or modify
 * > it under the terms of the GNU General Public License as published by
 * > the Free Software Foundation, either version 3 of the License, or
 * > (at your option) any later version.
 * >
 * > sdl2_tests is distributed in the hope that it will be useful,
 * > but WITHOUT ANY WARRANTY; without even the implied warranty of
 * > MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * > GNU General Public License for more details.
 * >
 * > You should have received a copy of the GNU General Public License
 * > along with sdl2_tests.  If not, see <a href="http://www.gnu.org/licenses/">
 * > http://www.gnu.org/licenses/</a>.
 * @brief		TODO WRITEME
 * @details		TODO WRITEME
 */
#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include "event-handlers.hpp"
#include "../libsilly/defs.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <zmq.hpp>
#include <msgpack.hpp>
#include <stdio.h>
#include <stdlib.h>

void do_quit();

void blit(SDL_Surface* src_surf,
          const SDL_Rect* src_rect,
          SDL_Rect* dst_rect,
          zmq::socket_t sock);

#endif /* CLIENT_HPP_ */
