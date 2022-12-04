#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));

    connect(ui->pushButton_ac, SIGNAL(clicked()), this, SLOT(clearAll()));
    connect(ui->pushButton_backspace, SIGNAL(clicked()), this, SLOT(backspace()));

    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(binaryOp()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(binaryOp()));

    connect(ui->pushButton_multiple, SIGNAL(clicked()), this, SLOT(multipleOp()));
    connect(ui->pushButton_divide, SIGNAL(clicked()), this, SLOT(multipleOp()));

    connect(ui->pushButton_changeSign, SIGNAL(clicked()), this, SLOT(changeSign()));

    connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(commaOp()));
    connect(ui->pushButton_percent, SIGNAL(clicked()), this, SLOT(percentOp()));

    connect(ui->pushButton_equal, SIGNAL(clicked()), this, SLOT(equalOp()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits_numbers()
{
    QPushButton* button = (QPushButton*)sender();
}

void MainWindow::clearAll()
{

}

void MainWindow::backspace()
{

}

void MainWindow::binaryOp()
{

}

void MainWindow::multipleOp()
{

}

void MainWindow::changeSign()
{

}

void MainWindow::commaOp()
{

}

void MainWindow::percentOp()
{

}

void MainWindow::equalOp()
{

}
