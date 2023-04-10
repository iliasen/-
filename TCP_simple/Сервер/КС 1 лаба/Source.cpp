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

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	SOCKET newConnection;
	newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

	if (newConnection == 0) {
		std::cout << "Error\n";
	}
	else {
		std::cout << "Клиент подключился к серверу\n";
		char m[256],n[256];
		recv(newConnection,m,sizeof(m),NULL);
		recv(newConnection, n, sizeof(n), NULL);

		int k = atoi(m);
		int l = atoi(n);
		int a=1;
		while (k != 1) 
		{
			a = a*k;
			k--;
		}
		int b = 1;
		while (l != 1)
		{
			b = b * l;
			l--;
		}
		int sum = a + b;
		char msg[256];
		itoa(sum, (char*)msg, 10);

		send(newConnection, msg, sizeof(msg), NULL);
		std::cout << "Результат отправлен клиенту\n";
	}


	system("pause");
	return 0;
}