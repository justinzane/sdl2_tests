/**
 * @file 		main.cpp is part of Project winmgr
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
#include "blitmgr.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <chrono>

int main() {
    fprintf(stdout, "client: got winmgr& ...\n");
    blitmgr& bm = blitmgr::get_blitmgr();
    fprintf(stdout, "client: got blitmgr& ...\n");
    srand48(time(0));
    SDL_Rect src_rect;
    SDL_Rect dst_rect;
    SDL_Surface* surf;
    surf = SDL_CreateRGBSurface(0,32,32,32,RMASK,GMASK,BMASK,AMASK);
    src_rect.x = 0; src_rect.y = 0; src_rect.w = 32; src_rect.h = 32;
    Uint32 color = 0;
    for (int i = 0; i < 2048; i++) {
        color = 0xff000000 + (lrand48() % 0x00ffffff);
        SDL_FillRect(surf, NULL, color);
        dst_rect.x = lrand48() % 1334;
        dst_rect.y = lrand48() % 688;
        dst_rect.w = 32;
        dst_rect.h = 32;
        bm.blit(surf, &src_rect, &dst_rect);
//        wm.blit_(*surf, src_rect, dst_rect, (Uint64)i);
        if ((i % 128) == 0) {
            fprintf(stdout, "client loop iteration %d\n", i);
            timespec ts1, ts2;
            ts1.tv_sec = 0;
            ts1.tv_nsec = 30000000;
            nanosleep(&ts1, &ts2);
        }
    }
    bm.quit();
    return 0;
}
