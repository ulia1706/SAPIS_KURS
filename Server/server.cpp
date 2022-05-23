#define _AFXDLL 
#include <iostream>
#include <cstring>
#include <afx.h> 
#include <winsock2.h>
#include <process.h>
#include <string>
#include <fstream>
#include <list>
#include <iomanip>
#include <time.h>

using namespace std;

CFile f;
CFileException ex;

class Contract {
	char client[50];     //заказчик
	char supplier[50];   //поставщик
	char contr_num[50];  //номер договора
	int status;          //статус договора
public:
	Contract() {    //конструктор по умолчанию
		strcpy_s(client, "АвтоМир");
		strcpy_s(supplier, "-");
		strcpy_s(contr_num, "-");
		status = 0;
	} 
	//сеттеры
	void SetSupplier(char* str) { strcpy_s(supplier, str); }
	void SetContrNum(char* str) { strcpy_s(contr_num, str); }
	void SetStatus(int a) { status = a; }
	//геттеры
	int GetStatus() { return status; }
	char* GetClient() { return client; }
	char* GetSupplier() { return supplier; }
	char* GetContrNum() { return contr_num; }
	//дружественные функции для работы по заключению и считыванию договоров
	friend void WriteContracts(list<Contract> lst);
	friend void ReadContract(list<Contract>& lst);
	friend void TableContracts(list<Contract> lst);
	friend int FindContract(list<Contract> lst, char* str);
}; 

class Authorization {
protected:
	char login[50]; 
	char password[50];
public:
	Authorization() {
		strcpy_s(login, "-");
		strcpy_s(password, "-");
	}
	//сеттеры
	void SetLogin(char* str) { strcpy_s(login, str); }
	void SetPassword(char* str) { strcpy_s(password, str); }
	//геттеры
	char* GetLogin() { return login; }
	char* GetPassword() { return password; }
};

class CarShowroom: public Authorization {
protected:
	char name[50]; //название автосалона
	char F[50];    //фамилия сотрудника автосалона
	char I[50];    //имя сотрудника
	char O[50];    //отчество
public:
	CarShowroom() {
		strcpy_s(name, "АвтоМир");
		strcpy_s(F, "Городная");
		strcpy_s(I, "Юлия");
		strcpy_s(O, "Сергеевна");
	}
	//сеттеры
	void SetF(char* str) { strcpy_s(F, str); } //ввести фамилию
	void SetI(char* str) { strcpy_s(I, str); } //ввести имя
	void SetO(char* str) { strcpy_s(O, str); }; //ввести отчество
	//геттеры
	char* GetF() { return F; }
	char* GetI() { return I; }
	char* GetO() { return O; }
};

class Expert : public CarShowroom {
	char pos[50]; //должность
	int exp;      //опыт
public:
	Expert() {
		strcpy_s(F, "-");
		strcpy_s(I, "-");
		strcpy_s(O, "-");
		strcpy_s(pos, "-");
		exp = 0;
	}
	friend bool operator<(Expert e1, Expert e2); //перегрузка, необходимая для работы со списками STL
	//геттеры и сеттеры
	void SetPos(char* str) { strcpy_s(pos, str); }
	char* GetPos() { return pos; }
	void SetExp(int a) { exp = a; }
	int GetExp() { return exp; }
	void WriteFile(list<Expert> lst); //запись в файл для последующего считывания
	void WriteTable(list<Expert> lst); //запись в файл для псоледующего просмотра/вывода на экран
	friend void MakeExpList(list<Expert> &lst);
	void Sorting(list<Expert> lst) {
		lst.sort();
		list<Expert>::iterator p;
		ofstream file("Experts_buf.txt", ios_base::trunc);
		file << setw(101) << setfill('-') << "" << endl;
		file << setfill(' ') << "|" << setw(13) << "ФИО" << setw(10) << "|" << setw(17) << "Стаж" << setw(7) << "|" << setw(29) << "Должность" << setw(24) << "|" << endl;
		file << setw(101) << setfill('-') << "" << endl;
		for (p = lst.begin(); p != lst.end(); p++) {
			file << setfill(' ') << "|" << left << setw(22) << p->GetF() << right << "|" << left << setw(23) << p->GetExp() << right << "|" << left << setw(52) << p->GetPos() << right << "|" << endl;
			file << setfill(' ') << "|" << left << setw(22) << p->GetI() << right << "|" << setw(24) << "|" << setw(53) << "|" << endl;
			file << setfill(' ') << "|" << left << setw(22) << p->GetO() << right << "|" << setw(24) << "|" << setw(53) << "|" << endl;
			file << setw(101) << setfill('-') << "" << endl;
		}
		file.close();
	}
	int Filtre(list<Expert> lst, int a) {
		int i = 0;
		list<Expert>::iterator p;
		ofstream file("Experts_buf.txt", ios_base::trunc);
		file << setw(101) << setfill('-') << "" << endl;
		file << setfill(' ') << "|" << setw(13) << "ФИО" << setw(10) << "|" << setw(17) << "Стаж" << setw(7) << "|" << setw(29) << "Должность" << setw(24) << "|" << endl;
		file << setw(101) << setfill('-') << "" << endl;
		for (p = lst.begin(); p != lst.end(); p++) {
			if (p->GetExp() >= a) {
				file << setfill(' ') << "|" << left << setw(22) << p->GetF() << right << "|" << left << setw(23) << p->GetExp() << right << "|" << left << setw(52) << p->GetPos() << right << "|" << endl;
				file << setfill(' ') << "|" << left << setw(22) << p->GetI() << right << "|" << setw(24) << "|" << setw(53) << "|" << endl;
				file << setfill(' ') << "|" << left << setw(22) << p->GetO() << right << "|" << setw(24) << "|" << setw(53) << "|" << endl;
				file << setw(101) << setfill('-') << "" << endl;
				i++;
			}
		}
		file.close();
		return i; 
	}
};

class Mistake : public std::exception //класс исключения
{
public:
	virtual const char* what() const throw()
	{
		return "Вызвано исключение преднамеренной проверки";
	}

} file_mistake;

void Expert::WriteFile(list<Expert> lst)
{
	list<Expert>::iterator p;
	ofstream file("Experts.txt", ios_base::trunc);
	for (p = lst.begin(); p != lst.end(); p++) {
		file << p->F << ";" << p->I << ";" << p->O << ";" << p->pos << ";" << p->exp  << "\n";
	}
	file << "*;";
	file.close();
	ofstream f("Exp_log_passw.txt", ios_base::trunc);
	for (p = lst.begin(); p != lst.end(); p++) {
		for (int i = 0; i < strlen(p->login); i++) {
			p->login[i] = (char)((int)p->login[i] + 3);
		}
		for (int i = 0; i < strlen(p->password); i++) {
			p->password[i] = (char)((int)p->password[i] + 3);
		}
		f << p->login << " " << p->password << "\n";
	}
	f.close();
}

void Expert::WriteTable(list<Expert> lst)
{
	list<Expert>::iterator p;
	ofstream file("Experts_table.txt", ios_base::trunc);
	file << setw(101) << setfill('-') << "" << endl;
	file << setfill(' ') << "|" << setw(13) << "ФИО" << setw(10) << "|" << setw(17) << "Стаж" << setw(7) << "|" << setw(29) << "Должность" << setw(24) << "|" << endl;
	file << setw(101) << setfill('-') << "" << endl;
	for (p = lst.begin(); p != lst.end(); p++) {
		file << setfill(' ') << "|" << left << setw(22) << p->GetF() << right << "|" << left << setw(23) << p->GetExp() << right << "|" << left << setw(52) << p->GetPos() << right << "|" << endl;
		file << setfill(' ') << "|" << left << setw(22) << p->GetI() << right << "|" << setw(24) << "|" << setw(53) << "|" << endl;
		file << setfill(' ') << "|" << left << setw(22) << p->GetO() << right << "|" << setw(24) << "|" << setw(53) << "|" << endl;
		file << setw(101) << setfill('-') << "" << endl;
	}
	file.close();
}

bool operator<(Expert e1, Expert e2) {
	return e1.exp>e2.exp;
}

