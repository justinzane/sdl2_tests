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

/* @defgroup SRF SDL2 Surface Related Functions **********************************************/

void pixar2surf(double* pixar, SDL_Surface* surf) {
    SDL_LockSurface(surf);
    Uint8* pix = (Uint8*)surf->pixels;
    if (is_surf_abgr(surf)) {
        for (int i = 0; i < (surf->h * surf->w * 4); i += 4) {
            (pixar[0+i] > 1.0) ? pix[3+i] = 255 : (pixar[0+i] < 0.0) ? pix[3+i] = 0 : pix[3+i] = Uint8(pixar[0+i] * 255.0);
            (pixar[1+i] > 1.0) ? pix[2+i] = 255 : (pixar[1+i] < 0.0) ? pix[2+i] = 0 : pix[2+i] = Uint8(pixar[1+i] * 255.0);
            (pixar[2+i] > 1.0) ? pix[1+i] = 255 : (pixar[2+i] < 0.0) ? pix[1+i] = 0 : pix[1+i] = Uint8(pixar[2+i] * 255.0);
            (pixar[3+i] > 1.0) ? pix[0+i] = 255 : (pixar[3+i] < 0.0) ? pix[0+i] = 0 : pix[0+i] = Uint8(pixar[3+i] * 255.0);
        }
    } else if (is_surf_argb(surf)) {
        for (int i = 0; i < (surf->h * surf->w * 4); i += 4) {
            (pixar[0+i] > 1.0) ? pix[3+i] = 255 : (pixar[0+i] < 0.0) ? pix[3+i] = 0 : pix[3+i] = Uint8(pixar[0+i] * 255.0);
            (pixar[1+i] > 1.0) ? pix[0+i] = 255 : (pixar[1+i] < 0.0) ? pix[0+i] = 0 : pix[0+i] = Uint8(pixar[1+i] * 255.0);
            (pixar[2+i] > 1.0) ? pix[1+i] = 255 : (pixar[2+i] < 0.0) ? pix[1+i] = 0 : pix[1+i] = Uint8(pixar[2+i] * 255.0);
            (pixar[3+i] > 1.0) ? pix[2+i] = 255 : (pixar[3+i] < 0.0) ? pix[2+i] = 0 : pix[2+i] = Uint8(pixar[3+i] * 255.0);
        }
    } else if (is_surf_bgra(surf)) {
        for (int i = 0; i < (surf->h * surf->w * 4); i += 4) {
            (pixar[0+i] > 1.0) ? pix[2+i] = 255 : (pixar[0+i] < 0.0) ? pix[2+i] = 0 : pix[2+i] = Uint8(pixar[0+i] * 255.0);
            (pixar[1+i] > 1.0) ? pix[1+i] = 255 : (pixar[1+i] < 0.0) ? pix[1+i] = 0 : pix[1+i] = Uint8(pixar[1+i] * 255.0);
            (pixar[2+i] > 1.0) ? pix[0+i] = 255 : (pixar[2+i] < 0.0) ? pix[0+i] = 0 : pix[0+i] = Uint8(pixar[2+i] * 255.0);
            (pixar[3+i] > 1.0) ? pix[3+i] = 255 : (pixar[3+i] < 0.0) ? pix[3+i] = 0 : pix[3+i] = Uint8(pixar[3+i] * 255.0);
        }
    } else if (is_surf_rgba(surf)) {
        for (int i = 0; i < (surf->h * surf->w * 4); i += 4) {
            (pixar[0+i] > 1.0) ? pix[0+i] = 255 : (pixar[0+i] < 0.0) ? pix[0+i] = 0 : pix[0+i] = Uint8(pixar[0+i] * 255.0);
            (pixar[1+i] > 1.0) ? pix[1+i] = 255 : (pixar[1+i] < 0.0) ? pix[1+i] = 0 : pix[1+i] = Uint8(pixar[1+i] * 255.0);
            (pixar[2+i] > 1.0) ? pix[2+i] = 255 : (pixar[2+i] < 0.0) ? pix[2+i] = 0 : pix[2+i] = Uint8(pixar[2+i] * 255.0);
            (pixar[3+i] > 1.0) ? pix[3+i] = 255 : (pixar[3+i] < 0.0) ? pix[3+i] = 0 : pix[3+i] = Uint8(pixar[3+i] * 255.0);
        }
    }
    SDL_UnlockSurface(surf);
}

