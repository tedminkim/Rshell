//This is the connector.h file
#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "base.h"
#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;
/*MAJOR OVERHAUL WITH CONNECTOR CLASS
ALL CONNECTORS IN CONNECTOR.H
ALL SEPARATE CONNECTOR FILES COMMENTED OUT
ALL CONNECTORS IN SINGLE AREA*/
class Connector: public Base {
    public:
        Connector() : Base() {};
        virtual bool execute() = 0;
        virtual bool verify() = 0;
};

class AlwaysRunNext : public Connector {
    public:
        AlwaysRunNext() : Connector() {};
        bool execute();
        bool verify();
};

class FailRunNext : public Connector {
    public:
        FailRunNext() : Connector() {};
        bool execute();
        bool verify();
};

class PassRunNext : public Connector {
    public:
        PassRunNext() : Connector() {};
        bool execute();
        bool verify();
};


#endif
