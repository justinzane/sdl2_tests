/**
 * @file 		silly.hpp is part of sdl2_tests
 * @author		justin
 * @date		Dec 2, 2013
 * @copyright   Copyright justin, 2013
 * @section		License GPLv3
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
 * > along with sdl2_tests.  If not, see http://www.gnu.org/licenses/ .
 * @brief		TODO WRITEME
 * @details		TODO WRITEME
 */
#ifndef SILLY_HPP_
#define SILLY_HPP_

#include "../libsilly/defs.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <atomic>
#include <cmath>
#include <cstdbool>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <tuple>
#include <unordered_map>
#include <valarray>

// sdl2 stuff
SDL_Window*   wind_;
SDL_Renderer* rend_;
SDL_Surface*  scrn_;
SDL_Texture*  txtr_;
SDL_DisplayMode disp_mode_;
Uint32 pixfmt_;
int disp_w_;
int disp_h_;
Sint32 win_size[2] {0,0};                           /**< Silly holder for current window size. */
SDL_Surface* sample_img {nullptr};
SDL_Surface* changed_img {nullptr};
static bool stop_ {false};

/** WRITEME */
void quit(int signal) {
    fprintf(stderr, "Received signal %d.\n", signal);
    stop_ = true;
}

/** @brief base handler for all SDL_Events, distributes or ignores them as needed. */
void handler(const SDL_Event* evt);

/** @brief base handler for all Window Events. */
void handle_window_event(const SDL_Event* event);

/** @brief silly handler for mouse movement. */
void handle_mouse_motion(const SDL_Event* evt);

/** @brief silly handler for text input. */
void handle_text_input(const SDL_Event* evt);

/** @brief handler for window resizes. */
void handle_window_resized(const SDL_Event* evt);


#endif /* SILLY_HPP_ */
