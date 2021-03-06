// SocketClientTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <WS2tcpip.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 15555

int main()
{
	WSADATA wsaData;
	int result = 0;
	result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) {
		WSACleanup();
		return -1;
	}

	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_port = htons(PORT);
	//service.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	inet_pton(AF_INET, "127.0.0.1", &(service.sin_addr.S_un.S_addr));

	SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (client == INVALID_SOCKET) {
		WSACleanup();
		return -1;
	}

	result = connect(client, (const sockaddr*)&service, sizeof(service));
	if (result == SOCKET_ERROR) {
		std::cout << "connect failed!" << std::endl;
		closesocket(client);
		WSACleanup();
		return -1;
	}

	const char* buf = "{\"id\": \"test\"}";
	result = send(client, buf, strlen(buf), 0);
	if (result < 0) {
		closesocket(client);
		WSACleanup();
		return -1;
	}

	shutdown(client, SD_SEND);  //send done

	char recvBuf[512];

	do{
		result = recv(client, recvBuf, 512, 0);
		if (result > 0) {

			recvBuf[result] = '\0';
			std::cout << "recv: "<<recvBuf << std::endl;
		}
		else if (result == 0) {
			std::cout << "connection closed" << std::endl;
		}
		else {
			std::cout << "recv failed with error: " << WSAGetLastError() << "\n";
		}

	} while (result > 0);

	closesocket(client);

	WSACleanup();

	std::cin.get();
}
