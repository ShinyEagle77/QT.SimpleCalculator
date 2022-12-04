#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QString>
#include <QLineEdit>

class Calculator : public QWidget
{
    Q_OBJECT
public:
    explicit Calculator(QWidget *parent = nullptr);

signals:

private slots:
    void digitClicked();
    void unaryOpClicked();
    void addOpClicked();
    void multiplieOpClicked();
    void equalClicked();
    void pointClicked();
    void changeSignClicked();
    void backSpaceClicked();
    void clearAll();

private:

    void abortOp();
    bool calculate(double rightOp, const QString& pendingOp);

    double finalSum, tempFactor;
    QString pendingAddOp, pendingMultiOp;
    bool waitingForOp;

    QLineEdit *display;

};

#endif // CALCULATOR_H