void surf2pixar(SDL_Surface* surf, double* pixar) {
    SDL_LockSurface(surf);
    int i = 0;
    if (is_surf_abgr(surf)) {
        for (i = 0; i < (surf->h * surf->w * 4); i += 4) {
            pixar[0+i] = ( (double) ((Uint8*)surf->pixels)[3+i] ) / 255.0;
            pixar[1+i] = ( (double) ((Uint8*)surf->pixels)[2+i] ) / 255.0;
            pixar[2+i] = ( (double) ((Uint8*)surf->pixels)[1+i] ) / 255.0;
            pixar[3+i] = ( (double) ((Uint8*)surf->pixels)[0+i] ) / 255.0;
        }
    } else if (is_surf_argb(surf)) {
        for (i = 0; i < (surf->h * surf->w * 4); i += 4) {
            pixar[0+i] = ( (double) ((Uint8*)surf->pixels)[1+i] ) / 255.0;
            pixar[1+i] = ( (double) ((Uint8*)surf->pixels)[2+i] ) / 255.0;
            pixar[2+i] = ( (double) ((Uint8*)surf->pixels)[3+i] ) / 255.0;
            pixar[3+i] = ( (double) ((Uint8*)surf->pixels)[0+i] ) / 255.0;
        }
    } else if (is_surf_bgra(surf)) {
        for (i = 0; i < (surf->h * surf->w * 4); i += 4) {
            pixar[0+i] = ( (double) ((Uint8*)surf->pixels)[2+i] ) / 255.0;
            pixar[1+i] = ( (double) ((Uint8*)surf->pixels)[1+i] ) / 255.0;
            pixar[2+i] = ( (double) ((Uint8*)surf->pixels)[0+i] ) / 255.0;
            pixar[3+i] = ( (double) ((Uint8*)surf->pixels)[3+i] ) / 255.0;
        }
    } else if (is_surf_rgba(surf)) {
        for (i = 0; i < (surf->h * surf->w * 4); i += 4) {
            pixar[0+i] = ( (double) ((Uint8*)surf->pixels)[0+i] ) / 255.0;
            pixar[1+i] = ( (double) ((Uint8*)surf->pixels)[1+i] ) / 255.0;
            pixar[2+i] = ( (double) ((Uint8*)surf->pixels)[2+i] ) / 255.0;
            pixar[3+i] = ( (double) ((Uint8*)surf->pixels)[3+i] ) / 255.0;
        }
    }
    SDL_UnlockSurface(surf);
}

pixel_order get_surf_order(SDL_Surface* surf) {
    if (surf->format->Bmask > surf->format->Gmask &&
        surf->format->Gmask > surf->format->Rmask &&
        surf->format->Rmask > surf->format->Amask) {
        fprintf(stdout, "BGRA\n");
        return pixel_order::BGRA;
    } else if (surf->format->Rmask > surf->format->Gmask &&
        surf->format->Gmask > surf->format->Bmask &&
        surf->format->Bmask > surf->format->Amask) {
        fprintf(stdout, "RGBA\n");
        return pixel_order::RGBA;
    } else if (surf->format->Amask > surf->format->Rmask &&
        surf->format->Rmask > surf->format->Gmask &&
        surf->format->Gmask > surf->format->Bmask) {
        fprintf(stdout, "ARGB\n");
        return pixel_order::ARGB;
    } else if (surf->format->Amask > surf->format->Bmask &&
        surf->format->Bmask > surf->format->Gmask &&
        surf->format->Gmask > surf->format->Rmask) {
        fprintf(stdout, "ABGR\n");
        return pixel_order::ABGR;
    }
    return pixel_order::BOGUS;
}

bool is_surf_bgra(SDL_Surface* surf) {
    return (surf->format->Bmask > surf->format->Gmask &&
            surf->format->Gmask > surf->format->Rmask &&
            surf->format->Rmask > surf->format->Amask);
}
bool is_surf_rgba(SDL_Surface* surf) {
    return (surf->format->Rmask > surf->format->Gmask &&
            surf->format->Gmask > surf->format->Bmask &&
            surf->format->Bmask > surf->format->Amask);
}
bool is_surf_argb(SDL_Surface* surf) {
    return (surf->format->Amask > surf->format->Rmask &&
            surf->format->Rmask > surf->format->Gmask &&
            surf->format->Gmask > surf->format->Bmask);
}
bool is_surf_abgr(SDL_Surface* surf) {
    return (surf->format->Amask > surf->format->Bmask &&
            surf->format->Bmask > surf->format->Gmask &&
            surf->format->Gmask > surf->format->Rmask);
}

