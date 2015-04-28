#include "playmp3.h"
#include <iostream>
PlayMp3::PlayMp3()
{
    cmd=new QProcess();
}
void PlayMp3::sayHello()
{
    QString prog="./StartVideo";
    //QString para1="play.py";
    //QString para2="22";
    //QStringList para;
    //para<<para1<<para2;
    cmd->start(prog);
}

void PlayMp3::play(QString num1,QString num2,QString num3,QString num4)
{
    QString prog="python";
    QString para1="play.py";
    QStringList para;
    para<<para1;
    para<<num1<<num2<<num3<<num4;
    cmd->start(prog,para);
    //cmd->terminate();

}
void PlayMp3::say(OurPoint from, OurPoint to)
{
    int num[4];
    switch(theChessBoard.getStatus(from))
    {
    case B_CAR:
    case R_CAR:
        num[0]=1;
        break;
    case B_HORSE:
    case R_HORSE:
        num[0]=2;
        break;
    case B_MINISTER:
    case R_MINISTER:
        num[0]=3;
        break;
    case B_IMPERIAL:
    case R_IMPERIAL:
        num[0]=4;
        break;
    case B_KING:
        num[0]=5;
        break;
    case R_KING:
        num[0]=6;
        break;
    case B_CANON:
    case R_CANON:
        num[0]=7;
        break;
    case B_PAWN:
        num[0]=8;
        break;
    case R_PAWN:
        num[0]=9;
        break;
    default:
        num[0]=1;
        break;
    }
    num[1]=8-from.x+13;
    switch (theChessBoard.getStatus(from)) {
    case B_CAR:
    case B_CANON:
    case B_PAWN:
    case B_KING:
    case R_CAR:
    case R_CANON:
    case R_PAWN:
    case R_KING:
        if(from.y==to.y)
        {
            num[2]=12;
            num[3]=8-to.x+13;
        }
        else if(from.y>to.y)
        {
            num[2]=10;
            num[3]=(from.y-to.y-1)+13;
        }
        else
        {
            num[2]=11;
            num[3]=(to.y-from.y-1)+13;
        }

        break;
    case R_HORSE:
    case R_MINISTER:
    case R_IMPERIAL:
        if(from.y>to.y)
        {
            num[2]=10;
            num[3]=8-to.x+13;
        }
        else
        {
            num[2]=11;
            num[3]=8-to.x+13;
        }
        break;
    default:
        num[2]=1;
        num[3]=1;
        break;
    }
    QString nums[4];
    for(int i=0;i<4;i++)
    {
        nums[i]=QString().setNum(num[i]);
        std::cout<<num[i]<<std::endl;
    }

   play(nums[0],nums[1],nums[2],nums[3]);

}
