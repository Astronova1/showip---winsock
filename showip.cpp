//
// Created by Dark on 23/06/2026.
//
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <cstring>
using namespace std;

int main(int argc, char *argv[]) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        cerr << "WSAStartup() failed." << endl;
        WSACleanup();
        return 1;
    }

    struct addrinfo hints, *res, *p;

    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <hostname>" << endl;
        return 1;
    }

    memset(&hints, 0, sizeof(hints));     //set hints to 0
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;               //use tcp connection
    char ipst[INET6_ADDRSTRLEN];

    int status;
    if ((status = getaddrinfo(argv[1], nullptr, &hints, &res )) != 0) {
        cerr << "getaddrinfo() failed with " << gai_strerror(status) <<endl;
        return 2;
    }

    for (p = res; p != nullptr; p = p->ai_next) {
        struct sockaddr_in* ipv4;
        struct sockaddr_in6* ipv6;
        void* addr;
        const char* ipver;

        if (p->ai_family == AF_INET) {
            ipv4 = (struct sockaddr_in*)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        }
        else {
            ipv6 = (struct sockaddr_in6*)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }
        inet_ntop(p->ai_family,addr ,ipst, sizeof ipst);
        cout << ipver << " " << ipst << endl;
    }
    freeaddrinfo(res);
    WSACleanup();
}