## `src/AST.h` - Line by Line Hinglish Explanation

Yeh file Abstract Syntax Tree (AST) ke nodes ko define karti hai. AST, code ka ek tree jaisa structure hota hai jo compiler ko code samajhne mein madad karta hai.

---

**Line 1: `#ifndef AST_H`**

- **Hinglish:** Yeh ek "include guard" hai. Iska matlab hai ki agar `AST_H` pehle se define nahi hua hai, tabhi neeche ka code include hoga. Isse multiple inclusion ki problem nahi hoti.
- **English:** This is an "include guard". It means if `AST_H` hasn't been defined before, then include the code below. This prevents multiple inclusion problems.

**Line 2: `#define AST_H`**

- **Hinglish:** Yahan `AST_H` ko define kiya ja raha hai. Ab agar yeh file dobara include hogi, toh line 1 ki condition false ho jayegi.
- **English:** Here `AST_H` is being defined. Now if this file is included again, the condition on line 1 will be false.

**Line 4: `#include <memory>`**

- **Hinglish:** Yeh C++ standard library se `memory` header ko include kar raha hai. Ismein `unique_ptr` jaise memory management tools hote hain.
- **English:** This includes the `memory` header from the C++ standard library. It contains memory management tools like `unique_ptr`.

**Line 5: `#include <string>`**

- **Hinglish:** Yeh `string` header ko include kar रहा hai, taaki hum `std::string` (ya `string` agar `using namespace std;` hai) use kar sakein.
- **English:** This includes the `string` header, so we can use `std::string` (or `string` if `using namespace std;` is used).

**Line 6: `#include <vector>`**

- **Hinglish:** Yeh `vector` header ko include kar raha hai, `std::vector` (dynamic arrays) use karne ke liye.
- **English:** This includes the `vector` header to use `std::vector` (dynamic arrays).

**Line 7: `#include <iostream>`**

- **Hinglish:** Yeh `iostream` header include kiya gaya hai `std::cout` (console par output print karne ke liye) use karne ke liye, jo `print()` methods mein kaam aayega.
- **English:** This `iostream` header is included to use `std::cout` (for printing output to the console), which will be used in the `print()` methods.

**Line 9: `using namespace std;`**

- **Hinglish:** Is line ka matlab hai ki hum `std::` prefix ke bina standard library ki cheezein (jaise `string`, `vector`, `cout`) directly use kar sakte hain.
- **English:** This line means we can use things from the standard library (like `string`, `vector`, `cout`) directly without the `std::` prefix.

**Line 11: `// Base class for all expression nodes.`**

- **Hinglish:** Yeh ek comment hai, jo bata raha hai ki neeche `ExprAST` class define ho rahi hai, jo sabhi expression nodes ki base class (parent class) hogi.
- **English:** This is a comment, indicating that the `ExprAST` class is defined below, which will be the base class (parent class) for all expression nodes.

**Line 12: `class ExprAST`**

- **Hinglish:** Yahan `ExprAST` naam ki class shuru ho rahi hai.
- **English:** The class named `ExprAST` starts here.

**Line 14: `public:`**

- **Hinglish:** Iske neeche define hone wale members (functions, variables) class ke bahar se access kiye ja sakte hain.
- **English:** Members (functions, variables) defined below this can be accessed from outside the class.

**Line 15: `virtual ~ExprAST() = default;`**

- **Hinglish:** Yeh ek virtual destructor hai. `virtual` keyword polymorphism ke liye zaroori hai, taaki derived class ke objects jab base class pointer ke through delete hon, toh derived class ka destructor bhi call ho. `= default` ka matlab hai compiler default destructor generate karega.
- **English:** This is a virtual destructor. The `virtual` keyword is necessary for polymorphism, so that when derived class objects are deleted through a base class pointer, the derived class's destructor is also called. `= default` means the compiler will generate the default destructor.

**Line 16: `virtual void print() const = 0;`**

