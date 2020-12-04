#include "dialog.h"
#include "ui_dialog.h"
#include"model.h"
//新增
#include<QDebug>
#include<QDesktopWidget>
static QString Tmp;//静态全局变量
//
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);//连接按钮和槽函数
    connect(ui->pushButton_0,SIGNAL(clicked(bool)),this,SLOT(getpushbutton_o()));
    connect(ui->pushButton_1,SIGNAL(clicked(bool)),this,SLOT(getpushbutton_1()));
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SLOT(getpushbutton_2()));
    connect(ui->pushButton_3,SIGNAL(clicked(bool)),this,SLOT(getpushbutton_3()));
    connect(ui->pushButton_4,SIGNAL(clicked(bool)),this,SLOT(getpushbutton_4()));
    connect(ui->pushButton_5,SIGNAL(clicked(bool)),this,SLOT(getpushbutton_5()));
    connect(ui->pushButton_6,SIGNAL(clicked(bool)),this,SLOT(getpushbutton_6()));
    connect(ui->pushButton_7,SIGNAL(clicked(bool)),this,SLOT(getpushbutton_7()));
    connect(ui->pushButton_8,SIGNAL(clicked(bool)),this,SLOT(getpushbutton_8()));
    connect(ui->pushButton_9,SIGNAL(clicked(bool)),this,SLOT(getpushbutton_9()));
    connect(ui->pushButton_add,SIGNAL(clicked(bool)),this,SLOT(getpushbutton_add()));
    connect(ui->pushButton_sub,SIGNAL(clicked(bool)),this,SLOT(getpushbutton_sub()));
    connect(ui->pushButton_mul,SIGNAL(clicked(bool)),this,SLOT(getpushbutton_mul()));
    connect(ui->pushButton_div,SIGNAL(clicked(bool)),this,SLOT(getpushbutton_div()));
    connect(ui->pushButton_equ,SIGNAL(clicked(bool)),this,SLOT(getpushbutton_equ()));
    connect(ui->pushButton_c,SIGNAL(clicked(bool)),this,SLOT(getpushbutton_c()));
    //2020.11.30增加算术表达式运算功能
    connect(ui->pushButton_left,SIGNAL(clicked(bool)),this,SLOT(getpushbutton_left()));//左括号
    connect(ui->pushButton_right,SIGNAL(clicked(bool)),this,SLOT(getpushbutton_right()));//右括号
    connect(ui->pushButton_del,SIGNAL(clicked(bool)),this,SLOT(getpushbutton_del()));//del
    connect(ui->pushButton_r,SIGNAL(clicked(bool)),this,SLOT(getpushbutton_r()));//运算记录回显
    //this->mode= new model;
    //this->tmp="";//初始化显示字符串为空
    lefts=0;
    init();

}
Dialog::~Dialog()
{
    delete ui;
}

//初始化
void Dialog::init(){
    //初始栈不为空，则清空
    if(!expStack.isEmpty())
            expStack.clear();
        if(!opStack.isEmpty())
            opStack.clear();
        //压入结束符#
        opStack.push('#');
        //初始表达式运算已经完成 即true
        complete=true;
}

