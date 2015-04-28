#include<vector>
#include<string>
#include <QLabel>
#include "global.h"
#include "Chess/chess.h"
#include <iostream>
using namespace std;
void Chess::compmove()
{
    void Make_move(mov&);
    void Gen_All_Move(vector<mov>&);
    short posx(short,short);
    short posy(short,short);
 //   progress->show();
    max_depth=4;
    if(10<history.size()&&history.size()<=50)
        max_depth=4;
    if(history.size()>50)
        max_depth=5;
    value=PVS(max_depth,-Max_value,Max_value);
    if(value==-Max_value)
        std::cout<<"end"<<std::endl;
    Make_move(best_move);
    history.push_back(best_move);
    Gen_All_Move(human_move);
    if(human_move.size()==0)
        std::cout<<"end"<<std::endl;
    showMoveByComputer(best_move.from,best_move.to);

}
void Chess::go(OurPoint start, OurPoint target)
{
    void Gen_All_Move(vector<mov>&);
    bool checkmate();
    short start_a =(start.y+3)*16+start.x+3;
    short target_a=(target.y+3)*16+target.x+3;
    mov theMove;
    human_move.clear();
    Gen_All_Move(human_move);
    theMove.from=start_a;
    theMove.to=target_a;
    theMove.capture=board[theMove.to];
//    for(unsigned int i=0;i<human_move.size();i++)
//    {
//        mov movable=human_move[i];
//        if(theMove.from==movable.from&&theMove.to==movable.to)
//        {
//            Make_move(theMove);
//            history.push_back(theMove);
//            update();
//            compmove();
//            update();
//            break;
//        }
//    }
    Make_move(theMove);
    history.push_back(theMove);
    update();
    compmove();
    update();

}

void Chess::showMoveByComputer(short start, short target)
{
    OurPoint startm,targetm;
    startm.y=start/16-3;//line
    startm.x=start%16-3;//road
    targetm.y=target/16-3;
    targetm.x=target%16-3;
    if(theBoard->getStatus(targetm)!=NOCHESS)
    {
        theMove.toEat=true;
        std::cout<<theMove.toEat<<std::endl;
    }
    else
    {
        theMove.toEat=false;
    }
    std::cout<<theMove.toEat<<std::endl;
    theBoard->setChess(targetm,theBoard->getStatus(startm));
    theBoard->setChess(startm,NOCHESS);
    theMove.startx=startm.x+1;//road

    theMove.starty=startm.y+1;//line
    theMove.endx=targetm.x+1;//road
    theMove.endy=targetm.y+1;//road
    theMove.toMove=true;
    update();
}


