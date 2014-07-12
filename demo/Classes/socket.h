//
//  socket.h
//  demo
//
//  Created by li zaoji on 7/10/14.
//
//
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <stdlib.h>
#include "cocos2d.h"

USING_NS_CC;

class BSDSocket: public cocos2d::Node{
public:
    //"110.184.1.126", 2012
    //"192.168.0.120", 6666, local
    //Methods
    BSDSocket(const char * ip, unsigned int port);
    int connectSocket();
    int closeSocket();
    int sendDataToServer(const void *buf, size_t len, int flags);
    int recvDataFromServer(void *buf, size_t len, int flags);
    void threadFun(const char * ip,unsigned int port);
private:
    int socketHandle;
    char recvData[1024], sendData[1024];
    bool threadDone = false;
    const char * ip;
    unsigned int port;
};