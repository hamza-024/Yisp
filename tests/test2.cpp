#include "lisp.cpp"

//To run Sprint Test:
 // 1. copy and paste the code below the line into lisp.cpp below the repl() function
 // 2. Add "testSprint2()" into the main function and compile & run 
 //--------------------------------------------------------------------------------------------------------------------------------
void testSprint2() {
    EnvironmentPtr globalEnv = createGlobalEnv(); // Initialize global environment

    // Test 1: Print nil
    try {
        CellPtr expr1 = std::make_shared<Cell>(Symbol, "nil");
        std::string result1 = toString(eval(expr1, globalEnv));
        std::cout << "Test 1 - nil: " << result1 << " - " 
                  << (result1 == "nil" ? "PASS" : "FAIL") << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test 1 failed: " << e.what() << std::endl;
    }

    // Test 2: Print truth (t)
    try {
        CellPtr expr2 = std::make_shared<Cell>(Symbol, "t");
        std::string result2 = toString(eval(expr2, globalEnv));
        std::cout << "Test 2 - truth (t): " << result2 << " - " 
                  << (result2 == "t" ? "PASS" : "FAIL") << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test 2 failed: " << e.what() << std::endl;
    }

    // Test 3: Check if a symbol is an atom
    try {
        CellPtr expr3 = read("(symbol? \"symbol\")");
        std::string result3 = toString(eval(expr3, globalEnv));
        std::cout << "Test 3 - symbol?(\"symbol\"): " << result3 << " - " 
                  << (result3 == "t" ? "PASS" : "FAIL") << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test 3 failed: " << e.what() << std::endl;
    }

    // Test 4: Check if a number is a number
    try {
        CellPtr expr4 = read("(number? \"411\")");
        std::string result4 = toString(eval(expr4, globalEnv));
        std::cout << "Test 4 - number?(\"411\"): " << result4 << " - " 
                  << (result4 == "t" ? "PASS" : "FAIL") << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test 4 failed: " << e.what() << std::endl;
    }

    // Test 5: Construct a list with cons and symbols
    try {
        CellPtr expr5 = read("(cons 'one (cons 'two (cons 'three nil)))");
        std::string result5 = toString(eval(expr5, globalEnv));
        std::cout << "Test 5 - cons('one, cons('two, cons('three, nil))): " 
                  << result5 << " - " << (result5 == "(one two three)" ? "PASS" : "FAIL") << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test 5 failed: " << e.what() << std::endl;
    }

    // Test 6: Check if nil is nil
    try {
        CellPtr expr6 = read("(nil? nil)");
        std::string result6 = toString(eval(expr6, globalEnv));
        std::cout << "Test 6 - nil?(nil): " << result6 << " - " 
                  << (result6 == "t" ? "PASS" : "FAIL") << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test 6 failed: " << e.what() << std::endl;
    }

    // Test 7: Check equality of two atoms
    try {
        CellPtr expr7 = read("(eq 'x 'x)");
        std::string result7 = toString(eval(expr7, globalEnv));
        std::cout << "Test 7 - eq('x, 'x): " << result7 << " - " 
                  << (result7 == "t" ? "PASS" : "FAIL") << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test 7 failed: " << e.what() << std::endl;
    }

    // Test 8: Check inequality of two atoms
    try {
        CellPtr expr8 = read("(eq 'x 'y)");
        std::string result8 = toString(eval(expr8, globalEnv));
        std::cout << "Test 8 - eq('x, 'y): " << result8 << " - " 
                  << (result8 == "nil" ? "PASS" : "FAIL") << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test 8 failed: " << e.what() << std::endl;
    }
}


