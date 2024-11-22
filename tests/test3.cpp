#include "lisp.cpp"

//To run Sprint Test:
 // 1. copy and paste the code below the line into lisp.cpp below the repl() function
 // 2. Add "testSprint3()" into the main function and compile & run 
 //--------------------------------------------------------------------------------------------------------------------------------
void testSprint3() {
    EnvironmentPtr globalEnv = createGlobalEnv(); // Initialize global environment

    try {
        // Test 1: Add two numbers
        CellPtr expr1 = read("(add 2 3)");
        std::string result1 = toString(eval(expr1, globalEnv));
        std::cout << "Test 1 - add(2, 3): " << result1 << " - " 
                  << (result1 == "5" ? "PASS" : "FAIL") << std::endl;

        // Test 2: Subtract two numbers
        CellPtr expr2 = read("(sub 5 3)");
        std::string result2 = toString(eval(expr2, globalEnv));
        std::cout << "Test 2 - sub(5, 3): " << result2 << " - " 
                  << (result2 == "2" ? "PASS" : "FAIL") << std::endl;

        // Test 3: Multiply two numbers
        CellPtr expr3 = read("(mul 4 3)");
        std::string result3 = toString(eval(expr3, globalEnv));
        std::cout << "Test 3 - mul(4, 3): " << result3 << " - " 
                  << (result3 == "12" ? "PASS" : "FAIL") << std::endl;

        // Test 4: Divide two numbers
        CellPtr expr4 = read("(div 10 2)");
        std::string result4 = toString(eval(expr4, globalEnv));
        std::cout << "Test 4 - div(10, 2): " << result4 << " - " 
                  << (result4 == "5" ? "PASS" : "FAIL") << std::endl;

        // Test 5: Check equality
        CellPtr expr5 = read("(eq 3 3)");
        std::string result5 = toString(eval(expr5, globalEnv));
        std::cout << "Test 5 - eq(3, 3): " << result5 << " - " 
                  << (result5 == "t" ? "PASS" : "FAIL") << std::endl;

        // Test 6: Less than comparison
        CellPtr expr6 = read("(lt 2 3)");
        std::string result6 = toString(eval(expr6, globalEnv));
        std::cout << "Test 6 - lt(2, 3): " << result6 << " - " 
                  << (result6 == "t" ? "PASS" : "FAIL") << std::endl;

        // Test 7: Greater than comparison
        CellPtr expr7 = read("(gt 5 3)");
        std::string result7 = toString(eval(expr7, globalEnv));
        std::cout << "Test 7 - gt(5, 3): " << result7 << " - " 
                  << (result7 == "t" ? "PASS" : "FAIL") << std::endl;

        // Test 8: Less than or equal to comparison
        CellPtr expr8 = read("(lte 3 3)");
        std::string result8 = toString(eval(expr8, globalEnv));
        std::cout << "Test 8 - lte(3, 3): " << result8 << " - " 
                  << (result8 == "t" ? "PASS" : "FAIL") << std::endl;

        // Test 9: Greater than or equal to comparison
        CellPtr expr9 = read("(gte 4 3)");
        std::string result9 = toString(eval(expr9, globalEnv));
        std::cout << "Test 9 - gte(4, 3): " << result9 << " - " 
                  << (result9 == "t" ? "PASS" : "FAIL") << std::endl;

                // Test 10: Modulus operation (optional if implemented)
        CellPtr expr10 = read("(mod 10 3)");
        std::string result10 = toString(eval(expr10, globalEnv));
        std::cout << "Test 10 - mod(10, 3): " << result10 << " - "
                  << (result10 == "1" ? "PASS" : "FAIL") << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error during Sprint 3 tests: " << e.what() << std::endl;
    }
}
