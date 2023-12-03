#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <locale.h>
#include <stdbool.h>
#define MAX_SIZE 1024
#define SIZE 100
#define PORT 6379

#pragma comment(lib, "ws2_32.lib")

SOCKET Socket(int af, int type, int protocol);

void Bind(SOCKET sock, const struct sockaddr* addr, int addrlen);

void Listen(SOCKET sock, int backlog);

SOCKET Accept(SOCKET sock, struct sockaddr* addr, int* addrlen);

void Connect(SOCKET sock, const struct sockaddr* addr, int addrlen);

void Inet_pton(int af, const char* src, void* dst);