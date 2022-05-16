#define _AFXDLL
#define _WINSOCK_DEPRECATED_NO_WARNINGS        //???
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include<conio.h> //для getch()

using namespace std;

int CheckNumber()     //только целые числа
{
	int number;
	while (1) {
		cin >> number;
		if (cin.get() != '\n') {
			cout << "Это не похоже на целое число... Повторите ввод: " << endl;
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

float CheckFloat()     //целые и дробные числа
{
	float number;
	while (1) {
		cin >> number;
		if (cin.get() != '\n') {
			cout << "Это не похоже на целое или дробное число... Повторите ввод: " << endl;
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
			cout << "Такой вариант невозможен! Повторите ввод:" << endl;
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
			cout << "Такой вариант невозможен! Повторите ввод:" << endl;
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
		cout << "Логин должен содержать от 6 до 16 символов.\nПопробуйте снова:" << endl;
		return 0;
	}
	if (flag != k) return 1; //при некорректном логине
	else return 2;           //при корректном
}

int CheckPassword(char* str) { //проверка на корректность введённого пароля
	int flag = 0, k;
	k = strlen(str);
	if ((strlen(str) > 18) || (strlen(str) < 8)) {
		cout << "Пароль должен содержать от 8 до 18 символов.\nПопробуйте снова:" << endl;
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
	if (flag != 0) return 1; //при некорректном пароле
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
			return 1; //при некорректном вводе
		}
		else return 2;
	}
}


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int err, t, t1 = 0, t2 = 0, t3 = 0;

	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData); //инициализация WinSock API
	if (err != 0)
	{
		cout << "Ошибка использования Winsock DLL" << endl;
		return -1;
	}
	struct sockaddr_in peer;
	peer.sin_family = AF_INET;
	peer.sin_port = htons(1280);
	peer.sin_addr.s_addr = inet_addr("127.0.0.1");       //выбор адреса обусловлен тем, что сервер и клиент расположены на одном компьютере
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);          //создание сокета, использующего протокол TCP, при помощи функции socket
	connect(s, (struct sockaddr*)&peer, sizeof(peer));   //установление соединения с сервером при помощи функции connect
	char b[500], buf[500], f[500], k[500], num[500];    
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
			int choice;
			f[0] = '\0';
			recv(s, f, sizeof(f), 0);
			cout << "1. Войти.\n2. Зарегистрироваться." << endl;
			choice = CheckChoice(1, 2);
			system("cls");
			if (strcmp(f, "m") == 0) {
				cout<< "Администратор уже был зарегистрирован! Используйте логин и пароль для входа:" << endl;
				choice = 1;
			}
			else {
				cout<<"Администратор ещё не был зарегистрирован! Пожалуйста, придумайте логин и пароль для входа:" << endl;
				choice = 2;
			}
			k[0] = '\0';
			_itoa_s(choice, k, 10);
			send(s, k, sizeof(k), 0);
			if (choice == 1) {
				//авторизация
				char log[500];
				f[0] = '\0';
				strcpy_s(f, "a");
				while (strcmp(f, "b") != 0) {
					b[0] = '\0';
					k[0] = '\0';
					cout << "Введите логин:  " << endl;
					cin.getline(b, 50, '\n');
					int j = 0;
					cout << "Введите пароль:  "<<endl;
					int a = 0;
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
				    send(s, b, sizeof(b), 0);
					send(s, buf, sizeof(buf), 0);
					f[0] = '\0';
					recv(s, f, sizeof(f), 0);
					system("cls");
					if (strcmp(f, "b") != 0) cout << "Логин или пароль были введены неверно. Повторите попытку:" << endl;
				}
			}
			else {
				//задание логина
				int a = 0;
				cout << "Придумайте логин:  ";
				while (a != 2) {
					buf[0] = '\0';
					cin.getline(buf, 50, '\n');
					a = CheckLogin(buf);
					if (a == 1) { cout << "Были использованы недопустимые символы. Повторите попытку:" << endl; }
				}
				send(s, buf, sizeof(buf), 0);
				//задание пароля
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
					a = CheckPassword(buf);
					if (a == 1) { cout << "Были использованы недопустимые символы. Повторите попытку:" << endl; }
				}
				send(s, buf, sizeof(buf), 0);
				system("cls");
			}
			t1 = 0;
			while (t1 != 4) {
				k[0] = '\0';
				b[0] = '\0';
				recv(s, k, sizeof(k), 0);
				cout << k << endl;
				t1=CheckChoice(1,4);
				_itoa_s(t1, b, 10);
				send(s, b, sizeof(b), 0);
				recv(s, k, sizeof(k), 0);
				//system("cls");
				t1 = atoi(k);
				switch (t1) {
				case 1: {
					while (t2 != 5) {
						recv(s, k, sizeof(k), 0);
						cout << k << endl;
						t2 = CheckChoice(1, 5);

						//system("cls");
						_itoa_s(t2, b, 10);
						send(s, b, sizeof(b), 0);
						k[0] = '\0';
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
								if(strcmp(b,k)!=0)
								cout << b << endl;
							}
							//cout << "вышел из цикла" << endl;
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
							b[0] = '\0';
							k[0] = '\0';
							strcpy_s(k, "g");
							
								cout << "Введите название организации, с которой Вы намерены заключить договор о поставках:" << endl;
								cin.getline(b, 50, '\n');
								send(s, b, sizeof(b), 0);
								b[0] = '\0';
								k[0] = '\0';
								recv(s, k, sizeof(k), 0);
								if (strcmp(k, "t") == 0) {
									cout<<"Такого поставщика нет в списке потенциальных" << endl;
									break;
							    }
								else {
									cout<< "Заявка была отправлена!" << endl;
								}
							
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
					while (t2 != 5) {
						recv(s, k, sizeof(k), 0);
						cout << k << endl;
						t2=CheckChoice(1,5);
						system("cls");
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
								system("cls");
								_itoa_s(t3, b, 10);
								send(s, b, sizeof(b), 0);
								recv(s, k, sizeof(k), 0);
								t3 = atoi(k);
								switch (t3) {
								case 1: {
									k[0] = '\0';
									recv(s, k, sizeof(k), 0);
									if (strcmp(k, "m") == 0) { cout<<"Вы ещё не назначили экспертов." << endl; }
									else {
										b[0] = '\0';
										k[0] = '\0';
										strcpy_s(k, "конец");
										strcpy_s(b, "f");
										while (strcmp(b, k) != 0) {
											b[0] = '\0';
											recv(s, b, sizeof(b), 0);
											if (strcmp(b, "конец") != 0)
												cout << b << endl;
										}
										cout << endl;
										k[0] = '\0';
									}
									break;
								}
								case 2: {
									recv(s, k, sizeof(k), 0);
									if (strcmp(k, "m") == 0) { cout << "Вы ещё не назначили экспертов." << endl; }
									else {
										b[0] = '\0';
										cout << "Введите нижнюю границу стажа эксперта:" << endl;
										cin.getline(b, 50, '\n');
										send(s, b, sizeof(b), 0);
										k[0] = '\0';
										f[0] = '\0';
										system("cls");
										strcpy_s(f, "Экспертов с таким стажем нет!\n");
										strcpy_s(k, "конец");
										while ((strcmp(b, k) != 0) && (strcmp(b, f) != 0)) {
											b[0] = '\0';
											recv(s, b, sizeof(b), 0);
											if (strcmp(b, "конец") != 0)
												cout << b << endl;
										}
										cout << endl;
									}
									break;
								}
								case 3: {
									break;
								}
								/*case 4: {
									break;
								}
								case 5: {
									break;
								}*/
								}
							}
							t3 = 0;
							break;
							break;
						}
						case 2: {
							int a = 0;
							//вводим фамилию эксперта
							cout << "Введите фамилию эксперта:  ";
							while (a != 2) {
								buf[0] = '\0';
								cin.getline(buf, 50, '\n');
								a = CheckLetters(buf);
								if (a == 1) { cout << "В данном поле могут быть использованы только буквы кириллицы!" << endl; }
							}
							send(s, buf, sizeof(buf), 0);
							system("cls");
							a = 0;
							//вводим имя эксперта
							cout << "Введите имя эксперта:  ";
							while (a != 2) {
								buf[0] = '\0';
								cin.getline(buf, 50, '\n');
								a = CheckLetters(buf);
								if (a == 1) { cout << "В данном поле могут быть использованы только буквы кириллицы!" << endl; }
							}
							send(s, buf, sizeof(buf), 0);
							system("cls");
							a = 0;
							//вводим отчество эксперта
							cout << "Введите отчество эксперта:  ";
							while (a != 2) {
								buf[0] = '\0';
								cin.getline(buf, 50, '\n');
								a = CheckLetters(buf);
								if (a == 1) { cout << "В данном поле могут быть использованы только буквы кириллицы!" << endl; }
							}
							send(s, buf, sizeof(buf), 0);
							system("cls");
							a = 0;
							//вводим должность эксперта
							cout << "Введите должность эксперта:  ";
							buf[0] = '\0';
							cin.getline(buf, 50, '\n');
							send(s, buf, sizeof(buf), 0);
							system("cls");
							//вводим стаж работы
							cout << "Введите стаж работы:  ";
							a = CheckChoice(1, 55);
							_itoa_s(a, buf, 10);
							send(s, buf, sizeof(buf), 0);
							system("cls");
							a = 0;
							buf[0] = '\0';
							//задаём логин эксперта
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
								if (ch != -1) { 
									system("cls");
									cout << "Этот логин занят. Попробуйте другое сочетание символов:" << endl; }
							}
							system("cls");
							//задаём пароль эксперта
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
							system("cls");
							cout<<"Новый эксперт успешно назначен!" << endl<<endl;
							a = 0;
							break;
						}
						case 3: {
							k[0] = '\0';
							recv(s, k, sizeof(k), 0);
							if (strcmp(k, "m") == 0) { cout << "Вы ещё не назначили экспертов." << endl; }
							else {
								int q = 0;
								cout << "Введите фамилию эксперта, которого необходимо удалить." << endl;
								cin.getline(k, 50, '\n');
								send(s, k, sizeof(k), 0);
								system("cls");
								k[0] = '\0';
								recv(s, k, sizeof(k), 0);
								cout << k << endl;
							}
							break;
						}
						case 4: {
							b[0] = '\0';
							f[0] = '\0';
							k[0] = '\0';
							int u = 0;
							recv(s, k, sizeof(k), 0);
							if (strcmp(k, "m") == 0) { cout << "Вы ещё не назначили экспертов." << endl; }
							else {
							cout << "Введите фамилию сотрудника, данные о котором необходимо отредактировать:" << endl;
							cin.getline(b, 50, '\n');
							send(s, b, sizeof(b), 0);
							b[0] = '\0';
							recv(s, b, sizeof(b), 0);
							if (strcmp(b, "k") == 0) { cout << "Эксперт с такой фамилией не был добавлен!\n" << endl; }
							else {
								u = 0;
								while (u!=6) {

									cout << "1. Отредактировать фамилию.\n2. Отредактировать имя.\n3. Отредактировать отчество.\n4. Отредактировать должность.\n5. Отредактировать стаж.\n6. Вернуться." << endl;
									int u = CheckChoice(1, 6);
									_itoa_s(u, f, 10);
									send(s, f, sizeof(f), 0);
									b[0] = '\0';
									recv(s, b, sizeof(b), 0);
									u = atoi(b);
									switch (u) {
									case 1: {
										int a = 0;
										//вводим фамилию эксперта
										cout << "Введите фамилию эксперта:  ";
										while (a != 2) {
											buf[0] = '\0';
											cin.getline(buf, 50, '\n');
											a = CheckLetters(buf);
											if (a == 1) { cout << "В данном поле могут быть использованы только буквы кириллицы!" << endl; }
										}
										send(s, buf, sizeof(buf), 0);
										break;
									}
									case 2: {
										int a = 0;
										//вводим имя эксперта
										cout << "Введите имя эксперта:  ";
										while (a != 2) {
											buf[0] = '\0';
											cin.getline(buf, 50, '\n');
											a = CheckLetters(buf);
											if (a == 1) { cout << "В данном поле могут быть использованы только буквы кириллицы!" << endl; }
										}
										send(s, buf, sizeof(buf), 0);
										break;
									}
									case 3: {
										int a = 0;
										//вводим отчество эксперта
										cout << "Введите отчество эксперта:  ";
										while (a != 2) {
											buf[0] = '\0';
											cin.getline(buf, 50, '\n');
											a = CheckLetters(buf);
											if (a == 1) { cout << "В данном поле могут быть использованы только буквы кириллицы!" << endl; }
										}
										send(s, buf, sizeof(buf), 0);
										break;
									}
									case 4: {
										int a = 0;
										//вводим должность эксперта
										cout << "Введите должность эксперта:  ";
										buf[0] = '\0';
										cin.getline(buf, 50, '\n');
										send(s, buf, sizeof(buf), 0);
										break;
									}
									case 5: {
										int a = 0;
										//вводим стаж работы
										cout << "Введите стаж работы:  ";
										a = CheckChoice(1, 55);
										_itoa_s(a, buf, 10);
										send(s, buf, sizeof(buf), 0);
										break;
									}
									case 6: {
										break;
									}
									}
									if (u == 6) {
										break;
									}

								}
							}
							}
						
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
						system("cls");
						_itoa_s(t2, b, 10);
						send(s, b, sizeof(b), 0);
						recv(s, k, sizeof(k), 0);
						t2 = atoi(k);
						switch (t2) {
						case 1: { //изменение логина
							cout<<"Введите новый логин:"<< endl;
							int a = 0;
							while (a != 2) {
								buf[0] = '\0';
								cin.getline(buf, 50, '\n');
								a = CheckLogin(buf);
								if (a == 1) { cout << "Были использованы недопустимые символы. Повторите попытку:" << endl; }
							}
							send(s, buf, sizeof(buf), 0);
							system("cls");
							cout<< "Логин успешно изменён!" << endl<<endl;
							break;
						}
						case 2: { //изменение пароля
							cout << "Введите новый пароль:" << endl;
							int j = 0;
							int a = 0;
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
								a = CheckPassword(buf);
								if (a == 1) { cout << "Были использованы недопустимые символы. Повторите попытку:" << endl; }
							}
							send(s, buf, sizeof(buf), 0);
							system("cls");
							cout << "Пароль успешно изменён!" << endl << endl;
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
					a = CheckChoice(1, 10000);
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
					char log[500];
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
					strcpy_s(log, b);
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
							cout<< "1. Отредактировать название.\n2. Отредактировать страну локации представителя.\n3. Отредактировать город локации представителя.\n4. Отредактировать фамилию представителя.\n5. Отредактировать имя представителя.\n6. Отредактировать отчество представителя.\n7. Отредактировать номер телефона.\n8. Отредактировать email.\n9. Отредактировать количество действующих контрактов.\n10. Отредактировать минимальную сумму разовой закупки.\n11. Вернуться." << endl;
							int qw = CheckChoice(1, 11);
							f[0] = '\0';
							b[0] = '\0';
							_itoa_s(qw, f, 10);
							send(s, log, sizeof(log), 0);
							send(s, f, sizeof(f), 0);
							cout<<"вот из гоинг он "<<qw << endl;
							recv(s, b, sizeof(b), 0);
							qw = atoi(b);
							switch (qw) {
							case 1: {
								cout << "Введите название вашей организации:  ";
								cin.getline(buf, 50, '\n');
								send(s, buf, sizeof(buf), 0);
								buf[0] = '\0';
								break;
							}
							case 2: {
								int a = 0;
								cout << "Введите страну локации поставщика:  ";
								while (a != 2) {
									buf[0] = '\0';
									cin.getline(buf, 50, '\n');
									a = CheckPlace(buf);
									if (a == 1) { cout << "Здесь могут быть только буквы кириллицы, дефис и пробел! Пожалуйста, попробуйте снова:" << endl; }
								}
								send(s, buf, sizeof(buf), 0);
								buf[0] = '\0';
								break;
							}
							case 3: {
								int a = 0;
								cout << "Введите город локации поставщика:  ";
								while (a != 2) {
									buf[0] = '\0';
									cin.getline(buf, 50, '\n');
									a = CheckPlace(buf);
									if (a == 1) { cout << "Здесь могут быть только буквы кириллицы, дефис и пробел! Пожалуйста, попробуйте снова:" << endl; }
								}
								send(s, buf, sizeof(buf), 0);
								buf[0] = '\0';
								break;
							}
							case 4: {
								int a = 0;
								cout << "Введите фамилию представителя:  ";
								while (a != 2) {
									buf[0] = '\0';
									cin.getline(buf, 50, '\n');
									a = CheckLetters(buf);
									if (a == 1) { cout << "В данном поле могут быть использованы только буквы кириллицы!" << endl; }
								}
								send(s, buf, sizeof(buf), 0);
								buf[0] = '\0';
								break;
							}
							case 5: {
								int a = 0;
								cout << "Введите имя представителя:  ";
								while (a != 2) {
									buf[0] = '\0';
									cin.getline(buf, 50, '\n');
									a = CheckLetters(buf);
									if (a == 1) { cout << "В данном поле могут быть использованы только буквы кириллицы!" << endl; }
								}
								send(s, buf, sizeof(buf), 0);
								buf[0] = '\0';
								break;
							}
							case 6: {
								int a = 0;
								cout << "Введите отчество представителя:  ";
								while (a != 2) {
									buf[0] = '\0';
									cin.getline(buf, 50, '\n');
									a = CheckLetters(buf);
									if (a == 1) { cout << "В данном поле могут быть использованы только буквы кириллицы!" << endl; }
								}
								send(s, buf, sizeof(buf), 0);
								buf[0] = '\0';
								break;
							}
							case 7: {
								int a = 0;
								cout << "Введите номер телефона:  ";
								while (a != 2) {
									buf[0] = '\0';
									cin.getline(buf, 50, '\n');
									a = CheckPhone(buf);
									if (a == 1) { cout << "Кажется, номер телефона введён некорректно... Пожалуйста, попробуйте снова:" << endl; }
								}
								send(s, buf, sizeof(buf), 0);
								buf[0] = '\0';
								break;
							}
							case 8: {
								int a = 0;
								cout << "Введите электронную почту:  ";
								while (a != 2) {
									buf[0] = '\0';
									cin.getline(buf, 50, '\n');
									a = CheckEmail(buf);
									if (a == 1) { cout << "Кажется, адрес электронной почты введён некорректно...\nПожалуйста, попробуйте снова:" << endl; }
								}
								send(s, buf, sizeof(buf), 0);
								buf[0] = '\0';
								break;
							}
							case 9: {
								int a = 0;
								cout << "Введите количество действующих контрактов:  ";
								a = CheckChoice(1, 100000);
								_itoa_s(a, buf, 10);
								send(s, buf, sizeof(buf), 0);
								a = 0;
								buf[0] = '\0';
								break;
							}
							case 10: {
								int c = 0;
								cout << "Введите минимальную сумму разовой закупки:  ";
								c = CheckChoiceF(1, 1000000000);
								sprintf_s(buf, "%.2f", c);
								send(s, buf, sizeof(buf), 0);
								buf[0] = '\0';
								break;
							}
							case 11: {
								break;
							}
							}
							break;
						}
						case 2: {
							k[0] = '\0';
							int q = 0;
							cout<< "Вы действительно хотите удалить свой аккаунт? Данные невозможно будет восстановить." << endl;
							cout << "1. Да, я дейсвительно хочу свой аккаунт.\n2. Отменить и вернуться назад." << endl;
							q = CheckChoice(1, 2);
							_itoa_s(q, k, 10);
							send(s, k, sizeof(k), 0);
							if (q == 1) {
								cout << log << endl;
								send(s, log, sizeof(log), 0);
								k[0] = '\0';
								recv(s, k, sizeof(k), 0);
								cout << k << endl;
							}
							
							break;
						}
						case 3: {
							k[0] = '\0';
							send(s, log, sizeof(log), 0); //отправили логин свой
							recv(s, k, sizeof(k), 0);
							if (strcmp(k, "1") == 0) {
								cout<<"Договор успешно заключён!!!" << endl;
							}
							else {
								cout<< "У вас нет заявок на заключение договора о поставках!" << endl;
							}
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
					int a, b;
					k[0] = '\0';
					recv(s, k, sizeof(k), 0);
					a = atoi(k); //suppliers
					k[0] = '\0';
					recv(s, k, sizeof(k), 0);
					b = atoi(k); //experts
					int arr[50][50];
					int flag,buff;
					for (int i = 0; i < b; i++) {
						cout << "Оценивает эксперт №" << i + 1 << endl;
						for (int j = 0; j < a; j++) {
							cout << "Оценка поставщика №" << j + 1 << endl;
							flag = 1;
							while (flag != 0) {
								buff = CheckChoice(1, 10);
								flag = 0;
								for (int k = 0; k < j; k++) {
									if (arr[i][k] == buff) flag++;
								}
								if (flag != 0) {
									cout << "Вы поставили такую оценку другому поставщику. Их нельзя повторять!" << endl;
								}
								else {
									arr[i][j] = buff;
									k[0] = '\0';
									_itoa_s(arr[i][j], k, 10);
									send(s, k, sizeof(k), 0);
								}

							}
						}
					}
					for (int i = 0; i < b; i++) {
						for (int j = 0; j < a; j++) {
							cout << arr[i][j] << "  ";
						}
						cout << endl;
					}
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