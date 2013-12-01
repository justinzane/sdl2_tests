/**
 * @file 		defs.hpp is part of Project sdl2_utils
 * @author		justin
 * @date		Nov 12, 2013
 * @copyright   Copyright justin, Nov 12, 2013
 * @section		License GPLv3
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
 * @details
 * - "rgba" is a reference to a color in the common RGB space with an alpha channel
 * - "xyza" is a reference to a color in the CIEXYZ space with an alpha channel
 * - "laba" is a reference to a color in the CIEL*a*b* space with an alpha channel
 * @cite http://www.cs.rit.edu/~ncs/color/t_convert.html#RGB%20to%20XYZ%20&%20XYZ%20to%20RGB
 * @cite https://en.wikipedia.org/wiki/Illuminant_D65
 * @cite
 */
#ifndef DEFS_HPP_
#define DEFS_HPP_

#include <SDL2/SDL.h>
#include <assert.h>
#include <math.h>
#include <msgpack.hpp>
#include <gcrypt.h>
#include <stdlib.h>
#include <type_traits>
#include <valarray>
#include <vector>

/**@defgroup    SDL_Defines
 * @brief       These are SDL2 related "standards used throughout the application.
 * @details
 * One of the design choices is to only use 32 bit per pixel ARGB images. These are intended for
 * use with SDL_CreateRGBSurface() to prevent confusion and limit typos.
 */
#define AMASK  0xff000000
#define BMASK  0x00ff0000
#define GMASK  0x0000ff00
#define RMASK  0x000000ff
#define ASHIFT 24
#define BSHIFT 16
#define GSHIFT  8
#define RSHIFT  0
#define BPP    32

/** @defgroup ZMQ_Socket_Addresses */
/** @def Address for display server reply socket. Recvs commands from clients. */
#define SRVR_REP_ADDR   "tcp://127.0.0.1:19090"
/** @def Address for display server pull socket. Recvs images from clients. */
#define SRVR_PULL_ADDR  "tcp://127.0.0.1:19091"
/** @def Address for display server publish socket. Sends events to clients. */
#define SRVR_PUB_ADDR   "tcp://127.0.0.1:19092"
/** @def Address for game client request socket. Sends commands from clients. */
#define CLNT_REQ_ADDR   "tcp://127.0.0.1:19990"
/** @def Address for game client push socket. Sends images from clients. */
#define CLNT_PUSH_ADDR  "tcp://127.0.0.1:19991"
/** @def Address for game client subscribe socket. Recvs events from clients. */
#define CLNT_SUB_ADDR   "tcp://127.0.0.1:19992"
/** @def Millisecs to process queued messages before close. Default infinite wait.*/
#define ZMQ_SOCK_LINGER 1000

/** @brief Matrix for conversion of CIEXYZ to RGB */
const std::valarray<std::valarray<double> > XYZ2RGB_MAT
    { {  0.41847  , -0.091169 ,  0.0009209},
      { -0.15866  ,  0.25243  , -0.0025498},
      { -0.082835 ,  0.015708 ,  0.1786   }};
/** { { 3.240479, -1.537150, -0.498535 },
      {-0.969256,  1.875992,  0.041556 },
      { 0.055648, -0.204043,  1.057311 } }; */

/** @brief Matrix for conversion of RGB to CIEXYZ */
const std::valarray<std::valarray<double> > RGB2XYZ_MAT
    { { 2.76883088,  1.        ,  0.        },
      { 1.75170933,  4.59060858,  0.05650675},
      { 1.13013505,  0.06006668,  5.5941685 } };
/**
    { { 0.412453,  0.357580,  0.180423 },
      { 0.212671,  0.715160,  0.072169 },
      { 0.019334,  0.119193,  0.950227 } };
 */


/** @brief CIE X tristimulus value at D65. */
const double X_d65 { 95.047};
/** @brief CIE Y tristimulus value at D65. */
const double Y_d65 {100.000};
/** @brief CIE Z tristimulus value at D65. */
const double Z_d65 {108.883};

