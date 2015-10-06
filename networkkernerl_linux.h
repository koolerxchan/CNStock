#ifndef NETWORKKERNERL_LINUX_H
#define NETWORKKERNERL_LINUX_H
#include <netinet/in.h>    // for sockaddr_in
#include <sys/types.h>    // for socket
#include <sys/socket.h>    // for socket
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include<DataType.h>
#include<QString>
#include <QtDebug>
#include <QTextCodec>
#include<iostream>
#include <fstream>
#include "networkkernel.h"

class NetworkKernerl_Linux : public NetworkKernel
{
public:
    NetworkKernerl_Linux();
    virtual int httpConnection(QString hostName);
    virtual int setupSockfd();
    virtual int setupServerAddr(struct sockaddr_in & servaddr,char *hostName);
    virtual char* generateHttpRequest(QString host,QString hostPath);

private:
    int sockfd ;
    struct sockaddr_in client_addr;
};

#endif // NETWORKKERNERL_LINUX_H
