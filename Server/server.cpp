#define _AFXDLL  //содержат MFC в DLL
#include <iostream>
#include <afx.h>  //для ускорения компиляции проектов
#include <winsock2.h>
#include <process.h> /* _beginthread, _endthread */  //содержит объявления функций и макросы, используемые при работе с потоками и процессами
#include <string>
#include <fstream>
#include <list>
#include<iomanip>

using namespace std;
CFile f;  //Базовый класс для файловых классов Microsoft Foundation Class. Создает CFileобъект из пути или дескриптора файла
CFileException ex;

class Contract {
	char client[50];     //заказчик
	char supplier[50];   //поставщик
	char contr_num[50];  //номер договора
	int status;          //статус договора
public:
	Contract() {
		strcpy_s(client, "АвтоМир");
		strcpy_s(supplier, "-");
		strcpy_s(contr_num, "-");
		status = 0;
	}
	//void SetClient(char* str) { strcpy_s(client, str); }
	void SetSupplier(char* str) { strcpy_s(supplier, str); }
	void SetContrNum(char* str) { strcpy_s(contr_num, str); }
	void SetStatus(int a) { status = a; }
}; //информация и методы, связанные с контрактами для обеих сторон,
//этот класс будет включен в виде списка в класс админ/салон и класс поставщик

class Authorization {
protected:
	char login[50];
	char password[50];
public:
	Authorization() {
		strcpy_s(login, "-");
		strcpy_s(password, "-");
	}
	/*Authorization(const Authorization& obj) {
		strcpy_s(this->login,obj.login);
		strcpy_s(this->password, obj.password);
	}*/
	void SetLogin(char* str) { strcpy_s(login, str); }
	void SetPassword(char* str) { strcpy_s(password, str); }
	char* GetLogin() { return login; }
	char* GetPassword() { return password; }
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
	CarShowroom() {
		strcpy_s(name, "-");
		strcpy_s(F, "-");
		strcpy_s(I, "-");
		strcpy_s(O, "-");
	}
	/*CarShowroom(const CarShowroom& obj) {
		strcpy_s(this->name, obj.name);
		strcpy_s(this->F, obj.F);
		strcpy_s(this->I, obj.I);
		strcpy_s(this->O, obj.O);
	}*/
	void SetF(char* str) { strcpy_s(F, str); } //ввести фамилию
	void SetI(char* str) { strcpy_s(I, str); } //ввести имя
	void SetO(char* str) { strcpy_s(O, str); }; //ввести отчество
	char* GetF() { return F; }
	char* GetI() { return I; }
	char* GetO() { return O; }
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
	char nameorg[50]; //название организации
	char country[50]; //название страны локации поставщика
	char city[50]; //название города локации поставщика
	char phone[50]; //контактный телефон
	char email[50]; //электронная почта
	int contracts; //количество действующих договоров
	//список договоров
	//список заявок
	float min_price; //цена минимальной разовой закупки
	Contract c;      //договор с нашим автосалоном
public:
	Supplier() {
		strcpy_s(nameorg, "-");
		strcpy_s(country, "-");
		strcpy_s(city, "-");
		strcpy_s(phone, "-");
		strcpy_s(email, "-");
		contracts = 0;
		min_price = 0;
	}
	/*Supplier(const Supplier& obj) {
		strcpy_s(this->nameorg, obj.nameorg);
		strcpy_s(this->country, obj.country);
		strcpy_s(this->city, obj.city);
		strcpy_s(this->F, obj.F);
		strcpy_s(this->I, obj.I);
		strcpy_s(this->O, obj.O);
		strcpy_s(this->phone, obj.phone);
		strcpy_s(this->email, obj.email);
		this->contracts = obj.contracts;
		this->min_price = obj.min_price;
	}*/
	friend bool operator<(Supplier s1, Supplier s2);
	friend void MakeSuppList(list<Supplier>& lst);
	Supplier operator()(const int index,list<Supplier> lst) {
		int counter = 0;
		list<Supplier>::iterator p=lst.begin();
		while (p != lst.end()) {
			if (counter == index) {
				return *p;
			}
			p++;
			counter++;
		}
	}
	void Set_nameorg(char* str) { strcpy_s(nameorg, str); }
	void Set_country(char* str) { strcpy_s(country,str); }
	void Set_city(char* str) { strcpy_s(city, str); }
	void Set_phone(char* str) { strcpy_s(phone, str); }
	void Set_email(char* str){ strcpy_s(email, str); }
	void Set_contracts(int a) { contracts = a; }
	void Set_min_price(float a) { min_price = a; }
	char* Get_nameorg() { return nameorg; }
	char* Get_country() { return country; }
	char* Get_city() { return city; }
	char* Get_phone() { return phone; }
	char* Get_email() { return email; }
	int Get_contracts() { return contracts; }
	float Get_min_price() { return min_price; }
	void WriteFile(list<Supplier> lst);
	void WriteTable(list <Supplier> lst);
	void Sorting(list<Supplier> lst);
	int Filtr_1(list<Supplier>lst, char* str);
};

