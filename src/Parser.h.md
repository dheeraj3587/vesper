## `src/Parser.h` Hinglish Mein Line-by-Line Explanation

Yeh file, `Parser.h`, C++ mein likhe gaye Kaleidoscope language ke compiler ke parser component ke liye header file hai. Ismein `Parser` class aur usse jude definitions hain.

1.  `#ifndef PARSER_H`

    - **Hinglish:** Yeh ek preprocessor directive hai jo check karta hai ki `PARSER_H` pehle se define kiya gaya hai ya nahi. Agar nahi, toh aage ka code process hoga. Isse "multiple inclusion" ki problem se bacha jaata hai, yaani ek hi header file baar baar include na ho.
    - **English:** This is a preprocessor directive that checks if `PARSER_H` has been defined before. If not, the subsequent code is processed. This prevents the "multiple inclusion" problem, meaning the same header file is not included multiple times.

2.  `#define PARSER_H`

    - **Hinglish:** Agar `PARSER_H` define nahi tha, toh ab yeh directive use define kar deta hai. Iska matlab, agar yeh file dobara include karne ki koshish ki gayi, toh `#ifndef` false ho jayega aur content skip ho jayega.
    - **English:** If `PARSER_H` was not defined, this directive defines it now. This means if an attempt is made to include this file again, the `#ifndef` will be false, and the content will be skipped.

3.  `#include <memory>`

    - **Hinglish:** Yeh C++ standard library ka header `memory` include karta hai. Ismein smart pointers jaise `std::unique_ptr` hote hain, jo memory management ko aasan banate hain.
    - **English:** This includes the `memory` header from the C++ standard library. It contains smart pointers like `std::unique_ptr`, which make memory management easier.

4.  `#include <string>`

    - **Hinglish:** Yeh C++ standard library ka header `string` include karta hai, jo `std::string` class provide karta hai text strings ke saath kaam karne ke liye.
    - **English:** This includes the `string` header from the C++ standard library, which provides the `std::string` class for working with text strings.

5.  `#include <vector>`

    - **Hinglish:** Yeh C++ standard library ka header `vector` include karta hai, jo `std::vector` class (dynamic array) provide karta hai.
    - **English:** This includes the `vector` header from the C++ standard library, which provides the `std::vector` class (dynamic array).

6.  `#include "AST.h"`

    - **Hinglish:** Yeh hamare project ka custom header `AST.h` include karta hai. `AST.h` mein Abstract Syntax Tree (AST) ke nodes ke definitions hote hain, jo parser code ko represent karne ke liye banata hai.
    - **English:** This includes our project's custom header `AST.h`. `AST.h` contains the definitions for Abstract Syntax Tree (AST) nodes, which the parser creates to represent the code.

7.  `using namespace std;`

    - **Hinglish:** Yeh line `std` namespace ke sabhi naamon ko current scope mein laati hai. Iska matlab hai ki `std::cout`, `std::vector`, `std::string`, etc., ko bina `std::` prefix ke `cout`, `vector`, `string` likh sakte hain.
    - **English:** This line brings all names from the `std` namespace into the current scope. This means that `std::cout`, `std::vector`, `std::string`, etc., can be written as `cout`, `vector`, `string` without the `std::` prefix.

8.  `// Token enum`

    - **Hinglish:** Yeh ek comment hai jo batata hai ki neeche `Token` ka enumeration (enum) define kiya gaya hai.
    - **English:** This is a comment indicating that the `Token` enumeration (enum) is defined below.

9.  `enum Token`

    - **Hinglish:** Yeh `Token` naam ka ek enumeration shuru karta hai. Enum ek user-defined type hai jismein named integer constants hote hain. Yeh tokens ko represent karne ke liye istemal hota hai jo lexer se milte hain.
    - **English:** This starts an enumeration named `Token`. An enum is a user-defined type consisting of named integer constants. It is used to represent the tokens received from the lexer.

10. `{`

    - **Hinglish:** Enum definition ka opening brace.
    - **English:** Opening brace for the enum definition.

11. `tok_eof = -1,`

    - **Hinglish:** `tok_eof` ek enumerator hai jo "end of file" token ko represent karta hai. Iski value -1 set ki gayi hai.
    - **English:** `tok_eof` is an enumerator representing the "end of file" token. Its value is set to -1.

12. `tok_def = -2,`

    - **Hinglish:** `tok_def` function definition (`def` keyword) ke liye token hai.
    - **English:** `tok_def` is the token for function definitions (`def` keyword).

