/**
 * @file 		silly.cpp is part of sdl2_tests
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
#include "silly.hpp"

void handler(const SDL_Event* evt) {
    switch (evt->type) {
        // Application events -----------------------------------------------------------------
        case SDL_QUIT: quit(SIGQUIT); break;
        // Android and iOS events IGNORED -----------------------------------------------------
        case SDL_APP_TERMINATING: break;
        case SDL_APP_LOWMEMORY: break;
        case SDL_APP_WILLENTERBACKGROUND: break;
        case SDL_APP_DIDENTERBACKGROUND: break;
        case SDL_APP_WILLENTERFOREGROUND: break;
        case SDL_APP_DIDENTERFOREGROUND: break;
        // Window events ----------------------------------------------------------------------
        case SDL_WINDOWEVENT: handle_window_event(evt); break;
        case SDL_SYSWMEVENT: break;
        // Keyboard events --------------------------------------------------------------------
        case SDL_KEYDOWN: break;
        case SDL_KEYUP: break;
        case SDL_TEXTEDITING: break;
        case SDL_TEXTINPUT: handle_text_input(evt); break;
        // Mouse events -----------------------------------------------------------------------
        case SDL_MOUSEMOTION: handle_mouse_motion(evt); break;
        case SDL_MOUSEBUTTONDOWN: break;
        case SDL_MOUSEBUTTONUP: break;
        case SDL_MOUSEWHEEL: break;
        // Joystick events --------------------------------------------------------------------
        case SDL_JOYAXISMOTION: break;
        case SDL_JOYBALLMOTION: break;
        case SDL_JOYHATMOTION: break;
        case SDL_JOYBUTTONDOWN: break;
        case SDL_JOYBUTTONUP: break;
        case SDL_JOYDEVICEADDED: break;
        case SDL_JOYDEVICEREMOVED: break;
        // Controller events ------------------------------------------------------------------
        case SDL_CONTROLLERAXISMOTION: break;
        case SDL_CONTROLLERBUTTONDOWN: break;
        case SDL_CONTROLLERBUTTONUP: break;
        case SDL_CONTROLLERDEVICEADDED: break;
        case SDL_CONTROLLERDEVICEREMOVED: break;
        case SDL_CONTROLLERDEVICEREMAPPED: break;
        // Touch events -----------------------------------------------------------------------
        case SDL_FINGERDOWN: break;
        case SDL_FINGERUP: break;
        case SDL_FINGERMOTION: break;
        // Gesture events ---------------------------------------------------------------------
        case SDL_DOLLARGESTURE: break;
        case SDL_DOLLARRECORD: break;
        case SDL_MULTIGESTURE: break;
        // Clipboard events -------------------------------------------------------------------
        case SDL_CLIPBOARDUPDATE: break;
        // Drag and drop events ---------------------------------------------------------------
        case SDL_DROPFILE: break;
        // These are for your use, and should be allocated with SDL_RegisterEvents() ----------
        case SDL_USEREVENT: break;
        case SDL_LASTEVENT: break;
    }
}

void handle_window_event(const SDL_Event* event) {
    if (event->type == SDL_WINDOWEVENT) {
        switch (event->window.event) {
            case SDL_WINDOWEVENT_SHOWN: break;
            case SDL_WINDOWEVENT_HIDDEN: break;
            case SDL_WINDOWEVENT_EXPOSED: break;
            case SDL_WINDOWEVENT_MOVED: break;
            case SDL_WINDOWEVENT_RESIZED: handle_window_resized(event); break;
            case SDL_WINDOWEVENT_MINIMIZED: break;
            case SDL_WINDOWEVENT_MAXIMIZED: break;
            case SDL_WINDOWEVENT_RESTORED: break;
            case SDL_WINDOWEVENT_ENTER: break;
            case SDL_WINDOWEVENT_LEAVE: break;
            case SDL_WINDOWEVENT_FOCUS_GAINED: break;
            case SDL_WINDOWEVENT_FOCUS_LOST: break;
            case SDL_WINDOWEVENT_CLOSE: break;
            default:
                fprintf(stdout, "Window %d got unknown event %d\n", event->window.windowID,
                        event->window.event);
                break;
        }
    }
}

void handle_window_resized(const SDL_Event* evt) {
    SDL_WindowEvent* win_evt = (SDL_WindowEvent*)evt;
    win_size[0] = win_evt->data1;
    win_size[0] = win_evt->data2;
}

void handle_mouse_motion(const SDL_Event* evt) {
    SDL_MouseMotionEvent* mmevt = (SDL_MouseMotionEvent*)evt;
    SDL_Rect src_rect, dst_rect;
    if (sample_img == nullptr) {
        SDL_Surface* tmp_img = IMG_Load("/home/justin/src/sdl2_tests/docs/images/RGB_grad.tif");
        fprintf(stderr, "MASK: R=%08x G=%08x B=%08x A=%08x\n",
                tmp_img->format->Rmask, tmp_img->format->Gmask, tmp_img->format->Bmask, tmp_img->format->Amask);
        fprintf(stderr, "SHFT: R=% 8d G=% 8d B=% 8d A=% 8d\n",
                tmp_img->format->Rshift, tmp_img->format->Gshift, tmp_img->format->Bshift, tmp_img->format->Ashift);
        fprintf(stderr, "LOSS: R=% 8d G=% 8d B=% 8d A=% 8d\n\n",
                tmp_img->format->Rloss, tmp_img->format->Gloss, tmp_img->format->Bloss, tmp_img->format->Aloss);
        sample_img = SDL_CreateRGBSurface(0, tmp_img->w, tmp_img->h, 32,
                                           RGBA_consts::rmask, RGBA_consts::gmask,
                                           RGBA_consts::bmask, RGBA_consts::amask);
        sample_img = SDL_ConvertSurface(tmp_img, sample_img->format, 0);
        fprintf(stderr, "MASK: R=%08x G=%08x B=%08x A=%08x\n",
                sample_img->format->Rmask, sample_img->format->Gmask, sample_img->format->Bmask, sample_img->format->Amask);
        fprintf(stderr, "SHFT: R=% 8d G=% 8d B=% 8d A=% 8d\n",
                sample_img->format->Rshift, sample_img->format->Gshift, sample_img->format->Bshift, sample_img->format->Ashift);
        fprintf(stderr, "LOSS: R=% 8d G=% 8d B=% 8d A=% 8d\n\n",
                sample_img->format->Rloss, sample_img->format->Gloss, sample_img->format->Bloss, sample_img->format->Aloss);
    }
    src_rect.x = 0;                   src_rect.y = 0;
    src_rect.h = sample_img->h;       src_rect.w = sample_img->w;
    dst_rect.x = mmevt->x;            dst_rect.y = mmevt->y;
    dst_rect.h = sample_img->h;       dst_rect.w = sample_img->w;
    surf_change_hue(sample_img, std::atan2(mmevt->yrel, mmevt->xrel));
    SDL_BlitSurface(sample_img, &src_rect, scrn_, &dst_rect);
    SDL_UpdateTexture(txtr_, nullptr, scrn_->pixels, scrn_->pitch);
    SDL_RenderClear (rend_);
    SDL_RenderCopy(rend_, txtr_, nullptr, nullptr);
    SDL_RenderPresent(rend_);
}

void handle_text_input(const SDL_Event* evt) {
/*  Uint32  type        SDL_TEXTINPUT
    Uint32  timestamp   timestamp of the event
    Uint32  windowID    The window with keyboard focus, if any
    char    text        The null-terminated input text in UTF-8 encoding */
    fprintf(stdout, ">>>>    TEXT_INPUT: %s", ((SDL_TextInputEvent*)evt)->text);
}



