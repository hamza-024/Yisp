#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <memory>
#include <sstream>

enum CellType { Symbol, Number, List, Proc, Lambda };
using CellPtr = std::shared_ptr<struct Cell>;
using EnvironmentPtr = std::shared_ptr<struct Environment>;

struct Environment;

struct Cell {
    CellType type;
    std::string val;
    std::vector<CellPtr> list;
    std::function<CellPtr(const std::vector<CellPtr>&)> proc;
    EnvironmentPtr env;

    Cell(CellType type) : type(type), env(nullptr) {}
    Cell(CellType type, const std::string& val) : type(type), val(val), env(nullptr) {}
    Cell(std::function<CellPtr(const std::vector<CellPtr>&)> proc) : type(Proc), proc(proc), env(nullptr) {}
};

using Cells = std::vector<CellPtr>;

struct Environment {
    std::map<std::string, CellPtr> symbols;
    EnvironmentPtr outer;

    Environment(EnvironmentPtr outer = nullptr) : outer(outer) {}

    void define(const std::string& symbol, CellPtr value) {
        symbols[symbol] = value;
    }

    CellPtr find(const std::string& symbol) {
        if (symbols.find(symbol) != symbols.end())
            return symbols[symbol];
        else if (outer)
            return outer->find(symbol);
        throw std::runtime_error("Symbol not found: " + symbol);
    }
};

CellPtr makeNumber(long n) {
    return std::make_shared<Cell>(Number, std::to_string(n));
}

bool isNumber(const std::string& s) {
    if (s.empty()) return false;
    if (s == "-") return false;  // Standalone minus is not a number
    for (size_t i = (s[0] == '-' ? 1 : 0); i < s.size(); ++i) {
        if (!isdigit(s[i])) return false;
    }
    return true;
}

bool isTrue(const CellPtr& cell) {
    return !(cell->type == Symbol && cell->val == "nil");  // Only "nil" is false
}


//////////////////////////////////////////////////////////////-PROCEDURES-////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CellPtr procAdd(const Cells& args) {
    long result = 0;
    for (auto& arg : args) {
        if (arg->type != Number) {
            throw std::runtime_error("Non-numeric operand in addition");
        }
        result += std::stol(arg->val);
    }
    return makeNumber(result);
}

CellPtr procSub(const Cells& args) {
    if (args.empty()) {
        throw std::runtime_error("Subtraction requires at least one operand");
    }

    if (args[0]->type != Number) {
        throw std::runtime_error("Non-numeric operand in subtraction (first argument)");
    }

    long result = std::stol(args[0]->val);

    if (args.size() == 1) {
        return makeNumber(-result);
    }

    for (size_t i = 1; i < args.size(); i++) {
        if (args[i]->type != Number) {
            throw std::runtime_error("Non-numeric operand in subtraction");
        }
        result -= std::stol(args[i]->val);
    }

    return makeNumber(result);
}

CellPtr procMul(const Cells& args) {
    long result = 1;
    for (auto& arg : args) {
        if (arg->type != Number) {
            throw std::runtime_error("Non-numeric operand in multiplication");
        }
        result *= std::stol(arg->val);
    }
    return makeNumber(result);
}

CellPtr procDiv(const Cells& args) {
    if (args.size() < 2) {
        throw std::runtime_error("Division requires at least two operands");
    }
    if (args[0]->type != Number) {
        throw std::runtime_error("Non-numeric operand in division");
    }
    long result = std::stol(args[0]->val);

    for (size_t i = 1; i < args.size(); i++) {
        if (args[i]->type != Number) {
            throw std::runtime_error("Non-numeric operand in division");
        }
        long divisor = std::stol(args[i]->val);
        if (divisor == 0) {
            throw std::runtime_error("Division by zero");
        }
        result /= divisor;
    }
    return makeNumber(result);
}

CellPtr procGreaterThan(const Cells& args) {
    if (args.size() != 2 || args[0]->type != Number || args[1]->type != Number) {
        throw std::runtime_error("> requires exactly two numeric operands");
    }
    return std::stol(args[0]->val) > std::stol(args[1]->val) ? 
           std::make_shared<Cell>(Symbol, "t") : std::make_shared<Cell>(Symbol, "nil");
}

