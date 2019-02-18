#include <WinSock2.h>
#include <ws2tcpip.h>
#include <MSWSock.h>
#include <cstdio>
#include "sock_t.h"
#include "SockCtrl.h"

#pragma comment(lib, "ws2_32.lib")


HANDLE g_dummyEvent;

void WINAPI dummyAPC(ULONG_PTR param) {}

static  void __stdcall recv_complete_routine(
	IN DWORD dwError,
	IN DWORD cbTransferred,
	IN LPWSAOVERLAPPED lpOverlapped,
	IN DWORD dwFlags
) {
	sock_t* tsock = reinterpret_cast<sock_t*>(lpOverlapped->hEvent);

	if (cbTransferred > 0) {
		printf("recv %d bytes: %s\n", cbTransferred, tsock->m_buf);

		shutdown(tsock->m_sock, SD_RECEIVE);

		SetEvent(g_dummyEvent);
		//QueueUserAPC(dummyAPC, GetCurrentThread(), NULL);  //tell main loop to exit
	}
}

static  void __stdcall send_complete_routine(
	IN DWORD dwError,
	IN DWORD cbTransferred,
	IN LPWSAOVERLAPPED lpOverlapped,
	IN DWORD dwFlags
) {

	if (cbTransferred > 0) {
		sock_t* psock = reinterpret_cast<sock_t*>(lpOverlapped->hEvent);
		printf("sent %d bytes: %s\n", cbTransferred, psock->m_buf);

		shutdown(psock->m_sock, SD_SEND);

		PostRecvRequest(*psock, recv_complete_routine);
	}

}


int main() {

	//DWORD ret;
	//WSADATA wsadata;

	//ret = WSAStartup(MAKEWORD(2, 2), &wsadata);
	//if (ret != 0) {
	//	return -1;
	//}
	SockCtrl::Start();

	SOCKET sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (sock == INVALID_SOCKET) {
		WSACleanup();
		return -1;
	}

	sockaddr_in service;
	service.sin_family = AF_INET;

	const char* const address = "127.0.0.1";
	const int port = 55555;

	inet_pton(AF_INET, address, &(service.sin_addr.s_addr));
	service.sin_port = htons(port);

	DWORD ret = connect(sock, (const sockaddr*)&service, sizeof(service));
	if (ret != 0) {
		closesocket(sock);
		WSACleanup();
		return -1;
	}
	
	char data[] = "hello";

	sock_t tsock(sock);
	memcpy_s(tsock.m_buf, tsock.m_bufsize, data, sizeof(data));
	tsock.m_bufsize = sizeof(data);

	PostSendRequest(tsock, send_complete_routine);//send "hello"
	

	g_dummyEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	while (true)
	{
		DWORD r = WaitForSingleObjectEx(g_dummyEvent, INFINITE, true);//rely on APC
		if (r == WAIT_OBJECT_0) {
			printf("got exit signal, exiting...\n");
			break;
		}
		else if (r == WAIT_IO_COMPLETION) {
			//todo: do something
		}
		else {

		}
	}

	//WSACleanup();
	return 0;
}

