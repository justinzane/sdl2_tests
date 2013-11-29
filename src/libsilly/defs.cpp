/**
 * @file 		defs.cpp is part of Project sdl2_test
 * @author		justin
 * @date		Nov 15, 2013
 * @copyright   Copyright justin, Nov 15, 2013
 * @section		<license> License
 * > sdl2_test is free software: you can redistribute it and/or modify
 * > it under the terms of the GNU General Public License as published by
 * > the Free Software Foundation, either version 3 of the License, or
 * > (at your option) any later version.
 * >
 * > sdl2_test is distributed in the hope that it will be useful,
 * > but WITHOUT ANY WARRANTY; without even the implied warranty of
 * > MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * > GNU General Public License for more details.
 * >
 * > You should have received a copy of the GNU General Public License
 * > along with sdl2_test.  If not, see <a href="http://www.gnu.org/licenses/">
 * > http://www.gnu.org/licenses/</a>.
 * @brief		TODO WRITEME
 * @details		TODO WRITEME
 */

#include "defs.hpp"
#include <emmintrin.h>

void surf_diff(SDL_Surface* a, SDL_Surface* b, SDL_Surface* diff) {
    if ((a->w * a->h * a->format->BitsPerPixel != b->w * b->h * b->format->BitsPerPixel) ||
        (a->w * a->h * a->format->BitsPerPixel != diff->w * diff->h * diff->format->BitsPerPixel)) {
        throw std::invalid_argument("Must be same size.");
    }
    SDL_LockSurface(a); SDL_LockSurface(b); SDL_LockSurface(diff);
    for (int i = 0; i < (a->h * a->w * 4); i++) {
        ((Uint8*)diff->pixels)[i] = abs(((Uint8*)a->pixels)[i] - ((Uint8*)b->pixels)[i]);
    }
    SDL_UnlockSurface(a); SDL_UnlockSurface(b); SDL_UnlockSurface(diff);
}

void surf_change_hue(SDL_Surface* surf, double hue_adj_deg) {
    assert(surf != nullptr &&
           surf->h > 0 &&
           surf->w > 0);
    const Uint32 numsubpix = (surf->h * surf->w * 4);
    double* surfpix = static_cast<double*> (::operator new (sizeof(double[numsubpix])));;
    surf2pixar(surf, surfpix);
    for (int i = 0; i < (surf->h * surf->w); i++) {
        double* curpix = surfpix + i * 4;
        rgba2laba(curpix);
        laba_change_hue(curpix, hue_adj_deg);
        laba2rgba(curpix);
    }
    pixar2surf(surfpix, surf);
}

void laba_change_hue(double* laba, double hue_adj_deg) {
    double hue_adj = hue_adj_deg * M_PI / 180.0;
    double hue = std::atan2(laba[1], laba[2]) + hue_adj;
    double chroma = std::sqrt(std::pow(laba[1], 2.0) + std::pow(laba[2], 2.0));
    laba[1] = (chroma * std::sin(hue));
    laba[2] = (chroma * std::cos(hue));
}

void laba_change_hue(subpixar_t<double>& laba, double hue_adj_deg) {
    double hue_adj = hue_adj_deg * M_PI / 180.0;
    double hue = std::atan2(laba[1], laba[2]) + hue_adj;
    double chroma = std::sqrt(std::pow(laba[1], 2.0) + std::pow(laba[2], 2.0));
    laba[1] = (chroma * std::sin(hue));
    laba[2] = (chroma * std::cos(hue));
}

void laba2rgba(double* pixar) {
    laba2xyza(pixar);
    xyza2rgba(pixar);
}

subpixar_t<double> laba2rgba(subpixar_t<double>& laba) {
    subpixar_t<double> xyza = laba2xyza(laba);
    return xyza2rgba(xyza);
}

void rgba2laba(double* pixar) {
    rgba2xyza(pixar);
    xyza2laba(pixar);
}

subpixar_t<double> rgba2laba(subpixar_t<double>& rgba) {
    subpixar_t<double> xyza = rgba2xyza(rgba);
    return xyza2laba(xyza);
}

