#define _AFXDLL
//So you must use the DLL version of MFC and the DLL version of the C and C++ 
//runtime libraries, and link their import libraries, they take on that responsibility
//And you have to tell the compiler about it, so that the library will go looking for the 
//right place for those globals.That requires #defining _AFXDLL.Read it like "the application
//framework lives in its own DLL".The CRT has a macro for that as well, it is _DLL.
#define _WINSOCK_DEPRECATED_NO_WARNINGS //постараться избавиться от этой штуки
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include<conio.h> //для getch

using namespace std;

int CheckNumber()     //пропускает только целые числа
{
	int number;
	while (1) {
		cin >> number;
		if (cin.get() != '\n') {
			cout << "Это не похоже на целое число... Повторите попытку : " << endl;
			cin.clear();
			cin.ignore(32767, '\n');
		}
		else return number;
	}
}

int CheckPlace(char* str) {
	int flag = 0, k;
	k = strlen(str);
		for (int i = 0; i < k; i++) {
			if ((str[i] >= (-64)) && (str[i] <= (-1)))
			{
				flag++;
			}
			if ((str[i] == (-88)) || (str[i] == (-72)))
			{
				flag++;
			}
			if ((str[i] == 45) || (str[i] == 32)) {
				flag++;
			}
		}
		if (flag != k) return 1;
		else return 2;
}

int CheckPhone(char* str) {
	int flag = 0, k;
	k = strlen(str);
	for (int i = 0; i < k; i++) {
		if ((str[i] >= (48)) && (str[i] <= (57)))
		{
			flag++;
		}
		if ((str[i] == (41)) || (str[i] == (40)))
		{
			flag++;
		}
		if ((str[i] == 43) || (str[i] == 32)) {
			flag++;
		}
		if (str[i] == 45) {
			flag++;
		}
	}
	if (flag != k) return 1;
	else return 2;
}

int CheckEmail(char* str) {
	int flag = 0, k,g=0;
	k = strlen(str);
	for (int i = 0; i < k; i++) {
		if ((str[i] >= 65) && (str[i] <= 90)) //большие латинские
		{
			flag++;
		}
		if ((str[i] >= 97) && (str[i] <= 122)) //маленькие латинские
		{
			flag++;
		}
		if ((str[i] >= (48)) && (str[i] <= (57))) //цифры
		{
			flag++;
		}
		if ((str[i] == '-') || (str[i] == '_')) {
			flag++;
		}
		if ((str[i] == '@') || (str[i] == '.')) {
			flag++;
			g++;
		}
	}
	if ((flag != k)||(g!=2)) return 1;
	else return 2;
}

float CheckFloat()     //пропускает дробные числа и числа с плавающей точкой
{
	float number;
	while (1) {
		cin >> number;
		if (cin.get() != '\n') {
			cout << "Это не похоже на целое или дробное число... Повторите попытку : " << endl;
			cin.clear();
			cin.ignore(32767, '\n');
		}
		else return number;
	}
}

float CheckChoiceF(float a, float b) //сужает целые числа до определённого диапазона (от a до b)
{
	float choice = 0;
	while (choice == 0) {
		choice = CheckFloat();
		if ((choice < a) || (choice > b)) {
			cout << "Такой вариант невозможен! Пожалуйста, повторите попытку:" << endl;
			choice = 0;
		}
	}
	return choice;
}

int CheckChoice(int a, int b) //сужает целые числа до определённого диапазона (от a до b)
{
	int choice = 0;
	while (choice == 0) {
		choice = CheckNumber();
		if ((choice < a) || (choice > b)) {
			cout << "Такой вариант невозможен! Пожалуйста, повторите попытку:" << endl;
			choice = 0;
		}
	}
	return choice;
}

int CheckLogin(char* str) {
	int flag = 0, k;
	k = strlen(str);
	for (int i = 0; i < k; i++) {
		if ((str[i] >= 65) && (str[i] <= 90)) //большие латинские
		{
			flag++;
		}
		if ((str[i] >= 97) && (str[i] <= 122)) //маленькие латинские
		{
			flag++;
		}
		if ((str[i] >= (48)) && (str[i] <= (57))) //цифры
		{
			flag++;
		}
		if ((str[i] == '.') || (str[i] == '_')) {
			flag++;
		}
	}
	if ((strlen(str) > 16) || (strlen(str) < 6)) {
		cout << "Логин должен содержать от 6 до 16 символов.\nПожалуйста, попробуйте снова:" << endl;
		return 0;
	}
	if (flag != k) return 1;
	else return 2;
}

int CheckPassword(char* str) {
	int flag = 0, k;
	k = strlen(str);
	if ((strlen(str) > 18) || (strlen(str) < 8)) {
		cout << "Пароль должен содержать от 8 до 18 символов.\nПожалуйста, попробуйте снова:" << endl;
		return 0;
	}
	for (int i = 0; i < k; i++) {
		if ((str[i] >= (-64)) && (str[i] <= (-1)))
		{
			flag++;
		}
		if ((str[i] == (-88)) || (str[i] == (-72)))
		{
			flag++;
		}
		if ((str[i] == 45) || (str[i] == 32)) {
			flag++;
		}
	}
	if (flag != 0) return 1;
	else return 2;
}

