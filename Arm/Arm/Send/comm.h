#ifndef COMM_H
#define COMM_H
#include "pyinit.hpp"
#include "../Representation/Blackboard.h"
using namespace boost::python;
class Comm
{
public:
    Comm();
    ~Comm();
    void Communicate();
private:
    pyinit *python;
};

#endif // COMM_H
