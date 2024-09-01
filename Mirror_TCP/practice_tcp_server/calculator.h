#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>

class Calculator : public QObject
{
    Q_OBJECT
public:
    explicit Calculator(QObject* parent = nullptr);

    double display() const;
    void setDisplay(double newDisplay);

private:
    double mDisplay ;
    double mFirstOperand ;
    double mSecondOperand ;
    bool mWaitingForSecondOperand ;
    QString Op ;

    void DigitPressed(QString digit) ;
    void OperatorPressed(QString op) ;
    void clear() ;
    void equal_Pressed() ;


signals:
    void DisplayChanged() ;
    void buttonClicked(QString btn) ;
    void timeOut() ;
public slots:
    void onBtnClicked(QString btn) ;
};

#endif // CALCULATOR_H
