/**
 * @file 		event-handlers.cpp is part of Project sdl2_tests
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

#include "event-handlers.hpp"

void handler(const SDL_Event* evt) {
    switch (evt->type) {
        // Application events  Application events
        case SDL_QUIT:
            // Send Quit to daemon
            client::do_quit();
            break;
            // Android and iOS events
        case SDL_APP_TERMINATING:
            fprintf(stderr, "Received an unhandled event.\n");
            break;
        case SDL_APP_LOWMEMORY:
            fprintf(stderr, "Received an unhandled event.\n");
            break;
        case SDL_APP_WILLENTERBACKGROUND:
            fprintf(stderr, "Received an unhandled event.\n");
            break;
        case SDL_APP_DIDENTERBACKGROUND:
            fprintf(stderr, "Received an unhandled event.\n");
            break;
        case SDL_APP_WILLENTERFOREGROUND:
            fprintf(stderr, "Received an unhandled event.\n");
            break;
        case SDL_APP_DIDENTERFOREGROUND:
            fprintf(stderr, "Received an unhandled event.\n");
            break;
            // Window events   Window events
        case SDL_WINDOWEVENT:
            handle_window_event(evt);
            break;
        case SDL_SYSWMEVENT:
            fprintf(stderr, "Received an unhandled SDL_SYSWMEVENT event.\n");
            break;
            // Keyboard events Keyboard events
        case SDL_KEYDOWN:
            fprintf(stderr, "Received an unhandled SDL_KEYDOWN event.\n");
            break;
        case SDL_KEYUP:
            fprintf(stderr, "Received an unhandled SDL_KEYUP event.\n");
            break;
        case SDL_TEXTEDITING:
            fprintf(stderr, "Received an unhandled SDL_TEXTEDITING event.\n");
            break;
        case SDL_TEXTINPUT:
            fprintf(stderr, "Received an unhandled SDL_TEXTINPUT event.\n");
            break;
            // Mouse events    Mouse events
        case SDL_MOUSEMOTION:
            fprintf(stderr, "Received an unhandled SDL_MOUSEMOTION event.\n");
            break;
        case SDL_MOUSEBUTTONDOWN:
            fprintf(stderr, "Received an unhandled SDL_MOUSEBUTTONDOWN event.\n");
            break;
        case SDL_MOUSEBUTTONUP:
            fprintf(stderr, "Received an unhandled SDL_MOUSEBUTTONUP event.\n");
            break;
        case SDL_MOUSEWHEEL:
            fprintf(stderr, "Received an unhandled SDL_MOUSEWHEEL event.\n");
            break;
            // Joystick events Joystick events
        case SDL_JOYAXISMOTION:
            fprintf(stderr, "Received an unhandled event.\n");
            break;
        case SDL_JOYBALLMOTION:
            fprintf(stderr, "Received an unhandled event.\n");
            break;
        case SDL_JOYHATMOTION:
            fprintf(stderr, "Received an unhandled event.\n");
            break;
        case SDL_JOYBUTTONDOWN:
            fprintf(stderr, "Received an unhandled event.\n");
            break;
        case SDL_JOYBUTTONUP:
            fprintf(stderr, "Received an unhandled event.\n");
            break;
        case SDL_JOYDEVICEADDED:
            fprintf(stderr, "Received an unhandled event.\n");
            break;
        case SDL_JOYDEVICEREMOVED:
            fprintf(stderr, "Received an unhandled event.\n");
            break;
            // Controller events   Controller events
        case SDL_CONTROLLERAXISMOTION:
            fprintf(stderr, "Received an unhandled event.\n");
            break;
        case SDL_CONTROLLERBUTTONDOWN:
            fprintf(stderr, "Received an unhandled event.\n");
            break;
        case SDL_CONTROLLERBUTTONUP:
            fprintf(stderr, "Received an unhandled event.\n");
            break;
        case SDL_CONTROLLERDEVICEADDED:
            fprintf(stderr, "Received an unhandled event.\n");
            break;
        case SDL_CONTROLLERDEVICEREMOVED:
            fprintf(stderr, "Received an unhandled event.\n");
            break;
        case SDL_CONTROLLERDEVICEREMAPPED:
            fprintf(stderr, "Received an unhandled event.\n");
            break;
            // Touch events    Touch events
        case SDL_FINGERDOWN:
            fprintf(stderr, "Received an unhandled event.\n");
            break;
        case SDL_FINGERUP:
            fprintf(stderr, "Received an unhandled event.\n");
            break;
        case SDL_FINGERMOTION:
            fprintf(stderr, "Received an unhandled event.\n");
            break;
            // Gesture events  Gesture events
        case SDL_DOLLARGESTURE:
            fprintf(stderr, "Received an unhandled event.\n");
            break;
        case SDL_DOLLARRECORD:
            fprintf(stderr, "Received an unhandled event.\n");
            break;
        case SDL_MULTIGESTURE:
            fprintf(stderr, "Received an unhandled event.\n");
            break;
            // Clipboard events    Clipboard events
        case SDL_CLIPBOARDUPDATE:
            fprintf(stderr, "Received an unhandled SDL_CLIPBOARDUPDATE event.\n");
            break;
            // Drag and drop events    Drag and drop events
        case SDL_DROPFILE:
            fprintf(stderr, "Received an unhandled SDL_DROPFILE event.\n");
            break;
            // These are for your use, and should be allocated with SDL_RegisterEvents()   These are for your use, and should be allocated with SDL_RegisterEvents()
        case SDL_USEREVENT:
            fprintf(stderr, "Received an unhandled event.\n");
            break;
        case SDL_LASTEVENT:
            fprintf(stderr, "Received an unhandled event.\n");
            break;
    }
}

void handle_window_event(const SDL_Event* event) {
    if (event->type == SDL_WINDOWEVENT) {
        switch (event->window.event) {
            case SDL_WINDOWEVENT_SHOWN:
                fprintf(stderr, "Window %d shown", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_HIDDEN:
                fprintf(stderr, "Window %d hidden", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_EXPOSED:
                fprintf(stderr, "Window %d exposed", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_MOVED:
                fprintf(stderr, "Window %d moved to %d,%d", event->window.windowID,
                        event->window.data1, event->window.data2);
                break;
            case SDL_WINDOWEVENT_RESIZED:
                fprintf(stderr, "Window %d resized to %dx%d", event->window.windowID,
                        event->window.data1, event->window.data2);
                break;
            case SDL_WINDOWEVENT_MINIMIZED:
                fprintf(stderr, "Window %d minimized", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_MAXIMIZED:
                fprintf(stderr, "Window %d maximized", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_RESTORED:
                fprintf(stderr, "Window %d restored", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_ENTER:
                fprintf(stderr, "Mouse entered window %d", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_LEAVE:
                fprintf(stderr, "Mouse left window %d", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                fprintf(stderr, "Window %d gained keyboard focus", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_FOCUS_LOST:
                fprintf(stderr, "Window %d lost keyboard focus", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_CLOSE:
                fprintf(stderr, "Window %d closed", event->window.windowID);
                break;
            default:
                fprintf(stderr, "Window %d got unknown event %d", event->window.windowID,
                        event->window.event);
                break;
        }
    }
}

