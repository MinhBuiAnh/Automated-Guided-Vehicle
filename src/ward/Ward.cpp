#include "Ward.h"

using namespace std;

Ward::Ward()
{
    this->name = "A";
    this->entry.x = 0;
    this->entry.y = 0;
    this->exit.x = 0;
    this->exit.y = 0;
    this->top_left.x = 0;
    this->top_left.y = 0;
    this->top_right.x = 0;
    this->top_right.y = 0;
    this->low_left.x = 0;
    this->low_left.y = 0;
    this->low_right.x = 0;
    this->low_right.y = 0;
}

string Ward::getName(){
    return this->name;
}

Point Ward::getEntry(){
    return this->entry;
}

Point Ward::getExit(){
    return this->exit;
}

Point Ward::getTopLeft(){
    return this->top_left;
}

Point Ward::getTopRight(){
    return this->top_right;
}

Point Ward::getLowLeft(){
    return this->low_left;
}

Point Ward::getLowRight(){
    return this->low_right;
}

void Ward::setName(std::string name){
    this->name = name;
}

void Ward::setEntry(double x, double y){
    this->entry.x = x;
    this->entry.y = y;
}

void Ward::setExit(double x, double y){
    this->exit.x = x;
    this->exit.y = y;
}

void Ward::setTopLeft(double x, double y){
    this->top_left.x = x;
    this->top_left.y = y;
}
void Ward::setTopRight(double x, double y){
    this->top_right.x = x;
    this->top_right.y = y;
}

void Ward::setLowLeft(double x, double y){
    this->low_left.x = x;
    this->low_left.y = y;
}

void Ward::setLowRight(double x, double y){
    this->low_right.x = x;
    this->low_right.y = y;
}
