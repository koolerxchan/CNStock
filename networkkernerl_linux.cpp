#include "networkkernerl_linux.h"


NetworkKernerl_Linux::NetworkKernerl_Linux()
{
    bzero(&client_addr,sizeof(client_addr)); //把一段内存区的内容全部设置为0
    client_addr.sin_family = AF_INET;    //internet协议族
    client_addr.sin_addr.s_addr = htons(INADDR_ANY);//INADDR_ANY表示自动获取本机地址
    client_addr.sin_port = htons(0);    //0表示让系统自动分配一个空闲端口
}

int NetworkKernerl_Linux::setupSockfd()
{

    //创建用于internet的流协议(TCP)socket,用client_socket代表客户机socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
    {
        qDebug()<<"socket open error \n";
       return -1;
    }
    //把客户机的socket和客户机的socket地址结构联系起来
    if( bind(sockfd,(struct sockaddr*)&client_addr,sizeof(client_addr)))
    {
        qDebug()<<("Client Bind Port Failed!\n");
        return -1;
    }
    return 0;
}

int NetworkKernerl_Linux::setupServerAddr(struct sockaddr_in & servaddr,char *hostName)
{
    //set server addr
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(80);
    //cout<<"host name:"<<hostName<<endl;
    struct hostent *host;
    if( (host= gethostbyname(hostName)) == NULL)
    {
        qDebug()<<"[E] gethostbyname failed"<<endl;
        return NONETWORKCONNNECT;
    }
    char* ipstr = (char *)inet_ntoa(*(struct in_addr *)(host->h_addr));
    if (inet_pton(AF_INET, ipstr, &servaddr.sin_addr) <= 0 )
    {
          qDebug()<<"[E] inet_pton failed"<<endl;
          return NONETWORKCONNNECT;
    }
    return 1;
}
char* NetworkKernerl_Linux::generateHttpRequest(QString host,QString hostPath)
{
    QString Reqst;
    Reqst += "GET /";
    Reqst += hostPath + " HTTP/1.1\n";
    Reqst += "Accept-Language: zh-cn\n";
    Reqst += "Host:" + host + "\n";
    Reqst +=  "Cache-Control: no-cache";
    Reqst +=  "\r\n\r\n";
    return Reqst.toLatin1().data();
}


int NetworkKernerl_Linux::httpConnection(QString hostName)
{
    struct sockaddr_in servaddr;
    char buf[4096];
    fd_set t_set1;
    fd_set mask;
    struct timeval  tv;
    int ret;
    this->result.clear();
    if(this->setupSockfd() <0)
        return -1;
    QString hosts = hostName.section('/',0,0);
    QString hostPath = hostName.section('/',1);

    ret = this->setupServerAddr(servaddr,hosts.toLatin1().data());
    if(ret<0)
        return ret;

    int flags=fcntl(sockfd,F_GETFL,0);
    fcntl(sockfd,F_SETFL,flags|O_NONBLOCK);

    ret =  connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if (-1 == ret)
    {
        if(errno != EINPROGRESS)
        {
            qDebug()<<"[E] connect failed,errno is EINPROGRESS "<<endl;
            close(sockfd);
            return NONETWORKCONNNECT;
        }

        FD_ZERO(&mask);
        FD_SET(sockfd,&mask);
        tv.tv_sec = 5;
        tv.tv_usec = 0;

        switch(select(sockfd+1,NULL,&mask,NULL,&tv))
        {
        case -1:
            qDebug()<<"[E] select read failed,errno is -1 "<<endl;
            close(sockfd);
            return NONETWORKCONNNECT;
        case 0:
            qDebug()<<"[E] select read failed, TIMEOUT "<<endl;
            close(sockfd);
            return NONETWORKCONNNECT;

//        default:
//            int error=0;
//            socklen_t len = sizeof(int);
//            if(getsockopt(sockfd,SOL_SOCKET,SO_ERROR,&error,&len))
//            {
//                if(0 == error)
//                {
//                    printf("has connect");
//                }
//            }
        }
    }

    char *s = this->generateHttpRequest(hosts,hostPath);
    ret = write(sockfd,s,strlen(s));
    if (ret < 0){
        qDebug()<<"[E] socket write failed"<<endl;
        close(sockfd);
        return NONETWORKCONNNECT;
    }

    FD_ZERO(&t_set1);
    FD_SET(sockfd, &t_set1);
    ret =0;
    while(1){
        //设置超时为1秒，如果1秒还没有反应直接返回
        tv.tv_sec= 5;
        tv.tv_usec= 0;
        memset(buf, 0, sizeof(buf));
        int h= select(sockfd +1, &t_set1, NULL, NULL, &tv);
        if (h == 0){
            qDebug()<<"[W] select2 write failed,timeout "<<endl;
            break;
        }
        else if (h < 0) {
            qDebug()<<"[E] select2 read failed,errno is -1 "<<endl;
            ret = NONETWORKCONNNECT;
        }
        else {
            int i= read(sockfd, buf, sizeof(buf));
            if(i>0)
            {
//                result = result + buf;
                QTextCodec *gbk = QTextCodec::codecForName("GBK");
                result = result + gbk->toUnicode(buf);// gbk  convert utf8
            }
            else
                break;
        }
    }
    close(sockfd);
    return ret;

}
