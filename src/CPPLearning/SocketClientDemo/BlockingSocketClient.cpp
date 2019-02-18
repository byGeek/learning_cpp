#undef UNICODE

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

#define PORT "55555"

int main() {

	WSADATA wsaData;

	SOCKET clientSocket = INVALID_SOCKET;
	int result = 0;

	struct addrinfo* ai = NULL;
	struct addrinfo hints;
	struct addrinfo* ptr;

	const int DEFAULT_LEN = 1024;
	char buf[DEFAULT_LEN];
	const char* testStr = "this is a socket test";


	DWORD timeout = 20;  //20ms test


	result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) {
		std::cout << "WSAStartup failed with error: " << WSAGetLastError() << "\n";
		goto FAILED;
	}



	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_socktype = SOCK_STREAM;

	result = getaddrinfo(NULL, PORT, &hints, &ai);
	if (result != 0) {
		std::cout << "getaddrinfo failed with error: " << WSAGetLastError() << "\n";
		goto FAILED;
	}

	for (ptr = ai; ptr != NULL; ptr = ai->ai_next) {
		clientSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (clientSocket == INVALID_SOCKET) {
			std::cout << "socket failed with error: " << WSAGetLastError() << "\n";
			goto FAILED;
		}

		result = connect(clientSocket, ptr->ai_addr, ptr->ai_addrlen);  //connect
		if (result == SOCKET_ERROR) {
			std::cout << "connect failed with error: " << WSAGetLastError() << "\n";
			closesocket(clientSocket);
			clientSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(ai);

	if (clientSocket == INVALID_SOCKET) {
		std::cout << "unable to connect to server!";
		goto FAILED;
	}

	result = send(clientSocket, testStr, strlen(testStr), 0);
	if (result == SOCKET_ERROR) {
		std::cout << "send failed with error: " << WSAGetLastError() << "\n";
		closesocket(clientSocket);
		goto FAILED;
	}

	std::cout << "bytes sent: " << result << "\ndata: " << testStr << "\n";

	result = shutdown(clientSocket, SD_SEND);  //send done
	if (result == SOCKET_ERROR) {
		std::cout << "shutdown failed with error: " << WSAGetLastError() << "\n";
		closesocket(clientSocket);
		goto FAILED;
	}

	/*set recv timeout using setsockopt*/
	/*result = setsockopt(clientSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
	if (result == SOCKET_ERROR) {
		std::cout << "setsockopt failed with error: " << WSAGetLastError() << "\n";
		closesocket(clientSocket);
		goto FAILED;
	}*/


	do {
		result = recv(clientSocket, buf, DEFAULT_LEN, 0);
		if (result > 0) {
			buf[result] = '\0';
			std::cout << "bytes recv: " << result << "\ndata: " << buf << "\n";
		}
		else if (result == 0) {
			std::cout << "connection closed!\n";
		}
		else {
			std::cout << "recv failed with error: " << WSAGetLastError() << "\n";
		}
	} while (result > 0);
	result = shutdown(clientSocket, SD_RECEIVE);
	if (result == SOCKET_ERROR) {
		std::cout << "shutdown failed with error: " << WSAGetLastError() << "\n";
	}

	closesocket(clientSocket);

	WSACleanup();
	std::cin.get();
	return 0;

FAILED:
	WSACleanup();
	std::cin.get();
	return 1;

}