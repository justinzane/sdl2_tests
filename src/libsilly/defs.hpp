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
#include <cstdio>
#include <stdlib.h>
#include <type_traits>
#include <valarray>
#include <vector>

/** @defgroup CnE Constants and Enums ********************************************************/

/**@ingroup CnE
 * @brief Supported Channel Orders within 32 Bit Unsigned Int Pixels. */
typedef enum class pixel_order_t {
        ABGR,//!< ABGR  0xAABBGGRR
        ARGB,//!< ARGB  0xAARRGGBB
        BGRA,//!< BGRA  0xBBGGRRAA  (Default for SDL2 on little-endian machines.)
        RGBA,//!< RGBA  0xRRGGBBAA  (Most common order in end-user apps and references.)
        BOGUS//!< BOGUS Booooogus!
} pixel_order;

/**@ingroup CnE
 * @brief   Struct of constants for SDL2 Surfaces with ABGR order.*/
struct ABGR_consts {
    public:
        const pixel_order_t order {pixel_order_t::ABGR};
        const Uint32 amask {0xff000000};
        const Uint32 bmask {0x00ff0000};
        const Uint32 gmask {0x0000ff00};
        const Uint32 rmask {0x000000ff};
        const Uint32 ashift {24};
        const Uint32 bshift {16};
        const Uint32 gshift {8};
        const Uint32 rshift {0};
        const Uint8 bpp {32};
};

/**@ingroup CnE
 * @brief   Struct of constants for SDL2 Surfaces with ABGR order.*/
struct ARGB_consts {
    public:
        const pixel_order_t order {pixel_order_t::ABGR};
        const Uint32 amask {0xff000000};
        const Uint32 rmask {0x00ff0000};
        const Uint32 gmask {0x0000ff00};
        const Uint32 bmask {0x000000ff};
        const Uint32 ashift {24};
        const Uint32 rshift {16};
        const Uint32 gshift {8};
        const Uint32 bshift {0};
        const Uint8 bpp {32};
};

/**@ingroup CnE
 * @brief   Struct of constants for SDL2 Surfaces with ABGR order.*/
struct BGRA_consts {
    public:
        const pixel_order_t order {pixel_order_t::ABGR};
        const Uint32 bmask {0xff000000};
        const Uint32 gmask {0x00ff0000};
        const Uint32 rmask {0x0000ff00};
        const Uint32 amask {0x000000ff};
        const Uint32 bshift {24};
        const Uint32 gshift {16};
        const Uint32 rshift {8};
        const Uint32 ashift {0};
        const Uint8 bpp {32};
};

/**@ingroup CnE
 * @brief   Struct of constants for SDL2 Surfaces with ABGR order.*/
struct RGBA_consts {
    public:
        static const pixel_order_t order {pixel_order_t::ABGR};
        static const Uint32 rmask {0xff000000};
        static const Uint32 gmask {0x00ff0000};
        static const Uint32 bmask {0x0000ff00};
        static const Uint32 amask {0x000000ff};
        static const Uint32 rshift {24};
        static const Uint32 gshift {16};
        static const Uint32 bshift {8};
        static const Uint32 ashift {0};
        static const Uint8 bpp {32};
};

/** @defgroup SRF SDL2 Surface Related Functions **********************************************/

/**@ingroup SRF
 * @brief Determines the channel order for subpixels; i.e. RGBA, ABGR, etc. */
pixel_order get_surf_order(SDL_Surface* surf);

/**@ingroup SRF
 * @brief Change the channel order of subpixel data within a surface. */
void surf_remap(SDL_Surface* src, SDL_Surface* dst);

/**@ingroup SRF
 * @brief  Fill the surf with the data from pixar.
 * @details Denormalizes the floating point data to the 0-255 range. */
void pixar2surf(double* pixar, SDL_Surface* surf);

/**@ingroup SRF
 * @brief   Fill pixar with the data from surf.
 * @details frees the contents of pixar, then normalizes the 0-255 data to the 0.0-1.0 range. */