void surf_diff(SDL_Surface* a, SDL_Surface* b, SDL_Surface* diff) {
    if ((a->w * a->h * a->format->BitsPerPixel != b->w * b->h * b->format->BitsPerPixel) ||
        (a->w * a->h * a->format->BitsPerPixel != diff->w * diff->h * diff->format->BitsPerPixel)) {
        throw std::invalid_argument("Must be same size.");
    }
    SDL_LockSurface(a); SDL_LockSurface(b); SDL_LockSurface(diff);
#pragma omp parallel for
    for (int i = 0; i < (a->h * a->w * 4); i++) {
        ((Uint8*)diff->pixels)[i] = abs(((Uint8*)a->pixels)[i] - ((Uint8*)b->pixels)[i]);
    }
    SDL_UnlockSurface(a); SDL_UnlockSurface(b); SDL_UnlockSurface(diff);
}

void surf_remap(SDL_Surface* src, SDL_Surface* dst) {
    pixel_order src_order = get_surf_order(src);
    pixel_order dst_order = get_surf_order(dst);
    SDL_LockSurface(src); SDL_LockSurface(dst);
    if (src_order == dst_order) {
        memcpy(dst->pixels, src->pixels, (src->w * src->h * 4));
    }
#pragma GCC diagnostic push                 // We know that we do not hit every enum value!
#pragma GCC diagnostic ignored "-Wswitch"
    switch (src_order) {
        case pixel_order::ABGR:
            switch (dst_order) {
                case pixel_order::ARGB:
                    for (int i = 0; i < (src->w * src->h * 4); i += 4) {
                        ((Uint8*)dst->pixels)[i+0] = ((Uint8*)src->pixels)[i+0];
                        ((Uint8*)dst->pixels)[i+1] = ((Uint8*)src->pixels)[i+3];
                        ((Uint8*)dst->pixels)[i+2] = ((Uint8*)src->pixels)[i+2];
                        ((Uint8*)dst->pixels)[i+3] = ((Uint8*)src->pixels)[i+1];
                    }
                    break;
                case pixel_order::RGBA:
                    for (int i = 0; i < (src->w * src->h * 4); i += 4) {
                        ((Uint8*)dst->pixels)[i+0] = ((Uint8*)src->pixels)[i+3];
                        ((Uint8*)dst->pixels)[i+1] = ((Uint8*)src->pixels)[i+2];
                        ((Uint8*)dst->pixels)[i+2] = ((Uint8*)src->pixels)[i+1];
                        ((Uint8*)dst->pixels)[i+3] = ((Uint8*)src->pixels)[i+0];
                    }
                    break;
                case pixel_order::BGRA:
                        for (int i = 0; i < (src->w * src->h * 4); i += 4) {
                        ((Uint8*)dst->pixels)[i+0] = ((Uint8*)src->pixels)[i+1];
                        ((Uint8*)dst->pixels)[i+1] = ((Uint8*)src->pixels)[i+2];
                        ((Uint8*)dst->pixels)[i+2] = ((Uint8*)src->pixels)[i+3];
                        ((Uint8*)dst->pixels)[i+3] = ((Uint8*)src->pixels)[i+0];
                    }
                    break;
            }
            break;
        case pixel_order::ARGB:
            switch (dst_order) {
                case pixel_order::ABGR:
                    for (int i = 0; i < (src->w * src->h * 4); i += 4) {
                        ((Uint8*)dst->pixels)[i+0] = ((Uint8*)src->pixels)[i+0];
                        ((Uint8*)dst->pixels)[i+1] = ((Uint8*)src->pixels)[i+3];
                        ((Uint8*)dst->pixels)[i+2] = ((Uint8*)src->pixels)[i+2];
                        ((Uint8*)dst->pixels)[i+3] = ((Uint8*)src->pixels)[i+1];
                    }
                    break;
                case pixel_order::RGBA:
                    for (int i = 0; i < (src->w * src->h * 4); i += 4) {
                        ((Uint8*)dst->pixels)[i+0] = ((Uint8*)src->pixels)[i+3];
                        ((Uint8*)dst->pixels)[i+1] = ((Uint8*)src->pixels)[i+0];
                        ((Uint8*)dst->pixels)[i+2] = ((Uint8*)src->pixels)[i+1];
                        ((Uint8*)dst->pixels)[i+3] = ((Uint8*)src->pixels)[i+2];
                    }
                    break;
                case pixel_order::BGRA:
                    for (int i = 0; i < (src->w * src->h * 4); i += 4) {
                        ((Uint8*)dst->pixels)[i+0] = ((Uint8*)src->pixels)[i+3];
                        ((Uint8*)dst->pixels)[i+1] = ((Uint8*)src->pixels)[i+2];
                        ((Uint8*)dst->pixels)[i+2] = ((Uint8*)src->pixels)[i+1];
                        ((Uint8*)dst->pixels)[i+3] = ((Uint8*)src->pixels)[i+0];
                    }
                    break;
            }
            break;
        case pixel_order::BGRA:
            switch (dst_order) {
                case pixel_order::ABGR:
                    for (int i = 0; i < (src->w * src->h * 4); i += 4) {
                        ((Uint8*)dst->pixels)[i+0] = ((Uint8*)src->pixels)[i+3];
                        ((Uint8*)dst->pixels)[i+1] = ((Uint8*)src->pixels)[i+0];
                        ((Uint8*)dst->pixels)[i+2] = ((Uint8*)src->pixels)[i+1];
                        ((Uint8*)dst->pixels)[i+3] = ((Uint8*)src->pixels)[i+2];
                    }
                    break;
                case pixel_order::ARGB:
                    for (int i = 0; i < (src->w * src->h * 4); i += 4) {
                        ((Uint8*)dst->pixels)[i+0] = ((Uint8*)src->pixels)[i+3];
                        ((Uint8*)dst->pixels)[i+1] = ((Uint8*)src->pixels)[i+2];
                        ((Uint8*)dst->pixels)[i+2] = ((Uint8*)src->pixels)[i+1];
                        ((Uint8*)dst->pixels)[i+3] = ((Uint8*)src->pixels)[i+0];
                    }
                    break;
                case pixel_order::RGBA:
                    for (int i = 0; i < (src->w * src->h * 4); i += 4) {
                        ((Uint8*)dst->pixels)[i+0] = ((Uint8*)src->pixels)[i+2];
                        ((Uint8*)dst->pixels)[i+1] = ((Uint8*)src->pixels)[i+1];
                        ((Uint8*)dst->pixels)[i+2] = ((Uint8*)src->pixels)[i+0];
                        ((Uint8*)dst->pixels)[i+3] = ((Uint8*)src->pixels)[i+3];
                    }
                    break;
            }
            break;
        case pixel_order::RGBA:
            switch (dst_order) {
                case pixel_order::ARGB:
                    for (int i = 0; i < (src->w * src->h * 4); i += 4) {
                        ((Uint8*)dst->pixels)[i+0] = ((Uint8*)src->pixels)[i+3];
                        ((Uint8*)dst->pixels)[i+1] = ((Uint8*)src->pixels)[i+0];
                        ((Uint8*)dst->pixels)[i+2] = ((Uint8*)src->pixels)[i+1];
                        ((Uint8*)dst->pixels)[i+3] = ((Uint8*)src->pixels)[i+2];
                    }
                    break;
                case pixel_order::ABGR:
                    for (int i = 0; i < (src->w * src->h * 4); i += 4) {
                        ((Uint8*)dst->pixels)[i+0] = ((Uint8*)src->pixels)[i+3];
                        ((Uint8*)dst->pixels)[i+1] = ((Uint8*)src->pixels)[i+2];
                        ((Uint8*)dst->pixels)[i+2] = ((Uint8*)src->pixels)[i+1];
                        ((Uint8*)dst->pixels)[i+3] = ((Uint8*)src->pixels)[i+0];
                    }
                    break;
                case pixel_order::BGRA:
                    for (int i = 0; i < (src->w * src->h * 4); i += 4) {
                        ((Uint8*)dst->pixels)[i+0] = ((Uint8*)src->pixels)[i+2];
                        ((Uint8*)dst->pixels)[i+1] = ((Uint8*)src->pixels)[i+1];
                        ((Uint8*)dst->pixels)[i+2] = ((Uint8*)src->pixels)[i+0];
                        ((Uint8*)dst->pixels)[i+3] = ((Uint8*)src->pixels)[i+3];
                    }
                    break;
            }
            break;
    }
#pragma GCC diagnostic pop
    SDL_UnlockSurface(src); SDL_UnlockSurface(dst);
}

