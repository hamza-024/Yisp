#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>

enum CellType { Symbol, Number, List };
using CellPtr = std::shared_ptr<struct Cell>;

struct Cell {
    CellType type;
    std::string val;
    std::vector<CellPtr> list;

    Cell(CellType type) : type(type) {}
    Cell(CellType type, const std::string& val) : type(type), val(val) {}
};

//////////////////////////////////////////////////////////////-TOKENIZATION-//////////////////////////////////////////////////////////////

std::vector<std::string> tokenize(const std::string& input) {
    std::vector<std::string> tokens;
    std::string token;
    bool in_string = false;

    for (size_t i = 0; i < input.size(); i++) {
        char c = input[i];

        if (c == '"') {
            if (in_string) {
                token += c; // End of string
                tokens.push_back(token); // Push complete string as a token
                token.clear();
                in_string = false;
            } else {
                if (!token.empty()) {
                    tokens.push_back(token); // Push preceding token if exists
                    token.clear();
                }
                token += c; // Start of string
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
        return std::make_shared<Cell>(Symbol, token.substr(1, token.size() - 2));
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
        tokens.erase(tokens.begin()); // Pop ")"
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

//////////////////////////////////////////////////////////////-EVAL FUNCTION-//////////////////////////////////////////////////////////////

CellPtr eval(CellPtr expr) {
    if (expr->type == Number || expr->type == Symbol) return expr;
    if (expr->type == List && expr->list.empty()) return expr;

    throw std::runtime_error("Evaluation not implemented for this version");
}

//////////////////////////////////////////////////////////////-PRINT FUNCTION-/////////////////////////////////////////////////////////////

std::string toString(CellPtr exp) {
    if (exp->type == Number || exp->type == Symbol) return exp->val;
    if (exp->type == List) {
        std::string s = "(";
        for (auto& e : exp->list) s += toString(e) + " ";
        s.pop_back();
        return s + ")";
    }
    return "<Unknown>";
}

//////////////////////////////////////////////////////////////-REPL FUNCTION-//////////////////////////////////////////////////////////////

void repl(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) break;
        if (line.empty()) continue;
        try {
            CellPtr result = eval(read(line));
            std::cout << toString(result) << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

//////////////////////////////////////////////////////////////-MAIN FUNCTION-//////////////////////////////////////////////////////////////

int main() {
    repl("lisp> ");
    return 0;
}
