#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <thread>
#include <fstream>
#include <string>
#include <functions.h>

void setHeader(int client,const char* extention){
  
  std::string check = extention;
  std::string data;
  
  if(check.substr(0,4) == "html"){
    data = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n";
  }else if(check.substr(0,3) == "jpg"){
    data = "HTTP/1.1 200 OK\r\nContent-type: image/jpg\r\n\r\n";
  }else if(check.substr(0,3) == "txt"){
    data = "HTTP/1.1 200 OK\r\nContent-type: text/plain\r\n\r\n";
  }else if(check.substr(0,2) == "js"){
    data = "HTTP/1.1 200 OK\r\nContent-type: text/javascript\r\n\r\n";
  }else if(check.substr(0,3) == "png"){
    data = "HTTP/1.1 200 OK\r\nContent-type: image/png\r\n\r\n";
  }else if(check.substr(0,3) == "mp4"){
    data = "HTTP/1.1 200 OK\r\nContent-type: video/mp4\r\n\r\n";
  }else if(check.substr(0,3) == "mp3"){
    data = "HTTP/1.1 200 OK\r\nContent-type: audio/mp3\r\n\r\n";
  }else if(check.substr(0,3) == "wav"){
    data = "HTTP/1.1 200 OK\r\nContent-type: audio/wav\r\n\r\n";
  }else{
    data = "HTTP/1.1 200 OK\r\nContent-type: application/binary\r\n\r\n";
  }
  
  write(client,data.c_str(),data.length());
}

void response(int client){
  
   char buffer[1000];
  
   std::cout<<"new client connected : "<<client<<std::endl;
  
   read(client,buffer,sizeof(buffer));
   
   char filename[200];
   char fileExtension[20];
   
   for(int i=0;i<1000;i++){
     if(buffer[i+5] == ' '){
       break;
       buffer[i+5] = '\0';
     }
     filename[i] = buffer[i+5];
   }
   
   
   for(int i =0;i<200;i++){
     if(filename[i] == '.'){
       
       for(int j=0;j<20;j++){
         if(filename[j] == '\0'){
           break;
           fileExtension[j] = '\0';
         }
         fileExtension[j] = filename[i+1+j];
       }
       break;
     }
   }
   std::cout<<"file requested : "<<filename<<std::endl;
   
   char folder[500] = "./files/";

   strcat(folder,filename);
  
   std::ifstream input(folder,std::ios::binary);
   
   if(input.is_open()){
     setHeader(client,fileExtension);
     
     int fileSize;
     input.seekg(0,std::ios::end);
     fileSize = input.tellg();
     input.seekg(0,std::ios::beg);
     
     char* fileData = new char[fileSize];
     input.read(fileData,fileSize);
     write(client,fileData,fileSize);
     std::cout<<"file sent"<<std::endl;
     
     delete[] fileData;
     input.close();
     
   }else{
    std::string data = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n";
     write(client,data.c_str(),data.length());
     write(client,"<h2>file not found</h2>",23);
   }
   
   close(client);
   std::cout<<"client closed : "<<client<<std::endl;
}

int main(){
 
 int serverSocket = socket(AF_INET,SOCK_STREAM,0);
 
 if(serverSocket < 0){
   std::cout<<"failed to create socket closing."<<std::endl;
   return 1;
 }
 
 sockaddr_in serverAddress{};
 serverAddress.sin_family = AF_INET;
 serverAddress.sin_port = htons(3000);
 serverAddress.sin_addr.s_addr = INADDR_ANY;
 
 if(bind(serverSocket,(sockaddr*)&serverAddress,sizeof(serverAddress))<0){
   
   std::cout<<"failed to bind socket";
   return 1;
 };
 
 listen(serverSocket,10);
 
 std::cout<<"server is listening on port 3000"<<std::endl;
 
 execute();

 while(true){
   int client = accept(serverSocket,nullptr,nullptr);
  
   std::thread worker(response,client);
   
   worker.detach();
 }
 
 close(serverSocket);
  return 0;
}
