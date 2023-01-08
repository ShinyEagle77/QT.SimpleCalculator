#include "mainwindow.h"
#include "ui_mainwindow.h"


// MAKE OTHER CLASS FOR CALCULATOR WITH PRIVATE METHODS

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
    qDebug() <<"INPUT BUTTON: " + button->text() + " ";
    QString temp = ui->resultShow->text();

    if (temp.isEmpty())
    {
        displayOnLabel();
    }
    else
    {
        qDebug() << "IN MATH: " << " " + getSign() + " | " + button->text() + " ";
        if(getSign() != button->text())
        {
            if(getSign() == "=")
            {
                qDebug() << "CASE A" << Qt::endl;
                displayOnLabel();
            }
            else
            {
                qDebug() << "CASE B" << Qt::endl;
                ui->resultShow->setText(temp.left(temp.length() - 2) + " " + button->text() + " "); // rework here
            }

        }
        else
        {
            qDebug() << "CASE C" << Qt::endl;
            ui->resultShow->setText(equalOp() + " " + button->text() + " ");
        }
    }
}

QString MainWindow::equalOp() // to look up
{
    QPushButton* button = (QPushButton*) sender();
    qDebug() << "EQUALOP CALLED WITH " + button->text() + " ";
    QString entry = ui->finalResult->text(),
            temp = ui->resultShow->text(),
            result;

    if (!temp.isEmpty())
    {
        double first_num = getFirstNum().toDouble(),
               second_num = getSecondNum().toDouble();
        QString sign = getSign();

        qDebug() << "fnum: " << first_num << " | snum: " << second_num << " | sign: " << sign;

        if (sign == '+')
        {
            qDebug() << "OP + CALL";
            result = QString::number(first_num + second_num);
        }
        else if (sign == '-')
        {
            qDebug() << "OP - CALL";
            result = QString::number(second_num - first_num);
        }
        else if (sign == 'x')
        {
            qDebug() << "OP * CALL";
            result = QString::number(first_num * second_num);
        }
        else if(sign == '/')
        {
            qDebug() << "OP / CALL";
            result = QString::number(second_num / first_num);
        }

        ui->resultShow->setText(temp + removeZeros(entry) + " = ");

        ui->finalResult->setText(removeZeros(result));
        return result;
    }
}

void MainWindow::clearAll()
{
    ui->resultShow->setText("");
    ui->finalResult->setText("0");
    qDebug() << " ------------------ CLEAR ------------------ " << Qt::endl;
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

QVariant MainWindow::getFirstNum()
{
    QString final_text = ui->finalResult->text();
    return final_text.contains('.') ? final_text.toDouble() : final_text.toInt();
}

QVariant MainWindow::getSecondNum()
{
    QString labelText = ui->resultShow->text();
    if (!labelText.isEmpty())
    {
        QString temp = labelText.split(" ")[0];
        bool isFloat = temp.contains(".");

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

QString MainWindow::removeZeros(const QVariant& num)
{
    QString n = QString::number(num.toFloat());
    if (n.endsWith(".0"))
        return n.replace(".0", "");
    else
        return n;
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
