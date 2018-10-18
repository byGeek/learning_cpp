
#undef UNICODE  //because following api are ANSI version

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

#define DEFAULT_PORT "20086"
#define DEFAULT_BUFLEN 1024

int main() {
	WSADATA wsaData;

	SOCKET listenSocket = INVALID_SOCKET;
	SOCKET clientSocket = INVALID_SOCKET;

	int err = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (err != 0) {
		std::cout << "WSAStartup failed with error: " << WSAGetLastError() << std::endl;
		std::cin.get();
		return 1;
	}

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;  //ipv4
	hints.ai_socktype = SOCK_STREAM;  //SOCK_STREAM ->tcp, SOCK_
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	err = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (err != 0) {
		std::cout << "getaddrinfo failed with error: " << WSAGetLastError() << std::endl;
		freeaddrinfo(result);
		WSACleanup();
		std::cin.get();
		return 1;
	}

	listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (listenSocket == INVALID_SOCKET) {
		std::cout << "socket failed with error: " << WSAGetLastError() << std::endl;
		freeaddrinfo(result);
		WSACleanup();
		std::cin.get();
		return 1;
	}

	err = bind(listenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (err == SOCKET_ERROR) {
		std::cout << "bind failed with error: " << WSAGetLastError() << std::endl;
		freeaddrinfo(result);
		WSACleanup();
		std::cin.get();
		return 1;
	}

	freeaddrinfo(result);

	err = listen(listenSocket, 10); //backlog set to 10
	if (err == SOCKET_ERROR) {
		std::cout << "listen failed with error: " << WSAGetLastError() << std::endl;
		closesocket(listenSocket);
		WSACleanup();
		std::cin.get();
		return 1;
	}

	std::cout << "listenning on port: " << DEFAULT_PORT << std::endl;

	clientSocket = accept(listenSocket, NULL, NULL); //blocking here
	if (clientSocket == INVALID_SOCKET) {
		std::cout << "accept failed with error: " << WSAGetLastError() << std::endl;
		closesocket(clientSocket);
		WSACleanup();
		std::cin.get();
		return 1;
	}

	closesocket(listenSocket);

	char recvBuf[DEFAULT_BUFLEN];
	int len = DEFAULT_BUFLEN;
	int recvCnt = 0;
	int sendCnt = 0;

	do {
		recvCnt = recv(clientSocket, recvBuf, len, 0);
		if (recvCnt > 0) {
			std::cout << "bytes received: " << recvCnt << std::endl;

			sendCnt = send(clientSocket, recvBuf, recvCnt, 0);
			if (sendCnt == SOCKET_ERROR) {
				std::cout << "send failed with error: " << WSAGetLastError() << std::endl;
				closesocket(clientSocket);
				WSACleanup();
				std::cin.get();
				return 1;
			}

			recvBuf[sendCnt] = '\0';
			std::cout << "bytes sent: " << sendCnt << ", data:" << recvBuf <<std::endl;
		}
		else if (recvCnt == 0) {
			std::cout << "connection closing...\n";
		}
		else {
			std::cout << "recv failed with error: " << WSAGetLastError() << std::endl;
			closesocket(clientSocket);
			WSACleanup();
			std::cin.get();
			return 1;
		}
	} while (recvCnt > 0);

	err = shutdown(clientSocket, SD_SEND);
	if (err == SOCKET_ERROR) {
		std::cout << "shutdown failed with error: " << WSAGetLastError() << std::endl;
		closesocket(clientSocket);
		WSACleanup();
		std::cin.get();
		return 1;
	}

	closesocket(clientSocket);
	WSACleanup();
	std::cin.get();

	return 0;
}