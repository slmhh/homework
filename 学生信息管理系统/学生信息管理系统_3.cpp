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
 
//ѧ������ 
class student {
	public:
		int id;  		//ѧ��	
		string name; 	//���� 
		string gender;  //�Ա� 
		int age;     	//���� 
		string major;   //רҵ
		int cla;	 	//�༶ 
		int score;   	//�ɼ� 
		
		friend class manage;
		//���ء�<�� 
		bool operator < (student a) {return this->score < a.score;}
		//���ء�>��
		bool operator > (student a) {return this->score > a.score;}
};

student temp;
list<student>* stu = new list<student>();  //˫������ 

//������������о�����
class undergraduate : public student{
	//���ء�<��
		int id;  		//ѧ��	
		string name; 	//���� 
		string gender;  //�Ա� 
		int age;     	//���� 
		string major;   //רҵ
		int cla;	 	//�༶ 
		int score;   	//�ɼ� 
		
		bool operator < (undergraduate a) {
			return this->score < a.score;
		}
	
		//���ء�>��
		bool operator > (undergraduate a) {
			return this->score > a.score;
		}
};

class master : public student{
		int id;  		//ѧ��	
		string name; 	//���� 
		string gender;  //�Ա� 
		int age;     	//���� 
		string major;   //רҵ
		int cla;	 	//�༶ 
		int score;   	//�ɼ� 
		//���ء�<�� 
		bool operator < (master a) {
			return this->score < a.score;
		}
	
		//���ء�>��
		bool operator > (master a) {
			return this->score > a.score;
		}
};


//������Ķ��� 
class manage{
	private:
		string password;
	public:
		manage(){password = "nanamichiaki";}
		void enterMenu();
		void Print();
		void Insert();
		void Delete();
		void Menu(int n = 1);
		void Modify();
		void Find();
		void Sort();
		void Other();
		
		
};
//�������ʵ�� 
//������� 
void manage::enterMenu(){
	string ansCode;
	system("cls");
	cout << "����������:";
	while(1){
		cin >> ansCode;
		if(ansCode == password){
			system("cls");
			cout << "����ɹ�!!\n";
			break;
		}
		else{
			cout << "������󣡣�\n";
			cout << "��������������:";
		}
	}
}

//�˵� 
void manage::Menu(int n) {
	switch(n){
		case 1:
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
			break;
		//��ѯ�˵� 
		case 2:
			cout << "========================ѧ����Ϣ����ϵͳ========================\n";
			cout << "----------------------------��ѯ��Ϣ----------------------------\n";
			cout << "\n";
			cout << "               1.��ѧ�Ų�ѯ\n";
			cout << "\n";
			cout << "               2.��������ѯ\n";
			cout << "\n";
			cout << "               3.���༶��ѯ\n";
			cout << "\n";
			cout << "\n";
			cout << "----------------------------------------------------------------\n";
			break;
		//ɾ���˵�
		case 3:
			cout << "========================ѧ����Ϣ����ϵͳ========================\n";
			cout << "----------------------------ɾ����Ϣ----------------------------\n";
			cout << "\n";
			cout << "               1.��ѧ�Ų�ѯ\n";
			cout << "\n";
			cout << "\n";
			cout << "\n";
			cout << "               2.������ɾ��\n";
			cout << "\n";
			cout << "\n";
			cout << "----------------------------------------------------------------\n";
			break;
		case 4:
			cout << "========================ѧ����Ϣ����ϵͳ========================\n";
			cout << "----------------------------������Ϣ----------------------------\n";
			cout << "\n";
			cout << "               1.��ƽ���ɼ�\n";
			cout << "\n";
			cout << "               2.�Է�������\n";
			cout << "\n";
			cout << "               3.�������������\n";
			cout << "\n";
			cout << "\n";
			cout << "----------------------------------------------------------------\n";
			break;
		case 5:
			cout << "========================ѧ����Ϣ����ϵͳ========================\n";
			cout << "----------------------------����ѡ��----------------------------\n";
			cout << "\n";
			cout << "               1.�󱾿�������\n";
			cout << "\n";
			cout << "               2.���о�������\n";
			cout << "\n";
			cout << "               3.��༶����\n";
			cout << "\n";
			cout << "\n";
			cout << "----------------------------------------------------------------\n";
			break;
		default: break;
	}
}

