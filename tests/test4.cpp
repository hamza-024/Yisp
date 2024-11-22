#include "lisp.cpp"

//To run Sprint Test:
 // 1. copy and paste the code below the line into lisp.cpp below the repl() function
 // 2. Add "testSprint4()" into the main function and compile & run 
 //--------------------------------------------------------------------------------------------------------------------------------
void testSprint4() {
    EnvironmentPtr globalEnv = createGlobalEnv(); // Initialize global environment

    try {
        // Test 1: Evaluate a number
        CellPtr expr1 = read("42");
        std::string result1 = toString(eval(expr1, globalEnv));
        std::cout << "Test 1 - eval(42): " << result1 << " - " 
                  << (result1 == "42" ? "PASS" : "FAIL") << std::endl;

        // Test 2: Evaluate a symbol
        globalEnv->define("x", makeNumber(10)); // Define x = 10
        CellPtr expr2 = read("x");
        std::string result2 = toString(eval(expr2, globalEnv));
        std::cout << "Test 2 - eval(x): " << result2 << " - " 
                  << (result2 == "10" ? "PASS" : "FAIL") << std::endl;

        // Test 3: Undefined symbol
        try {
            CellPtr expr3 = read("y");
            eval(expr3, globalEnv);
            std::cout << "Test 3 - eval(y): FAIL (expected error for undefined symbol)" << std::endl;
        } catch (const std::exception&) {
            std::cout << "Test 3 - eval(y): PASS" << std::endl;
        }

        // Test 4: Set a variable
        CellPtr expr4 = read("(set z 20)");
        std::string result4 = toString(eval(expr4, globalEnv));
        std::cout << "Test 4 - set(z, 20): " << result4 << " - " 
                  << (result4 == "20" ? "PASS" : "FAIL") << std::endl;

        // Test 5: Evaluate a variable after set
        CellPtr expr5 = read("z");
        std::string result5 = toString(eval(expr5, globalEnv));
        std::cout << "Test 5 - eval(z): " << result5 << " - " 
                  << (result5 == "20" ? "PASS" : "FAIL") << std::endl;

        // Test 6: Quote a list
        CellPtr expr6 = read("(quote (a b c))");
        std::string result6 = toString(eval(expr6, globalEnv));
        std::cout << "Test 6 - quote((a b c)): " << result6 << " - " 
                  << (result6 == "(a b c)" ? "PASS" : "FAIL") << std::endl;

        // Test 7: Arithmetic operation with eval
        globalEnv->define("a", makeNumber(15)); // Define a = 15
        globalEnv->define("b", makeNumber(5));  // Define b = 5
        CellPtr expr7 = read("(add a b)");
        std::string result7 = toString(eval(expr7, globalEnv));
        std::cout << "Test 7 - add(a, b): " << result7 << " - " 
                  << (result7 == "20" ? "PASS" : "FAIL") << std::endl;

        // Test 8: Nested evaluation
        CellPtr expr8 = read("(eval (quote (add 3 4)))");
        std::string result8 = toString(eval(expr8, globalEnv));
        std::cout << "Test 8 - eval(quote(add 3 4)): " << result8 << " - " 
                  << (result8 == "7" ? "PASS" : "FAIL") << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error during Sprint 4 tests: " << e.what() << std::endl;
    }
}

