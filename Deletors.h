#pragma once

#include <iostream>
#include <windows.h>
#include <memory>
#include <functional>



void labdaDeleter(){
    auto delSock = [](SOCKET* sock){
        if(*sock == INVALID_SOCKET){
            std::cout << "Invalid socket\n";
            return;
        }
        closesocket(*sock);
        delete(sock);
        std::cout << "A socket freed using lamda-deleter\n";

    };

    std::unique_ptr<SOCKET, decltype(delSock)> sock(new SOCKET, delSock);
}

void fDeleter(){
    std::function<void(SOCKET*)> delSock = [](SOCKET* sock){
        if(*sock == INVALID_SOCKET){
            std::cout << "Invalid socket\n";
            return;
        }
        closesocket(*sock);
        delete(sock);
        std::cout << "A socket freed using function-deleter\n";
    };

    std::unique_ptr<SOCKET, decltype(delSock)> sock(new SOCKET, delSock);
}

void delSock(SOCKET* sock){
    if(*sock == INVALID_SOCKET){
        std::cout << "Invalid socket\n";
        return;
    }
    closesocket(*sock);
    delete(sock);
    std::cout << "A socket freed using pointer to the function\n";
}

void pDeleter(){
    std::unique_ptr<SOCKET, void(*)(SOCKET*)> sock(new SOCKET, delSock);
}