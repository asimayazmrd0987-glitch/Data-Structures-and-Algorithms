#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// ============================================================
// CONSTANTS
// ============================================================

const double EPS = 1e-8;
const double INF_THRESHOLD = 1e7;

// ============================================================
// HELPER FUNCTIONS
// ============================================================

// Checks whether a number is practically zero.
bool isZero(double value)
{
    return abs(value) < EPS;
}

// Checks whether a value is effectively infinite for our
// numerical calculation.
bool isInfiniteValue(double value)
{
    return !isnan(value) && abs(value) >= INF_THRESHOLD;
}

// ============================================================
// BASE CLASS: ExprNode
// ============================================================
//
// Every mathematical expression in our program inherits from
// this class.
//
// Examples:
//     ConstantNode
//     PowerNode
//     TrigNode
//     LogNode
//     SumNode
//     QuotientNode
//
// ============================================================

class ExprNode
{
public:
    virtual ~ExprNode() = default;

    // Converts the expression into readable text.
    virtual string toString() const = 0;

    // Calculates f(x).
    virtual double evaluate(double x) const = 0;
};

// ============================================================
// CONSTANT NODE
// ============================================================
//
// Represents:
//     c
//
// Example:
//     5
//     -3
//     2.5
//
// ============================================================

class ConstantNode : public ExprNode
{
private:
    double value;

public:
    ConstantNode(double v)
        : value(v)
    {
    }

    string toString() const override
    {
        if (value == static_cast<int>(value))
            return to_string(static_cast<int>(value));

        return to_string(value);
    }

    double evaluate(double) const override
    {
        return value;
    }
};

// ============================================================
// POWER NODE
// ============================================================
//
// Represents:
//
//     a * x^n
//
// Examples:
//
//     3x^2
//     -2x^3
//     x^5
//     7x
//
// ============================================================

class PowerNode : public ExprNode
{
private:
    double coefficient;
    double power;

public:
    PowerNode(double c, double p)
        : coefficient(c), power(p)
    {
    }

    string toString() const override
    {
        // a*x^0 = a
        if (power == 0)
        {
            if (coefficient == static_cast<int>(coefficient))
                return to_string(static_cast<int>(coefficient));

            return to_string(coefficient);
        }

        string coefficientText;

        // Don't print 1x.
        if (coefficient == 1)
        {
            coefficientText = "";
        }
        // Print -x instead of -1x.
        else if (coefficient == -1)
        {
            coefficientText = "-";
        }
        else if (coefficient == static_cast<int>(coefficient))
        {
            coefficientText =
                to_string(static_cast<int>(coefficient));
        }
        else
        {
            coefficientText =
                to_string(coefficient);
        }

        // x^1 = x
        if (power == 1)
        {
            return coefficientText + "x";
        }

        string powerText;

        if (power == static_cast<int>(power))
        {
            powerText =
                to_string(static_cast<int>(power));
        }
        else
        {
            powerText =
                to_string(power);
        }

        return coefficientText + "x^" + powerText;
    }

    double evaluate(double x) const override
    {
        return coefficient * pow(x, power);
    }
};

// ============================================================
// TRIGONOMETRIC NODE
// ============================================================

enum class TrigType
{
    SIN,
    COS,
    TAN
};

class TrigNode : public ExprNode
{
private:
    double coefficient;
    TrigType type;

public:
    TrigNode(double c, TrigType t)
        : coefficient(c), type(t)
    {
    }

    string toString() const override
    {
        string coefficientText;

        if (coefficient == 1)
        {
            coefficientText = "";
        }
        else if (coefficient == -1)
        {
            coefficientText = "-";
        }
        else if (coefficient == static_cast<int>(coefficient))
        {
            coefficientText =
                to_string(static_cast<int>(coefficient));
        }
        else
        {
            coefficientText =
                to_string(coefficient);
        }

        if (type == TrigType::SIN)
            return coefficientText + "sin(x)";

        if (type == TrigType::COS)
            return coefficientText + "cos(x)";

        return coefficientText + "tan(x)";
    }

