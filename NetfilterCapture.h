#pragma once
#include "Capture.h"
#ifdef __linux
#include <libnetfilter_queue/libnetfilter_queue.h>

class NetfilterCapture : public Capture
{
private:
    struct nfq_handle *h;
    struct nfq_q_handle *qh;
    int fd;

    constexpr static char add_iptables[] = "sudo iptables -A PREROUTING -t mangle -j NFQUEUE --queue-num 0\n"
                                           "sudo iptables -A OUTPUT -j NFQUEUE --queue-num 0\n";
    constexpr static char del_iptables[] = "sudo iptables -D PREROUTING -t mangle -j NFQUEUE --queue-num 0\n"
                                           "sudo iptables -D OUTPUT -j NFQUEUE --queue-num 0\n";

private:
    static int nfcallback(struct nfq_q_handle *qh, struct nfgenmsg *nfmsg, struct nfq_data *nfa, void *data);

public:
    NetfilterCapture();
    ~NetfilterCapture();
    void next() final;
};
#endif