- **Hinglish:** Yeh ek "pure virtual function" hai. `virtual` matlab derived classes isko override kar sakti hain. `void print() const` ka matlab hai yeh function kuch return nahi karta, object ko modify nahi karta (`const`), aur iska naam `print` hai. `= 0` ka matlab hai yeh pure virtual hai, yaani `ExprAST` class abstract ban gayi hai aur iska object nahi banaya ja sakta. Derived classes ko yeh function zaroor implement karna hoga. AST node ko print karne ke liye use hoga.
- **English:** This is a "pure virtual function". `virtual` means derived classes can override it. `void print() const` means this function returns nothing, doesn't modify the object (`const`), and its name is `print`. `= 0` means it's pure virtual, i.e., the `ExprAST` class has become abstract and its object cannot be created. Derived classes must implement this function. It will be used to print the AST node.

**Line 17: `};`**

- **Hinglish:** `ExprAST` class ki definition yahan khatm hoti hai.
- **English:** The definition of the `ExprAST` class ends here.

**Line 19: `// Expression class for numeric literals like "1.0".`**

- **Hinglish:** Comment: Yeh class numeric literals (jaise 1.0, 42) ke liye hai.
- **English:** Comment: This class is for numeric literals (like 1.0, 42).

**Line 20: `class NumberExprAST : public ExprAST`**

- **Hinglish:** `NumberExprAST` class define ho rahi hai, jo `ExprAST` se inherit kar rahi hai (yaani `ExprAST` iski parent class hai).
- **English:** The `NumberExprAST` class is being defined, which inherits from `ExprAST` (i.e., `ExprAST` is its parent class).

**Line 22: `double Val;`**

- **Hinglish:** Is class ka private member variable, jo number ki value store karega (double precision floating point).
- **English:** A private member variable of this class, which will store the value of the number (double precision floating point).

**Line 24: `public:`**

- **Hinglish:** Public members shuru.
- **English:** Public members begin.

**Line 25: `NumberExprAST(double Val) : Val(Val) {}`**

- **Hinglish:** Yeh constructor hai. Jab `NumberExprAST` ka object banega, toh yeh ek `double` value lega aur usko class ke `Val` member mein store kar dega. `: Val(Val)` member initializer list hai.
- **English:** This is the constructor. When a `NumberExprAST` object is created, it will take a `double` value and store it in the class's `Val` member. `: Val(Val)` is a member initializer list.

**Line 26: `void print() const override { std::cout << Val; }`**

- **Hinglish:** Yeh `ExprAST` class ke `print()` function ko override kar raha hai. Yeh number ki value (`Val`) ko console par print karega. `std::cout` use kiya gaya hai, `using namespace std;` ke bawajood specific rehne ke liye ya purane code se.
- **English:** This overrides the `print()` function from the `ExprAST` class. It will print the number's value (`Val`) to the console. `std::cout` is used, possibly to be specific despite `using namespace std;` or from older code.

**Line 27: `};`**

- **Hinglish:** `NumberExprAST` class khatm.
- **English:** `NumberExprAST` class ends.

**Line 29: `// Expression class for referencing a variable, like "a".`**

- **Hinglish:** Comment: Yeh class variable ko reference karne ke liye hai (jaise 'a').
- **English:** Comment: This class is for referencing a variable (like 'a').

**Line 30: `class VariableExprAST : public ExprAST`**

- **Hinglish:** `VariableExprAST` class, `ExprAST` se inherit kar rahi hai.
- **English:** `VariableExprAST` class, inheriting from `ExprAST`.

**Line 32: `string Name;`**

- **Hinglish:** Private member variable, variable ka naam store karne ke liye. `string` (ya `std::string`) use hoga.
- **English:** Private member variable, for storing the variable's name. `string` (or `std::string`) will be used.

**Line 34: `public:`**

- **Hinglish:** Public members.
- **English:** Public members.

**Line 35: `VariableExprAST(const string &Name) : Name(Name) {}`**

- **Hinglish:** Constructor, jo variable ka naam lega aur `Name` member mein store karega. `const string &Name` ka matlab hai yeh string ka reference lega aur usko modify nahi karega.
- **English:** Constructor, which will take the variable's name and store it in the `Name` member. `const string &Name` means it takes a reference to the string and won't modify it.

**Line 36: `void print() const override { std::cout << Name; }`**

- **Hinglish:** `print()` function override. Yeh variable ka naam (`Name`) print karega.
- **English:** `print()` function override. This will print the variable's name (`Name`).

**Line 37: `};`**

- **Hinglish:** `VariableExprAST` class khatm.
- **English:** `VariableExprAST` class ends.

**Line 39: `// Expression class for a binary operator.`**

