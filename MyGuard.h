#pragma once
#include <iostream>
#include <windows.h>

class MyGuard{
private:
    HANDLE hfile;
public:
    MyGuard(LPCTSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes,
            DWORD dwCreationDistribution, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
            : hfile(CreateFile(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
                               dwCreationDistribution, dwFlagsAndAttributes, hTemplateFile))
    {
        if(hfile == INVALID_HANDLE_VALUE)
            throw std::runtime_error("The file can not be created or opened");
    }
    operator HANDLE() const{
        return hfile;
    }

    ~MyGuard(){
        CloseHandle(hfile);
    }
};