CellPtr procLessThan(const Cells& args) {
    if (args.size() != 2 || args[0]->type != Number || args[1]->type != Number) {
        throw std::runtime_error("< requires exactly two numeric operands");
    }
    return std::stol(args[0]->val) < std::stol(args[1]->val) ? 
           std::make_shared<Cell>(Symbol, "t") : std::make_shared<Cell>(Symbol, "nil");
}

CellPtr procEquals(const Cells& args) {
    if (args.size() != 2) {
        throw std::runtime_error("= requires exactly two operands");
    }
    if (args[0]->type == Number && args[1]->type == Number) {
        return std::stol(args[0]->val) == std::stol(args[1]->val) ? 
               std::make_shared<Cell>(Symbol, "t") : std::make_shared<Cell>(Symbol, "nil");
    }
    return (args[0]->val == args[1]->val) ? 
           std::make_shared<Cell>(Symbol, "t") : std::make_shared<Cell>(Symbol, "nil");
}

CellPtr procGreaterEqual(const Cells& args) {
    if (args.size() != 2 || args[0]->type != Number || args[1]->type != Number) {
        throw std::runtime_error(">= requires exactly two numeric arguments");
    }
    return std::make_shared<Cell>(Symbol, (args[0]->val >= args[1]->val) ? "t" : "nil");
}

CellPtr procLessEqual(const Cells& args) {
    if (args.size() != 2 || args[0]->type != Number || args[1]->type != Number) {
        throw std::runtime_error("<= requires exactly two numeric arguments");
    }
    return std::make_shared<Cell>(Symbol, (args[0]->val <= args[1]->val) ? "t" : "nil");
}


CellPtr procAnd(const Cells& args) {
    for (auto& arg : args) {
        if (!isTrue(arg)) return std::make_shared<Cell>(Symbol, "nil");
    }
    return std::make_shared<Cell>(Symbol, "t");  // Returns "t" for true if all are true
}

CellPtr procOr(const Cells& args) {
    for (auto& arg : args) {
        if (isTrue(arg)) return std::make_shared<Cell>(Symbol, "t");
    }
    return std::make_shared<Cell>(Symbol, "nil");  // Returns "nil" if all are false
}

CellPtr procNumber(const Cells& args) {
    if (args.size() != 1) {
        throw std::runtime_error("number? requires exactly one argument");
    }
    return args[0]->type == Number ? std::make_shared<Cell>(Symbol, "t") : std::make_shared<Cell>(Symbol, "nil");
}

CellPtr procSymbol(const Cells& args) {
    if (args.size() != 1) {
        throw std::runtime_error("symbol? requires exactly one argument");
    }
    CellPtr arg = args[0];
    
    // A symbol is considered a `Symbol` type and not a `Number`
    if (arg->type == Symbol && !(arg->val.empty() || isdigit(arg->val[0]))) {
        return std::make_shared<Cell>(Symbol, "t");
    }
    return std::make_shared<Cell>(Symbol, "nil");
}


CellPtr procList(const Cells& args) {
    if (args.size() != 1) {
        throw std::runtime_error("list? requires exactly one argument");
    }
    return args[0]->type == List ? std::make_shared<Cell>(Symbol, "t") : std::make_shared<Cell>(Symbol, "nil");
}

CellPtr procNil(const Cells& args) {
    if (args.size() != 1) {
        throw std::runtime_error("nil? requires exactly one argument");
    }
    return (!isTrue(args[0])) ? std::make_shared<Cell>(Symbol, "t") : std::make_shared<Cell>(Symbol, "nil");
}

CellPtr procCons(const Cells& args) {
    if (args.size() != 2) {
        throw std::runtime_error("cons requires exactly two arguments: an element and a list");
    }

    CellPtr result = std::make_shared<Cell>(List);

    result->list.push_back(args[0]);

    if (args[1]->type == List) {
        result->list.insert(result->list.end(), args[1]->list.begin(), args[1]->list.end());
    } else if (args[1]->type == Symbol && args[1]->val == "nil") {
    } else {
        throw std::runtime_error("cons requires the second argument to be a list or nil");
    }
    
    return result;
}


CellPtr procCar(const Cells& args) {
    if (args.size() != 1 || args[0]->type != List || args[0]->list.empty()) {
        throw std::runtime_error("car requires a non-empty list");
    }
    return args[0]->list[0];
}

