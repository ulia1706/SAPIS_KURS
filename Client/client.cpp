#define _AFXDLL
//So you must use the DLL version of MFC and the DLL version of the C and C++ 
//runtime libraries, and link their import libraries, they take on that responsibility.
//And you have to tell the compiler about it, so that the library will go looking for the 
//right place for those globals.That requires #defining _AFXDLL.Read it like "the application
//framework lives in its own DLL".The CRT has a macro for that as well, it is _DLL.
#define _WINSOCK_DEPRECATED_NO_WARNINGS //постараться избавиться от этой штуки
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>

using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	WORD wVersionRequested;
	WSADATA wsaData;
	int err, t, t1 = 0, t2 = 0, t3 = 0;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData); //инициализируем WinSock API
	if (err != 0)
	{
		cout << "Ошибка использования Winsock DLL" << endl;
		return -1;
	}

	struct sockaddr_in peer;
	peer.sin_family = AF_INET;
	peer.sin_port = htons(1280);
	// т.к. клиент и сервер на одном компьютере,
	// пишем адрес 127.0.0.1
	peer.sin_addr.s_addr = inet_addr("127.0.0.1");
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0); //Создаем сокет, использующий протокол TCP, при помощи функции socket
	connect(s, (struct sockaddr*)&peer, sizeof(peer)); //Устанавливаем соединение с сервером, используя функцию connect.
	char b[500], buf[500], f[500], k[500], num[500];
	while (1) {
		recv(s, b, sizeof(b), 0); //прочитали информацию из сокета в b
		recv(s, f, sizeof(f), 0); //прочитали информацию из сокета в f
		cout << b; //вывели полученную в b информацию на экран
		cout << f; //вывели полученную в f информацию на экран
		cin >> t;  //ввели t (отвечает за выбор пункта в главном меню) ПРОВЕРКА НА КОРРЕКТНОЕ ЧИСЛО
		_itoa_s(t, b, 10); //преобразовали в символьный тип, записали в буфер b
		send(s, b, sizeof(b), 0); //отправили на сервер
		recv(s, k, sizeof(k), 0);
		t = atoi(k);   //число отвечающее за номер кейса в соответствии с главным меню
		switch (t) {
		case 1: {
			recv(s, k, sizeof(k), 0);
			cout << k << endl;
			while (t1 != 4) {
				recv(s, k, sizeof(k), 0);
				cout << k << endl;
				cin >> t1; //Провеееерка
				_itoa_s(t1, b, 10);
				send(s, b, sizeof(b), 0);
				recv(s, k, sizeof(k), 0);
				t1 = atoi(k);
				switch (t1) {
				case 1: {
					while (t2 != 4) {
						recv(s, k, sizeof(k), 0);
						cout << k << endl;
						cin >> t2;
						_itoa_s(t2, b, 10);
						send(s, b, sizeof(b), 0);
						recv(s, k, sizeof(k), 0);
						t2 = atoi(k);
						switch (t2) {
						case 1: {
							break;
						}
						case 2: {
							break;
						}
						case 3: {
							break;
						}
						case 4: {
							break;
						}
						}
					}
					t2 = 0;
					break;
				}
				case 2: {
					while (t2 != 5) {
						recv(s, k, sizeof(k), 0);
						cout << k << endl;
						cin >> t2;
						_itoa_s(t2, b, 10);
						send(s, b, sizeof(b), 0);
						recv(s, k, sizeof(k), 0);
						t2 = atoi(k);
						switch (t2) {
						case 1: {
							while (t3 != 3) {
								recv(s, k, sizeof(k), 0);
								cout << k << endl;
								cin >> t3;
								_itoa_s(t3, b, 10);
								send(s, b, sizeof(b), 0);
								recv(s, k, sizeof(k), 0);
								t3 = atoi(k);
								switch (t3) {
								case 1: {
									break;
								}
								case 2: {
									break;
								}
								case 3: {
									break;
								}
								case 4: {
									break;
								}
								case 5: {
									break;
								}
								}
							}
							t3 = 0;
							break;
							break;
						}
						case 2: {
							break;
						}
						case 3: {
							break;
						}
						case 4: {
							break;
						}
						case 5: {
							break;
						}
						}
					}
					t2 = 0;
					break;
				}
				case 3: {
					while (t2 != 3) {
						recv(s, k, sizeof(k), 0);
						cout << k << endl;
						cin >> t2;
						_itoa_s(t2, b, 10);
						send(s, b, sizeof(b), 0);
						recv(s, k, sizeof(k), 0);
						t2 = atoi(k);
						switch (t2) {
						case 1: {
							break;
						}
						case 2: {
							break;
						}
						case 3: {
							break;
						}
						}
					}
					t2 = 0;
					break;
				}
				case 4: {
					break;
				}
				}
			}
			t1 = 0;
			break;
		}
		case 2: {
			while (t1 != 6) {
				recv(s, k, sizeof(k), 0);
				cout << k << endl;
				cin >> t1;
				_itoa_s(t1, b, 10);
				send(s, b, sizeof(b), 0);
				recv(s, k, sizeof(k), 0);
				t1 = atoi(k);
				switch (t1) {
				case 1: {
					break;
				}
				case 2: {
					break;
				}
				case 3: {
					break;
				}
				case 4: {
					break;
				}
				case 5: {
					break;
				}
				case 6: {
					break;
				}
				}
			}
			t1 = 0;
			break;
		}
		case 3: {
			while (t1 != 3) {
				recv(s, k, sizeof(k), 0);
				cout << k << endl;
				cin >> t1;
				_itoa_s(t1, b, 10);
				send(s, b, sizeof(b), 0);
				recv(s, k, sizeof(k), 0);
				t1 = atoi(k);
				switch (t1) {
				case 1: {
					while (t2 != 5) {
						recv(s, k, sizeof(k), 0);
						cout << k << endl;
						cin >> t2;
						_itoa_s(t2, b, 10);
						send(s, b, sizeof(b), 0);
						recv(s, k, sizeof(k), 0);
						t2 = atoi(k);
						switch (t1) {
						case 1: {
							break;
						}
						case 2: {
							break;
						}
						case 3: {
							break;
						}
						case 4: {
							break;
						}
						case 5: {
							break;
						}
						}
					}
					t2 = 0;
					break;
				}
				case 2: {
					break;
				}
				case 3: {
					break;
				}
				}
			}
			t1 = 0;
			break;
		}
		case 4: {
			WSACleanup(); //завершение работы программы
			return 0;
		}
		}
	}
}