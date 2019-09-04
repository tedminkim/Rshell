#ifndef EXECUTE_H
#define EXECUTE_H
#include <vector>
#include <iostream>
#include "base.h"

using namespace std;
//HUGE EXECUTE OVERHAUL
class Execute: public Base {
    protected:
        vector<string> execvpr;
    public:
        Execute() {};
        Execute(string userString);
        bool execute();
        bool verify();

};

#endif