void Supplier::WriteFile(list<Supplier> lst)
{
	list<Supplier>::iterator p;
	ofstream file("Suppliers.txt", ios_base::trunc);
	for (p=lst.begin(); p!=lst.end(); p++) {
		file << p->nameorg << ";" << p->country << ";" <<p->city << ";" << p->F << ";" << p->I << ";" <<p->O<<";" <<p->phone <<";" << p->email << ";" << p->contracts << ";" << p->min_price << "\n";
	}
	file << "*;";
	file.close();
	ofstream f("Supp_log_passw.txt", ios_base::trunc);
	for (p = lst.begin(); p != lst.end(); p++) {
		for (int i = 0; i < strlen(p->login); i++) {
			p->login[i] = (char)((int)p->login[i] + 3);
		}
		for (int i = 0; i < strlen(p->password); i++) {
			p->password[i] = (char)((int)p->password[i] + 3);
		}
		f << p->login << " " << p->password<< "\n";
	}
	f.close();
}

void Supplier::WriteTable(list<Supplier> lst)
{
	list<Supplier>::iterator p;
	ofstream file("Supp_table.txt", ios_base::trunc);
	file << setw(107) << setfill('-') <<"" << endl;
	file <<setfill(' ') << "|" << setw(15) << "Поставщик" <<setw(8)<< "|" <<setw(15)<<"Страна" << setw(8) << "|" << setw(15)<<"Город" << setw(9) << "|" << setw(15)<<"Количество" << setw(4) << "|" << setw(10)<<"min" << setw(7) << "|" << endl;
	file << setfill(' ') << "|" << setw(23) << "|" << setw(23) << "|" << setw(24) << "|" << setw(14) << "договоров" << setw(5) << "|" << setw(11) << "сумма" << setw(6) << "|" << endl;
	file << setw(107) << setfill('-') << "" << endl;
	for (p = lst.begin(); p != lst.end(); p++) {
		file << setfill(' ') << "|" << left << setw(22) << p->Get_nameorg() << right << "|" << left << setw(22) << p->Get_country() << right << "|" << left << setw(23) << p->Get_city() << right << "|" << left << setw(18) << p->Get_contracts() << right << "|" << left << setw(16) << p->Get_min_price() << right << "|" << endl;
		file << setw(107) << setfill('-') << "" << endl;
	}
	file.close();
}

void Supplier::Sorting(list<Supplier> lst)
{
	lst.sort();
	list<Supplier>::iterator p;
	ofstream file("Supp_table_sort.txt", ios_base::trunc);
	file << setw(107) << setfill('-') << "" << endl;
	file << setfill(' ') << "|" << setw(15) << "Поставщик" << setw(8) << "|" << setw(15) << "Страна" << setw(8) << "|" << setw(15) << "Город" << setw(9) << "|" << setw(15) << "Количество" << setw(4) << "|" << setw(10) << "min" << setw(7) << "|" << endl;
	file << setfill(' ') << "|" << setw(23) << "|" << setw(23) << "|" << setw(24) << "|" << setw(14) << "договоров" << setw(5) << "|" << setw(11) << "сумма" << setw(6) << "|" << endl;
	file << setw(107) << setfill('-') << "" << endl;
	for (p = lst.begin(); p != lst.end(); p++) {
		file << setfill(' ') << "|" << left << setw(22) << p->Get_nameorg() << right << "|" << left << setw(22) << p->Get_country() << right << "|" << left << setw(23) << p->Get_city() << right << "|" << left << setw(18) << p->Get_contracts() << right << "|" << left << setw(16) << p->Get_min_price() << right << "|" << endl;
		file << setw(107) << setfill('-') << "" << endl;
	}
	file.close();
}

