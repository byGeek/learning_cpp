#pragma once

#include <WinSock2.h>


class SockCtrl {
public:
	static bool Start(){
		static SockCtrl ctrl;
		return err;
	}

	~SockCtrl() {
		WSACleanup();
	}

	SockCtrl(const SockCtrl&) = delete;
	SockCtrl& operator=(const SockCtrl&) = delete;

private:
	SockCtrl() {
		err = 0;
		WSADATA wsaData;
		err = WSAStartup(MAKEWORD(2, 2), &wsaData);
	}

	static int err; //declaration

};

int SockCtrl::err = 0;  //definition