    double evaluate(double x) const override
    {
        if (type == TrigType::SIN)
            return coefficient * sin(x);

        if (type == TrigType::COS)
            return coefficient * cos(x);

        return coefficient * tan(x);
    }
};

// ============================================================
// LOG NODE
// ============================================================
//
// Represents:
//
//     a * ln(x)
//
// Domain:
//
//     x > 0
//
// ============================================================

class LogNode : public ExprNode
{
private:
    double coefficient;

public:
    LogNode(double c)
        : coefficient(c)
    {
    }

    string toString() const override
    {
        string coefficientText;

        if (coefficient == 1)
        {
            coefficientText = "";
        }
        else if (coefficient == -1)
        {
            coefficientText = "-";
        }
        else if (coefficient == static_cast<int>(coefficient))
        {
            coefficientText =
                to_string(static_cast<int>(coefficient));
        }
        else
        {
            coefficientText =
                to_string(coefficient);
        }

        return coefficientText + "ln(x)";
    }

    double evaluate(double x) const override
    {
        // ln(x) is undefined when x <= 0.
        if (x <= 0)
        {
            return numeric_limits<double>::quiet_NaN();
        }

        return coefficient * log(x);
    }
};

// ============================================================
// SUM NODE
// ============================================================
//
// Represents:
//
//     f(x) + g(x) + h(x)
//
// Example:
//
//     3x^2 + 2x + 5
//
// ============================================================

class SumNode : public ExprNode
{
private:
    vector<unique_ptr<ExprNode>> terms;

public:
    void addTerm(unique_ptr<ExprNode> term)
    {
        terms.push_back(move(term));
    }

    string toString() const override
    {
        // If no terms were added, expression is 0.
        if (terms.empty())
            return "0";

        string result;

        for (size_t i = 0; i < terms.size(); i++)
        {
            if (i > 0)
                result += " + ";

            result += terms[i]->toString();
        }

        return result;
    }

    double evaluate(double x) const override
    {
        double result = 0.0;

        for (const auto &term : terms)
        {
            double value = term->evaluate(x);

            // If one term is invalid, the entire expression
            // is invalid.
            if (isnan(value))
                return numeric_limits<double>::quiet_NaN();

            result += value;
        }

        return result;
    }
};

// ============================================================
// QUOTIENT NODE
// ============================================================
//
// Represents:
//
//          N(x)
//     f(x) = -----
//          D(x)
//
// ============================================================

class QuotientNode : public ExprNode
{
private:
    unique_ptr<ExprNode> numerator;
    unique_ptr<ExprNode> denominator;

public:
    QuotientNode(
        unique_ptr<ExprNode> n,
        unique_ptr<ExprNode> d)
        : numerator(move(n)),
          denominator(move(d))
    {
    }

    string toString() const override
    {
        return "(" + numerator->toString() +
               ") / (" + denominator->toString() + ")";
    }

    double evaluate(double x) const override
    {
        double numeratorValue =
            numerator->evaluate(x);

        double denominatorValue =
            denominator->evaluate(x);

        // Invalid numerator/denominator.
        if (isnan(numeratorValue) ||
            isnan(denominatorValue))
        {
            return numeric_limits<double>::quiet_NaN();
        }

        // Division by zero is undefined.
        if (isZero(denominatorValue))
        {
            return numeric_limits<double>::quiet_NaN();
        }

        return numeratorValue / denominatorValue;
    }
};

// ============================================================
// BUILD EXPRESSION
// ============================================================
//
// Allows the user to create an expression term-by-term.
//
// Example:
//
//     2x^2 + 3sin(x) + ln(x) + 5
//
// ============================================================

