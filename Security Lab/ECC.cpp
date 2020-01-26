#include<bits/stdc++.h>
#include<gmp.h>
using namespace std;
mpz_t q,a,b,Gx,Gy,n,minusGy,na,nb,pax,pay,pbx,pby,kax,kay,kbx,kby;

void getLambda(mpz_t xp, mpz_t yp, mpz_t lambda)
{
	mpz_t tmp;
	mpz_inits(tmp,NULL);
	
	mpz_mul_ui(tmp,yp,2);
	mpz_invert(lambda,tmp,q);
	
	mpz_mul(tmp,xp,xp);
	mpz_mul_ui(tmp,tmp,3);
	mpz_add(tmp,tmp,a);
	
	mpz_mul(lambda,lambda,tmp);
	mpz_mod(lambda,lambda,q);
}

void getLambda(mpz_t xp, mpz_t yp, mpz_t xq, mpz_t yq, mpz_t lambda)
{
	//cout<<xp<<" "<<yp<<" "<<xq<<" "<<yq<<endl;
	mpz_t tmp;
	mpz_inits(tmp,NULL);
	
	mpz_sub(lambda,yq,yp);
	mpz_sub(tmp,xq,xp);
	//cout<<"tmp: "<<tmp<<endl;
	mpz_invert(tmp,tmp,q);
	//cout<<"tmp:: "<<tmp<<endl;
	mpz_mul(lambda,lambda,tmp);
	mpz_mod(lambda,lambda,q);
	//cout<<"lambda:: "<<lambda<<endl;
}

bool isEqual(mpz_t x1, mpz_t y1, mpz_t x2, mpz_t y2)
{
	if(mpz_cmp(x1,x2)==0 and mpz_cmp(y1,y2)==0)
		return true;
	return false;
}

void getn(mpz_t n)
{
	mpz_t x,y,lambda,lambda2,xr,yr;
	mpz_inits(x,y,lambda,lambda2,xr,yr,NULL);
	mpz_set(x,Gx);
	mpz_set(y,Gy);
	mpz_set_ui(n,1);
	while(!isEqual(x,y,Gx,minusGy))
	{
		if(isEqual(x,y,Gx,Gy))
		{
			getLambda(x,y,lambda);
		}
		else
		{
			getLambda(x,y,Gx,Gy,lambda);
		}
		mpz_mul(lambda2,lambda,lambda);

		mpz_sub(xr,lambda2,x);
		mpz_sub(xr,xr,Gx);
		mpz_mod(xr,xr,q);
		
		mpz_sub(yr,x,xr);
		mpz_mul(yr,lambda,yr);
		mpz_sub(yr,yr,y);
		mpz_mod(yr,yr,q);
				
		mpz_set(x,xr);
		mpz_set(y,yr);
		
		mpz_add_ui(n,n,1);
	}
}

void mul(mpz_t resx, mpz_t resy, mpz_t opx, mpz_t opy, mpz_t num)
{
	mpz_sub_ui(num,num,1);
	if(mpz_cmp_ui(num,0)==0)
		return;
	mpz_t lambda,lambda2,xr,yr;
	mpz_inits(lambda,lambda2,xr,yr,NULL);
	if(isEqual(resx,resy,opx,opy))
	{
		getLambda(opx,opy,lambda);
	}
	else
	{
		getLambda(resx,resy,opx,opy,lambda);
	}
	mpz_mul(lambda2,lambda,lambda);

	mpz_sub(xr,lambda2,resx);
	mpz_sub(xr,xr,opx);
	mpz_mod(xr,xr,q);
	
	mpz_sub(yr,resx,xr);
	mpz_mul(yr,lambda,yr);
	mpz_sub(yr,yr,resy);
	mpz_mod(yr,yr,q);
			
	mpz_set(resx,xr);
	mpz_set(resy,yr);
	mul(resx,resy,opx,opy,num);
}

int main()
{
	mpz_t tmp;
	mpz_inits(q,a,b,Gx,Gy,n,minusGy,na,nb,pax,pay,pbx,pby,tmp,kax,kay,kbx,kby,NULL);
	
	cout<<"Enter a prime number (q): ";
	cin>>q;
	cout<<"Enter curve parameters, a and b: ";
	cin>>a>>b;
	cout<<"Enter base point coordinates (G): ";
	cin>>Gx>>Gy;
	
	mpz_neg(minusGy,Gy);
	mpz_mod(minusGy,minusGy,q);
	getn(n);
	gmp_printf("n: %Zd\n",n);
	
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	gmp_randseed_ui(state,time(NULL));
	mpz_urandomm(na,state,n);
	
	gmp_randseed(state,na);
	mpz_urandomm(nb,state,n);
	
	mpz_add_ui(na,na,1);
	mpz_add_ui(nb,nb,1);
	gmp_printf("na: %Zd\n",na);
	gmp_printf("nb: %Zd\n",nb);

	mpz_set(pax,Gx);
	mpz_set(pay,Gy);
	mpz_set(tmp,na);
	mul(pax,pay,Gx,Gy,tmp);
	mpz_set(pbx,Gx);
	mpz_set(pby,Gy);
	mpz_set(tmp,nb);
	mul(pbx,pby,Gx,Gy,tmp);
	
	gmp_printf("Pa: %Zd %Zd\n",pax,pay);
	gmp_printf("Pb: %Zd %Zd\n",pbx,pby);
	
	mpz_set(kax,pax);
	mpz_set(kay,pay);
	mul(kax,kay,pax,pay,nb);
	mpz_set(kbx,pbx);
	mpz_set(kby,pby);
	mul(kbx,kby,pbx,pby,na);

	gmp_printf("Ka: %Zd %Zd\n",kax,kay);
	gmp_printf("Kb: %Zd %Zd\n",kbx,kby);
	return 0;
}
