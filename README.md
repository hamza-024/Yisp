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
### Sprint 2 Tests

This section explains and evaluates the functionality tested in Sprint 2. Each test includes the input, explanation, expected output, the actual test run, and the result.

---

#### **What is being tested in Sprint 2?**
1. **`nil`:** Tests that the interpreter correctly recognizes and evaluates `nil`.
2. **`truth (t)`:** Ensures the interpreter recognizes `t` as a true value.
3. **`symbol?`:** Checks whether an expression is a symbol.
4. **`number?`:** Validates whether an expression is numeric.
5. **`cons`:** Constructs a list using `cons` and ensures it evaluates properly.
6. **`nil?`:** Confirms if a value is `nil`.
7. **`eq`:** Compares two expressions to determine equality.

---

#### **Sprint 2 Test Results**

1. **Test: Recognizing `nil`**
   - **Input:** `nil`
   - **Explanation:** Verifies that `nil` is properly recognized as the Lisp equivalent of "null" or an empty value.
   - **Expected Output:** `nil`
   - **Test Run:** 
     ```plaintext
     Test 1 - nil: nil - PASS
     ```

2. **Test: Recognizing `truth (t)`**
   - **Input:** `t`
   - **Explanation:** Ensures the interpreter recognizes `t` as a true value in the Lisp environment.
   - **Expected Output:** `t`
   - **Test Run:**
     ```plaintext
     Test 2 - truth (t): t - PASS
     ```

3. **Test: Checking `symbol?`**
   - **Input:** `(symbol? "symbol")`
   - **Explanation:** Checks whether the provided expression is a symbol and returns `t` if true.
   - **Expected Output:** `t`
   - **Test Run:**
     ```plaintext
     Test 3 failed: Symbol not found: symbol
     ```
   - **Result:** `FAIL`
   - **Explanation:** The interpreter could not evaluate the `symbol?` function, likely due to a missing or incorrect implementation.

4. **Test: Checking `number?`**
   - **Input:** `(number? "411")`
   - **Explanation:** Confirms whether the provided expression is numeric.
   - **Expected Output:** `t`
   - **Test Run:**
     ```plaintext
     Test 4 - number?("411"): t - PASS
     ```

5. **Test: Constructing a list with `cons`**
   - **Input:** `(cons 'one (cons 'two (cons 'three nil)))`
   - **Explanation:** Verifies that the `cons` function correctly constructs a list from the provided elements.
   - **Expected Output:** `(one two three)`
   - **Test Run:**
     ```plaintext
     Test 5 - cons('one, cons('two, cons('three, nil))): (one two three) - PASS
     ```

6. **Test: Checking `nil?`**
   - **Input:** `(nil? nil)`
   - **Explanation:** Ensures that the `nil?` function correctly identifies `nil` values.
   - **Expected Output:** `t`
   - **Test Run:**
     ```plaintext
     Test 6 - nil?(nil): t - PASS
     ```

7. **Test: Comparing equality with `eq` (same objects)**
   - **Input:** `(eq 'x 'x)`
   - **Explanation:** Verifies that `eq` correctly identifies two identical objects.
   - **Expected Output:** `t`
   - **Test Run:**
     ```plaintext
     Test 7 - eq('x, 'x): t - PASS
     ```

8. **Test: Comparing equality with `eq` (different objects)**
   - **Input:** `(eq 'x 'y)`
   - **Explanation:** Verifies that `eq` identifies two different objects as not equal.
   - **Expected Output:** `nil`
   - **Test Run:**
     ```plaintext
     Test 8 - eq('x, 'y): nil - PASS
     ```
### Sprint 3 Tests

This section explains and evaluates the functionality tested in Sprint 3. Each test includes the input, explanation, expected output, the actual test run, and the result.

---

#### **What is being tested in Sprint 3?**
1. **Arithmetic Operations:** Addition, subtraction, multiplication, division, and modulus (if implemented).
2. **Comparison Operators:** Equality, less than, greater than, less than or equal to, greater than or equal to.

---

#### **Sprint 3 Test Results**

1. **Test: Add two numbers**
   - **Input:** `(add 2 3)`
   - **Explanation:** Verifies that the `add` function computes the sum of two numbers.
   - **Expected Output:** `5`
   - **Test Run:**
     ```plaintext
     Test 1 - add(2, 3): 5 - PASS
     ```

2. **Test: Subtract two numbers**
   - **Input:** `(sub 5 3)`
   - **Explanation:** Verifies that the `sub` function computes the difference of two numbers.
   - **Expected Output:** `2`
   - **Test Run:**
     ```plaintext
     Test 2 - sub(5, 3): 2 - PASS
     ```

3. **Test: Multiply two numbers**
   - **Input:** `(mul 4 3)`
   - **Explanation:** Ensures that the `mul` function computes the product of two numbers.
   - **Expected Output:** `12`
   - **Test Run:**
     ```plaintext
     Test 3 - mul(4, 3): 12 - PASS
     ```

4. **Test: Divide two numbers**
   - **Input:** `(div 10 2)`
   - **Explanation:** Confirms that the `div` function computes the division of two numbers.
   - **Expected Output:** `5`
   - **Test Run:**
     ```plaintext
     Test 4 - div(10, 2): 5 - PASS
     ```