- **Hinglish:** Comment: Yeh class binary operators (jaise +, -, \*) ke liye hai.
- **English:** Comment: This class is for binary operators (like +, -, \*).

**Line 40: `class BinaryExprAST : public ExprAST`**

- **Hinglish:** `BinaryExprAST` class, `ExprAST` se inherit kar rahi hai.
- **English:** `BinaryExprAST` class, inheriting from `ExprAST`.

**Line 42: `char Op;`**

- **Hinglish:** Operator ka character store karega (jaise '+').
- **English:** Will store the operator's character (like '+').

**Line 43: `unique_ptr<ExprAST> LHS, RHS;`**

- **Hinglish:** Do `unique_ptr` hain. `LHS` (Left Hand Side) aur `RHS` (Right Hand Side) expressions ko point karenge. `unique_ptr` memory ko automatically manage karta hai.
- **English:** Two `unique_ptr`s. `LHS` (Left Hand Side) and `RHS` (Right Hand Side) will point to expressions. `unique_ptr` manages memory automatically.

**Line 45: `public:`**

- **Hinglish:** Public members.
- **English:** Public members.

**Line 46-48: `BinaryExprAST(...) : Op(op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}`**

- **Hinglish:** Constructor. Yeh operator (`op`), left expression (`LHS`), aur right expression (`RHS`) lega. `std::move` use kiya gaya hai `unique_ptr` ki ownership transfer karne ke liye, performance behtar karne ke liye.
- **English:** Constructor. It will take the operator (`op`), left expression (`LHS`), and right expression (`RHS`). `std::move` is used to transfer ownership of `unique_ptr`, improving performance.

**Line 49-55: `void print() const override { ... }`**

- **Hinglish:** `print()` function override. Yeh binary expression ko parentheses ke saath print karega, jaise `(LHS Op RHS)`. Pehle `(`, phir LHS, phir operator, phir RHS, aur aakhir mein `)`. Recursively LHS aur RHS ke `print()` ko call karega.
- **English:** `print()` function override. This will print the binary expression with parentheses, like `(LHS Op RHS)`. First `(`, then LHS, then operator, then RHS, and finally `)`. It will recursively call `print()` for LHS and RHS.

**Line 56: `};`**

- **Hinglish:** `BinaryExprAST` class khatm.
- **English:** `BinaryExprAST` class ends.

**Line 58: `// Expression class for function calls.`**

- **Hinglish:** Comment: Yeh class function calls ke liye hai.
- **English:** Comment: This class is for function calls.

**Line 59: `class CallExprAST : public ExprAST`**

- **Hinglish:** `CallExprAST` class, `ExprAST` se inherit kar rahi hai.
- **English:** `CallExprAST` class, inheriting from `ExprAST`.

**Line 61: `string Callee;`**

- **Hinglish:** Function ka naam (jise call kiya ja raha hai) store karega.
- **English:** Will store the name of the function being called (the callee).

**Line 62: `vector<unique_ptr<ExprAST>> Args;`**

- **Hinglish:** Function arguments ki list (vector) store karega. Har argument ek expression (`ExprAST`) ho sakta hai, isliye `unique_ptr<ExprAST>`.
- **English:** Will store a list (vector) of function arguments. Each argument can be an expression (`ExprAST`), hence `unique_ptr<ExprAST>`.

**Line 64: `public:`**

- **Hinglish:** Public members.
- **English:** Public members.

**Line 65-67: `CallExprAST(...) : Callee(Callee), Args(std::move(Args)) {}`**

- **Hinglish:** Constructor. Function ka naam (`Callee`) aur arguments ki vector (`Args`) lega. `std::move` yahan `Args` vector ke liye use hua hai.
- **English:** Constructor. Takes the function name (`Callee`) and a vector of arguments (`Args`). `std::move` is used here for the `Args` vector.

**Line 68-76: `void print() const override { ... }`**

- **Hinglish:** `print()` function override. Function call ko print karega, jaise `Callee(Arg1, Arg2, ...)`. Arguments ke beech comma lagayega.
- **English:** `print()` function override. Will print the function call, like `Callee(Arg1, Arg2, ...)`. It will put commas between arguments.

**Line 77: `};`**

- **Hinglish:** `CallExprAST` class khatm.
- **English:** `CallExprAST` class ends.

**Line 79-81: `// This class represents the "prototype" for a function...`**

