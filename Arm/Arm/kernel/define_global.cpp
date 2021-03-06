#include"global.h"
#include<iostream>

void Make_move(mov& mv)
{
    short to=mv.to;
    short from=mv.from;
    short capture=mv.capture;
    piece[board[from]]=to;
    piece[capture]=0;
    board[to]=board[from];
    board[from]=0;
    side=1-side;
}
void Un_move(mov& mv)
{
    short to=mv.to;
    short from=mv.from;
    short capture=mv.capture;
    board[from]=board[to];
    board[to]=capture;
    piece[capture]=to;
    piece[board[from]]=from;
    side=1-side;
}

vector<mov>human_move;
vector<mov>history;
/* 棋盘数组初始化*/

short piece[48]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                 0xc7,0xc6,0xc8,0xc5,0xc9,0xc4,0xca,0xc3,0xcb,0xa4,0xaa,0x93,0x95,0x97,0x99,0x9b,
                 0x37,0x36,0x38,0x35,0x39,0x34,0x3a,0x33,0x3b,0x54,0x5a,0x63,0x65,0x67,0x69,0x6b
};

short repiece[48]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                 0xc7,0xc6,0xc8,0xc5,0xc9,0xc4,0xca,0xc3,0xcb,0xa4,0xaa,0x93,0x95,0x97,0x99,0x9b,
                 0x37,0x36,0x38,0x35,0x39,0x34,0x3a,0x33,0x3b,0x54,0x5a,0x63,0x65,0x67,0x69,0x6b
};/*高楠定义，非AI部分的全局变量*/

short board[256]={
    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
    0 ,0 ,0 ,39,37,35,33,32,34,36,38,40,0 ,0 ,0 ,0 ,
    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
    0 ,0 ,0 ,0 ,41,0 ,0 ,0 ,0 ,0 ,42,0 ,0 ,0 ,0 ,0 ,
    0 ,0 ,0 ,43,0 ,44,0 ,45,0 ,46,0 ,47,0 ,0 ,0 ,0 ,
    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
    0 ,0 ,0 ,27,0 ,28,0 ,29,0 ,30,0 ,31,0 ,0 ,0 ,0 ,
    0 ,0 ,0 ,0 ,25,0 ,0 ,0 ,0 ,0 ,26,0 ,0 ,0 ,0 ,0 ,
    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
    0 ,0 ,0 ,23,21,19,17,16,18,20,22,24,0 ,0 ,0 ,0 ,
    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
};

short side,max_depth,mode,progressinfo;
int value;
mov best_move;

