#ifndef CALCULATORWINDOW_H
#define CALCULATORWINDOW_H

#include <QWidget>

class QLineEdit;
class QComboBox;
class QPushButton;
class QLabel;

class CalculatorWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CalculatorWindow(QWidget *parent = nullptr);

private slots:
    void calculate();

private:
    QLineEdit *number1Input;
    QLineEdit *number2Input;
    QComboBox *operatorInput;
    QPushButton *calculateButton;
    QLabel *resultLabel;
};

#endif