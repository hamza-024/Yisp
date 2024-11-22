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

///////////////////////////////////////////////////////-EVAL-FX-//////////////////////////////////////////////////////////////////////////
CellPtr eval(CellPtr expr, EnvironmentPtr env) {
    if (expr->type == Number) return expr;

    // Treat as a literal if enclosed in double quotes
    if (expr->type == Symbol && expr->val.size() >= 2 && expr->val.front() == '"' && expr->val.back() == '"') {
        return expr;
    }

    // Lookup symbols in environment
    if (expr->type == Symbol) throw std::runtime_error("Symbols cannot be evaluated in this version");

    // Return empty lists as is
    if (expr->list.empty()) return expr;

    CellPtr first = expr->list[0]; // First element in the list (function or special form)

    // QUOTE (Placeholder for later sprint)
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
    return "<Proc>";
}

void repl(const std::string& prompt, EnvironmentPtr env) {
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) break;
        if (line.empty()) continue;
        try {
            CellPtr result = eval(nullptr, env); // Temporarily handle REPL logic
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