unique_ptr<ExprNode> buildExpression()
{
    auto expression =
        make_unique<SumNode>();

    while (true)
    {
        cout << "\n";
        cout << "------------------------------------------\n";
        cout << "         ADD TERM TO EXPRESSION\n";
        cout << "------------------------------------------\n";

        cout << "1. Power term      (a * x^n)\n";
        cout << "2. Trigonometric   (a * sin/cos/tan(x))\n";
        cout << "3. Logarithm       (a * ln(x))\n";
        cout << "4. Constant        (c)\n";
        cout << "5. Finish expression\n";

        cout << "\nEnter choice: ";

        int choice;
        cin >> choice;

        if (choice == 5)
        {
            break;
        }

        // ----------------------------------------------------
        // POWER TERM
        // ----------------------------------------------------

        if (choice == 1)
        {
            double coefficient;
            double power;

            cout << "\nCoefficient (a): ";
            cin >> coefficient;

            cout << "Power (n): ";
            cin >> power;

            expression->addTerm(
                make_unique<PowerNode>(
                    coefficient,
                    power));

            cout << "Power term added successfully.\n";
        }

        // ----------------------------------------------------
        // TRIGONOMETRIC TERM
        // ----------------------------------------------------

        else if (choice == 2)
        {
            double coefficient;
            int trigChoice;

            cout << "\nCoefficient (a): ";
            cin >> coefficient;

            cout << "\nChoose function:\n";
            cout << "1. sin(x)\n";
            cout << "2. cos(x)\n";
            cout << "3. tan(x)\n";

            cout << "Enter choice: ";
            cin >> trigChoice;

            if (trigChoice < 1 || trigChoice > 3)
            {
                cout << "Invalid trigonometric choice.\n";
                continue;
            }

            TrigType type;

            if (trigChoice == 1)
                type = TrigType::SIN;

            else if (trigChoice == 2)
                type = TrigType::COS;

            else
                type = TrigType::TAN;

            expression->addTerm(
                make_unique<TrigNode>(
                    coefficient,
                    type));

            cout << "Trigonometric term added successfully.\n";
        }

        // ----------------------------------------------------
        // LOGARITHM TERM
        // ----------------------------------------------------

        else if (choice == 3)
        {
            double coefficient;

            cout << "\nCoefficient (a): ";
            cin >> coefficient;

            expression->addTerm(
                make_unique<LogNode>(
                    coefficient));

            cout << "Logarithm term added successfully.\n";
        }

        // ----------------------------------------------------
        // CONSTANT
        // ----------------------------------------------------

        else if (choice == 4)
        {
            double value;

            cout << "\nConstant value: ";
            cin >> value;

            expression->addTerm(
                make_unique<ConstantNode>(
                    value));

            cout << "Constant added successfully.\n";
        }

        else
        {
            cout << "Invalid choice. Please choose 1-5.\n";
        }
    }

    return expression;
}

// ============================================================
// DISPLAY LIMIT RESULT
// ============================================================

void displaySideResult(
    const string &sideName,
    double value)
{
    cout << left
         << setw(28)
         << sideName
         << ": ";

    if (isnan(value))
    {
        cout << "Undefined";
    }

    else if (isInfiniteValue(value))
    {
        if (value > 0)
            cout << "+Infinity";
        else
            cout << "-Infinity";
    }

    else
    {
        cout << fixed
             << setprecision(6)
             << value;
    }

    cout << "\n";
}

// ============================================================
// CALCULATE NUMERICAL LIMIT
// ============================================================
//
// Calculates:
//
//              lim f(x)
//         x -> a
//
// by approaching 'a' from both sides.
//
// Left:
//
//     x = a - epsilon
//
// Right:
//
//     x = a + epsilon
//
// IMPORTANT:
// This is numerical approximation, not symbolic calculus.
//
// ============================================================