CellPtr procCdr(const Cells& args) {
    if (args.size() != 1 || args[0]->type != List || args[0]->list.empty()) {
        throw std::runtime_error("cdr requires a non-empty list");
    }
    CellPtr result = std::make_shared<Cell>(List);
    result->list.insert(result->list.end(), args[0]->list.begin() + 1, args[0]->list.end());
    return result;
}

// Helper functions for list navigation
CellPtr cadr(const CellPtr& expr) {
    return expr->list[1];
}

CellPtr caddr(const CellPtr& expr) {
    return expr->list[2];
}

///////////////////////////////////////////////////////////-Initialization in Global ENV-///////////////////////////////////////////////////
EnvironmentPtr createGlobalEnv() {
    auto env = std::make_shared<Environment>();
    //Arithmetic Operators
    env->define("+", std::make_shared<Cell>(procAdd));
    env->define("-", std::make_shared<Cell>(procSub));
    env->define("*", std::make_shared<Cell>(procMul));
    env->define("/", std::make_shared<Cell>(procDiv));
    //Comparison Operators
    env->define(">", std::make_shared<Cell>(procGreaterThan));
    env->define("<", std::make_shared<Cell>(procLessThan));
    env->define("=", std::make_shared<Cell>(procEquals));
    env->define(">=", std::make_shared<Cell>(procGreaterEqual));  
    env->define("<=", std::make_shared<Cell>(procLessEqual));     
    //Logical and Type Checking Operators
    env->define("and?", std::make_shared<Cell>(procAnd));
    env->define("or?", std::make_shared<Cell>(procOr));
    env->define("number?", std::make_shared<Cell>(procNumber));
    env->define("symbol?", std::make_shared<Cell>(procSymbol));
    env->define("list?", std::make_shared<Cell>(procList));
    env->define("nil?", std::make_shared<Cell>(procNil));
    // t and nil symbols
    env->define("t", std::make_shared<Cell>(Symbol, "t"));   
    env->define("nil", std::make_shared<Cell>(Symbol, "nil")); 
    //Define commands
    env->define("quote", std::make_shared<Cell>(Symbol, "quote"));
    env->define("eval", std::make_shared<Cell>(Symbol, "eval"));
    env->define("cons", std::make_shared<Cell>(procCons));
    env->define("car", std::make_shared<Cell>(procCar));
    env->define("cdr", std::make_shared<Cell>(procCdr));
    env->define("set", std::make_shared<Cell>(Symbol, "set"));

    return env;
}

///////////////////////////////////////////////////////////////-TOKENIZE INPUT-////////////////////////////////////////////////////////////
std::vector<std::string> tokenize(const std::string& input) {
    std::vector<std::string> tokens;
    std::string token;
    bool in_string = false;

    for (size_t i = 0; i < input.size(); i++) {
        char c = input[i];

        if (c == '"') {
            if (in_string) {
                token += c;  // End of string
                tokens.push_back(token);  // Push complete string as a token
                token.clear();
                in_string = false;
            } else {
                if (!token.empty()) {
                    tokens.push_back(token);  // Push preceding token if exists
                    token.clear();
                }
                token += c;  // Start of string
                in_string = true;
            }
        } else if (isspace(c) && !in_string) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else if ((c == '(' || c == ')' || c == '\'') && !in_string) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(std::string(1, c));
        } else {
            token += c;
        }
    }

    if (!token.empty()) {
        tokens.push_back(token);
    }

    return tokens;
}

CellPtr atom(const std::string& token) {
    if (token.size() >= 2 && token.front() == '"' && token.back() == '"') {
        std::string inner_token = token.substr(1, token.size() - 2);  // Remove the quotes
        if (isNumber(inner_token)) {
            return makeNumber(std::stol(inner_token));
        }
        return std::make_shared<Cell>(Symbol, inner_token);  // Treat as a string symbol if not a number
    }
    if (isNumber(token)) {
        return makeNumber(std::stol(token));
    }
    return std::make_shared<Cell>(Symbol, token);
}


CellPtr readFromTokens(std::vector<std::string>& tokens);

CellPtr read(const std::string& s) {
    auto tokens = tokenize(s);
    return readFromTokens(tokens);
}

