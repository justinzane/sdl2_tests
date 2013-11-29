/**
 * @file 		blitmgr.cpp is part of Project winmgr
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
#include "client.hpp"

void handler(const SDL_Event* evt) {
    switch (evt->type) {
        // Application events -----------------------------------------------------------------
        case SDL_QUIT:      // Send Quit to daemon
            do_quit(); break;
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
        case SDL_TEXTINPUT:
            handle_text_input(evt); break;
        // Mouse events -----------------------------------------------------------------------
        case SDL_MOUSEMOTION:
            handle_mouse_motion(evt); break;
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
            case SDL_WINDOWEVENT_RESIZED:
                handle_window_resized(event); break;
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

void porter_duff_over(Uint32* top, Uint32* bot, Uint32* cmp) {
    if (top == nullptr || bot == nullptr  || cmp == nullptr) {
        throw std::invalid_argument("Cannot overlay with null pixels.\n");
    }
    float topR = ((Uint8*)top)[0] / 255.0f;
    float topG = ((Uint8*)top)[1] / 255.0f;
    float topB = ((Uint8*)top)[2] / 255.0f;
    float topA = ((Uint8*)top)[3] / 255.0f;
    float botR = ((Uint8*)bot)[0] / 255.0f;
    float botG = ((Uint8*)bot)[1] / 255.0f;
    float botB = ((Uint8*)bot)[2] / 255.0f;
    float botA = ((Uint8*)bot)[3] / 255.0f;
    float cmpR = topR * topA + (1.0f - topA) * botR * botA;
    float cmpG = topG * topA + (1.0f - topA) * botG * botA;
    float cmpB = topB * topA + (1.0f - topA) * botB * botA;
    float cmpA = topA        + (1.0f - topA) * botA;
    if (cmpR > 1.0f) { cmpR = 1.0f; }
    if (cmpG > 1.0f) { cmpG = 1.0f; }
    if (cmpB > 1.0f) { cmpB = 1.0f; }
    if (cmpA > 1.0f) { cmpA = 1.0f; }
    if (cmpR < 0.0f) { cmpR = 0.0f; }
    if (cmpG < 0.0f) { cmpG = 0.0f; }
    if (cmpA < 0.0f) { cmpA = 0.0f; }
    ((Uint8*)cmp)[0] = (Uint8)(cmpR * 255.0f);
    ((Uint8*)cmp)[1] = (Uint8)(cmpG * 255.0f);
    ((Uint8*)cmp)[2] = (Uint8)(cmpB * 255.0f);
    ((Uint8*)cmp)[3] = (Uint8)(cmpA * 255.0f);
}

template<typename subpix_t>
void alpha_blend_rgba(const cv::Mat& src1, const cv::Mat& src2, cv::Mat& dst) {
    typedef cv::Vec<subpix_t, 4> pixvec_t;

    const float alpha_scale = (float)std::numeric_limits<subpix_t>::max();
    const float inv_scale = 1.f/alpha_scale;

    CV_Assert( src1.type() == src2.type() &&
               src1.type() == cv::DataType<pixvec_t>::type &&
               src1.size() == src2.size());
    cv::Size size = src1.size();
    dst.create(size, src1.type());

    cv::MatConstIterator_<pixvec_t> it2 = src2.begin<pixvec_t>();
    cv::MatIterator_<pixvec_t> dst_it = dst.begin<pixvec_t>();

    for(cv::MatConstIterator_<pixvec_t> it1 = src1.begin<pixvec_t>();
        it1 != src1.end<pixvec_t>(); ++it1, ++it2, ++dst_it ) {
        pixvec_t pix1 = *it1, pix2 = *it2;
        float alpha = pix1[3]*inv_scale, beta = pix2[3]*inv_scale;
        *dst_it = pixvec_t(cv::saturate_cast<subpix_t>(pix1[0]*alpha + pix2[0]*beta),
                           cv::saturate_cast<subpix_t>(pix1[1]*alpha + pix2[1]*beta),
                           cv::saturate_cast<subpix_t>(pix1[2]*alpha + pix2[2]*beta),
                           cv::saturate_cast<subpix_t>((1 - (1-alpha)*(1-beta))*alpha_scale));
    }
}


void surface_change_hsv(SDL_Surface* src_surf, SDL_Surface* dst_surf,
                        float hue_diff, float sat_diff, float val_diff) {
    if (hue_diff != 0.0f) { surface_change_hue(src_surf, dst_surf, hue_diff); }
    if (sat_diff != 0.0f) { surface_change_sat(src_surf, dst_surf, sat_diff); }
    if (val_diff != 0.0f) { surface_change_val(src_surf, dst_surf, val_diff); }
}

void surface_change_hue(SDL_Surface* src_surf, SDL_Surface* dst_surf, float hue_diff) {
    using namespace cv;

    SDL_LockSurface(src_surf);
    Mat src_mat = Mat(src_surf->h, src_surf->w, CV_8UC4);                // Make mat from surf
    memcpy(src_mat.data, src_surf->pixels, src_surf->h * src_surf->w * sizeof(Uint32));
    SDL_UnlockSurface(src_surf);

    Mat rgbI_mat = Mat(src_mat.rows, src_mat.cols, CV_8UC3);     // split rgba into rgb and a
    Mat aI_mat = Mat(src_mat.rows, src_mat.cols, CV_8UC1);       // since hsv has no a
    Mat to_ar[] {rgbI_mat, aI_mat};
    int from_to[] = { 0,0, 1,1, 2,2, 3,3 };                      // r=0, ... a=3
    mixChannels(&src_mat, 1, to_ar, 2, from_to, 4);

    Mat rgbF_mat = Mat(src_mat.rows, src_mat.cols, CV_32FC3);    // Make ints into floats
    rgbI_mat.convertTo(rgbF_mat, CV_32F);

    typedef Vec<float, 3> flt_vec_t;                             // The type of pixel in hsv
    Mat hsv_mat = Mat(src_mat.rows, src_mat.cols, CV_32FC3);
    cvtColor(rgbF_mat, hsv_mat, CV_RGB2HSV, 3);                  // convert to HSV

    flt_vec_t pix_vec;
    for (MatIterator_<flt_vec_t> mat_it = hsv_mat.begin<flt_vec_t>();
         mat_it != hsv_mat.end<flt_vec_t>();
         mat_it++) {
        pix_vec = *mat_it;
        Matx<float, 3, 1> pix_matx = (Matx<float, 3, 1>)pix_vec;
        pix_matx.val[0] += hue_diff;
        if (pix_matx.val[0] >= 360.0f || pix_matx.val[0] < 0.0f) {
            pix_matx.val[0] = (180.0f / M_PI) * (std::asin(std::sin((pix_matx.val[0] * M_PI / 180.0f))));
        }
    }

    cvtColor(hsv_mat, rgbF_mat, CV_HSV2RGB, 3);              // convert back to RGB

    rgbF_mat.convertTo(rgbI_mat, CV_8U);                     // float back to int
    Mat from_ar[] {rgbI_mat, aI_mat};
    int to_from[] = { 0,0, 1,1, 2,2, 0,3 };                  // r=0, ... a=3
    mixChannels(from_ar, 2, &src_mat, 1, to_from, 4);        // add alpha for RGBA

    SDL_LockSurface(dst_surf);
    memcpy(dst_surf->pixels, (void*)src_mat.data, dst_surf->h * dst_surf->w * sizeof(Uint32));
    SDL_UnlockSurface(dst_surf);
}

void surface_change_sat(SDL_Surface* src_surf, SDL_Surface* dst_surf, float sat_diff) {
    using namespace cv;

    SDL_LockSurface(src_surf);
    SDL_LockSurface(dst_surf);

    Mat src_mat = Mat(src_surf->h, src_surf->w, CV_8UC4,
                      src_surf->pixels, src_surf->w * sizeof(Uint32));            // Make mat from surf
    Mat tmp_src_mat = src_mat.clone();
    Mat src_rgbI = Mat(src_mat.rows, src_mat.cols, CV_8UC3);     // split rgba into rgb and a
    Mat aI_mat = Mat(src_mat.rows, src_mat.cols, CV_8UC1);       // since hsv has no a
    Mat to_ar[] {src_rgbI, aI_mat};
    int from_to[] = { 0,0, 1,1, 2,2, 3,3 };                      // r=0, ... a=3
    mixChannels(&tmp_src_mat, 1, to_ar, 2, from_to, 4);

    Mat rgbF_mat = Mat(src_mat.rows, src_mat.cols, CV_32FC3);    // Make ints into floats
    src_rgbI.convertTo(rgbF_mat, CV_32F);

    typedef Vec<float, 3> flt_vec_t;                             // The type of pixel in hsv
    Mat hsv_mat = Mat(src_mat.rows, src_mat.cols, CV_32FC3);
    cvtColor(rgbF_mat, hsv_mat, CV_RGB2HSV, 3);                  // convert to HSV

    flt_vec_t pix_vec;
    for (MatIterator_<flt_vec_t> mat_it = hsv_mat.begin<flt_vec_t>();
         mat_it != hsv_mat.end<flt_vec_t>();
         mat_it++) {
        pix_vec = *mat_it;
        Matx<float, 3, 1> pix_matx = (Matx<float, 3, 1>)pix_vec;
        CV_Assert(pix_matx.val[1] <= 1.0f && pix_matx.val[1] >= 0.0f);
        pix_matx.val[1] += sat_diff;
        if (pix_matx.val[1] > 1.0f) { pix_matx.val[1] = 1.0f; }
        if (pix_matx.val[1] < 0.0f) { pix_matx.val[1] = 0.0f; }
    }

    cvtColor(hsv_mat, rgbF_mat, CV_HSV2RGB, 3);              // convert back to RGB

    Mat tmp_dst_mat = Mat(dst_surf->h, dst_surf->w, CV_8UC4);
    Mat dst_rgbI = Mat(tmp_dst_mat.rows, tmp_dst_mat.cols, CV_8UC3);
    rgbF_mat.convertTo(dst_rgbI, CV_8U);                     // float back to int
    Mat from_ar[] {dst_rgbI, aI_mat};
    int to_from[] = { 0,0, 1,1, 2,2, 0,3 };                  // r=0, ... a=3
    mixChannels(from_ar, 2, &tmp_dst_mat, 1, to_from, 4);        // add alpha for RGBA
    Mat dst_mat = Mat(dst_surf->h, dst_surf->w, CV_8UC4, dst_surf->pixels, dst_surf->w*sizeof(Uint32));
    tmp_dst_mat.copyTo(dst_mat);
    SDL_UnlockSurface(dst_surf);
    SDL_UnlockSurface(src_surf);
}


void surface_change_val(SDL_Surface* src_surf, SDL_Surface* dst_surf, float val_diff) {
    using namespace cv;
    typedef Vec<float, 4> flt_vec_t;

    SDL_LockSurface(src_surf);
    Mat src_mat = Mat(src_surf->h, src_surf->w, CV_8UC4, src_surf->pixels);
    Mat hsv_mat = Mat(src_surf->h, src_surf->w, CV_32FC4);
    cvtColor(src_mat, hsv_mat, CV_RGB2HSV, 4);      // convert to HSV
    for (MatIterator_<flt_vec_t> mat_it = hsv_mat.begin<flt_vec_t>();
         mat_it != hsv_mat.end<flt_vec_t>();
         mat_it++) {
        (*mat_it)[2] += val_diff;
        if ((*mat_it)[2] > 1.0f) { (*mat_it)[2] = 1.0f; }
        if ((*mat_it)[2] < 0.0f) { (*mat_it)[2] = 0.0f; }
    }
    cvtColor(hsv_mat, src_mat, CV_HSV2RGB, 4);      // convert back to RGBA
    SDL_UnlockSurface(dst_surf);
}

void surface_compose_overlay(SDL_Surface* top, int top_offset_x, int top_offset_y,
                             SDL_Surface* bot, int bot_offset_x, int bot_offset_y,
                             SDL_Surface* dst) {
    // TODO Rewriteme to properly handle transparency.
    if (top == nullptr || bot == nullptr || dst == nullptr) {
        throw std::invalid_argument("Cannot compose with null arguments.");
    }
    if ((top->w + abs(top_offset_x) > dst->w) ||
        (top->h + abs(top_offset_y) > dst->h) ||
        (bot->w + abs(bot_offset_x) > dst->w) ||
        (bot->h + abs(bot_offset_y) > dst->h)) {
        throw std::invalid_argument("Src surfs + offsets must lie within dst surf.");
    }
    SDL_Rect dst_rect = SDL_Rect {0,0,dst->w, dst->h};

    SDL_Surface* new_top;
    new_top =  SDL_CreateRGBSurface(0, dst->w, dst->h, BPP, RMASK, GMASK, BMASK, AMASK);
    SDL_FillRect(new_top, &dst_rect, 0x00000000);
    SDL_LockSurface(top); SDL_LockSurface(new_top);

    for (int y = 0; y < top->h; y++) {
        for (int x = 0; x < top->w; x++) {
            if (top_offset_y <= 0) {
                if (top_offset_x <= 0) {
                    *(((Uint32*)new_top)+ (y * top->w + x)) =
                        *(((Uint32*)top) + (y * top->w + x));
                } else {
                    *(((Uint32*)new_top) + (y * top->w + x + top_offset_x)) =
                        *(((Uint32*)new_top) + (y * top->w + x));
                }
            } else {
                if (top_offset_x <= 0) {
                    *(((Uint32*)new_top) + ((y + top_offset_y) * top->w + x)) =
                        *(((Uint32*)top) + (y * top->w + x));
                } else {
                    *(((Uint32*)new_top) + ((y + top_offset_y) * top->w + (x + top_offset_x))) =
                        *(((Uint32*)new_top) + (y * top->w + x));
                }
            }
        }
    }

    SDL_UnlockSurface(top); SDL_UnlockSurface(new_top);

    SDL_Surface* new_bot;
    new_bot =  SDL_CreateRGBSurface(0, dst->w, dst->h, BPP, RMASK, GMASK, BMASK, AMASK);
    SDL_FillRect(new_bot, &dst_rect, 0x00000000);
    SDL_LockSurface(bot); SDL_LockSurface(new_bot);

    for (int y = 0; y < bot->h; y++) {
        for (int x = 0; x < bot->w; x++) {
            if (bot_offset_y <= 0) {
                if (bot_offset_x <= 0) {
                    ((Uint32*)new_bot)[y * bot->w + x] =
                        ((Uint32*)bot)[y * bot->w + x];
                } else {
                    ((Uint32*)new_bot)[y * bot->w + (x + bot_offset_x)] =
                        ((Uint32*)new_bot)[y * bot->w + x];
                }
            } else {
                if (bot_offset_x <= 0) {
                    ((Uint32*)new_bot)[(y + bot_offset_y) * bot->w + x] =
                        ((Uint32*)bot)[y * bot->w + x];
                } else {
                    ((Uint32*)new_bot)[(y + bot_offset_y) * bot->w + (x + bot_offset_x)] =
                        ((Uint32*)new_bot)[y * bot->w + x];
                }
            }
        }
    }

    SDL_UnlockSurface(bot); SDL_UnlockSurface(new_bot);

    SDL_LockSurface(new_top); SDL_LockSurface(new_bot); SDL_LockSurface(dst);
    Uint32* toppix = (Uint32*)new_top->pixels;
    Uint32* botpix = (Uint32*)new_bot->pixels;
    Uint32* dstpix = (Uint32*)dst->pixels;
    for (int i = 0; i < dst->h * dst->w; i++){
        porter_duff_over(toppix + i, botpix + i, dstpix + i);
    }
    SDL_UnlockSurface(new_top); SDL_UnlockSurface(new_bot); SDL_UnlockSurface(dst);
}

void surface_shadow(SDL_Surface* src, SDL_Surface* dst, int offset_x, int offset_y) {
    SDL_Surface* tmp1 = SDL_CreateRGBSurface(0, src->w, src->h, BPP, RMASK, GMASK, BMASK, AMASK);
    SDL_Surface* tmp2 = SDL_CreateRGBSurface(0, src->w, src->h, BPP, RMASK, GMASK, BMASK, AMASK);
    surface_blur(src, tmp1, 7);
    surface_change_val(tmp1, tmp2, -0.25);
    surface_compose_overlay(src, 0, 0,
                            tmp2, offset_x, offset_y,
                            dst);
}

void surface_blur(SDL_Surface* src, SDL_Surface* dst, Uint8 amount) {
    SDL_LockSurface(src); SDL_LockSurface(dst);

    cv::Mat src_mat = cv::Mat(src->h, src->w, CV_8UC4, src->pixels);
    cv::Mat dst_mat = cv::Mat(dst->h, dst->w, CV_8UC4, dst->pixels);

    cv::Point anchor = cv::Point(-1, -1);
    cv::Size kern_size = cv::Size(amount, amount);
    cv::blur(src_mat, dst_mat, kern_size, anchor, cv::BORDER_REFLECT_101);

    SDL_UnlockSurface(src); SDL_UnlockSurface(dst);
}

void surface_diff(SDL_Surface* asurf, SDL_Surface* bsurf, SDL_Surface* diffsurf) {
    using namespace cv;

    if (asurf->h != bsurf->h || asurf->w != bsurf->w ||
        asurf->h != diffsurf->h || asurf->w != diffsurf->w) {
        throw std::invalid_argument("Args to surface_diff must be the same size.");
    }

    SDL_LockSurface(asurf); SDL_LockSurface(bsurf); SDL_LockSurface(diffsurf);
    Mat amat    = Mat(asurf->h,    asurf->w,    CV_8UC4, asurf->pixels,    CV_AUTOSTEP);
    Mat bmat    = Mat(bsurf->h,    bsurf->w,    CV_8UC4, bsurf->pixels,    CV_AUTOSTEP);
    Mat diffmat = Mat(diffsurf->h, diffsurf->w, CV_8UC4, diffsurf->pixels, CV_AUTOSTEP);
    diffmat = abs(amat-bmat);
    SDL_UnlockSurface(asurf); SDL_UnlockSurface(bsurf); SDL_UnlockSurface(diffsurf);
}

void handle_mouse_motion(const SDL_Event* evt) {
    SDL_MouseMotionEvent* mmevt = (SDL_MouseMotionEvent*)evt;
    SDL_Rect src_rect, dst_rect;
    if (sample_img == nullptr) {
        SDL_Surface* tmp_img = IMG_Load("/home/justin/src/sdl2_tests/docs/images/Purple-dragon-sm.png");
        sample_img = SDL_ConvertSurfaceFormat(tmp_img, SDL_PIXELFORMAT_RGBA8888, 0);
    }
    src_rect.x = 0;                   src_rect.y = 0;
    src_rect.h = sample_img->h;       src_rect.w = sample_img->w;
    dst_rect.x = mmevt->x;            dst_rect.y = mmevt->y;
    dst_rect.h = sample_img->h;       dst_rect.w = sample_img->w;
    if (mmevt->x > mmevt->y) {
        SDL_Surface* changed = SDL_CreateRGBSurface(0, sample_img->w, sample_img->h, BPP,
                                                    RMASK, GMASK, BMASK, AMASK);
        SDL_Surface* diff = SDL_CreateRGBSurface(0, sample_img->w, sample_img->h, BPP,
                                                 RMASK, GMASK, BMASK, AMASK);
        SDL_LockSurface(sample_img); SDL_LockSurface(changed);
        memcpy(changed->pixels, sample_img->pixels, (sample_img->w * sample_img->h * BPP / 8));
        SDL_UnlockSurface(sample_img); SDL_UnlockSurface(changed);
        surf_change_hue(changed, 15.0);
        surf_diff(sample_img, changed, diff);
        blit(diff, &src_rect, &dst_rect);
    } else {
        blit(sample_img, &src_rect, &dst_rect);
    }
}

void handle_text_input(const SDL_Event* evt) {
/*  Uint32  type        SDL_TEXTINPUT
    Uint32  timestamp   timestamp of the event
    Uint32  windowID    The window with keyboard focus, if any
    char    text        The null-terminated input text in UTF-8 encoding */
    fprintf(stdout, ">>>>    TEXT_INPUT: %s", ((SDL_TextInputEvent*)evt)->text);
}