//��ʾ
void manage::Print() {
	if (stu->empty()) {
		cout << "��δ����������Ϣ...\n";
		return;
	}
	system("cls");
	cout << "----------------------------------------------------------------\n";
	cout << "|  ѧ��  |    ����    |�Ա�| ���� |    רҵ    | �༶ |  �ɼ�  |\n";
	for (list<class student>::iterator it = stu->begin(); it != stu->end(); it++) {
		cout << "----------------------------------------------------------------\n";
		cout << "|" << setw(8) << (*it).id << "|" << setw(12) << (*it).name << "|" << setw(4) << (*it).gender << "|" << setw(6) << (*it).age << "|" << setw(12) << (*it).major << "|" << setw(6) << (*it).cla << "|" << setw(8) << (*it).score << "|\n";
	}
	cout << "----------------------------------------------------------------\n";
}

//�� 
void manage::Insert() {
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
void manage::Delete() {
	
	if (stu->empty()) {
		cout << "��δ����������Ϣ...\n";
		return;
	}
	

	int flag1;
	system("cls");
	Menu(3);
	cout << "����������ʹ�õĹ��ܣ�";
 	cin >> flag1;
	
	switch(flag1){
		case 1:
			while (1) {
			int ID;
			int flag = 0;
			cout << "������Ҫɾ����ѧ��ѧ��(��1001):";
			cin >> ID;
			for (list<class student>::iterator it = stu->begin(); it != stu->end(); it++) {
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
			break;
		case 2:
			while (1) {
			string sname;
			int flag = 0;
			cout << "������Ҫɾ����ѧ������:";
			cin >> sname;
			for (list<class student>::iterator it = stu->begin(); it != stu->end(); it++) {
				if (sname == (*it).name) {
					stu->erase(it);
					flag = 1;
					break;
				}
			}
			if (flag == 1) cout << "����Ϊ" << sname << "��ѧ����Ϣ�ѱ�ɾ��\n";
			else cout << "û���ҵ�����Ϊ" << sname << "��ѧ����Ϣ\n";
			cout << "�Ƿ����ɾ��(y/n):";
			cin >> ans;
			if (ans != 'y') break;
			}
			break;
		default: break;
	}
	while (1) {
		int ID;
		int flag = 0;
		cout << "������Ҫɾ����ѧ��ѧ��(��1001):";
		cin >> ID;
		for (list<class student>::iterator it = stu->begin(); it != stu->end(); it++) {
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
void manage::Modify() {
	if (stu->empty()) {
		cout << "��δ����������Ϣ...\n";
		return;
	}
	while (1) {
		int ID, flag = 0;
		cout << "������Ҫ�޸ĵ�ѧ����ѧ�ţ�";
		cin >> ID;
		for (list<class student>::iterator it = stu->begin(); it != stu->end(); it++) {
			if (ID == (*it).id) {
				cout << "���ҵ���ѧ�������޸ģ�\n";
				cout << "������ѧ��(��1001):";
				cin >> (*it).id;
				cout << "�������޸ĵ�����:";
				cin >> (*it).name;
				cout << "�������޸ĵ��Ա�(man = 1/woman = 2):";
				cin >> (*it).gender;
				if((*it).gender == "1") (*it).gender = "��";
				else (*it).gender = "Ů"; 
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
void manage::Find() {
	int flag1;
 	
	if (stu->empty()) {
		cout << "��δ����������Ϣ...\n";
		return;
	}
	
	
	system("cls");
 	Menu(2);
 	cout << "����������ʹ�õĹ��ܣ�";
 	cin >> flag1;
 	
 	switch(flag1){
		case 1:
			while (1) {
				int ID, flag = 0;
				cout << "������ѧ��ѧ��(��1001):";
				cin >> ID;
				for (list<class student>::iterator it = stu->begin(); it != stu->end(); it++) {
					if (ID == (*it).id) {
						if(flag == 0){
							flag = 1;
							cout << "----------------------------------------------------------------\n";
							cout << "|  ѧ��  |    ����    |�Ա�| ���� |    רҵ    | �༶ |  �ɼ�  |\n";
							cout << "----------------------------------------------------------------\n";
						}
						cout << "|" << setw(8) << (*it).id << "|" << setw(12) << (*it).name << "|" << setw(4) << (*it).gender << "|" << setw(6) << (*it).age << "|" << setw(12) << (*it).major << "|" << setw(6) << (*it).cla << "|" << setw(8) << (*it).score << "|\n";
						cout << "----------------------------------------------------------------\n";
					}
				}
				if (flag == 0) cout << "δ�ҵ���ѧ����Ϣ\n";
				cout << "�Ƿ��������(y/n):";
				cin >> ans;
				if (ans != 'y') break;
			}
			break;
		case 2:
			while (1) {
				string 	sname;
				int flag = 0;
				cout << "������ѧ������:";
				cin >> sname;
				for (list<class student>::iterator it = stu->begin(); it != stu->end(); it++) {
					if (sname == (*it).name) {
						if(flag == 0){
							flag = 1;
							cout << "----------------------------------------------------------------\n";
							cout << "|  ѧ��  |    ����    |�Ա�| ���� |    רҵ    | �༶ |  �ɼ�  |\n";
							cout << "----------------------------------------------------------------\n";
						}
						cout << "|" << setw(8) << (*it).id << "|" << setw(12) << (*it).name << "|" << setw(4) << (*it).gender << "|" << setw(6) << (*it).age << "|" << setw(12) << (*it).major << "|" << setw(6) << (*it).cla << "|" << setw(8) << (*it).score << "|\n";
						cout << "----------------------------------------------------------------\n";
					}
				}
				if (flag == 0) cout << "δ�ҵ���ѧ����Ϣ\n";
				cout << "�Ƿ��������(y/n):";
				cin >> ans;
				if (ans != 'y') break;
			}
			break;
		case 3:
			while (1) {
				int scla,flag = 0;
				cout << "������ѧ���༶:";
				cin >> scla;
				for (list<class student>::iterator it = stu->begin(); it != stu->end(); it++) {
					if (scla == (*it).cla) {
						if(flag == 0){
							flag = 1;
							cout << "----------------------------------------------------------------\n";
							cout << "|  ѧ��  |    ����    |�Ա�| ���� |    רҵ    | �༶ |  �ɼ�  |\n";
							cout << "----------------------------------------------------------------\n";
						}
						cout << "|" << setw(8) << (*it).id << "|" << setw(12) << (*it).name << "|" << setw(4) << (*it).gender << "|" << setw(6) << (*it).age << "|" << setw(12) << (*it).major << "|" << setw(6) << (*it).cla << "|" << setw(8) << (*it).score << "|\n";
						cout << "----------------------------------------------------------------\n";
					}
				}
				if (flag == 0) cout << "δ�ҵ���ѧ����Ϣ\n";
				cout << "�Ƿ��������(y/n):";
				cin >> ans;
				if (ans != 'y') break;
			}
			break;
		default: break;	
		}
}


//����
bool compare(student a, student b) {
	return a > b;
}

//���� 
void manage::Sort() {
	/*if (stu->empty()) {
		cout << "��δ����������Ϣ...\n";
		return;
	}*/
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




void manage::Other(){
	if (stu->empty()) {
		cout << "��δ����������Ϣ...\n";
		return;
	}
	int flag1;
	system("cls");
 	Menu(2);
 	cout << "����������ʹ�õĹ��ܣ�";
 	cin >> flag1;
	
	switch(flag1){
		case 1:
			while(1){
				int sum = 0,n = 0;
				for (list<class student>::iterator it = stu->begin(); it != stu->end(); it++) {
					sum += (*it).score;
					n++;
				}
				cout << "��" << n << "��ѧ����ƽ���ɼ�Ϊ:" <<  sum / (n) << endl;
				cout << "�Ƿ��������(y/n):";
				cin >> ans;
				if (ans != 'y') break;
			}
			break;
		case 2:
			Sort();
			break;
		case 3:
			while(1){
				int count = 0,min,max;
				cout << "��������ҳɼ��½�:";
				cin >> min;
				cout << "��������ҳɼ��Ͻ�:";
				cin >> max;
				for (list<class student>::iterator it = stu->begin(); it != stu->end(); it++) {
					if((*it).score >= min && (*it).score <= max) count++;
				}
				cout << "�ɼ���" << min << "��" << max << "��ѧ������Ϊ" << count << endl;
				cout << "�Ƿ��������(y/n):";
				cin >> ans;
				if (ans != 'y') break;
			}
			break;
		default: break;
		}
}



int main() {
	manage a;
	a.enterMenu();
	a.Menu(5);
	cout << "����������ʹ�õĹ��ܣ�";
	cin >> choice;
	//û��ø���ôʵ�ַ������ 
	switch(choice){
		case 1:break;
		case 2:break;
		case 3:break;
		default:break;
	}
	while (1) {
		a.Menu(1);
		cout << "����������ʹ�õĹ��ܣ�";
		cin >> choice;
		switch (choice) {
			case 1: a.Insert(); break;
			case 2: a.Find(); break;
			case 3: a.Delete(); break;
			case 4: a.Modify(); break;
			case 5: a.Sort();break;
			case 6: a.Print(); break;
			default: break;
		}
		system("cls");
		a.Menu();
		cout << "�Ƿ����(y/n):";
		cin >> ans;
		if (ans != 'y') break;
		system("cls");
	}

	cout << endl;
	return 0;
}
