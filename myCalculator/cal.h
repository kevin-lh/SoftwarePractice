#ifndef CAL_H
#define CAL_H

#endif // CAL_H
#include<iostream>
using namespace std;

struct node{
    int flag;
    union{
        double fg; //flag==0时，为数字
        char op;    //flag==1时，为符号
    }exp;
};
