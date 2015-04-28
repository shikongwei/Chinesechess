#include "thread_auto.h"
#include "fstream"
#include <iostream>
using namespace std;
void ThreadAuto::run()
{


    while(1)
    {

        myarm.setPara(2.42,2.28,1.99,2.45);

        //std::cout<<"chess have move "<<theMove.toMove<<std::endl;
        /*when chess has been move the theMove.move will be set true,then we judge whether the move have eat some chess or not
        ,by which we give different plan to move my arm*/
        if(theMove.toMove)
        {
            if(theMove.toEat)
            {
                int i=0;
                while(i<5)
                {
                    std::cout<<"which action "<<i<<" is ready "<<theActionToSend.action_done<<std::endl;
                    if(theActionToSend.action_done)//it is true when arm have complete an action or it is just been started
                    {
                        theActionToSend.action_done=false;//we set it false because we give arm a new action to move
                        std::cout<<i<<std::endl;
                        switch (i) {
                        case 0:
                            armModify.Move_Path(0,0,theMove.endy,theMove.endx,false);
                            break;
                        case 1:
                            armModify.Move_Path(theMove.endy,theMove.endx,0,0,true);
                            break;
                        case 2:
                            armModify.Move_Path(0,0,theMove.starty,theMove.startx,false);
                            break;
                        case 3:
                            armModify.Move_Path(theMove.starty,theMove.startx,theMove.endy,theMove.endx,true);
                            break;
                        case 4:
                            armModify.Move_Path(theMove.endy,theMove.endx,0,0,false);
                            theChessBoard.toSee=true;
                            break;
                        default:
                            break;
                        }
                        theMove.toMove=false;

                         theActionToSend.action_ready=true;//we set it true to make serial port to sent our order
                         i++;
                    }
                }


            }
            else
            {
                std::cout<<"just move "<<std::endl;
                int i=0;
                while(i<3)
                {
                    std::cout<<"action done "<<theActionToSend.action_done<<std::endl;
                    if(theActionToSend.action_done)
                    {
                        theActionToSend.action_done=false;
                        switch (i) {
                        case 0:
                           armModify.Move_Path(0,0,theMove.starty,theMove.startx,false);
                            break;
                        case 1:
                            armModify.Move_Path(theMove.starty,theMove.startx,theMove.endy,theMove.endx,true);

                            break;
                        case 2:
                            armModify.Move_Path(theMove.endy,theMove.endx,0,0,false);
                            break;
                            theChessBoard.toSee=true;
                        default:
                            break;
                        }
                        theMove.toMove=false;

                        theActionToSend.action_ready=true;
                         i++;
                    }
                }
            }



        }
    }
}
void ThreadAuto::recSigFromDialog()
{
    qDebug()<<"rec sig from dialog"<<"current thread id is"<<currentThreadId();
}
