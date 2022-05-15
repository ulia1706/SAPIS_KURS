#define _AFXDLL 
#include <iostream>
#include <afx.h> 
#include <winsock2.h>
#include <process.h>
#include <string>
#include <fstream>
#include <list>
#include<iomanip>

using namespace std;

CFile f;                 //???
CFileException ex;
//+++
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
	int GetStatus() { return status; }
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
	char pos[50]; //должность
	int exp; //опыт
public:
	Expert() {
		strcpy_s(F, "-");
		strcpy_s(I, "-");
		strcpy_s(O, "-");
		strcpy_s(pos, "-");
		exp = 0;
	}
	//методы эксперта
	friend bool operator<(Expert e1, Expert e2);
	void SetPos(char* str) { strcpy_s(pos, str); }
	char* GetPos() { return pos; }
	void SetExp(int a) { exp = a; }
	int GetExp() { return exp; }
	void WriteFile(list<Expert> lst);
	void WriteTable(list<Expert> lst);
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
	char city[50]; //название города локации поставщика
	char phone[50]; //контактный телефон
	char email[50]; //электронная почта
	int contracts; //количество действующих договоров
	//список договоров
	//список заявок
	float min_price; //цена минимальной разовой закупки
	      //договор с нашим автосалоном
public:
	Contract c;
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
	void WriteTableAdm(list<Supplier> lst);
	void Sorting(list<Supplier> lst);
	int Filtr_1(list<Supplier>lst, char* str);
	int Filtr_2(list<Supplier> lst, float a, float b);
	int Find(list<Supplier> lst, char* str);
	int FindAdm(list<Supplier> lst, char* str);
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

class Request{}; //инфа и методы о заявках для обеих сторон

class Method{}; //поля и методы, связанные с методом ранга, включён в класс эксперты

