#include <iostream>
#include <map>

#define pi 3.14

void cat(char* value1,const char* value2){
 int size = 0;
 int counter = 0;

 while(true){
  if(value1[counter] == 0){
  break;  
  }
  size++;
  counter++;
 }

 counter = 0;

 while(true){
 if(value2[counter] == 0){
  break; 
}
  value1[size+counter] = value2[counter];
  counter++;
 }

}

int execute(){

 char final[100] = "hello";

 char first[] = "world";

 cat(final," world");

 cat(final," how are you");

 std::map<int,std::string> x;

 x[0] = "imran";
  
 std::cout<<x[0]<<std::endl;

 return 0;

}
