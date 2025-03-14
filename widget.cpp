#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    activateButton(); //Disable buttons when constructor is called
}

Widget::~Widget()
{
    delete ui;
}

void Widget::checkMoney(int v)
{
    money += v;
    Q_ASSERT(money >= 0); //always true logic Exception
    activateButton(); // Automatically check button activation when amount changes
    ui->lcdNumber->display(money);
}

void Widget::reset()
{
    money = 0;
    ui->lcdNumber->display(money);
    activateButton();
}

// Logic for button activation based on amount
void Widget::activateButton()
{
    ui->pbCoffee->setEnabled(money >= 100);
    ui->pbWater->setEnabled(money >= 150);
    ui->pbMilkTee->setEnabled(money >= 500);
    
    if(money < 0){
        ui->pbCoffee->setEnabled(false);
        ui->pbMilkTee->setEnabled(false);
        ui->pbWater->setEnabled(false);
    }
    ui->pbReset->setEnabled(money > 0);
   
void Widget::on_pb10_clicked()
{
    checkMoney(10);
}

void Widget::on_pb50_clicked()
{
    checkMoney(50);
}

void Widget::on_pb100_clicked()
{
    checkMoney(100);
}

void Widget::on_pb500_clicked()
{
    checkMoney(500);
}

void Widget::on_pbReset_clicked()
{
    int temp = money;
    int coins[] = {500, 100, 50, 10};
    int counts[4];
    
    for(int i=0; i<4; i++) {
        counts[i] = temp / coins[i];
        temp %= coins[i];
    }

    QString msg = QString("500: %1\n100: %2\n50: %3\n10: %4")
                    .arg(counts[0])
                    .arg(counts[1]) 
                    .arg(counts[2])
                    .arg(counts[3]);

    QMessageBox mb;
    mb.information(this, "Change", msg);
    reset();
}


void Widget::on_pbCoffee_clicked()
{
    checkMoney(-100);
}

void Widget::on_pbMilkTee_clicked()
{
    checkMoney(-500);
}

void Widget::on_pbWater_clicked()
{
    checkMoney(-150);
}
