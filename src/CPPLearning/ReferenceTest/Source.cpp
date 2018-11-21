#pragma comment(lib, "ws2_32.lib")

#include <WinSock2.h>
#include <memory>
#include <vector>
#include <iostream>


void foo(int a, int&b) {
	int x, y;
	int& xx = b;
	int* yy = &a;
	x = a;
	y = b;

}

class cfoo {
public:
	cfoo(SOCKET s, int b) : m_sock(s), m_b(b) {

	}

private:
	SOCKET m_sock;
	int& m_b;
};


static std::vector<std::unique_ptr<cfoo>> g_conns;

int main() {
	int t1 = 1;
	int t2 = 2;
	foo(t1, t2);

	SOCKET s = 128;
	int b = 100;
	//cfoo* ptr = new cfoo(s);
	g_conns.emplace_back(new cfoo(s, b));
	std::cout << "pause" << std::endl;
}