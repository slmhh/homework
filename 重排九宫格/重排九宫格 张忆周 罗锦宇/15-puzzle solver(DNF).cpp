#include<iostream>
#include<vector>
#include<ctime>
#include<iomanip>
#include<map>
#include<algorithm>
using namespace std;
int n = 4;  //����
string dir[4] = { "right","left","up","down" }; //�ƶ�����
vector<vector<int>> target = { {1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,0} };//��̬

//���㿵��չ��
long long factorial[16] = { 1,1,2,6,24,120,720,5040,40320,362880,39916800,479001600,6227020800,87178291200,1307674368000,20922789888000};
long long Cantor(vector<vector<int> >& nums) {
	long long x = 0,a = 0;
	vector<long long> A;
	for (int i = 0; i < n * n; i++) {
		a = 0;
		for (int j = i + 1; j < n * n; j++)
			if (nums[j / n][j % n] < nums[i / n][i % n]) a++;
		A.push_back(a);
	}
	for (int i = 0; i < n * n; i++)
		x += A[i] * factorial[n * n - i - 1];
	return x;
}

class EightPuzzle {
private:
	vector<vector<int>> S; //�Ź���,��̬
	string direction;    //�ƶ�����
	long long can;       //����չ��ֵ
	int deep;
public:
	EightPuzzle() {};
	EightPuzzle(vector<vector<int >>& input);
	void Print();
	void PrintSolve(EightPuzzle Sg);
	void IDAstar(EightPuzzle Sg);
	bool dfs(EightPuzzle& now,int h, EightPuzzle& Sg);
	bool Sovleable();
};

bool EightPuzzle::Sovleable() {
	int inv = 0, x = 0;
	for (int i = 0; i < n * n; i++) {
		if (S[i / n][i % n] == 0) x = n - i / n;
		for (int j = i + 1; j < n * n; j++) {
			if (S[j / n][j % n] && S[i / n][i % n] && S[j / n][j % n] < S[i / n][i % n]) inv++;
		}
	}
	return (inv + x) & 1;
}

EightPuzzle::EightPuzzle(vector<vector<int>>& input) {
	S.resize(n, vector<int>(n));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			S[i][j] = input[i][j];
	can = Cantor(S);
	deep = 0;
	direction = "start";
}

void EightPuzzle::Print() {
	for (int i = 0; i < S.size(); i++) {
		for (int j = 0; j < S[0].size(); j++) {
			if (S[i][j]) printf("%3d ", S[i][j]);
			else printf("    ");
		}
		cout << "\n";
	}
	cout << "\n";
}

int movex[4] = { 0,0,1,-1 }, movey[4] = { 1,-1,0,0 };  //�ĸ������ƶ�
map<long long,EightPuzzle> parent; //��¼���ڵ�
int maxdeep;
void EightPuzzle::IDAstar(EightPuzzle Sg) {
	if (!Sovleable()) {   //�ж����޽�
		cout << "��״̬�޽�\n";
		return;
	}
	maxdeep = 0;
	while (!dfs(*this, -1, Sg)) {
		cout << "maxdeep = " << maxdeep << "\n";
		maxdeep++;
	}
	PrintSolve(Sg);
}

bool EightPuzzle::dfs(EightPuzzle& now, int last, EightPuzzle& Sg) {
	if (now.deep > maxdeep) return false;
	if (now.can == Sg.can) return true;

	EightPuzzle temp = now;
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
		if (i == last) continue;
		//�ж��ƶ��ĺϷ���
		if (x + movex[i] >= 0 && y + movey[i] >= 0 && x + movex[i] < n && y + movey[i] < n) {
			swap(ts[x + movex[i]][y + movey[i]], ts[x][y]);    //�ƶ�
			EightPuzzle s(ts);
			swap(ts[x + movex[i]][y + movey[i]], ts[x][y]);    //��λ
			s.deep = temp.deep + 1;
			parent[s.can] = temp;
			if (dfs(s, i, Sg)) {
				return true;
			}
		}
	}
	return false;
}

void EightPuzzle::PrintSolve(EightPuzzle Sg) {
	EightPuzzle temp = Sg;
	vector<EightPuzzle> ans;
	while (temp.can != can) {
		ans.push_back(temp);
		temp = parent[temp.can];
	}
	ans.push_back(*this);
	cout << "���ٲ��ⷨ��" << Sg.deep << "��,���岽������:\n";
	for (int i = ans.size() - 1; i >= 0; i--) {
		cout << "-----step" << ans.size() - 1 - i << "----\n";
		cout << ans[i].direction << "\n";
		ans[i].Print();
	}
	cout << "finish\n";
}

int main() {
	vector<vector<int>> input(n, vector<int>(n));
	cout << "�������ʼ�Ź���(��0��ʾ�ո�):\n";
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> input[i][j];

	EightPuzzle S0(input);
	EightPuzzle Sg(target);
	cout << "��ʼ״̬Ϊ\n";
	S0.Print();
	cout << "Ŀ��״̬Ϊ\n";
	Sg.Print();
	clock_t start, end;
	start = clock();
	S0.IDAstar(Sg);
	end = clock();
	cout << "123\n";
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



//1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 0
//2 5 3 10 7 0 9 14 12 1 6 13 4 11 15 8
//14 10 6 0 4 9 1 8 2 3 5 11 12 13 7 15
