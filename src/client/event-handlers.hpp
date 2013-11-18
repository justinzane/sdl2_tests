/**
 * @file 		event-handlers.hpp is part of Project sdl2_tests
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
#ifndef EVENT_HANDLERS_HPP_
#define EVENT_HANDLERS_HPP_

#include "client.hpp"
#include <SDL2/SDL.h>

/**
 * @namespace client    convenience namespace for quitter.
 */
namespace client {
/** @brief count cows by satellite. */
static bool quit_client_loop = false;
/** @brief LEts the client loop know that it is time to exit. */
inline bool should_quit() { return quit_client_loop; }
/** @brief Causes the client loop to exit on next iteration.*/
inline void do_quit() { quit_client_loop = true; }
}
/**
 * @brief base handler for all SDL_Events, distributes or ignores them as needed.
 * @param evt
 */
void handler(const SDL_Event* evt);

/**
 * @brief base handler for all Window Events.
 * @param event
 */
void handle_window_event(const SDL_Event* event);

#endif /* EVENT_HANDLERS_HPP_ */