CellPtr readFromTokens(std::vector<std::string>& tokens) {
    if (tokens.empty()) throw std::runtime_error("Unexpected EOF");

    std::string token = tokens[0];
    tokens.erase(tokens.begin());

    if (token == "(") {
        auto L = std::make_shared<Cell>(List);
        while (tokens[0] != ")") {
            L->list.push_back(readFromTokens(tokens));
        }
        tokens.erase(tokens.begin());  // Pop ")"
        return L;
    } else if (token == ")") {
        throw std::runtime_error("Unexpected )");
    } else if (token == "'") {
        // Convert 'expression to (quote expression)
        auto quotedExpr = std::make_shared<Cell>(List);
        quotedExpr->list.push_back(std::make_shared<Cell>(Symbol, "quote"));
        quotedExpr->list.push_back(readFromTokens(tokens));
        return quotedExpr;
    } else {
        return atom(token);
    }
}

// Parallel lists for environment
std::vector<CellPtr> symbolTable;
std::vector<CellPtr> valueTable;

// Set a symbol to a value in the environment
void set(const std::string& name, const CellPtr& value) {
    for (size_t i = 0; i < symbolTable.size(); ++i) {
        if (symbolTable[i]->val == name) {
            valueTable[i] = value;
            return;
        }
    }
    symbolTable.push_back(std::make_shared<Cell>(Symbol, name));
    valueTable.push_back(value);
}

// Lookup a symbol's value in the environment
CellPtr lookup(const std::string& name) {
    for (size_t i = 0; i < symbolTable.size(); ++i) {
        if (symbolTable[i]->val == name) {
            return valueTable[i];
        }
    }
    return std::make_shared<Cell>(Symbol, name); // Return the symbol itself if not found
}

