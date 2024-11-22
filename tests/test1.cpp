#include "lisp.cpp"

//To run Sprint Test:
 // 1. copy and paste the code below the line into lisp.cpp below the repl() function
 // 2. Add "testSprint1()" into the main function and compile & run 
 //--------------------------------------------------------------------------------------------------------------------------------
void testSprint1() {
    EnvironmentPtr globalEnv = createGlobalEnv(); // Initialize global environment

    try {
        // Test 1: Parse a single symbol
        CellPtr expr1 = read("x");
        std::string result1 = toString(expr1);
        std::cout << "Test 1 - parse 'x': " << result1 << " - " 
                  << (result1 == "x" ? "PASS" : "FAIL") << std::endl;

        // Test 2: Parse a number
        CellPtr expr2 = read("42");
        std::string result2 = toString(expr2);
        std::cout << "Test 2 - parse '42': " << result2 << " - " 
                  << (result2 == "42" ? "PASS" : "FAIL") << std::endl;

        // Test 3: Parse a simple list
        CellPtr expr3 = read("(x 42)");
        std::string result3 = toString(expr3);
        std::cout << "Test 3 - parse '(x 42)': " << result3 << " - " 
                  << (result3 == "(x 42)") << " - " << (result3 == "(x 42)" ? "PASS" : "FAIL") << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error during Sprint 1 tests: " << e.what() << std::endl;
    }
}