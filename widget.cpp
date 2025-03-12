#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    deactivateButton();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::checkMoney(int v)
{
    money += v;
    if(money < 0) reset();

    ui->lcdNumber->display(money);
    activateButton(); // 금액 변경시 자동으로 버튼 활성화 체크
}

void Widget::reset()
{
    money = 0;
    ui->lcdNumber->display(money);
}

// 금액에 따른 버튼 활성화 로직
void Widget::activateButton()
{
    ui->pbCoffee->setEnabled(money >= 100);
    ui->pbWater->setEnabled(money >= 150);
    ui->pbMilkTee->setEnabled(money >= 500);
    
    /* 기존 중복 코드 제거
    if (money >= 500) {
        ui->pbCoffee->setEnabled(true);
        ui->pbMilkTee->setEnabled(true); 
        ui->pbWater->setEnabled(true);
    }
    else if (money >= 150) {
        ui->pbCoffee->setEnabled(true);
        ui->pbWater->setEnabled(true);
        ui->pbMilkTee->setEnabled(false);
    }
    else if (money >= 100) {
        ui->pbCoffee->setEnabled(true);
        ui->pbWater->setEnabled(false);
        ui->pbMilkTee->setEnabled(false);
    }
    else {
        ui->pbCoffee->setEnabled(false);
        ui->pbWater->setEnabled(false);
        ui->pbMilkTee->setEnabled(false);
    }
    */
}

// deactivateButton은 money가 0일때만 처리하므로 activateButton으로 통합 가능
void Widget::deactivateButton()
{
    switch(money)
    {
        case 0:
            ui->pbCoffee->setEnabled(false);
            ui->pbMilkTee->setEnabled(false);
            ui->pbWater->setEnabled(false);
            break;
        default:
            break;
    }
}

void Widget::on_pb10_clicked()
{
    checkMoney(10);
    // activateButton(); // checkMoney에서 처리
}

void Widget::on_pb50_clicked()
{
    checkMoney(50);
    // activateButton(); // checkMoney에서 처리
}

void Widget::on_pb100_clicked()
{
    checkMoney(100);
    // activateButton(); // checkMoney에서 처리
}

void Widget::on_pb500_clicked()
{
    checkMoney(500);
    // activateButton(); // checkMoney에서 처리
}

void Widget::on_pbReset_clicked()
{
    int temp = money;
    int num500 = temp / 500;
    temp %= 500;
    int num100 = temp / 100;
    temp %= 100;
    int num50 = temp / 50;
    temp %= 50;
    int num10 = temp / 10;

    QString msg = QString("500: %1\n100: %2\n50: %3\n10: %4")
                    .arg(num500)
                    .arg(num100)
                    .arg(num50)
                    .arg(num10);

    QMessageBox mb;
    mb.information(this, "Change", msg);
    reset();
}

// 음료 버튼 클릭시 공통 처리 함수
void Widget::handleDrinkButtonClick(int price) {
    QWidget* senderButton = qobject_cast<QPushButton*>(sender());
    if (senderButton) {
        senderButton->setEnabled(false);
    }
    checkMoney(-price);
}

void Widget::on_pbCoffee_clicked()
{
    handleDrinkButtonClick(100);
}

void Widget::on_pbMilkTee_clicked()
{
    handleDrinkButtonClick(500);
}

void Widget::on_pbWater_clicked()
{
    handleDrinkButtonClick(150);
}