void surf_change_hue(SDL_Surface* surf, double hue_adj_deg) {
    assert(surf != nullptr && surf->h > 0 && surf->w > 0);
    while (hue_adj_deg > 180.0) {
        hue_adj_deg -= 360.0;
    }
    while (hue_adj_deg < -180.0) {
        hue_adj_deg += 360.0;
    }
    double hue_adj_rad = hue_adj_deg * M_PI / 180.0;

    const Uint32 numsubpix = (surf->h * surf->w * 4);
    double* surfpix = static_cast<double*> (::operator new (sizeof(double[numsubpix])));
    surf2pixar(surf, surfpix);
    for (int i = 0; i < (surf->h * surf->w * 4); i += 4) {
        double* curpix = surfpix + i;
        rgba2laba(curpix);
        laba_change_hue(curpix, hue_adj_rad);
        laba2rgba(curpix);
    }
    pixar2surf(surfpix, surf);
}

void surf_change_nothing(SDL_Surface* surf, double bogus __attribute__((unused))) {
    assert(surf != nullptr && surf->h > 0 && surf->w > 0);
    const Uint32 numsubpix = (surf->h * surf->w * 4);
    double* surfpix = static_cast<double*> (::operator new (sizeof(double[numsubpix])));
    surf2pixar(surf, surfpix);
    for (int i = 0; i < (surf->h * surf->w * 4); i += 4) {
        rgba2xyza(&(surfpix[i]));
        xyza2laba(&(surfpix[i]));
        laba2xyza(&(surfpix[i]));
        xyza2rgba(&(surfpix[i]));
    }
    pixar2surf(surfpix, surf);
}

