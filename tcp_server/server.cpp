#include<iostream>
#include<string>
#include<cstring>  //memset所在库
using namespace std;

///这里是TCP所需库
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

//#include<arpa/inet.h>


#define BUF_SIZE 1024

#define PORT 8080

int main()
{
    int server_socket;//服务器端套接字索引
    int client_socket;//客户端套接字索引
    int len;
    sockaddr_in server_addr; //服务器端网络地址
    sockaddr_in client_addr; //客户端端网络地址
    socklen_t   sockaddr_in_len_S = sizeof(server_addr);    //存储服务端sockaddr_in结构体长度
    socklen_t   sockaddr_in_len_C = sizeof(client_addr);    //存储客户端sockaddr_in结构体长度
    memset(&server_addr,0,sockaddr_in_len_S); //数据初始化-清零
    memset(&client_addr,0,sockaddr_in_len_C);
    char receive[BUF_SIZE];  //数据接受缓存区

    //socket连接
    server_socket = socket(PF_INET,SOCK_STREAM,0); //TCP连接使用套接字,连接失败返回-1,成功返回当前套接字索引
    if(server_socket < 0)
    {
        cout<<"TCP服务器未成功建立Socket连接"<<endl;
    }
    cout<<"TCP服务器成功建立Socket连接"<<endl;
    //设置通信端口
    server_addr.sin_family = AF_INET;     //IPv4通信
    server_addr.sin_port = htons(PORT);   //PORT为宏定义8088
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    cout<<"设置服务端地址为："<<server_addr.sin_addr.s_addr <<":"<<server_addr.sin_port<<endl;
    //进行bind连接
    if( bind(server_socket,(const sockaddr*)&server_addr,sockaddr_in_len_S) < 0)
    {
        cout<<"TCP服务器未成功建立bind连接"<<endl;
    }
    cout<<"TCP服务器成功建立bind连接"<<endl;
    //进行listen监听
    if(listen(server_socket,SOMAXCONN) < 0)
    {
        cout<<"TCP服务器未成功建立listen连接"<<endl;
    }
    cout<<"TCP服务器成功建立listen连接"<<endl;
    //进行accept()连接,服务端套接字以及客户端地址和大小
    client_socket = accept(server_socket,( sockaddr*)&client_addr,(socklen_t *)&sockaddr_in_len_C);
    if(client_socket < 0)
    {
        cout<<"TCP服务器未成功建立accept连接"<<endl;
    }
    cout<<"TCP服务器成功建立accept连接"<<endl;
    cout<<"-----------------------已成功连接到客户端-----------------------"<<endl;
    //顺利到这代表已经完成服务端和客户端的三次握手，可以进行信息传输了
    while(true)  //一直保持接收发送状态
    {
        receive[BUF_SIZE] = {0};
        char sendTo[] = "我已经接收到您发送的信息"; //需要发送给客户端的信息
        int recv_flag = recv(client_socket,receive,BUF_SIZE,0);//recv_flag返回实际读取到的字节数
        if(recv_flag >0)
        {
            cout<<"接收到来自客户端的信息："<<receive<<endl;
            //const char * sendData = "你好，TCP客户端！\n";
            int send_flag = send(client_socket,sendTo,sizeof(sendTo),0);//发送成功则返回发送的字节数大小给send_flag
            if(send_flag != sizeof(sendTo))
            {
                cout<<"未成功发送信息至客户端"<<endl;
            }
            //完成一次信息传递就关闭客户端，未关闭监听
            

        }
    }
    //关闭服务端监听
    close(client_socket);
    close(server_socket);
    return 0;


}