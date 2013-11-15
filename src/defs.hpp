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

typedef struct blit_params {
    public:
        int w;                  /**< src_surf->w */
        int h;                  /**< src_surf->h */
        std::vector<Uint32> pixdata;     /**< src_surf->pixels */
        int src_x;              /**< src_rect->x */
        int src_y;              /**< src_rect->y */
        int src_w;              /**< src_rect->w */
        int src_h;              /**< src_rect->h */
        int dst_x;              /**< dst_rect->x */
        int dst_y;              /**< dst_rect->y */
        int dst_w;              /**< dst_rect->w */
        int dst_h;              /**< dst_rect->h */

        blit_params() :
            w(0),
            h(0),
            src_x(0),
            src_y(0),
            src_w(0),
            src_h(0),
            dst_x(0),
            dst_y(0),
            dst_w(0),
            dst_h(0)
        {};
        blit_params(SDL_Surface*    src_surf,
                    const SDL_Rect* src_rect,
                    SDL_Rect*       dst_rect) :
            w(src_surf->w),
            h(src_surf->h),
            src_x(src_rect->x),
            src_y(src_rect->y),
            src_w(src_rect->w),
            src_h(src_rect->h),
            dst_x(dst_rect->x),
            dst_y(dst_rect->y),
            dst_w(dst_rect->w),
            dst_h(dst_rect->h)
        {};
        MSGPACK_DEFINE(w, h, pixdata, src_x, src_y, src_w, src_h, dst_x, dst_w, dst_x, dst_h);

} blit_params_t;

#endif /* DEFS_HPP_ */