- **Hinglish:** Comment: Yeh class function prototype (declaration) ke liye hai. Ismein function ka naam aur uske arguments ke naam hote hain.
- **English:** Comment: This class is for a function prototype (declaration). It contains the function's name and its argument names.

**Line 82: `class PrototypeAST : public ExprAST`**

- **Hinglish:** `PrototypeAST` class, `ExprAST` se inherit kar rahi hai (yeh isliye taaki `extern` ko top-level statement ki tarah parse kiya ja sake aur AST mein represent kiya ja sake, even though yeh technically expression nahi hai).
- **English:** `PrototypeAST` class, inheriting from `ExprAST` (this is so that `extern` can be parsed as a top-level statement and represented in the AST, even though it's not technically an expression).

**Line 84: `string Name;`**

- **Hinglish:** Function ka naam.
- **English:** Function's name.

**Line 85: `vector<string> Args;`**

- **Hinglish:** Function ke arguments ke naamo ki list.
- **English:** List of function argument names.

**Line 86: `bool IsOperator;`**

- **Hinglish:** Kya yeh prototype ek operator ke liye hai (jaise binary '+').
- **English:** Is this prototype for an operator (like binary '+').

**Line 87: `unsigned Precedence;`**

- **Hinglish:** Agar operator hai, toh uski precedence (priority).
- **English:** If it's an operator, its precedence (priority).

**Line 89: `public:`**

- **Hinglish:** Public members.
- **English:** Public members.

**Line 90-91: `PrototypeAST(...) : Name(name), Args(std::move(Args)), ... {}`**

- **Hinglish:** Constructor. Function ka naam, arguments, kya yeh operator hai, aur uski precedence lega. `IsOperator` aur `Precedence` ke default values hain.
- **English:** Constructor. Takes the function name, arguments, whether it's an operator, and its precedence. `IsOperator` and `Precedence` have default values.

**Line 92-100: `void print() const override { ... }`**

- **Hinglish:** `print()` function override. Function prototype ko print karega, jaise `def Name(Arg1, Arg2, ...)`. (Note: Yahan `def` print ho raha hai, jo shayad `extern` ke case mein zyada appropriate hoga agar yeh sirf externs ke liye hai. Agar definitions ke liye bhi hai, tab theek hai.)
- **English:** `print()` function override. Will print the function prototype, like `def Name(Arg1, Arg2, ...)`. (Note: It prints `def` here, which might be more appropriate for `extern` if this is only for externs. If it's also for definitions, then it's fine.)

**Line 101: `};`**

- **Hinglish:** `PrototypeAST` class khatm.
- **English:** `PrototypeAST` class ends.

**Line 103: `// This class represents a function definition itself.`**

- **Hinglish:** Comment: Yeh class function definition ke liye hai (prototype + body).
- **English:** Comment: This class is for a function definition (prototype + body).

**Line 104: `class FunctionAST : public ExprAST`**

- **Hinglish:** `FunctionAST` class, `ExprAST` se inherit kar rahi hai.
- **English:** `FunctionAST` class, inheriting from `ExprAST`.

**Line 106: `unique_ptr<PrototypeAST> Proto;`**

- **Hinglish:** Function ka prototype (jo upar define kiya hai).
- **English:** The function's prototype (defined above).

**Line 107: `unique_ptr<ExprAST> Body;`**

- **Hinglish:** Function ka body (jo ek expression hoga).
- **English:** The function's body (which will be an expression).

**Line 109: `public:`**

- **Hinglish:** Public members.
- **English:** Public members.

**Line 110-112: `FunctionAST(...) : Proto(std::move(Proto)), Body(std::move(Body)) {}`**

- **Hinglish:** Constructor. Function ka prototype aur body lega.
- **English:** Constructor. Takes the function's prototype and body.

**Line 113-117: `void print() const override { ... }`**

- **Hinglish:** `print()` function override. Pehle prototype ko print karega, phir ek space, aur phir body ko print karega.
- **English:** `print()` function override. Will first print the prototype, then a space, and then print the body.

**Line 118: `};`**

- **Hinglish:** `FunctionAST` class khatm.
- **English:** `FunctionAST` class ends.

**Line 120: `#endif // AST_H`**

- **Hinglish:** Include guard ko yahan khatm kiya ja raha hai.
- **English:** The include guard is ended here.

---
