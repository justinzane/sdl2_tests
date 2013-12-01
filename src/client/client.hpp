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

#define _USE_MATH_DEFINES

#include "client.hpp"
#include "../libsilly/defs.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <zmq.hpp>
#include <msgpack.hpp>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include <tuple>
#include <valarray>

// Variables ----------------------------------------------------------------------------------
static bool quit_client_loop = false;               /**< Counts cows by satellite. */
zmq::context_t zmqcntx_(3);                         /**< The only client ZMQ context. */
zmq::socket_t zmq_req_sock_(zmqcntx_, ZMQ_REQ);     /**< The socket to send commands to server. */
zmq::socket_t zmq_push_sock_(zmqcntx_, ZMQ_PUSH);   /**< The socket to push images to server. */
zmq::socket_t zmq_sub_sock_(zmqcntx_, ZMQ_SUB);     /**< The socket to get events from server. */
/** A simplistic cache for images sent to server, intented to limit redundant messages. */
std::unordered_map<long long, std::vector<Uint32> > surf_cache {};
Sint32 win_size[2] {0,0};                           /**< Silly holder for current window size. */
SDL_Surface* sample_img = nullptr;
SDL_Surface* changed_img = nullptr;

// Functions ----------------------------------------------------------------------------------
/** @brief Called by client loop for exit. */
inline bool should_quit() { return quit_client_loop; }

/** @brief Causes client loop to exit.*/
void do_quit();

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

/** @brief returns true if argument was added to cache, false if it already in cache. */
bool cache_blitparam_vec(std::vector<Uint32>& bp_vec);

/**
 * @brief   Alpha composition of top (RGBA8888) pixel onto bottom pixel using the
 * Porter-Duff Over method.
 * @cite    https://en.wikipedia.org/wiki/Alpha_compositing
 * @todo    OPTIMIZEME via SSE/OpenMP/OpenCL
 */
void porter_duff_over(Uint32* top, Uint32* bot, Uint32* cmp);

void surface_blur(SDL_Surface* src, SDL_Surface* dst, Uint8 amount);

/**
 * @brief Adjust the color of a surface by changing any HSV parameter.
 * @note  This is a wrapper for individual hue, sat and val functions for performance
 * raisins.
 * @cite  Wikipedia provides a good explanation: https://en.wikipedia.org/wiki/HSL_and_HSV
 * @param surf      The image to be adjusted.
 * @param hue_diff  The change in hue           0.0f <= hue_diff <  360.0f;
 * @param sat_diff  The change in saturation    0.0f <= sat_diff <=   1.0f;
 * @param val_diff  The change in value         0.0f <= val_diff <=   1.0f;
 */
void surface_change_hsv(SDL_Surface* src_surf, SDL_Surface* dst_surf,
                        float hue_diff = 0.0f,
                        float sat_diff = 0.0f,
                        float val_diff = 0.0f);

/**
 * @brief Adjust the color of a surface by changing hue.
 * @cite  Wikipedia provides a good explanation: https://en.wikipedia.org/wiki/HSL_and_HSV
 * @param surf      The image to be adjusted.
 * @param hue_diff  The change in hue           0.0f <= hue_diff <  360.0f;
 */
void surface_change_hue(SDL_Surface* src_surf, SDL_Surface* dst_surf, float hue_diff);

/**
 * @brief Adjust the color of a surface by changing saturation.
 * @cite  Wikipedia provides a good explanation: https://en.wikipedia.org/wiki/HSL_and_HSV
 * @param surf      The image to be adjusted.
 * @param sat_diff  The change in saturation    0.0f <= sat_diff <=   1.0f;
 */
void surface_change_sat(SDL_Surface* src_surf, SDL_Surface* dst_surf, float sat_diff);

/**
 * @brief Adjust the color of a surface by changing value.
 * @cite  Wikipedia provides a good explanation: https://en.wikipedia.org/wiki/HSL_and_HSV
 * @param surf      The image to be adjusted.
 * @param val_diff  The change in value         0.0f <= val_diff <=   1.0f;
 */
void surface_change_val(SDL_Surface* src_surf, SDL_Surface* dst_surf, float val_diff);

void surface_compose_overlay(SDL_Surface* top, int top_offset_x, int top_offset_y,
                             SDL_Surface* bot, int bot_offset_x, int bot_offset_y,
                             SDL_Surface* dst);

void surface_shadow(SDL_Surface* src, SDL_Surface* dst, int offset_x, int offset_y);

/**
 * @brief Sends a surface to the server for rendering.
 * @param src_surf  the image to be sent
 * @param src_rect  the wanted portion of the image
 * @param dst_rect  where to render on the window
 */
void blit(SDL_Surface* src_surf, const SDL_Rect* src_rect, SDL_Rect* dst_rect);

#endif /* CLIENT_HPP_ */
