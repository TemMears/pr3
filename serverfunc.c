#include "server.h"

SOCKET Socket(int af, int type, int protocol) {
    WSADATA wsaData;
    int err = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (err != 0) {
        printf("WSAStartup failed with error: %d\0", err);
        return INVALID_SOCKET;
    }

    SOCKET sock = socket(af, type, protocol);
    if (sock == INVALID_SOCKET) {
        printf("socket failed with error: %ld\0", WSAGetLastError());
        WSACleanup();
        return INVALID_SOCKET;
    }

    return sock;
}

void Bind(SOCKET sock, const struct sockaddr* addr, int addrlen) {
    int res = bind(sock, addr, addrlen);
    if (res == SOCKET_ERROR) {
        printf("bind failed with error: %d\0", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        exit(EXIT_FAILURE);
    }
}

void Listen(SOCKET sock, int backlog) {
    int res = listen(sock, backlog);
    if (res == SOCKET_ERROR) {
        printf("listen failed with error: %d\0", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        exit(EXIT_FAILURE);
    }
}

SOCKET Accept(SOCKET sock, struct sockaddr* addr, int* addrlen) {
    SOCKET clientSock = accept(sock, addr, addrlen);
    if (clientSock == INVALID_SOCKET) {
        printf("accept failed with error: %d\0", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    return clientSock;
}

void Connect(SOCKET sock, const struct sockaddr* addr, int addrlen) {
    int res = connect(sock, addr, addrlen);
    if (res == SOCKET_ERROR) {
        printf("connect failed with error: %d\0", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        exit(EXIT_FAILURE);
    }
}

void Inet_pton(int af, const char* src, void* dst) {
    int res = inet_pton(af, src, dst);
    if (res == 0) {
        printf("inet_pton failed: src does not contain a character string representing a valid network address in the specified address family.\0");
        exit(EXIT_FAILURE);
    }
    if (res == -1) {
        printf("inet_pton failed with error: %d\0", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
}
