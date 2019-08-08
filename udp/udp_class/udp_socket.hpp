#pragma once
#include <cstdio>
#include <cstring>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class UdpSocket {
public:
    UdpSocket() : fd_(-1) {

    }

    // 打开一个 udp 的 socket
    // 返回 true 表示创建成功, false 表示失败
    bool Socket() {
        fd_ = socket(AF_INET, SOCK_DGRAM, 0);
        if (fd_ < 0) {
            perror("socket");
        }
        return true;
    }

    bool Close() {
        if (fd_ != -1) {
            close(fd_);
        }
        return true;
    }

    bool Bind(const std::string& ip, uint16_t port) {
        // 根据参数构造一个 sockaddr_in 结构
        // 调用 bind
        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
        addr.sin_port = htons(port);
        int ret = bind(fd_, (sockaddr*)&addr, sizeof(addr));
        if (ret < 0) {
            perror("bind");
            return false;
        }
        return true;
    }

    // 除了成功失败, 还需要返回啥?
    // 1. 读到的数据
    // 2. 对方的 ip 地址
    // 3. 对方的 端口号
    bool RecvFrom(std::string* msg, std::string* ip = NULL, 
        uint16_t* port = NULL) {
        char buf[1024 * 10] = {0};
        sockaddr_in peer;
        socklen_t len = sizeof(peer);
        ssize_t n = recvfrom(fd_, buf, sizeof(buf) - 1, 0,
            (sockaddr*)&peer, &len);
        if (n < 0) {
            perror("recvfrom");
            return false;
        }
        *msg = buf;
        if (ip != NULL) {
            *ip = inet_ntoa(peer.sin_addr);
        }
        if (port != NULL) {
            *port = ntohs(peer.sin_port);
        }
        return true;
    }

    bool SendTo(const std::string& msg,
        const std::string& ip, uint16_t port) {
        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
        addr.sin_port = htons(port);
        ssize_t n = sendto(fd_, msg.c_str(), msg.size(), 0,
            (sockaddr*)&addr, sizeof(addr));
        if (n < 0) {
            perror("sendto");
            return false;
        }
        return true;
    }
private:
    int fd_;    // 用来表示 socket
};