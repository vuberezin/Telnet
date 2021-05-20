#ifndef TELNET_H
#define TELNET_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <termios.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <string>
#include <regex>


using namespace std;

 class Telnet {

    public:
        Telnet(string host, string c1, string c2, string c3, string c4) :
            host(host), c1(c1), c2(c2), c3(c3), c4(c4) {}            
        void execute(int timeout);
        void regexSearch();
        void printLog(string path);
        string c1;
        string c2;
        string c3;
        string c4;
        ~Telnet(){}

    private:
        struct sockaddr_in server;
        unsigned char bufChar[1024];
        unsigned char bufLog[1024]; 
        string path;
        string host;
        bool exit = false;
        int sock;
        int port = 23;
        int timeout;
        int n = -1;
        int i = 0;
        int s;

 };
 #endif // TELNET_H