13. `tok_extern = -3,`

    - **Hinglish:** `tok_extern` external function declarations (`extern` keyword) ke liye token hai.
    - **English:** `tok_extern` is the token for external function declarations (`extern` keyword).

14. `tok_identifier = -4,`

    - **Hinglish:** `tok_identifier` identifiers (jaise variable ya function names) ke liye token hai.
    - **English:** `tok_identifier` is the token for identifiers (like variable or function names).

15. `tok_number = -5,`

    - **Hinglish:** `tok_number` numeric literals (numbers) ke liye token hai.
    - **English:** `tok_number` is the token for numeric literals (numbers).

16. `tok_if = -6,`

    - **Hinglish:** `tok_if` `if` keyword ke liye token hai (conditional statements).
    - **English:** `tok_if` is the token for the `if` keyword (conditional statements).

17. `tok_then = -7,`

    - **Hinglish:** `tok_then` `then` keyword ke liye token hai (conditional statements).
    - **English:** `tok_then` is the token for the `then` keyword (conditional statements).

18. `tok_else = -8,`

    - **Hinglish:** `tok_else` `else` keyword ke liye token hai (conditional statements).
    - **English:** `tok_else` is the token for the `else` keyword (conditional statements).

19. `tok_for = -9,`

    - **Hinglish:** `tok_for` `for` keyword ke liye token hai (looping constructs).
    - **English:** `tok_for` is the token for the `for` keyword (looping constructs).

20. `tok_in = -10,`

    - **Hinglish:** `tok_in` `in` keyword ke liye token hai (aksar `for` loops ke saath use hota hai).
    - **English:** `tok_in` is the token for the `in` keyword (often used with `for` loops).

21. `tok_binary = -11,`

    - **Hinglish:** `tok_binary` custom binary operator definitions ke liye token hai.
    - **English:** `tok_binary` is the token for custom binary operator definitions.

22. `tok_unary = -12,`

    - **Hinglish:** `tok_unary` custom unary operator definitions ke liye token hai.
    - **English:** `tok_unary` is the token for custom unary operator definitions.

23. `tok_var = -13`

    - **Hinglish:** `tok_var` variable declarations (`var` keyword) ke liye token hai.
    - **English:** `tok_var` is the token for variable declarations (`var` keyword).

24. `};`

    - **Hinglish:** Enum definition ka closing brace aur semicolon.
    - **English:** Closing brace and semicolon for the enum definition.

25. `class Parser`

    - **Hinglish:** `Parser` naam ki ek class define karta hai. Yeh class Kaleidoscope code ko parse karne ki logic encapsulate karegi.
    - **English:** Defines a class named `Parser`. This class will encapsulate the logic for parsing Kaleidoscope code.

26. `{`

    - **Hinglish:** Class definition ka opening brace.
    - **English:** Opening brace for the class definition.

27. `private:`

    - **Hinglish:** Yeh access specifier batata hai ki neeche declare kiye gaye members class ke andar hi accessible honge (encapsulation).
    - **English:** This access specifier indicates that the members declared below will only be accessible from within the class (encapsulation).

28. `int CurrentToken;`

    - **Hinglish:** Yeh ek integer member variable hai jo current token ko store karta hai, jo parser abhi process kar raha hai. Iski value `Token` enum se aayegi.
    - **English:** This is an integer member variable that stores the current token the parser is currently processing. Its value will come from the `Token` enum.

29. `vector<string> Tokens;`

    - **Hinglish:** Ab yeh istemal nahi ho raha hai, pehle yeh lexer se mile tokens ki list ko store karne ke liye tha. Ab `CurrentToken`, `IdentifierStr`, aur `NumVal` ko seedha `getNextToken()` update karta hai.
    - **English:** This is no longer used; it was previously for storing the list of tokens from the lexer. Now `CurrentToken`, `IdentifierStr`, and `NumVal` are updated directly by `getNextToken()`.

30. `size_t CurrentPos;`

    - **Hinglish:** Ab yeh istemal nahi ho raha hai. Pehle yeh `Tokens` vector mein current position track karta tha.
    - **English:** This is no longer used. It previously tracked the current position in the `Tokens` vector.

31. `// Token semantic values`

    - **Hinglish:** Comment batata hai ki neeche token ke semantic values (extra information) store karne ke liye variables hain.
    - **English:** Comment indicating that the variables below are for storing semantic values (extra information) of tokens.