void MakeExpList(list<Expert> &lst) {
	ifstream file("Experts.txt");
	ifstream file1("Exp_log_passw.txt");
	char str[50];
	Expert e;
	if (!file.is_open() || file.peek() == EOF) { //проверяем, связан ли наш поток с открываемым файлом
		cout << "Возникла проблема при открытии файла или файл пустой\n" << endl;
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
void Make1Table(int arr[50][50], int a, int b) { //a - supps; b- experts
	//шапка таблицы
	cout << "|" << setw(8) << setfill('-')<<"|";
	for (int i = 0; i < a; i++) {
		cout << setw(5)<<"|";
	}
	cout << endl;
	cout << "|" << setw(6) << setfill(' ') << "Zi/Эi" << setw(2) << "|";
	for (int i = 0; i < a; i++) {
		cout << " Z" << i + 1 << " |";
	}
	cout << endl;
	cout << "|" << setw(8) << setfill('-') << "|";
	for (int i = 0; i < a; i++) {
		cout << setw(5) << "|";
	}
	cout << endl;
    //
	for (int i = 0; i < b; i++) {
		cout << "|" << setw(4) << setfill(' ') << "Э" << i + 1 << setw(3) << "|";
		for (int j = 0; j < a; j++) {
			cout << setw(3) << arr[i][j] << setw(2) << "|";
		}
		cout << endl;
		cout << "|" << setw(8) << setfill('-') << "|";
		for (int i = 0; i < a; i++) {
			cout << setw(5) << "|";
		}
		cout << endl;
	}
	
}

void Make2Table(int arr[50][50], int a, int b) {//a - supps; b- experts
	//шапка таблицы
	cout << "|" << setw(8) << setfill('-') << "|";
	for (int i = 0; i < a; i++) {
		cout << setw(8) << "|";
	}
	cout << endl;
	cout << "|" << setw(6) << setfill(' ') << "Zi/Эi" << setw(2) << "|";
	for (int i = 0; i < a; i++) {
		cout << "   Z" << i + 1 << "  |";
	}
	cout << endl;
	cout << "|" << setw(8) << setfill('-') << "|";
	for (int i = 0; i < a; i++) {
		cout << setw(8) << "|";
	}
	cout << endl;
	//
	int total;
	for (int i = 0; i < b; i++) {
		total = 0;
		for (int m = 0; m < a; m++) {
			total = total + arr[i][m];
		}
		cout << "|" << setw(4) << setfill(' ') << "Э" << i + 1 << setw(3) << "|";
		for (int j = 0; j < a; j++) {
			cout << setw(3) << arr[i][j]<<"/"<<setw(2)<<total << setw(2) << "|";
		}
		cout << endl;
		cout << "|" << setw(8) << setfill('-') << "|";
		for (int i = 0; i < a; i++) {
			cout << setw(8) << "|";
		}
		cout << endl;
	}

}

int Make3Table(int arr[50][50], int a, int b) {
	float array[50][50];
	float weight[100];
	for (int i = 0; i < a; i++) {
		cout <<"|" << setw(8) <<setfill('-') << "|";
	}
	cout << endl;
	int total;
	for (int i = 0; i < b; i++) {   //вычислили дробные значения для каждой штуки
		total = 0;
		for (int m = 0; m < a; m++) {
			total = total + arr[i][m];
			array[i][m] = arr[i][m] / total;
		}
	}
	for (int i = 0; i < a; i++) { //цикл прохождения по поставщикам
		weight[i] = 0;
		for (int f = 0; f < b; f++) { //цикл прохождения по экспертам
			weight[i] = weight[i] + array[f][i];
		}
		weight[i] = weight[i] / b;
	}
}


void mailWorking(void* newS) {
	Supplier supp; 
	Expert expert;
	list<Expert> lexpert;
	list<Expert>::iterator pexpert;
	list<Supplier> lsupp;
	list<Supplier> ::iterator psupp;
	int c, c1 = 0, c2 = 0, c3 = 0;
	int flag = 0;
	char p[500], com[500], k[500], m[500];
	com[0] = '\0'; p[0] = '\0'; k[0] = '\0'; m[0] = '\0';
	cout << "Сервер работает.\n";
	/*cout <<  "size = " << lsupp.size() << endl;*/
	MakeSuppList(lsupp);
	MakeExpList(lexpert);
	//cout << lsupp.size() << endl;
	//cout << "фУНКЦИЯ ЗАВЕРШЕНА МЭЙКСАПЛИСТ" << endl;
	/*for (psupp = lsupp.begin(); psupp != lsupp.end(); psupp++) {
		cout << psupp->GetPassword() << endl;
	}*/
	while (1) 
	{
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
					while (c2 != 5) {
						strcpy_s(p, "РАБОТА С ПОСТАВЩИКАМИ:\n 1. Просмотреть список имеющихся поставщиков.\n 2. Найти информацию о конкретном поставщике.\n 3. Заключить договор.\n 4. Расторгнуть договор. \n 5. Вернуться в меню администратора.\n");
						send((SOCKET)newS, p, sizeof(p), 0);
						recv((SOCKET)newS, m, sizeof(m), 0);
						c2 = atoi(m);
						switch (c2) {
						case 1: {
							strcpy_s(p, "1");
							send((SOCKET)newS, p, sizeof(p), 0);
							supp.WriteTable(lsupp);
							supp.WriteTableAdm(lsupp);
							strcpy_s(p, "1");
							send((SOCKET)newS, p, sizeof(p), 0);
							supp.Sorting(lsupp);
							ifstream file("Supp_table_adm.txt");
							while (!file.eof()) {
								cout << "Hi, babe" << endl;
								k[0] = '\0';
								file.getline(k, 256, '\n');
								m[0] = '\0';
								strcpy_s(m, "конец");
								if (file.eof()) 	send((SOCKET)newS, m, sizeof(m), 0);
								else send((SOCKET)newS, k, sizeof(k), 0);
								cout << k << endl;
							}
							k[0] = '\0';
							cout << "вышел из цикла" << endl;
							file.close();
							m[0] = '\0';
							int u = 0;
							for (psupp = lsupp.begin(); psupp != lsupp.end(); psupp++) {
								u++;
								if (u == 2) { psupp->c.SetStatus(u); }
								cout << psupp->c.GetStatus() << endl;
							}
							/*cout<<supp(3, lsupp).GetF()<<endl;
							cout << "fff" << endl;*/
							break;
						}
						case 2: {
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
				case 2: 
				{
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
									expert.Sorting(lexpert);
									ifstream file("Experts_buf.txt");
									while (!file.eof()) {
										cout << "Hi, babe" << endl;
										k[0] = '\0';
										file.getline(k, 256, '\n');
										m[0] = '\0';
										strcpy_s(m, "конец");
										if (file.eof()) 	send((SOCKET)newS, m, sizeof(m), 0);
										else send((SOCKET)newS, k, sizeof(k), 0);
										cout << k << endl;
									}
									k[0] = '\0';
									cout << "вышел из цикла" << endl;
									file.close();
									m[0] = '\0';
									break;
								}
								case 2: {
									strcpy_s(p, "2");
									send((SOCKET)newS, p, sizeof(p), 0);
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
								}
							}
							c3 = 0;
							break;
						}
						case 2: {
							p[0] = '\0';
							strcpy_s(p, "2");
							send((SOCKET)newS, p, sizeof(p), 0);

							//получение фамилии
							com[0] = '\0';
							recv((SOCKET)newS, com, sizeof(com), 0);
							expert.SetF(com);
							com[0] = '\0';
							//получение имени эксперта
							recv((SOCKET)newS, com, sizeof(com), 0);
							expert.SetI(com);
							com[0] = '\0';
							//получение отчества эксперта
							recv((SOCKET)newS, com, sizeof(com), 0);
							expert.SetO(com);
							com[0] = '\0';
							//получение отчества эксперта
							recv((SOCKET)newS, com, sizeof(com), 0);
							expert.SetPos(com);
							com[0] = '\0';
							//получение количество действующих контрактов
							recv((SOCKET)newS, com, sizeof(com), 0);
							int d;
							d = atoi(com);
							expert.SetExp(d);
							com[0] = '\0';
							//получение логина
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

							//получение пароль
							recv((SOCKET)newS, com, sizeof(com), 0);
							expert.SetPassword(com);
							com[0] = '\0';
                            //добавление нового эксперта в список
							lexpert.push_back(expert);
							expert.WriteFile(lexpert);
							expert.WriteTable(lexpert);
							break;
						}
						case 3: {
							strcpy_s(p, "3");
							send((SOCKET)newS, p, sizeof(p), 0);
							p[0] = '\0';
							m[0] = '\0';
							recv((SOCKET)newS, m, sizeof(m), 0);
								cout << m << endl;
								for (pexpert = lexpert.begin(); pexpert != lexpert.end(); pexpert++) {
									if (strcmp(pexpert->GetF(), m) == 0) {
										cout << "Мы здесь" << endl;
										lexpert.erase(pexpert);
										break;
									}
								}
								expert.WriteFile(lexpert);
								expert.WriteTable(lexpert);
								m[0] = '\0';
								strcpy_s(m, "Аккаунт успешно удалён!\n");
								send((SOCKET)newS, m, sizeof(m), 0);
								m[0] = '\0';
								break;
					    }
						case 4: {
							strcpy_s(p, "4");
							send((SOCKET)newS, p, sizeof(p), 0);
							//редактирование экспертов
							p[0] = '\0';
							k[0] = '\0';
							int qw;
							recv((SOCKET)newS, k, sizeof(k), 0); //фамилия
							m[0] = '\0';
							recv((SOCKET)newS, m, sizeof(m), 0); //номер пункта меню
							int ll = 0;
							for (pexpert = lexpert.begin(); pexpert != lexpert.end(); pexpert++) {
								if (strcmp(pexpert->GetF(), k) == 0) {
									cout << "Мы здесь" << endl;
									//lsupp.erase(psupp);
									break;
								}
								ll++;
							}
							cout << pexpert->GetF() << endl;
							cout << "Он седьмой по счёту  " << ll << endl;
							qw = atoi(m);
							switch (qw) {
							case 1: {
								p[0] = '\0';
								strcpy_s(p, "1");
								send((SOCKET)newS, p, sizeof(p), 0);
								com[0] = '\0';
								recv((SOCKET)newS, com, sizeof(com), 0);
								pexpert->SetF(com);
								//cout << supp(ll, lsupp).Get_nameorg() << endl;
								com[0] = '\0';
								expert.WriteFile(lexpert);
								expert.WriteTable(lexpert);
								//supp.WriteTableAdm(lsupp);
								break;
							}
							case 2: {
								p[0] = '\0';
								strcpy_s(p, "2");
								send((SOCKET)newS, p, sizeof(p), 0);
								com[0] = '\0';
								recv((SOCKET)newS, com, sizeof(com), 0);
								pexpert->SetI(com);
								com[0] = '\0';
								expert.WriteFile(lexpert);
								expert.WriteTable(lexpert);
								//expert.WriteTableAdm(lsupp);
								break;
							}
							case 3: {
								p[0] = '\0';
								strcpy_s(p, "3");
								send((SOCKET)newS, p, sizeof(p), 0);
								com[0] = '\0';
								recv((SOCKET)newS, com, sizeof(com), 0);
								pexpert->SetO(com);
								com[0] = '\0';
								expert.WriteFile(lexpert);
								expert.WriteTable(lexpert);
								//supp.WriteTableAdm(lsupp);
								break;
							}
							case 4: {
								p[0] = '\0';
								strcpy_s(p, "4");
								send((SOCKET)newS, p, sizeof(p), 0);
								com[0] = '\0';
								recv((SOCKET)newS, com, sizeof(com), 0);
								pexpert->SetPos(com);
								com[0] = '\0';
								expert.WriteFile(lexpert);
								expert.WriteTable(lexpert);
								//supp.WriteTableAdm(lsupp);
								break;
							}
							case 5: {
								int bb;
								p[0] = '\0';
								strcpy_s(p, "5");
								com[0] = '\0';
								send((SOCKET)newS, p, sizeof(p), 0);
								recv((SOCKET)newS, com, sizeof(com), 0);
								bb = atoi(com);
								pexpert->SetExp(bb);
								com[0] = '\0';
								expert.WriteFile(lexpert);
								expert.WriteTable(lexpert);
								//supp.WriteTableAdm(lsupp);
								break;
							}
							case 6: {
								break;
							}
								  
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
					int ps, exn;
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


