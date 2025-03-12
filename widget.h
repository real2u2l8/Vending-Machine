#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    
    int money{0}; //this day c++ has to initialize with {}
    int v;

    void checkMoney(int v);
    void reset();
    void activateButton();
    void deactivateButton();
    void handleDrinkButtonClick(int price); 

private slots:
    void on_pb10_clicked();

    void on_pb50_clicked();

    void on_pb100_clicked();

    void on_pb500_clicked();

    void on_pbReset_clicked();

    void on_pbCoffee_clicked();

    void on_pbMilkTee_clicked();

    void on_pbWater_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
