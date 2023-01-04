#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void digits_numbers();
    void mathOps();
    void additionalOps();

    QString equalOp();

    void backspace();
    void clearAll();

    QString removeZeros(QString num);
    void displayOnLabel();

    double getFirstNum();
    double getSecondNum();
    QString getSign();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
