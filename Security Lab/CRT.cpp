#include<bits/stdc++.h>
using namespace std;

int GCD_Extended(int a,int b,int *x,int *y)
{
	if(a==0)
	{
		*x=0;
		*y=1;
		return b;
	}
	int x1,y1;
	int gcd=GCD_Extended(b%a,a,&x1,&y1);
	*x=y1-(b/a)*x1;
	*y=x1;
	return gcd;
}
int ChineseRemainderTheorem(int num[], int rem[], int n)
{
	int prd=1;
	for(int i=0;i<n;i++) prd *= num[i];

	int pp[n];
	for(int i=0;i<n;i++) pp[i]=prd/num[i];

	int sum=0;	

	for(int i=0;i<n;i++)
	{
		int x,y;
		GCD_Extended(pp[i],num[i],&x,&y);
		if(x<0) x+=num[i];
		sum += rem[i]*x*pp[i];
	}	
	return sum%prd;
}

int main(int argc, char const *argv[])
{
	int n;
	cout<<"Enter n : "; cin>>n;
	int num[n] , rem[n];
	cout<<endl;
	cout<<"Enter the divisor array : ";
	for(int i=0;i<n;i++) cin>>num[i];
	cout<<endl;
	cout<<"Enter the remainder array : ";
	for(int i=0;i<n;i++) cin>>rem[i];

	int solution = ChineseRemainderTheorem(num,rem,n);	
	cout<<"Solution = "<<solution<<endl;
	return 0;
}
