#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<signal.h>
#include<iostream>
using namespace std;
int main()
{
	int sockfd;
	struct sockaddr_in sin;
	char buf[1024];
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	memset(&sin,0,sizeof(sin));
	sin.sin_family=AF_INET;
	sin.sin_addr.s_addr=inet_addr("127.0.0.1");
	sin.sin_port=htons(4321);
	connect(sockfd,(struct sockaddr*)&sin,sizeof(sin));
	string s;
	bool exit=false;
	while(!exit)
	{
		recv(sockfd,buf,1024,0);
		cout<<buf;
		getline(cin,s);
		if(s.size()==0)
		{
			s=" ";
			exit=true;
		}
		strcpy(buf,s.c_str());
		buf[s.length()]=0;
		send(sockfd,buf,s.length(),0);
	}
	close(sockfd);
}