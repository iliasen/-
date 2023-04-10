//#include<WinSock2.h>
//#include<iostream>
//#include<string>
//#include <clocale>
//#pragma comment(lib, "ws2_32.lib")
//#pragma warning(disable: 4996)
//
//using namespace std;
//
//int main() {
//	setlocale(LC_ALL, "ru");
//	WSADATA wsaData;
//
//	int erStat = WSAStartup(MAKEWORD(2, 2), &wsaData);
//	if (erStat) {
//		cout << "������ ������������� ������ WinSock";
//		return 1;
//	}
//	else cout << "������ ���������!" << endl;
//
//	struct sockaddr_in addrServer;
//	int sizeServer = sizeof(addrServer);
//	addrServer.sin_addr.s_addr = htonl(INADDR_ANY);
//	addrServer.sin_family = AF_INET;
//	addrServer.sin_port = htons(1280);
//
//	SOCKET s = socket(AF_INET, SOCK_DGRAM, 0); // ������������ ����� ���������� (�������� ��������� �� ����� ��������� ������ ��������.)
//	erStat = bind((SOCKET)s, (SOCKADDR*)&addrServer, sizeServer);
//	listen(s, SOMAXCONN);
//	char stroka[256], result[256];
//
//	while (1) {
//		cout << "Ghbrjk" << endl;
//		if (recvfrom(s, stroka, sizeof(stroka), 0, (SOCKADDR*)&addrServer, &sizeServer)!=SOCKET_ERROR) 
//		{ // ��������� ��� ��������� ������������ ��� ��������� ������ ������, ���������� �����������. �� ����� ������ ����� ������� �����
//			cout << "dsadasda" << endl;
//			cout << stroka << endl;
//
//			char check[] = "WINDOWS";
//			int key=0;
//			for (int i = 0; i < 8; i++) {
//				if (stroka[i] == check[i]) {
//					key++;
//				}
//			}
//			cout << key << endl;
//
//			//itoa(key,result,256);
//			cin.getline(result, 256, '\n');
//			cout << "!!!!!!!!!!!!!!!!" << result << endl;
//			sendto(s, result, sizeof(result), 0, (SOCKADDR*)&addrServer, sizeServer);
//			cout << "\n������������ ������: " << result << endl;
//		}
//		else cout << "\n������ �������� ������!\n";
//	}
//
//	closesocket(s);
//	WSACleanup();
//	system("pause");
//	return 0;
//}


#define _CRT_SECURE_NO_DEPRECATE 
#include <iostream>
#include <string>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

int main()
{
	SetConsoleCP(1251);
	setlocale(LC_ALL, "rus");
	// ��������� ��� WSAStartup
	WSADATA wsaData;
	// �������������� WinSock API
	int erStat = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (erStat) {
		cout << "������ ������������� ������ WinSock";
		return 1;
	}

	// ������� ��������� �����, ������������ �������� UDP
	SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s == INVALID_SOCKET) {
		cout << "������ ������������� ������" << endl;
		closesocket(s);
		WSACleanup();
	}

	// ������� ��������� ������ ����������
	struct sockaddr_in ad;
	ad.sin_family = AF_INET;
	ad.sin_port = htons(1280);
	// ������� ��� ������� ����������
	ad.sin_addr.s_addr = htonl(INADDR_ANY);
	int size_ad = sizeof(ad);

	// ��������� ������ �� ����������-�������
	char buff[100];
	char buff1[100] = "";

	//���������� ������ � ��������� �������
	erStat = bind((SOCKET)s, (LPSOCKADDR)&ad, size_ad);
	if (erStat != 0) {
		cout << "������ ���������� ������ � �������" << endl;
		closesocket(s);
		WSACleanup();
		return 1;
	}
	cout << "������ �������" << endl;

	//���� �������� �����-�� ������, �� ���������� ��
	while(recvfrom((SOCKET)s, (LPSTR)&buff, sizeof(buff), 0, (LPSOCKADDR)&ad, &size_ad))
	{
		cout << buff << endl;
		char check[] = "WINDOWS";
		int key=0;
		for (int i = 0; i < 8; i++) {
			if (buff[i] == check[i]) {
				key++;
			}
		}
		cout << key << endl;
		_itoa(key,buff1,100);
		sendto((SOCKET)s, (LPCSTR)&buff1, strlen(buff1) + 1, 0, (LPSOCKADDR)&ad, size_ad);	
	}
	// ��������� ������ ������
	closesocket(s);
	// ��������� ������������� WinSock DLL
	WSACleanup();
	return 0;
}
