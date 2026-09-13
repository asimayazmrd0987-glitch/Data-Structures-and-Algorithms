#include <bits/stdc++.h>
using namespace std;

struct DerivResult
{
    string expr;
    string step;
};

string toLowerString(string s)
{
    transform(
        s.begin(),
        s.end(),
        s.begin(),
        [](unsigned char c)
        {
            return static_cast<char>(tolower(c));
        });

    return s;
}

void replaceAllInPlace(string &s, const string &from, const string &to)
{
    if (from.empty())
    {
        return;
    }

    size_t pos = 0;

    while ((pos = s.find(from, pos)) != string::npos)
    {
        s.replace(pos, from.size(), to);
        pos += to.size();
    }
}

string replaceAllCopy(string s, const string &from, const string &to)
{
    replaceAllInPlace(s, from, to);
    return s;
}

bool isBlank(const string &s)
{
    return all_of(
        s.begin(),
        s.end(),
        [](unsigned char c)
        {
            return isspace(c);
        });
}

bool isNumber(const string &s)
{
    if (s.empty())
    {
        return false;
    }

    size_t i = 0;

    if (s[i] == '+' || s[i] == '-')
    {
        ++i;
    }

    bool hasDigit = false;
    bool hasDot = false;

    for (; i < s.size(); ++i)
    {
        unsigned char uc = static_cast<unsigned char>(s[i]);

        if (isdigit(uc))
        {
            hasDigit = true;
        }
        else if (s[i] == '.' && !hasDot)
        {
            hasDot = true;
        }
        else
        {
            return false;
        }
    }

    return hasDigit;
}

string formatNumber(double v)
{
    if (!std::isfinite(v))
    {
        return "0";
    }

    if (std::fabs(v) < 1e-12)
    {
        return "0";
    }

    if (std::fabs(v - std::round(v)) < 1e-12 && std::fabs(v) < 1e15)
    {
        return to_string(static_cast<long long>(std::round(v)));
    }

    ostringstream oss;
    oss << setprecision(10) << v;
    return oss.str();
}

string insertSpacesBetweenDigitAndLetter(const string &s)
{
    string out;

    for (size_t i = 0; i < s.size(); ++i)
    {
        out += s[i];

        if (i + 1 < s.size())
        {
            unsigned char current = static_cast<unsigned char>(s[i]);
            unsigned char next = static_cast<unsigned char>(s[i + 1]);

            if (isdigit(current) && isalpha(next))
            {
                // Keep forms like 2x, 3x^2 compact.
                bool simpleX =
                    s[i + 1] == 'x' &&
                    (i + 2 >= s.size() || !isalpha(static_cast<unsigned char>(s[i + 2])));

                if (!simpleX)
                {
                    out += ' ';
                }
            }
        }
    }

    return out;
}

string addSpacesAroundPlusMinus(const string &s)
{
    string out;

    for (size_t i = 0; i < s.size(); ++i)
    {
        char c = s[i];

        if (c == '+' || c == '-')
        {
            bool unary = false;

            if (i == 0)
            {
                unary = true;
            }
            else
            {
                char prev = s[i - 1];

                if (
                    prev == '^' ||
                    prev == '(' ||
                    prev == '*' ||
                    prev == '/' ||
                    prev == '+' ||
                    prev == '-' ||
                    prev == ' ')
                {
                    unary = true;
                }
            }

            if (unary)
            {
                out += c;
            }
            else
            {
                if (!out.empty() && out.back() != ' ')
                {
                    out += ' ';
                }

                out += c;

                if (i + 1 < s.size() && s[i + 1] != ' ')
                {
                    out += ' ';
                }
            }
        }
        else
        {
            out += c;
        }
    }

    return out;
}

string pretty(string s)
{
    replaceAllInPlace(s, "*", " ");

    s = insertSpacesBetweenDigitAndLetter(s);

    replaceAllInPlace(s, "sec^2x", "sec^2 x");
    replaceAllInPlace(s, "log10x", "log10 x");
    replaceAllInPlace(s, "sinx", "sin x");
    replaceAllInPlace(s, "cosx", "cos x");
    replaceAllInPlace(s, "tanx", "tan x");
    replaceAllInPlace(s, "lnx", "ln x");
    replaceAllInPlace(s, "logx", "log x");
    replaceAllInPlace(s, "sqrtx", "sqrt x");
    replaceAllInPlace(s, "expx", "e^x");

    s = addSpacesAroundPlusMinus(s);

    // Collapse multiple spaces.
    string collapsed;
    bool previousWasSpace = false;

    for (char c : s)
    {
        if (c == ' ')
        {
            if (!previousWasSpace)
            {
                collapsed += c;
            }

            previousWasSpace = true;
        }
        else
        {
            collapsed += c;
            previousWasSpace = false;
        }
    }

    // Trim spaces.
    size_t first = collapsed.find_first_not_of(' ');
    if (first == string::npos)
    {
        return "";
    }

    size_t last = collapsed.find_last_not_of(' ');
    return collapsed.substr(first, last - first + 1);
}

