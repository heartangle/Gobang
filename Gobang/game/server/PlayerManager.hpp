#pragma once
#include<iostream>
#include<string>
#include<unordered_map>
#include<utility>
#include<pthread.h>
#include"Player.hpp"
#include"Log.hpp"
#define DEFAULT_ID 10000
using namespace std;

class PlayerManager{
private:
    std::unordered_map<uint32_t, Player> player_set;//存储所有的用户；后面可以考虑用数据库实现
    uint32_t assign_id;
    pthread_mutex_t lock;
public:
    PlayerManager():assign_id(DEFAULT_ID)
    {
        pthread_mutex_init(&lock, NULL);
    }
    void Lock()
    {
        pthread_mutex_lock(&lock);
    }
    void Unlock()
    {
        pthread_mutex_unlock(&lock);
    }
    uint32_t InsertPlayer(string& name, string& passwd)
    {
        Lock();
        uint32_t id_ = assign_id++;
        Player p(name, passwd, id_);
        player_set.insert(make_pair(id_, p));
        Unlock();
        LOG(INFO, "插入玩家成功......");
        return id_;
    }
    uint32_t SearchPlayer(uint32_t& id, string& passwd)
    {
        Lock();
        auto iter = player_set.find(id);
        if(iter == player_set.end()){
            LOG(WARNING, "查找的用户不存在......");
            Unlock();
            return 1;
        }
        Player& p = iter->second;
        if(p.Passwd() != passwd){
            Unlock();
            LOG(WARNING, "用户认证失败......");
            return 2;
        }
        p.Online();
        Unlock();
        LOG(INFO, "用户登录成功......");
        return id;
    }
    void SetPlayStatus(uint32_t& one, uint32_t& two)
    {
        Lock();
        player_set[one].Playing();
        player_set[two].Playing();
        Unlock();
    }
    void SetPlayRoom(uint32_t& room_id, uint32_t& one, uint32_t& two)
    {
        Lock();
        player_set[one].SetRoom(room_id);
        player_set[two].SetRoom(room_id);
        Unlock();
    }
    void SetMatching(uint32_t& id)
    {
        Lock();
        player_set[id].Matching();
        Unlock();
    }
    void SetOnline(uint32_t& id)
    {
        Lock();
        player_set[id].Online();
        Unlock();
    }
    uint32_t GetPlayerRoomId(uint32_t& id)
    {
        Lock();
        uint32_t _room_id = player_set[id].Room();
        Unlock();
        return _room_id;
    }
    int GetRate(uint32_t& id)
    {
        Lock();
        int rate = player_set[id].Rate();
        Unlock();
        return rate;
    }
    int Ready(uint32_t& id)
    {
        Lock();
        int st = player_set[id].Status();
        Unlock();
        return st;
    }
    ~PlayerManager()
    {
        pthread_mutex_destroy(&lock);
    }
};
