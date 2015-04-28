#ifndef PYINIT_H
#define PYINIT_H
#include <boost/noncopyable.hpp>
#include <boost/python.hpp>
class pyinit:boost::noncopyable
{
public:
    pyinit(int initsigs=1)
    {
        assert(initsigs==0||initsigs==1);
        Py_InitializeEx(initsigs);
    }
    ~pyinit()
    {

    }
    bool isInitialized()
    {
        return Py_IsInitialized();
    }
    const char* version()
    {
        return Py_GetVersion();
    }
    static void err_print()
    {
        PyErr_Print();
    }
};
#endif // PYINIT_H
