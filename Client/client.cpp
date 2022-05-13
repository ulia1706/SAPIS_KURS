#define _AFXDLL
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include<conio.h> //для getch()

using namespace std;

int CheckNumber()     //пропускает только целые числа
{
	int number;
	while (1) {
		cin >> number;
		if (cin.get() != '\n') {
			cout << "Это не похоже на целое число... Пожалуйста, повторите попытку: " << endl;
			cin.clear();
			cin.ignore(32767, '\n');
		}
		else return number;
	}
}

int CheckPlace(char* str) { //проверка на корректный ввод страны и города (буквы кириллицы, пробел, дефис)
	int flag = 0, k;
	k = strlen(str);
		for (int i = 0; i < k; i++) {
			if ((str[i] >= (-64)) && (str[i] <= (-1))) //буквы кириллицы
			{
				flag++;
			}
			if ((str[i] == (-88)) || (str[i] == (-72))) //"Ё" и "ё"
			{
				flag++;
			}
			if ((str[i] == 45) || (str[i] == 32)) { //дефис и пробел
				flag++;
			}
		}
		if (flag != k) return 1;
		else return 2;
}

int CheckPhone(char* str) { //проверка на корректный ввод номера телефона(цифры, пробел, дефис, круглые скобки, плюс)
	int flag = 0, k;
	k = strlen(str);
	for (int i = 0; i < k; i++) {
		if ((str[i] >= (48)) && (str[i] <= (57))) //цифры
		{
			flag++;
		}
		if ((str[i] == (41)) || (str[i] == (40))) //круглые скобки
		{
			flag++;
		}
		if ((str[i] == 43) || (str[i] == 32)) {// плюс и пробел
			flag++;
		}
		if (str[i] == 45) { //дефис
			flag++;
		}
	}
	if (flag != k) return 1; //при некорректном вводе
	else return 2;           //при корректном вводе
}

