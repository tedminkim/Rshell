#include "execute.h"
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
#include <algorithm>
#include <iterator>
//assignment3
using namespace std;
//HUGE EXECUTE OVERHAUL
//will add more execute functiion (vector function)
bool Execute::verify() {
    return true;
}

Execute::Execute(string userString) {
    char * cstr = new char[userString.size() + 1];
    strcpy(cstr, userString.c_str());
    char * token = strtok(cstr, " ");

    while (token != NULL) {
        execvpr.push_back(token);
        token = strtok(NULL, " ");
    }
}

bool Execute::execute() {
    if (execvpr.size() == 0) {
        return false;
    }
    if (execvpr.at(0) == "exit") {
        exit(0);
    }
    if (execvpr.at(0) == "test" || execvpr.at(0) == "[") {
        if (execvpr.at(0) == "[") {
            if (execvpr.at(execvpr.size() - 1) != "]") {
                cout << "Missing brackets" << endl;
                return false;
            }
        }
        struct stat cont; //content info
        if (execvpr.at(1) == "-e") {
            if (stat(const_cast<char*>(execvpr.at(2).c_str()), &cont) == 0) {
                cout << "(True)" << endl;
                return true;
            }
            else {
                cout << "unable to access " << execvpr.at(2) << endl;
                cout << "(False)" << endl;
                return false;
            }
        }
        else if (execvpr.at(1) == "-f") {
            if (stat(const_cast<char*>(execvpr.at(2).c_str()), &cont) != 0) {
                cout << "unable to access " << execvpr.at(2) << endl;
                cout << "(False)" << endl;
                return false;
            }

            else if (cont.st_mode & S_IFREG) {
                cout << "(True)" << endl;
                return true;
            }

            else {
                cout << "(False)" << endl;
                return false;
            }
        }
        else if (execvpr.at(1) == "-d") {
            if (stat(const_cast<char*>(execvpr.at(2).c_str()), &cont) != 0) {
                cout << "unable to access " << execvpr.at(2) << endl;
                cout << "(False)" << endl;
                return false;
            }

            else if (cont.st_mode & S_IFDIR) {
                cout << "(True)" << endl;
                return true;
            }

            else {
                cout << "(False)" << endl;
                return false;
            }
        }

        else {
            if (stat(const_cast<char*>(execvpr.at(1).c_str()), &cont) == 0) {
                cout << "(True)" << endl;
                return true;
            }

            else {
                cout << "unable to access " << execvpr.at(1) << endl;
                cout << "(False)" << endl;
                return false;
            }
        }

    }
    else {
        char * args[execvpr.size() + 1];
            for (unsigned i = 0; i < execvpr.size(); i++) {
                args[i] = const_cast<char*>(execvpr.at(i).c_str());
                // pid_t pid = fork();
                // pid_t w;
            }
            args[execvpr.size()] = NULL;
            // for (unsigned i = 0; i < execvpr.size() + 1; ++i) { //loop doesn't work
                pid_t pid = fork();
                pid_t w;

                int status;

                if (pid < 0) {
                    perror("process");
                    exit(1);
                }

                else if (pid == 0) {
                    if (execvp(*args, args) < 0) {
                        perror("exec");
                        exit(1);
                    }
                }

                else {
                    w = waitpid(pid, &status, 0);
                    if (w == -1) {
                        perror("wait");
                        exit(EXIT_FAILURE);
                    }

                    if (WEXITSTATUS(status) == 0) {
                        return true;
                    }
            // }     // }
		}
	}
    return false;
}
