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
#include "winmgr.hpp"
#include "blitmgr.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main() {
    winmgr& wm = winmgr::get_winmgr();
    wm.listener_();
    blitmgr& bm = blitmgr::get_blitmgr();
    srand(time(0));
    SDL_Rect src_rect;
    SDL_Rect dst_rect;
    SDL_Surface* surf;
    surf = IMG_Load("/usr/share/icons/oxygen/32x32/emotes/face-smile.png");
    src_rect.x = 0; src_rect.y = 0; src_rect.w = 32; src_rect.h = 32;
    for (int i = 0; i < 2048; i++) {
        dst_rect.x = rand() % 1334; dst_rect.y = rand() % 688; dst_rect.w = 32; dst_rect.h = 32;
        bm.blit(surf, &src_rect, &dst_rect);
    }
    return 0;
}
