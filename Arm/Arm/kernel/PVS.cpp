/****************************************************************
 *
 * ***************************************************************/

#include<iostream>
#include<vector>
#include"kernel/global.h"
#include "Chess/chess.h"
using namespace std;
int Chess::PVS(short depth,int alpha,int beta)
{
	void Gen_All_Move(vector<mov>&);
	int Weight_value();
	void Make_move(mov&);
	void Un_move(mov&);
	int search(short,int,int);


    int value=0;
	vector<mov>Move_array;
	bool pv_flag=false;


	if(depth==0)
		return Weight_value();


	Gen_All_Move(Move_array);
	if(Move_array.size()==0)//may not be nessary
	{
		return -Max_value;
	}


    for(unsigned int progressinfo=0;progressinfo<Move_array.size();progressinfo++)
	{
        //progress->setValue((progressinfo+1)*100/Move_array.size());//show progress
        mov mv=Move_array[progressinfo];
		Make_move(mv);
		if(pv_flag)
		{
			value=-search(depth-1,-alpha-1,-alpha);
            if(value>alpha && value<beta)
                value=-search(depth-1,-beta,-alpha);//CAUTION
		}
		else
		{
			value=-search(depth-1,-beta,-alpha);//caution!
		}
		Un_move(mv);
//		cout<<"value="<<value<<endl;
//		cout<<"beta="<<beta<<endl;
		if(value>=beta)
		{
//			cout<<"value="<<value;
//			cout<<"beta="<<beta;
			if(beta==Max_value)
			{
//				cout<<"i="<<i<<endl;
				best_move=mv;
			}
			return value;//is it OK?
		}
		if(value>alpha)
		{
			alpha=value;
			pv_flag=true;
			if(depth==max_depth)
				best_move=mv;
		}
	}
	return value;
}


	

