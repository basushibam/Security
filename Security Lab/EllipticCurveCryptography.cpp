#include<bits/stdc++.h>
#include<gmp.h>
#include<gmpxx.h>
#include <unistd.h>
using namespace std;

int main(){
	mpz_class a,b,p,m,limit,temp,x,y,d;

	unsigned long seed;
	gmp_randstate_t state;
	seed = time(NULL);
	gmp_randinit_mt(state);
	gmp_randseed_ui(state, seed);
	mpz_set_ui(limit.get_mpz_t(),1e10);

	while(mpz_probab_prime_p(p.get_mpz_t(),25) != 2) mpz_urandomm(p.get_mpz_t(),state,limit.get_mpz_t());    //finding p randomly

	limit=p;

	while(1){                                    //finding  a and b randomly and check if((4 a^3  + 27 b^2) != 0)
		mpz_urandomm(a.get_mpz_t(),state,limit.get_mpz_t());
		mpz_urandomm(b.get_mpz_t(),state,limit.get_mpz_t());
		if(((4*a*a*a + 27*b*b) % p) != 0) break;
	}

	x=0;												//finding a point on curve
	while(1){
		y = (x*x*x + a*x + b) % p;
		if(mpz_perfect_square_p(y.get_mpz_t()) != 0) break;
		else x+=1;
	}
	mpz_sqrt(y.get_mpz_t(),y.get_mpz_t());


	cout<<"p : "<<p<<"\n";
	cout<<"Curve : y^2 = x^3 + "<<a<<"x + "<<b<<"\n";

	pair<mpz_class,mpz_class> P1,P2;
	vector<pair<mpz_class,mpz_class> > points;

	P1.first = x;
	P1.second = y;
	cout<<"A point on the given curve : ";
	cout<<"("<<P1.first<<","<<P1.second<<")\n\n";

	mpz_class lambda;

	points.push_back(P1);
														/****************finding p-1 points on curve************/
	temp = 2*P1.second;
	mpz_invert(temp.get_mpz_t(),temp.get_mpz_t(),p.get_mpz_t());
	lambda = ((3 * P1.first * P1.first + a) * temp)%p;
	P2.first = (lambda * lambda - P1.first - P1.first);
	mpz_mod(P2.first.get_mpz_t(),P2.first.get_mpz_t(),p.get_mpz_t());
	P2.second = (lambda * (P1.first - P2.first) - P1.second);
	mpz_mod(P2.second.get_mpz_t(),P2.second.get_mpz_t(),p.get_mpz_t());

	points.push_back(P2);

	for(int i=2;i<p;i++){
		temp = P2.first - P1.first;
		mpz_invert(temp.get_mpz_t(),temp.get_mpz_t(),p.get_mpz_t());
		lambda = (P2.second - P1.second) * temp;
		mpz_mod(lambda.get_mpz_t(),lambda.get_mpz_t(),p.get_mpz_t());
		x = (lambda * lambda - P1.first - P2.first);
		P2.first = x;
		mpz_mod(P2.first.get_mpz_t(),P2.first.get_mpz_t(),p.get_mpz_t());
		P2.second = (lambda * (P1.first - P2.first) - P1.second);
		mpz_mod(P2.second.get_mpz_t(),P2.second.get_mpz_t(),p.get_mpz_t());
		points.push_back(P2);
	}
	sleep(3);
															/*********displaying points************/
	cout<<"Points on given curve\n";
	for(int i=0;i<points.size();i++){
		cout<<"("<<points[i].first<<","<<points[i].second<<")"<<"   ";
	}
	cout<<"\n";
													/*********finding private and public key**********/
	mpz_set(limit.get_mpz_t(),p.get_mpz_t());
	while(mpz_cmp_ui(d.get_mpz_t(),1) < 0) mpz_urandomm(d.get_mpz_t(),state,limit.get_mpz_t());

	cout<<"\nPrivate key(d) : "<<d<<"\n\n";
	pair<mpz_class,mpz_class> Q = points[d.get_ui() - 1];
	cout<<"Public key(Q) : "<<"("<<Q.first<<","<<Q.second<<")\n\n";



	/********************ENCRYPTION*****************/ 

}