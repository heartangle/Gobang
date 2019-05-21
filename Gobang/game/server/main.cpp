#include <rpc_server.h>
#include<iostream>
#include<string>
using namespace rest_rpc;
using namespace rpc_service;
#include <fstream>
#include"Hall.hpp"
using namespace std;

Hall GameHall;//定义大厅这个全局变量

uint32_t RpcRegister(connection* conn, string name, string passwd)//conn里面应该包含socket
{
    return GameHall.Register(name, passwd);
}
uint32_t RpcLogin(connection* conn, uint32_t id, string passwd)
{
    return GameHall.Login(id, passwd);
}
bool RpcMatchAndWait(connection* conn, uint32_t id)
{
    return GameHall.PushIdInMatchPool(id);
}
int RpcPlayerReady(connection* conn, uint32_t id)
{
    return GameHall.IsPlayerReady(id);
}
string RpcBoard(connection* conn, uint32_t id)
{
    return GameHall.GetPlayerBoard(id);
}
uint32_t RpcPlayerRoomId(connection* conn, uint32_t id)
{
    return GameHall.GetPlayerRoomId(id);
}
char RpcPlayerPiece(connection* conn, uint32_t room_id, uint32_t id)
{
    return GameHall.GetPlayerPiece(room_id, id);
}
bool RpcIsMyTurn(connection* conn, uint32_t room_id, uint32_t id)
{
    return GameHall.IsMyTurn(room_id, id);
}
void RpcStep(connection* conn, uint32_t room_id, uint32_t id, int x, int y)
{
    return GameHall.Step(room_id, id, x, y);
}
char RpcJudge(connection* conn, uint32_t room_id, uint32_t id)
{
    return GameHall.Judge(room_id, id);
}
bool RpcPopMatchPool(connection* conn, uint32_t id)
{
    return GameHall.PopIdMatchPool(id);
}
int main() {
	rpc_server server(9001, 4);//4指的是的底层进行IO服务线程数
    LOG(INFO, "初始化服务器成功......");

    server.register_handler("RpcRegister", RpcRegister);
    server.register_handler("RpcLogin", RpcLogin);
    server.register_handler("RpcMatchAndWait", RpcMatchAndWait);
    server.register_handler("RpcPlayerReady", RpcPlayerReady);
    server.register_handler("RpcBoard", RpcBoard);
    server.register_handler("RpcPlayerRoomId", RpcPlayerRoomId);
    server.register_handler("RpcPlayerPiece", RpcPlayerPiece);
    server.register_handler("RpcIsMyTurn", RpcIsMyTurn);
    server.register_handler("RpcStep", RpcStep);
    server.register_handler("RpcJudge", RpcJudge);
    server.register_handler("RpcPopMatchPool", RpcPopMatchPool);
    LOG(INFO, "注册所有的方法完毕......");
	server.run();
    LOG(INFO, "服务器成功启动......");
    GameHall.InitHall();

	std::string str;
	std::cin >> str;
}