string stripOuterParentheses(string s)
{
    while (s.size() >= 2 && s.front() == '(' && s.back() == ')')
    {
        int depth = 0;
        bool closesAtEnd = false;

        for (size_t i = 0; i < s.size(); ++i)
        {
            if (s[i] == '(')
            {
                ++depth;
            }
            else if (s[i] == ')')
            {
                --depth;

                if (depth == 0)
                {
                    if (i == s.size() - 1)
                    {
                        closesAtEnd = true;
                    }

                    break;
                }
            }
        }

        if (closesAtEnd)
        {
            s = s.substr(1, s.size() - 2);
        }
        else
        {
            break;
        }
    }

    return s;
}

string cleanInput(string s)
{
    s = toLowerString(s);

    // Allow ** as power.
    replaceAllInPlace(s, "**", "^");

    // Allow user to write d/dx(expression).
    replaceAllInPlace(s, "d/dx", "");

    string out;

    for (char c : s)
    {
        unsigned char uc = static_cast<unsigned char>(c);

        if (
            !isspace(uc) &&
            c != '[' &&
            c != ']' &&
            c != '{' &&
            c != '}' &&
            c != '*')
        {
            out += c;
        }
    }

    return stripOuterParentheses(out);
}

string normalizeExpr(string s)
{
    s = toLowerString(s);

    string out;

    for (char c : s)
    {
        unsigned char uc = static_cast<unsigned char>(c);

        if (
            !isspace(uc) &&
            c != '*' &&
            c != '[' &&
            c != ']')
        {
            out += c;
        }
    }

    return stripOuterParentheses(out);
}

size_t findTopLevelSlash(const string &s)
{
    int depth = 0;

    for (size_t i = 0; i < s.size(); ++i)
    {
        if (s[i] == '(')
        {
            ++depth;
        }
        else if (s[i] == ')')
        {
            --depth;
        }
        else if (s[i] == '/' && depth == 0)
        {
            return i;
        }
    }

    return string::npos;
}

size_t findTopLevelAddSub(const string &e)
{
    int depth = 0;

    for (size_t i = 0; i < e.size(); ++i)
    {
        char c = e[i];

        if (c == '(')
        {
            ++depth;
        }
        else if (c == ')')
        {
            --depth;
        }
        else if (depth == 0 && (c == '+' || c == '-'))
        {
            if (i == 0)
            {
                continue;
            }

            char prev = e[i - 1];

            if (
                prev == '^' ||
                prev == '(' ||
                prev == '+' ||
                prev == '-' ||
                prev == '*' ||
                prev == '/')
            {
                continue;
            }

            return i;
        }
    }

    return string::npos;
}

string wrapIfAddSub(string s)
{
    if (findTopLevelAddSub(s) != string::npos)
    {
        return "(" + s + ")";
    }

    return s;
}

pair<string, string> splitLeadingCoefficient(const string &e)
{
    if (e.empty())
    {
        return {"", e};
    }

    size_t i = 0;

    if (i < e.size() && (e[i] == '+' || e[i] == '-'))
    {
        ++i;
    }

    bool hasDigit = false;

    while (i < e.size() && (isdigit(static_cast<unsigned char>(e[i])) || e[i] == '.'))
    {
        hasDigit = true;
        ++i;
    }

    if (!hasDigit || i == 0 || i >= e.size())
    {
        return {"", e};
    }

    char next = e[i];

    if (isalpha(static_cast<unsigned char>(next)) || next == '(')
    {
        return {e.substr(0, i), e.substr(i)};
    }

    return {"", e};
}

struct FuncInfo
{
    string name;
    string inner;
};

FuncInfo parseFunction(const string &e)
{
    vector<string> names =
        {
            "sqrt",
            "log10",
            "sin",
            "cos",
            "tan",
            "ln",
            "log",
            "exp"};

    for (const string &name : names)
    {
        if (e.size() > name.size() && e.rfind(name, 0) == 0)
        {
            size_t start = e.find('(', name.size());

            if (start != string::npos && e.back() == ')')
            {
                string inner = e.substr(start + 1, e.size() - start - 2);
                return {name, inner};
            }
        }
    }

    return {"", ""};
}

