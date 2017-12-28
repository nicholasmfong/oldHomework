#include "mainwindow.h"
#include "ui_mainwindow.h"          //mainwindow.cpp
#include <QMessageBox>
#include <iostream>
using std::cout;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}
void MainWindow::on_actionAbout_triggered(){
    QMessageBox::about(this,tr("About Calculator"),
                       tr("<h2>Nicholas Fong Calculator</h2>"
                          "<p> Copyight &copy; 2015 CS 60. Section2<br>"
                          "Results are stored in Input 1, while the functions use Input 2 on 1.<br>"
                          "Store puts Input 1 into Memory, Recall puts Memory into Input 2.<br>"
                          "All numbers must be whole numbers."));
}
void MainWindow::on_actionQuit_triggered(){
    exit(0);
}
void MainWindow::update_calculator(){
    ui->LE_1->setText(QString(_a.toQString()));
    ui->LE_2->setText(QString(_b.toQString()));
    ui->LE_3->setText(QString(_c.toQString()));
}
void MainWindow::on_P_Add_clicked(){
    _a += _b;
    update_calculator();
}
void MainWindow::on_LE_1_textChanged(const QString &arg1){
    _a = arg1.toStdString();
}
void MainWindow::on_LE_2_textChanged(const QString &arg1){
    _b = arg1.toStdString();
}
void MainWindow::on_LE_3_textChanged(const QString &arg1){
    _c = arg1.toStdString();
}
void MainWindow::on_P_Subtract_clicked(){
    if(_a > _b){
        _a -= _b;
    }
    else{
        _a = biguint("0",1);
    }
    update_calculator();
}
void MainWindow::on_P_Multiply_clicked(){
    _a *= _b;
    update_calculator();
}
void MainWindow::on_P_Divide_clicked(){
    _a /= _b;
    update_calculator();
}
void MainWindow::on_P_Store_clicked(){
    _c = _a;
    update_calculator();
}
void MainWindow::on_P_Recall_clicked(){
    _b = _c;
    update_calculator();
}
void MainWindow::on_P_Modulo_clicked(){
    _a %= _b;
    update_calculator();
}
void MainWindow::on_P_Power_clicked(){
    biguint a = _a;
    for(biguint i(1,1); i < _b; i+= 1){
        _a *= a;
    }
    update_calculator();
}
void MainWindow::on_P_Factorial_clicked(){
    biguint num(1,1);
    for(biguint i = _a; i > 1; i-= 1){
        num *= i;
    }
    _a = num;
    update_calculator();
}