//bool check(char* str)
//{
//	for (int i = 0; str[i] != '\0'; i++)
//		if (str[i] == '!' || str[i] == '@' || str[i] == '#' || str[i] == '$' || str[i] == '%' || str[i] == '^' || str[i] == '&' || str[i] == '*' || str[i] == '/' || str[i] == '.')
//			return false;
//	return true;
//}

int CheckLetters(char stroka[100]) //добавить ещё английские буковки может???
{
	int k, flag = 0;
	k = strlen(stroka);
	while (flag != k)
	{
		for (int i = 0; i < k; i++)
		{
			int l = flag;
			if ((stroka[i] >= (-64)) && (stroka[i] <= (-1)))
			{
				flag++;
			}
			if ((stroka[i] == (-88)) || (stroka[i] == (-72)))
			{
				flag++;
			}
			if (flag == l)
			{
				i = k;
			}
		}
		if (flag != k)
		{
			return 1;
		}
		else return 2;
	}
}

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
		t=CheckChoice(1,4);  //ввели t (отвечает за выбор пункта в главном меню)
		_itoa_s(t, b, 10); //преобразовали в символьный тип, записали в буфер b
		send(s, b, sizeof(b), 0); //отправили на сервер
		recv(s, k, sizeof(k), 0);
		t = atoi(k);   //число отвечающее за номер кейса в соответствии с главным меню
		system("cls");
		switch (t) {
		case 1: {
			recv(s, k, sizeof(k), 0);
			cout << k << endl;
			while (t1 != 4) {
				recv(s, k, sizeof(k), 0);
				cout << k << endl;
				t1=CheckChoice(1,4);
				_itoa_s(t1, b, 10);
				send(s, b, sizeof(b), 0);
				recv(s, k, sizeof(k), 0);
				t1 = atoi(k);
				switch (t1) {
				case 1: {
					while (t2 != 4) {
						recv(s, k, sizeof(k), 0);
						cout << k << endl;
						t2=CheckChoice(1,4);
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
						t2=CheckChoice(1,5);
						_itoa_s(t2, b, 10);
						send(s, b, sizeof(b), 0);
						recv(s, k, sizeof(k), 0);
						t2 = atoi(k);
						switch (t2) {
						case 1: {
							while (t3 != 3) {
								recv(s, k, sizeof(k), 0);
								cout << k << endl;
								t3=CheckChoice(1,3);
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
						t2=CheckChoice(1,3);
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
				t1=CheckChoice(1,6);
				_itoa_s(t1, b, 10);
				send(s, b, sizeof(b), 0);
				recv(s, k, sizeof(k), 0);
				t1 = atoi(k);
				system("cls");
				switch (t1) {
				case 1: {
					int a = 0;
					float c =0;
					//вводим название организации
						cout << "Введите название вашей организации:  ";
						cin.getline(buf, 50, '\n');
						send(s, buf, sizeof(buf), 0);
					
					//вводим страну локации поставщика
					cout << "Введите страну локации поставщика:  ";
					while (a != 2) {
						buf[0] = '\0';
						cin.getline(buf, 50, '\n');
						a = CheckPlace(buf);
						if (a == 1) { cout << "Здесь могут быть только буквы кириллицы, дефис и пробел! Пожалуйста, попробуйте снова:" << endl; }
					}
					send(s, buf, sizeof(buf), 0);
					a = 0;
					//вводим город локации поставщика
					cout << "Введите город локации поставщика:  ";
					while (a != 2) {
						buf[0] = '\0';
						cin.getline(buf, 50, '\n');
						a = CheckPlace(buf);
						if (a == 1) { cout << "Здесь могут быть только буквы кириллицы, дефис и пробел! Пожалуйста, попробуйте снова:" << endl; }
					}
					send(s, buf, sizeof(buf), 0);
					a = 0;
					//вводим фамилию представителя
					cout << "Введите фамилию представителя:  ";
					while (a != 2) {
						buf[0] = '\0';
						cin.getline(buf, 50, '\n');
						a = CheckLetters(buf);
						if (a == 1) { cout << "В данном поле могут быть использованы только буквы кириллицы!" << endl; }
					}
					send(s, buf, sizeof(buf), 0);
					a = 0;
					//вводим имя представителя
					cout << "Введите имя представителя:  ";
					while (a != 2) {
						buf[0] = '\0';
						cin.getline(buf, 50, '\n');
						a = CheckLetters(buf);
						if (a == 1) { cout << "В данном поле могут быть использованы только буквы кириллицы!" << endl; }
					}
					send(s, buf, sizeof(buf), 0);
					a = 0;
					//вводим отчество представителя
					cout << "Введите отчество представителя:  ";
					while (a != 2) {
						buf[0] = '\0';
						cin.getline(buf, 50, '\n');
						a = CheckLetters(buf);
						if (a == 1) { cout << "В данном поле могут быть использованы только буквы кириллицы!" << endl; }
					}
					send(s, buf, sizeof(buf), 0);
					a = 0;
					//вводим номер телефона представителя
					cout << "Введите номер телефона:  ";
					while (a != 2) {
						buf[0] = '\0';
						cin.getline(buf, 50, '\n');
						a = CheckPhone(buf);
						if (a == 1) { cout << "Кажется, номер телефона введён некорректно... Пожалуйста, попробуйте снова:" << endl; }
					}
					send(s, buf, sizeof(buf), 0);
					a = 0;
					//вводим электронную почту
					cout << "Введите электронную почту:  ";
					while (a != 2) {
						buf[0] = '\0';
						cin.getline(buf, 50, '\n');
						a = CheckEmail(buf);
						if (a == 1) { cout << "Кажется, адрес электронной почты введён некорректно...\nПожалуйста, попробуйте снова:" << endl; }
					}
					send(s, buf, sizeof(buf), 0);
					a = 0;
					buf[0] = '\0';
					//вводим количество действующих контрактов
					cout << "Введите количество действующих контрактов:  ";
					a = CheckChoice(1, 100000);
					_itoa_s(a, buf, 10);
					send(s, buf, sizeof(buf), 0);
					a = 0;
					buf[0] = '\0';
					//вводим минимальную сумму разовой закупки
					cout << "Введите минимальную сумму разовой закупки:  ";
					c = CheckChoiceF(1, 1000000000);
					sprintf_s(buf, "%.2f", c);
					send(s, buf, sizeof(buf), 0);
					a = 0;
					buf[0] = '\0';
					////вводим информацию об имеющихся договорах с заказчиками
					//int choice,cho;
					//cout << "Введите данные о заключённых с заказчиками договорах." << endl;
					//cout << "1. Перейти к следующему шагу.\n2. Ввести данные." << endl;
					//choice = CheckChoice(1, 2);
					//cho = choice;
					//int ch1 = 0;
					//buf[0] = '\0';
					//_itoa_s(cho, buf, 10);
					//send(s, buf, sizeof(buf), 0);
					//if (choice == 2) {
					//	while (ch1 != 1) {
					//		cout << "Введите название организации-заказчика:  ";
					//		buf[0] = '\0';
					//		cin.getline(buf, 50, '\n');
					//		send(s, buf, sizeof(buf), 0);
					//		cout << "Введите номер договора:  ";
					//		buf[0] = '\0';
					//		cin.getline(buf, 50, '\n');
					//		send(s, buf, sizeof(buf), 0);
					//		if (ch1 != 1) { cout << "1. Перейти к следующему шагу.\n2. Продолжить ввод данных." << endl; ch1 = CheckChoice(1, 2); }
					//		cho = ch1;
					//		buf[0] = '\0';
					//		_itoa_s(cho, buf, 10);
					//		send(s, buf, sizeof(buf), 0);
					//	}
					//}
					//задаём логин
					int ch = 0;
					while (ch != -1) {
						cout << "Придумайте логин:  ";
						while (a != 2) {
							buf[0] = '\0';
							cin.getline(buf, 50, '\n');
							a = CheckLogin(buf);
							if (a == 1) { cout << "Были использованы недопустимые символы. Повторите попытку:" << endl; }
						}
						send(s, buf, sizeof(buf), 0);
						k[0] = '\0';
						recv(s, k, sizeof(k), 0);
						ch = atoi(k);
						cout << ch << endl;
						k[0] = '\0';
						a = 0;
						buf[0] = '\0';
					}
					
					//задаём пароль
					int j = 0;
					cout << "Придумайте пароль:  ";
					a = 0;
					while (a != 2) {
						buf[0] = '\0';
						for (;;) {
							buf[j] = _getch();
							if (buf[j] == '\r')
								break;
							if (buf[j] == '\b') {
								cout << "\b \b";
								j--;
							}
							else if (buf[j] != '\0') {
								cout << "*";
								j++;
							}
						}
						buf[j] = '\0';
						//cin.getline(buf, 50, '\n');
						a = CheckPassword(buf);
						if (a == 1) { cout << "Были использованы недопустимые символы. Повторите попытку:" << endl; }
					}
					send(s, buf, sizeof(buf), 0);
					a = 0;
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
				t1=CheckChoice(1,3);
				_itoa_s(t1, b, 10);
				send(s, b, sizeof(b), 0);
				recv(s, k, sizeof(k), 0);
				t1 = atoi(k);
				switch (t1) {
				case 1: {
					while (t2 != 5) {
						recv(s, k, sizeof(k), 0);
						cout << k << endl;
						t2=CheckChoice(1,5);
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