32. `string IdentifierStr; // Holds the identifier name if the current token is tok_identifier`

    - **Hinglish:** Yeh ek string member variable hai. Jab `CurrentToken` `tok_identifier` hota hai, toh `IdentifierStr` us identifier ka naam (jaise "myVar") store karta hai.
    - **English:** This is a string member variable. When `CurrentToken` is `tok_identifier`, `IdentifierStr` stores the name of that identifier (e.g., "myVar").

33. `double NumVal;        // Holds the number value if the current token is tok_number`

    - **Hinglish:** Yeh ek double member variable hai. Jab `CurrentToken` `tok_number` hota hai, toh `NumVal` us number ki actual value (jaise 3.14) store karta hai.
    - **English:** This is a double member variable. When `CurrentToken` is `tok_number`, `NumVal` stores the actual value of that number (e.g., 3.14).

34. `// Helper functions to advance the token stream and parse specific grammar rules.`

    - **Hinglish:** Comment batata hai ki neeche helper functions declare kiye gaye hain jo token stream ko aage badhane aur specific grammar rules ko parse karne mein madad karte hain.
    - **English:** Comment indicating that helper functions are declared below which help in advancing the token stream and parsing specific grammar rules.

35. `int getNextToken();`

    - **Hinglish:** Yeh lexer se agla token fetch karta hai aur `CurrentToken` (aur zaroorat padne par `IdentifierStr` ya `NumVal`) ko update karta hai. Return value naya `CurrentToken` hota hai.
    - **English:** This fetches the next token from the lexer and updates `CurrentToken` (and `IdentifierStr` or `NumVal` if needed). The return value is the new `CurrentToken`.

36. `int GetTokPrecedence();`

    - **Hinglish:** Yeh current token (jo ek binary operator hona chahiye) ki precedence (priority) return karta hai. Precedence decide karta hai ki expressions kaise evaluate honge (jaise `*` `+` se pehle hota hai).
    - **English:** This returns the precedence (priority) of the current token (which should be a binary operator). Precedence decides how expressions are evaluated (e.g., `*` comes before `+`).

37. `unique_ptr<ExprAST> ParseNumberExpr();`

    - **Hinglish:** Yeh function ek number expression (jaise `123` ya `4.5`) ko parse karta hai aur uska `NumberExprAST` node return karta hai.
    - **English:** This function parses a number expression (like `123` or `4.5`) and returns its `NumberExprAST` node.

38. `unique_ptr<ExprAST> ParseParenExpr();`

    - **Hinglish:** Yeh function parentheses `()` mein band expression (jaise `(a+b)`) ko parse karta hai.
    - **English:** This function parses an expression enclosed in parentheses `()` (like `(a+b)`).

39. `unique_ptr<ExprAST> ParseIdentifierExpr();`

    - **Hinglish:** Yeh function ek identifier ko parse karta hai. Identifier ya toh ek variable reference (`x`) ho sakta hai ya function call (`foo(a,b)`).
    - **English:** This function parses an identifier. An identifier can be either a variable reference (`x`) or a function call (`foo(a,b)`).

40. `unique_ptr<ExprAST> ParsePrimary();`

    - **Hinglish:** Yeh sabse basic expressions (primary expressions) ko parse karta hai. Ismein numbers, identifiers, parenthesis expressions, `if/then/else`, `for/in`, etc., aa sakte hain. Yeh dusre `Parse...Expr` functions ko dispatch karta hai.
    - **English:** This parses the most basic expressions (primary expressions). This can include numbers, identifiers, parenthesis expressions, `if/then/else`, `for/in`, etc. It dispatches to other `Parse...Expr` functions.

41. `unique_ptr<ExprAST> ParseBinOpRHS(int ExprPrec, unique_ptr<ExprAST> LHS);`

    - **Hinglish:** Yeh function binary operator ke right-hand side (RHS) ko parse karta hai. `ExprPrec` operator ki precedence hai, aur `LHS` left-hand side ka already parsed expression hai. Operator precedence climbing algorithm ka part hai.
    - **English:** This function parses the right-hand side (RHS) of a binary operator. `ExprPrec` is the precedence of the operator, and `LHS` is the already parsed expression of the left-hand side. It's part of the operator-precedence climbing algorithm.

42. `unique_ptr<ExprAST> ParseExpression();`

    - **Hinglish:** Yeh ek poora expression parse karta hai, jismein primary expression aur uske baad binary operators ho sakte hain.
    - **English:** This parses a full expression, which can include a primary expression followed by binary operators.

