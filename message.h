#pragma once
#ifndef MESSAGE
#define MESSAGE
class message{
public:


    int from;
    int type;
    int damage;
    string contents;



public:
const char* sendMessage(){
    contents = "From: " + to_string(from) + " Type: " + to_string(type) + " Damage: " + to_string(damage);
    
    return contents.c_str();
}


};


#endif