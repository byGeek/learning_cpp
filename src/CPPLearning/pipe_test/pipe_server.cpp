#include <Windows.h>
#include <stdio.h>

typedef struct _message {
	int id;
	char data[8];
} Message;

int main() {

	HANDLE h = INVALID_HANDLE_VALUE;
	const char* pipename = "\\\\.\\pipe\\mypipe";
	const int BUFSIZE = 1024;
	const int DEFAULT_TIMEOUT = 100;
	char buf[1024];

	h = CreateNamedPipe(
		pipename,
		PIPE_ACCESS_DUPLEX,/*| FILE_FLAG_OVERLAPPED*/
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE,
		PIPE_UNLIMITED_INSTANCES,
		BUFSIZE,
		BUFSIZE,
		DEFAULT_TIMEOUT,
		NULL
	);

	if (h == INVALID_HANDLE_VALUE) {
		exit(0);
	}

	if (ConnectNamedPipe(h, NULL)) {
		DWORD read = 0;
		if (ReadFile(h, buf, sizeof(Message), &read, NULL)
			&& read == sizeof(Message)) {
			Message* msg = reinterpret_cast<Message*>(buf);
			printf("get message from client: id: %d, data: %s\n", msg->id, msg->data);

			printf("ready to echo back!\n");

			DWORD written = 0;
			if (WriteFile(h, msg, sizeof(Message), &written, NULL)
				&& written == sizeof(Message)) {
				printf("echo back completed!\n");
			}
			else {
				printf("WriteFile failed: %d\n", GetLastError());
				exit(0);
			}
		}
		else {
			printf("ReadFile failed: %d\n", GetLastError());
			exit(0);
		}
	}
	else {
		printf("ConnectNamedPipe failed: %d\n", GetLastError());
		exit(0);
	}

	CloseHandle(h);

	getchar();
	exit(0);
}