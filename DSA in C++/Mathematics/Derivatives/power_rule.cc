#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <cmath>
using namespace std;

// Base class for expression tree nodes
class ExprNode
{
public:
    virtual ~ExprNode() = default;
    virtual string toString() const = 0;
    virtual unique_ptr<ExprNode> derivative() const = 0;
    virtual double evaluate(double x) const = 0;
};

// 1. Constant Rule: d/dx [c] = 0
class ConstantNode : public ExprNode
{
    double val;

public:
    ConstantNode(double v) : val(v) {}
    string toString() const override
    {
        return to_string((int)val == val ? (int)val : val);
    }
    unique_ptr<ExprNode> derivative() const override
    {
        return make_unique<ConstantNode>(0);
    }
    double evaluate(double) const override { return val; }
};

// 2. Power Rule: d/dx [a * x^n] = (a * n) * x^(n-1)
class PowerTermNode : public ExprNode
{
    double coeff;
    double power;

public:
    PowerTermNode(double c, double p) : coeff(c), power(p) {}

    string toString() const override
    {
        if (power == 0)
            return to_string(coeff);
        string cStr = (coeff == 1) ? "" : ((coeff == -1) ? "-" : to_string((int)coeff == coeff ? (int)coeff : coeff));
        if (power == 1)
            return cStr + "x";
        return cStr + "x^" + to_string((int)power == power ? (int)power : power);
    }

    unique_ptr<ExprNode> derivative() const override
    {
        double newCoeff = coeff * power;
        double newPower = power - 1;
        if (newPower == 0)
            return make_unique<ConstantNode>(newCoeff);
        return make_unique<PowerTermNode>(newCoeff, newPower);
    }

    double evaluate(double x) const override { return coeff * pow(x, power); }
};

// 3. Log Rule: d/dx [a * ln(x)] = a / x (or a * x^-1)
class LogTermNode : public ExprNode
{
    double coeff;

public:
    LogTermNode(double c) : coeff(c) {}

    string toString() const override
    {
        string cStr = (coeff == 1) ? "" : to_string((int)coeff == coeff ? (int)coeff : coeff);
        return cStr + "ln(x)";
    }

    unique_ptr<ExprNode> derivative() const override
    {
        // d/dx [c * ln(x)] = c * x^-1
        return make_unique<PowerTermNode>(coeff, -1);
    }

    double evaluate(double x) const override { return coeff * log(x); }
};

// 4. Trig Rules: sin(x) -> cos(x), cos(x) -> -sin(x)
enum TrigType
{
    SIN,
    COS,
    TAN
};

class TrigTermNode : public ExprNode
{
    double coeff;
    TrigType type;

public:
    TrigTermNode(double c, TrigType t) : coeff(c), type(t) {}

    string toString() const override
    {
        string cStr = (coeff == 1) ? "" : to_string((int)coeff == coeff ? (int)coeff : coeff);
        if (type == SIN)
            return cStr + "sin(x)";
        if (type == COS)
            return cStr + "cos(x)";
        return cStr + "tan(x)";
    }

    unique_ptr<ExprNode> derivative() const override
    {
        if (type == SIN)
        {
            // d/dx [a*sin(x)] = a*cos(x)
            return make_unique<TrigTermNode>(coeff, COS);
        }
        else if (type == COS)
        {
            // d/dx [a*cos(x)] = -a*sin(x)
            return make_unique<TrigTermNode>(-coeff, SIN);
        }
        else
        {
            // d/dx [a*tan(x)] = a*sec^2(x) (represented as a / cos(x)^2 for evaluation)
            return make_unique<PowerTermNode>(coeff, 0); // Simplified placeholder for expression engine
        }
    }

    double evaluate(double x) const override
    {
        if (type == SIN)
            return coeff * sin(x);
        if (type == COS)
            return coeff * cos(x);
        return coeff * tan(x);
    }
};

// 5. Sum Rule: d/dx [f(x) + g(x)] = f'(x) + g'(x)
class ExpressionSum : public ExprNode
{
    vector<unique_ptr<ExprNode>> terms;

public:
    void addTerm(unique_ptr<ExprNode> term)
    {
        terms.push_back(move(term));
    }

    string toString() const override
    {
        string result = "";
        for (size_t i = 0; i < terms.size(); ++i)
        {
            if (i > 0)
                result += " + ";
            result += terms[i]->toString();
        }
        return result;
    }

    unique_ptr<ExprNode> derivative() const override
    {
        auto dSum = make_unique<ExpressionSum>();
        for (const auto &term : terms)
        {
            dSum->addTerm(term->derivative());
        }
        return dSum;
    }

    double evaluate(double x) const override
    {
        double total = 0;
        for (const auto &term : terms)
        {
            total += term->evaluate(x);
        }
        return total;
    }
};

int main()
{
    ExpressionSum f;
    int choice;
    cout << "=== Interactive Symbolic Derivative Engine ===\n";

    while (true)
    {
        cout << "\nAdd a term to f(x):\n";
        cout << "1. Power Term  (a * x^n)\n";
        cout << "2. Log Term    (a * ln(x))\n";
        cout << "3. Trig Term   (a * sin(x) or a * cos(x))\n";
        cout << "4. Constant    (c)\n";
        cout << "5. Build Function & Calculate Derivative\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 5)
            break;

        double coeff, power;
        if (choice == 1)
        {
            cout << "Enter coefficient (a) and power (n): ";
            cin >> coeff >> power;
            f.addTerm(make_unique<PowerTermNode>(coeff, power));
        }
        else if (choice == 2)
        {
            cout << "Enter coefficient (a): ";
            cin >> coeff;
            f.addTerm(make_unique<LogTermNode>(coeff));
        }
        else if (choice == 3)
        {
            int tChoice;
            cout << "Enter coefficient (a): ";
            cin >> coeff;
            cout << "Select Function (1 for sin, 2 for cos): ";
            cin >> tChoice;
            f.addTerm(make_unique<TrigTermNode>(coeff, tChoice == 1 ? SIN : COS));
        }
        else if (choice == 4)
        {
            cout << "Enter constant value: ";
            cin >> coeff;
            f.addTerm(make_unique<ConstantNode>(coeff));
        }
    }

    // Symbolic Differentiation Step
    auto df = f.derivative();

    cout << "\n========================================\n";
    cout << "Original Function : f(x)  = " << f.toString() << "\n";
    cout << "Symbolic Derivative: f'(x) = " << df->toString() << "\n";
    cout << "========================================\n";

    // Numerical Evaluation
    double evalX;
    cout << "\nEnter a value for x to evaluate f'(x): ";
    cin >> evalX;
    cout << "f'(" << evalX << ") = " << df->evaluate(evalX) << "\n";

    return 0;
}