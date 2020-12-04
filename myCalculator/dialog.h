#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include"model.h"
#include<QString>
//新增
#include<QStack>
const int INIT = 0;
const int DIGIT = 1;
const int OPERA = 2;
const int LEFT = 3;
const int RIGHT = 4;
//
QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

    //2020.12.1新增
    void init();//初始化堆栈
    int getLevel(const QChar& oper);//得到运算符等级
    void toPostfix();//转成后缀表达式
    void evaluation();//求解
    void digitBtn(char ch);//显示


private slots:       //为每个按钮设置槽函数
    void getpushbutton_o();
    void getpushbutton_1();
    void getpushbutton_2();
    void getpushbutton_3();
    void getpushbutton_4();
    void getpushbutton_5();
    void getpushbutton_6();
    void getpushbutton_7();
    void getpushbutton_8();
    void getpushbutton_9();
    void getpushbutton_add();
    void getpushbutton_sub();
    void getpushbutton_mul();
    void getpushbutton_div();
    void getpushbutton_equ();
    void getpushbutton_c();
    //2020.11.30增加算术表达式运算功能
    void getpushbutton_left();
    void getpushbutton_right();
    void getpushbutton_del();
    void getpushbutton_r();


private:
    QString tmp;//存放显示的字符串
    Ui::Dialog *ui;
    //model *mode;
    //2020.12.1新增
    QStack<QChar> expStack;//后缀表达式栈
    QStack<QChar>opStack;//运算符栈
    QString postfix;//存储后缀表达式
    bool complete;//运算是否完成
    int lefts;

};
#endif // DIALOG_H
