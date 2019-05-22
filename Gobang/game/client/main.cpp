#include "game.hpp"

static void LoginMenu()
{
    cout<<"**************************************"<<endl;
    cout<<"**  1.登录             2.注册    *****"<<endl;
    cout<<"**                     3.退出    *****"<<endl;
    cout<<"**************************************"<<endl;
    cout<<"请选择：>";
}
static void Usage(string proc)
{
    cout<<"Usage: "<<proc<<"ip port"<<endl;
}
int main(int argc, char* argv[])
{
    if(argc != 3){
        Usage(argv[0]);
        return 1;
    }
    string ip = argv[1];
    int port = atoi(argv[2]);
    
    string name;
    string passwd;
    uint32_t id = 0;
    int select = 0;
    while(1){
        LoginMenu();
        cin>>select;
        switch(select){
        case 1:
            {//登录
            uint32_t result = Login(ip, port);
            if(result >= 10000){
                id = result;
                cout<<"登录成功，开始游戏吧！"<<endl;
                Game(ip, port, id);
            }
            else{
                cout<<"登录失败，退出码："<<result<<endl;
            }
            }
            break;
        case 2:
            {
            Register(ip, port, name, passwd, id);
            if(id < 10000){
                cout<<"注册失败，请稍后在试！"<<endl;
            }
            else{
                cout<<"注册成功，请一定记住你的ID:["<<id<<"]"<<endl;
                cout<<"请直接登录！"<<endl;
            }
            }
            break;
        case 3:
            cout<<"客户端退出......"<<endl;
            exit(2);
            break;
        default:
            cout<<"输入错误...  请重新输入！"<<endl;
            break;
        }
    }
    return 0;
}