int main(int argc __attribute__((unused)), char** argv __attribute__((unused))) {
    // Start SDL2 -----------------------------------------------------------------------------
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Unable to initialize SDL:  %s\n", SDL_GetError()); throw;
    }
    if (SDL_GetNumVideoDisplays() < 1) {
        fprintf(stderr, "Num displays:  %d\n", SDL_GetNumVideoDisplays()); throw;
    }
    if (SDL_GetDesktopDisplayMode(0, &disp_mode_) != 0) {
        fprintf(stderr, "\nUnable to get display into:  %s\n", SDL_GetError()); throw;
    }
    pixfmt_ = disp_mode_.format;
    disp_w_ = disp_mode_.w;
    disp_h_ = disp_mode_.h - 48;
    wind_ = SDL_CreateWindow("Silly!", 0, 0, disp_w_, disp_h_,
                             (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL));
    rend_ = SDL_CreateRenderer(wind_, -1,
                               SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    SDL_SetRenderDrawColor(rend_, 31, 31, 31, 255);
    scrn_ = SDL_CreateRGBSurface(0, disp_w_, disp_h_, RGBA_consts::bpp, RGBA_consts::rmask, RGBA_consts::gmask,
                                 RGBA_consts::bmask, RGBA_consts::amask);
    txtr_ = SDL_CreateTexture(rend_, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
                              disp_w_, disp_h_);

    // Handle kill/term signals ---------------------------------------------------------------
    struct sigaction quit_action;
    quit_action.sa_handler = &quit;
    sigemptyset(&quit_action.sa_mask);
    sigaddset(&quit_action.sa_mask, SIGINT);
    sigaddset(&quit_action.sa_mask, SIGQUIT);
    sigaddset(&quit_action.sa_mask, SIGKILL);
    sigaddset(&quit_action.sa_mask, SIGTERM);
    quit_action.sa_flags = 0;
    sigaction(SIGINT, &quit_action, nullptr);
    sigaction(SIGKILL, &quit_action, nullptr);
    sigaction(SIGQUIT, &quit_action, nullptr);
    sigaction(SIGTERM, &quit_action, nullptr);

    // Main Loop ------------------------------------------------------------------------------
    while (!stop_) {
        SDL_Event evt;
        int poll_result = SDL_PollEvent(&evt);
        if (poll_result == 1) {     // If poll_result == 0, no event, move along
            handler(&evt);
        }
    }

    SDL_Quit();
}
