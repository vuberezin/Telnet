#include "telnet.h"


int main(void) {

   string host = "127.0.0.1";
   string login = "login\r";
   string pass = "password\r";
   string ls = "ls\r";
   string exit = "exit\r";
   string path = "/home/file.log";
   int timeout = 1;

   Telnet t(host,login,pass,ls,exit);
   t.execute(timeout);
   t.printLog(path);
   t.regexSearch();

   return 0;
} 
    
