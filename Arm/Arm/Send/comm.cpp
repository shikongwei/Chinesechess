#include "comm.h"
#include <string>
#include <QString>
#include <iostream>
using namespace std;
Comm::Comm()
{
    python=new pyinit();
}
void Comm::Communicate()
{
    object main_ns=import("__main__").attr("__dict__");//import dictionary of python
        try
        {
            object result=exec_file("../Arm/python/SerialW.py",main_ns,main_ns);//relative path
            object send=main_ns["send"];
            object rece=main_ns["rece"];
            while(0)
            {
                string data;
                if(theActionToSend.action_ready)
                {

                     for(unsigned int num=0;num<10;num++)
                     {
                         data="65535";
                         cout<<num<<endl;
                         for(unsigned int i=0;i<40;i++)
                         {
                             data+=" ";
                             theActionToSend.data=theActionToSend.data.substr(1);
                             data+=theActionToSend.data.substr(0,theActionToSend.data.find_first_of(' '));
                             theActionToSend.data=theActionToSend.data.substr(theActionToSend.data.find_first_of(' '));
                            // cout<<"test  i "<<i<<endl;
                         }
                          //cout<<data<<endl;
                          //cout<<theActionToSend.data<<endl;
                         //theActionToSend.data.clear();
                         send(data);
                         theActionToSend.action.clear();
                         theActionToSend.action_ready=false;
                         theActionToSend.action_done=false;
                         while(1)
                         {
                             cout<<"waiting rece"<<endl;
                             object recedata=rece(1);
                             string receData=extract<string>(recedata);
                             cout<<receData<<endl;
                             if(receData[0]=='1')
                             {

                                 cout<<"action_done "<<num<<endl;
                                 break;
                             }
                         }
                     }
                     theActionToSend.action_done=true;//wnen we receive 1 from arm,we set it true
                }


            }


       }
       catch(...)
       {
           pyinit::err_print();
       }
}
Comm::~Comm()
{

}

