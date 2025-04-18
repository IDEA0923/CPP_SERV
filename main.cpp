#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
///////////////////////////////////////////////////////

#define PORT 5500




//////////////////////////////////////////////////
using namespace std;


void setp(int& sock , struct sockaddr_in& adress ){
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == 0){
        cout<<"BAD SOCK"<<endl;
        return ;
    }
    //
    //struct sockaddr_in adress ;
    adress.sin_family = AF_INET;
    adress.sin_addr.s_addr = INADDR_ANY;
    adress.sin_port = htons(PORT);

    //if(
    bind(sock , (struct sockaddr *)&adress, sizeof(adress));
//){
    //     cout<<"BAD BIND"<<endl;
    //     return ;
    // }

    if ( listen(sock, SOMAXCONN) < 0){
        cout<<"BAD LISTEN"<<endl;
        return;
    }
}
void func(struct sockaddr_in& client_addr, int& new_sd){
    cout<<"USER"<<endl;
    
    // char memory[1024] = { 0 };
    // int n;

    // while ((n = recv(new_sd, memory, 1024, 0)))
    // {
    //     cout << "Current Thread ID " << this_thread::get_id() << endl;
    // }
    // return;

}
int main(){
    int sock;
    struct sockaddr_in adress ;
    setp(sock , adress );


    vector<std::thread> poolofthread;
    struct sockaddr_in client_addr;
    socklen_t length = sizeof(sockaddr_in);
    int new_sd;
    cout<<"START"<<endl;
    while ((new_sd = accept(sock, (sockaddr*)&client_addr, (socklen_t*)&length)) > 0)
    {
        cout << "Client Accepted" << endl;
        thread t(func, ref(client_addr), ref(new_sd));
        poolofthread.push_back(move(t));
    }
    return 0;

}
