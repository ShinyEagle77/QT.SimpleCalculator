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

    connect(ui->pushButton_plus, SIGNAL(clicked()), SLOT(mathOps()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), SLOT(mathOps()));
    connect(ui->pushButton_multiple, SIGNAL(clicked()), SLOT(mathOps()));               // in one container (enum)
    connect(ui->pushButton_divide, SIGNAL(clicked()), SLOT(mathOps()));

    connect(ui->pushButton_changeSign, SIGNAL(clicked()), SLOT(additionalOps()));
    connect(ui->pushButton_dot, SIGNAL(clicked()), SLOT(additionalOps()));              // in one container (enum)
    connect(ui->pushButton_percent, SIGNAL(clicked()), SLOT(additionalOps()));

    connect(ui->pushButton_equal, SIGNAL(clicked()), SLOT(equalOp()));

    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_divide->setCheckable(true);                                          // in one container (enum)
    ui->pushButton_multiple->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits_numbers()
{
    QPushButton* button = (QPushButton*)sender();

    if(ui->finalResult->text() == "0")
    {
        double input_numbers = (ui->finalResult->text() + button->text()).toDouble();
        QString digits_to_str = QString::number(input_numbers, 'g', 15);
        ui->finalResult->setText(digits_to_str);
    }
    else
    {
        ui->finalResult->setText(ui->finalResult->text() + button->text());
    }
}

void MainWindow::mathOps() // to look up on this
{
    QPushButton* button = (QPushButton*) sender();
    QString temp = ui->resultShow->text();

    if (temp.isEmpty())
    {
        displayOnLabel();
    }
    else
    {
        if(getSign() != button->text())
        {
            if(getSign() == "=")
            {
                displayOnLabel();
            }
            else
            {
                ui->resultShow->setText(temp.left(temp.length() - 2) + button->text() + " ");
            }

        }
        else
        {
            ui->resultShow->setText(equalOp() + " " + button->text());
        }
    }
}

QString MainWindow::equalOp() // to look up
{
    QString entry = ui->finalResult->text(),
            temp = ui->resultShow->text();

    if (!temp.isEmpty())
    {
        double  first_num = getFirstNum(),
                second_num = getSecondNum();
        QString sign = getSign();

        qDebug() << "first_num is " << first_num << Qt::endl << "second num is " << second_num << Qt::endl << "Sign: " << sign << Qt::endl;

        if (sign == '+')
        {
            entry = QString::number(first_num + second_num);
        }
        else if (sign == '-')
        {
            entry = QString::number(second_num - first_num);
        }
        else if (sign == '*')
        {
            entry = QString::number(first_num * second_num);
        }
        else if(sign == '/')
        {
            entry = QString::number(second_num / first_num);
        }

        ui->resultShow->setText(temp + QString::number(first_num) + " =");

        ui->finalResult->setText(entry);
        return entry;
    }
}

void MainWindow::clearAll()
{
    ui->resultShow->setText("");
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
    }
    else if (button->text() == "%")
    {
        ui->finalResult->setText(QString::number(input_number * 0.01, 'g', 15));
    }
}

double MainWindow::getFirstNum()
{
    if(ui->finalResult->text().contains('.'))
    {
        qDebug() << ("FirstNumDouble: " + QString::number(ui->finalResult->text().toDouble()));
        return ui->finalResult->text().toDouble();
    }
    else
    {
        qDebug() << ("FirstNumInt: " + QString::number(ui->finalResult->text().toInt()));
        return ui->finalResult->text().toInt();
    }
}

double MainWindow::getSecondNum()
{
    QString labelText = ui->resultShow->text();
    if (!labelText.isEmpty())
    {
        QString temp = labelText.split(" ")[0];
        bool isFloat = temp.contains(".");

        qDebug() << ("SecondNumIs: " + temp);
        return isFloat ? temp.toDouble() : temp.toInt();
    }
    return 0;
}

QString MainWindow::getSign()
{
    QString labelText = ui->resultShow->text();
    if(!labelText.isEmpty())
    {
        return labelText.split(" ")[1];
    }
    return " ";
}

QString MainWindow::removeZeros(QString num)
{
    QString n = QString::number(num.toDouble());
    return (n.right(2) == ".0") ? n.left(n.size() - 2) : n;
}

void MainWindow::displayOnLabel() // check this out
{
    QPushButton* button = (QPushButton*) sender();
    QString clear_text = removeZeros(ui->finalResult->text());

    if (ui->resultShow->text().isEmpty() || getSign() == "=")
    {
        ui->resultShow->setText(clear_text + " " + button->text() + " ");
        ui->finalResult->setText("0");
    }
}
