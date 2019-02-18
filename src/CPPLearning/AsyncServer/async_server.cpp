#include <WinSock2.h>
#include <ws2tcpip.h>
#include <MSWSock.h>
#include <iostream>
#include <vector>
#include "sock_t.h"
#include "SockCtrl.h"

#pragma comment(lib, "ws2_32.lib")



//TODO: use unicode
static std::vector<HANDLE> g_vhandles;

static void got_new_conn(sock_t& psock);

int main() {

	//DWORD ret;
	//WSADATA d;

	//ret = WSAStartup(MAKEWORD(2, 2), &d);
	//if (ret != 0) {
	//	return -1;
	//}

	SockCtrl::Start();

	SOCKET sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (sock == INVALID_SOCKET) {
		WSACleanup();
		return -1;
	}

	DWORD reuse_addr = 1;
	DWORD ret = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse_addr, sizeof(reuse_addr));
	if (ret != 0) {
		closesocket(sock);
		WSACleanup();
		return -1;
	}

	GUID acceptex_guid = WSAID_ACCEPTEX;
	DWORD dwBytes = 0;
	LPFN_ACCEPTEX lpfnAccessEx;

	//msdn: https://docs.microsoft.com/en-us/windows/desktop/api/Winsock2/nf-winsock2-wsaioctl
	//call WSAIoctl to get a lpfnAccessEx pointer
	if (SOCKET_ERROR == WSAIoctl(sock,
		SIO_GET_EXTENSION_FUNCTION_POINTER,
		&acceptex_guid,
		sizeof(acceptex_guid),
		&lpfnAccessEx,
		sizeof(lpfnAccessEx),
		&dwBytes,
		NULL,
		NULL
	)) {
		closesocket(sock);
		WSACleanup();
		return -1;
	}

	sockaddr_in service;
	service.sin_family = AF_INET;
	
	const char* const address = "127.0.0.1";
	const int port = 55555;

	//service.sin_addr.s_addr = inet_addr(m_addr.c_str());
	inet_pton(AF_INET, address, &(service.sin_addr.s_addr));
	service.sin_port = htons(port);

	if (SOCKET_ERROR == bind(sock,
		(SOCKADDR*)&service,
		sizeof(service))) {

		closesocket(sock);
		WSACleanup();
		return -1;
	}

	if (SOCKET_ERROR == listen(sock, 100)) {
		closesocket(sock);
		WSACleanup();
		return -1;
	}

	char buf[1];  //we will receive nothing
	DWORD transfered;
	OVERLAPPED overlapped;
	ZeroMemory(&overlapped, sizeof(overlapped));
	overlapped.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	g_vhandles.emplace_back(overlapped.hEvent);

	SOCKET acceptSock = INVALID_SOCKET;
	BOOL r = SOCKET_ERROR;
	char* recvbuf = NULL;
	DWORD dwTransfered;

	bool keepListen = true;

	while (true) {

		if (keepListen) {
			keepListen = false;
			acceptSock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);

			r = lpfnAccessEx(sock,
				acceptSock,
				buf,
				0,  //read nothing
				sizeof(SOCKADDR_STORAGE) + 16,
				sizeof(SOCKADDR_STORAGE) + 16,
				&transfered,
				&overlapped
			);

			if (!r) {
				if (WSAGetLastError() != WSA_IO_PENDING) {
					closesocket(sock);
					closesocket(acceptSock);
					WSACleanup();
					return -1;
				}
			}
		}

		size_t size = g_vhandles.size();
		DWORD result = WaitForMultipleObjectsEx(size, g_vhandles.data(), false, INFINITE, true);
		if (result >= WAIT_OBJECT_0 && result <= WAIT_OBJECT_0 + size - 1) {
			if (result == WAIT_OBJECT_0) {
				//new connection
				sock_t* psock = new sock_t(acceptSock);

				got_new_conn(*psock);
				acceptSock = INVALID_SOCKET;
				keepListen = true;
				continue;

			}
		}
		else if (result = WAIT_IO_COMPLETION) {
			//read or write?
			//post another read/write request?



		}
		else {
			std::cout << "error in WaitForMultipleObjectEx: " << GetLastError() << std::endl;
		}
	}

	//WSACleanup();
}

static void __stdcall send_complete_routine(
	IN DWORD dwError,
	IN DWORD cbTransferred,
	IN LPWSAOVERLAPPED lpOverlapped,
	IN DWORD dwFlags
) {
	if (cbTransferred > 0) {
		sock_t* psock = reinterpret_cast<sock_t*>(lpOverlapped->hEvent);
		printf("sent %d bytes: %s\n", cbTransferred, psock->m_buf);

		shutdown(psock->m_sock, SD_SEND);

	}
}

static  void __stdcall recv_complete_routine(
	IN DWORD dwError,
	IN DWORD cbTransferred,
	IN LPWSAOVERLAPPED lpOverlapped,
	IN DWORD dwFlags
) {
	if (cbTransferred > 0) {
		sock_t* psock = reinterpret_cast<sock_t*>(lpOverlapped->hEvent);
		//psock->m_buf[cbTransferred] = '\0';
		printf("recv %d bytes: %s\n", cbTransferred, psock->m_buf);

		shutdown(psock->m_sock, SD_RECEIVE);

		char response[] = "world";

		//should copy to psock's m_buf memory
		//because response memory will be destroyed when leave the function scope
		memcpy_s(psock->m_buf, psock->m_bufsize, response, sizeof(response));
		psock->m_bufsize = sizeof(response);  //change buf size to actual data size

		PostSendRequest(*psock, send_complete_routine);
	}
	else {
		//todo: shutdownsock??
	}
}


static void got_new_conn(sock_t& tsock) {
	//todo: WSARecv use completion routine
	PostRecvRequest(tsock, recv_complete_routine);
}