///////////////////////////////////////////////////////-EVAL-FX-//////////////////////////////////////////////////////////////////////////
CellPtr eval(CellPtr expr, EnvironmentPtr env) {
    if (expr->type == Number) return expr;

    // Treat as a literal if enclosed in double quotes
    if (expr->type == Symbol && expr->val.size() >= 2 && expr->val.front() == '"' && expr->val.back() == '"') {
        return expr;
    }

    // Lookup symbols in environment
    if (expr->type == Symbol) return env->find(expr->val);

    // Return empty lists as is
    if (expr->list.empty()) return expr;

    CellPtr first = expr->list[0]; // First element in the list (function or special form)

    // QUOTE
    if (first->type == Symbol && first->val == "quote") {
        return expr->list[1]; // Return the second element
    }

    // EVAL
    if (first->type == Symbol && first->val == "eval") {
        return eval(eval(expr->list[1], env), env); // Evaluate twice
    }

    // SET
    if (first->type == Symbol && first->val == "set") {
        if (expr->list.size() != 3) {
            throw std::runtime_error("set requires exactly two arguments: a name and a value");
        }
        std::string var = expr->list[1]->val;      // Second element is the variable name
        if (expr->list[1]->type != Symbol) {
            throw std::runtime_error("First argument of set must be a symbol");
        }
        CellPtr val = eval(expr->list[2], env);    // Evaluate the third element
        env->define(var, val);                     // Define the variable in the environment
        return val;
    }

    // IF (Updated)
    if (first->type == Symbol && first->val == "if") {
        if (expr->list.size() < 3) {
            throw std::runtime_error("if requires at least three arguments");
        }
        CellPtr condition = eval(expr->list[1], env); // Evaluate condition
        if (isTrue(condition)) {
            return eval(expr->list[2], env);          // Evaluate true branch
        } else if (expr->list.size() > 3) {
            return eval(expr->list[3], env);          // Evaluate false branch
        }
        return std::make_shared<Cell>(Symbol, "nil"); // Default to nil if false branch is missing
    }

    // COND (Updated)
    if (first->type == Symbol && first->val == "cond") {
        for (size_t i = 1; i < expr->list.size(); ++i) {
            CellPtr clause = expr->list[i];
            if (clause->type != List || clause->list.size() != 2) {
                throw std::runtime_error("Each cond clause must have exactly two elements");
            }
            CellPtr condition = eval(clause->list[0], env); // Evaluate condition
            if (isTrue(condition)) {
                return eval(clause->list[1], env); // Evaluate and return matching clause
            }
        }
        return std::make_shared<Cell>(Symbol, "nil"); // Default to nil if no conditions match
    }

    // AND (New)
    if (first->type == Symbol && first->val == "and") {
        if (expr->list.size() != 3) {
            throw std::runtime_error("and requires exactly two arguments");
        }
        CellPtr e1 = eval(expr->list[1], env); // Evaluate first expression
        if (!isTrue(e1)) return std::make_shared<Cell>(Symbol, "nil"); // Short-circuit if e1 is nil
        return eval(expr->list[2], env); // Evaluate and return second expression
    }

    // OR (New)
    if (first->type == Symbol && first->val == "or") {
        if (expr->list.size() != 3) {
            throw std::runtime_error("or requires exactly two arguments");
        }
        CellPtr e1 = eval(expr->list[1], env); // Evaluate first expression
        if (isTrue(e1)) return std::make_shared<Cell>(Symbol, "t"); // Short-circuit if e1 is true
        return eval(expr->list[2], env); // Evaluate and return second expression
    }

    // Arithmetic and comparison operators
    if (first->type == Symbol) {
        std::string funcName = first->val;

        // Arithmetic operators
        if (funcName == "add") return procAdd({ eval(expr->list[1], env), eval(expr->list[2], env) });
        if (funcName == "sub") return procSub({ eval(expr->list[1], env), eval(expr->list[2], env) });
        if (funcName == "mul") return procMul({ eval(expr->list[1], env), eval(expr->list[2], env) });
        if (funcName == "div") return procDiv({ eval(expr->list[1], env), eval(expr->list[2], env) });

        // Comparison operators
        if (funcName == "eq") return procEquals({ eval(expr->list[1], env), eval(expr->list[2], env) });
        if (funcName == "lt") return procLessThan({ eval(expr->list[1], env), eval(expr->list[2], env) });
        if (funcName == "gt") return procGreaterThan({ eval(expr->list[1], env), eval(expr->list[2], env) });
        if (funcName == "lte") return procLessEqual({ eval(expr->list[1], env), eval(expr->list[2], env) });
        if (funcName == "gte") return procGreaterEqual({ eval(expr->list[1], env), eval(expr->list[2], env) });

        // Existing logic for handling other functions
        if (funcName == "define") {
            std::string var = expr->list[1]->val;
            CellPtr val = eval(expr->list[2], env);
            env->define(var, val);
            return val;
        }

        // symbol? function
        if (funcName == "symbol?") {
            if (expr->list.size() != 2) throw std::runtime_error("symbol? requires one argument");
            CellPtr arg = expr->list[1];
            return std::make_shared<Cell>(Symbol, (arg->type == Symbol && !(arg->val.empty() || isdigit(arg->val[0]))) ? "t" : "nil");
        }

        // number? function
        if (funcName == "number?") {
            if (expr->list.size() != 2) throw std::runtime_error("number? requires one argument");
            CellPtr arg = expr->list[1];
            return std::make_shared<Cell>(Symbol, (arg->type == Number) ? "t" : "nil");
        }

        // Look up function and evaluate its arguments
        CellPtr proc = env->find(funcName);
        Cells args;
        for (size_t i = 1; i < expr->list.size(); i++) {
            args.push_back(eval(expr->list[i], env)); // Evaluate arguments recursively
        }
        if (proc->type == Proc) return proc->proc(args);
    }

    // If no match, throw an error
    throw std::runtime_error("Unknown function or expression");
}

//////////////////////////////////////////////////////////////To-String-FX-///////////////////////////////////////////////////////////////
std::string toString(CellPtr exp) {
    if (exp->type == Number || exp->type == Symbol) return exp->val;
    if (exp->type == List) {
        std::string s = "(";
        for (auto& e : exp->list) s += toString(e) + " ";
        s.pop_back();
        return s + ")";
    }
    if (exp->type == Lambda) return "<Lambda>";
    return "<Proc>";
}

void repl(const std::string& prompt, EnvironmentPtr env) {
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) break;
        if (line.empty()) continue;
        try {
            CellPtr result = eval(read(line), env);
            std::cout << toString(result) << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

int main() {
    auto global_env = std::make_shared<Environment>();
    repl("lisp> ", global_env);
    return 0;
}

