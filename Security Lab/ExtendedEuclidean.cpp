#include<bits/stdc++.h>
#include<gmp.h>
using namespace std;

void GCDExtended(mpz_t num1 , mpz_t num2 , mpz_t x , mpz_t y , mpz_t g)
{
	if(mpz_cmp_ui(num1,0)==0)
	{
		mpz_set(g,num2); mpz_set_ui(x,0); mpz_set_ui(y,1);
		gmp_printf("a = %Zd , b = %Zd , x = %Zd , y = %Zd , gcd = %Zd\n", num1 , num2 , x , y , g );
		return;
	}
	mpz_t x1, y1 , q , r ,t1 ;
	mpz_inits(x1,y1,q,r,t1,NULL);
	mpz_fdiv_qr(q,r,num2,num1);
    GCDExtended(r, num1, x1, y1 , g);
    mpz_mul(t1,q,x1);
    mpz_sub(x,y1,t1);
    mpz_set(y,x1);
    gmp_printf("a = %Zd , b = %Zd , x = %Zd , y = %Zd , gcd = %Zd\n", num1 , num2 , x , y , g );
}
int main(int argc, char const *argv[])
{
	if(argc!=3)
	{
		printf("Input should be ./a.out <number1> <number2> \n");
		return 0;
	}
	mpz_t num1,num2,x,y,g;
	mpz_inits(num1,num2,x,y,g,NULL);
	mpz_set_str(num1,argv[1],10);
	mpz_set_str(num2,argv[2],10);
	mpz_set_str(g,"0",10);
	gmp_printf("a = %Zd , b = %Zd \n", num1 , num2 );

	GCDExtended(num1,num2,x,y,g);
	return 0;
}