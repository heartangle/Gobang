#pragma once

#include<iostream>
#include<string>

#define SIZE 5
#define BLACK 'X'
#define WHITE 'O'

using namespace std;

class Room{
private:
    uint32_t one;//'X'
    uint32_t two;//'O'
    char piece[2];
    int current;//当前该谁走    
    char board[SIZE][SIZE];
    char result;//X(玩家1赢), O(玩家2赢), E(平局), N()
public:
    Room()
    {}
    Room(uint32_t& id1, uint32_t& id2):one(id1),two(id2){
        piece[0] = 'X';
        piece[1] = 'O';
        memset(board, ' ', sizeof(board));
        result = 'N';
        current = one;//这里默认玩家1先走
    }
    char Piece(uint32_t& id)
    {
        int pos = (id == one ? 0 : 1);
        return piece[pos];
    }
    bool IsMyTurn(uint32_t& id)
    {
        return id == current ? true : false;
    }
    void Step(uint32_t& id, int& x, int& y)
    {
        if(current == id){
            int pos = (id == one ? 0 : 1);//piece[pos]
            board[x][y] = piece[pos];
            current = (id == one ? two : one);
            result = Judge();
        }
    }
    char GameResult(uint32_t& id)
    {
        return result;
    }
    char Judge()
    {
        int row = SIZE;
        int col = SIZE;
        for(auto i=0; i<row; i++){//判断行
            if(board[i][0] != ' '&& \
               board[i][0] == board[i][1] && \
               board[i][1] == board[i][2] && \
               board[i][2] == board[i][3] && \
               board[i][3] == board[i][4]){
                return board[i][0];
            }
        }
        for(auto i=0; i<col; i++){//判断列
            if(board[0][i] != ' ' && \
               board[0][i] == board[1][i] && \
               board[1][i] == board[2][i] && \
               board[2][i] == board[3][i] && \
               board[3][i] == board[4][i]){
                return board[0][i];
            }
        }
        //判断对角线
        if(board[0][0] != ' ' && \
           board[0][0] == board[1][1] &&\
           board[1][1] == board[2][2] &&\
           board[2][2] == board[3][3] &&\
           board[3][3] == board[4][4]){
            return board[0][0];
        }
        if(board[0][4] != ' ' && \
           board[0][4] == board[1][3] && \
           board[1][3] == board[2][2] && \
           board[2][2] == board[3][1] && \
           board[3][1] == board[4][0]){
            return board[0][4];
        }
        //还没人赢，棋盘还没满
        for(auto i=0; i<row; i++){
            for(auto j=0; j<col; j++)
            {
                if(board[i][j] == ' '){
                    return 'N';
                }
            }
        }
        //棋盘满了，还没人赢，平局。
        return 'E';
    }
    void Board(string& _board)
    {
        for(auto i=0; i<SIZE; i++){
            for(auto j=0; j<SIZE; j++){
                _board.push_back(board[i][j]);
            }
        }
    }
    ~Room()
    {}
};