int Supplier::Filtr_1(list<Supplier> lst, char* str)
{
	lst.sort();
	int i = 0;
	list<Supplier>::iterator p;
	ofstream file("Supp_table_f1.txt", ios_base::trunc);
	file << setw(107) << setfill('-') << "" << endl;
	file << setfill(' ') << "|" << setw(15) << "Поставщик" << setw(8) << "|" << setw(15) << "Страна" << setw(8) << "|" << setw(15) << "Город" << setw(9) << "|" << setw(15) << "Количество" << setw(4) << "|" << setw(10) << "min" << setw(7) << "|" << endl;
	file << setfill(' ') << "|" << setw(23) << "|" << setw(23) << "|" << setw(24) << "|" << setw(14) << "договоров" << setw(5) << "|" << setw(11) << "сумма" << setw(6) << "|" << endl;
	file << setw(107) << setfill('-') << "" << endl;
	for (p = lst.begin(); p != lst.end(); p++) {
		if (strcmp(str, p->country) == 0) {
			file << setfill(' ') << "|" << left << setw(22) << p->Get_nameorg() << right << "|" << left << setw(22) << p->Get_country() << right << "|" << left << setw(23) << p->Get_city() << right << "|" << left << setw(18) << p->Get_contracts() << right << "|" << left << setw(16) << p->Get_min_price() << right << "|" << endl;
			file << setw(107) << setfill('-') << "" << endl;
			i++;
		}	
	}
	file.close();
	return i;
}

bool operator<(Supplier s1, Supplier s2) {
	return strcmp(s1.nameorg, s2.nameorg) < 0;
}

class Request{}; //инфа и методы о заявках для обеих сторон

class Method{}; //поля и методы, связанные с методом ранга, включён в класс эксперты

void MakeSuppList(list<Supplier>& lst) {
	ifstream file("Suppliers.txt");
	ifstream f("Supp_log_passw.txt");
	char str[50];
	Supplier sup;
	if (!file.is_open()||file.peek()==EOF) { //проверяем, связан ли наш поток с открываемым файлом
	cout << "Возникла проблема при открытии файла или файл пустой\n" << endl;
}
else {
		cout << "File is open ok" << endl;
	for (int i = 0;; i++) 
	{
		file.getline(sup.nameorg, 50, ';');
		if (strcmp(sup.nameorg, "*") == 0) { break; }
		file.getline(sup.country, 50, ';');
		file.getline(sup.city, 50, ';');
		file.getline(sup.F, 50, ';');
		file.getline(sup.I, 50, ';');
		file.getline(sup.O, 50, ';');
		file.getline(sup.phone, 50, ';');
		file.getline(sup.email, 50, ';');
		str[0] = '\0';
		file.getline(str, 50, ';');
		sup.Set_contracts(atoi(str));
		str[0] = '\0';
		file.getline(str, 50, '\n');
		sup.Set_min_price(stof(str));
		str[0] = '\0';
		f.getline(str, 50, ' ');
		for (int i = 0; i < strlen(str); i++) {
			str[i] = (char)((int)str[i] - 3);
		}
		strcpy_s(sup.login, str);
		str[0] = '\0';
		f.getline(str, 50, '\n');
		for (int i = 0; i < strlen(str); i++) {
			str[i] = (char)((int)str[i] - 3);
		}
		strcpy_s(sup.password, str);
		str[0] = '\0';
		lst.push_back(sup);
	}
}
file.close();
f.close();
}

