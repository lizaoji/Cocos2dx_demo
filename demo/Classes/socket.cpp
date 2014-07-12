//
//  socket.cpp
//  demo
//
//  Created by li zaoji on 7/10/14.
//
//

#include "socket.h"
BSDSocket::BSDSocket(const char * ip, unsigned int port){
    this->ip = ip;
    this->port = port;
    this->socketHandle = -1;
}

int BSDSocket::connectSocket(){
    
    struct sockaddr_in  saddr;
    
    socketHandle = socket(AF_INET, SOCK_STREAM, 0);
    if (socketHandle < 0) {
        log("Socket failed!");
        return -1;
    }
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    if(inet_pton(AF_INET, ip, &saddr.sin_addr) != 1){
        log("inet_pton is failed");
        return -1;
    }
    
    if(::connect(socketHandle, (struct sockaddr*)&saddr, sizeof(saddr)) < 0){
        log("connect failed");
        return -1;
    }
    else{
        log("connect success");
    }
    
    return 0;
}

int BSDSocket::closeSocket(){
    if(::close(socketHandle) != 0){
        log("close socket failed");
        return -1;
    }
    return 0;
}

int BSDSocket::sendDataToServer(const void *buf, size_t len, int flags){
    if(::send(socketHandle, buf,len, 0) < 0){
        log("send data failed");
        return -1;
    }
    return 0;
}

int BSDSocket::recvDataFromServer(void *buf, size_t len, int flags){
    if(::recv(socketHandle, buf,len, 0) < 0){
        log("recv data failed");
        return -1;
    }
    return 0;
}

void BSDSocket::threadFun(const char * ip,unsigned int port){
    threadDone = false;
    memset(recvData, 0, sizeof(recvData));
    memset(sendData, 0, sizeof(sendData));
    if(connectSocket() == 0){
        log("connect success\n");
        sendDataToServer("hello, this is another test2\n", 1024, 0);
        recvDataFromServer(recvData, 1024, 0);
        log(recvData);
    }
    if(closeSocket() != 0){
        log("close socket failed");
        exit(-1);
    }
    threadDone = true;
}

//int main(int argc, const char * argv[]) {
//
//    BSDSocket * BSDSocket = new BSDSocket();
//    printf("begin:%s\n", BSDSocket->recvData);
//    std::thread t1(&BSDSocket::threadFun, BSDSocket, "110.184.1.126", 2012);
//    t1.detach();
//    printf("thread t1 detached\n");
//    while(!BSDSocket->threadDone){
//        printf("main thread is waiting\n");
//    }
//    printf("after:%s\n", BSDSocket->recvData);
//    return 0;
//}