void surf2pixar(SDL_Surface* surf, double* pixar);

void surf_change_nothing(SDL_Surface* surf, double bogus __attribute__((unused)));

/**@ingroup SRF
 * @brief   Change the hue of the surface by -180.0 to 180.0 degrees.
 * @details Red + 120deg = Green, Red - 120deg = Blue, etc.
 * @note    This conversion is done in CIEL*a*b* space. */
void surf_change_hue(SDL_Surface* surf, double hue_adj_deg);

/**@ingroup SRF
 * @brief   Change the saturation of the surface by -100.0% to 100% degrees.
 * @details No saturation is greyscale, full saturation is cartoon vivid.
 * @note    This conversion is done in CIEL*a*b* space. */
void surf_change_sat(SDL_Surface* surf, double sat_adj_pct);

/**@ingroup SRF
 * @brief   Change the brightness of the surface by -100.0% to 100% degrees.
 * @details No brightness is black, full brightness is white.
 * @note    This conversion is done in CIEL*a*b* space. */
void surf_change_lum(SDL_Surface* surf, double lum_adj_pct);

/**@ingroup SRF
 * @brief   The absolute difference, per pixel per channel between surfaces in 32 bpp format.
 * @details This also takes the difference between alphas, so this is likely **not** what
 * you want since two opaque pixels will become transparent. */
void surf_diff_rgba(SDL_Surface* a, SDL_Surface* b, SDL_Surface* diff);

/**@ingroup SRF
 * @brief   The absolute difference, per pixel per RGB channel between surfaces in 32 bpp format.
 * @details This function **averages** the two alpha values per pixel. */
void surf_diff_rgbx(SDL_Surface* a, SDL_Surface* b, SDL_Surface* diff);

/**@ingroup SRF
 * @brief   True if BGRA. */
bool is_surf_bgra(SDL_Surface* surf);

/**@ingroup SRF
 * @brief   True if RGBA. */
bool is_surf_rgba(SDL_Surface* surf);

/**@ingroup SRF
 * @brief   True if ARGB. */
bool is_surf_argb(SDL_Surface* surf);

/**@ingroup SRF
 * @brief   True if ABGR. */
bool is_surf_abgr(SDL_Surface* surf);

/** @defgroup CLR_def Color Definitions *******************************************************/

/**@ingroup CLR_def
 * @brief Matrix for conversion of CIEXYZ to RGB */
const double XYZ2RGB_MAT[3][3] =
    { {  0.41847  , -0.091169 ,  0.0009209},
      { -0.15866  ,  0.25243  , -0.0025498},
      { -0.082835 ,  0.015708 ,  0.1786   }};

/**@ingroup CLR_def
 * @brief Matrix for conversion of RGB to CIEXYZ */
const double RGB2XYZ_MAT[3][3]
    { { 2.76883088,  1.        ,  0.        },
      { 1.75170933,  4.59060858,  0.05650675},
      { 1.13013505,  0.06006668,  5.5941685 } };

/**@ingroup CLR_def
 * @brief CIE X tristimulus value at D65. */
const double X_d65 { 95.047};

/**@ingroup CLR_def
 * @brief CIE Y tristimulus value at D65. */
const double Y_d65 {100.000};

/**@ingroup CLR_def
 * @brief CIE Z tristimulus value at D65. */
const double Z_d65 {108.883};

/** @defgroup CLR_func Color Functions ********************************************************/

/**@ingroup CLR_func
 * @brief Change the hue of a surface by hue_adj_rad radians, considering hue to
 *  be circular from 0.0 rad = red to 2pi/3 rad = green to 4pi/3 rad = blue. */
void laba_change_hue(double* pixar, double hue_adj_rad);

/**@ingroup CLR_func
 * @brief Change the saturation of a surface by sat_adj, considering sat to
 *  be from 0.0 = greyscale to 1.0 = vivid. */
void laba_change_sat(double* pixar, double sat_adj);

/**@ingroup CLR_func
 * @brief Change the brightness of a surface by lum_adj degrees, considering lum to
 *  be from 0.0 = black to 1.0 = white. */
