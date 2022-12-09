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
    connect(ui->pushButton_5, SIGNAL(clicked()), SLOT(digits_numbers()));               // in one container (enum)
    connect(ui->pushButton_6, SIGNAL(clicked()), SLOT(digits_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), SLOT(digits_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), SLOT(digits_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), SLOT(digits_numbers()));

    connect(ui->pushButton_ac, SIGNAL(clicked()), SLOT(clearAll()));
    connect(ui->pushButton_backspace, SIGNAL(clicked()), SLOT(backspace()));

    connect(ui->pushButton_plus, SIGNAL(clicked()), SLOT(displayOnLabel()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), SLOT(mathOps()));
    connect(ui->pushButton_multiple, SIGNAL(clicked()), SLOT(mathOps()));               // in one container (enum)
    connect(ui->pushButton_divide, SIGNAL(clicked()), SLOT(mathOps()));

    connect(ui->pushButton_changeSign, SIGNAL(clicked()), SLOT(additionalOps()));
    connect(ui->pushButton_dot, SIGNAL(clicked()), SLOT(additionalOps()));              // in one container (enum)
    connect(ui->pushButton_percent, SIGNAL(clicked()), SLOT(additionalOps()));

    connect(ui->pushButton_equal, SIGNAL(clicked()), SLOT(equalOp()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits_numbers()
{
    QPushButton* button = (QPushButton*)sender();

    ui->statusBar->showMessage(QString::number(ui->finalResult->text().size(), 'g', 15));

    double input_numbers = (ui->finalResult->text() + button->text()).toDouble();
    QString digits_to_str = QString::number(input_numbers, 'g', 15);

    ui->finalResult->setText(digits_to_str);
}

void MainWindow::clearAll()
{
    ui->resultShow->setText("0");
    ui->finalResult->setText("0");
}

void MainWindow::backspace()
{
    QString str = ui->finalResult->text();
    if(str.size() == 1 || (str.size() == 2 && str.contains('-')))
    {
        ui->finalResult->setText("0");
    }
    else
    {
        str.chop(1);
        ui->finalResult->setText(str);
    }
}

void MainWindow::mathOps()
{
    QPushButton* button = (QPushButton*) sender();

    button->setChecked(true);
}

void MainWindow::additionalOps()
{
    QPushButton* button = (QPushButton*) sender();

    double input_number = ui->finalResult->text().toDouble();
    if (button->text() == "+/-")
    {
        ui->finalResult->setText(QString::number(input_number * (-1), 'g', 15));
    }
    else if (button->text() == ".")
    {
        if(!ui->finalResult->text().contains("."))
        {
            ui->finalResult->setText(ui->finalResult->text() + ".");
        }
    } else if (button->text() == "%")
    {
        ui->finalResult->setText(QString::number(input_number * 0.01, 'g', 15));
    }
}

void MainWindow::equalOp()
{

}

void MainWindow::displayOnLabel()
{
    QPushButton* button = (QPushButton*) sender();

    if (ui->resultShow->text().isEmpty())
    {
        ui->resultShow->setText(ui->finalResult->text() + " " + button->text() + " ");
        ui->finalResult->setText("0");
    }
}