class Supplier :public CarShowroom {
	char nameorg[50]; //название организации
	char country[50]; //название страны локации поставщика
	char city[50];    //название города локации поставщика
	char phone[50];   //контактный телефон
	char email[50];    //электронная почта
	int contracts;     //количество действующих договоров
	float min_price; //цена минимальной разовой закупки
public:
	Contract c;     //договор с нашим автосалоном
	Supplier() {
		strcpy_s(nameorg, "-");
		strcpy_s(country, "-");
		strcpy_s(city, "-");
		strcpy_s(phone, "-");
		strcpy_s(email, "-");
		contracts = 0;
		min_price = 0;
	}
	friend bool operator<(Supplier s1, Supplier s2);
	friend void MakeSuppList(list<Supplier>& lst);
	friend void MakePotSupp(list<Supplier>& lst, list<Supplier> lst1);
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
	//сеттеры
	void Set_nameorg(char* str) { strcpy_s(nameorg, str); }
	void Set_country(char* str) { strcpy_s(country,str); }
	void Set_city(char* str) { strcpy_s(city, str); }
	void Set_phone(char* str) { strcpy_s(phone, str); }
	void Set_email(char* str){ strcpy_s(email, str); }
	void Set_contracts(int a) { contracts = a; }
	void Set_min_price(float a) { min_price = a; }
	//геттеры
	char* Get_nameorg() { return nameorg; }
	char* Get_country() { return country; }
	char* Get_city() { return city; }
	char* Get_phone() { return phone; }
	char* Get_email() { return email; }
	int Get_contracts() { return contracts; }
	float Get_min_price() { return min_price; }
	//работа с файлами
	void WriteFile(list<Supplier> lst);
	void WriteTable(list <Supplier> lst);
	void WriteTableAdm(list<Supplier> lst);
	//сортировка
	void Sorting(list<Supplier> lst);
	//фильтрации
	int Filtr_1(list<Supplier>lst, char* str);
	int Filtr_2(list<Supplier> lst, float a, float b);
	//методы поиска
	int Find(list<Supplier> lst, char* str);
	int FindAdm(list<Supplier> lst, char* str);
};

