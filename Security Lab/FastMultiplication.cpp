#include<bits/stdc++.h>
using namespace std;

void print(int x)
{
	for(int i=7;i>=0;i--)
	{
		if( x & (1<<i) ) cout<<"1.x("<<i<<")";
		else cout<<"0.x("<<i<<")";
		if(i) cout<<" + ";
	}
	cout<<endl;
}

int main(int argc, char const *argv[])
{
	
	string Ax,Bx,Mx,EXOR;

	Mx = "100011011"; // m(x) = x^8 + x^4 + x^3 + x^1 + 1
	EXOR = Mx.substr(4); 
	cout<<"m(x) = x^8 + x^4 + x^3 + x^1 + 1 "<<endl;
	cout<<"Enter Ax polynomial belonging to GF(2^8) "<<endl;
	cin>>Ax;
	cout<<"Enter Bx polynomial belonging to GF(2^8)"<<endl;
	cin>>Bx;

	int ax = stoull(Ax,0,2); int bx = stoull(Bx,0,2); int mx = stoull(Mx,0,2); int exor = stoull(EXOR,0,2);
	int lim = (1<<8)-1; 
	int curr = ax,ans;
	int product = 0;

	if( bx&1 ) product = ax;
	for(int power=1; power<8; power++)
	{
		ans=0;
		ans = (curr<<1) & (lim);
		if( curr & (1<<7) ) 	ans ^=  exor;
		curr = ans;
		print(ans);
		if( bx & (1<<(power)) ) product ^= ans;
	}

	cout<<"Product : "<<endl;

	print(product);

	
	return 0;
}

/*
01010111
10000011
*/