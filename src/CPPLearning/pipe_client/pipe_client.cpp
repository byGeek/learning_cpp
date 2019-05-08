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

	h = CreateFile(pipename,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL
	);
	if (h == INVALID_HANDLE_VALUE) {
		printf("open pipe failed: %d\n", GetLastError());
		exit(0);
	}

	Message m = { 1, "hello" };
	DWORD written = 0;
	if (WriteFile(h, &m, sizeof(Message), &written, NULL)
		&& written == sizeof(Message)) {

		printf("client write pipe finished\n");

		char buf[1024];
		DWORD read = 0;
		if (ReadFile(h, buf, sizeof(Message), &read, NULL)
			&& read == sizeof(Message)) {
			Message* msg = reinterpret_cast<Message*>(buf);
			printf("received message: id: %d, data: %s\n", msg->id, msg->data);
		}
		else {
			printf("read pipe failed: %d\n", GetLastError());
			exit(0);
		}

	}
	else {
		printf("Write Pipe failed: %d\n", GetLastError());
		exit(0);
	}

	CloseHandle(h);

	getchar();
	exit(0);
}