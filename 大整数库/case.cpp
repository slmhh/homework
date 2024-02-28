#include "BigInteger.hpp"
//(n,e)公钥，(n,d)私钥
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
	// cout << a + b << "\n";
	// cout << a - b << "\n";
	// cout << a * b << "\n";
	// cout << a / b << "\n";
	// cout << a % b << "\n";
	BigInteger text;
	cout << "待加密的明文: ";
	cin >> text;
	// p,q为301位的质数
	BigInteger p("7111167112911336603319175093244978465032364840523253245304196018614767311758605269460029801746155644548032566649704172107381476542349699967990642470203137669096334143239619269936994913887954815878272099646043519676508754360666450914667208815480992884760723010968752045360829136512111614640772758045429");
	BigInteger q("6782718952521717399907453200417107099313212373253336344956002115889165531159144149709436951272570262455655070942487829846999099635061132670789641385741208263366217593238376675578206877635945865977799564959670054850128295015255313436935818450136981258059931177223793966139825891095599988344937031231609");
	rsa_get_key(p,q);
	BigInteger code = encode(text);
	BigInteger plain = decode(code);
	cout << "公钥为:\n" << "n = " << n << "\n" << "e = " << e << "\n";
	cout << "密文为: " << code << "\n";
	cout << "解密结果为: " << plain << "\n";
	return 0;
}