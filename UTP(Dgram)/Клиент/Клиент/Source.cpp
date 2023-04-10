//#include<WinSock2.h>
//#include<iostream>
//#include <clocale>
//#include<string>
//#pragma comment(lib, "ws2_32.lib")
//#pragma warning(disable: 4996)
//
//using namespace std;
//
//int main() {
//
//	setlocale(LC_ALL, "ru");
//
//	WSADATA wsaData;
//	if (WSAStartup(MAKEWORD(2, 2), &wsaData)) {
//		cout << "������ �����������!" << endl;
//		exit(1);
//	}
//	else cout << "����� � �������� �����������!" << endl;
//
//	struct sockaddr_in addrServer;
//	int sizeServer = sizeof(addrServer);
//	addrServer.sin_addr.s_addr = 0;
//	addrServer.sin_family = AF_INET;
//	addrServer.sin_port = htons(1280);
//
//	SOCKET udp = socket(AF_INET, SOCK_DGRAM, 0);
//
//	while (1) {
//		char stroka[256], result[256];
//		cout << "������� ���������: ";
//		cin.getline(stroka,256,'\n');
//		
//		if (sendto(udp, stroka, sizeof(stroka), 0, (SOCKADDR*)&addrServer, sizeServer!=SOCKET_ERROR)){
//			cout << "���� ���������: " << stroka << " ����������" << endl;
//		}
//		
//		recvfrom(udp, result, sizeof(result), 0, (SOCKADDR*)&addrServer, &sizeServer);
//		cout << " Result" << result << endl;
//		
//	}
//}


#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <iostream>
#include<stdio.h>
#include<io.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;


int main(void)
{
	SetConsoleCP(1251);
	setlocale(LC_ALL, "rus");
	WSADATA wsaData;
	int erStat = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (erStat) {
		cout << "������ ������������� ������ WinSock";
		return 1;
	}

	SOCKET s;
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s == INVALID_SOCKET) {
		cout << "������ ������������� ������" << endl;
		closesocket(s);
		WSACleanup();
	}

	sockaddr_in add;
	add.sin_family = AF_INET;
	add.sin_port = htons(1280);
	add.sin_addr.s_addr = inet_addr("127.0.0.1");
	int t = sizeof(add);

	while (true)
	{
		char buff[100] = "";
		char buff1[100] = "";
		cout << "������� ������(### - �����):" << endl;
		cin.getline(buff, 100, '\n');
		if (!strcmp(buff, "###")) {
			break;
		}
		sendto(s, buff, strlen(buff) + 1, 0, (struct sockaddr*)&add, t);

		recvfrom(s, buff1, sizeof(buff1), 0, (struct sockaddr*)&add, &t);

		cout << "���������� ��������� - " << buff1 << endl;
	}

	closesocket(s);
	WSACleanup();
	return 0;
}
