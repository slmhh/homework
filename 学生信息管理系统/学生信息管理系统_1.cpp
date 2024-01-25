#include<iostream>
#include<string>
#include<list>
#include<stdlib.h>
#include<algorithm>
#include<iomanip>
using namespace std;

void Print();
void Insert();
void Delete();
void Menu();
void Modify();
void Find();
void Sort();


int choice;
char ans;

struct student {
	int id;  		//ѧ��	
	string name; 	//���� 
	string gender;  //�Ա� 
	int age;     	//���� 
	string major;   //רҵ
	int cla;	 	//�༶ 
	int score;   	//�ɼ� 

	//���ء�<�� 
	bool operator < (student a) {
		return this->score < a.score;
	}

	//���ء�>��
	bool operator > (student a) {
		return this->score > a.score;
	}
}temp;

list<student>* stu = new list<student>();  //˫������ 

//�˵� 
void Menu() {
	cout << "========================ѧ����Ϣ����ϵͳ========================\n";
	cout << "----------------------------���ܲ˵�----------------------------\n";
	cout << "\n";
	cout << "               1.¼��ѧ����Ϣ\n";
	cout << "               2.����ѧ����Ϣ\n";
	cout << "               3.ɾ��ѧ����Ϣ\n";
	cout << "               4.�޸�ѧ����Ϣ\n";
	cout << "               5.��ѧ����Ϣ����\n";
	cout << "               6.��ʾ����ѧ����Ϣ\n";
	cout << "\n";
	cout << "----------------------------------------------------------------\n";
}



//��ʾ
void Print() {
	if (stu->empty()) {
		cout << "��δ����������Ϣ...\n";
		return;
	}
	system("cls");
	cout << "----------------------------------------------------------------\n";
	cout << "|  ѧ��  |    ����    |�Ա�| ���� |    רҵ    | �༶ |  �ɼ�  |\n";
	for (list<struct student>::iterator it = stu->begin(); it != stu->end(); it++) {
		cout << "----------------------------------------------------------------\n";
		cout << "|" << setw(8) << (*it).id << "|" << setw(12) << (*it).name << "|" << setw(4) << (*it).gender << "|" << setw(6) << (*it).age << "|" << setw(12) << (*it).major << "|" << setw(6) << (*it).cla << "|" << setw(8) << (*it).score << "|\n";
	}
	cout << "----------------------------------------------------------------\n";
}




//�� 
void Insert() {
	while (1) {
		cout << "������ѧ��(��1001):";
		cin >> temp.id;
		cout << "����������:";
		cin >> temp.name;
		cout << "�������Ա�(man/woman):";
		cin >> temp.gender;
		cout << "����������:";
		cin >> temp.age;
		cout << "������רҵ:";
		cin >> temp.major;
		cout << "������༶:";
		cin >> temp.cla;
		cout << "������ɼ�:";
		cin >> temp.score;

		stu->push_back(temp);
		system("cls");
		Menu();
		cout << "��Ϣ¼��ɹ�!!!\n";
		cout << "�Ƿ����¼��(y/n):";
		cin >> ans;
		if (ans != 'y') break;
	}
}



//ɾ
void Delete() {
	if (stu->empty()) {
		cout << "��δ����������Ϣ...\n";
		return;
	}
	while (1) {
		int ID;
		int flag = 0;
		cout << "������Ҫɾ����ѧ��ѧ��(��1001):";
		cin >> ID;
		for (list<struct student>::iterator it = stu->begin(); it != stu->end(); it++) {
			if (ID == (*it).id) {
				stu->erase(it);
				flag = 1;
				break;
			}
		}
		if (flag == 1) cout << "ѧ��Ϊ" << ID << "��ѧ����Ϣ�ѱ�ɾ��\n";
		else cout << "û���ҵ�ѧ��Ϊ" << ID << "��ѧ����Ϣ\n";
		cout << "�Ƿ����ɾ��(y/n):";
		cin >> ans;
		if (ans != 'y') break;
	}

}

//�޸�
void Modify() {
	if (stu->empty()) {
		cout << "��δ����������Ϣ...\n";
		return;
	}
	while (1) {
		int ID, flag = 0;
		cout << "������Ҫ�޸ĵ�ѧ����ѧ�ţ�";
		cin >> ID;
		for (list<struct student>::iterator it = stu->begin(); it != stu->end(); it++) {
			if (ID == (*it).id) {
				cout << "���ҵ���ѧ�������޸ģ�\n";
				cout << "������ѧ��(��1001):";
				cin >> (*it).id;
				cout << "�������޸ĵ�����:";
				cin >> (*it).name;
				cout << "�������޸ĵ��Ա�(man/woman):";
				cin >> (*it).gender;
				cout << "�������޸ĵ�����:";
				cin >> (*it).age;
				cout << "�������޸ĵ�רҵ:";
				cin >> (*it).major;
				cout << "�������޸ĵİ༶:";
				cin >> (*it).cla;
				cout << "�������޸ĵĳɼ�:";
				cin >> (*it).score;
				flag = 1;
				break;
			}
		}
		if (flag == 0) cout << "δ�ҵ���ѧ����Ϣ\n";
		cout << "�Ƿ�����޸�(y/n):";
		cin >> ans;
		if (ans != 'y') break;
	}
}

//����
void Find() {
	if (stu->empty()) {
		cout << "��δ����������Ϣ...\n";
		return;
	}
	system("cls");
	while (1) {
		int ID, flag = 0;
		cout << "������ѧ��ѧ��(��1001):";
		cin >> ID;
		for (list<struct student>::iterator it = stu->begin(); it != stu->end(); it++) {
			if (ID == (*it).id) {
				cout << "----------------------------------------------------------------\n";
				cout << "|  ѧ��  |    ����    |�Ա�| ���� |    רҵ    | �༶ |  �ɼ�  |\n";
				cout << "----------------------------------------------------------------\n";
				cout << "|" << setw(8) << (*it).id << "|" << setw(12) << (*it).name << "|" << setw(4) << (*it).gender << "|" << setw(6) << (*it).age << "|" << setw(12) << (*it).major << "|" << setw(6) << (*it).cla << "|" << setw(8) << (*it).score << "|\n";
				cout << "----------------------------------------------------------------\n";
				break;
			}
		}
		if (flag == 0) cout << "δ�ҵ���ѧ����Ϣ\n";
		cout << "�Ƿ��������(y/n):";
		cin >> ans;
		if (ans != 'y') break;
	}
}


//����
bool compare(student a, student b) {
	return a > b;
}


//���� 
void Sort() {
	if (stu->empty()) {
		cout << "��δ����������Ϣ...\n";
		return;
	}
	cout << "����������1������������2:";
	cin >> ans;
	if (ans == 1) {
		stu->sort();
	}
	else if (ans == 2) {
		stu->sort(compare);
	}
	system("cls");
	Print();
}




int main() {
	while (1) {
		Menu();
		cout << "����������ʹ�õĹ��ܣ�";
		cin >> choice;
		switch (choice) {
		case 1: Insert(); break;
		case 2: Find(); break;
		case 3: Delete(); break;
		case 4: Modify(); break;
		case 5: Sort();break;
		case 6: Print(); break;
		default: break;
		}
		system("cls");
		Menu();
		cout << "�Ƿ����(y/n):";
		cin >> ans;
		if (ans != 'y') break;
		system("cls");
	}

	cout << endl;
	return 0;
}
