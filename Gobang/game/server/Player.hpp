#pragma once

#include<iostream>
#include<string>
#include<pthread.h>

using namespace std;

typedef enum {
    OFFLINE = 0,
    ONLINE,
    MATCHING,
    PLAYING,
}status_t;

class Player{
private:
    string name;
    string passwd;
    uint32_t id;

    int win;
    int lose;
    int tie;//平局
    
    status_t st;//当前用户的状态信息；
    uint32_t room_id;
public:    
    Player()
    {}
    Player(string& name_, string& passwd_, uint32_t& id_)
        :name(name_),passwd(passwd_),id(id_)
    {
        win = 0;
        lose = 0;
        tie = 0;
        st = OFFLINE;//用户刚注册完，还没有登录时的状态为OFFLINE；
    }
    const string& Passwd()
    {
        return passwd;
    }
    void Online()
    {
        st = ONLINE;
    }
    void Matching()
    {
        st = MATCHING;
    }
    void Playing()
    {
        st = PLAYING;
    }
    int Status()
    {
        return st;
    }
    int Rate()//当前用户的胜率
    {
        int total = win + lose;
        if(total == 0){
            return 0;
        }
        return win*100/total;//0--100
    }
    uint32_t Room()
    {
        return room_id;
    }
    void SetRoom(uint32_t& room_id_)
    {
        room_id = room_id_;
    }
    ~Player()
    {
    }
};