//显示
void Dialog::digitBtn(char ch){
    QString s = ui->label->text();
    //如果运算没有完成
       if(!complete)
           ui->label->setText(s+ch);
       else
       {
           ui->label->setText(QString(ch));
           complete = false;
       }
}
//每个按钮的槽函数，在label显示（注释的代码是之前没有封装的，现在封装成digitBtn函数）
void Dialog::getpushbutton_o(){
    if(this->tmp!=""){
//    this->tmp += this->ui->pushButton_0->text();
//    this->ui->label->setText(tmp);
      digitBtn('0');
    }
}
void Dialog::getpushbutton_1(){
//    this->tmp += this->ui->pushButton_1->text();
//    this->ui->label->setText(tmp);
    digitBtn('1');
}
void Dialog::getpushbutton_2(){
//    this->tmp += this->ui->pushButton_2->text();
//    this->ui->label->setText(tmp);
    digitBtn('2');
}
void Dialog::getpushbutton_3()
{
//    this->tmp += this->ui->pushButton_3->text();
//    this->ui->label->setText(tmp);
    digitBtn('3');
}
void Dialog::getpushbutton_4()
{
//    this->tmp += this->ui->pushButton_4->text();
//    this->ui->label->setText(tmp);
    digitBtn('4');
}
void Dialog::getpushbutton_5()
{
//    this->tmp += this->ui->pushButton_5->text();
//    this->ui->label->setText(tmp);
    digitBtn('5');
}
void Dialog::getpushbutton_6()
{
//    this->tmp += this->ui->pushButton_6->text();
//    this->ui->label->setText(tmp);
    digitBtn('6');
}
void Dialog::getpushbutton_7()
{
//    this->tmp += this->ui->pushButton_7->text();
//    this->ui->label->setText(tmp);
    digitBtn('7');
}
void Dialog::getpushbutton_8()
{
//    this->tmp += this->ui->pushButton_8->text();
//    this->ui->label->setText(tmp);
    digitBtn('8');
}
void Dialog::getpushbutton_9()
{
//    this->tmp += this->ui->pushButton_9->text();
//    this->ui->label->setText(tmp);
    digitBtn('8');
}
void Dialog::getpushbutton_add()
{
//    int num= this->tmp.toInt();//将qstring转为int类型
//    this->mode->setNum1(num);
//    this->tmp="";
//    QString ex=this->ui->pushButton_add->text();
//    this->mode->setFlag(ex);
    QString s=ui->label->text();
    ui->label->setText(s+"+");
}
void Dialog::getpushbutton_sub()
{
//    int num= this->tmp.toInt();
//    this->mode->setNum1(num);
//    this->tmp="";
//    QString ex=this->ui->pushButton_sub->text();
//    this->mode->setFlag(ex);
    QString s=ui->label->text();
    ui->label->setText(s+"-");
}
void Dialog::getpushbutton_mul()
{
//    int num= this->tmp.toInt();
//    this->mode->setNum1(num);
//    this->tmp="";
//    QString ex=this->ui->pushButton_mul->text();
//    this->mode->setFlag(ex);
    QString s=ui->label->text();
    ui->label->setText(s+"*");
}
void Dialog::getpushbutton_div()
{
//    int num= this->tmp.toInt();
//    this->mode->setNum1(num);
//    this->tmp="";
//    QString ex=this->ui->pushButton_div->text();
//    this->mode->setFlag(ex);
    QString s=ui->label->text();
    ui->label->setText(s+"/");
}
void Dialog::getpushbutton_equ()
{
//    int num=this->tmp.toInt();
//    this->mode->setNum2(num);
//    QString res=this->mode->expr();
//    this->ui->label->setText(res);
//    this->tmp="";
    //新增
    if(ui->label->text()=="0"){
        return;
    }
    Tmp=ui->label->text();//将本次运算表达式赋给Tmp
    toPostfix();
    evaluation();
    init();
}
//清空
void Dialog::getpushbutton_c()
{
    this->tmp="";
    this->ui->label->setText(tmp);
}
//删除
void Dialog::getpushbutton_del(){
    QString s=ui->label->text();
    s=s.mid(0,s.size()-1);
    ui->label->setText(s);
}
//回显
void Dialog::getpushbutton_r(){
    ui->label->setText(Tmp);
}
//2020.11.30增加算术表达式运算功能
void Dialog::getpushbutton_left(){
//    this->tmp="";
//    this->ui->label->setText(tmp);
    QString s = ui->label->text();
    if(!complete)
        ui->label->setText(s+"(");
            else
            {
                ui->label->setText("(");
                complete = false;
            }
            lefts++;
}
void Dialog::getpushbutton_right(){
//    this->tmp="";
//    this->ui->label->setText(tmp);
    QString s = ui->label->text();
        if(!complete)
            ui->label->setText(s+")");
        lefts--;
}
//得到运算符的优先级
int Dialog::getLevel(const QChar &oper)
{
    switch(oper.cell())
    {
    case '#':
    case '(':return 0;
    case '+':
    case '-':return 1;
    case '*':
    case '/':
    case '%':return 2;
    }
    return 0;
}

//转为后缀表达式
void Dialog::toPostfix()
{
     QString exp = ui->label->text();
    //QString exp = "0.3/(5*2+1)",postfix;

    int j=0;
    qDebug()<<j;
    for(int i=0;i<exp.length();i++)
    {qDebug()<<i<<exp[i];
        //isDigit():如果是十进制数字就返回True
        if(exp[i].isDigit()||exp[i]=='.')
        {
            //在后面追加
            postfix.push_back(exp[i]);
        }
        else if(exp[i]=='(')
        {
            //压栈
            opStack.push(exp[i]);
        }
        else if(exp[i]==')')
        {
            postfix.push_back(' ');
            while(opStack.top()!='(')
            {
                postfix.push_back(opStack.pop());qDebug()<<postfix;
            }
            opStack.pop();
        }
        else if(getLevel(exp[i])>getLevel(opStack.top()))
        {
            postfix.push_back(' ');qDebug()<<"postfix";
            opStack.push(exp[i]);
        }
        else
        {
            postfix.push_back(' ');qDebug()<<postfix;
            while(getLevel(exp[i])<=getLevel(opStack.top()))
                postfix.push_back(opStack.pop());
            opStack.push(exp[i]);
        }
    }
    while(opStack.top()!='#')
    {
        QChar c = opStack.pop();
        postfix.push_back(' ');
        postfix.push_back(c);
    }
    qDebug()<<postfix;
}
//

//后缀表达式求值
void Dialog::evaluation()
{
    QString tem;
    QStack<double> ans;
    for(int i=0;i<postfix.size();i++)
    {
        qDebug()<<postfix[i]<<i;
        if(postfix[i].isDigit()||postfix[i]=='.')
            tem.push_back(postfix[i]);
        else if(postfix[i]==' ')
        {
            if(!tem.isEmpty())
            {
                ans.push(tem.toDouble());
                tem.clear();
            }
            qDebug()<<ans.top()<<tem.isEmpty();
        }
        else
        {
            double a,b;
            a=ans.pop();qDebug()<<a<<"a";
            b=ans.pop();qDebug()<<b<<"b";
            switch(postfix[i].cell())
            {
            case '+':ans.push(b+a);break;
            case '-':ans.push(b-a);break;
            case '*':ans.push(b*a);break;
            case '/':ans.push(b/a);break;           
            }
            qDebug()<<ans.top()<<"top";
        }

    }
    //qDebug()<<ans.top();
    ui->label->setText(QString::number(ans.top()));
}




