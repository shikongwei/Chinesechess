#ifndef ACTIONTOSEND_H
#define ACTIONTOSEND_H
#include <vector>
#include <string>
using namespace std;
class ActionToSend
{
public:
    vector<vector<int> > action;

    bool action_done;//waiting for us to send
    bool action_ready;//we have calculate the angle, and wait to send
    string data;
    ActionToSend();

};

#endif // ACTIONTOSEND_H
