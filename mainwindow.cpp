#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0, SIGNAL(clicked()), SLOT(digits_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), SLOT(digits_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), SLOT(digits_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), SLOT(digits_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), SLOT(digits_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), SLOT(digits_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), SLOT(digits_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), SLOT(digits_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), SLOT(digits_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), SLOT(digits_numbers()));

    connect(ui->pushButton_ac, SIGNAL(clicked()), SLOT(clearAll()));
    connect(ui->pushButton_backspace, SIGNAL(clicked()), SLOT(backspace()));

    connect(ui->pushButton_plus, SIGNAL(clicked()), SLOT(binaryOp()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), SLOT(binaryOp()));

    connect(ui->pushButton_multiple, SIGNAL(clicked()), SLOT(multipleOp()));
    connect(ui->pushButton_divide, SIGNAL(clicked()), SLOT(multipleOp()));

    connect(ui->pushButton_changeSign, SIGNAL(clicked()), SLOT(changeSign()));

    connect(ui->pushButton_dot, SIGNAL(clicked()), SLOT(commaOp()));
    connect(ui->pushButton_percent, SIGNAL(clicked()), SLOT(percentOp()));

    connect(ui->pushButton_equal, SIGNAL(clicked()), SLOT(equalOp()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits_numbers()
{
    QPushButton* button = (QPushButton*)sender();

    ui->statusBar->showMessage(QString::number(ui->resultShow->text().size(), 'g', 15));

    double input_numbers = (ui->resultShow->text() + button->text()).toDouble();
    QString digits_to_str = QString::number(input_numbers, 'g', 15);

    ui->resultShow->setText(digits_to_str);
}

void MainWindow::clearAll()
{
    ui->resultShow->setText("0");
    ui->finalResult->setText("0");
}

void MainWindow::backspace()
{
    QString str = ui->resultShow->text();
    if(str.size() == 1)
    {
        ui->resultShow->setText("0");
    }
    else
    {
        if(str.size() >= 15)
        {
            double input_number = str.toDouble();

            ui->statusBar->showMessage(QString::number(input_number, 'g', 15));
        }
        else
        {
            ui->resultShow->setText(str.remove(str.size() - 1, 1));
        }

    }
}

void MainWindow::binaryOp()
{

}

void MainWindow::multipleOp()
{

}

void MainWindow::changeSign()
{
    double input_number = ui->resultShow->text().toDouble();
    ui->resultShow->setText(QString::number(input_number * (-1), 'g', 15));
}

void MainWindow::commaOp()
{
    if(!ui->resultShow->text().contains("."))
    {
        ui->resultShow->setText(ui->resultShow->text() + ".");
    }
}

void MainWindow::percentOp()
{
    double input_number = ui->resultShow->text().toDouble();
    ui->resultShow->setText(QString::number(input_number * 0.01, 'g', 15));
}

void MainWindow::equalOp()
{

}
