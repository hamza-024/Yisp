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
## Testing: All Sprints

This section provides detailed explanations and test cases for each sprint. Each test showcases the functionality implemented during the respective sprint.

## Sprint 1 Testing

### **What is being tested:**
- **Parsing symbols:** Verifies that individual symbols are parsed correctly.
- **Parsing numbers:** Ensures that numeric literals are correctly handled.
- **Parsing simple lists:** Checks the ability to read and interpret lists with mixed symbols and numbers.

### **Tests and Explanations:**

1. **Test: Parse a single symbol**
   - **Input:** `x`
   - **Explanation:** Parses the symbol `x` and ensures it is correctly represented as a symbol.
   - **Expected Output:** `x`
   - **Test Run:**
     ```lisp
     Test 1 - parse 'x': x - PASS
     ```

2. **Test: Parse a number**
   - **Input:** `42`
   - **Explanation:** Parses the numeric literal `42` and ensures it is correctly identified as a number.
   - **Expected Output:** `42`
   - **Test Run:**
     ```lisp
     Test 2 - parse '42': 42 - PASS
     ```

3. **Test: Parse a simple list**
   - **Input:** `(x 42)`
   - **Explanation:** Parses a list containing a symbol and a number, ensuring the list structure is maintained.
   - **Expected Output:** `(x 42)`
   - **Test Run:**
     ```lisp
     Test 3 - parse '(x 42)': (x 42) - PASS
     ```
