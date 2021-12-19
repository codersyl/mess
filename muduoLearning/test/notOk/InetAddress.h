#ifndef _INETADDRESS_H_
#define _INETADDRESS_H_

#include "muduo/base/StringPiece.h"
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>　// uint16_t htons(uint16_t hostshort);
                        // uint32_t htonl(uint32_t hostlong);　

// 封装sockaddr_in
// 默认使用 IPv4
class InetAddress {
public:
    explicit InetAddress(uint16_t port = 0) {
        bzero(&addr_, sockaddr_in_len);
        addr_.sin_family = AF_INET;
        addr_.sin_port = htons(port);
        addr_.sin_addr.s_addr = INADDR_ANY; // 也可以
    }

private:
    struct sockaddr_in addr_; 
    static sockaddr_in_len = sizeof(sockaddr_in);
};
#endif  // MUDUO_NET_INETADDRESS_H
