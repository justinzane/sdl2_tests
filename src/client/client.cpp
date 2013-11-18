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

void blit(SDL_Surface* src_surf,
          const SDL_Rect* src_rect,
          SDL_Rect* dst_rect,
          zmq::socket_t sock) {
    std::vector<Uint32> bp = blitparams2vec(src_surf, src_rect, dst_rect);
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, bp);
    try {
        size_t bytes_sent __attribute__((unused));
        bytes_sent = sock.send(sbuf.data(), sbuf.size(), 0);
    } catch (zmq::error_t &e) {
        fprintf(stderr, "Error[blit]  %d, %s\n", e.num(), e.what());
    }
}

/*--------------------------------------------------------------------------------------------*/

int main() {
    zmq::context_t zmqcntx_;
    // Setup ZMQ PUSH for sending bitmaps to server
    zmq::socket_t zmq_push_sock_(zmqcntx_, ZMQ_PUSH);
    zmq_push_sock_.bind(CLNT_PUSH_ADDR);
    zmq_push_sock_.connect(SRVR_PULL_ADDR);
    // Setup ZMQ SUB for getting events
    zmq::socket_t zmq_sub_sock_(zmqcntx_, ZMQ_SUB);
    zmq_sub_sock_.bind(CLNT_SUB_ADDR);
    zmq_sub_sock_.connect(SRVR_PUB_ADDR);

    // The main loop -- recv events and send bitmaps
    while (!(client::should_quit())) {
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

    // Cleanup after ourselves.
    if (zmq_push_sock_.connected()) {
        zmq_push_sock_.disconnect(SRVR_PULL_ADDR);
    }
    if (zmq_sub_sock_.connected()) {
        zmq_sub_sock_.disconnect(SRVR_PULL_ADDR);
    }
    zmq_push_sock_.close();
    zmq_sub_sock_.close();
    zmqcntx_.close();

    return 0;
}