/** @brief Change the hue of a surface by hue_adj_rad radians, considering hue to
 *  be circular from 0.0 rad = red to 2pi/3 rad = green to 4pi/3 rad = blue. */
void laba_change_hue(double* pixar, double hue_adj_rad);

/** @brief Change the saturation of a surface by sat_adj, considering sat to
 *  be from 0.0 = greyscale to 1.0 = vivid. */
void laba_change_sat(double* pixar, double sat_adj);

/** @brief Change the brightness of a surface by lum_adj degrees, considering lum to
 *  be from 0.0 = black to 1.0 = white. */
void laba_change_lum(double* pixar, double lum_adj);

/** @brief converts an CIEL*a*b*A pixel into a RGBA pixel. */
void laba2rgba(double* pixar);

/** @brief converts an RGBA pixel into a CIEL*a*b*A pixel. */
void rgba2laba(double* pixar);

/** @brief converts an CIEL*a*b*A pixel into a CIEXYZA pixel. */
void laba2xyza(double* pixar);

/** @brief converts a CIEXYZA pixel into a CIEL*a*b*A pixel. */
void xyza2laba(double* pixar);

/** @brief converts an RGBA pixel into a CIEXYZA pixel. */
void rgba2xyza(double* pixar);

/** @brief converts a CIEXYZA pixel into an ABGR pixel. */
void xyza2rgba(double* pixar);

/** @brief  Fill the surf with the data from pixar.
 * @details Denormalizes the 0.0-1.0 data to the 0-255 range. */
void pixar2surf(double* pixar, SDL_Surface* surf);

/** @brief   Fill pixar with the data from surf.
 *  @details frees the contents of pixar, then normalizes the 0-255 data to the 0.0-1.0 range. */
void surf2pixar(SDL_Surface* surf, double* pixar);

void surf_change_hue(SDL_Surface* surf, double hue_adj_deg);
void surf_change_sat(SDL_Surface* surf, double sat_adj_pct);
void surf_change_lum(SDL_Surface* surf, double lum_adj_pct);

void surf_diff(SDL_Surface* a, SDL_Surface* b, SDL_Surface* diff);

bool is_surf_bgra(SDL_Surface* surf);
bool is_surf_rgba(SDL_Surface* surf);
bool is_surf_argb(SDL_Surface* surf);
bool is_surf_abgr(SDL_Surface* surf);

/**@brief Gets the md5 hash of the vector contents to the back of the vector.
 * @note The MD5 algorithm was chosen because it is only 4 Uint32s. This is for
 * redundancy reduction, NOT for security. */
long long get_vec_hash(std::vector<Uint32>& vec);
long long get_vec_hash(std::vector<Uint8>& vec);

/**@brief Blindly convert an SDL_Event into a vector.
 * @details Since an SDL_Event is a ~56 byte (currently) union, just put the bytes in a
 * vector for packing with msgpack. Note that this size is subject to change. */
std::vector<Uint8> event2vec(SDL_Event* evt);

/**@brief Blindly convert an a vector to an SDL_Event.
 * @details Since an SDL_Event is a ~56 byte (currently) union, just take the bytes from a
 * vector for unpacked with msgpack. Note that this size is subject to change. */
SDL_Event vec2event(std::vector<Uint8> vec);

/** @brief Converts everything necessary to call SDL_BlitSurface into a vector. */
std::vector<Uint32> blitparams2vec(SDL_Surface*    src_surf,
                                   const SDL_Rect* src_rect,
                                   SDL_Rect*       dst_rect);

/** @brief Converts a vector into a tuple of the arguments to SDL_BlitSurface. */
std::tuple<SDL_Surface, SDL_Rect, SDL_Rect> vec2blitparams(std::vector<Uint32> bv);

#endif /* DEFS_HPP_ */
