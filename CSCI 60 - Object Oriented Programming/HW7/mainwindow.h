#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "biguint.h"        //mainwindow.h
#include <QMainWindow>
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_actionAbout_triggered();
    void on_actionQuit_triggered();
    void on_P_Add_clicked();
    void on_LE_1_textChanged(const QString &arg1);
    void on_LE_2_textChanged(const QString &arg1);
    void on_LE_3_textChanged(const QString &arg1);
    void on_P_Subtract_clicked();
    void on_P_Multiply_clicked();
    void on_P_Divide_clicked();
    void on_P_Store_clicked();
    void on_P_Recall_clicked();
    void on_P_Modulo_clicked();
    void on_P_Power_clicked();
    void on_P_Factorial_clicked();
private:
    Ui::MainWindow *ui;
    biguint _a, _b, _c;
    void update_calculator();
};
#endif // MAINWINDOW_H
