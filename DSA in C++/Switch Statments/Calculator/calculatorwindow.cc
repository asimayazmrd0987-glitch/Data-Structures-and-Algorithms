#include "calculatorwindow.h"

#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

CalculatorWindow::CalculatorWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("C++ Calculator");
    setFixedSize(400, 350);

    // Title
    QLabel *title = new QLabel("C++ Calculator");
    title->setAlignment(Qt::AlignCenter);

    QFont titleFont = title->font();
    titleFont.setPointSize(20);
    titleFont.setBold(true);
    title->setFont(titleFont);

    // Number 1
    number1Input = new QLineEdit();
    number1Input->setPlaceholderText("Enter first number");

    // Operator
    operatorInput = new QComboBox();
    operatorInput->addItem("+");
    operatorInput->addItem("-");
    operatorInput->addItem("*");
    operatorInput->addItem("/");

    // Number 2
    number2Input = new QLineEdit();
    number2Input->setPlaceholderText("Enter second number");

    // Calculate button
    calculateButton = new QPushButton("Calculate");

    // Result
    resultLabel = new QLabel("Result: ");
    resultLabel->setAlignment(Qt::AlignCenter);

    QFont resultFont = resultLabel->font();
    resultFont.setPointSize(14);
    resultFont.setBold(true);
    resultLabel->setFont(resultFont);

    // Layout
    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(title);
    layout->addSpacing(20);

    layout->addWidget(new QLabel("Number 1"));
    layout->addWidget(number1Input);

    layout->addWidget(new QLabel("Operator"));
    layout->addWidget(operatorInput);

    layout->addWidget(new QLabel("Number 2"));
    layout->addWidget(number2Input);

    layout->addSpacing(15);
    layout->addWidget(calculateButton);
    layout->addSpacing(15);

    layout->addWidget(resultLabel);

    setLayout(layout);

    // Button → calculate()
    connect(calculateButton, &QPushButton::clicked,
            this, &CalculatorWindow::calculate);
}

void CalculatorWindow::calculate()
{
    bool firstValid;
    bool secondValid;

    double number1 = number1Input->text().toDouble(&firstValid);
    double number2 = number2Input->text().toDouble(&secondValid);

    if (!firstValid || !secondValid)
    {
        QMessageBox::warning(
            this,
            "Invalid Input",
            "Please enter valid numbers."
        );

        return;
    }

    QString selectedOperator = operatorInput->currentText();

    double result = 0;

    if (selectedOperator == "+")
    {
        result = number1 + number2;
    }
    else if (selectedOperator == "-")
    {
        result = number1 - number2;
    }
    else if (selectedOperator == "*")
    {
        result = number1 * number2;
    }
    else if (selectedOperator == "/")
    {
        if (number2 == 0)
        {
            QMessageBox::critical(
                this,
                "Math Error",
                "You cannot divide by zero."
            );

            return;
        }

        result = number1 / number2;
    }

    resultLabel->setText(
        "Result: " + QString::number(result)
    );
}