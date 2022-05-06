#define _AFXDLL  //содержат MFC в DLL
#include <iostream>
#include <afx.h>  //для ускорения компиляции проектов
#include <winsock2.h>
#include <process.h> /* _beginthread, _endthread */  //содержит объявления функций и макросы, используемые при работе с потоками и процессами
#include <string.h>
#include <fstream>
#include <list>

using namespace std;
CFile f;  //Базовый класс для файловых классов Microsoft Foundation Class. Создает CFileобъект из пути или дескриптора файла
CFileException ex;

class Authorization {
protected:
	char login[20];
	char password[20];
public:
	int CheckLogin(); //возвращает 1, если всё правильно, 2 - если неправильно (к примеру) //проверка правильности логина
	int CheckPassword(); //проверка правильности пароля
	void ChangeLogin(); //изменить логин
	void ChangePassword(); //изменить пароль
};

class CarShowroom: public Authorization {
protected:
	//добавить информации об автосалоне
	char name[50]; //название автосалона
	char F[50]; //фамилия сотрудника автосалона
	char I[50]; //имя сотрудника
	char O[50]; //отчество
public:
	void SetF(); //ввести фамилию
	void SetI(); //ввести имя
	void SetO(); //ввести отчество
};

class Admin :public CarShowroom {
public:
	//методы администратора
};

class Expert : public CarShowroom {
	int pos; //должность
	int exp; //опыт
public:
	Expert() {
		strcpy_s(F, "-");
		strcpy_s(I, "-");
		strcpy_s(O, "-");
		pos = 0;
		exp = 0;
	}
	//методы эксперта
	friend bool operator<(Expert e1, Expert e2);
};

bool operator<(Expert e1, Expert e2) {
	return strcmp(e1.F, e2.F) < 0;
}

class Supplier :public CarShowroom {
	char name[50]; //название организации
	char phone[20]; //контактный телефон
	char email[50]; //электронная почта
	int contracts; //количество действующих договоров
	//список договоров
	//список заявок
	float min_price; //цена минимальной разовой закупки
public:
	Supplier() {
		strcpy_s(name, "-");
		strcpy_s(phone, "-");
		strcpy_s(email, "-");
		contracts = 0;
		min_price = 0;
	}
	friend bool operator<(Supplier s1, Supplier s2);
	//методы поставщика
};

bool operator<(Supplier s1, Supplier s2) {
	return strcmp(s1.F, s2.F) < 0;
}

class Contract{}; //информация и методы, связанные с контрактами для обеих сторон,
//этот класс будет включен в виде списка в класс админ/салон и класс поставщик

class Request{}; //инфа и методы о заявках для обеих сторон

class Method{}; //поля и методы, связанные с методом ранга, включён в класс эксперты