5. **Test: Check equality**
   - **Input:** `(eq 3 3)`
   - **Explanation:** Verifies that the `eq` function identifies two identical numbers as equal.
   - **Expected Output:** `t`
   - **Test Run:**
     ```plaintext
     Test 5 - eq(3, 3): t - PASS
     ```

6. **Test: Less than comparison**
   - **Input:** `(lt 2 3)`
   - **Explanation:** Ensures that the `lt` function correctly compares two numbers and identifies the smaller one.
   - **Expected Output:** `t`
   - **Test Run:**
     ```plaintext
     Test 6 - lt(2, 3): t - PASS
     ```

7. **Test: Greater than comparison**
   - **Input:** `(gt 5 3)`
   - **Explanation:** Verifies that the `gt` function correctly identifies the larger of two numbers.
   - **Expected Output:** `t`
   - **Test Run:**
     ```plaintext
     Test 7 - gt(5, 3): t - PASS
     ```

8. **Test: Less than or equal to comparison**
   - **Input:** `(lte 3 3)`
   - **Explanation:** Confirms that the `lte` function returns `t` when the first number is less than or equal to the second.
   - **Expected Output:** `t`
   - **Test Run:**
     ```plaintext
     Test 8 - lte(3, 3): t - PASS
     ```

9. **Test: Greater than or equal to comparison**
   - **Input:** `(gte 4 3)`
   - **Explanation:** Ensures that the `gte` function returns `t` when the first number is greater than or equal to the second.
   - **Expected Output:** `t`
   - **Test Run:**
     ```plaintext
     Test 9 - gte(4, 3): t - PASS
     ```

10. **Test: Modulus operation**
    - **Input:** `(mod 10 3)`
    - **Explanation:** Verifies that the `mod` function calculates the remainder of the division.
    - **Expected Output:** `1`
    - **Test Run:**
      ```plaintext
      Test 10 - mod(10, 3): 1 - PASS
      ```
### Sprint 4 Tests

This section outlines the testing for Sprint 4 functionality. **Sprint 4 primarily focuses on the `eval` function**, which evaluates expressions in the environment. It also tests how `eval` interacts with other Lisp functions, such as `set`, `quote`, and arithmetic operations. Each test includes the input provided, its explanation, the expected output, the actual test run, and whether it passed or failed.

---

#### **What is being tested in Sprint 4?**
1. **Evaluate a number or symbol.**
2. **Define and retrieve symbols.**
3. **Set variables and evaluate them.**
4. **Use `quote` to handle literal data.**
5. **Perform arithmetic operations with evaluation.**
6. **Nested evaluation using `eval`.**

---

#### **Sprint 4 Test Results**

1. **Test: Evaluate a number**
   - **Input:** `42`
   - **Explanation:** Directly evaluates a number and returns its value.
   - **Expected Output:** `42`
   - **Test Run:**
     ```plaintext
     Test 1 - eval(42): 42 - PASS
     ```

2. **Test: Evaluate a symbol**
   - **Input:** `x` (after defining `x = 10`)
   - **Explanation:** Looks up the value of a defined symbol.
   - **Expected Output:** `10`
   - **Test Run:**
     ```plaintext
     Test 2 - eval(x): 10 - PASS
     ```

3. **Test: Undefined symbol**
   - **Input:** `y`
   - **Explanation:** Attempts to evaluate an undefined symbol, expecting an error.
   - **Expected Output:** Error for undefined symbol.
   - **Test Run:**
     ```plaintext
     Test 3 - eval(y): PASS
     ```

4. **Test: Set a variable**
   - **Input:** `(set z 20)`
   - **Explanation:** Defines a variable `z` and assigns it the value `20`.
   - **Expected Output:** `20`
   - **Test Run:**
     ```plaintext
     Test 4 - set(z, 20): 20 - PASS
     ```

5. **Test: Evaluate a variable after set**
   - **Input:** `z`
   - **Explanation:** Evaluates the variable `z` after it has been defined.
   - **Expected Output:** `20`
   - **Test Run:**
     ```plaintext
     Test 5 - eval(z): 20 - PASS
     ```

6. **Test: Quote a list**
   - **Input:** `(quote (a b c))`
   - **Explanation:** Returns the list `(a b c)` without evaluating it.
   - **Expected Output:** `(a b c)`
   - **Test Run:**
     ```plaintext
     Test 6 - quote((a b c)): (a b c) - PASS
     ```

7. **Test: Arithmetic operation with eval**
   - **Input:** `(add a b)` (with `a = 15` and `b = 5`)
   - **Explanation:** Performs addition using symbols that have been defined in the environment.
   - **Expected Output:** `20`
   - **Test Run:**
     ```plaintext
     Test 7 - add(a, b): 20 - PASS
     ```

8. **Test: Nested evaluation**
   - **Input:** `(eval (quote (add 3 4)))`
   - **Explanation:** Evaluates the quoted list `(add 3 4)` to compute its result.
   - **Expected Output:** `7`
   - **Test Run:**
     ```plaintext
     Test 8 - eval(quote(add 3 4)): 7 - PASS
     ```
