#pragma comment(lib, "rpcrt4.lib") 
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main()
{
    UUID uuid;
    UuidCreate(&uuid);
    char* str;
    UuidToStringA(&uuid, (RPC_CSTR*)&str);
    cout << str << endl;
    RpcStringFreeA((RPC_CSTR*)&str);
    system("pause");
    return 0;
}
