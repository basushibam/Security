#include<bits/stdc++.h>
#include<gmpxx.h>
using namespace std;

#define ll mpz_class
#define MAXN 70000000
#define pb push_back

ll ra ;
int tests;

// vector<ll> primes;
// bool isPrime[MAXN];

// void SieveOfEratosthenes()
// {	
// 	memset(isPrime,true,sizeof isPrime);
// 	isPrime[1]=false;
// 	for(ll p=2;p<MAXN;p++)
// 	{
// 		if( isPrime[p.get_ui()] )
// 		{
// 			primes.pb(p);
// 			for(ll m = p*2; m<MAXN; m+=p)
// 			{
// 				isPrime[m.get_ui()]=false;
// 			}
// 		}
// 	}
// 	return;
// }

void FindDistinctPrimeFactors(set<ll> &s, ll n)
{
	if( n%2 == 0 )
	{
		s.insert(2);
		while( n%2==0 ) n/=2;
	}
	for(ll i=3;i<=sqrt(n); i++)
	{
		if( mpz_probab_prime_p(i.get_mpz_t(),tests ) )
		{
			while(n%i==0)
			{
				s.insert(i);
				n /= i;
			}
		}
	}
	if( mpz_probab_prime_p(n.get_mpz_t(),tests ) )
	{
		s.insert(n);
	}
}

ll ModularExponent(ll a, ll x, ll n)
{
	if( x==0 ) return 1;
	ll ans = 1;
	ll prd = ModularExponent(a,x/2,n);
	ans = ( prd%n * prd%n )%n;
	if( x%2==1 ) ans = ( ans%n * a%n)%n;
	return ans;
}

ll FindPrimitiveRoot(ll q)
{
	set<ll> distinct_prime_factors;
	ll phi = q-1;
	FindDistinctPrimeFactors(distinct_prime_factors,phi);

	for (ll r=2; r<=phi; r++) 
    { 
    	bool flag = false;
        for (set<ll>::iterator it = distinct_prime_factors.begin(); it != distinct_prime_factors.end(); it++) 
        { 
            if ( ModularExponent(r, phi/(*it), q) == 1) 
            { 
                flag = true; 
                break; 
            } 
         } 
         if (flag == false) 
           return r; 
    } 
  	return -1;

}

ll gcdExtended(ll a, ll b, ll *x, ll *y) 
{ 
    if (a == 0) 
    { 
        *x = 0, *y = 1; 
        return b; 
    } 
  
    ll x1, y1; 
    ll gcd = gcdExtended(b%a, a, &x1, &y1);  
    *x = y1 - (b/a) * x1; 
    *y = x1; 
    return gcd; 
} 

ll ModuloMultiplicativeInverse(ll a, ll b)
{
	ll x,y;
	ll gcd = gcdExtended(a,b,&x,&y);
	if(x<0) x+=b;
	return x;
}

int main(int argc, char const *argv[])
{
	cout<<" ############### EL GAMAL CRYPTOGRAPHY ###############"<<endl;
	ll p,d,b,M,k,r,t,phi ;
	
	//SieveOfEratosthenes();
	gmp_randstate_t s;
	gmp_randinit_default(s);
	unsigned long seed;
	seed = time(NULL);
	gmp_randseed_ui(s, seed);
	ll x;
	mpz_urandomb(x.get_mpz_t(), s, 50);
	

	//Choose a large prime number
	do
	{
		mpz_nextprime(p.get_mpz_t(),x.get_mpz_t());
		ra+=10;
		cout<<"Checking for primality of : "<<p<<endl;
	}while( mpz_probab_prime_p(p.get_mpz_t(),tests ) == 0 );
	
	
	phi = p-1;
	cout<<"Chosen prime number p : "<<p<<endl;

	//Choose a primitive element
	ll a = FindPrimitiveRoot(p);
	cout<<"Primitive round selected a : "<<a<<endl;

	//Select the private key of user A
	cout<<"Enter the private key of user A between 2 and "<<p-2<<" d : ";
	cin>>d;

	//Calculate the public key of user A
	b = ModularExponent(a,d,p);

	cout<<"Private key of user A is d : "<<d<<endl;
	cout<<"Public key of user A is the tuple ( "<<p<<" , "<<a<<" , "<<b<<" ) "<<endl;

	//Input the message to be sent to user A

	cout<<"Enter the message (less than " << p << ") to be sent to user A which is M : ";
	cin>>M;

	//Select a secret random integer k
	cout<<"Select a secret random integer to be used to encrypt the message k : ";
	cin>>k;

	//Calculate the two encrypted messages r and t.

	r = ModularExponent(a,k,p);
	t = (ModularExponent(b,k,p)%p * M%p)%p;

	//User A receives message
	cout<<"Message sent to uer A : ( "<<r<<" , "<<t<< " )"<<endl;

	//User A decrypts message M = t * r ^ (-d)  mod p
	
	ll msg = ( t%p * ModularExponent(r,phi-d,p) )%p;
	cout<<"Message decrypted by user A : "<<msg<<endl;


	return 0;
}