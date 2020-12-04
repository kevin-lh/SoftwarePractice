#include "dialog.h"
#include"cal.h"

void Dialog::calculate()
{
    node Node[NUM_OF_NUMBER];
    double num1=0;
    int len=s.length();
    int i=0;            //标记字符串位置
    int num_of_point=0; //记录小数点个数
    int num_and_op=0;    //记录浮点数和操作符的个数
    int isfloat=0;      //标记为小数部分

    //读取表达式
    while(i<len){
        if((s[i]>='0'&&s[i]<='9')){
            if(!isfloat){   //整数部分
                num1=num1*10+(s[i].toLatin1()-'0');//s[i].toLatin1():QString类型转换为const char*（toLatin1）
                i++;
            }
            else{       //小数部分
                double per=1;
                for(int k=0;k<num_of_point;k++)
                    per*=0.1;
                num1+=(s[i].toLatin1()-'0')*per;
                num_of_point++;
                i++;
            }
        }
        else if(s[i].toLatin1()=='.'){     //读到小数点
            isfloat=1;
            num_of_point=1;
            i++;
        }
        else{       //读到操作符
            if(num1){
                Node[num_and_op].flag=NUMBERS;
                Node[num_and_op].exp.fg=num1;
                num1=0;
                num_and_op++;
                isfloat=0;
                num_of_point=0;
            }

            Node[num_and_op].flag=OPERATORS;
            Node[num_and_op].exp.op=s[i].toLatin1();
            ++num_and_op;
            ++i;
        }
    }
    if(num1){
        Node[num_and_op].flag=NUMBERS;
        Node[num_and_op].exp.fg=num1;
        ++num_and_op;
        num1=0;
    }

    //计算
    //中缀表达式转后缀表达式
    QStack<node> stack;
    node Node_1[NUM_OF_NUMBER];
    int j = 0;

    for(int i = 0; i < num_and_op;){
        if(Node[i].flag){//符号
            if(stack.isEmpty())
                stack.push_back(Node[i++]);
            else{
                node tem=stack.top();
                int ret=judge(tem.exp.op,Node[i].exp.op);
                switch (ret) {
                case -1:
                    stack.push_back(Node[i++]);
                    break;
                case 1:
                    Node_1[j++]=stack.top();
                    stack.pop();
                    break;
                default:
                    stack.pop();
                    i++;
                    break;
                }
            }
        }
        else{
            Node_1[j++]=Node[i++];
        }
    }
    for(;!stack.isEmpty();){
        node tem=stack.top();
        if(tem.exp.op != '('&& tem.exp.op != ')')
            Node_1[j++]=tem;
        stack.pop();
    }

    QStack<double> stack_1;
    double d1,d2;
    for(int i = 0; i < j; i++){
        if(Node_1[i].flag){     //操作符

            d2=stack_1.top();
            stack_1.pop();
            d1=stack_1.top();
            stack_1.pop();
            switch (Node_1[i].exp.op) {
            case '+':
                d1+=d2;
                break;
            case '-':
                d1-=d2;
                break;
            case '*':
                d1*=d2;
                break;
            case '/':
                d1/=d2;
                break;
            default:    //相当于#
                break;
            }
            stack_1.push_back(d1);
        }
        else{
            stack_1.push_back(Node_1[i].exp.fg);
        }
    }
    qDebug() << d1;
    s += '=';
    s += QString::number(d1);
}

//判断两个符号的优先级
int Dialog::judge(char a, char b)
{
    char aim[7][8] = { { ">><<<>>" },{ ">><<<>>" },{ ">>>><>>" },{ ">>>><>>" },{ "<<<<<=1" },{ ">>>>1>>" },{ "<<<<<1=" } };
    char sta[7] = { '+','-','*','/','(',')','#' };
    char _result;
    int i, pa, pb;
    for (i = 0; i<6; i++) {
        if (a == sta[i])pa = i;
        if (b == sta[i])pb = i;
    }
    _result = aim[pa][pb];
    if (_result == '>')return 1;
    else if (_result == '<')return -1;
    else return 0;
}
