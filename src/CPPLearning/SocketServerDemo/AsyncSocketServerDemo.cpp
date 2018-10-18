//// SocketServerDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
////
//
//#include <iostream>
//
//// Need to link with Ws2_32.lib
//#pragma comment(lib, "ws2_32.lib")
//
//#include <WinSock2.h>
//#include <WS2tcpip.h>
//
//
//int main()
//{
//
//	const short PORT = 20086;
//
//	WORD wVersionRequested;
//	WSADATA wsaData;
//	int err;
//
//	/* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
//	wVersionRequested = MAKEWORD(2, 2);
//
//	err = WSAStartup(wVersionRequested, &wsaData);
//
//	if (err != 0) {
//		std::cout << "WSAStartup failed with error: " << err << std::endl;
//		return 1;
//	}
//
//	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
//		std::cout << "could not find a usable version of winsock.dll\n";
//		WSACleanup();
//		return 1;
//	}
//
//	SOCKET serverSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
//	if (serverSocket == INVALID_SOCKET) {
//		std::cout << "WSASocket function failed with error: " << WSAGetLastError() << std::endl;
//		WSACleanup();
//		return 1;
//	}
//
//
//
//	WSACleanup();
//
//
//}
//
