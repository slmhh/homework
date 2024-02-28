#include<iostream>
#include<vector>
#include<queue>
#include<ctime>
#include<iomanip>
using namespace std;

int n = 3;  //����
//��̬
vector<vector<int>> target = {{1,2,3},
                              {8,0,4},
                              {7,6,5}};
//���㿵��չ��
int factorial[10] = { 1,1,2,6,24,120,720,5040,40320,362880 };

void swap(int* a, int* b) {
	int* c = a;
	a = b;
	b = c;
}

int Cantor(vector<vector<int> >& nums) {
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
	moveto step;    //�ƶ���ʽ
	int can;       //����չ��ֵ
	bool tag;      //���޽�
    int deep;      //�������ʼ̬����̬���ۺ���g(x)
	EightPuzzle() { can = -1; };
	EightPuzzle(vector<vector<int >>& input);
	void print();
	void BfsSolve(EightPuzzle& Sg);
	void PrintSolve(EightPuzzle Sg);
    int h(); //��̬����̬���ۺ���h(x),δ��λ�������
    friend bool operator < (EightPuzzle a, EightPuzzle b){ return a.deep + a.h() > b.deep + b.h(); }
};

int EightPuzzle::h(){
    int cnt = 0;
    for(int i = 0;i < n;i++)
        for(int j = 0;j < n;j++)
            if(S[i][j] != target[i][j]) cnt++;
    return cnt;
}

EightPuzzle::EightPuzzle(vector<vector<int>>& input) {
	S.resize(n, vector<int>(n));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			S[i][j] = input[i][j];
	can = Cantor(S);
    deep = 0;
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
int st[365000];   //��¼�Ƿ�������
void EightPuzzle::BfsSolve(EightPuzzle& Sg) {
    priority_queue<EightPuzzle> q;
	q.push(*this);
	parent[can] = *this;
	st[can] = 1;
	while (!q.empty()) {
		EightPuzzle temp = q.top();
		q.pop();
        //�ж��Ƿ�ִ���̬
		if (temp.can == Sg.can) {
			tag = true;
			Sg = temp;
			return;
		}
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
				if (st[s.can] && st[s.can] <= st[temp.can] + 1) continue;
				st[s.can] = st[temp.can] + 1;
				parent[s.can] = temp;
				s.step = { x,y, dir[i] };
                s.deep = temp.deep + 1;
				q.push(s);
			}
		}
	}
	tag = false;
}

void EightPuzzle::PrintSolve(EightPuzzle Sg) {
	if (!tag) {
		cout << "��״̬�޽�\n";
		return;
	}
	EightPuzzle temp = Sg;
	vector<EightPuzzle> ans;
	while (temp.can != can) {
		ans.push_back(temp);
		temp = parent[temp.can];
	}

	cout << "���ٲ��ⷨ��" << Sg.deep << "��,���岽������:\n";
	cout << step.direction << "\n";
	print();
	for (int i = ans.size() - 1; i >= 0; i--) {
        cout << "-----step" << ans.size() - i << "----\n"; 
		cout << ans[i].step.direction << "\n";
		ans[i].print();
	}
	cout << "finish\n";
}

int main() {
	vector<vector<int>> input(n, vector<int>(n));
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
    clock_t start,end;
    start = clock();
	S0.BfsSolve(Sg);
    end = clock();
	S0.PrintSolve(Sg);
    cout << "��ʱ��" << fixed << setprecision(10) << (double)(end - start) / CLOCKS_PER_SEC << "s\n"; 
	return 0;
}

//2 8 3 1 0 4 7 6 5
//1 2 3 8 0 4 7 6 5
//2 1 3 8 0 4 7 6 5

//hack
//7 6 5 4 2 0 3 8 1 
//29
//8 2 1 3 0 4 6 5 7
//20
//2 0 1 5 3 4 7 8 6
//19