/* @defgroup CLR_func Color Functions ********************************************************/

void laba_change_hue(double* laba, double hue_adj_rad) {
    double hue = std::atan(laba[2] / laba[1]) + hue_adj_rad;
    while (hue > M_PI) {
        hue -= (2.0 * M_PI);
    }
    while (hue < -1.0 * M_PI) {
        hue += (2.0 * M_PI);
    }
    double chroma = std::sqrt(std::pow(laba[1], 2.0) + std::pow(laba[2], 2.0));
    laba[2] = (chroma * std::sin(hue));
    laba[1] = (chroma * std::cos(hue));
}

void laba_change_sat(double* laba, double sat_adj_pct) {
    /// @cite http://math.stackexchange.com/questions/586424/adjust-saturation-in-cie-lab-space
    double sat = std::sqrt(std::pow(laba[1], 2.0) + std::pow(laba[2], 2.0)) / laba[0];
    sat += sat_adj_pct / 100.0;
    if (sat < 0.0) { sat = 0.0; } else if (sat > 1.0) { sat = 1.0; }
    double t = sat * laba[0] / std::sqrt((std::pow(laba[1], 2.0) + std::pow(laba[2], 2.0)) *
                                         (1 - std::pow(sat, 2.0)));
    laba[1] *= t; laba[2] *= t;
}

void laba2rgba(double* pixar) {
    laba2xyza(pixar);
    xyza2rgba(pixar);
}

void rgba2laba(double* pixar) {
    rgba2xyza(pixar);
    xyza2laba(pixar);
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

void rgba2xyza(double* pixar) {
    double x, y, z;
    x = RGB2XYZ_MAT[0][0] * pixar[0] + RGB2XYZ_MAT[0][1] * pixar[1] + RGB2XYZ_MAT[0][2] * pixar[2];
    y = RGB2XYZ_MAT[1][0] * pixar[0] + RGB2XYZ_MAT[1][1] * pixar[1] + RGB2XYZ_MAT[1][2] * pixar[2];
    z = RGB2XYZ_MAT[2][0] * pixar[0] + RGB2XYZ_MAT[2][1] * pixar[1] + RGB2XYZ_MAT[2][2] * pixar[2];
    pixar[0] = x; pixar[1] = y; pixar[2] = z; // pixar[3] = unchanged alpha
}

void xyza2rgba(double* pixar) {
    double r, g, b;
    r = XYZ2RGB_MAT[0][0] * pixar[0] + XYZ2RGB_MAT[0][1] * pixar[1] + XYZ2RGB_MAT[0][2] * pixar[2];
    g = XYZ2RGB_MAT[1][0] * pixar[0] + XYZ2RGB_MAT[1][1] * pixar[1] + XYZ2RGB_MAT[1][2] * pixar[2];
    b = XYZ2RGB_MAT[2][0] * pixar[0] + XYZ2RGB_MAT[2][1] * pixar[1] + XYZ2RGB_MAT[2][2] * pixar[2];
    pixar[0] = r; pixar[1] = g; pixar[2] = b; //pixar[3] = unchanged alpha
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
    SDL_Surface* ss = SDL_CreateRGBSurfaceFrom(ssp, ssw, ssh,
                                               RGBA_consts::bpp, 4*ssw, RGBA_consts::rmask,
                                               RGBA_consts::gmask, RGBA_consts::bmask,
                                               RGBA_consts::amask);
    return std::tuple<SDL_Surface, SDL_Rect, SDL_Rect>(*ss, sr, dr);
}

