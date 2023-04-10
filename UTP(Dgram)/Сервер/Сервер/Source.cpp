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
//		cout << "Ошибка инициализации версии WinSock";
//		return 1;
//	}
//	else cout << "Сервер подключен!" << endl;
//
//	struct sockaddr_in addrServer;
//	int sizeServer = sizeof(addrServer);
//	addrServer.sin_addr.s_addr = htonl(INADDR_ANY);
//	addrServer.sin_family = AF_INET;
//	addrServer.sin_port = htons(1280);
//
//	SOCKET s = socket(AF_INET, SOCK_DGRAM, 0); // используется сокет дейтаграмм (средства поддержки не очень надежного обмена пакетами.)
//	erStat = bind((SOCKET)s, (SOCKADDR*)&addrServer, sizeServer);
//	listen(s, SOMAXCONN);
//	char stroka[256], result[256];
//
//	while (1) {
//		cout << "Ghbrjk" << endl;
//		if (recvfrom(s, stroka, sizeof(stroka), 0, (SOCKADDR*)&addrServer, &sizeServer)!=SOCKET_ERROR) 
//		{ // Последние два параметра используются для получения адреса сокета, пославшего дейтаграмму. По этому адресу можно по¬слать ответ
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
//			cout << "\nОТПРАВЛЕННАЯ строка: " << result << endl;
//		}
//		else cout << "\nОшибка передачи данных!\n";
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
	// структура для WSAStartup
	WSADATA wsaData;
	// инициализируем WinSock API
	int erStat = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (erStat) {
		cout << "Ошибка инициализации версии WinSock";
		return 1;
	}

	// Создаем серверный сокет, использующий протокол UDP
	SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s == INVALID_SOCKET) {
		cout << "Ошибка инициализации сокета" << endl;
		closesocket(s);
		WSACleanup();
	}

	// Создаем структуру данных соединения
	struct sockaddr_in ad;
	ad.sin_family = AF_INET;
	ad.sin_port = htons(1280);
	// Слушаем все сетевые соединения
	ad.sin_addr.s_addr = htonl(INADDR_ANY);
	int size_ad = sizeof(ad);

	// Принимаем данные от приложения-клиента
	char buff[100];
	char buff1[100] = "";

	//Связывание сокета с локальным адресом
	erStat = bind((SOCKET)s, (LPSOCKADDR)&ad, size_ad);
	if (erStat != 0) {
		cout << "Ошибка связывания сокета с адресом" << endl;
		closesocket(s);
		WSACleanup();
		return 1;
	}
	cout << "Сервер запущен" << endl;

	//Если получены какие-то данные, то обработаем их
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
	// Завершаем работу сокета
	closesocket(s);
	// Завершаем использование WinSock DLL
	WSACleanup();
	return 0;
}
