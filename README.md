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

This section provides detailed explanations and test cases for each sprint. Each test was run through the main file. Testing code can be found in tests directory. 

### Sprint 1 Tests
---

#### **What is being tested:**
- **Parsing symbols:** Verifies that individual symbols are parsed correctly.
- **Parsing numbers:** Ensures that numeric literals are correctly handled.
- **Parsing simple lists:** Checks the ability to read and interpret lists with mixed symbols and numbers.

#### **Tests and Explanations:**

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
---

#### **What is being tested in Sprint 2?**
1. **`nil`:** Tests that the interpreter correctly recognizes and evaluates `nil`.
2. **`truth (t)`:** Ensures the interpreter recognizes `t` as a true value.
3. **`symbol?`:** Checks whether an expression is a symbol.
4. **`number?`:** Validates whether an expression is numeric.
5. **`cons`:** Constructs a list using `cons` and ensures it evaluates properly.
6. **`nil?`:** Confirms if a value is `nil`.
7. **`eq`:** Compares two expressions to determine equality.


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
---

#### **What is being tested in Sprint 3?**
1. **Arithmetic Operations:** Addition, subtraction, multiplication, division, and modulus (if implemented).
2. **Comparison Operators:** Equality, less than, greater than, less than or equal to, greater than or equal to.


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
---


#### **What is being tested in Sprint 4?**
1. **Evaluate a number or symbol.**
2. **Define and retrieve symbols.**
3. **Set variables and evaluate them.**
4. **Use `quote` to handle literal data.**
5. **Perform arithmetic operations with evaluation.**
6. **Nested evaluation using `eval`.**


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

### Sprint 5 Tests
---

#### **What is being tested in Sprint 5?**
1. **Short-circuiting logical AND (`and`).**
   - Evaluate the first expression, and return `nil` if it’s false; otherwise, evaluate the second expression.
2. **Short-circuiting logical OR (`or`).**
   - Evaluate the first expression, and return its value if true; otherwise, evaluate the second expression.
3. **Conditional branching with `if`.**
   - Evaluate a condition and execute one of two branches based on the result.
4. **Conditional branching with `cond`.**
   - Evaluate a series of condition-action pairs, executing the action corresponding to the first true condition.


#### **Sprint 5 Test Results**

1. **Test: Short-circuiting AND (`and t t`)**
   - **Input:** `(and t t)`
   - **Explanation:** Both expressions evaluate to true, so the result is `t`.
   - **Expected Output:** `t`
   - **Test Run:**
     ```plaintext
     Test 1 - and(t, t): t - PASS
     ```

2. **Test: Short-circuiting AND with `nil` (`and t nil`)**
   - **Input:** `(and t nil)`
   - **Explanation:** The first expression is true, but the second is false, so the result is `nil`.
   - **Expected Output:** `nil`
   - **Test Run:**
     ```plaintext
     Test 2 - and(t, nil): nil - PASS
     ```

3. **Test: Short-circuiting OR (`or t nil`)**
   - **Input:** `(or t nil)`
   - **Explanation:** The first expression is true, so the result is `t` without evaluating the second expression.
   - **Expected Output:** `t`
   - **Test Run:**
     ```plaintext
     Test 3 - or(t, nil): t - PASS
     ```

4. **Test: Short-circuiting OR with `nil` (`or nil nil`)**
   - **Input:** `(or nil nil)`
   - **Explanation:** Both expressions evaluate to false, so the result is `nil`.
   - **Expected Output:** `nil`
   - **Test Run:**
     ```plaintext
     Test 4 - or(nil, nil): nil - PASS
     ```

5. **Test: Conditional IF (true condition)**
   - **Input:** `(if t 42 99)`
   - **Explanation:** The condition evaluates to true, so the result is the first branch (`42`).
   - **Expected Output:** `42`
   - **Test Run:**
     ```plaintext
     Test 5 - if(t, 42, 99): 42 - PASS
     ```

6. **Test: Conditional IF (false condition)**
   - **Input:** `(if nil 42 99)`
   - **Explanation:** The condition evaluates to false, so the result is the second branch (`99`).
   - **Expected Output:** `99`
   - **Test Run:**
     ```plaintext
     Test 6 - if(nil, 42, 99): 99 - PASS
     ```

7. **Test: Conditional IF with no false branch**
   - **Input:** `(if t 42)`
   - **Explanation:** The condition evaluates to true, and there’s no false branch, so the result is `42`.
   - **Expected Output:** `42`
   - **Test Run:**
     ```plaintext
     Test 7 - if(t, 42): 42 - PASS
     ```

