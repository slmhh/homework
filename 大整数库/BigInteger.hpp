#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<cstdio>
using namespace std;
const int N = 4e6 + 10;
const int g = 3,mod = 998244353,gi = 332748118;

class BigInteger {
	private:
		vector<int> num;  //从低位到高位存储每一位数字
		bool sign;        //符号位(+:false,-:true)
	public:
		BigInteger() { sign = false; };
		BigInteger(bool s, BigInteger t) : sign(s), num(t.num) {};
		BigInteger(string temp);
		BigInteger(int temp);
		friend istream & operator>>( istream &input,BigInteger &a);
		friend ostream & operator<<(ostream &output,BigInteger a);
		bool IsZero();  //判零
		friend bool operator == (BigInteger a, BigInteger b);
		friend bool operator <= (BigInteger a, BigInteger b);
		friend bool operator < (BigInteger a, BigInteger b){return (a <= b && !(a == b));};
		friend bool operator >= (BigInteger a, BigInteger b){return !(a < b);};
		friend bool operator > (BigInteger a, BigInteger b){return (a >= b && !(a == b));};
		BigInteger operator + () const { return *this; }  // +a
		BigInteger operator - () const { return BigInteger(!sign, *this); } // -a
		friend BigInteger operator + (BigInteger a, BigInteger b); // a + b
		BigInteger add(BigInteger b);
		friend BigInteger operator - (BigInteger a, BigInteger b); // a - b
		BigInteger sub(BigInteger b);
		friend BigInteger operator * (BigInteger a, BigInteger b); // a * b
		friend BigInteger operator / (BigInteger a, BigInteger b); // a / b
		friend BigInteger operator % (BigInteger a, BigInteger b); // a % b
		BigInteger pow(BigInteger b, BigInteger m); // a ^ b mod p
		BigInteger abs() { return BigInteger(false,*this); }  //|a|
		BigInteger inv(BigInteger m);
		bool IsOdd(); //判断奇偶
};

BigInteger::BigInteger(string temp) {	sign = false;
	if (temp[0] == '-') {
		sign = true;
		temp.erase(temp.begin());
	}
	for (int i = temp.size() - 1; i >= 0; i--)
		num.push_back(temp[i] - '0');
}

BigInteger::BigInteger(int temp) {
	sign = false;
	if(temp == 0) num.push_back(0);
	if (temp < 0) {
		sign = true;
		temp = -temp;
	}
	while (temp > 0) {
		num.push_back(temp % 10);
		temp /= 10;
	}
}

istream & operator>>(istream &input,BigInteger &a){
	char ch = getchar();
    while(ch < '0' || ch > '9'){
        if(ch == '-')
            a.sign = true;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9'){
        a.num.push_back(ch - '0');
        ch = getchar();
    }
    reverse(a.num.begin(),a.num.end());
	return input;
}

ostream & operator<<(ostream &output,BigInteger a){
	if(a.IsZero()){
		output << "0";
		return output;
	}
	if (a.sign) output << '-';
	for (int i = a.num.size() - 1; i >= 0; i--)
		output << a.num[i];
	return output;
}

bool BigInteger::IsZero() {
	if (num.size() > 1) return false;
	if (num[0] == 0) return true;
	return false;
}

bool operator <= (BigInteger a, BigInteger b) {
	if(a.sign ^ b.sign) return a.sign;
	if (a.num.size() != b.num.size())
		return a.num.size() < b.num.size();
	for (int i = a.num.size() - 1; i >= 0; i--) {
		if (a.num[i] != b.num[i])
			return a.num[i] < b.num[i];
	}
	return true;
}

bool operator == (BigInteger a, BigInteger b) {
	if (a.sign != b.sign) return false;
	if (a.num.size() != b.num.size()) return false;
	for (int i = 0; i < a.num.size(); i++) {
		if (a.num[i] != b.num[i]) return false;
	}
	return true;
}

// a + b
BigInteger BigInteger::add(BigInteger b) {
	BigInteger ans;
	int last = 0;
	for (int i = 0; i < num.size() || i < b.num.size(); i++) {
		if (i < num.size()) last += num[i];
		if (i < b.num.size()) last += b.num[i];
		ans.num.push_back(last % 10);
		last /= 10;
	}
	if (last) ans.num.push_back(last);
	return ans;
}

BigInteger operator + (BigInteger a, BigInteger b) {
	if(a.sign ^ b.sign){
		if(a.sign) return b.sub(a);
		else return a.sub(b);
	}
	return BigInteger(a.sign,a.add(b));
}

// a - b
BigInteger BigInteger::sub(BigInteger b){
	if(abs() < b.abs()) return BigInteger(true,b.sub(*this));
	BigInteger ans;
	int last = 0;
	for (int i = 0; i < num.size(); i++) {
		last = num[i] - last;
		if (i < b.num.size()) last -= b.num[i];
		ans.num.push_back((last + 10) % 10);
		if (last < 0) last = 1;
		else last = 0;
	}
	while (ans.num.size() > 1 && ans.num.back() == 0) //去除前导零
		ans.num.pop_back();
	return ans;
}