string multiply(string a, string b)
{
    if (a.empty())
    {
        return b;
    }

    if (b.empty())
    {
        return a;
    }

    if (a == "0" || b == "0")
    {
        return "0";
    }

    if (a == "1")
    {
        return b;
    }

    if (b == "1")
    {
        return a;
    }

    if (a == "-1")
    {
        if (!b.empty() && b[0] == '-')
        {
            return b.substr(1);
        }

        return "-" + b;
    }

    if (b == "-1")
    {
        if (!a.empty() && a[0] == '-')
        {
            return a.substr(1);
        }

        return "-" + a;
    }

    if (!a.empty() && !b.empty() && a[0] == '-' && b[0] == '-')
    {
        return multiply(a.substr(1), b.substr(1));
    }

    if (!a.empty() && a[0] == '-')
    {
        return "-" + multiply(a.substr(1), b);
    }

    if (!b.empty() && b[0] == '-')
    {
        return "-" + multiply(a, b.substr(1));
    }

    if (isNumber(a) && isNumber(b))
    {
        return formatNumber(stod(a) * stod(b));
    }

    if (isNumber(a))
    {
        auto [bCoeff, bRest] = splitLeadingCoefficient(b);

        if (!bCoeff.empty() && isNumber(bCoeff))
        {
            string newCoeff = formatNumber(stod(a) * stod(bCoeff));

            if (bRest.empty())
            {
                return newCoeff;
            }

            return multiply(newCoeff, bRest);
        }

        if (
            b.find('+') == string::npos &&
            b.find('-') == string::npos &&
            b.find('/') == string::npos &&
            b.find('*') == string::npos)
        {
            if (!b.empty() && (isalpha(static_cast<unsigned char>(b[0])) || b[0] == '('))
            {
                return a + b;
            }
        }

        return a + "*(" + b + ")";
    }

    if (isNumber(b))
    {
        return multiply(b, a);
    }

    auto [bCoeff, bRest] = splitLeadingCoefficient(b);

    if (!bCoeff.empty() && isNumber(bCoeff))
    {
        return multiply(bCoeff, multiply(a, bRest));
    }

    if (a == "x" && b == "x")
    {
        return "x^2";
    }

    a = wrapIfAddSub(a);
    b = wrapIfAddSub(b);

    return a + "*" + b;
}

string combineAddSub(string left, char op, string right)
{
    if (isNumber(left) && isNumber(right))
    {
        double l = stod(left);
        double r = stod(right);

        if (op == '+')
        {
            return formatNumber(l + r);
        }

        return formatNumber(l - r);
    }

    if (left == "0")
    {
        if (op == '-')
        {
            if (!right.empty() && right[0] == '-')
            {
                return right.substr(1);
            }

            return "-" + right;
        }

        return right;
    }

    if (right == "0")
    {
        return left;
    }

    string l = wrapIfAddSub(left);
    string r = wrapIfAddSub(right);

    if (op == '+')
    {
        if (!right.empty() && right[0] == '-')
        {
            return l + "-" + right.substr(1);
        }

        return l + "+" + r;
    }

    if (!right.empty() && right[0] == '-')
    {
        return l + "+" + right.substr(1);
    }

    return l + "-" + r;
}

string squareExpression(string v)
{
    if (v == "x")
    {
        return "x^2";
    }

    if (isNumber(v))
    {
        double value = stod(v);
        return formatNumber(value * value);
    }

    return "(" + v + ")^2";
}