void mailWorking(void* newS) {
	Supplier supp; 
	list<Supplier> lsupp;
	list<Supplier> ::iterator psupp;
	int c, c1 = 0, c2 = 0, c3 = 0;
	int flag = 0;
	char p[500], com[500], k[500], m[500];
	com[0] = '\0'; p[0] = '\0'; k[0] = '\0'; m[0] = '\0';
	cout << "Сервер работает.\n";
	/*cout <<  "size = " << lsupp.size() << endl;*/
	MakeSuppList(lsupp);
	//cout << lsupp.size() << endl;
	//cout << "фУНКЦИЯ ЗАВЕРШЕНА МЭЙКСАПЛИСТ" << endl;
	/*for (psupp = lsupp.begin(); psupp != lsupp.end(); psupp++) {
		cout << psupp->GetPassword() << endl;
	}*/
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
							supp.WriteTable(lsupp);
							/*cout<<supp(3, lsupp).GetF()<<endl;
							cout << "fff" << endl;*/
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
			while (c1 != 3) {
				strcpy_s(k, "МЕНЮ ПОСТАВЩИКА:\n 1. Зарегистрироваться.\n 2. Войти.\n 3. Вернуться в главное меню.");
				send((SOCKET)newS, k, sizeof(k), 0);
				recv((SOCKET)newS, m, sizeof(m), 0);
				c1 = atoi(m);
				switch (c1) {
				case 1: {
					strcpy_s(p, "1");
					send((SOCKET)newS, p, sizeof(p), 0);

					//получение названия организации
					recv((SOCKET)newS, com, sizeof(com), 0);
					supp.Set_nameorg(com);
					com[0] = '\0';

					//получение страны
					recv((SOCKET)newS, com, sizeof(com), 0);
					supp.Set_country(com);
					com[0] = '\0';

					//получение города
					recv((SOCKET)newS, com, sizeof(com), 0);
					supp.Set_city(com);
					com[0] = '\0';

					//получение фамилии
					recv((SOCKET)newS, com, sizeof(com), 0);
					supp.SetF(com);
					com[0] = '\0';

					//получение имя
					recv((SOCKET)newS, com, sizeof(com), 0);
					supp.SetI(com);
					com[0] = '\0';

					//получение отчества
					recv((SOCKET)newS, com, sizeof(com), 0);
					supp.SetO(com);
					com[0] = '\0';

					//получение номера телефона
					recv((SOCKET)newS, com, sizeof(com), 0);
					supp.Set_phone(com);
					com[0] = '\0';

					//получение электронную почту
					recv((SOCKET)newS, com, sizeof(com), 0);
					supp.Set_email(com);
					com[0] = '\0';

					//получение количество действующих контрактов
					recv((SOCKET)newS, com, sizeof(com), 0);
					int d;
					d = atoi(com);
					supp.Set_contracts(d);
					com[0] = '\0';

					//получение минимальную стоимость
					recv((SOCKET)newS, com, sizeof(com), 0);
					float numb;
					numb = stof(com);
					supp.Set_min_price(numb);
					com[0] = '\0';

					////получение информации о договорах
					//int ss,fll=0;
					//recv((SOCKET)newS, com, sizeof(com), 0);
					//ss = atoi(com);
					//if (ss == 2) {
					//	while (fll != 1) {
					//		com[0] = '\0';
					//		recv((SOCKET)newS, com, sizeof(com), 0);
					//		supp.Set
					//	}
					//}
					//com[0] = '\0';
					//получение логина
					int ch = 0;
					while (ch != -1) {
						ch = 0;
						recv((SOCKET)newS, com, sizeof(com), 0);
						for (psupp = lsupp.begin(); psupp != lsupp.end(); psupp++) {
							if (strcmp(com, psupp->GetLogin()) == 0) {
								ch++;
							}
						}
						if (ch == 0) {
							ch = -1;
						}
							m[0] = '\0';
							_itoa_s(ch, m, 10);
							send((SOCKET)newS, m, sizeof(m), 0);
							m[0] = '\0';
							
					}
					supp.SetLogin(com);
					com[0] = '\0';

					//получение пароль
					recv((SOCKET)newS, com, sizeof(com), 0);
					supp.SetPassword(com);
					com[0] = '\0';

					lsupp.push_back(supp);
					/*for (psupp = lsupp.begin(); psupp != lsupp.end(); psupp++) {
						cout << psupp->Get_nameorg() << "\n" << psupp->Get_country() << "\n" << psupp->Get_city() << "\n" << psupp->GetF() << "\n" << psupp->GetI() << "\n" << psupp->GetO() << "\n" << psupp->Get_phone() << "\n" << psupp->Get_email() << "\n" << psupp->Get_contracts() << "\n" << psupp->Get_min_price() << endl;
						cout << psupp->GetLogin() << "\n" << psupp->GetPassword() << endl;
					}*/
					supp.WriteFile(lsupp);
					break;
				}
				case 2: {
					int post=0;
					strcpy_s(p, "2");
					send((SOCKET)newS, p, sizeof(p), 0);
					//авторизация
					k[0] = '\0';
					m[0] = '\0';
					p[0] = '\0';
					strcpy_s(p, "a");
					while (strcmp(p, "b") != 0) {
						int a = 0;
						recv((SOCKET)newS, k, sizeof(k), 0); //получили логин
						recv((SOCKET)newS, m, sizeof(m), 0); //получили пароль
						for (psupp = lsupp.begin(); psupp != lsupp.end(); psupp++) {
							if (strcmp(k, psupp->GetLogin()) == 0) {
								p[0] = '\0';
								cout << psupp->GetLogin() << endl;
								strcpy_s(p, "b");
								psupp = lsupp.end();
								psupp--;
								//continue;
							}
							 a++;
						}
						a--;
						cout << a << endl;
						//check password now
						k[0] = '\0';
						if (strcmp(m, supp(a, lsupp).GetPassword()) == 0) {
							strcpy_s(k, "b");
							cout << supp(a, lsupp).GetPassword() << endl;
						}
						if(strcmp(p,k)==0) send((SOCKET)newS, k, sizeof(k), 0);
						else {
							send((SOCKET)newS, "a", sizeof("a"), 0);
							strcpy_s(p, "a");
						}
						k[0] = '\0';
					}
					//авторизация
					p[0] = '\0';
					while (post != 5) {
						k[0] = '\0';
						m[0] = '\0';
						strcpy_s(k, "АККАУНТ ПОСТАВЩИКА:\n 1. Отредактировать информацию.\n 2. Удалить аккаунт.\n 3. Заключить договор.\n 4. Расторгнуть договор.\n 5. Вернуться.");
						send((SOCKET)newS, k, sizeof(k), 0);
						recv((SOCKET)newS, m, sizeof(m), 0);
						post = atoi(m);
						switch (post) {
						case 1: {
							p[0] = '\0';
							strcpy_s(p, "1");
							send((SOCKET)newS, p, sizeof(p), 0);
							break;
						}
						case 2: {
							p[0] = '\0';
							strcpy_s(p, "2");
							send((SOCKET)newS, p, sizeof(p), 0);
							break;
						}
						case 3: {
							p[0] = '\0';
							strcpy_s(p, "3");
							send((SOCKET)newS, p, sizeof(p), 0);
							break;
						}
						case 4: {
							p[0] = '\0';
							strcpy_s(p, "4");
							send((SOCKET)newS, p, sizeof(p), 0);
							break;
						}
						case 5: {
							p[0] = '\0';
							strcpy_s(p, "5");
							send((SOCKET)newS, p, sizeof(p), 0);
							break;
						}
						}
					}
					break;
				}
				case 3: {
					strcpy_s(p, "3");
					send((SOCKET)newS, p, sizeof(p), 0);
					break;
				}
				/*case 4: {
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
				}*/
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
						k[0] = '\0';
						m[0] = '\0';
						strcpy_s(k, "ИНФОРМАЦИЯ О ПОТЕНЦИАЛЬНЫХ ПОСТАВЩИКАХ:\n 1. В алфавитном порядке.\n 2. С фильтрацией по странам.\n 3. С фильтрацией по минимальной разовой цене закупки.\n 4. Поиск конкретного поставщика.\n 5. Вернуться в меню эксперта.\n ");
						send((SOCKET)newS, k, sizeof(k), 0);
						cout << k << endl;
						recv((SOCKET)newS, m, sizeof(m), 0);
						c2 = atoi(m);
						switch (c2) {
						case 1: {
							//p[0] = '\0';
							strcpy_s(p, "1");
							send((SOCKET)newS, p, sizeof(p), 0);
							supp.Sorting(lsupp);
							ifstream file("Supp_table_sort.txt"); 
							while (!file.eof()) {
								cout<<"Hi, babe" << endl;
								k[0] = '\0';
								file.getline(k, 256,'\n');
								m[0] = '\0';
								strcpy_s(m, "конец");
								if(file.eof()) 	send((SOCKET)newS, m, sizeof(m), 0);
								else send((SOCKET)newS, k, sizeof(k), 0);
								cout << k << endl;
							}
							k[0] = '\0';
							cout << "вышел из цикла" << endl;
							file.close();
							m[0] = '\0';
							//p[0] = '\0';
							break;
						}
						case 2: {
							strcpy_s(p, "2");
							send((SOCKET)newS, p, sizeof(p), 0);
							m[0] = '\0'; int tt;
							recv((SOCKET)newS, m, sizeof(m), 0);
							tt = supp.Filtr_1(lsupp, m);
							if (tt == 0) {
								m[0] = '\0';
								strcpy_s(m, "Поставщик из заданной страны не найден!\n");
								send((SOCKET)newS, m, sizeof(m), 0);
							}
							else {
								ifstream file("Supp_table_f1.txt");
								while (!file.eof()) {
									//cout << "Hi, babe" << endl;
									k[0] = '\0';
									file.getline(k, 256, '\n');
									m[0] = '\0';
									strcpy_s(m, "конец");
									if (file.eof()) 	send((SOCKET)newS, m, sizeof(m), 0);
									else send((SOCKET)newS, k, sizeof(k), 0);
									//cout << k << endl;
								}
								k[0] = '\0';
							}
							m[0] = '\0';
							k[0] = '\0';
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