BigInteger operator - (BigInteger a, BigInteger b){
	if(!a.sign && b.sign) return a.add(b);
	if(a.sign && !b.sign) return -a.add(b);
	if(a.sign) return b.sub(a);
	return a.sub(b); 
}

// a * b
long long qpow(long long a,long long b){
  	long long ans = 1;
  	while(b){
		if(b & 1) ans = ans * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
  	return ans;
}

long long R[N],ni,f[N],h[N];
void NTT(long long A[],int n,int op){ //op为虚部符号，op为1时FFT/NTT，op为-1时IFFT/INTT
	for(int i = 0;i < n;i++)
		R[i] = R[i / 2] / 2 + (i & 1) * (n / 2);
	for(int i = 0;i < n;i++)
		if(i < R[i]) swap(A[i],A[R[i]]);

	for(int i = 2;i <= n;i <<= 1){
		long long g1 = qpow(op == 1 ? g : gi,(mod - 1) / i);
		for(int j = 0;j < n;j += i){
			long long gk = 1;
			for(int k = j;k < j + i / 2;k++){
				long long x = A[k],y = gk * A[k + i / 2] % mod;
				A[k] = (x + y) % mod;
				A[k + i / 2] = (x - y + mod) % mod;
				gk = gk * g1 % mod;
			}
		}
  }
}

BigInteger operator * (BigInteger a,BigInteger b){
    BigInteger ans;
	if(a.sign ^ b.sign) ans.sign = true;
	int len = 1 << max((int)ceil(log2(a.num.size() + b.num.size())),1);  //FFT/NTT需要项数为2的整数次方倍,len为第一个大于a.size() + b.size()的二的正整数次方
    ni = qpow(len,mod - 2);
	for(int i = 0;i < 2 * len;i++){  //转换为多项式
		if(i < a.num.size()) f[i] = a.num[i];
		else f[i] = 0;
	}
	for(int i = 0;i < 2 * len;i++){
		if(i < b.num.size()) h[i] = b.num[i];
		else h[i] = 0;
	}

	NTT(f,len,1),NTT(h,len,1);  //系数表达转点值表达

	for(int i = 0;i <= len;i++)
		f[i] = (f[i] * h[i]) % mod;

	NTT(f,len,-1);  //点值表达转系数表达
	for(int i = 0;i <= a.num.size() + b.num.size();i++) f[i] = f[i] * ni % mod;

	long long last = 0;
	for(int i = 0;i <= a.num.size() + b.num.size();i++){
		last += f[i];
		ans.num.push_back((int)last % 10);
		last /= 10;
	}
	while(ans.num.size() > 1 && ans.num.back() == 0)
		ans.num.pop_back();
    return ans;
}

// a / b
BigInteger operator / (BigInteger a,BigInteger b){
	if(a.abs() < b.abs()) return BigInteger(0);
	BigInteger ans,tempa = a.abs(),tempb = b.abs();
	if(a.sign ^ b.sign) ans.sign = true;
	int move = a.num.size() - b.num.size();
	ans.num.resize(move + 1,0);
	tempb.num.insert(tempb.num.begin(),move,0);
	for(int i = move;i >= 0;i--){
		int left = 0,right = 11;
		while(left + 1 < right){   //二分法求商
			int mid = (left + right) >> 1;
			if(tempb * BigInteger(mid) <= tempa) left = mid;
			else right = mid;
		}
		ans.num[i] = left;
		tempa = tempa - tempb * BigInteger(left);
		tempb.num.erase(tempb.num.begin());
	}
	while(ans.num.size() > 1 && ans.num.back() == 0)
		ans.num.pop_back();
	return ans;
}

// a % b
BigInteger operator % (BigInteger a,BigInteger b){
	if(a == b) return BigInteger(0);
	return a - b * (a / b);
}

bool BigInteger::IsOdd(){
	if(num[0] & 1) return true;
	return false;
}

// a ^ b mod p
BigInteger BigInteger::pow(BigInteger b,BigInteger m){
	BigInteger ans(1);
	BigInteger a = *this;
	while(!b.IsZero()){
		if(b.IsOdd()) ans = (ans * a) % m;
		b = b / BigInteger(2);
		a = (a * a) % m;
	}
  	return ans;
}

//gcd(a,b)
BigInteger gcd(BigInteger a,BigInteger b){
	if(a == b) return a;
	if(a <= b) return gcd(b,a);
	if(b.IsZero()) return a;
	return gcd(b,a % b);
}

//ax + by = 1
BigInteger exgcd(BigInteger a,BigInteger b,BigInteger &x,BigInteger &y){
	if(b.IsZero()){
		x = BigInteger(1);
		y = BigInteger(0);
		return a;
	}
	BigInteger d = exgcd(b,a % b,y,x);
	y = y - (a / b) * x;
	return d;
}

BigInteger BigInteger::inv(BigInteger m){
	BigInteger x,y;
	exgcd((*this),m,x,y);
	return (x % m + m) % m;
}
