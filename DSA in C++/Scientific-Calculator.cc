/*
 * ============================================================
 *  SCIENTIFIC CALCULATOR — a DSA study build (C++17)
 * ============================================================
 *  DATA STRUCTURES USED
 *    1. std::vector<Token>   token stream + postfix output "queue"
 *    2. std::stack<Token>    operator stack (Shunting-Yard)
 *    3. std::stack<double>   operand stack (RPN evaluation)
 *    4. std::unordered_map   O(1) lookup table for math functions
 *    5. std::stack<string>   history memory (LIFO by nature)
 *
 *  ALGORITHMS USED
 *    1. Lexical analysis (tokenizing)             O(n)
 *    2. Shunting-Yard, infix -> postfix (Dijkstra) O(n)
 *    3. Postfix (RPN) evaluation                   O(n)
 *  Total: O(n) time and O(n) space per expression,
 *  because every token is pushed and popped at most once.
 * ============================================================
 */

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <functional>   // std::function (for the lambda lookup table)
#include <cmath>
#include <cctype>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>

const double PI = 3.14159265358979323846;
const double E  = 2.71828182845904523536;

/* A token is the smallest meaningful unit of an expression.
 * Tagged-union style: `num` is valid only when type == NUM. */
enum class Type { NUM, OP, FUNC, LP, RP };

struct Token {
    Type type;
    double num = 0;        // value, if NUM
    std::string text;      // operator symbol or function name
};