void laba2xyza(double* pixar) {
/*       X = Xn * ( P + a* / 500 )^3
 *       Y = Yn * P^3
 *       Z = Zn * ( P - b* / 200 )^3
 * where P = (L* + 16) / 116 */
    double x, y, z;
    double p = (pixar[0] + 16.0) / 116.0;
    x = X_d65 * std::pow((p + pixar[1] / 500.0), 3);
    y = Y_d65 * std::pow(p, 3);
    z = Z_d65 * std::pow((p - pixar[2] / 200.0), 3);
    pixar[0] = x; pixar[1] = y; pixar[2] = z; // pixar[3] = unchanged alpha
}

subpixar_t<double> laba2xyza(subpixar_t<double>& laba) {
    subpixar_t<double> xyza (4);
/*       X = Xn * ( P + a* / 500 )^3
 *       Y = Yn * P^3
 *       Z = Zn * ( P - b* / 200 )^3
 * where P = (L* + 16) / 116 */
    double p = (laba[0] + 16.0) / 116.0;
    xyza[0] = X_d65 * std::pow((p + laba[1] / 500.0), 3);
    xyza[1] = Y_d65 * std::pow(p, 3);
    xyza[2] = Z_d65 * std::pow((p - laba[2] / 200.0), 3);
    xyza[3] = laba[3];
    return xyza;
}

double _f_(double x) {
    if (x > 0.008856) {
        return std::pow(x, 1.0/3.0);
    } else {
        return (7.787 * x + 16/116);
    }
}

void xyza2laba(double* pixar) {
    double Lstar, astar, bstar;
    if ((pixar[1] / Y_d65) > 0.008856) {
        Lstar = 116.0 * std::pow((pixar[1] / Y_d65), 1.0/3.0) - 16.0;
    } else {
        Lstar = 903.3 *           pixar[1] / Y_d65;
    }
    astar = 500.0 * (_f_(pixar[0] / X_d65) - _f_(pixar[1] / Y_d65));
    bstar = 200.0 * (_f_(pixar[1] / Y_d65) - _f_(pixar[2] / Z_d65));
    pixar[0] = Lstar; pixar[1] = astar; pixar[2] = bstar; // pixar[3] = unchanged alpha
}

subpixar_t<double> xyza2laba(subpixar_t<double>& xyza) {
    subpixar_t<double> laba (4);
    if ((xyza[1] / Y_d65) > 0.008856) {
        laba[0] = 116.0 * std::pow((xyza[1] / Y_d65), 1.0/3.0) - 16.0;
    } else {
        laba[0] = 903.3 *           xyza[1] / Y_d65;
    }
    laba[1] = 500.0 * (_f_(xyza[0] / X_d65) - _f_(xyza[1] / Y_d65));
    laba[2] = 200.0 * (_f_(xyza[1] / Y_d65) - _f_(xyza[2] / Z_d65));
    laba[3] = xyza[3];
    return laba;
}

void rgba2xyza(double* pixar) {
    double x, y, z;
    x = RGB2XYZ_MAT[0][0] * pixar[0] + RGB2XYZ_MAT[0][1] * pixar[1] + RGB2XYZ_MAT[0][2] * pixar[2];
    y = RGB2XYZ_MAT[1][0] * pixar[0] + RGB2XYZ_MAT[1][1] * pixar[1] + RGB2XYZ_MAT[1][2] * pixar[2];
    z = RGB2XYZ_MAT[2][0] * pixar[0] + RGB2XYZ_MAT[2][1] * pixar[1] + RGB2XYZ_MAT[2][2] * pixar[2];
    pixar[0] = x; pixar[1] = y; pixar[2] = z; // pixar[3] = unchanged alpha
}

subpixar_t<double> rgba2xyza(subpixar_t<double>& rgba) {
    subpixar_t<double> xyza (4);
    xyza[0] = RGB2XYZ_MAT[0][0] * rgba[0] + RGB2XYZ_MAT[0][1] * rgba[1] + RGB2XYZ_MAT[0][2] * rgba[2];
    xyza[1] = RGB2XYZ_MAT[1][0] * rgba[0] + RGB2XYZ_MAT[1][1] * rgba[1] + RGB2XYZ_MAT[1][2] * rgba[2];
    xyza[2] = RGB2XYZ_MAT[2][0] * rgba[0] + RGB2XYZ_MAT[2][1] * rgba[1] + RGB2XYZ_MAT[2][2] * rgba[2];
    xyza[3] = rgba[3];
    return xyza;
}

