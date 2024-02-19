#include "BigInteger.hpp"
//(n,e)公钥，(n,d)私钥
BigInteger d,n,phi,e(65537);
void rsa_get_key(BigInteger p,BigInteger q){
	n = p * q;
	phi = (p - BigInteger(1)) * (q - BigInteger(1));
	d = e.inv(phi);
}

BigInteger encode(BigInteger text){
	return text.pow(e,n);
}

BigInteger decode(BigInteger code){
	return code.pow(d,n);
}

int main() {
	//ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	// BigInteger a,b;
	// cin >> a >> b;
	// cout << a << "\n";
	// cout << b << "\n";
	// cout << a + b << "\n";
	// cout << a - b << "\n";
	// cout << a * b << "\n";
	// cout << a / b << "\n";
	// cout << a % b << "\n";
	BigInteger text;
	cout << "待加密的明文: ";
	cin >> text;
	BigInteger p("33478071698956898786044169848212690817704794983713768568912431388982883793878002287614711652531743087737814467999489");
	BigInteger q("36746043666799590428244633799627952632279158164343087642676032283815739666511279233373417143396810270092798736308917");
	rsa_get_key(p,q);
	BigInteger code = encode(text);
	BigInteger plain = decode(code);
	cout << "公钥为:\n" << "n = " << n << "\n" << "e = " << e << "\n";
	cout << "密文为: " << code << "\n";
	cout << "解密结果为: " << plain << "\n";
	return 0;
}