int CheckEmail(char* str) { //проверка на корректность ввода email
	int flag = 0, k,g=0;
	k = strlen(str);
	for (int i = 0; i < k; i++) {
		if ((str[i] >= 65) && (str[i] <= 90)) //большие латинские буквы
		{
			flag++;
		}
		if ((str[i] >= 97) && (str[i] <= 122)) //маленькие латинские буквы
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
	if ((flag != k)||(g!=2)) return 1; //при некорректном вводе
	else return 2;                     //при корректном вводе
}

float CheckFloat()     //пропускает целые и дробные числа
{
	float number;
	while (1) {
		cin >> number;
		if (cin.get() != '\n') {
			cout << "Это не похоже на целое или дробное число... Пожалуйста, повторите попытку: " << endl;
			cin.clear();
			cin.ignore(32767, '\n');
		}
		else return number;
	}
}

float CheckChoiceF(float a, float b) //сужает дробные числа до определённого диапазона (от a до b)
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

int CheckLogin(char* str) { //проверка на корректность введённого логина
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

int CheckPassword(char* str) { //проверка на корректность введённого пароля
	int flag = 0, k;
	k = strlen(str);
	if ((strlen(str) > 18) || (strlen(str) < 8)) {
		cout << "Пароль должен содержать от 8 до 18 символов.\nПожалуйста, попробуйте снова:" << endl;
		return 0;
	}
	for (int i = 0; i < k; i++) {
		if ((str[i] >= (-64)) && (str[i] <= (-1))) //не включает буквы кириллицы, дефис и пробел
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

int CheckLetters(char stroka[100]) //проверка для ФИО (только буквы кириллицы)
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
	int err, t, t1 = 0, t2 = 0, t3 = 0; //набор переменных для работы
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
	peer.sin_addr.s_addr = inet_addr("127.0.0.1");       //выбор адреса обусловлен тем, что сервер и клиент расположены на одном компьютере
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);          //создаем сокет, использующий протокол TCP, при помощи функции socket
	connect(s, (struct sockaddr*)&peer, sizeof(peer));   //устанавливаем соединение с сервером, используя функцию connect
	char b[500], buf[500], f[500], k[500], num[500];     //набор "буферов" для работы
	while (1) {                                          //ЦИКЛ ГЛАВНОГО МЕНЮ
		f[0] = '\0'; b[0] = '\0';
		recv(s, b, sizeof(b), 0); recv(s, f, sizeof(f), 0);
		cout << b; cout << f;
		t=CheckChoice(1,4);                              //выбор пункта в главном меню
		_itoa_s(t, b, 10);                              
		send(s, b, sizeof(b), 0); 
		recv(s, k, sizeof(k), 0);
		t = atoi(k);                                     //номер кейса в главном меню
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
							b[0] = '\0';
							k[0] = '\0';
							strcpy_s(k, "конец");
							strcpy_s(b, "f");
							while (strcmp(b, k) != 0) {
								b[0] = '\0';
								recv(s, b, sizeof(b), 0);
								cout << b << endl;
							}
							cout << "вышел из цикла" << endl;
							k[0] = '\0';
							break;
						}
						case 2: {
							b[0] = '\0';
							cout << "Введите интересующего Вас поставщика:" << endl;
							cin.getline(b, 50, '\n');
							send(s, b, sizeof(b), 0);
							k[0] = '\0';
							f[0] = '\0';
							strcpy_s(f, "Такой поставщик не был зарегистрирован!\n");
							strcpy_s(k, "конец");
							while ((strcmp(b, k) != 0) && (strcmp(b, f) != 0)) {
								b[0] = '\0';
								recv(s, b, sizeof(b), 0);
								cout << b << endl;
							}
							cout << "вышел из цикла" << endl;
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
			
			while (t1 != 3) {
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
					//авторизация
					f[0] = '\0';
					strcpy_s(f, "a");
					while (strcmp(f, "b") != 0) {
						b[0] = '\0';
						k[0] = '\0';
						cout << "Введите логин:  " << endl;
						cin.getline(b, 50, '\n');
						cout << "Введите пароль:  " << endl;
						cin.getline(k, 50, '\n');
						send(s, b, sizeof(b), 0);
						send(s, k, sizeof(b), 0);
						f[0] = '\0';
						recv(s, f, sizeof(f), 0);
					}
					while (t1 != 5) {
						k[0] = '\0';
						b[0] = '\0';
						recv(s, k, sizeof(k), 0);
						cout << k << endl;
						k[0] = '\0';
						t1 = CheckChoice(1, 5);
						_itoa_s(t1, b, 10);
						send(s, b, sizeof(b), 0);
						recv(s, k, sizeof(k), 0);
						t1 = atoi(k);
						k[0] = '\0';
						b[0] = '\0';
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
					t1 = 0;
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
		case 3: {
			while (t1 != 3) {
				k[0] = '\0';
				b[0] = '\0';
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
						k[0] = '\0';
						b[0] = '\0';
						recv(s, k, sizeof(k), 0);
						cout << k << endl;
						t2=CheckChoice(1,5);
						_itoa_s(t2, b, 10);
						send(s, b, sizeof(b), 0);
						recv(s, k, sizeof(k), 0);
						t2 = atoi(k);
						switch (t2) {
						case 1: {
							b[0] = '\0';
							k[0] = '\0';
							strcpy_s(k, "конец");
							strcpy_s(b, "f");
							while (strcmp(b, k) != 0) {
								b[0] = '\0';
								recv(s, b, sizeof(b), 0);
								cout << b << endl;
							}
							cout << "вышел из цикла" << endl;
							k[0] = '\0';
							break;
						}
						case 2: {
							b[0] = '\0';
							cout << "Введите интересующую Вас страну:" << endl;
							cin.getline(b, 50, '\n');
							send(s, b, sizeof(b), 0);
							k[0] = '\0';
							f[0] = '\0';
							strcpy_s(f, "Поставщик из заданной страны не найден!\n");
							strcpy_s(k, "конец");
							while ((strcmp(b, k) != 0)&&(strcmp(b, f)!=0)) {
								b[0] = '\0';
								recv(s, b, sizeof(b), 0);
								cout << b << endl;
							}
							cout << "вышел из цикла" << endl;
							break;
						}
						case 3: {
							b[0] = '\0';
							float a, c;
							cout << "Введите нижнюю границу минимальной суммы разовой закупки:" << endl;
							a = CheckChoiceF(1, 1000000000);
							sprintf_s(b, "%.2f", a);
							//cin.getline(b, 50, '\n');
							send(s, b, sizeof(b), 0);
							b[0] = '\0';
							cout << "Введите верхнюю границу минимальной суммы разовой закупки:" << endl;
							c = CheckChoiceF(1, 1000000000);
							sprintf_s(b, "%.2f", c);
							//cin.getline(b, 50, '\n');
							send(s, b, sizeof(b), 0);
							k[0] = '\0';
							f[0] = '\0';
							strcpy_s(f, "Такие поставщики не найдены!\n");
							strcpy_s(k, "конец");
							while ((strcmp(b, k) != 0) && (strcmp(b, f) != 0)) {
								b[0] = '\0';
								recv(s, b, sizeof(b), 0);
								cout << b << endl;
							}
							cout << "вышел из цикла" << endl;
							break;
						}
						case 4: {
							b[0] = '\0';
							cout << "Введите интересующего Вас поставщика:" << endl;
							cin.getline(b, 50, '\n');
							send(s, b, sizeof(b), 0);
							k[0] = '\0';
							f[0] = '\0';
							strcpy_s(f, "Такой поставщик не был зарегистрирован!\n");
							strcpy_s(k, "конец");
							while ((strcmp(b, k) != 0) && (strcmp(b, f) != 0)) {
								b[0] = '\0';
								recv(s, b, sizeof(b), 0);
								cout << b << endl;
							}
							cout << "вышел из цикла" << endl;
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