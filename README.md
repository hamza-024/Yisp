# Yisp
A Lisp interpreter (language) written in C++.

## Introduction
This Lisp interpreter designed to evaluate S-expressions. It features a set of Lisp primitives, support for user-defined functions, and an interactive REPL (Read-Eval-Print Loop). 

## Project Structure

### 1. Environment and Pointer Creation
- The `Environment` structure stores variables and functions, supporting nested evaluation.
- The `Cell` structure represents Lisp data types: symbols, numbers, lists, procedures, and lambdas.
- Uses `shared_ptr` to manage memory effectively.

### 2. Procedures
- Implements core Lisp primitives such as:
  - `set`, `car`, `cdr`, `cons`, `atom`.
  - Arithmetic (`add`, `sub`, `mul`, `div`, `mod`) or (`+`, `-`, `*`, `/`, `%`).
  - Comparison (`gt`, `lt`, `eq`, `gte`, `lte`) or (`>`, `<`, `=`, `>=`, `<=`).
  - Type-checking (`number?`, `symbol?`, `list?`, `nil?`).
  - Logical operations (`and?`, `or?`, `not`).
- Includes support for user-defined functions with `lambda` and `define`.

### 3. Initialization in the Global Environment
- Adds primitives, constants, and keywords in the global environment.
- Registers all Lisp functions for easy access during evaluation.

### 4. Tokenization
- Splits user input into tokens for parsing.
- Handles quotes, parentheses, and special symbols.

### 5. Evaluation (`eval`)
- Implements the core recursive evaluation logic.
- Supports special forms like `if`, `cond`, `quote`, `eval` and user-defined functions.
- Manages argument validation and scoping for function calls.

### 6. Reading Input
- Converts user input into nested `Cell` structures representing S-expressions.
- Parses tokens into a tree structure for evaluation.

### 7. REPL (Read-Eval-Print Loop)
- Provides an interactive interface for executing Lisp commands.
- Handles user input, evaluates expressions, and prints results or errors.

## Build Instructions
To compile and run Yisp, use the following commands in your terminal:

1. **Compile the Source Code:**
   ```bash
   g++ -o lisp lisp.cpp
2. **Run the Interpreter:**
   ```bash
   ./lisp