void laba_change_lum(double* pixar, double lum_adj);

/**@ingroup CLR_func
 * @brief converts an CIEL*a*b*A pixel into a RGBA pixel. */
void laba2rgba(double* pixar);

/**@ingroup CLR_func
 * @brief converts an RGBA pixel into a CIEL*a*b*A pixel. */
void rgba2laba(double* pixar);

/**@ingroup CLR_func
 * @brief converts an CIEL*a*b*A pixel into a CIEXYZA pixel. */
void laba2xyza(double* pixar);

/**@ingroup CLR_func
 * @brief converts a CIEXYZA pixel into a CIEL*a*b*A pixel. */
void xyza2laba(double* pixar);

/**@ingroup CLR_func
 * @brief converts an RGBA pixel into a CIEXYZA pixel. */
void rgba2xyza(double* pixar);

/**@ingroup CLR_func
 * @brief converts a CIEXYZA pixel into an ABGR pixel. */
void xyza2rgba(double* pixar);

/** @defgroup ZnM ZeroMQ and MessagePack ******************************************************/

/**@ingroup ZnM
 * @brief Gets the md5 hash of the vector contents to the back of the vector.
 * @note The MD5 algorithm was chosen because it is only 4 Uint32s. This is for
 * redundancy reduction, NOT for security. */
long long get_vec_hash(std::vector<Uint32>& vec);
long long get_vec_hash(std::vector<Uint8>& vec);

/**@ingroup ZnM
 * @brief Blindly convert an SDL_Event into a vector.
 * @details Since an SDL_Event is a ~56 byte (currently) union, just put the bytes in a
 * vector for packing with msgpack. Note that this size is subject to change. */
std::vector<Uint8> event2vec(SDL_Event* evt);

/**@ingroup ZnM
 * @brief Blindly convert an a vector to an SDL_Event.
 * @details Since an SDL_Event is a ~56 byte (currently) union, just take the bytes from a
 * vector for unpacked with msgpack. Note that this size is subject to change. */
SDL_Event vec2event(std::vector<Uint8> vec);

/**@ingroup ZnM
 * @brief Converts everything necessary to call SDL_BlitSurface into a vector. */
std::vector<Uint32> blitparams2vec(SDL_Surface*    src_surf,
                                   const SDL_Rect* src_rect,
                                   SDL_Rect*       dst_rect);

/**@ingroup ZnM
 * @brief Converts a vector into a tuple of the arguments to SDL_BlitSurface. */
std::tuple<SDL_Surface, SDL_Rect, SDL_Rect> vec2blitparams(std::vector<Uint32> bv);

/** @defgroup ZMQ ZMQ Socket Addresses ********************************************************/
/**@ingroup ZMQ
 * @def Address for display server reply socket. Recvs commands from clients. */
#define SRVR_REP_ADDR   "tcp://127.0.0.1:19090"
/**@ingroup ZMQ
 * @def Address for display server pull socket. Recvs images from clients. */
#define SRVR_PULL_ADDR  "tcp://127.0.0.1:19091"
/**@ingroup ZMQ
 * @def Address for display server publish socket. Sends events to clients. */
#define SRVR_PUB_ADDR   "tcp://127.0.0.1:19092"
/**@ingroup ZMQ
 * @def Address for game client request socket. Sends commands from clients. */
#define CLNT_REQ_ADDR   "tcp://127.0.0.1:19990"
/**@ingroup ZMQ
 * @def Address for game client push socket. Sends images from clients. */
#define CLNT_PUSH_ADDR  "tcp://127.0.0.1:19991"
/**@ingroup ZMQ
 * @def Address for game client subscribe socket. Recvs events from clients. */
#define CLNT_SUB_ADDR   "tcp://127.0.0.1:19992"
/**@ingroup ZMQ
 * @def Millisecs to process queued messages before close. Default infinite wait.*/
#define ZMQ_SOCK_LINGER 1000

#endif /* DEFS_HPP_ */
