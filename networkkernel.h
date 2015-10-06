#ifndef NETWORKKERNEL_H
#define NETWORKKERNEL_H
#include<DataType.h>
#include<QString>
#include <QtDebug>
#include <QTextCodec>
#include<iostream>
#include <fstream>

using namespace std;
class NetworkKernel
{
public:
    NetworkKernel()
    {}
public:
    QString result;

public:
    virtual int httpConnection(QString hostName)
    { return 0 ;}
    virtual int setupSockfd()
    { return 0 ;}
    virtual int setupServerAddr(struct sockaddr_in & servaddr,char *hostName)
    { return 0 ;}
    virtual char* generateHttpRequest(QString host,QString hostPath)
    { return NULL ;}

    inline QString getResult()
    {
        return result;
    }
};

#endif // NETWORKKERNEL_H