void calculateLimit(
    const ExprNode &expression,
    double target)
{
    const double epsilon = 1e-7;

    // Evaluate from the left.
    double leftValue =
        expression.evaluate(target - epsilon);

    // Evaluate from the right.
    double rightValue =
        expression.evaluate(target + epsilon);

    cout << "\n\n";
    cout << "==========================================\n";
    cout << "              LIMIT RESULT\n";
    cout << "==========================================\n";

    cout << "Function:\n";
    cout << "f(x) = "
         << expression.toString()
         << "\n\n";

    cout << "Limit point:\n";
    cout << "x -> "
         << fixed
         << setprecision(6)
         << target
         << "\n\n";

    displaySideResult(
        "Left-Hand Limit",
        leftValue);

    displaySideResult(
        "Right-Hand Limit",
        rightValue);

    cout << "\n------------------------------------------\n";

    if (isInfiniteValue(leftValue) &&
        isInfiniteValue(rightValue) &&
        leftValue > 0 &&
        rightValue > 0)
    {
        cout << "LIMIT = +Infinity\n";
    }

    else if (isInfiniteValue(leftValue) &&
             isInfiniteValue(rightValue) &&
             leftValue < 0 &&
             rightValue < 0)
    {
        cout << "LIMIT = -Infinity\n";
    }

    else if (!isnan(leftValue) &&
             !isnan(rightValue) &&
             !isInfiniteValue(leftValue) &&
             !isInfiniteValue(rightValue) &&
             abs(leftValue - rightValue) < 1e-4)
    {
        double answer =
            (leftValue + rightValue) / 2.0;

        cout << "LIMIT = "
             << fixed
             << setprecision(6)
             << answer
             << "\n";
    }

    else
    {
        cout << "LIMIT = DNE\n";
        cout << "(Does Not Exist)\n";
    }

    cout << "==========================================\n";
}

int main()
{
    cout << "\n";
    cout << "==========================================\n";
    cout << "       C++ NUMERICAL LIMIT CALCULATOR\n";
    cout << "==========================================\n";

    cout << "\nThis program supports:\n";
    cout << "  * Polynomial expressions\n";
    cout << "  * sin(x), cos(x), tan(x)\n";
    cout << "  * ln(x)\n";
    cout << "  * Rational expressions\n";
    cout << "  * Left-hand and right-hand limits\n";

    cout << "\n------------------------------------------\n";
    cout << "              MAIN MENU\n";
    cout << "------------------------------------------\n";

    cout << "1. Single expression\n";
    cout << "2. Rational expression\n";

    cout << "\nEnter your choice: ";

    int choice;
    cin >> choice;

    if (choice != 1 && choice != 2)
    {
        cout << "\nInvalid choice. Program terminated.\n";
        return 1;
    }

    unique_ptr<ExprNode> function;

    if (choice == 1)
    {
        cout << "\n";
        cout << "==========================================\n";
        cout << "          BUILDING f(x)\n";
        cout << "==========================================\n";

        function =
            buildExpression();
    }

  
    else
    {
        cout << "\n";
        cout << "==========================================\n";
        cout << "          BUILDING NUMERATOR\n";
        cout << "==========================================\n";

        auto numerator =
            buildExpression();

        cout << "\n";
        cout << "==========================================\n";
        cout << "         BUILDING DENOMINATOR\n";
        cout << "==========================================\n";

        auto denominator =
            buildExpression();

        function =
            make_unique<QuotientNode>(
                move(numerator),
                move(denominator));
    }


    cout << "\n";
    cout << "==========================================\n";
    cout << "          FUNCTION CREATED\n";
    cout << "==========================================\n";

    cout << "f(x) = "
         << function->toString()
         << "\n";


    double target;

    cout << "\nEnter the value of a:\n";
    cout << "Calculate lim (x -> a) f(x)\n";

    cout << "\na = ";
    cin >> target;

    calculateLimit(
        *function,
        target);

    cout << "\nThank you for using the calculator!\n";

    return 0;
}