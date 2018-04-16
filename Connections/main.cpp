#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<signal.h>

#include "../Query Processor/tree.h"
#include "ThreadPool.h"
map<string,int> datatype_vals;
Root* root;
void initdatatype()
{
	datatype_vals.insert({"int",1});
	datatype_vals.insert({"decimal",2});
	datatype_vals.insert({"timestamp",3});
	datatype_vals.insert({"varchar",4});
}
int main()
{
	initdatatype();
	root=new Root();
	ThreadPool *pool=new ThreadPool(5);
	int listenfd,connfd;
	struct sockaddr_in sin;
	socklen_t addrsize;
	listenfd=socket(AF_INET,SOCK_STREAM,0);
	memset(&sin,0,sizeof(sin));
	sin.sin_family=AF_INET;
	sin.sin_addr.s_addr=inet_addr("127.0.0.1");
	sin.sin_port=htons(4321);
	bind(listenfd,(struct sockaddr*)&sin,sizeof(sin));
	listen(listenfd,5);
	while((connfd=accept(listenfd,(struct sockaddr*)&sin,&addrsize)))
	{
		pool->submit(connfd);
	}
	pool->completed();
}