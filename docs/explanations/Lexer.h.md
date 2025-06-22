## `src/Lexer.h` - Line by Line Hinglish Explanation

Yeh file `Lexer` class ka header file hai. Lexer ka kaam hota hai source code (text) ko chote-chote pieces mein todna jinhe "tokens" kehte hain. Tokens compiler ke liye code ko samajhne ka pehla step hota hai.

---

**Line 1: `#ifndef LEXER_H`**

- **Hinglish:** Include guard shuru. Agar `LEXER_H` define nahi hai, toh aage badho.
- **English:** Include guard starts. If `LEXER_H` is not defined, proceed.

**Line 2: `#define LEXER_H`**

- **Hinglish:** `LEXER_H` ko define karo, taaki yeh file dobara include na ho.
- **English:** Define `LEXER_H` so this file isn't included again.

**Line 4: `#include <string>`**

- **Hinglish:** `std::string` (text ke liye) use karne ke liye `string` header include karo.
- **English:** Include the `string` header to use `std::string` (for text).

**Line 5: `#include <vector>`**

- **Hinglish:** `std::vector` (dynamic array, yahan tokens ki list store karne ke liye) use karne ke liye `vector` header include karo.
- **English:** Include the `vector` header to use `std::vector` (dynamic array, here for storing a list of tokens).

**Line 7: `class Lexer`**

- **Hinglish:** `Lexer` naam ki class ki definition shuru ho rahi hai.
- **English:** The definition of the class named `Lexer` begins.

**Line 9: `public:`**

- **Hinglish:** Iske neeche public members hain, jo class ke bahar se access kiye ja sakte hain.
- **English:** Below this are public members, which can be accessed from outside the class.

**Line 10: `Lexer(const std::string &source);`**

- **Hinglish:** Yeh `Lexer` class ka constructor hai. Yeh ek `const std::string` reference (`source`) lega, jo hamara input source code hoga. `const` matlab yeh source code ko modify nahi karega.
- **English:** This is the constructor for the `Lexer` class. It takes a `const std::string` reference (`source`), which will be our input source code. `const` means it won't modify the source code.

**Line 11: `std::vector<std::string> tokenize();`**

- **Hinglish:** Yeh ek public function hai `tokenize` naam ka. Jab yeh call hoga, toh yeh source code ko process karega aur `std::string`s ka ek `std::vector` return karega, jismein har string ek token hoga.
- **English:** This is a public function named `tokenize`. When called, it will process the source code and return a `std::vector` of `std::string`s, where each string is a token.

**Line 13: `private:`**

- **Hinglish:** Iske neeche private members hain, jo sirf `Lexer` class ke andar se hi access kiye ja sakte hain.
- **English:** Below this are private members, which can only be accessed from within the `Lexer` class.

**Line 14: `std::string source_;`**

- **Hinglish:** Yeh variable original source code ko store karega.
- **English:** This variable will store the original source code.

**Line 15: `size_t current_pos_;`**

- **Hinglish:** Yeh variable source code mein current position (index) ko track karega, yaani abhi hum konsa character पढ़ rahe hain.
- **English:** This variable will track the current position (index) in the source code, i.e., which character we are currently reading.

**Line 16: `char current_char_;`**

- **Hinglish:** Yeh variable `current_pos_` par jo character hai, usko store karega.
- **English:** This variable will store the character at `current_pos_`.

**Line 18: `void advance();`**

- **Hinglish:** Yeh ek private helper function hai. Iska kaam hoga `current_pos_` ko ek step aage badhana aur `current_char_` ko update karna.
- **English:** This is a private helper function. Its job will be to advance `current_pos_` one step and update `current_char_`.

**Line 19: `void skipWhitespace();`**

- **Hinglish:** Yeh function source code mein se whitespace characters (jaise space, tab, newline) ko skip karne ke liye hai.
- **English:** This function is for skipping whitespace characters (like space, tab, newline) in the source code.

**Line 20: `void skipComment();`**

- **Hinglish:** Yeh function comments ko skip karega (Kaleidoscope mein comments `#` se shuru hote hain).
- **English:** This function will skip comments (in Kaleidoscope, comments start with `#`).

**Line 21: `std::string getIdentifier();`**

- **Hinglish:** Yeh function ek identifier (jaise variable ka naam ya function ka naam) ko source code se extract karega.
- **English:** This function will extract an identifier (like a variable name or function name) from the source code.

**Line 22: `std::string getNumber();`**

- **Hinglish:** Yeh function ek number (integer ya decimal) ko source code se extract karega.
- **English:** This function will extract a number (integer or decimal) from the source code.

**Line 23: `};`**

- **Hinglish:** `Lexer` class ki definition yahan khatm hoti hai.
- **English:** The definition of the `Lexer` class ends here.

**Line 25: `#endif // LEXER_H`**

- **Hinglish:** Include guard yahan khatm hota hai.
- **English:** The include guard ends here.

---