void xyza2rgba(double* pixar) {
    double r, g, b;
    r = XYZ2RGB_MAT[0][0] * pixar[0] + XYZ2RGB_MAT[0][1] * pixar[1] + XYZ2RGB_MAT[0][2] * pixar[2];
    g = XYZ2RGB_MAT[1][0] * pixar[0] + XYZ2RGB_MAT[1][1] * pixar[1] + XYZ2RGB_MAT[1][2] * pixar[2];
    b = XYZ2RGB_MAT[2][0] * pixar[0] + XYZ2RGB_MAT[2][1] * pixar[1] + XYZ2RGB_MAT[2][2] * pixar[2];
    pixar[0] = r; pixar[1] = g; pixar[2] = b; //pixar[3] = unchanged alpha
}

subpixar_t<double> xyza2rgba(subpixar_t<double>& xyza) {
    subpixar_t<double> rgba (4);
    rgba[0] = XYZ2RGB_MAT[0][0] * xyza[0] + XYZ2RGB_MAT[0][1] * xyza[1] + XYZ2RGB_MAT[0][2] * xyza[2];
    rgba[1] = XYZ2RGB_MAT[1][0] * xyza[0] + XYZ2RGB_MAT[1][1] * xyza[1] + XYZ2RGB_MAT[1][2] * xyza[2];
    rgba[2] = XYZ2RGB_MAT[2][0] * xyza[0] + XYZ2RGB_MAT[2][1] * xyza[1] + XYZ2RGB_MAT[2][2] * xyza[2];
    rgba[3] = xyza[3];
    return rgba;
}

void pixar2surf(double* pixar, SDL_Surface* surf) {
    SDL_LockSurface(surf);
    Uint8* pix = (Uint8*)surf->pixels;
    for (Uint32 i = 0; i < (surf->h * surf->w * 4); i++) {
        pix[i] = (Uint8)(pixar[i] * 255.0);
    }
    SDL_UnlockSurface(surf);
}

void pixar2surf(pixar_t<double>& pixar, SDL_Surface* surf) {
    const Uint32 h = pixar.size();
    const Uint32 w = pixar[0].size();
    const Uint32 chans = pixar[0][0].size();
    SDL_LockSurface(surf);
    Uint32* intpix = (Uint32*)surf->pixels;
    for (Uint32 y = 0; y < h; y++) {
        for (Uint32 x = 0; x < w; x++) {
            for (Uint32 c = 0; c < chans; c++) {
                if (pixar[y][x][c] < 0.0) {
                    (((Uint8*) (intpix + (y * w + x)))[c]) = 0;
                } else if (pixar[y][x][c] > 1.0) {
                    (((Uint8*) (intpix + (y * w + x)))[c]) = 255;
                } else {
                    (((Uint8*) (intpix + (y * w + x)))[c]) = (Uint8)(pixar[y][x][c] * 255.0);
                }
            }
        }
    }
    SDL_UnlockSurface(surf);
}

void surf2pixar(SDL_Surface* surf, double* pixar) {
    assert(surf != nullptr &&
           surf->h > 0 && surf->w > 0 &&
           surf->format->BitsPerPixel == BPP &&
           surf->format->Amask == AMASK &&
           surf->format->Rmask == RMASK &&
           surf->format->Gmask == GMASK &&
           surf->format->Bmask == BMASK);
    if (pixar != nullptr) {
        free((void*)pixar);
    }
    pixar = (double*)malloc((surf->h * surf->w * 4 * sizeof(double)));
    SDL_LockSurface(surf);
    for (int i = 0; i < (surf->h * surf->w * 4); i++) {
        pixar[i] = ( (double) ((Uint8*)surf->pixels)[i] ) / 255.0;
    }
    SDL_UnlockSurface(surf);
}