8. **Test: Conditional COND with a matching condition**
   - **Input:** `(cond (nil 1) (t 2) (nil 3))`
   - **Explanation:** The second condition (`t`) evaluates to true, so its associated action (`2`) is executed.
   - **Expected Output:** `2`
   - **Test Run:**
     ```plaintext
     Test 8 - cond(nil -> 1, t -> 2, nil -> 3): 2 - PASS
     ```

9. **Test: Conditional COND with no matching condition**
   - **Input:** `(cond (nil 1) (nil 2) (nil 3))`
   - **Explanation:** None of the conditions evaluate to true, so the result is `nil`.
   - **Expected Output:** `nil`
   - **Test Run:**
     ```plaintext
     Test 9 - cond(nil -> 1, nil -> 2, nil -> 3): nil - PASS

### **Sprint 6 Tests**
---

#### **What is being tested in Sprint 6?**
1. **Defining user-defined functions (`define`).**
   - The ability to define reusable functions with custom arguments and body expressions.
2. **Calling user-defined functions.**
   - Verifies that functions are properly evaluated and return the expected results.
3. **Nested function calls.**
   - Tests the capability of evaluating functions that call other functions, ensuring proper argument handling and environment usage.
4. **Functions with no arguments.**
   - Ensures that functions without parameters can be defined and called correctly.
5. **Variable shadowing within functions.**
   - Tests whether arguments in a function correctly shadow global variables in the environment during execution.

#### **Sprint 6 Test Results**

1. **Test: Define and call a simple function**
   - **Input:**
     ```lisp
     (define square (x) (mul x x))
     (square 4)
     ```
   - **Explanation:** Defines a function `square` that takes one argument `x` and returns the result of multiplying `x` by itself. Then calls `square` with the argument `4`.
   - **Expected Output:** `16`
   - **Test Run:**
     ```plaintext
     Test 1 - square(4): 16 - PASS
     ```

2. **Test: Define and call a function with two arguments**
   - **Input:**
     ```lisp
     (define add (a b) (add a b))
     (add 5 10)
     ```
   - **Explanation:** Defines a function `add` that takes two arguments `a` and `b`, and returns their sum. Then calls `add` with the arguments `5` and `10`.
   - **Expected Output:** `15`
   - **Test Run:**
     ```plaintext
     Test 2 - add(5, 10): 15 - PASS
     ```

3. **Test: Nested function calls**
   - **Input:**
     ```lisp
     (add (square 3) (square 4))
     ```
   - **Explanation:** Calls the previously defined `add` function with the results of two nested `square` calls: `square(3)` and `square(4)`.
   - **Expected Output:** `25`
   - **Test Run:**
     ```plaintext
     Test 3 - add(square(3), square(4)): 25 - PASS
     ```

4. **Test: Function with no arguments**
   - **Input:**
     ```lisp
     (define const () 42)
     (const)
     ```
   - **Explanation:** Defines a constant function `const` that takes no arguments and always returns `42`. Then calls `const`.
   - **Expected Output:** `42`
   - **Test Run:**
     ```plaintext
     Test 4 - const(): 42 - PASS
     ```

5. **Test: Recursive function for factorial**
   - **Input:**
     ```lisp
     (define factorial (n) (if (eq n 0) 1 (mul n (factorial (sub n 1)))))
     (factorial 5)
     ```
   - **Explanation:** Defines a recursive function `factorial` that calculates the factorial of a number `n`. Then calls `factorial` with the argument `5`.
   - **Expected Output:** `120`
   - **Test Run:**
     ```plaintext
     Test 5 - factorial(5): 120 - PASS
     ```

6. **Test: Combining functions with `max`**
   - **Input:**
     ```lisp
     (define max (a b) (if (gt a b) a b))
     (max (add 3 5) (mul 2 4))
     ```
   - **Explanation:** Defines a function `max` that returns the larger of two arguments. Combines `add` and `mul` functions as inputs to `max`.
   - **Expected Output:** `8`
   - **Test Run:**
     ```plaintext
     Test 6 - max(add(3, 5), mul(2, 4)): 8 - PASS
     ```

7. **Test: Shadowing in function definitions**
   - **Input:** 
     ```lisp
     (define shadow_test (x) (set x 99) x)
     (shadow_test 42)
     ```
   - **Explanation:** Verifies that the function handles shadowing by redefining a variable within its scope and correctly returning the updated value.
   - **Expected Output:** `99`
   - **Test Run:**
     ```plaintext
     Test 7 - shadow_test(42): 99 - PASS
     ```
