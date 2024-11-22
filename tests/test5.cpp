#include "lisp.cpp"

//To run Sprint Test:
 // 1. copy and paste the code below the line into lisp.cpp below the repl() function
 // 2. Add "testSprint5()" into the main function and compile & run 
 //--------------------------------------------------------------------------------------------------------------------------------
void testSprint5() {
    EnvironmentPtr globalEnv = createGlobalEnv(); // Initialize global environment

    try {
        // Test 1: Short-circuiting AND (true && true)
        CellPtr expr1 = read("(and t t)");
        std::string result1 = toString(eval(expr1, globalEnv));
        std::cout << "Test 1 - and(t, t): " << result1 << " - " 
                  << (result1 == "t" ? "PASS" : "FAIL") << std::endl;

        // Test 2: Short-circuiting AND (true && false)
        CellPtr expr2 = read("(and t nil)");
        std::string result2 = toString(eval(expr2, globalEnv));
        std::cout << "Test 2 - and(t, nil): " << result2 << " - " 
                  << (result2 == "nil" ? "PASS" : "FAIL") << std::endl;

        // Test 3: Short-circuiting OR (true || false)
        CellPtr expr3 = read("(or t nil)");
        std::string result3 = toString(eval(expr3, globalEnv));
        std::cout << "Test 3 - or(t, nil): " << result3 << " - " 
                  << (result3 == "t" ? "PASS" : "FAIL") << std::endl;

        // Test 4: Short-circuiting OR (false || false)
        CellPtr expr4 = read("(or nil nil)");
        std::string result4 = toString(eval(expr4, globalEnv));
        std::cout << "Test 4 - or(nil, nil): " << result4 << " - " 
                  << (result4 == "nil" ? "PASS" : "FAIL") << std::endl;

        // Test 5: Conditional IF (true condition)
        CellPtr expr5 = read("(if t 42 99)");
        std::string result5 = toString(eval(expr5, globalEnv));
        std::cout << "Test 5 - if(t, 42, 99): " << result5 << " - " 
                  << (result5 == "42" ? "PASS" : "FAIL") << std::endl;

        // Test 6: Conditional IF (false condition)
        CellPtr expr6 = read("(if nil 42 99)");
        std::string result6 = toString(eval(expr6, globalEnv));
        std::cout << "Test 6 - if(nil, 42, 99): " << result6 << " - " 
                  << (result6 == "99" ? "PASS" : "FAIL") << std::endl;

        // Test 7: Conditional IF (no false branch)
        CellPtr expr7 = read("(if t 42)");
        std::string result7 = toString(eval(expr7, globalEnv));
        std::cout << "Test 7 - if(t, 42): " << result7 << " - " 
                  << (result7 == "42" ? "PASS" : "FAIL") << std::endl;

        // Test 8: Conditional COND with a matching condition
        CellPtr expr8 = read("(cond (nil 1) (t 2) (nil 3))");
        std::string result8 = toString(eval(expr8, globalEnv));
        std::cout << "Test 8 - cond(nil -> 1, t -> 2, nil -> 3): " 
                  << result8 << " - " << (result8 == "2" ? "PASS" : "FAIL") << std::endl;

        // Test 9: Conditional COND with no matching condition
        CellPtr expr9 = read("(cond (nil 1) (nil 2) (nil 3))");
        std::string result9 = toString(eval(expr9, globalEnv));
        std::cout << "Test 9 - cond(nil -> 1, nil -> 2, nil -> 3): " 
                  << result9 << " - " << (result9 == "nil" ? "PASS" : "FAIL") << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error during Sprint 5 tests: " << e.what() << std::endl;
    }
}
