#pragma once

#include <WinSock2.h>

struct sock_t {

	//todo: m_buf initialize null
	sock_t(SOCKET sock) : m_sock(sock), m_buf(new char[1024]), m_bufsize(1024) {
		//ZeroMemory(&m_overlapped, sizeof(m_overlapped);
		memset(&m_overlapped, 0, sizeof(m_overlapped));
	}

	~sock_t() {
		if (m_sock != INVALID_SOCKET) {
			/*
			In a multithreaded environment, WSACleanup terminates 
			Windows Sockets operations for all threads.

			Sockets that were open when WSACleanup was called are
			reset and automatically deallocated as if closesocket were called.
			*/

			closesocket(m_sock);  //must ensure that WSACleanup is not called first
		}
		if (m_buf != NULL) {
			delete[] m_buf;
		}
	}

	sock_t(const sock_t&) = delete;
	sock_t operator=(const sock_t&) = delete;


	SOCKET m_sock;
	OVERLAPPED m_overlapped;
	char* m_buf;
	size_t m_bufsize;
};


bool PostRecvRequest(sock_t& tsock,
	LPWSAOVERLAPPED_COMPLETION_ROUTINE routine) {

	memset(tsock.m_buf, 0, tsock.m_bufsize);

	WSABUF buf;
	buf.buf = tsock.m_buf;
	buf.len = tsock.m_bufsize;

	DWORD recvbytes = 0;
	DWORD flags = 0;

	tsock.m_overlapped.hEvent = &tsock;//pass context info

	DWORD ret = WSARecv(tsock.m_sock, &buf, 1, &recvbytes, &flags, &tsock.m_overlapped, routine);
	if (ret == SOCKET_ERROR) {
		if (WSAGetLastError() != WSA_IO_PENDING) {
			closesocket(tsock.m_sock);
			return false;
		}
	}

	return true;
}

bool PostSendRequest(sock_t& tsock,
	LPWSAOVERLAPPED_COMPLETION_ROUTINE routine) {

	WSABUF buf;
	buf.buf = tsock.m_buf;
	buf.len = tsock.m_bufsize;

	DWORD bytesent = 0;
	tsock.m_overlapped.hEvent = &tsock;  //pass context info

	DWORD flag = 0;

	DWORD ret = WSASend(tsock.m_sock, &buf, 1, &bytesent, flag, &tsock.m_overlapped, routine);
	if (ret == SOCKET_ERROR) {
		if (WSAGetLastError() != WSA_IO_PENDING) {
			closesocket(tsock.m_sock);
			WSACleanup();
			return false;
		}
	}

	return true;
}
