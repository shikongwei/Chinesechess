#ifndef Comm_armMove_H
#define Comm_armMove_H
#include "pyinit.hpp"
#include <string>
using namespace boost::python;
using namespace std;
class Comm_armMove
{
public:
    Comm_armMove();
    ~Comm_armMove();
    void Communicate();
    void Send(string pwm1,string pwm2,string pwm3,string pwm4);
    void SendAngle(int angle1, int angle2, int angle3, int angle4);
    void SendPosition(double x,double y,double z);
    void SendPath(string theActionToSendData);
    bool lift;

private:
    pyinit *python;

};

#endif // Comm_armMove_H
