#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define MAXN 2000005
#define pb push_back

vector<ll> primes;
bool isPrime[MAXN];

void SieveOfEratosthenes()
{	
	memset(isPrime,true,sizeof isPrime);
	isPrime[1]=false;
	for(ll p=2;p<MAXN;p++)
	{
		if( isPrime[p] )
		{
			primes.pb(p);
			for(ll m = p*2; m<MAXN; m+=p)
			{
				isPrime[m]=false;
			}
		}
	}
	return;
}

void FindDistinctPrimeFactors(set<ll> &s, ll n)
{
	if( n%2 == 0 )
	{
		s.insert(2);
		while( n%2==0 ) n/=2;
	}
	for(ll i=3;i<=sqrt(n); i++)
	{
		if( isPrime[i] )
		{
			while(n%i==0)
			{
				s.insert(i);
				n /= i;
			}
		}
	}
	if( isPrime[n] )
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
	if( x&1 ) ans = ( ans%n * a%n)%n;
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

int main(int argc, char const *argv[])
{
	cout<<" ############### DIFFIE HELLMAN KEY EXCHANGE ###############"<<endl;
	SieveOfEratosthenes();

	//Select a prime number q
	ll q = primes[primes.size()-1];
	cout<<"Chosen prime number q : "<<q<<endl;

	//Find 'a' which is primitive root of q and a < q
	ll a = FindPrimitiveRoot(q); 
	if(a==-1)
	{
		cout<<"No Primitive Root present. Exiting..."<<endl;
		return 0;
	}

	//Select private keys X < q and calculate public keys Y 
	ll XA,XB,YA,YB,KA,KB;
	cout<<"To exchange a key select a private key XA less than "<<q<<" : ";
	cin>>XA;
	YA = ModularExponent(a,XA,q);
	cout<<"Your public key YA : "<<YA<<endl<<endl;

	cout<<"To exchange a key select a private key XB less than "<<q<<" : ";
	cin>>XB;
	YB = ModularExponent(a,XB,q);
	cout<<"Your public key YB : "<<YB<<endl<<endl;

	//Calculation of secret key by user A
	KA = ModularExponent(YB,XA,q);
	cout<<"Secret key sent by user A : "<<KA<<endl;

	//Calculation of secret key by user B
	KB = ModularExponent(YA,XB,q);
	cout<<"Secret key received by user B : "<<KB<<endl;


	return 0;
}