DerivResult simpleDerivative(string raw)
{
    string e = normalizeExpr(raw);

    if (e.empty())
    {
        throw runtime_error("empty expression");
    }

    size_t addSubPos = findTopLevelAddSub(e);

    if (addSubPos != string::npos)
    {
        string left = e.substr(0, addSubPos);
        char op = e[addSubPos];
        string right = e.substr(addSubPos + 1);

        DerivResult leftDeriv = simpleDerivative(left);
        DerivResult rightDeriv = simpleDerivative(right);

        string expr = combineAddSub(leftDeriv.expr, op, rightDeriv.expr);

        string step =
            "sum/difference rule applied to " + pretty(e);

        return {expr, step};
    }

    if (e == "x")
    {
        return {"1", "d/dx(x) = 1"};
    }

    if (isNumber(e))
    {
        return {"0", "constant rule: d/dx(" + pretty(e) + ") = 0"};
    }

    if (e[0] == '+')
    {
        return simpleDerivative(e.substr(1));
    }

    if (e[0] == '-')
    {
        DerivResult inner = simpleDerivative(e.substr(1));

        if (inner.expr == "0")
        {
            return {"0", "negative rule: " + inner.step};
        }

        if (!inner.expr.empty() && inner.expr[0] == '-')
        {
            return {inner.expr.substr(1), "negative rule: " + inner.step};
        }

        return {"-" + inner.expr, "negative rule: " + inner.step};
    }

    auto [coeff, rest] = splitLeadingCoefficient(e);

    if (!coeff.empty())
    {
        DerivResult restDeriv = simpleDerivative(rest);

        string expr = multiply(coeff, restDeriv.expr);

        string step =
            "constant multiple rule: d/dx(" +
            pretty(coeff) + " " + pretty(rest) +
            ") = " + pretty(coeff) + " * derivative of " + pretty(rest);

        return {expr, step};
    }

    if (e == "sinx" || e == "sin(x)")
    {
        return {"cosx", "d/dx(sin x) = cos x"};
    }

    if (e == "cosx" || e == "cos(x)")
    {
        return {"-sinx", "d/dx(cos x) = -sin x"};
    }

    if (e == "tanx" || e == "tan(x)")
    {
        return {"sec^2x", "d/dx(tan x) = sec^2 x"};
    }

    if (e == "lnx" || e == "ln(x)")
    {
        return {"1/x", "d/dx(ln x) = 1/x"};
    }

    if (e == "logx" || e == "log(x)")
    {
        return {"1/x", "assuming log means natural log: d/dx(log x) = 1/x"};
    }

    if (e == "log10x" || e == "log10(x)")
    {
        return {"1/(x*ln(10))", "d/dx(log10 x) = 1/(x ln 10)"};
    }

    if (e == "expx" || e == "e^x")
    {
        return {"e^x", "d/dx(e^x) = e^x"};
    }

    if (e == "sqrtx" || e == "sqrt(x)")
    {
        return {"1/(2*x)", "d/dx(sqrt x) = 1/(2 sqrt x)"};
    }

    FuncInfo func = parseFunction(e);

    if (!func.name.empty())
    {
        DerivResult innerDeriv = simpleDerivative(func.inner);

        string expr;
        string rule;

        if (func.name == "sin")
        {
            expr = multiply(innerDeriv.expr, "cos(" + func.inner + ")");
            rule = "d/dv(sin v) = cos v";
        }
        else if (func.name == "cos")
        {
            expr = multiply(innerDeriv.expr, "-sin(" + func.inner + ")");
            rule = "d/dv(cos v) = -sin v";
        }
        else if (func.name == "tan")
        {
            expr = multiply(innerDeriv.expr, "sec^2(" + func.inner + ")");
            rule = "d/dv(tan v) = sec^2 v";
        }
        else if (func.name == "ln" || func.name == "log")
        {
            if (innerDeriv.expr == "1")
            {
                expr = "1/(" + func.inner + ")";
            }
            else
            {
                expr = "(" + innerDeriv.expr + ")/(" + func.inner + ")";
            }

            rule = "d/dv(ln v) = 1/v";
        }
        else if (func.name == "log10")
        {
            if (innerDeriv.expr == "1")
            {
                expr = "1/((" + func.inner + ")*ln(10))";
            }
            else
            {
                expr = "(" + innerDeriv.expr + ")/((" + func.inner + ")*ln(10))";
            }

            rule = "d/dv(log10 v) = 1/(v ln 10)";
        }
        else if (func.name == "exp")
        {
            expr = multiply(innerDeriv.expr, "exp(" + func.inner + ")");
            rule = "d/dv(exp v) = exp v";
        }
        else if (func.name == "sqrt")
        {
            expr = "(" + innerDeriv.expr + ")/(2*sqrt(" + func.inner + "))";
            rule = "d/dv(sqrt v) = 1/(2 sqrt v)";
        }
        else
        {
            throw runtime_error("unsupported function: " + func.name);
        }

        string step =
            "chain rule: " + rule +
            ", where v = " + pretty(func.inner) +
            "; " + innerDeriv.step;

        return {expr, step};
    }

    size_t powPos = e.find('^');

    if (powPos != string::npos)
    {
        string base = e.substr(0, powPos);
        string exponent = e.substr(powPos + 1);

        if (base == "x" && isNumber(exponent))
        {
            double n = stod(exponent);

            if (std::fabs(n) < 1e-12)
            {
                return {"0", "x^0 is constant 1, so derivative is 0"};
            }

            if (std::fabs(n - 1.0) < 1e-12)
            {
                return {"1", "x^1 is x, so derivative is 1"};
            }

            string coeff = formatNumber(n);
            string newExp = formatNumber(n - 1.0);

            string expr;

            if (newExp == "0")
            {
                expr = coeff;
            }
            else if (newExp == "1")
            {
                expr = multiply(coeff, "x");
            }
            else
            {
                expr = multiply(coeff, "x^" + newExp);
            }

            string step =
                "power rule: d/dx(x^" + exponent + ") = " +
                exponent + "x^(" + exponent + "-1)";

            return {expr, step};
        }
    }

    throw runtime_error(
        "unsupported expression: " + pretty(e) +
        ". Supported forms include x, constants, sin, cos, tan, ln, log, log10, exp, sqrt, x^n, coefficients, and simple sums/differences.");
}

