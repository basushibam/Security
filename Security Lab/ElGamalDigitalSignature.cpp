#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define MAXN 2000000
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

ll H( ll M , ll p )
{
	return ( M % p ) + 1 ;
}

int main(int argc, char const *argv[])
{
	cout<<" ############### DIGITAL SIGNATURE USING ELGAMAL'S ALGORITHM ###############"<<endl;
	ll g,p,d,y,x,M,k,s1,s2,phi;
	SieveOfEratosthenes();

	//Choose a large prime number
	p = primes[primes.size()-1];
	//p = 293;
	phi = p-1;
	cout<<"Chosen prime number p : "<<p<<endl;

	//Choose a primitive element
	g = FindPrimitiveRoot(p);
	cout<<"Generator selected is g : "<< g <<endl;

	//Select the private key of user A
	cout<<"Enter the private key of user A between 2 and "<<p-2<<" x : ";
	cin>>x;

	//Calculate the public key of user A
	y = ModularExponent(g,x,p);

	cout<<"Private key of user A is d : "<< x <<endl;
	cout<<"Public key of user A is the tuple ( "<< p <<" , "<< g <<" , "<< y <<" ) "<<endl;

	//Input the message to be sent to user A

	cout<<"Enter the message to be sent to user A which is M : ";
	cin>>M;
	
	ll m = H(M,p);

	//Select a secret random integer k
	cout<<"Select a secret random integer to be used to encrypt the message which is coprime to " << ( p-1 )<<" k : ";
	cin>>k;

	s1 = ModularExponent(g,k,p);
	
	s2 = ( ModuloMultiplicativeInverse(k,p-1) % (p-1) * ( m - ( (x % (p-1)) * (s1 % (p-1) )) % (p-1) ) % (p-1) ) % (p-1);
	if( s2 < 0 ) s2 += (p-1);
	cout<<"Signed message is the tuple ( " << m << " , " << s1 << " , " << s2 << " ) "<<endl;
	
	//Verification
	ll v1 = ModularExponent(g,m,p);
	ll v2 = ( ModularExponent(y,s1,p) * ModularExponent(s1,s2,p) ) % p;
	
	cout<<"The pair (v1 , v2) := ( " << v1 << " , "<< v2 << " ) "<<endl;
	if( v1 == v2 )
	{
		cout << "User is authenticated "<<endl;
	}
	else 
	{
		cout << "User is not authenticated "<<endl;
	}
	return 0;
}