pixar_t<double> surf2pixar(SDL_Surface* surf) {
    using namespace std;
    assert(surf != nullptr &&
           surf->h > 0 && surf->w > 0 &&
           surf->format->BitsPerPixel == BPP &&
           surf->format->Amask == AMASK &&
           surf->format->Rmask == RMASK &&
           surf->format->Gmask == GMASK &&
           surf->format->Bmask == BMASK);

    SDL_LockSurface(surf);
    const Uint32* intpix = (Uint32*)surf->pixels;
    const Uint32 h = surf->h; const Uint32 w = surf->w; const Uint32 chans = 4;

    pixar_t<double> pixar = valarray<valarray<valarray<double> > >(h);
    for (Uint32 y = 0; y < h; y++) {
        pixar[y] = valarray<valarray<double> >(w);
        for (Uint32 x = 0; x < w; x++) {
            pixar[y][x] = valarray<double>(chans);
            Uint8* pixptr = (Uint8*) (intpix + (y * w + x));
            for (Uint32 c = 0; c < chans; c++) {
                pixar[y][x][c] = (double)pixptr[c] / 255.0;
            }
        }
    }
    SDL_UnlockSurface(surf);
    return pixar;
}

long long get_vec_hash(std::vector<Uint32>& vec) {
    long long digest;
    gcry_md_hash_buffer(GCRY_MD_MD5, (void*)&digest, (void*)vec.data(), vec.size());
    return digest;
}

long long get_vec_hash(std::vector<Uint8>& vec) {
    long long digest;
    gcry_md_hash_buffer(GCRY_MD_MD5, (void*)&digest, (void*)vec.data(), vec.size());
    return digest;
}

/** @todo Modify this to use OpenMP/Cilk+/OpenACC/magic. */
std::vector<Uint8> event2vec(SDL_Event* evt) {
    std::vector<Uint8> vec;
    for (Uint32 i = 0; i < sizeof(SDL_Event); i++) {
        vec.push_back( ((Uint8*)evt)[i] );
    }
    vec.shrink_to_fit();
    return vec;
}

/** @todo Modify this to use OpenMP/Cilk+/OpenACC/magic. */
SDL_Event vec2event(std::vector<Uint8> vec) {
    SDL_Event evt;
    for (Uint32 i = 0; i < sizeof(SDL_Event); i++) {
        ((Uint8*)&evt)[i] = vec[i];
    }
    return evt;
}

/** @todo Modify this to use OpenMP/Cilk+/OpenACC/magic. */
std::vector<Uint32> blitparams2vec(SDL_Surface*    src_surf,
                                   const SDL_Rect* src_rect,
                                   SDL_Rect*       dst_rect) {
    std::vector<Uint32> bv;
    bv.push_back(src_surf->w);  // 0
    bv.push_back(src_surf->h);  // 1
    bv.push_back(src_rect->x);  // 2
    bv.push_back(src_rect->y);  // 3
    bv.push_back(src_rect->w);  // 4
    bv.push_back(src_rect->h);  // 5
    bv.push_back(dst_rect->x);  // 6
    bv.push_back(dst_rect->y);  // 7
    bv.push_back(dst_rect->w);  // 8
    bv.push_back(dst_rect->h);  // 9
    SDL_LockSurface(src_surf);
    Uint32* surfpix = (Uint32*)src_surf->pixels;
    for (Uint64 i = 0; i < (Uint64)(src_surf->h * src_surf->w); i++) {
        bv.push_back(surfpix[i]);  //10 -> x*y+10
    };
    SDL_UnlockSurface(src_surf);
    bv.shrink_to_fit();
    return bv;
}

/** @todo Modify this to use OpenMP/Cilk+/OpenACC/magic. */
std::tuple<SDL_Surface, SDL_Rect, SDL_Rect> vec2blitparams(std::vector<Uint32> bv) {
    SDL_Rect sr, dr;
    Uint32 ssw = bv[0];
    Uint32 ssh = bv[1];
    sr.x = bv[2];
    sr.y = bv[3];
    sr.w = bv[4];
    sr.h = bv[5];
    dr.x = bv[6];
    dr.y = bv[7];
    dr.w = bv[8];
    dr.h = bv[9];
    Uint32 ssp[ssw*ssh];
    for (Uint64 i = 0; i < (ssw*ssh); i++){
        ssp[i] = bv[i+10];
    }
    SDL_Surface* ss = SDL_CreateRGBSurfaceFrom(ssp, ssw, ssh, BPP, 4*ssw, RMASK, GMASK, BMASK, AMASK);
    return std::tuple<SDL_Surface, SDL_Rect, SDL_Rect>(*ss, sr, dr);
}