int main()
{
    cout << "Derivative Calculator\n";
    cout << "Enter a quotient as u/v to use the quotient rule.\n";
    cout << "If you enter a single expression, it will be differentiated directly.\n";
    cout << "Example: [sin x/x] or tanx\n";
    cout << "Supported functions: sin, cos, tan, ln, log, log10, exp, sqrt.\n";

    string line;

    while (true)
    {
        cout << "\nEnter expression, or leave blank to exit: ";

        if (!getline(cin, line))
        {
            break;
        }

        if (isBlank(line))
        {
            break;
        }

        try
        {
            string expression = cleanInput(line);

            if (expression.empty())
            {
                continue;
            }

            size_t slashPos = findTopLevelSlash(expression);

            // If there is no '/', differentiate the expression directly.
            if (slashPos == string::npos)
            {
                string expr = normalizeExpr(expression);
                DerivResult direct = simpleDerivative(expr);

                cout << "\nSteps:\n";

                cout << "1. Expression:\n";
                cout << "   f(x) = " << pretty(expr) << "\n";

                cout << "\n2. Derivative rule:\n";
                cout << "   " << direct.step << "\n";

                cout << "\n3. Derivative:\n";
                cout << "   f'(x) = " << pretty(direct.expr) << "\n";

                cout << "\nResult:\n";
                cout << "   [" << pretty(direct.expr) << "]\n";

                continue;
            }

            string uRaw = expression.substr(0, slashPos);
            string vRaw = expression.substr(slashPos + 1);

            if (uRaw.empty() || vRaw.empty())
            {
                throw runtime_error("both numerator and denominator must be non-empty");
            }

            string u = normalizeExpr(uRaw);
            string v = normalizeExpr(vRaw);

            if (v == "0")
            {
                throw runtime_error("denominator cannot be zero");
            }

            DerivResult uDeriv = simpleDerivative(u);
            DerivResult vDeriv = simpleDerivative(v);

            string term1 = multiply(v, uDeriv.expr);
            string term2 = multiply(u, vDeriv.expr);

            string numerator = combineAddSub(term1, '-', term2);
            string denominator = squareExpression(v);

            string result;

            if (numerator == "0")
            {
                result = "0";
            }
            else if (denominator == "1")
            {
                result = numerator;
            }
            else
            {
                result = "(" + numerator + ")/" + denominator;
            }

            cout << "\nSteps:\n";

            cout << "1. Identify u and v:\n";
            cout << "   u = " << pretty(wrapIfAddSub(u)) << "\n";
            cout << "   v = " << pretty(wrapIfAddSub(v)) << "\n";

            cout << "\n2. Differentiate u:\n";
            cout << "   " << uDeriv.step << "\n";
            cout << "   u' = " << pretty(uDeriv.expr) << "\n";

            cout << "\n3. Differentiate v:\n";
            cout << "   " << vDeriv.step << "\n";
            cout << "   v' = " << pretty(vDeriv.expr) << "\n";

            cout << "\n4. Quotient rule:\n";
            cout << "   d/dx(u/v) = (v u' - u v') / v^2\n";

            cout << "\n5. Substitute:\n";
            cout << "   ("
                 << pretty(wrapIfAddSub(v)) << " * " << pretty(uDeriv.expr)
                 << " - "
                 << pretty(wrapIfAddSub(u)) << " * " << pretty(vDeriv.expr)
                 << ") / ("
                 << pretty(wrapIfAddSub(v)) << ")^2\n";

            cout << "\n6. Result:\n";
            cout << "   [" << pretty(result) << "]\n";
        }
        catch (const exception &ex)
        {
            cerr << "Error: " << ex.what() << "\n";
        }
    }

    return 0;
}
/*
Enter expression, or leave blank to exit: sin x

Steps:
1. Expression:
   f(x) = sin x

2. Derivative rule:
   d/dx(sin x) = cos x

3. Derivative:
   f'(x) = cos x

Result:
   [cos x]

*/