// Image Rendering ----------------------------------------------------------------------------

bool cache_blitparam_vec(std::vector<Uint32>& bp_vec) {
    auto was_inserted = surf_cache.emplace(get_vec_hash(bp_vec), bp_vec);
    return std::get<1>(was_inserted);
}

Uint64 dup_count = 0;

void blit(SDL_Surface* src_surf, const SDL_Rect* src_rect, SDL_Rect* dst_rect) {
    std::vector<Uint32> bp_vec = blitparams2vec(src_surf, src_rect, dst_rect);
//    if (!cache_blitparam_vec(bp_vec)) {
//        if ((dup_count++ % 100) == 0) {
//            fprintf(stderr, ">>>>    dup_count = %lu\n", dup_count);
//        }
//    }
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, bp_vec);
    try {
        size_t bytes_sent __attribute__((unused));
        bytes_sent = zmq_push_sock_.send(sbuf.data(), sbuf.size(), 0);
    } catch (zmq::error_t &e) {
        fprintf(stderr, "SDL Error %d %s\n", e.num(), e.what());
    }
}

// Quitting -----------------------------------------------------------------------------------
void do_quit() {
    std::string quit = "quit";
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, quit);
    bool server_quitting = false;
    while(!server_quitting) {
        zmq_req_sock_.send((void*)sbuf.data(), sbuf.size(), 0);
        zmq::message_t reply_msg;
        zmq_req_sock_.recv(&reply_msg, 0);
        msgpack::unpacked unpacked;
        msgpack::unpack(&unpacked, reinterpret_cast<char*>(reply_msg.data()), reply_msg.size());
        msgpack::object obj = unpacked.get();
        std::string reply;
        obj.convert(&reply);
        if (reply == "quitting") { server_quitting = true; }
    }
    quit_client_loop = true;
}
/*--------------------------------------------------------------------------------------------*/