void mailWorking(void* newS) {
	int c, c1 = 0, c2 = 0, c3 = 0;
	int flag = 0;
	char p[500], com[200], k[500], m[500];
	com[0] = '\0'; p[0] = '\0'; k[0] = '\0'; m[0] = '\0';
	cout << "Сервер работает.\n";
	while (1) {
		strcpy_s(p, "ГЛАВНОЕ МЕНЮ:\n");
		send((SOCKET)newS, p, sizeof(p), 0);
		strcpy_s(k, " 1. Войти как администратор.\n 2. Войти как поставщик.\n 3. Войти как эксперт.\n 4. Завершить работу.\n ");
		send((SOCKET)newS, k, sizeof(k), 0);
		p[0] = '\0'; k[0] = '\0';
		recv((SOCKET)newS, m, sizeof(m), 0); //получили, какой пункт в главном меню выбрал клиент
		c = atoi(m); //преобразовали в число типа инт
		switch (c) {
		case 1: {
			strcpy_s(p, "1");
			send((SOCKET)newS, p, sizeof(p), 0); //передала в клиент единицу, чтобы у клиента открылся соответствующий кейс
			strcpy_s(p, "Здесь будет авторизация админа. Честно, будет))");
			send((SOCKET)newS, p, sizeof(p), 0);
			while (c1 != 4) {
				strcpy_s(k, "МЕНЮ АДМИНИСТРАТОРА:\n 1. Работа с поставщиками.\n 2. Управление экспертами.\n 3. Изменить логин и/или пароль.\n 4. Вернуться в главное меню.");
				send((SOCKET)newS, k, sizeof(k), 0);
				recv((SOCKET)newS, m, sizeof(m), 0);
				c1 = atoi(m);
				switch (c1) {
				case 1: {
					strcpy_s(p, "1"); //дали знать клиентскому приложению, с каким кейсом работаем
					send((SOCKET)newS, p, sizeof(p), 0);
					while (c2 != 4) {
						strcpy_s(p, "РАБОТА С ПОСТАВЩИКАМИ:\n 1. Просмотреть список имеющихся поставщиков.\n 2. Заключить договор.\n 3. Расторгнуть договор. \n 4. Вернуться в меню администратора.\n");
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
						case 4: {
							strcpy_s(p, "4");
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
					while (c2 != 5) {
						strcpy_s(p, "УПРАВЛЕНИЕ ЭКСПЕРТАМИ:\n 1. Просмотреть информацию об экспертах.\n 2. Назначить эксперта.\n 3. Удалить эксперта.\n 4. Отредактировать информацию об эксперте. \n 5. Вернуться в меню администратора.\n");
						send((SOCKET)newS, p, sizeof(p), 0);
						recv((SOCKET)newS, m, sizeof(m), 0);
						c2 = atoi(m);
						switch (c2) {
						case 1: {
							strcpy_s(p, "1");
							send((SOCKET)newS, p, sizeof(p), 0);
							while (c3 != 3) {
								strcpy_s(p, "ИНФОРМАЦИЯ ОБ ЭКСПЕРТАХ:\n 1. Просмотреть в алфавитном порядке. \n 2. Просмотреть в порядке убывания стажа.\n 3. Вернуться в меню управления экспертами.\n");
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
						}
					}
					c2 = 0;
					break;
				}
				case 3: {
					strcpy_s(p, "3");
					send((SOCKET)newS, p, sizeof(p), 0);
					while (c2 != 3) {
						strcpy_s(p, "ИЗМЕНИТЬ ЛОГИН И/ИЛИ ПАРОЛЬ:\n 1. Изменить пароль.\n 2. Изменить логин.\n 3. Вернуться в меню администратора.\n");
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
			while (c1 != 6) {
				strcpy_s(k, "МЕНЮ ПОСТАВЩИКА:\n 1. Ввести информацию.\n 2. Отредактировать информацию.\n 3. Удалить информацию.\n 4. Заключить договор.\n 5. Расторгнуть договор.\n 6. Вернуться в главное меню.\n ");
				send((SOCKET)newS, k, sizeof(k), 0);
				recv((SOCKET)newS, m, sizeof(m), 0);
				c1 = atoi(m);
				switch (c1) {
				case 1: {
					strcpy_s(p, "1");
					send((SOCKET)newS, p, sizeof(p), 0);
					recv((SOCKET)newS, com, sizeof(m), 0);
					cout << com << endl;
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
			c1 = 0;
			break;
		}
		case 3: {
			strcpy_s(p, "3");
			send((SOCKET)newS, p, sizeof(p), 0);
			while (c1 != 3) {
				strcpy_s(k, "МЕНЮ ЭКСПЕРТА:\n 1. Просмотреть информацию о потенциальных поставщиках.\n 2. Выбрать наиболее подходящего поставщика.\n 3. Вернуться в главное меню.\n ");
				send((SOCKET)newS, k, sizeof(k), 0);
				recv((SOCKET)newS, m, sizeof(m), 0);
				c1 = atoi(m);
				switch (c1) {
				case 1: {
					strcpy_s(p, "1");
					send((SOCKET)newS, p, sizeof(p), 0);
					while (c2 != 5) {
						strcpy_s(k, "ИНФОРМАЦИЯ О ПОТЕНЦИАЛЬНЫХ ПОСТАВЩИКАХ:\n 1. В алфавитном порядке.\n 2. С фильтрацией по странам.\n 3. С фильтрацией по минимальной разовой цене закупки.\n 4. Поиск конкретного поставщика.\n 5. Вернуться в меню эксперта.\n ");
						send((SOCKET)newS, k, sizeof(k), 0);
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
			closesocket((SOCKET)newS); //сокет закрываем
			exit(EXIT_SUCCESS);        //и выходим
			break;
		}
		}
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
	if (err != 0) {
		cout << "Ошибка использования Winsock DLL" << endl;
		return -1;
	}

	sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(1280);
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	int c = bind(s, (struct sockaddr*)&local, sizeof(local)); //соединение с сокетом
	int r = listen(s, 5);  //режим ожидания запросов от клиентов
	while (true) {
		sockaddr_in remote;
		int j = sizeof(remote);
		SOCKET newS = accept(s, (struct sockaddr*)&remote, &j);
		_beginthread(mailWorking, 0, (void*)newS);  //создание потока(Начальный адрес процедуры, который начинает выполнение нового потока; размер стека нового потока или 0; список аргументов, передаваемый в новый поток, или NULL)
	}
	WSACleanup();  //прекращаем работу Winsock API
	return 0;
}