43. `unique_ptr<PrototypeAST> ParsePrototype();`

    - **Hinglish:** Yeh ek function prototype (signature) ko parse karta hai, jaise `def myfunc(x y)`. Ismein function ka naam aur argument names hote hain.
    - **English:** This parses a function prototype (signature), like `def myfunc(x y)`. It includes the function name and argument names.

44. `unique_ptr<FunctionAST> ParseDefinition();`

    - **Hinglish:** Yeh ek poori function definition ko parse karta hai, jismein prototype (`def myfunc(...)`) aur function body (expression) dono hote hain.
    - **English:** This parses a complete function definition, which includes both the prototype (`def myfunc(...)`) and the function body (expression).

45. `unique_ptr<PrototypeAST> ParseExtern();`

    - **Hinglish:** Yeh ek external function declaration (`extern sin(a)`) ko parse karta hai.
    - **English:** This parses an external function declaration (`extern sin(a)`).

46. `unique_ptr<FunctionAST> ParseTopLevelExpr();`

    - **Hinglish:** Yeh ek top-level expression ko parse karta hai (jo REPL mein seedha execute ho sakta hai). Isko internally ek anonymous function (`__anon_expr`) ki tarah treat kiya jata hai.
    - **English:** This parses a top-level expression (which can be directly executed in a REPL). It is treated internally as an anonymous function (`__anon_expr`).

47. `public:`

    - **Hinglish:** Yeh access specifier batata hai ki neeche declare kiye gaye members class ke bahar se bhi accessible honge.
    - **English:** This access specifier indicates that the members declared below will be accessible from outside the class.

48. `Parser(const vector<string> &tokens);`

    - **Hinglish:** Yeh `Parser` class ka constructor hai. Original design mein yeh lexer se mile tokens ka vector leta tha. Ab, `main.cpp` mein lexer object parser ko pass kiya jata hai aur `getNextToken` lexer se directly token leta hai. Constructor abhi bhi `vector<string>` argument leta hai, lekin `main.cpp` mein empty vector pass kiya jaata hai.
    - **English:** This is the constructor for the `Parser` class. In the original design, it took a vector of tokens from the lexer. Now, in `main.cpp`, the lexer object is passed to the parser, and `getNextToken` gets tokens directly from the lexer. The constructor still takes a `vector<string>` argument, but an empty vector is passed in `main.cpp`.

49. `// Main entry point for parsing.`

    - **Hinglish:** Comment jo batata hai ki agla function parsing ke liye main entry point hai.
    - **English:** Comment indicating that the next function is the main entry point for parsing.

50. `unique_ptr<ExprAST> Parse();`

    - **Hinglish:** Yeh parser ka main function hai. Yeh top-level constructs (function definitions, externs, ya top-level expressions) ko parse karne ki koshish karta hai. Ab yeh loop mein call hota hai `main.cpp` se, semicolon-separated inputs ke liye.
    - **English:** This is the main function of the parser. It attempts to parse top-level constructs (function definitions, externs, or top-level expressions). It is now called in a loop from `main.cpp` for semicolon-separated inputs.

51. `};`

    - **Hinglish:** Class definition ka closing brace.
    - **English:** Closing brace for the class definition.

52. ` #endif // PARSER_H`
    - **Hinglish:** Yeh `#ifndef PARSER_H` directive ko end karta hai.
    - **English:** This ends the `#ifndef PARSER_H` directive.

Lekin yaad rakhein, original design mein `Parser` constructor ek `vector<string>` tokens leta tha, aur `CurrentPos` us vector mein current position track karta tha. `getNextToken()` us vector se token fetch karta tha. Ab `main.cpp` mein `Lexer` object `getNextToken()` ke andar `static` variable ke taur par store hota hai, aur `getNextToken()` seedha lexer se token maangta hai. Isliye `Tokens` aur `CurrentPos` members ab `Parser` class mein actively use nahi ho rahe hain. `Parser` constructor ko abhi bhi `vector<string>` pass kiya jaata hai `main.cpp` se, lekin woh empty hota hai.

The main changes hue hain:

- `getNextToken` ab lexer se directly communicate karta hai.
- `Parser` ka state (current token, identifier string, number value) `getNextToken` mein manage hota hai aur `Parser` ke member variables (`CurrentToken`, `IdentifierStr`, `NumVal`) mein store hota hai.
- `main.cpp` ab parser ko semicolon `(;)`, `tok_def`, `tok_extern`, ya `tok_eof` milne tak loop mein call karta hai.

#endif // PARSER_H
