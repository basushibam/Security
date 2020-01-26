#include<time.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/select.h>
#include<pthread.h>
#include<signal.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/shm.h>
#include<unistd.h>
#include<sys/un.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<pcap.h>
#include<errno.h>
#include<netinet/if_ether.h>
#include<net/ethernet.h>
#include<netinet/ether.h>
#include<netinet/udp.h>
#include <bits/stdc++.h>
#include<gmpxx.h>
using namespace std;

#define ll mpz_class
#define MAXN 2000005
#define pb push_back

ll p,q,n,phi_n,e,d,pub_B;

ll ModularExponent(ll a, ll x, ll n)
{
	if( x==0 ) return 1;
	ll ans = 1;
	ll prd = ModularExponent(a,x/2,n);
	ans = ( prd%n * prd%n )%n;
	if( x%2==1 ) ans = ( ans%n * a%n)%n;
	return ans;
}

int SendKey(int &sfd,ll k,int port)
{
	if(sfd==-1){	
		struct sockaddr_in serv_addr;
		int port_no=port;

		bzero(&serv_addr,sizeof(serv_addr));

		if((sfd = socket(AF_INET , SOCK_STREAM , 0))==-1)
		{perror("\n socket"); return 0;}
		else printf("\n socket created successfully\n");

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(port_no);
		serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

		if(connect(sfd , (struct sockaddr *)&serv_addr , sizeof(serv_addr))==-1)
		perror("\n connect : ");
		else printf("\nconnect succesful");
	}
	string str = k.get_str(10);
	cout<<"Sending "<<str<<" to proxy\n";
	send(sfd,str.c_str(),100,0);
	return 1;
}



int main(int argc, char const *argv[])
{
	int psfd=-1,bsfd=-1;
	pub_B = 237;
	//Generate Key
	cout<<"Enter two large prime numbers p and q "<<endl;
	cin>>p>>q;
	n = p*q;
	phi_n = (p-1)*(q-1);
	cout<<"Select a key e which is coprime to " <<phi_n<<" : ";
	cin>>e;
	mpz_invert(d.get_mpz_t(),e.get_mpz_t(),phi_n.get_mpz_t()); //Key pair (e,d) is generated.

	//Send e to Proxy
	if(SendKey(psfd,d,9090)) cout<<"Successfully sent key"<<d<< " to proxy "<<endl;

	//Send d to User B
	if(SendKey(bsfd,e,8080)) cout<<"Successfully sent key"<<e<<" to User B "<<endl;
	ll M;
			cout<<"Enter the message which is an integer "<<endl;
		cin>>M;
		ll C = ModularExponent(M,pub_B,n);
		if(SendKey(psfd,C,9090)) cout<<"Successfully sent Message"<<C<<" to proxy "<<endl;
	
	

	return 0;
}