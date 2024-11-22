#include "lisp.cpp"

//To run Sprint Test:
 // 1. copy and paste the code below the line into lisp.cpp below the repl() function
 // 2. Add "testSprint6()" into the main function and compile & run 
 //--------------------------------------------------------------------------------------------------------------------------------
void testSprint6() {
    EnvironmentPtr globalEnv = createGlobalEnv();

    try {
        // Test 1: Define and call a simple function
        CellPtr expr1 = read("(define square (x) (mul x x))");
        eval(expr1, globalEnv);
        CellPtr expr2 = read("(square 4)");
        std::string result2 = toString(eval(expr2, globalEnv));
        std::cout << "Test 1 - square(4): " << result2 << " - "
                  << (result2 == "16" ? "PASS" : "FAIL") << std::endl;

        // Test 2: Define and call a function with two arguments
        CellPtr expr3 = read("(define add (a b) (add a b))");
        eval(expr3, globalEnv);
        CellPtr expr4 = read("(add 5 10)");
        std::string result4 = toString(eval(expr4, globalEnv));
        std::cout << "Test 2 - add(5, 10): " << result4 << " - "
                  << (result4 == "15" ? "PASS" : "FAIL") << std::endl;

        // Test 3: Nested function calls
        CellPtr expr5 = read("(add (square 3) (square 4))");
        std::string result5 = toString(eval(expr5, globalEnv));
        std::cout << "Test 3 - add(square(3), square(4)): " << result5 << " - "
                  << (result5 == "25" ? "PASS" : "FAIL") << std::endl;

        // Test 4: Function with no arguments
        CellPtr expr6 = read("(define const () 42)");
        eval(expr6, globalEnv);
        CellPtr expr7 = read("(const)");
        std::string result7 = toString(eval(expr7, globalEnv));
        std::cout << "Test 4 - const(): " << result7 << " - "
                  << (result7 == "42" ? "PASS" : "FAIL") << std::endl;

        // Test 5: Recursive function (factorial)
        CellPtr expr8 = read("(define factorial (n) (if (eq n 0) 1 (mul n (factorial (sub n 1)))))");
        eval(expr8, globalEnv);
        CellPtr expr9 = read("(factorial 5)");
        std::string result9 = toString(eval(expr9, globalEnv));
        std::cout << "Test 5 - factorial(5): " << result9 << " - "
                  << (result9 == "120" ? "PASS" : "FAIL") << std::endl;

        // Test 6: Function with multiple nested arguments
        CellPtr expr10 = read("(define max (a b) (if (gt a b) a b))");
        eval(expr10, globalEnv);
        CellPtr expr11 = read("(max (add 3 5) (mul 2 4))");
        std::string result11 = toString(eval(expr11, globalEnv));
        std::cout << "Test 6 - max(add(3, 5), mul(2, 4)): " << result11 << " - "
                  << (result11 == "8" ? "PASS" : "FAIL") << std::endl;

        // Test 7: Function shadowing (local scope test)
        CellPtr expr12 = read("(define shadow_test (x) (set x 99))");
        eval(expr12, globalEnv);
        CellPtr expr13 = read("(shadow_test 42)");
        std::string result13 = toString(eval(expr13, globalEnv));
        std::cout << "Test 7 - shadow_test(42): " << result13 << " - "
                  << (result13 == "99" ? "PASS" : "FAIL") << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error during Sprint 6 tests: " << e.what() << std::endl;
    }
}