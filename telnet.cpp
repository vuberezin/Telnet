#include "telnet.h"
 

void Telnet::execute(int timeout){
 
    const char *host_ = host.c_str();      
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1) {
        perror("Error opening socket");
        return;
    }
    
    server.sin_addr.s_addr = inet_addr(host_);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
 
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0) {
        perror("Error connecting");
        return;
    }
    
    struct timeval ts;
    ts.tv_sec = 1; 
    ts.tv_usec = 0;
   
    while(1){

    fd_set fds;
    FD_ZERO(&fds);
    if (sock != 0){
        FD_SET(sock, &fds);
        FD_SET(0, &fds);
    }    
    
    int res = select(sock + 1, &fds, (fd_set *) 0, (fd_set *) 0, &ts);

    if (res < 0) {
        perror("Error on select");
        return;

    } else if (res == 0) {
        ts.tv_sec = 1; 
        ts.tv_usec = 0;
    

    } else if (sock != 0 && FD_ISSET(sock, &fds)) {

        int s = recv(sock , bufChar , 1 , 0);
        if (s < 0) {
         perror("Error reading from socket");
         return;
        }
        if (s == 0) {
            return;
          
//---------------------------------------------------------------------------------------------------------------------

        } else if (bufChar[0] == 255) {
        s = recv(sock , bufChar + 1 , 2 , 0);

        if (s == 0){
            return;
        }

        for (i = 0; i < 3; i++) {

        if (bufChar[i] == 253 || bufChar[i] == 254) {
            bufChar[i] = 252;
        }
        }  
        int n = send(sock, bufChar, 3 , 0);
            if (n < 0) {
            perror("Error writing to socket");
            return;
        }
//---------------------------------------------------------------------------------------------------------------------
          
        } else {  
            bufLog[++n] = bufChar[0];  
        }
    }    


    if ((bufChar[0] != 255) & !exit) {   
        
        sleep(timeout);
        for(int i = 0; i < c1.length(); i++){
        bufChar[0] = c1[i];
        int n = send(sock, bufChar, 1, 0);
            if (n < 0) {
            perror("Error writing to socket");
            return;
            }
        }

        sleep(timeout);
        for(int i = 0; i < c2.length(); i++){
        bufChar[0] = c2[i];
        int n = send(sock, bufChar, 1, 0);
            if (n < 0) {
            perror("Error writing to socket");
            return;
            }
        } 

        sleep(timeout);
        for(int i = 0; i < c3.length(); i++){
        bufChar[0] = c3[i];
        int n = send(sock, bufChar, 1, 0);
            if (n < 0) {
            perror("Error writing to socket");
            return;
            }
        }

        sleep(timeout);
        for(int i = 0; i < c4.length(); i++){
        bufChar[0] = c4[i];
        int n = send(sock, bufChar, 1, 0);
            if (n < 0) {
            perror("Error writing to socket");
            return;
            }
        exit = true; 
        }
        }    
    }
    
    close(sock); 
}   

void Telnet::regexSearch(){

  std::string str = (const char*)bufLog;
  std::smatch match;
  std::regex reg (".*loc.*");

  regex_search (str, match, reg);
    for (auto x : match){
        cout << x << '\n';
    }
}

void Telnet::printLog(string path){
  
  std::ofstream file;
  file.open (path,  std::ios::app | std::ios::out);
  file << bufLog;
  file.close();
    
}
