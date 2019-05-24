#pragma once

#include <iostream>
#include<string>
#include<stdlib.h>
#include <rpc_client.hpp>
#include <chrono>
#include <fstream>
#include "codec.h"
using namespace std;
using namespace std::chrono_literals;

using namespace rest_rpc;
using namespace rest_rpc::rpc_service;

bool PushMatchPool(string& ip, int& port, uint32_t id)
{
	try {
		rpc_client client(ip, port);//这里使用的是短链接，因为rpc_client是在栈上开辟的
		bool r = client.connect();
		if (!r) {
			std::cout << "connect timeout" << std::endl;
			return 3;
		}
        return client.call<bool>("RpcMatchAndWait", id);
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
uint32_t CheckReady(string& ip, int& port, uint32_t id)
{
	try {
		rpc_client client(ip, port);//这里使用的是短链接，因为rpc_client是在栈上开辟的
		bool r = client.connect();
		if (!r) {
			std::cout << "connect timeout" << std::endl;
			return 3;
		}
        return client.call<uint32_t>("RpcPlayerReady", id);
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
    return 1;
}
bool PopMatchPool(string& ip, int& port, uint32_t& id)
{
	try {
		rpc_client client(ip, port);//这里使用的是短链接，因为rpc_client是在栈上开辟的
		bool r = client.connect();
		if (!r) {
			std::cout << "connect timeout" << std::endl;
			return 3;
		}
        return client.call<bool>("RpcPopMatchPool", id);
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
    return false;
}
bool Match(string& ip, int& port, uint32_t& id)
{
    PushMatchPool(ip, port, id);//把用户放入到匹配池中，开始后期性检测。
    int count = 20;
    while(1)
    {
        int result = CheckReady(ip, port, id);
        if(result == 3){
            cout<<"匹配成功！"<<endl;
            return true;
        }
        else if(result == 1){
            cout<<"匹配失败！"<<endl;
            return false;
        }
        else{//result==2 表示该用户还在匹配中，每隔1秒在检测一次
            printf("匹配中...... %2d\r", count--);
            fflush(stdout);
            if(count < 0){
                cout<<endl;
                cout<<"匹配超时！"<<endl;
                PopMatchPool(ip, port, id);//移除客户端
                break;
            }
            sleep(1);
        }
    }
    return false;
}
int GetBoard(string& ip, int& port, uint32_t& room_id, string& board)
{
	try {
		rpc_client client(ip, port);//这里使用的是短链接，因为rpc_client是在栈上开辟的
		bool r = client.connect();
		if (!r) {
			std::cout << "connect timeout" << std::endl;
			return 3;
		}
        board = client.call<string>("RpcBoard", room_id);
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
uint32_t GetMyRoomId(string& ip, int& port, uint32_t& id)
{
	try {
		rpc_client client(ip, port);//这里使用的是短链接，因为rpc_client是在栈上开辟的
		bool r = client.connect();
		if (!r) {
			std::cout << "connect timeout" << std::endl;
			return 3;
		}
        return client.call<uint32_t>("RpcPlayerRoomId", id);
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
char GetMyPiece(string& ip, int& port, uint32_t& room_id, uint32_t& id)
{
	try {
		rpc_client client(ip, port);//这里使用的是短链接，因为rpc_client是在栈上开辟的
		bool r = client.connect();
		if (!r) {
			std::cout << "connect timeout" << std::endl;
			return 3;
		}
        return client.call<char>("RpcPlayerPiece", room_id, id);
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
void ShowBoard(string& board)
{
    cout<<"   ";
    for(auto i=1; i<=5; i++){
        cout<<i<<"   ";
    }
    cout<<endl;
    for(auto i=0; i<=5; i++){
        cout<<"----";
    }
    cout<<endl;
    int size = board.size();
    int basic_size = 5;
    for(auto i=0; i<size/basic_size; i++){
        cout<<i+1<<" |";
        for(auto j=0; j<basic_size; j++){
            cout<<" "<<board[i*basic_size+j]<<" |";
        }
        cout<<endl;
        for(auto i=0; i<=5; i++){
            cout<<"----";
        }
        cout<<endl;
    }
}
bool IsMyTurn(string& ip, int& port, uint32_t& room_id, uint32_t& id)
{
	try {
		rpc_client client(ip, port);//这里使用的是短链接，因为rpc_client是在栈上开辟的
		bool r = client.connect();
		if (!r) {
			std::cout << "connect timeout" << std::endl;
			return 3;
		}
        return client.call<bool>("RpcIsMyTurn", room_id, id);
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
    return false;
}
bool PosIsRight(string& board, int x, int y)
{
    int pos = (x-1)*5 + (y-1);
    return board[pos] == ' ' ? true : false;
}
int Step(string& ip, int& port, uint32_t& room_id, uint32_t& id, int x, int y)
{
	try {
		rpc_client client(ip, port);//这里使用的是短链接，因为rpc_client是在栈上开辟的
		bool r = client.connect();
		if (!r) {
			std::cout << "connect timeout" << std::endl;
			return 3;
		}
        client.call<void>("RpcStep", room_id, id, x-1, y-1);
        return 0;
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
char Judge(string& ip, int& port, uint32_t& room_id, uint32_t& id)
{
	try {
		rpc_client client(ip, port);//这里使用的是短链接，因为rpc_client是在栈上开辟的
		bool r = client.connect();
		if (!r) {
			std::cout << "connect timeout" << std::endl;
			return 3;
		}
        return client.call<char>("RpcJudge", room_id, id);
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
int GetNumber(string& ip, int& port)
{
	try {
		rpc_client client(ip, port);//这里使用的是短链接，因为rpc_client是在栈上开辟的
		bool r = client.connect();
		if (!r) {
			std::cout << "connect timeout" << std::endl;
			return 3;
		}
        return client.call<int>("RpcGetNumber");
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
void PlayTwoGame(string& ip, int& port)
{
    cout<<"欢迎来到猜数字游戏！"<<endl;
    cout<<"服务器将随即生成一个1-1000之内的数字哦！"<<endl;
    cout<<"游戏开始喽！"<<endl;
    int number = 500;
    number = GetNumber(ip, port);
    int ret = 0;
    while(1){
        cout<<"请输入一个数:>";
        cin>>ret;
        if(ret > number){
            cout<<"猜大了！"<<endl;
        }
        else if(ret < number){
            cout<<"猜小了！"<<endl;
        }
        else{
            cout<<"恭喜你，猜对了！"<<endl;
            break;
        }   
    }
}
void PlayOneGame(string& ip, int& port, uint32_t& id)
{
    int x,y;
    char result = 'N';
    string board;
    uint32_t room_id = GetMyRoomId(ip, port, id);
    cout<<"你的房间号是："<<room_id<<endl;
    if(room_id < 1024){
        return;
    }
    char piece = GetMyPiece(ip, port, room_id, id);
    cout<<"你所执棋子是："<<piece<<endl;
    for( ; ; ){
        GetBoard(ip, port, id, board);//获取棋盘
        ShowBoard(board);//展示棋盘
        //判断该谁走
        if(result = Judge(ip, port, room_id, id) != 'N'){
            break;
        }
        if(!IsMyTurn(ip, port, room_id, id)){
            cout<<"对方正在思考......"<<endl;
            sleep(1);
            continue;
        }
        cout<<"请输入你的落子位置：>";
        cin>>x>>y;
        if(x >= 1 && x<=5 && y>=1 && y<=5){
            if(!PosIsRight(board, x, y)){
                cout<<"你输入的位置已经被占用，请重新输入！"<<endl;
            }
            else{
                Step(ip, port, room_id, id, x, y);
                result = Judge(ip, port, room_id, id);
                if(result != 'N'){
                    break;
                }
            }
            }
        else{
            cout<<"你输入的位置有误，请重新输入！"<<endl;
        }
    }
    GetBoard(ip, port, id, board);//获取棋盘
    ShowBoard(board);//展示棋盘
    if(result == 'E'){
        cout<<"平局，在来一局吧!"<<endl;
    }
    else if(result == piece){
        cout<<"恭喜，你赢了！"<<endl;
    }
    else{
        cout<<"好遗憾，你输了，在来一局吧！"<<endl;
    }
}
void Game(string& ip, int& port, uint32_t& id)
{
    int game_select = 0;
    volatile bool quit = false;
    while(!quit)
    {

        cout<<"********************************"<<endl;
        cout<<"***1、五子棋      2、猜数字 ****"<<endl;
        cout<<"***3、退出                  ****"<<endl;
        cout<<"********************************"<<endl;
        cout<<"请选择：";
        cin>>game_select;

        switch(game_select)
        {
        case 1:
            {
                if(Match(ip, port, id)){
                    PlayOneGame(ip, port, id);
                }
                else{
                    cout<<"匹配失败，请重新在试！"<<endl;
                }
            }
            break;
        case 2:
            {
                PlayTwoGame(ip, port);
            }       
            break;
        case 3:
            quit = true;
            break;
        default:
                cout<<"选择有误，请重新选择！"<<endl;
                break;
        }
    }
}

uint32_t Login(const string& ip, const int& port)
{
    uint32_t id;
    string passwd;
    cout<<"请输入登录ID：";
    cin>>id;
    cout<<"请输入登录密码：";
    cin>>passwd;
    uint32_t result = 0;
	try {
		rpc_client client(ip, port);//这里使用的是短链接，因为rpc_client是在栈上开辟的
		bool r = client.connect();
		if (!r) {
			std::cout << "connect timeout" << std::endl;
			return 3;
		}
        result = client.call<uint32_t>("RpcLogin", id, passwd);
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
    return result;
}

uint32_t Register(const string& ip, const int& port, string& name, string& passwd, uint32_t& id)
{
    cout<<"请输入昵称：";
    cin>>name;
    cout<<"请设置密码：";
    cin>>passwd;
    string passwd_;
    cout<<"请重复输入密码：";
    cin>>passwd_;
    if(passwd != passwd_){
        cout<<"两次输入的密码不一致！"<<endl;
        return 1;
    }

	try {
		rpc_client client(ip, port);
		bool r = client.connect();
		if (!r) {
			std::cout << "connect timeout" << std::endl;
			return 2;
		}
        id = client.call<uint32_t>("RpcRegister", name, passwd);
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
    return 0;
}
