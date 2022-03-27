#define _AFXDLL  //содержат MFC в DLL
#include <iostream>
#include <afx.h>  //для ускорения компиляции проектов
#include <winsock2.h>
#include <process.h> /* _beginthread, _endthread */  //содержит объявления функций и макросы, используемые при работе с потоками и процессами
#include <string.h>
#include <fstream>

using namespace std;
CFile f;  //Базовый класс для файловых классов Microsoft Foundation Class. Создает CFileобъект из пути или дескриптора файла
CFileException ex;

void mailWorking(void* newS) {
	int c, c1 = 0, c2 = 0, c3 = 0;
	int flag = 0;
	char p[500], com[200], k[500], m[500];
	com[0] = '\0'; p[0] = '\0'; k[0] = '\0'; m[0] = '\0';
	cout << "Сервер работает.\n";
	while (1) {
		strcpy_s(p, "Добро пожаловать в Автосалон.\n");
		send((SOCKET)newS, p, sizeof(p), 0);
		strcpy_s(k, "Меню:\n 1)Войти в качестве администратора;\n 2)Войти в качестве поставщика;\n 3)Войти в качестве эксперта;\n 4)Завершить работу программы.\n ");
		send((SOCKET)newS, k, sizeof(k), 0);
		p[0] = '\0'; k[0] = '\0';
		recv((SOCKET)newS, m, sizeof(m), 0);
		c = atoi(m);
		switch (c) {
		case 1: {
			strcpy_s(p, "1");
			send((SOCKET)newS, p, sizeof(p), 0);
			strcpy_s(p, "Авторизация");
			send((SOCKET)newS, p, sizeof(p), 0);
			while (c1 != 4) {
				strcpy_s(k, "Меню администратора:\n 1)Работа с поставщиками;\n 2)Управление экспертами;\n 3)Изменить пароль и/или логин;\n 4)Выйти в главное меню.\n ");
				send((SOCKET)newS, k, sizeof(k), 0);
				recv((SOCKET)newS, m, sizeof(m), 0);
				c1 = atoi(m);
				switch (c1) {
				case 1: {
					strcpy_s(p, "1");
					send((SOCKET)newS, p, sizeof(p), 0);
					while (c2 != 3) {
						strcpy_s(p, "Меню работы с поставщиками:\n 1)Просмотреть информацию об имеющихся поставщиках;\n 2)Прекратить сотрудничество с поставщиком;\n 3)Выйти в меню администратора.\n");
						send((SOCKET)newS, p, sizeof(p), 0);
						recv((SOCKET)newS, m, sizeof(m), 0);
						c2 = atoi(m);
						switch (c2) {
						case 1: {
							strcpy_s(p, "1");
							send((SOCKET)newS, p, sizeof(p), 0);
							break;
						}
						case 2: {
							strcpy_s(p, "2");
							send((SOCKET)newS, p, sizeof(p), 0);
							break;
						}
						case 3: {
							strcpy_s(p, "3");
							send((SOCKET)newS, p, sizeof(p), 0);
							break;
						}
						}
					}
					c2 = 0;
					break;
				}
				case 2: {
					strcpy_s(p, "2");
					send((SOCKET)newS, p, sizeof(p), 0);
					while (c2 != 6) {
						strcpy_s(p, "Меню управления экспертами:\n 1)Просмотреть информацию об экспертах;\n 2)Назначить эксперта;\n 3)Просмотреть заключенные договора;\n 4)Удалить эксперта;\n 5)Отредактировать информацию об эксперте;\n 6)Выйти в меню администратора.\n");
						send((SOCKET)newS, p, sizeof(p), 0);
						recv((SOCKET)newS, m, sizeof(m), 0);
						c2 = atoi(m);
						switch (c2) {
						case 1: {
							strcpy_s(p, "1");
							send((SOCKET)newS, p, sizeof(p), 0);
							while (c3 != 3) {
								strcpy_s(p, "Меню вывода информации об экспертах:\n 1)Просмотреть информацию об экспертах в алфавитном порядке;\n 2)Просмотреть информацию об экспертах в порядке убывания стажа;\n 3)Выйти в меню управления экспертами.\n");
								send((SOCKET)newS, p, sizeof(p), 0);
								recv((SOCKET)newS, m, sizeof(m), 0);
								c3 = atoi(m);
								switch (c3) {
								case 1: {
									strcpy_s(p, "1");
									send((SOCKET)newS, p, sizeof(p), 0);
									break;
								}
								case 2: {
									strcpy_s(p, "2");
									send((SOCKET)newS, p, sizeof(p), 0);
									break;
								}
								case 3: {
									strcpy_s(p, "3");
									send((SOCKET)newS, p, sizeof(p), 0);
									break;
								}
								}
							}
							c3 = 0;
							break;
						}
						case 2: {
							strcpy_s(p, "2");
							send((SOCKET)newS, p, sizeof(p), 0);
							break;
						}
						case 3: {
							strcpy_s(p, "3");
							send((SOCKET)newS, p, sizeof(p), 0);
							break;
						}
						case 4: {
							strcpy_s(p, "4");
							send((SOCKET)newS, p, sizeof(p), 0);
							break;
						}
						case 5: {
							strcpy_s(p, "5");
							send((SOCKET)newS, p, sizeof(p), 0);
							break;
						}
						case 6: {
							strcpy_s(p, "6");
							send((SOCKET)newS, p, sizeof(p), 0);
							break;
						}
						}
					}
					c2 = 0;
					break;
				}
				case 3: {
					strcpy_s(p, "3");
					send((SOCKET)newS, p, sizeof(p), 0);
					while (c2 != 3) {
						strcpy_s(p, "Меню изменения пароля и/или логина:\n 1)Изменить пароль;\n 2)Изменить логин;\n 3)Выйти в меню администратора.\n");
						send((SOCKET)newS, p, sizeof(p), 0);
						recv((SOCKET)newS, m, sizeof(m), 0);
						c2 = atoi(m);
						switch (c2) {
						case 1: {
							strcpy_s(p, "1");
							send((SOCKET)newS, p, sizeof(p), 0);
							break;
						}
						case 2: {
							strcpy_s(p, "2");
							send((SOCKET)newS, p, sizeof(p), 0);
							break;
						}
						case 3: {
							strcpy_s(p, "3");
							send((SOCKET)newS, p, sizeof(p), 0);
							break;
						}
						}
					}
					c2 = 0;
					break;
				}
				case 4: {
					strcpy_s(p, "4");
					send((SOCKET)newS, p, sizeof(p), 0);
					break;
				}
				}
			}
			c1 = 0;
			break;
		}
		case 2: {
			strcpy_s(p, "2");
			send((SOCKET)newS, p, sizeof(p), 0);
			p[0] = '\0';
			while (c1 != 4) {
				strcpy_s(k, "Меню поставщика:\n 1)Ввести информацию о своих услугах;\n 2)Отредактировать информацию о своих услугах;\n 3)Удалить информацию о своих услугах;\n 4)Выйти в главное меню.\n ");
				send((SOCKET)newS, k, sizeof(k), 0);
				recv((SOCKET)newS, m, sizeof(m), 0);
				c1 = atoi(m);
				switch (c1) {
				case 1: {
					strcpy_s(p, "1");
					send((SOCKET)newS, p, sizeof(p), 0);
					break;
				}
				case 2: {
					strcpy_s(p, "2");
					send((SOCKET)newS, p, sizeof(p), 0);
					break;
				}
				case 3: {
					strcpy_s(p, "3");
					send((SOCKET)newS, p, sizeof(p), 0);
					break;
				}
				case 4: {
					strcpy_s(p, "4");
					send((SOCKET)newS, p, sizeof(p), 0);
					break;
				}
				}
			}
			c1 = 0;
			break;
		}
		case 3: {
			strcpy_s(p, "3");
			send((SOCKET)newS, p, sizeof(p), 0);
			while (c1 != 3) {
				strcpy_s(k, "Меню эксперта:\n 1)Просмотреть информацию о потенциальных поставщиках;\n 2)Выбрать наиболее подходящего поставщика;\n 3)Выйти в главное меню.\n ");
				send((SOCKET)newS, k, sizeof(k), 0);
				recv((SOCKET)newS, m, sizeof(m), 0);
				c1 = atoi(m);
				switch (c1) {
				case 1: {
					strcpy_s(p, "1");
					send((SOCKET)newS, p, sizeof(p), 0);
					while (c2 != 5) {
						strcpy_s(k, "Меню просмотра информации о потенциальных поставщиках:\n 1)Просмотреть информацию о потенциальных поставщиках в алфавитном порядке;\n 2)Просмотреть информацию о потенциальных поставщиках с фильтрацией по странам;\n 3)Просмотреть информацию о потенциальных поставщиках в определенном ценовом диапазоне;\n 4)Найти и просмотреть информацию о конкретном поставщике;\n 5)Выйти в меню эксперта.\n ");
						send((SOCKET)newS, k, sizeof(k), 0);
						recv((SOCKET)newS, m, sizeof(m), 0);
						c1 = atoi(m);
						switch (c1) {
						case 1: {
							strcpy_s(p, "1");
							send((SOCKET)newS, p, sizeof(p), 0);
							break;
						}
						case 2: {
							strcpy_s(p, "2");
							send((SOCKET)newS, p, sizeof(p), 0);
							break;
						}
						case 3: {
							strcpy_s(p, "3");
							send((SOCKET)newS, p, sizeof(p), 0);
							break;
						}
						case 4: {
							strcpy_s(p, "4");
							send((SOCKET)newS, p, sizeof(p), 0);
							break;
						}
						case 5: {
							strcpy_s(p, "5");
							send((SOCKET)newS, p, sizeof(p), 0);
							break;
						}
						}
					}
					c2 = 0;
					break;
				}
				case 2: {
					strcpy_s(p, "2");
					send((SOCKET)newS, p, sizeof(p), 0);
					break;
				}
				case 3: {
					strcpy_s(p, "3");
					send((SOCKET)newS, p, sizeof(p), 0);
					break;
				}
				}
			}
			c1 = 0;
			break;
		}
		case 4: {
			strcpy_s(p, "4");
			send((SOCKET)newS, p, sizeof(p), 0);
			closesocket((SOCKET)newS);
			exit(EXIT_SUCCESS);
			break;
		}
		}

		///(c = recv((SOCKET)newS, p, sizeof(p), 0) != 0)
	}

}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
		return -1;
	sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(1280);
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	int c = bind(s, (struct sockaddr*)&local, sizeof(local));
	int r = listen(s, 5);
	while (true) {
		sockaddr_in remote;
		int j = sizeof(remote);
		SOCKET newS = accept(s, (struct sockaddr*)&remote, &j);
		_beginthread(mailWorking, 0, (void*)newS);  //создание потока(Начальный адрес процедуры, который начинает выполнение нового потока; размер стека нового потока или 0; список аргументов, передаваемый в новый поток, или NULL)
	}
	WSACleanup();
	return 0;
}