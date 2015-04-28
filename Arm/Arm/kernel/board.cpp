#include<stdio.h>
#include<iostream>
#include<string>
#include"global.h"
using namespace std;
string get_piece(short piece_num)
{
	switch(piece_num)
	{
		case 16:return "红帅";
		case 17:
		case 18:return "红仕";
		case 19:
		case 20:return "红相";
		case 21:
		case 22:return "红马";
		case 23:
		case 24:return "红车";
		case 25:
		case 26:return "红炮";
		case 27:
		case 28:
		case 29:
		case 30:
		case 31:return "红兵";
		case 32:return "黑将";
	    case 33:
		case 34:return "黑士";
		case 35:
		case 36:return "黑象";
		case 37:
		case 38:return "黑马";
		case 39:
		case 40:return "黑车";
		case 41:
		case 42:return "黑炮";
		case 43:
		case 44:
		case 45:
		case 46:
		case 47:return "黑卒";
		default:return "0   ";
	}
}
void kernaldisplay()
{
	short p;
	for(int i=3;i<13;i++)
	{
		for(int j=3;j<12;j++)
		{
			p=board[i*16+j];
			cout<<'('<<i*16+j<<','<<get_piece(p)<<','<<p<<')'<<"\t";
		}
		cout<<"\n\n"<<endl;
	}
}
