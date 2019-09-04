#include "connector.h"
#include "base.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>	
#include <string.h>
#include <string>
#include <fcntl.h>


using namespace std;

/*MAJOR OVERHAUL WITH CONNECTOR CLASS
ALL CONNECTORS IN CONNECTOR.H
ALL SEPARATE CONNECTOR FILES COMMENTED OUT
ALL CONNECTORS IN SINGLE AREA*/

//this one is ;
//AlwaysRunNext::AlwaysRunNext() : Connector() {}

bool AlwaysRunNext::execute() {
    left->execute();
    bool rightExec = right->execute();
    if (rightExec) {
        return true;
    }
    return false;
}

bool AlwaysRunNext::verify() {
    return false;
}
//this one is ||
//FailRunNext::FailRunNext() : Connector() {}

bool FailRunNext::execute() {
    if(left->execute()) {
        return true;
    }

    else if(right->execute()) {
        return true;
    }
    else {
        return false;
    }
}


bool FailRunNext::verify() {
	return false;
}

//this one is &&
//PassRunNext::PassRunNext() : Connector() {}

bool PassRunNext::execute() {
    if(left->execute()) {
        if(right->execute()) {
            return true;
        }	
        else {
            return false;
        }
    }
    return false;
}

bool PassRunNext::verify() {
	return false;
}

