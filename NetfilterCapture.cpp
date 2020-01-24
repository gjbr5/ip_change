#include "NetfilterCapture.h"
#ifdef __linux
#include <arpa/inet.h>
#include <iostream>
#include <linux/netfilter.h>
#include <string>

NetfilterCapture::NetfilterCapture()
{
    h = nfq_open();
    if (!h)
        throw std::string("error: during nfq_open()");
    if (nfq_unbind_pf(h, AF_INET) < 0)
        throw std::string("error during nfq_unbind_pf()");
    if (nfq_bind_pf(h, AF_INET) < 0)
        throw std::string("error during nfq_bind_pf()");
    if (!(qh = nfq_create_queue(h, 0, nfcallback, this)))
        throw std::string("error during nfq_create_queue()");
    if (nfq_set_mode(qh, NFQNL_COPY_PACKET, 0xffff) < 0)
        throw std::string("can't set packet_copy mode\n");
    fd = nfq_fd(h);

    system(add_iptables);
}

void NetfilterCapture::next()
{
    ssize_t rv = recv(fd, packetBuf, PACKETBUFSIZE, 0);
    if (rv >= 0) {
        nfq_handle_packet(h, reinterpret_cast<char *>(packetBuf), static_cast<int>(rv));
    }
}

int NetfilterCapture::nfcallback(struct nfq_q_handle *qh, struct nfgenmsg *, struct nfq_data *nfa, void *data)
{
    uint32_t id = ntohl(nfq_get_msg_packet_hdr(nfa)->packet_id);
    NetfilterCapture *capture = reinterpret_cast<NetfilterCapture *>(data);
    uint8_t *payload;
    int length = nfq_get_payload(nfa, &payload);
    capture->notify(payload, static_cast<size_t>(length));
    return nfq_set_verdict(qh, id, NF_ACCEPT, static_cast<uint32_t>(length), payload);
}

NetfilterCapture::~NetfilterCapture()
{
    system(del_iptables);
    nfq_destroy_queue(qh);
    nfq_close(h);
}
#endif
