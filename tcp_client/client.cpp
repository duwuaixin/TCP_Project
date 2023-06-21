#include<iostream>
#include<string>
#include<cstring>  //memset所在库
using namespace std;

///这里是TCP所需库
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define Server_Addr  "192.168.233.128"               // "127.0.0.1"     //"192.168.1.1"
#define BUF_SIZE 1024
#define PORT 8082

int main()
{
    int client_socket;
    int client_connect;
    sockaddr_in client_addr;
    socklen_t sockaddr_in_len_C = sizeof(client_addr);    //存储客户端sockaddr_in结构体长度
    char receive[BUF_SIZE];
    string send_temp;
    memset(&client_addr,0,sockaddr_in_len_C);  //数据初始化-清零

    client_socket = socket(AF_INET,SOCK_STREAM,0); //TCP连接使用套接字,连接失败返回-1,成功返回当前套接字索引
    if(client_socket < 0)
    {
        cout<<"TCP客户端未成功完成socket连接"<<endl;
    }
    cout<<"TCP客户端成功完成socket连接"<<endl;
    //设置通信端口
    client_addr.sin_family = AF_INET;  //IPV4
    client_addr.sin_addr.s_addr = inet_addr(Server_Addr);
    client_addr.sin_port = htons(PORT);
    //客户端connect连接
    client_connect = connect(client_socket,(const sockaddr*)&client_addr,sockaddr_in_len_C);
    if(client_connect < 0)    
    {
        cout<<"TCP客户端未完成connect连接,等待连接"<<endl;
    }

    while(client_connect < 0)
    {
        client_connect = connect(client_socket,(const sockaddr*)&client_addr,sockaddr_in_len_C);
    } //只有当connect后才能进行之后操作1
    cout<<"----------TCP客户端成功完成connect连接到服务端--------------"<<endl;
    //进行信息传输
    while(true)
    {
        cout<<"请输入传输内容："<<endl;
        cin>>send_temp; //控制台将需要发送的内容传入
        const char  * send_data = send_temp.c_str();//将控制台输入的发送内容转换为控制台可以接受的形式
        int send_size = send(client_socket,send_data,sizeof(send_data),0);
        if(send_size != sizeof(send_data))
        {
            cout<<"未成功发送信息至服务器端"<<endl;
        }
        memset(receive,0,BUF_SIZE); //每次用完再次使用前清零
        int receive_size = recv(client_socket,receive,BUF_SIZE,0);
        if(receive_size > 0)
        {
            cout<<"接收来自服务器端的信息："<<receive<<endl;
        }
        cout<<"receive:"<<receive<<endl;
        if((string)receive == "close")
        {
            break;
        }
    }
    close(client_socket);
    return 0;
}