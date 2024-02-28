#include<iostream>
#include<vector>
#include<queue>
#include<map>
using namespace std;

int n = 3;
//���㿵��չ��
int factorial[10] = { 1,1,2,6,24,120,720,5040,40320,362880 };

void swap(int* a, int* b) {
	int* c = a;
	a = b;
	b = c;
}

int Cantor(vector<vector<int>>& nums) {
	int x = 0;
	vector<int> A(n * n, 0);
	for (int i = 0; i < n * n; i++)
		for (int j = i + 1; j < n * n; j++)
			if (nums[j / n][j % n] < nums[i / n][i % n]) A[i]++;

	for (int i = 0; i < n * n; i++)
		x += A[i] * factorial[n * n - i - 1];
	return x;
}

struct moveto {
	int zreox;
	int zeroy;
	string direction;
};

string dir[4] = { "right","left","up","down" };

class EightPuzzle {
public:
	vector<vector<int>> S; //�Ź���
	moveto step;
	int can;       //����չ��ֵ
	bool tag;      //���޽�
	EightPuzzle() { can = -1; };
	EightPuzzle(vector<vector<int>>& input);
	void print();
	void BfsSolve(EightPuzzle& target);
	void PrintSolve(EightPuzzle target);
};

EightPuzzle::EightPuzzle(vector<vector<int>>& input) {
	S.resize(n, vector<int>(n));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			S[i][j] = input[i][j];
	can = Cantor(S);
	step.direction = "start";
}

void EightPuzzle::print() {
	for (int i = 0; i < S.size(); i++) {
		for (int j = 0; j < S[0].size(); j++) {
			if (S[i][j]) cout << S[i][j] << " ";
			else cout << "  ";
		}
		cout << "\n";
	}
	cout << "\n";
}

int movex[4] = { 0,0,1,-1 }, movey[4] = { 1,-1,0,0 };  //�ĸ������ƶ�
vector<EightPuzzle> parent(365000); //��¼���ڵ�
bool st[365000] = { 0 };
void EightPuzzle::BfsSolve(EightPuzzle& target) {
	if (can == target.can) {
		tag = true;
		return;
	}
	queue<EightPuzzle> q;
	q.push(*this);
	parent[can] = *this;
	st[can]++;
	while (!q.empty()) {
		EightPuzzle temp = q.front();
		q.pop();
		vector<vector<int>> ts = temp.S;
		//Ѱ�ҿո��λ��
		int x, y;
		for (int i = 0; i < n * n; i++)
			if (ts[i / n][i % n] == 0) {
				x = i / n;
				y = i % n;
				break;
			}
		//���ĸ����򽻻�
		for (int i = 0; i < 4; i++) {
			//�ж��ƶ��ĺϷ���
			if (x + movex[i] >= 0 && y + movey[i] >= 0 && x + movex[i] < n && y + movey[i] < n) {
				swap(ts[x + movex[i]][y + movey[i]], ts[x][y]);    //�ƶ�
				EightPuzzle s(ts);
				swap(ts[x + movex[i]][y + movey[i]], ts[x][y]);    //��λ
				//�ж��Ƿ񱻼�����
				if (st[s.can]) continue;
				st[s.can] = true;
				parent[s.can] = temp;
				s.step = { x,y, dir[i] };
				//�ж��Ƿ�ִ���̬
				if (s.can == target.can) {
					tag = true;
					target = s;
					return;
				}
				q.push(s);
			}
		}
	}
	tag = false;
}

void EightPuzzle::PrintSolve(EightPuzzle target) {
	if (!tag) {
		cout << "��״̬�޽�\n";
		return;
	}
	EightPuzzle temp = target;
	vector<EightPuzzle> ans;
	while (temp.can != can) {
		ans.push_back(temp);
		temp = parent[temp.can];
	}

	cout << "���ٲ��ⷨ��" << ans.size() << "��,���岽������:\n";
	cout << step.direction << "\n";
	print();
	for (int i = ans.size() - 1; i >= 0; i--) {
		cout << ans[i].step.direction << "\n";
		ans[i].print();
	}
	cout << "finish\n";
}

int main() {
	vector<vector<int>> input(n, vector<int>(n)), target = { {1,2,3},{8,0,4},{7,6,5} };
	cout << "�������ʼ�Ź���(��0��ʾ�ո�):\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> input[i][j];
		}
	}
	EightPuzzle S0(input);
	EightPuzzle Sg(target);
	cout << "��ʼ״̬Ϊ\n";
	S0.print();
	cout << "Ŀ��״̬Ϊ\n";
	Sg.print();
	S0.BfsSolve(Sg);
	S0.PrintSolve(Sg);
	return 0;
}

//2 8 3 1 0 4 7 6 5
//1 2 3 8 0 4 7 6 5
//2 1 3 8 0 4 7 6 5
