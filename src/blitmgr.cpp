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
#include "blitmgr.hpp"

blitmgr::blitmgr() :
    zmqcntx_(1),
    zmqsock_(zmqcntx_, ZMQ_PUSH)
{
    try {
        zmqsock_.bind(CLNT_ADDR);
        fprintf(stdout, "blit bound to %s\n", CLNT_ADDR);
    } catch (zmq::error_t &e) {
        fprintf(stderr, "ZMQ Error trying to bind to %s.\n\t%d : %s",
                CLNT_ADDR, e.num(), e.what());
        zmqsock_.close();
        zmqcntx_.close();
        throw;
    }
    try {
        zmqsock_.connect(SRVR_ADDR);
        fprintf(stdout, "blit NOW connected to %s\n", SRVR_ADDR);
    } catch (zmq::error_t &e) {
        fprintf(stderr, "ZMQ Error trying to connect to %s.\n\t%d : %s",
                SRVR_ADDR, e.num(), e.what());
        zmqsock_.close();
        zmqcntx_.close();
        throw;
    }
}

blitmgr::~blitmgr() {
    if (zmqsock_.connected()) {
        zmqsock_.disconnect(SRVR_ADDR);
    }
    zmqsock_.close();
    zmqcntx_.close();
} // TODO Auto-generated destructor stub

void blitmgr::blit(SDL_Surface* src_surf, const SDL_Rect* src_rect, SDL_Rect* dst_rect) {
    // pack blit params into vector
    std::vector<Uint32> bp = blitparams2vec(src_surf, src_rect, dst_rect);
    // serialize struct with messagepack
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, bp);
    // create zmq message with msgpacked data
//    zmq::message_t msg(sbuf.size());
//    memcpy(msg.data(), sbuf.data(), sbuf.size());
    // send message
    try {
        size_t bytes_sent = zmqsock_.send(sbuf.data(), sbuf.size(), 0);
        //fprintf(stdout, "blit sent   %lu bytes\n", bytes_sent);
    } catch (zmq::error_t &e) {
        fprintf(stderr, "Error[blit]  %d, %s\n", e.num(), e.what());
    }
}