void Supplier::WriteFile(list<Supplier> lst)
{
	list<Supplier>::iterator p;
	ofstream file("Suppliers.txt", ios_base::trunc);
	for (p=lst.begin(); p!=lst.end(); p++) {
		file << p->nameorg << ";" << p->country << ";" <<p->city << ";" << p->F << ";" << p->I << ";" <<p->O<<";" <<p->phone <<";" << p->email << ";" << p->contracts << ";" << p->min_price << ";" << p->c.GetStatus() << "\n";
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

void Supplier::WriteTableAdm(list<Supplier> lst)
{
	list<Supplier>::iterator p;
	ofstream file("Supp_table_adm.txt", ios_base::trunc);
	file << setw(101) << setfill('-') << "" << endl;
	file << setfill(' ') << "|" << setw(15) << "Поставщик" << setw(8) << "|" << setw(13) << "ФИО" << setw(10) << "|" << setw(17) << "Контактный" << setw(7) << "|" << setw(17) << "Email" << setw(13) << "|" <<  endl;
	file << setfill(' ') << "|" << setw(23) << "|" << setw(23) << "|" << setw(16) << "телефон" << setw(8) << "|" << setw(30) << "|" << endl;
	file << setw(101) << setfill('-') << "" << endl;
	for (p = lst.begin(); p != lst.end(); p++) {
		file << setfill(' ') << "|" << left << setw(22) << p->Get_nameorg() << right << "|" << left << setw(22) << p->GetF() << right << "|" << left << setw(23) << p->Get_phone() << right << "|" << left << setw(29) << p->Get_email() << right << "|"  << endl;
		file << setfill(' ') << "|"  << setw(23)  << "|" << left << setw(22) << p->GetI() << right << "|"  << setw(24)  << "|" <<  setw(30) <<  "|" << endl;
		file << setfill(' ') << "|" << setw(23) << "|" << left << setw(22) << p->GetO() << right << "|" << setw(24) << "|" << setw(30) << "|" << endl;
		file << setw(101) << setfill('-') << "" << endl;
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

int Supplier::Filtr_2(list<Supplier> lst, float a, float b)
{
	int i = 0;
	list<Supplier>::iterator p;
	ofstream file("Supp_table_f2.txt", ios_base::trunc);
	file << setw(107) << setfill('-') << "" << endl;
	file << setfill(' ') << "|" << setw(15) << "Поставщик" << setw(8) << "|" << setw(15) << "Страна" << setw(8) << "|" << setw(15) << "Город" << setw(9) << "|" << setw(15) << "Количество" << setw(4) << "|" << setw(10) << "min" << setw(7) << "|" << endl;
	file << setfill(' ') << "|" << setw(23) << "|" << setw(23) << "|" << setw(24) << "|" << setw(14) << "договоров" << setw(5) << "|" << setw(11) << "сумма" << setw(6) << "|" << endl;
	file << setw(107) << setfill('-') << "" << endl;
	for (p = lst.begin(); p != lst.end(); p++) {
		if ((p->min_price>=a)&&(p->min_price<=b)) {
			file << setfill(' ') << "|" << left << setw(22) << p->Get_nameorg() << right << "|" << left << setw(22) << p->Get_country() << right << "|" << left << setw(23) << p->Get_city() << right << "|" << left << setw(18) << p->Get_contracts() << right << "|" << left << setw(16) << p->Get_min_price() << right << "|" << endl;
			file << setw(107) << setfill('-') << "" << endl;
			i++;
		}
	}
	file.close();
	return i;
}

int Supplier::Find(list<Supplier> lst, char* str)
{
	int i = 0;
	list<Supplier>::iterator p;
	ofstream file("Supp_table_f.txt", ios_base::trunc);
	file << setw(107) << setfill('-') << "" << endl;
	file << setfill(' ') << "|" << setw(15) << "Поставщик" << setw(8) << "|" << setw(15) << "Страна" << setw(8) << "|" << setw(15) << "Город" << setw(9) << "|" << setw(15) << "Количество" << setw(4) << "|" << setw(10) << "min" << setw(7) << "|" << endl;
	file << setfill(' ') << "|" << setw(23) << "|" << setw(23) << "|" << setw(24) << "|" << setw(14) << "договоров" << setw(5) << "|" << setw(11) << "сумма" << setw(6) << "|" << endl;
	file << setw(107) << setfill('-') << "" << endl;
	for (p = lst.begin(); p != lst.end(); p++) {
		if (strcmp(str, p->nameorg) == 0) {
			file << setfill(' ') << "|" << left << setw(22) << p->Get_nameorg() << right << "|" << left << setw(22) << p->Get_country() << right << "|" << left << setw(23) << p->Get_city() << right << "|" << left << setw(18) << p->Get_contracts() << right << "|" << left << setw(16) << p->Get_min_price() << right << "|" << endl;
			file << setw(107) << setfill('-') << "" << endl;
			i++;
		}
	}
	file.close();
	return i;
}

int Supplier::FindAdm(list<Supplier> lst, char* str)
{
	int i = 0;
	list<Supplier>::iterator p;
	ofstream file("Supp_table_f.txt", ios_base::trunc);
	file << setw(101) << setfill('-') << "" << endl;
	file << setfill(' ') << "|" << setw(15) << "Поставщик" << setw(8) << "|" << setw(13) << "ФИО" << setw(10) << "|" << setw(17) << "Контактный" << setw(7) << "|" << setw(17) << "Email" << setw(13) << "|" << endl;
	file << setfill(' ') << "|" << setw(23) << "|" << setw(23) << "|" << setw(16) << "телефон" << setw(8) << "|" << setw(30) << "|" << endl;
	file << setw(101) << setfill('-') << "" << endl;
	for (p = lst.begin(); p != lst.end(); p++) {
		if (strcmp(str, p->nameorg) == 0) {
			file << setfill(' ') << "|" << left << setw(22) << p->Get_nameorg() << right << "|" << left << setw(22) << p->GetF() << right << "|" << left << setw(23) << p->Get_phone() << right << "|" << left << setw(29) << p->Get_email() << right << "|" << endl;
			file << setfill(' ') << "|" << setw(23) << "|" << left << setw(22) << p->GetI() << right << "|" << setw(24) << "|" << setw(30) << "|" << endl;
			file << setfill(' ') << "|" << setw(23) << "|" << left << setw(22) << p->GetO() << right << "|" << setw(24) << "|" << setw(30) << "|" << endl;
			file << setw(101) << setfill('-') << "" << endl;
			i++;
		}
	}
	file.close();
	return i;
}

bool operator<(Supplier s1, Supplier s2) {
	return strcmp(s1.nameorg, s2.nameorg) < 0;
}

void MakeExpList(list<Expert> &lst) {
	ifstream file("Experts.txt");
	ifstream file1("Exp_log_passw.txt");
	char str[50];
	Expert e;
	if (!file.is_open() || file.peek() == EOF) { 
		cout << "Файл с данными экспертов пуст или не может быть открыт!\n" << endl;
	}
	else {
		for (int i = 0;; i++) {
			file.getline(e.F, 50, ';');
			if (strcmp(e.F, "*") == 0) { break; }
			file.getline(e.I, 50, ';');
			file.getline(e.O, 50, ';');
			file.getline(e.pos, 50, ';');
			file.getline(str, 50, '\n');
			e.SetExp(atoi(str));
			file1.getline(str, 50, ' ');
			for (int i = 0; i < strlen(str); i++) {
				str[i] = (char)((int)str[i] - 3);
			}
			strcpy_s(e.login, str);
			str[0] = '\0';
			file1.getline(str, 50, '\n');
			for (int i = 0; i < strlen(str); i++) {
				str[i] = (char)((int)str[i] - 3);
			}
			strcpy_s(e.password, str);
			str[0] = '\0';
			lst.push_back(e);
		}
	}
	file.close();
	file1.close();
}

void MakeSuppList(list<Supplier>& lst) {
	ifstream file("Suppliers.txt");
	ifstream f("Supp_log_passw.txt");
	char str[50];
	Supplier sup;
	try
	{
		if (!file.is_open() || file.peek() == EOF)
			throw file_mistake;
	}
	catch (Mistake ex)
	{
		std::cerr << "Внимание, файл с данными о поставщиках не может быть открыт!" << std::endl;
		return;
	}
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
		file.getline(str, 50, ';');
		sup.Set_min_price(stof(str));
		str[0] = '\0';
		file.getline(str, 50, '\n');
		sup.c.SetStatus(atoi(str));
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

file.close();
f.close();
}

void MakePotSupp(list<Supplier>& lst,list<Supplier> lst1) {
	list<Supplier>::iterator p;
	for (p = lst1.begin(); p != lst1.end(); p++) {
		cout << "hi" << endl;
		cout << p->c.GetStatus() << endl;
		if (p->c.GetStatus() == 0) {
			cout << "hello" << endl;
			lst.push_back(*p);
		}
	}
}

template<typename T>
void MaxElement(const T* arr, int& maxel, T& maxvalue, int a) { // шаблонная функция для поиска максимального элемента в массиве
	for (int i = 0; i < a; i++) {
		if (arr[i] > maxvalue) {
			maxvalue = arr[i];
			maxel = i;
		}
	}
	cout << "Номер элемента с наибольшим весом: " << maxel << endl;
	cout << "Наибольший вес: " << maxvalue;
}

void Make1Table(int arr[50][50], int a, int b) { //a - поставщики; b- эксперты
	ofstream file("Method_Res.txt", ios_base::trunc);
	file << setw(15)<<" " << "Матрица оценок экспертов" << endl<<endl;
	//шапка таблицы
	file << "|" << setw(8) << setfill('-')<<"|";
	for (int i = 0; i < a; i++) {
		file << setw(5)<<"|";
	}
	file << endl;
	file << "|" << setw(6) << setfill(' ') << "Zi/Эi" << setw(2) << "|";
	for (int i = 0; i < a; i++) {
		file << " Z" << i + 1 << " |";
	}
	file << endl;
	file << "|" << setw(8) << setfill('-') << "|";
	for (int i = 0; i < a; i++) {
		file << setw(5) << "|";
	}
	file << endl;
    //
	for (int i = 0; i < b; i++) {
		file << "|" << setw(4) << setfill(' ') << "Э" << i + 1 << setw(3) << "|";
		for (int j = 0; j < a; j++) {
			file << setw(3) << arr[i][j] << setw(2) << "|";
		}
		file << endl;
		file << "|" << setw(8) << setfill('-') << "|";
		for (int i = 0; i < a; i++) {
			file << setw(5) << "|";
		}
		file << endl;
	}
	file << endl;
	file.close();
}

void Make2Table(int arr[50][50], int a, int b) {//a - supps; b- experts
	//шапка таблицы
	ofstream file("Method_Res.txt", ios_base::app);
	file << setw(15) <<" " << "Матрица нормированных оценок" << endl<<endl;
	file << "|" << setw(8) << setfill('-') << "|";
	for (int i = 0; i < a; i++) {
		file << setw(8) << "|";
	}
	file << endl;
	file << "|" << setw(6) << setfill(' ') << "Zi/Эi" << setw(2) << "|";
	for (int i = 0; i < a; i++) {
		file << "   Z" << i + 1 << "  |";
	}
	file << endl;
	file << "|" << setw(8) << setfill('-') << "|";
	for (int i = 0; i < a; i++) {
		file << setw(8) << "|";
	}
	file << endl;
	int total;
	for (int i = 0; i < b; i++) {
		total = 0;
		for (int m = 0; m < a; m++) {
			total = total + arr[i][m];
		}
		file << "|" << setw(4) << setfill(' ') << "Э" << i + 1 << setw(3) << "|";
		for (int j = 0; j < a; j++) {
			file << setw(3) << arr[i][j]<<"/"<<setw(2)<<total << setw(2) << "|";
		}
		file << endl;
		file << "|" << setw(8) << setfill('-') << "|";
		for (int i = 0; i < a; i++) {
			file << setw(8) << "|";
		}
		file << endl;
	}
	file << endl;
	file.close();
}

int Make3Table(int arr[50][50], int a, int b) {
	float array[50][50];
	float weight[100];
	int total;
	int maxel = 0;
	float maxvalue = 0;
	ofstream file("Method_Res.txt", ios_base::app);
	file << setw(15) <<" " << "Итоговые веса целей" << endl<<endl;
	for (int i = 0; i < b; i++) {   //вычисление нормированных оценок
		total = 0;
		for (int m = 0; m < a; m++) {
			total = total + arr[i][m];
		}
		for (int m = 0; m < a; m++) {
			try {
				array[i][m] = arr[i][m];
				if (total == 0) throw 1;
				array[i][m] = array[i][m] / total;
				cout << "посчитали дроби = " << array[i][m] << endl;
			}
			catch (int) {
				cout << "Произошло деление на ноль.\nРезультаты расчётов не будут верны.\nВыполните работу по оценке поставщиков снова." << endl;
				m--;
				total = 1;
			}
		}
	}
	for (int i = 0; i < a; i++) { //цикл прохождения по поставщикам
		weight[i] = 0;
		for (int f = 0; f < b; f++) { //цикл прохождения по экспертам
			weight[i] = weight[i] + array[f][i];
		}
		weight[i] = weight[i] / b;
	}
	for (int i = 0; i < a; i++) {
		file<<"Итоговый вес цели (Поставщик) №"<<i+1<<" = "<<setprecision(3)<<fixed << weight[i] << endl;
	}
	file << endl;
	MaxElement(weight, maxel, maxvalue, a);
	file << "Наибольший вес: " << fixed << setprecision(3) << maxvalue << " (" << "Поставщик №" << maxel + 1 << ")" << endl;
	file.close();
	return maxel;
}

void Make4Table(list<Supplier> lst, int a) {
	list<Supplier>::iterator p;
	int b = 0;
	ofstream file("Method_Res.txt", ios_base::app);
	for (p = lst.begin(); p != lst.end(); p++) {
		if (b == a) {
			file << "\nСамый подходящий Поставщик согласно отчёту экспертов:   " <<p->Get_nameorg()<< endl;
		}
		b++;
	}
	file.close();
}

void CheckIn_Adm(char* str1, char* str2) {
	ofstream f("Adm_log_in.txt", ios_base::trunc);
	for (int i = 0; i < strlen(str1); i++) {
		str1[i] = (char)((int)str1[i] + 3);
	}
	for (int i = 0; i < strlen(str2); i++) {
		str2[i] = (char)((int)str2[i] + 3);
	}
	f << str1 << " " << str2 << "\n";
	f.close();
}

void WriteContracts(list<Contract> lst) {
	ofstream file("Contracts.txt", ios_base::trunc);
	list<Contract>::iterator p;
	for (p = lst.begin(); p != lst.end(); p++) {
		file << p->client << ";" << p->supplier << ";" << p->contr_num << "\n";
	}
	file << "*;";
	file.close();
}

void TableContracts(list<Contract> lst) {
	ofstream file("ContractsT.txt", ios_base::trunc);
	list<Contract>::iterator p;
	file << "|" << setw(10) << setfill('-')  << "|" << setw(50) << "|" << setw(15) << "|" << endl;
	file << "|" << setfill(' ') << setw(9) << "Автосалон" << "|" << setw(29) << "Поставщик" << setw(21) << "|" << setw(13) << "Договор №" << setw(2) << "|" << endl;
	file << "|" << setw(10) << setfill('-') << "|" << setw(50) << "|" << setw(15) << "|" << endl;
	for (p = lst.begin(); p != lst.end(); p++) {
		file <<setfill(' ') << "|" << left << setw(9) << p->client << right << "|" << setw(49) << left << p->supplier << right << "|" << setw(14) << left << p->contr_num << right << "|" << endl;
		file << "|" << setw(10) << setfill('-') << "|" << setw(50) << "|" << setw(15) << "|" << endl;
	}
	file.close();
}

int FindContract(list<Contract> lst,char* str) {
	int i = 0;
	ofstream file("ContractsTF.txt", ios_base::trunc);
	list<Contract>::iterator p;
	file << "|" << setw(10) << setfill('-') << "|" << setw(50) << "|" << setw(15) << "|" << endl;
	file << "|" << setfill(' ') << setw(9) << "Автосалон" << "|" << setw(29) << "Поставщик" << setw(21) << "|" << setw(13) << "Договор №" << setw(2) << "|" << endl;
	file << "|" << setw(10) << setfill('-') << "|" << setw(50) << "|" << setw(15) << "|" << endl;
	for (p = lst.begin(); p != lst.end(); p++) {
		if (strcmp(str, p->supplier)==0) {
			file << setfill(' ') << "|" << left << setw(9) << p->client << right << "|" << setw(49) << left << p->supplier << right << "|" << setw(14) << left << p->contr_num << right << "|" << endl;
			file << "|" << setw(10) << setfill('-') << "|" << setw(50) << "|" << setw(15) << "|" << endl;
			i++;
		}
	}
	file.close();
	return i;
}

void FinalContract(list<Contract> lst, list<Supplier> l, char* str) {
	time_t t = time(NULL);
	tm tm; 
	localtime_s(&tm,& t);
	ofstream file("FinalContract.txt", ios_base::trunc);
	list <Contract>::iterator c;
	for (c = lst.begin(); c != lst.end(); c++) {
		if (strcmp(str, c->GetSupplier()) == 0) break;
	}
	list<Supplier>::iterator s;
	for (s = l.begin(); s != l.end(); s++) {
		if (strcmp(str, s->Get_nameorg()) == 0) break;
	}
	file << setw(38) << "ДОГОВОР ПОСТАВКИ №" << c->GetContrNum() << endl << endl << endl;
	file << left  <<"г. Минск" <<right << setfill(' ') <<setw(50) << " " << setfill('0') << setw(2) << tm.tm_mday << '.' << setw(2) << tm.tm_mon + 1 << '.' << setw(4) << tm.tm_year + 1900 << '\n'<<endl;
	file << setfill(' ') << setw(25) << left << s->Get_nameorg() << setw(9) << "в лице" << setw(17) << s->GetF() << setw(17) << s->GetI() << endl;
	file<<setw(20) << s->GetO() << ",";
	file << "действующего на основании  Устава, именуемый  в" << endl;
	file << "дальнейшем   Поставщик,  с одной стороны, и Автомир в лице Городная " << endl;
	file << "Ю.С., именуемый в дальнейшем Покупатель, с другой стороны, именуемые" << endl;
	file<<"в дальнейшем Стороны, заключили настоящий договор." << endl;
	file.close();
}

void ReadContract(list<Contract>& lst) {
	Contract c;
	ifstream file("Contracts.txt");
	if (!file.is_open() || (file.peek() == EOF)) {
		cout << "Файл с данными о контрактах пуст или не может быть открыт!\n" << endl;
	}
	else {
		for (int i = 0;; i++) {
			file.getline(c.client, 50, ';');
			if (strcmp(c.client, "*") == 0) { break; }
			file.getline(c.supplier, 50, ';');
			file.getline(c.contr_num, 50, '\n');
			lst.push_back(c);
		}
	}
	file.close();
}

void mailWorking(void* newS) {
	Supplier supp; 
	Expert expert;
	list<Expert> lexpert;    //список, хранящий данные действующих экспертов
	list<Expert>::iterator pexpert;
	list<Supplier> lsupp;   //список, хранящий информацию обо всех зарегистрированных поставщиках
	list<Supplier> poten;   //потенциальные поставщики (статус = 0)
	list<Supplier> l1;      //поставщики, которым отправил заявку администратор (статус = 1)
	list<Supplier> l2;      //поставщики, с которыми заключён договор (статус = 2)
	list<Supplier> l3;      //поставщики, желающие расторгнуть договор (статус = 3)
	list<Supplier> l4;      //поставщики, с которыми администратор желает расторгнуть договор (статус = 4)
	list<Supplier> ::iterator psupp;
	list<Contract> contr;
	list<Contract>::iterator pcontr;
	ReadContract(contr);
	int c, c1 = 0, c2 = 0, c3 = 0,aaa=8;
	int flag = 0;
	char p[500], com[500], k[500], m[500],result[500];
	com[0] = '\0'; p[0] = '\0'; k[0] = '\0'; m[0] = '\0';
	cout << "*---Сервер готов к работе---*\n\n";
	MakeSuppList(lsupp);
	MakeExpList(lexpert);
	for (psupp = lsupp.begin(); psupp != lsupp.end();psupp++) {
		if (psupp->c.GetStatus() == 0) poten.push_back(*psupp); //заполнение списков поставщиков с разными статусами договора
		if (psupp->c.GetStatus() == 1) l1.push_back(*psupp);   
		if (psupp->c.GetStatus() == 2) l2.push_back(*psupp);
		if (psupp->c.GetStatus() == 3) l3.push_back(*psupp);
		if (psupp->c.GetStatus() == 4) l4.push_back(*psupp);
	}
	while (1) 
	{
		strcpy_s(p, "ГЛАВНОЕ МЕНЮ:\n");
		send((SOCKET)newS, p, sizeof(p), 0);
		strcpy_s(k, " 1. Войти как администратор.\n 2. Войти как поставщик.\n 3. Войти как эксперт.\n 4. Завершить работу.\n ");
		send((SOCKET)newS, k, sizeof(k), 0);
		p[0] = '\0'; k[0] = '\0';
		recv((SOCKET)newS, m, sizeof(m), 0); //пункт в главном меню, выбранный клиентом
		c = atoi(m); 
			
		switch (c) {
		case 1: {            //ВОЙТИ КАК АДМИНИСТРАТОР
			strcpy_s(p, "1");
			send((SOCKET)newS, p, sizeof(p), 0); //синхронизация кейса сервера и клиента
			//регистрация или авторизация//
			m[0] = '\0';
			int choice;
			ifstream ff("Adm_log_in.txt");
			if(ff.peek() != EOF) send((SOCKET)newS, "m", sizeof("m"), 0);
			else send((SOCKET)newS, "n", sizeof("n"), 0);
			recv((SOCKET)newS, m, sizeof(m), 0);
			choice = atoi(m);
			if (choice == 1) {          //авторизация  
				k[0] = '\0';
				m[0] = '\0';
				p[0] = '\0';
				strcpy_s(p, "a");
				while (strcmp(p, "b") != 0) {
					int a = 0;
					char alog[50];
					char apassw[50];
					recv((SOCKET)newS, k, sizeof(k), 0); //получили логин
					recv((SOCKET)newS, m, sizeof(m), 0); //получили пароль
					ifstream f("Adm_log_in.txt");
					f.getline(alog, 50, ' ');
					for (int i = 0; i < strlen(alog); i++) { //считали и расшифровали логин из файла
						alog[i] = (char)((int)alog[i] - 3);
					}
					f.getline(apassw, 50, '\n');
					for (int i = 0; i < strlen(apassw); i++) { //считали и расшифровали пароль из файла
						apassw[i] = (char)((int)apassw[i] - 3);
					}
					f.close();
					if ((strcmp(alog, k) == 0) && (strcmp(apassw, m) == 0))
						strcpy_s(p, "b");
					else strcpy_s(p, "a");
					send((SOCKET)newS, p, sizeof(p), 0);
				}
			}
			if (choice == 2) {   //регистрация
				k[0] = '\0';
				m[0] = '\0';
				recv((SOCKET)newS, k, sizeof(k), 0); //получили логин
				recv((SOCKET)newS, m, sizeof(m), 0); //получили пароль
				CheckIn_Adm(k, m);
			}
			while (c1 != 4) {
				strcpy_s(k, "МЕНЮ АДМИНИСТРАТОРА:\n 1. Работа с поставщиками.\n 2. Управление экспертами.\n 3. Изменить логин и/или пароль.\n 4. Вернуться в главное меню.");
				send((SOCKET)newS, k, sizeof(k), 0);
				m[0] = '\0';
				recv((SOCKET)newS, m, sizeof(m), 0);
				c1 = atoi(m);
				switch (c1) {
				case 1: {               //работа администратора с поставщиками
					strcpy_s(p, "1"); //дали знать клиентскому приложению, с каким кейсом работаем
					send((SOCKET)newS, p, sizeof(p), 0);
					while (c2 != 5) {
						strcpy_s(p, "РАБОТА С ПОСТАВЩИКАМИ:\n 1. Просмотреть полный список поставщиков.\n 2. Найти информацию о конкретном поставщике.\n 3. Заключить договор.\n 4. Расторгнуть договор. \n 5. Вернуться в меню администратора.\n");
						send((SOCKET)newS, p, sizeof(p), 0);
						recv((SOCKET)newS, m, sizeof(m), 0);
						c2 = atoi(m);
						switch (c2) {
						case 1: {               //просмотр полного списка поставщиков
							strcpy_s(p, "1");
							send((SOCKET)newS, p, sizeof(p), 0);
							supp.WriteTable(lsupp);
							supp.WriteTableAdm(lsupp);
							supp.Sorting(lsupp);
							if (lsupp.size() == 0) {
								send((SOCKET)newS, "13", sizeof("13"), 0);
							}
							else {
								ifstream file("Supp_table_adm.txt");
								while (!file.eof()) {
									k[0] = '\0';
									file.getline(k, 256, '\n');
									m[0] = '\0';
									strcpy_s(m, "конец");
									if (file.eof()) 	send((SOCKET)newS, m, sizeof(m), 0);
									else send((SOCKET)newS, k, sizeof(k), 0);
								}
								k[0] = '\0';
								file.close();
								m[0] = '\0';
							}
							break;
						}
						case 2: {                //поиск поставщика администратором
							strcpy_s(p, "2");
							send((SOCKET)newS, p, sizeof(p), 0);
							m[0] = '\0'; int tt;
							recv((SOCKET)newS, m, sizeof(m), 0);
							tt = supp.FindAdm(lsupp, m);
							if (tt == 0) {
								m[0] = '\0';
								strcpy_s(m, "Такой поставщик не был зарегистрирован!\n");
								send((SOCKET)newS, m, sizeof(m), 0);
							}
							else {
								ifstream file("Supp_table_f.txt");
								while (!file.eof()) {
									k[0] = '\0';
									file.getline(k, 256, '\n');
									m[0] = '\0';
									strcpy_s(m, "конец");
									if (file.eof()) 	send((SOCKET)newS, m, sizeof(m), 0);
									else send((SOCKET)newS, k, sizeof(k), 0);
								}
								k[0] = '\0';
							}
							m[0] = '\0';
							k[0] = '\0';
							break;
						}
						case 3: {              //отправление администратором заявки на заключение договора
							strcpy_s(p, "3");
							send((SOCKET)newS, p, sizeof(p), 0);
							k[0] = '\0';
							m[0] = '\0';
							ifstream file("Method_Res.txt");
							while (!file.eof()) {
								k[0] = '\0';
								file.getline(k, 256, '\n');
								m[0] = '\0';
								strcpy_s(m, "конец");
								if (file.eof()) 	send((SOCKET)newS, m, sizeof(m), 0);
								else send((SOCKET)newS, k, sizeof(k), 0);
							}
							k[0] = '\0';
							file.close();
							m[0] = '\0';
							strcpy_s(k, "g");
								recv((SOCKET)newS, m, sizeof(m), 0);
								int o = 0;
								for (psupp = poten.begin(); psupp != poten.end(); psupp++) {
									if (strcmp(m, psupp->Get_nameorg()) == 0) { o++; break; }
								}
								if(o==0) send((SOCKET)newS, "t", sizeof("t"), 0);
								else { 
									send((SOCKET)newS, "g", sizeof("g"), 0);
									l1.push_back(*psupp);
									poten.erase(psupp);
									for (psupp = lsupp.begin(); psupp != lsupp.end(); psupp++) {
										if (strcmp(m, psupp->Get_nameorg()) == 0) { psupp->c.SetStatus(1); break; }
									}
									supp.WriteFile(lsupp);
								}
							break;
						}
						case 4: {
							strcpy_s(p, "4");
							send((SOCKET)newS, p, sizeof(p), 0);
							k[0] = '\0';
							m[0] = '\0';
							strcpy_s(k, "g");
							recv((SOCKET)newS, m, sizeof(m), 0); //название организации
							int o = 0;
							for (psupp = l2.begin(); psupp != l2.end(); psupp++) {
								if (strcmp(m, psupp->Get_nameorg()) == 0) { o=1; break; } //данный поставщик не инициировал расторжение договора
							}
							if (o == 0) {
								for (psupp = l4.begin(); psupp != l4.end(); psupp++) {
									if (strcmp(m, psupp->Get_nameorg()) == 0) { o = 2; break; } //данный поставщик уже инициировал расторжение договора
								}
							}
							if (o == 0) send((SOCKET)newS, "t", sizeof("t"), 0);
							else {
								char bufer[500];
								
								if (o == 1) {                                    //отправление администратором заявки на расторжение договора
									send((SOCKET)newS, "e", sizeof("e"), 0);
									l3.push_back(*psupp);
									l2.erase(psupp);
									for (psupp = lsupp.begin(); psupp != lsupp.end(); psupp++) {
										if (strcmp(m, psupp->Get_nameorg()) == 0) { psupp->c.SetStatus(3); break; }
									}
								}
								if (o == 2) {               //окончательное двустороннее расторжение договора
									send((SOCKET)newS, "g", sizeof("g"), 0);
									psupp->Set_contracts(psupp->Get_contracts() - 1);
									poten.push_back(*psupp);
									l4.erase(psupp);
									for (psupp = lsupp.begin(); psupp != lsupp.end(); psupp++) {
										if (strcmp(m, psupp->Get_nameorg()) == 0) {
											psupp->c.SetStatus(0);
											psupp->Set_contracts(psupp->Get_contracts() - 1);
											strcpy_s(bufer, psupp->Get_nameorg());
											break;
										}
									}
									for (pcontr = contr.begin(); pcontr != contr.end(); pcontr++) {
										if (strcmp(pcontr->GetSupplier(), bufer) == 0) {
											contr.erase(pcontr);
											break;
										}
									}
								}
								supp.WriteFile(lsupp);
								WriteContracts(contr);
								TableContracts(contr);
							}
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
				case 2: {           //работа с экспертами
					strcpy_s(p, "2");
					send((SOCKET)newS, p, sizeof(p), 0);
					while (c2 != 5) {
						strcpy_s(p, "УПРАВЛЕНИЕ ЭКСПЕРТАМИ:\n 1. Просмотреть информацию об экспертах.\n 2. Назначить эксперта.\n 3. Удалить эксперта.\n 4. Отредактировать информацию об эксперте. \n 5. Вернуться в меню администратора.\n");
						send((SOCKET)newS, p, sizeof(p), 0);
						recv((SOCKET)newS, m, sizeof(m), 0);
						c2 = atoi(m);
						switch (c2) {
						case 1: {              //просмотр информации об экспертах (администратором)
							strcpy_s(p, "1");
							send((SOCKET)newS, p, sizeof(p), 0);
							while (c3 != 3) {
								strcpy_s(p, "ИНФОРМАЦИЯ ОБ ЭКСПЕРТАХ:\n 1. Просмотреть в порядке убывания стажа. \n 2. Просмотреть информацию об экспертах с определённым стажем.\n 3. Вернуться в меню управления экспертами.\n");
								send((SOCKET)newS, p, sizeof(p), 0);
								recv((SOCKET)newS, m, sizeof(m), 0);
								c3 = atoi(m);
								switch (c3) {
								case 1: {                 //просмотр информации об экспертах в порядке убывания их стажа
									strcpy_s(p, "1");
									send((SOCKET)newS, p, sizeof(p), 0);
									ifstream bf("Experts.txt");
									if (bf.peek() == EOF) {
										send((SOCKET)newS, "m", sizeof("m"), 0);
									}
									else {
										send((SOCKET)newS, "n", sizeof("n"), 0);
										expert.Sorting(lexpert);
										ifstream file("Experts_buf.txt");
										while (!file.eof()) {
											k[0] = '\0';
											file.getline(k, 256, '\n');
											m[0] = '\0';
											strcpy_s(m, "конец");
											if (file.eof()) 	send((SOCKET)newS, m, sizeof(m), 0);
											else send((SOCKET)newS, k, sizeof(k), 0);
										}
										k[0] = '\0';
										file.close();
										m[0] = '\0';
									}
									break;
								}
								case 2: {              //просмотреть информацию об экспертах с определённым стажем
									strcpy_s(p, "2");
									send((SOCKET)newS, p, sizeof(p), 0);
									m[0] = '\0';
									ifstream bf("Experts.txt");
									if (bf.peek() == EOF) {
										send((SOCKET)newS, "m", sizeof("m"), 0);
									}
									else {
										send((SOCKET)newS, "n", sizeof("n"), 0);
										m[0] = '\0'; int tt, ty;
										recv((SOCKET)newS, m, sizeof(m), 0);
										ty = atoi(m);
										tt = expert.Filtre(lexpert, ty);
										if (tt == 0) {
											m[0] = '\0';
											strcpy_s(m, "Экспертов с таким стажем нет!\n");
											send((SOCKET)newS, m, sizeof(m), 0);
										}
										else {
											ifstream file("Experts_buf.txt");
											while (!file.eof()) {
												k[0] = '\0';
												file.getline(k, 256, '\n');
												m[0] = '\0';
												strcpy_s(m, "конец");
												if (file.eof()) 	send((SOCKET)newS, m, sizeof(m), 0);
												else send((SOCKET)newS, k, sizeof(k), 0);
											}
											k[0] = '\0';
										}
										m[0] = '\0';
										k[0] = '\0';
									}
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
						case 2: {                 //добавление нового эксперта
							p[0] = '\0';
							strcpy_s(p, "2");
							send((SOCKET)newS, p, sizeof(p), 0);
							//фамилия нового эксперта
							com[0] = '\0';
							recv((SOCKET)newS, com, sizeof(com), 0);
							expert.SetF(com);
							com[0] = '\0';
							//имя нового эксперта
							recv((SOCKET)newS, com, sizeof(com), 0);
							expert.SetI(com);
							com[0] = '\0';
							//отчество нового эксперта
							recv((SOCKET)newS, com, sizeof(com), 0);
							expert.SetO(com);
							com[0] = '\0';
							//должность нового эксперта
							recv((SOCKET)newS, com, sizeof(com), 0);
							expert.SetPos(com);
							com[0] = '\0';
							//стаж нового эксперта
							recv((SOCKET)newS, com, sizeof(com), 0);
							int d;
							d = atoi(com);
							expert.SetExp(d);
							com[0] = '\0';
							//логин нового эксперта
							int ch = 0;
							while (ch != -1) {
								ch = 0;
								recv((SOCKET)newS, com, sizeof(com), 0);
								for (pexpert = lexpert.begin(); pexpert != lexpert.end(); pexpert++) {
									if (strcmp(com, pexpert->GetLogin()) == 0) {
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
							expert.SetLogin(com);
							com[0] = '\0';
							//пароль нового эксперта
							recv((SOCKET)newS, com, sizeof(com), 0);
							expert.SetPassword(com);
							com[0] = '\0';
                            //добавление нового эксперта в список
							lexpert.push_back(expert);
							//перезапись файлов, связанных с экспертами
							expert.WriteFile(lexpert);
							expert.WriteTable(lexpert);
							break;
						}
						case 3: {               //удаление экспертов
							strcpy_s(p, "3");
							send((SOCKET)newS, p, sizeof(p), 0);
							ifstream bf("Experts.txt");
							if (bf.peek() == EOF) {
								send((SOCKET)newS, "m", sizeof("m"), 0); //сообщаем клиенту, что эксперты ещё не были назначены
							}
							else {
								send((SOCKET)newS, "n", sizeof("n"), 0);
								p[0] = '\0';
								m[0] = '\0';
								recv((SOCKET)newS, m, sizeof(m), 0);
								int flag = 0;
								for (pexpert = lexpert.begin(); pexpert != lexpert.end(); pexpert++) {   //ищем эксперта с заданной фамилией; удаляем, если находим
									if (strcmp(pexpert->GetF(), m) == 0) {
										lexpert.erase(pexpert);
										flag++;
										break;
									}
								}
								if (flag == 0) {
									m[0] = '\0';
									strcpy_s(m, "Эксперт с такой фамилией не был добавлен!\n");  //сообщаем клиенту, что нет экспертов с такой фамилией 
									send((SOCKET)newS, m, sizeof(m), 0);
								}
								else {
									//перезапись файлов, связанных с экспертами
									expert.WriteFile(lexpert);
									expert.WriteTable(lexpert);
									//
									m[0] = '\0';
									strcpy_s(m, "Аккаунт успешно удалён!\n");
									send((SOCKET)newS, m, sizeof(m), 0);
									m[0] = '\0';
								}
							}
								break;
					    }
						case 4: {                      //редактирование информации об экспертах
							p[0] = '\0';
							strcpy_s(p, "4");
							send((SOCKET)newS, p, sizeof(p), 0);
							ifstream bf("Experts.txt");
							if (bf.peek() == EOF) {
								send((SOCKET)newS, "m", sizeof("m"), 0);           //сообщаем клиенту, что ни один эксперт ещё не был добавлен         
							}
							else {                                                //если хотя бы один эксперт был добавлен, редактируем данные о нём
								send((SOCKET)newS, "n", sizeof("n"), 0);
								p[0] = '\0';
								k[0] = '\0';
								int qw;
								recv((SOCKET)newS, k, sizeof(k), 0); //фамилия эксперта, данные о котором хочет изменить администратор
								m[0] = '\0';
								int ll = 0;
								int flag = 0;
								for (pexpert = lexpert.begin(); pexpert != lexpert.end(); pexpert++) {    //ищем эксперта с заданной фамилией
									if (strcmp(pexpert->GetF(), k) == 0) {
										flag++;
										break;
									}
									ll++;
								}
								if (flag==0) send((SOCKET)newS, "k", sizeof("k"), 0);        //сообщаем администратору, что нет эксперта с такой фамилией
								else {
									send((SOCKET)newS, "d", sizeof("d"), 0);  //если нашли эксперта с такой фамилией, редактируем
									qw = 0;
									while (qw!=6) {
										recv((SOCKET)newS, m, sizeof(m), 0); //номер пункта меню редактирования экспертов
										qw = atoi(m);
										switch (qw) {
										case 1: {                   //редактирование фамилии эксперта
											p[0] = '\0';
											strcpy_s(p, "1");
											send((SOCKET)newS, p, sizeof(p), 0);
											com[0] = '\0';
											recv((SOCKET)newS, com, sizeof(com), 0);
											pexpert->SetF(com);
											com[0] = '\0';
											//перезапись файлов, связанных с экспертом
											expert.WriteFile(lexpert);
											expert.WriteTable(lexpert);
											break;
										}
										case 2: {                 //редактирование имени эксперта
											p[0] = '\0';
											strcpy_s(p, "2");
											send((SOCKET)newS, p, sizeof(p), 0);
											com[0] = '\0';
											recv((SOCKET)newS, com, sizeof(com), 0);
											pexpert->SetI(com);
											com[0] = '\0';
											//перезапись файлов, связанных с экспертом
											expert.WriteFile(lexpert);
											expert.WriteTable(lexpert);
											break;
										}
										case 3: {                //редактирование отчества эксперта
											p[0] = '\0';
											strcpy_s(p, "3");
											send((SOCKET)newS, p, sizeof(p), 0);
											com[0] = '\0';
											recv((SOCKET)newS, com, sizeof(com), 0);
											pexpert->SetO(com);
											com[0] = '\0';
											//перезапись файлов, связанных с экспертом
											expert.WriteFile(lexpert);
											expert.WriteTable(lexpert);
											break;
										}
										case 4: {                //редактирование должности эксперта
											p[0] = '\0';
											strcpy_s(p, "4");
											send((SOCKET)newS, p, sizeof(p), 0);
											com[0] = '\0';
											recv((SOCKET)newS, com, sizeof(com), 0);
											pexpert->SetPos(com);
											com[0] = '\0';
											//перезапись файлов, связанных с экспертом
											expert.WriteFile(lexpert);
											expert.WriteTable(lexpert);
											break;
										}
										case 5: {                //редактирование стажа эксперта
											int bb;
											p[0] = '\0';
											strcpy_s(p, "5");
											com[0] = '\0';
											send((SOCKET)newS, p, sizeof(p), 0);
											recv((SOCKET)newS, com, sizeof(com), 0);
											bb = atoi(com);
											pexpert->SetExp(bb);
											com[0] = '\0';
											//перезапись файлов, связанных с экспертом
											expert.WriteFile(lexpert);
											expert.WriteTable(lexpert);
											break;
										}
										case 6: {
											p[0] = '\0';
											strcpy_s(p, "6");
											send((SOCKET)newS, p, sizeof(p), 0);
											break;
										}

										}
									}
									
								}
							}
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
					c2 = 0;
					break;
				}
				case 3: {                   //ИЗМЕНЕНИЕ ЛОГИНА И/ИЛИ ПАРОЛЯ
					strcpy_s(p, "3");
					send((SOCKET)newS, p, sizeof(p), 0);
					while (c2 != 3) {
						strcpy_s(p, "ИЗМЕНИТЬ ЛОГИН И/ИЛИ ПАРОЛЬ:\n 1. Изменить логин.\n 2. Изменить пароль.\n 3. Вернуться в меню администратора.\n");
						send((SOCKET)newS, p, sizeof(p), 0);
						recv((SOCKET)newS, m, sizeof(m), 0);
						c2 = atoi(m);
						switch (c2) {
						case 1: {                        //изменение логина администратора
							strcpy_s(p, "1");
							send((SOCKET)newS, p, sizeof(p), 0);
							char alog[50];
							char apassw[50];
							m[0] = '\0';
							recv((SOCKET)newS, m, sizeof(m), 0);
							ifstream f("Adm_log_in.txt");
							f.getline(alog, 50, ' ');
							for (int i = 0; i < strlen(alog); i++) {   //считали и расшифровали логин из файла
								alog[i] = (char)((int)alog[i] - 3);
							}
							f.getline(apassw, 50, '\n');
							for (int i = 0; i < strlen(apassw); i++) { //считали и расшифровали пароль из файла
								apassw[i] = (char)((int)apassw[i] - 3);
							}
							f.close();
							CheckIn_Adm(m, apassw);
							break;
						}
						case 2: {                      //изменение пароля администратора
							strcpy_s(p, "2");
							send((SOCKET)newS, p, sizeof(p), 0);
							char alog[50];
							char apassw[50];
							m[0] = '\0';
							recv((SOCKET)newS, m, sizeof(m), 0);
							ifstream f("Adm_log_in.txt");
							f.getline(alog, 50, ' ');
							for (int i = 0; i < strlen(alog); i++) {   //считали и расшифровали логин из файла
								alog[i] = (char)((int)alog[i] - 3);
							}
							f.getline(apassw, 50, '\n');
							for (int i = 0; i < strlen(apassw); i++) { //считали и расшифровали пароль из файла
								apassw[i] = (char)((int)apassw[i] - 3);
							}
							f.close();
							CheckIn_Adm(alog, m);
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
						cout << "jsdhfbd  "<< a << endl;
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
							strcpy_s(p, "1");
							send((SOCKET)newS, p, sizeof(p), 0);
							p[0] = '\0';
							k[0] = '\0';
							int qw;
							recv((SOCKET)newS, k, sizeof(k), 0); //логин
							m[0] = '\0';
							recv((SOCKET)newS, m, sizeof(m), 0); //номер пункта меню
							int ll = 0;
							for (psupp = lsupp.begin(); psupp != lsupp.end(); psupp++) {
								if (strcmp(psupp->GetLogin(), k) == 0) {
									cout << "Мы здесь" << endl;
									//lsupp.erase(psupp);
									break;
								}
								ll++;
							}
							cout << psupp->Get_nameorg() << endl;
							cout << "Он седьмой по счёту  " << ll << endl;
							qw = atoi(m);
							switch (qw) {
							case 1: {
								p[0] = '\0';
								strcpy_s(p, "1");
								send((SOCKET)newS, p, sizeof(p), 0);
								com[0] = '\0';
								recv((SOCKET)newS, com, sizeof(com), 0);
								psupp->Set_nameorg(com);
								//cout << supp(ll, lsupp).Get_nameorg() << endl;
								com[0] = '\0';
								supp.WriteFile(lsupp);
								supp.WriteTable(lsupp);
								supp.WriteTableAdm(lsupp);
								break;
							}
							case 2: {
								p[0] = '\0';
								strcpy_s(p, "2");
								send((SOCKET)newS, p, sizeof(p), 0);
								com[0] = '\0';
								recv((SOCKET)newS, com, sizeof(com), 0);
								psupp->Set_country(com);
								com[0] = '\0';
								supp.WriteFile(lsupp);
								supp.WriteTable(lsupp);
								supp.WriteTableAdm(lsupp);
								break;
							}
							case 3: {
								p[0] = '\0';
								strcpy_s(p, "3");
								send((SOCKET)newS, p, sizeof(p), 0);
								com[0] = '\0';
								recv((SOCKET)newS, com, sizeof(com), 0);
								psupp->Set_city(com);
								com[0] = '\0';
								supp.WriteFile(lsupp);
								supp.WriteTable(lsupp);
								supp.WriteTableAdm(lsupp);
								break;
							}
							case 4: {
								p[0] = '\0';
								strcpy_s(p, "4");
								send((SOCKET)newS, p, sizeof(p), 0);
								com[0] = '\0';
								recv((SOCKET)newS, com, sizeof(com), 0);
								psupp->SetF(com);
								com[0] = '\0';
								supp.WriteFile(lsupp);
								supp.WriteTable(lsupp);
								supp.WriteTableAdm(lsupp);
								break;
							}
							case 5: {
								p[0] = '\0';
								strcpy_s(p, "5");
								com[0] = '\0';
								send((SOCKET)newS, p, sizeof(p), 0);
								recv((SOCKET)newS, com, sizeof(com), 0);
								psupp->SetI(com);
								com[0] = '\0';
								supp.WriteFile(lsupp);
								supp.WriteTable(lsupp);
								supp.WriteTableAdm(lsupp);
								break;
							}
							case 6: {
								p[0] = '\0';
								strcpy_s(p, "6");
								send((SOCKET)newS, p, sizeof(p), 0);
								com[0] = '\0';
								recv((SOCKET)newS, com, sizeof(com), 0);
								psupp->SetO(com);
								com[0] = '\0';
								supp.WriteFile(lsupp);
								supp.WriteTable(lsupp);
								supp.WriteTableAdm(lsupp);
								break;
							}
							case 7: {
								p[0] = '\0';
								strcpy_s(p, "7");
								send((SOCKET)newS, p, sizeof(p), 0);
								com[0] = '\0';
								recv((SOCKET)newS, com, sizeof(com), 0);
								psupp->Set_phone(com);
								com[0] = '\0';
								supp.WriteFile(lsupp);
								supp.WriteTable(lsupp);
								supp.WriteTableAdm(lsupp);
								break;
							}
							case 8: {
								p[0] = '\0';
								strcpy_s(p, "8");
								send((SOCKET)newS, p, sizeof(p), 0);
								com[0] = '\0';
								recv((SOCKET)newS, com, sizeof(com), 0);
								psupp->Set_email(com);
								com[0] = '\0';
								supp.WriteFile(lsupp);
								supp.WriteTable(lsupp);
								supp.WriteTableAdm(lsupp);
								break;
							}
							case 9: {
								p[0] = '\0';
								strcpy_s(p, "9");
								send((SOCKET)newS, p, sizeof(p), 0);
								com[0] = '\0';
								recv((SOCKET)newS, com, sizeof(com), 0);
								int d;
								d = atoi(com);
								psupp->Set_contracts(d);
								com[0] = '\0';
								break;
							}
							case 10: {
								p[0] = '\0';
								strcpy_s(p, "10");
								send((SOCKET)newS, p, sizeof(p), 0);
								com[0] = '\0';
								recv((SOCKET)newS, com, sizeof(com), 0);
								float numb;
								numb = stof(com);
								psupp->Set_min_price(numb);
								com[0] = '\0';
								break;
							}
							case 11: {
								break;
							}
							}
							break;
						}
						case 2: {
							p[0] = '\0';
							m[0] = '\0';
							int q;
							strcpy_s(p, "2");
							send((SOCKET)newS, p, sizeof(p), 0);
							recv((SOCKET)newS, m, sizeof(m), 0);
							q = atoi(m);
							if (q == 1) {
								m[0] = '\0';
								recv((SOCKET)newS, m, sizeof(m), 0);
								cout << m << endl;
								for (psupp = lsupp.begin(); psupp != lsupp.end(); psupp++) {
									if (strcmp(psupp->GetLogin(), m) == 0) {
										cout << "Мы здесь" << endl;
										lsupp.erase(psupp);
										break;
									}
								}
								for (auto l : lsupp) {
									cout << l.GetF() << endl;
								}
								supp.WriteFile(lsupp);
								m[0] = '\0';
								strcpy_s(m, "Аккаунт успешно удалён!\n");
								send((SOCKET)newS, m, sizeof(m), 0);
								m[0] = '\0';
							}
							
							break;
						}
						case 3: {
							p[0] = '\0';
							strcpy_s(p, "3");
							send((SOCKET)newS, p, sizeof(p), 0);
							m[0] = '\0';
							char gbuf[500],gbuff[500];
							recv((SOCKET)newS, m, sizeof(m), 0); //получили логин
							int r = 0;
							gbuf[0] = '\0';
							gbuff[0] = '\0';
							for (psupp = l1.begin(); psupp != l1.end(); psupp++) {
								if (strcmp(psupp->GetLogin(), m) == 0) {
									send((SOCKET)newS, "1", sizeof("1"), 0);
									strcpy_s(gbuf, psupp->Get_nameorg());
									strcpy_s(gbuff, psupp->Get_nameorg());
									r++;
									break;
								}
							}
							if (r == 0) {
								send((SOCKET)newS, "2", sizeof("2"), 0);
							}
							else {
								int lastn;
								Contract c1;
								psupp->c.SetStatus(2);
								psupp->c.SetSupplier(gbuf);
								gbuf[0] = '\0';
								p[0] = '\0';
								strcpy_s(gbuf, "230001");
								_itoa_s(psupp->Get_contracts(), p, 10);
								strcat_s(gbuf, p);
								p[0] = '\0';
								srand(time(NULL));
								lastn = aaa+rand()%17;
								aaa++;
								_itoa_s(lastn, p, 10);
								strcat_s(gbuf, p);
								psupp->c.SetContrNum(gbuf);
								psupp->Set_contracts(psupp->Get_contracts() + 1);
								l2.push_back(*psupp);
								cout << "show tje contract:  " << endl;
								cout << psupp->c.GetClient() << endl;
								cout << psupp->c.GetSupplier() << endl;
								c1.SetSupplier(psupp->c.GetSupplier());
								cout << psupp->c.GetContrNum() << endl;
								c1.SetContrNum(psupp->c.GetContrNum());
								contr.push_back(c1);
								WriteContracts(contr);
								TableContracts(contr);
								l1.erase(psupp);
								
								for (psupp = lsupp.begin(); psupp != lsupp.end(); psupp++) {
									if (strcmp(psupp->GetLogin(), m) == 0) {
										cout << "Поменяли цифру на 2 в основном списке" << endl;
										psupp->c.SetStatus(2);
										psupp->Set_contracts(psupp->Get_contracts() + 1);
										break;
									}
								}
								cout<< lsupp.size() << endl;
								cout << poten.size() << endl;
								cout << l1.size() << endl;
								cout << l2.size() << endl;
								supp.WriteFile(lsupp);
								FindContract(contr,gbuff);
								FinalContract(contr, l2, gbuff);
								ifstream file("ContractsTF.txt");
								while (!file.eof()) {
									//cout << "Hi, babe" << endl;
									k[0] = '\0';
									file.getline(k, 256, '\n');
									m[0] = '\0';
									strcpy_s(m, "конец");
									if (file.eof()) 	send((SOCKET)newS, m, sizeof(m), 0);
									else send((SOCKET)newS, k, sizeof(k), 0);

								}
							}

							break;
						}
						case 4: {
							int state = 0;
							p[0] = '\0';
							strcpy_s(p, "4");
							send((SOCKET)newS, p, sizeof(p), 0);
							m[0] = '\0';
							recv((SOCKET)newS, m, sizeof(m), 0); //получили логин
							int r = 0;
							for (psupp = l2.begin(); psupp != l2.end(); psupp++) {
								if (strcmp(psupp->GetLogin(), m) == 0) {
									send((SOCKET)newS, "1", sizeof("1"), 0);
									r++;
									state = 1;   //стейт =1, если договор был в статусе заключённых
									break;
								}
							}
							if (r == 0) {
								for (psupp = l3.begin(); psupp != l3.end(); psupp++) {
									if (strcmp(psupp->GetLogin(), m) == 0) {
										send((SOCKET)newS, "3", sizeof("3"), 0);
										r++;
										state = 2; //если был в заявках от салона на расторжение
										break;
									}
								}
								if (r==0)
								send((SOCKET)newS, "2", sizeof("2"), 0);
							}
								if (state == 1) {
									psupp->c.SetStatus(4);
									l4.push_back(*psupp);
									l2.erase(psupp);
									for (psupp = lsupp.begin(); psupp != lsupp.end(); psupp++) {
										if (strcmp(psupp->GetLogin(), m) == 0) {
											//cout << "Поменяли цифру на 2 в основном списке" << endl;
											psupp->c.SetStatus(4);
											break;
										}
									}
								}
								else if(state==2){
									char bbuf[500];
									psupp->c.SetStatus(0);
									psupp->Set_contracts(psupp->Get_contracts() - 1);
									poten.push_back(*psupp);
									l3.erase(psupp);
									for (psupp = lsupp.begin(); psupp != lsupp.end(); psupp++) {
										if (strcmp(psupp->GetLogin(), m) == 0) {
											cout << "Поменяли цифру на 2 в основном списке" << endl;
											psupp->c.SetStatus(0);
											strcpy_s(bbuf, psupp->Get_nameorg());
											break;
										}
									}
									for (pcontr = contr.begin(); pcontr != contr.end(); pcontr++) {
										if (strcmp(bbuf, pcontr->GetSupplier()) == 0) {
											contr.erase(pcontr);
											break;
										}
									}
									WriteContracts(contr);
									TableContracts(contr);
									cout << "contracts = " << contr.size() << endl;
								}
								cout << lsupp.size() << endl;
								cout << poten.size() << endl;
								cout << l1.size() << endl;
								cout << l2.size() << endl;
								cout << l3.size() << endl;
								cout << l4.size() << endl;
								supp.WriteFile(lsupp);
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
							float a, b;
							k[0] = '\0'; int tt;
							recv((SOCKET)newS, k, sizeof(k), 0);
							a = stof(k);
							m[0] = '\0';
							recv((SOCKET)newS, m, sizeof(m), 0);
							b = stof(m);
							tt = supp.Filtr_2(lsupp, a,b);
							if (tt == 0) {
								m[0] = '\0';
								strcpy_s(m, "Такие поставщики не найдены!\n");
								send((SOCKET)newS, m, sizeof(m), 0);
							}
							else {
								ifstream file("Supp_table_f2.txt");
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
						case 4: {
							strcpy_s(p, "4");
							send((SOCKET)newS, p, sizeof(p), 0);
							m[0] = '\0'; int tt;
							recv((SOCKET)newS, m, sizeof(m), 0);
							tt = supp.Find(lsupp, m);
							if (tt == 0) {
								m[0] = '\0';
								strcpy_s(m, "Такой поставщик не был зарегистрирован!\n");
								send((SOCKET)newS, m, sizeof(m), 0);
							}
							else {
								ifstream file("Supp_table_f.txt");
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
					int ps, exn,sh;
					list<Supplier> potential;
					MakePotSupp(potential,lsupp);
					/*cout << lsupp.size() << endl;
					cout << potential.size() << endl;
					cout << lexpert.size() << endl;*/
					ps = potential.size();
					exn = lexpert.size();
					k[0] = '\0';
					m[0] = '\0';
					_itoa_s(ps, k, 10);
					_itoa_s(exn, m, 10);
					send((SOCKET)newS, k, sizeof(k), 0); //сообщаем клиенту количество потенц поставщиков
					send((SOCKET)newS, m, sizeof(m), 0); //сообщаем количество действущих экспертов
					int arr[50][50];
					for (int i = 0; i < exn; i++) {
						for (int j = 0; j < ps; j++) {
							k[0] = '\0';
							recv((SOCKET)newS, k, sizeof(k), 0);
							arr[i][j] = atoi(k);
						}
					}
					for (int i = 0; i < exn; i++) {
						for (int j = 0; j < ps; j++) {
							cout << arr[i][j] << "  ";
						}
						cout << endl;
					}
					Make1Table(arr, ps, exn);
					Make2Table(arr, ps, exn);
					sh=Make3Table(arr, ps, exn);
					Make4Table(poten, sh);
					int pointer = 0;
					m[0] = '\0';
					for (psupp = poten.begin(); psupp != poten.end(); psupp++) {
						if (pointer == sh) {
							cout << psupp->Get_nameorg() << endl;
							strcpy_s(m, psupp->Get_nameorg());
							break;
						}
						pointer++;
					}
					supp.Find(lsupp, m);
					result[0] = '\0';
					strcpy_s(result, m);
					ifstream file("Supp_table_f.txt");
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
					m[0] = '\0';
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

int numbcl = 0;
void print() {
	if (numbcl) printf("Клиент № %d подключён\n\n", numbcl);
	else printf("Нет подключений\n\n");
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
	int r = listen(s, 5);                                     //режим ожидания запросов от клиентов
	cout << "*---Сервер ожидает подключений---*" << endl << endl;
	while (true) {
		sockaddr_in remote;
		int j = sizeof(remote);
		SOCKET newS = accept(s, (struct sockaddr*)&remote, &j);
		numbcl++;
		print();
		_beginthread(mailWorking, 0, (void*)newS);  //создание потока(Начальный адрес процедуры, который начинает выполнение нового потока; размер стека нового потока или 0; список аргументов, передаваемый в новый поток, или NULL)
	}
	WSACleanup();  //прекращаем работу Winsock API
	return 0;
}