static std::string trim(const std::string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == std::string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

/* ------------------------------------------------------------
 * STEP 1 — TOKENIZER (lexical analysis), O(n)
 * One left-to-right scan. Greedy matching:
 *   digits/'.'  -> consume the whole number  ("12.5")
 *   letters     -> consume the whole word    ("sin", "pi", "ans")
 *   anything else must be a 1-char operator or parenthesis.
 * ------------------------------------------------------------ */
std::vector<Token> tokenize(const std::string& s, double ans) {
    std::vector<Token> tokens;
    size_t i = 0;
    while (i < s.size()) {
        char c = s[i];
        if (std::isspace((unsigned char)c)) { i++; continue; }

        // ---- number ----
        if (std::isdigit((unsigned char)c) || c == '.') {
            size_t j = i;
            while (j < s.size() && (std::isdigit((unsigned char)s[j]) || s[j] == '.')) j++;
            std::string numStr = s.substr(i, j - i);
            if (std::count(numStr.begin(), numStr.end(), '.') > 1)
                throw std::runtime_error("Invalid number: " + numStr);
            tokens.push_back({Type::NUM, std::stod(numStr), ""});
            i = j;
            continue;
        }

        // ---- word: function, constant, or previous answer ----
        if (std::isalpha((unsigned char)c)) {
            size_t j = i;
            while (j < s.size() && std::isalpha((unsigned char)s[j])) j++;
            std::string w = s.substr(i, j - i);
            if (w == "pi")      tokens.push_back({Type::NUM, PI, w});
            else if (w == "e")  tokens.push_back({Type::NUM, E,  w});
            else if (w == "ans")tokens.push_back({Type::NUM, ans, w});
            else                tokens.push_back({Type::FUNC, 0, w});
            i = j;
            continue;
        }

        // ---- operators & parentheses ----
        if (c=='+'||c=='-'||c=='*'||c=='/'||c=='^'||c=='%')
            { tokens.push_back({Type::OP, 0, std::string(1, c)}); i++; continue; }
        if (c == '(') { tokens.push_back({Type::LP, 0, "("}); i++; continue; }
        if (c == ')') { tokens.push_back({Type::RP, 0, ")"}); i++; continue; }

        throw std::runtime_error(std::string("Unknown character: ") + c);
    }
    return tokens;
}

/* Precedence table. `neg` = unary minus; it binds tighter than ^
  * so that 2^-3 parses as 2^(-3). (Consequence: -2^2 = (-2)^2 here;
 * swap the values if you prefer the textbook convention.) */
int precedence(const std::string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/" || op == "%") return 2;
    if (op == "^")   return 3;
    if (op == "neg") return 4;
    return -1;
}
bool isRightAssoc(const std::string& op) { return op == "^" || op == "neg"; }

/* ------------------------------------------------------------
 * STEP 2 — SHUNTING-YARD (infix -> postfix), O(n)
 * WHY a stack? In infix, an operator must WAIT until both of its
 * operands are known. A LIFO stack is exactly the structure that
 * lets higher-precedence operators "cut in line" and be emitted
 * first. Rules:
 *   number   -> straight to output
 *   function -> push (waits for its argument)
 *   op o1    -> pop ops with higher (or equal, if left-assoc)
 *               precedence, then push o1
 *   '('      -> push (opens a new scope)
 *   ')'      -> pop until '('; then pop a function if one sits on top
 *   end      -> pop everything remaining
 * ------------------------------------------------------------ */
std::vector<Token> toPostfix(const std::vector<Token>& tokens) {
    std::vector<Token> out;      // the "output queue"
    std::stack<Token>  st;       // operator stack
    const Token* prev = nullptr; // needed to detect unary minus

    for (const Token& t : tokens) {
        switch (t.type) {
            case Type::NUM:
                out.push_back(t);                       // numbers never wait
                break;

            case Type::FUNC:
                st.push(t);                             // waits for argument
                break;

            case Type::OP: {
                std::string op = t.text;
                // Unary-minus detection: '-' with no left operand
                // (start, or after an operator / '(') is 'neg'.
                bool unary = (prev == nullptr || prev->type == Type::OP || prev->type == Type::LP);
                if (unary && op == "+") { prev = &t; continue; }  // unary + = no-op
                if (unary && op == "-") op = "neg";

                // Pop operators that must be evaluated BEFORE op.
                while (!st.empty() && st.top().type == Type::OP &&
                       (precedence(st.top().text) >  precedence(op) ||
                        (precedence(st.top().text) == precedence(op) && !isRightAssoc(op)))) {
                    out.push_back(st.top());
                    st.pop();
                }
                st.push({Type::OP, 0, op});
                break;
            }

            case Type::LP:
                st.push(t);
                break;

            case Type::RP:
                while (!st.empty() && st.top().type != Type::LP) { out.push_back(st.top()); st.pop(); }
                if (st.empty()) throw std::runtime_error("Mismatched parentheses");
                st.pop();                                            // drop the '('
                if (!st.empty() && st.top().type == Type::FUNC) {    // f(x) -> x f
                    out.push_back(st.top());
                    st.pop();
                }
                break;
        }
        prev = &t;
    }
    while (!st.empty()) {
        if (st.top().type == Type::LP) throw std::runtime_error("Mismatched parentheses");
        out.push_back(st.top());
        st.pop();
    }
    return out;
}

/* ------------------------------------------------------------
 * STEP 3 — POSTFIX (RPN) EVALUATION, O(n)
 * The payoff of postfix: no precedence rules, no parentheses —
 * a single stack pass, strictly left to right.
 *   number   -> push
 *   function -> pop 1, apply, push
 *   'neg'    -> pop 1, negate, push
 *   binary   -> pop 2 (FIRST pop is the RIGHT operand!), apply, push
 * ------------------------------------------------------------ */
double evalPostfix(const std::vector<Token>& rpn) {
    std::stack<double> st;

    // O(1) name -> lambda lookup table (hash map as dispatch table).
    static const std::unordered_map<std::string, std::function<double(double)>> FUNCS = {
        {"sin",  [](double x){ return std::sin(x); }},   // radians
        {"cos",  [](double x){ return std::cos(x); }},
        {"tan",  [](double x){ return std::tan(x); }},
        {"log",  [](double x){ if (x <= 0) throw std::runtime_error("log of non-positive"); return std::log10(x); }},
        {"ln",   [](double x){ if (x <= 0) throw std::runtime_error("ln of non-positive");  return std::log(x);  }},
        {"sqrt", [](double x){ if (x < 0)  throw std::runtime_error("sqrt of negative");    return std::sqrt(x); }},
        {"abs",  [](double x){ return std::fabs(x); }},
    };

    for (const Token& t : rpn) {
        if (t.type == Type::NUM) { st.push(t.num); continue; }

        if (t.type == Type::FUNC) {
            if (st.empty()) throw std::runtime_error("Malformed expression");
            double a = st.top(); st.pop();
            auto it = FUNCS.find(t.text);
            if (it == FUNCS.end()) throw std::runtime_error("Unknown function: " + t.text);
            st.push(it->second(a));
            continue;
        }

        if (t.text == "neg") {                       // unary operator
            if (st.empty()) throw std::runtime_error("Malformed expression");
            double a = st.top(); st.pop();
            st.push(-a);
            continue;
        }

        if (st.size() < 2) throw std::runtime_error("Malformed expression");
        double b = st.top(); st.pop();               // RIGHT operand (popped first)
        double a = st.top(); st.pop();               // LEFT operand
        double r = 0;
        if      (t.text == "+") r = a + b;
        else if (t.text == "-") r = a - b;
        else if (t.text == "*") r = a * b;
        else if (t.text == "/") { if (b == 0) throw std::runtime_error("Division by zero"); r = a / b; }
        else if (t.text == "%") { if (b == 0) throw std::runtime_error("Modulo by zero"); r = std::fmod(a, b); }
        else if (t.text == "^") r = std::pow(a, b);
        st.push(r);
    }

    if (st.size() != 1) throw std::runtime_error("Malformed expression");
    return st.top();
}

/* ------------------------------------------------------------
 * STEP 4 — REPL + HISTORY (a stack used as LIFO memory)
 * Pipeline per line: tokenize -> shunting-yard -> evaluate.
 * ------------------------------------------------------------ */
int main() {
    std::stack<std::string> history;   // newest on top — LIFO
    double lastAns = 0;
    std::string line;

    std::cout << "=== Scientific Calculator (DSA edition) ===\n"
              << "Supports: + - * / ^ % ( )  sin cos tan log ln sqrt abs  pi e ans\n"
              << "Commands: history | clear | exit\n";

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;
        line = trim(line);
        if (line.empty()) continue;
        if (line == "exit")  break;
        if (line == "clear") { history = std::stack<std::string>(); std::cout << "History cleared.\n"; continue; }
        if (line == "history") {
            if (history.empty()) { std::cout << "(empty)\n"; continue; }
            std::stack<std::string> tmp = history;   // copy: never destroy the real stack
            int i = 1;
            while (!tmp.empty()) { std::cout << "  " << i++ << ": " << tmp.top() << "\n"; tmp.pop(); }
            continue;
        }

        try {
            double result = evalPostfix(toPostfix(tokenize(line, lastAns)));
            lastAns = result;
            std::ostringstream oss;
            oss << std::setprecision(12) << result;
            std::cout << "= " << oss.str() << "\n";
            history.push(line + " = " + oss.str());
        } catch (const std::exception& ex) {
            std::cout << "Error: " << ex.what() << "\n";   // errors never crash the REPL
        }
    }
    return 0;
}

// === Scientific Calculator (DSA edition) ===
// Supports: + - * / ^ % ( )  sin cos tan log ln sqrt abs  pi e ans
// Commands: history | clear | exit
// > log 10
// = 1
// > 100%10
// = 0
// > sin 30
// = -0.988031624093
// > -sin 45
// = -0.850903524534
// > 
