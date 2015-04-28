#ifndef BLACKBOARD_H
#define BLACKBOARD_H
#include "Angle.h"
#include "length.h"
#include "Move.h"
#include "actiontosend.h"
#include "Chess/ChessSubBoard.h"
extern Angle theAngle;
extern Length theLength;
extern Move theMove;
extern ChessSubBoard theChessBoard;
extern ActionToSend theActionToSend;
//Blackboard.o: Blackboard.cpp
//        $(CXX) -c $(CXXFLAGS) $(INCPATH) -o Blackboard.o Blackboard.cpp
#endif // BLACKBOARD_H
