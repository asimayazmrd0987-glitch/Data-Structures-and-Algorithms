#include <bits/stdc++.h>
using namespace std;

struct Node;
using NodePtr = shared_ptr<Node>;

enum class Op
{
    Add,
    Sub,
    Mul,
    Div,
    Pow
};

enum class FuncType
{
    Sin,
    Cos,
    Tan,
    Ln,
    Log10,
    Exp,
    Sqrt
};

string formatNumber(double v)
{
    if (!std::isfinite(v))
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

// Factory function declarations
NodePtr makeConst(double v);
NodePtr makeVar();
NodePtr makeNeg(NodePtr node);
NodePtr makeBinary(Op op, NodePtr left, NodePtr right);
NodePtr makeFunc(FuncType type, NodePtr arg);

struct Node
{
    virtual ~Node() = default;

    virtual string toString() const = 0;
    virtual NodePtr diff() const = 0;
    virtual bool isConst() const = 0;
};

struct ConstNode final : Node
{
    double value;

    explicit ConstNode(double v) : value(v) {}

    string toString() const override
    {
        return formatNumber(value);
    }

    NodePtr diff() const override;

    bool isConst() const override
    {
        return true;
    }
};

struct VarNode final : Node
{
    string toString() const override
    {
        return "x";
    }

    NodePtr diff() const override;

    bool isConst() const override
    {
        return false;
    }
};

struct UnaryNode final : Node
{
    NodePtr child;

    explicit UnaryNode(NodePtr c) : child(move(c)) {}

    string toString() const override
    {
        return "(-" + child->toString() + ")";
    }

    NodePtr diff() const override;

    bool isConst() const override
    {
        return child->isConst();
    }
};

struct BinaryNode final : Node
{
    Op op;
    NodePtr left;
    NodePtr right;

    BinaryNode(Op operation, NodePtr l, NodePtr r)
        : op(operation), left(move(l)), right(move(r)) {}

    string opToString() const
    {
        switch (op)
        {
        case Op::Add:
            return "+";
        case Op::Sub:
            return "-";
        case Op::Mul:
            return "*";
        case Op::Div:
            return "/";
        case Op::Pow:
            return "^";
        }

        return "?";
    }

    string toString() const override
    {
        return "(" + left->toString() + " " + opToString() + " " + right->toString() + ")";
    }

    NodePtr diff() const override;

    bool isConst() const override
    {
        return left->isConst() && right->isConst();
    }
};

struct FuncNode final : Node
{
    FuncType type;
    NodePtr arg;

    FuncNode(FuncType t, NodePtr a) : type(t), arg(move(a)) {}

    string funcName() const
    {
        switch (type)
        {
        case FuncType::Sin:
            return "sin";
        case FuncType::Cos:
            return "cos";
        case FuncType::Tan:
            return "tan";
        case FuncType::Ln:
            return "ln";
        case FuncType::Log10:
            return "log10";
        case FuncType::Exp:
            return "exp";
        case FuncType::Sqrt:
            return "sqrt";
        }

        return "func";
    }

    string toString() const override
    {
        return funcName() + "(" + arg->toString() + ")";
    }

    NodePtr diff() const override;

    bool isConst() const override
    {
        return arg->isConst();
    }
};

bool isConstValue(const NodePtr &node, double value)
{
    auto c = dynamic_pointer_cast<ConstNode>(node);
    return c && std::fabs(c->value - value) < 1e-12;
}

bool isZero(const NodePtr &node)
{
    return isConstValue(node, 0.0);
}

bool isOne(const NodePtr &node)
{
    return isConstValue(node, 1.0);
}

double evalBinary(Op op, double a, double b, bool &ok)
{
    ok = true;

    switch (op)
    {
    case Op::Add:
        return a + b;

    case Op::Sub:
        return a - b;

    case Op::Mul:
        return a * b;

    case Op::Div:
        if (std::fabs(b) < 1e-15)
        {
            ok = false;
            return 0.0;
        }
        return a / b;

    case Op::Pow:
    {
        double result = std::pow(a, b);
        if (!std::isfinite(result))
        {
            ok = false;
            return 0.0;
        }
        return result;
    }
    }

    ok = false;
    return 0.0;
}

NodePtr makeConst(double v)
{
    return make_shared<ConstNode>(v);
}

NodePtr makeVar()
{
    return make_shared<VarNode>();
}

NodePtr makeNeg(NodePtr node)
{
    if (!node)
    {
        return nullptr;
    }

    auto c = dynamic_pointer_cast<ConstNode>(node);
    if (c)
    {
        return makeConst(-c->value);
    }

    auto u = dynamic_pointer_cast<UnaryNode>(node);
    if (u)
    {
        return u->child;
    }

    return make_shared<UnaryNode>(node);
}

NodePtr makeBinary(Op op, NodePtr left, NodePtr right)
{
    if (!left || !right)
    {
        return nullptr;
    }

    auto lc = dynamic_pointer_cast<ConstNode>(left);
    auto rc = dynamic_pointer_cast<ConstNode>(right);

    if (lc && rc)
    {
        bool ok = false;
        double result = evalBinary(op, lc->value, rc->value, ok);

        if (ok && std::isfinite(result))
        {
            return makeConst(result);
        }
    }

    if (op == Op::Add)
    {
        if (isZero(left))
        {
            return right;
        }

        if (isZero(right))
        {
            return left;
        }
    }

    if (op == Op::Sub)
    {
        if (isZero(right))
        {
            return left;
        }

        if (isZero(left))
        {
            return makeNeg(right);
        }
    }

    if (op == Op::Mul)
    {
        if (isZero(left) || isZero(right))
        {
            return makeConst(0);
        }

        if (isOne(left))
        {
            return right;
        }

        if (isOne(right))
        {
            return left;
        }

        if (isConstValue(left, -1.0))
        {
            return makeNeg(right);
        }

        if (isConstValue(right, -1.0))
        {
            return makeNeg(left);
        }
    }

    if (op == Op::Div)
    {
        if (isZero(left) && !isZero(right))
        {
            return makeConst(0);
        }

        if (isOne(right))
        {
            return left;
        }
    }

    if (op == Op::Pow)
    {
        if (isZero(right))
        {
            return makeConst(1);
        }

        if (isOne(right))
        {
            return left;
        }

        if (isOne(left))
        {
            return makeConst(1);
        }

        auto rcPow = dynamic_pointer_cast<ConstNode>(right);
        if (isZero(left) && rcPow && rcPow->value > 0.0)
        {
            return makeConst(0);
        }
    }

    return make_shared<BinaryNode>(op, left, right);
}

NodePtr makeFunc(FuncType type, NodePtr arg)
{
    auto c = dynamic_pointer_cast<ConstNode>(arg);

    if (c)
    {
        double x = c->value;
        double result = 0.0;
        bool ok = true;

        switch (type)
        {
        case FuncType::Sin:
            result = std::sin(x);
            break;

        case FuncType::Cos:
            result = std::cos(x);
            break;

        case FuncType::Tan:
            result = std::tan(x);
            break;

        case FuncType::Ln:
            if (x > 0.0)
            {
                result = std::log(x);
            }
            else
            {
                ok = false;
            }
            break;

        case FuncType::Log10:
            if (x > 0.0)
            {
                result = std::log10(x);
            }
            else
            {
                ok = false;
            }
            break;

        case FuncType::Exp:
            result = std::exp(x);
            break;

        case FuncType::Sqrt:
            if (x >= 0.0)
            {
                result = std::sqrt(x);
            }
            else
            {
                ok = false;
            }
            break;
        }

        if (ok && std::isfinite(result))
        {
            return makeConst(result);
        }
    }

    return make_shared<FuncNode>(type, arg);
}

NodePtr ConstNode::diff() const
{
    return makeConst(0);
}

NodePtr VarNode::diff() const
{
    return makeConst(1);
}

NodePtr UnaryNode::diff() const
{
    return makeNeg(child->diff());
}

NodePtr BinaryNode::diff() const
{
    switch (op)
    {
    case Op::Add:
    {
        return makeBinary(Op::Add, left->diff(), right->diff());
    }

    case Op::Sub:
    {
        return makeBinary(Op::Sub, left->diff(), right->diff());
    }

    case Op::Mul:
    {
        // Product rule:
        // d(uv) = u'v + uv'
        NodePtr leftPart = makeBinary(Op::Mul, left->diff(), right);
        NodePtr rightPart = makeBinary(Op::Mul, left, right->diff());
        return makeBinary(Op::Add, leftPart, rightPart);
    }

    case Op::Div:
    {
        // Quotient rule:
        // d(u/v) = (u'v - uv') / v^2
        NodePtr numerator = makeBinary(
            Op::Sub,
            makeBinary(Op::Mul, left->diff(), right),
            makeBinary(Op::Mul, left, right->diff()));

        NodePtr denominator = makeBinary(Op::Pow, right, makeConst(2));

        return makeBinary(Op::Div, numerator, denominator);
    }

    case Op::Pow:
    {
        // If both base and exponent are constants, derivative is zero.
        if (left->isConst() && right->isConst())
        {
            return makeConst(0);
        }

        // Power rule with constant exponent:
        // d(u^n) = n * u^(n - 1) * u'
        auto constantExponent = dynamic_pointer_cast<ConstNode>(right);

        if (constantExponent)
        {
            double n = constantExponent->value;

            if (std::fabs(n) < 1e-12)
            {
                return makeConst(0);
            }

            if (std::fabs(n - 1.0) < 1e-12)
            {
                return left->diff();
            }

            NodePtr powerPart = makeBinary(
                Op::Pow,
                left,
                makeConst(n - 1.0));

            NodePtr coefficientPart = makeBinary(
                Op::Mul,
                makeConst(n),
                powerPart);

            return makeBinary(Op::Mul, coefficientPart, left->diff());
        }

        // If base is constant and exponent is variable:
        // d(a^v) = a^v * ln(a) * v'
        if (left->isConst())
        {
            NodePtr powNode = makeBinary(Op::Pow, left, right);
            NodePtr lnBase = makeFunc(FuncType::Ln, left);

            return makeBinary(
                Op::Mul,
                makeBinary(Op::Mul, powNode, lnBase),
                right->diff());
        }

        // General power/exponential rule:
        // d(u^v) = u^v * (v' ln(u) + v * u'/u)
        NodePtr powNode = makeBinary(Op::Pow, left, right);

        NodePtr term1 = makeBinary(
            Op::Mul,
            right->diff(),
            makeFunc(FuncType::Ln, left));

        NodePtr term2 = makeBinary(
            Op::Mul,
            right,
            makeBinary(Op::Div, left->diff(), left));

        NodePtr sum = makeBinary(Op::Add, term1, term2);

        return makeBinary(Op::Mul, powNode, sum);
    }
    }

    return makeConst(0);
}

NodePtr FuncNode::diff() const
{
    NodePtr du = arg->diff();

    switch (type)
    {
    case FuncType::Sin:
    {
        // d(sin u) = cos(u) * u'
        return makeBinary(Op::Mul, makeFunc(FuncType::Cos, arg), du);
    }

    case FuncType::Cos:
    {
        // d(cos u) = -sin(u) * u'
        NodePtr product = makeBinary(Op::Mul, makeFunc(FuncType::Sin, arg), du);
        return makeNeg(product);
    }

    case FuncType::Tan:
    {
        // d(tan u) = u' / cos(u)^2
        NodePtr denominator = makeBinary(
            Op::Pow,
            makeFunc(FuncType::Cos, arg),
            makeConst(2));

        return makeBinary(Op::Div, du, denominator);
    }

    case FuncType::Ln:
    {
        // d(ln u) = u' / u
        return makeBinary(Op::Div, du, arg);
    }

    case FuncType::Log10:
    {
        // d(log10 u) = u' / (u * ln(10))
        NodePtr denominator = makeBinary(
            Op::Mul,
            arg,
            makeFunc(FuncType::Ln, makeConst(10)));

        return makeBinary(Op::Div, du, denominator);
    }

    case FuncType::Exp:
    {
        // d(e^u) = e^u * u'
        return makeBinary(Op::Mul, makeFunc(FuncType::Exp, arg), du);
    }

    case FuncType::Sqrt:
    {
        // d(sqrt u) = u' / (2 sqrt u)
        NodePtr denominator = makeBinary(
            Op::Mul,
            makeConst(2),
            makeFunc(FuncType::Sqrt, arg));

        return makeBinary(Op::Div, du, denominator);
    }
    }

    return makeConst(0);
}

struct Token
{
    enum class Type
    {
        Number,
        Ident,
        Op,
        LParen,
        RParen,
        End
    };

    Type type;
    string text;
    double value;
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

vector<Token> tokenize(const string &input)
{
    vector<Token> tokens;
    size_t i = 0;

    while (i < input.size())
    {
        char c = input[i];

        if (isspace(static_cast<unsigned char>(c)))
        {
            ++i;
            continue;
        }

        if (
            isdigit(static_cast<unsigned char>(c)) ||
            (c == '.' && i + 1 < input.size() && isdigit(static_cast<unsigned char>(input[i + 1]))))
        {
            string rest = input.substr(i);
            size_t consumed = 0;
            double value = 0.0;

            try
            {
                value = stod(rest, &consumed);
            }
            catch (...)
            {
                throw runtime_error("Invalid number");
            }

            if (consumed == 0)
            {
                throw runtime_error("Invalid number");
            }

            i += consumed;
            tokens.push_back(Token{Token::Type::Number, "", value});
            continue;
        }

        if (isalpha(static_cast<unsigned char>(c)) || c == '_')
        {
            string name;

            while (
                i < input.size() &&
                (isalnum(static_cast<unsigned char>(input[i])) || input[i] == '_'))
            {
                name += input[i];
                ++i;
            }

            tokens.push_back(Token{Token::Type::Ident, name, 0.0});
            continue;
        }

        if (c == '(')
        {
            tokens.push_back(Token{Token::Type::LParen, "(", 0.0});
            ++i;
            continue;
        }

        if (c == ')')
        {
            tokens.push_back(Token{Token::Type::RParen, ")", 0.0});
            ++i;
            continue;
        }

        if (c == '*' && i + 1 < input.size() && input[i + 1] == '*')
        {
            tokens.push_back(Token{Token::Type::Op, "^", 0.0});
            i += 2;
            continue;
        }

        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
        {
            tokens.push_back(Token{Token::Type::Op, string(1, c), 0.0});
            ++i;
            continue;
        }

        throw runtime_error(string("Unexpected character: ") + c);
    }

    tokens.push_back(Token{Token::Type::End, "", 0.0});
    return tokens;
}

class Parser
{
private:
    vector<Token> tokens;
    size_t pos = 0;

    const Token &peek() const
    {
        return tokens.at(pos);
    }

    Token take()
    {
        return tokens.at(pos++);
    }

    bool matchOp(const string &op)
    {
        const Token &t = peek();

        if (t.type == Token::Type::Op && t.text == op)
        {
            ++pos;
            return true;
        }

        return false;
    }

    void expect(Token::Type type, const string &message)
    {
        if (peek().type != type)
        {
            throw runtime_error(message);
        }

        ++pos;
    }

    NodePtr parseExpression()
    {
        NodePtr left = parseTerm();

        while (true)
        {
            if (matchOp("+"))
            {
                NodePtr right = parseTerm();
                left = makeBinary(Op::Add, left, right);
            }
            else if (matchOp("-"))
            {
                NodePtr right = parseTerm();
                left = makeBinary(Op::Sub, left, right);
            }
            else
            {
                break;
            }
        }

        return left;
    }

    NodePtr parseTerm()
    {
        NodePtr left = parseUnary();

        while (true)
        {
            if (matchOp("*"))
            {
                NodePtr right = parseUnary();
                left = makeBinary(Op::Mul, left, right);
            }
            else if (matchOp("/"))
            {
                NodePtr right = parseUnary();
                left = makeBinary(Op::Div, left, right);
            }
            else if (
                peek().type == Token::Type::Number ||
                peek().type == Token::Type::Ident ||
                peek().type == Token::Type::LParen)
            {
                // Implicit multiplication:
                // 2x, 3sin(x), x(x+1), etc.
                NodePtr right = parseUnary();
                left = makeBinary(Op::Mul, left, right);
            }
            else
            {
                break;
            }
        }

        return left;
    }

    NodePtr parseUnary()
    {
        if (matchOp("+"))
        {
            return parseUnary();
        }

        if (matchOp("-"))
        {
            return makeNeg(parseUnary());
        }

        return parsePower();
    }

    NodePtr parsePower()
    {
        NodePtr left = parsePrimary();

        if (matchOp("^"))
        {
            NodePtr right = parseUnary();
            return makeBinary(Op::Pow, left, right);
        }

        return left;
    }

    NodePtr parsePrimary()
    {
        Token token = take();

        if (token.type == Token::Type::Number)
        {
            return makeConst(token.value);
        }

        if (token.type == Token::Type::LParen)
        {
            NodePtr inside = parseExpression();
            expect(Token::Type::RParen, "Expected ')'");
            return inside;
        }

        if (token.type == Token::Type::Ident)
        {
            string name = toLowerString(token.text);

            if (name == "x")
            {
                return makeVar();
            }

            if (name == "pi")
            {
                return makeConst(acos(-1.0));
            }

            if (name == "e")
            {
                return makeConst(exp(1.0));
            }

            FuncType funcType;
            bool isFunction = true;

            if (name == "sin")
            {
                funcType = FuncType::Sin;
            }
            else if (name == "cos")
            {
                funcType = FuncType::Cos;
            }
            else if (name == "tan")
            {
                funcType = FuncType::Tan;
            }
            else if (name == "ln")
            {
                funcType = FuncType::Ln;
            }
            else if (name == "log")
            {
                // In this program, log means natural logarithm.
                // Use log10 for base-10 logarithm.
                funcType = FuncType::Ln;
            }
            else if (name == "log10")
            {
                funcType = FuncType::Log10;
            }
            else if (name == "exp")
            {
                funcType = FuncType::Exp;
            }
            else if (name == "sqrt")
            {
                funcType = FuncType::Sqrt;
            }
            else
            {
                isFunction = false;
            }

            if (isFunction)
            {
                expect(Token::Type::LParen, "Expected '(' after function name");
                NodePtr argument = parseExpression();
                expect(Token::Type::RParen, "Expected ')' after function argument");
                return makeFunc(funcType, argument);
            }

            throw runtime_error("Unknown identifier: " + name);
        }

        throw runtime_error("Unexpected token");
    }

public:
    explicit Parser(vector<Token> tokenList) : tokens(move(tokenList)) {}

    NodePtr parse()
    {
        NodePtr result = parseExpression();

        if (peek().type != Token::Type::End)
        {
            throw runtime_error("Unexpected trailing input");
        }

        return result;
    }
};

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

int main()
{
    cout << "Symbolic Derivative Calculator\n";
    cout << "Supported variable: x\n";
    cout << "Supported operators: + - * / ^\n";
    cout << "Supported functions: sin, cos, tan, ln, log, log10, exp, sqrt\n";
    cout << "Example inputs:\n";
    cout << "  x^3 + 2*x\n";
    cout << "  sin(x)\n";
    cout << "  ln(x^2 + 1)\n";
    cout << "  e^x\n";
    cout << "  sqrt(x)\n";
    cout << "  tan(x)^2\n";

    string expression;

    while (true)
    {
        cout << "\nEnter f(x), or leave blank to exit: ";

        if (!getline(cin, expression))
        {
            break;
        }

        if (isBlank(expression))
        {
            break;
        }

        try
        {
            vector<Token> tokens = tokenize(expression);
            Parser parser(tokens);

            NodePtr function = parser.parse();
            NodePtr derivative = function->diff();

            cout << "f(x)  = " << function->toString() << "\n";
            cout << "f'(x) = " << derivative->toString() << "\n";
        }
        catch (const exception &ex)
        {
            cerr << "Error: " << ex.what() << "\n";
        }
    }

    return 0;
}

/*
Symbolic Derivative Calculator
Supported variable: x
Supported operators: + - * / ^
Supported functions: sin, cos, tan, ln, log, log10, exp, sqrt
Example inputs:
  x^3 + 2*x
  sin(x)
  ln(x^2 + 1)
  e^x
  sqrt(x)
  tan(x)^2

Enter f(x), or leave blank to exit: sin(x)^2
f(x)  = (sin(x) ^ 2)
f'(x) = ((2 * sin(x)) * cos(x))

Enter f(x), or leave blank to exit: 
*/