int main() {
    // Setup ZMQ PUSH for sending bitmaps to server
    zmq_req_sock_.bind(CLNT_REQ_ADDR);
    zmq_req_sock_.connect(SRVR_REP_ADDR);
    // Setup ZMQ PUSH for sending bitmaps to server
    zmq_push_sock_.bind(CLNT_PUSH_ADDR);
    zmq_push_sock_.connect(SRVR_PULL_ADDR);
    // Setup ZMQ SUB for getting events
    zmq_sub_sock_.bind(CLNT_SUB_ADDR);
    zmq_sub_sock_.setsockopt(ZMQ_SUBSCRIBE, nullptr, 0);
    zmq_sub_sock_.connect(SRVR_PUB_ADDR);
    fprintf(stdout, ">>>>    Setup Client Sockets.\n");

    // The main loop -- recv events and send bitmaps
    while (!(should_quit())) {
        // Check for events
        zmq::message_t evt_msg;
        if (zmq_sub_sock_.recv(&evt_msg, ZMQ_NOBLOCK)) {
            msgpack::unpacked unpacked;
            msgpack::unpack(&unpacked, reinterpret_cast<char*>(evt_msg.data()), evt_msg.size());
            msgpack::object obj = unpacked.get();
            std::vector<Uint8> evt_vec;
            obj.convert(&evt_vec);
            SDL_Event evt = vec2event(evt_vec);
            handler(&evt);
        }
        // Send graphics
    }

    fprintf(stdout, ">>>>    Left Main Loop, Quitting.\n");
    // Cleanup after ourselves.
    if (zmq_req_sock_.connected())  { zmq_req_sock_.disconnect(SRVR_REP_ADDR); }
    if (zmq_push_sock_.connected()) { zmq_push_sock_.disconnect(SRVR_PULL_ADDR); }
    if (zmq_sub_sock_.connected())  { zmq_sub_sock_.disconnect(SRVR_PUB_ADDR); }
    zmq_req_sock_.close();
    zmq_push_sock_.close();
    zmq_sub_sock_.close();
    zmqcntx_.close();

    return 0;
}
