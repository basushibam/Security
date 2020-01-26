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

ll n,d,C;

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
		sleep(5);
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
	n = 667;
	int sfd;
	struct sockaddr_in serv_addr,cli_addr;
	socklen_t cli_len;
	int port_no=9090;

	if((sfd = socket(AF_INET,SOCK_STREAM,0))==-1)
	perror("\n socket ");
	else printf("\n socket created successfully");

	bzero(&serv_addr,sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(bind(sfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))==-1)
	perror("\n bind : ");
	else printf("\n bind successful ");

	listen(sfd,10);

	int nsfd;
	if((nsfd = accept(sfd , (struct sockaddr *)&cli_addr , &cli_len))==-1)
	perror("\n accept ");
	else
	{
		printf("\n accept successful");
		printf("Connection accepted from %s : %d \n",inet_ntoa(cli_addr.sin_addr),ntohs(cli_addr.sin_port) );
	}
	char buf[100];
	recv(nsfd,buf,100,0);
	mpz_t x;
	mpz_init(x);
	mpz_set_str(x,buf,10);
	mpz_set(d.get_mpz_t(),x);
	cout<<"d = "<<d<<endl;
	// buf[0]='\0';
	char newbuf[100];
	recv(nsfd,newbuf,100,0);
	cout<<"Received "<<newbuf<<endl;
	mpz_set_str(x,newbuf,10);
	mpz_set(C.get_mpz_t(),x);
	cout<<"Encrypted Message:"<<C<<endl;

	ll nC = ModularExponent(C,d,n);
	cout<<"Sending encrypted msg "<<nC<<" to B\n";
	int bsfd = -1;
	SendKey(bsfd,nC,8081);

	return 0;
}