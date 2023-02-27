#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <locale.h>

#pragma warning(disable: 4996)

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru");
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Вы не подключились к серверу.\n";
		return 1;
	}
	std::cout << "Добро пожаловать!\n";
	char m[256],n[256];
	std::cout << "Введите m:";
	std::cin >> m;
	std::cout << "Введите n: ";
	std::cin >> n;
	send(Connection, m, sizeof(m), NULL);
	send(Connection, n, sizeof(n), NULL);
	char msg[256];
	recv(Connection, msg, sizeof(msg), NULL);
	std::cout <<"Сумма факториалов m!+n!=" << msg << std::endl;

	system("pause");
	return 0;
}