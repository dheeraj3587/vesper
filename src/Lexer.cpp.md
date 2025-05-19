## `src/Lexer.cpp` - Line by Line Hinglish Explanation

Yeh file `Lexer` class ke member functions ki implementation (definitions) provide karti hai. `Lexer.h` mein humne sirf declare kiya tha, yahan unka actual code hai.

---

**Line 1: `#include "Lexer.h"`**

- **Hinglish:** `Lexer.h` header file ko include karo. Ismein `Lexer` class ka declaration hai, jiske functions hum yahan define kar rahe hain.
- **English:** Include the `Lexer.h` header file. It contains the declaration of the `Lexer` class, whose functions we are defining here.

**Line 2: `#include <cctype>`**

- **Hinglish:** `cctype` header ko include karo. Ismein character type check karne wale functions hote hain, jaise `std::isspace`, `std::isalnum`, `std::isdigit`, `std::isalpha`.
- **English:** Include the `cctype` header. It contains functions for checking character types, like `std::isspace`, `std::isalnum`, `std::isdigit`, `std::isalpha`.

**Line 3: `#include <stdexcept>`**

- **Hinglish:** `stdexcept` header ko include karo. Ismein standard exception classes hoti hain, jaise `std::runtime_error`, jo hum unknown character milne par throw karenge.
- **English:** Include the `stdexcept` header. It contains standard exception classes like `std::runtime_error`, which we will throw if an unknown character is found.

**Line 5: `Lexer::Lexer(const std::string &source)`**

- **Hinglish:** Yeh `Lexer` class ke constructor ki definition hai. `Lexer::` batata hai ki yeh `Lexer` class ka member hai.
- **English:** This is the definition of the `Lexer` class's constructor. `Lexer::` indicates that it's a member of the `Lexer` class.

**Line 6: `: source_(source), current_pos_(0), current_char_(source.empty() ? '\0' : source_[0]) {}`**

- **Hinglish:** Yeh member initializer list hai. `source_` member ko input `source` se initialize karo. `current_pos_` ko `0` (shuruwat) se initialize karo. `current_char_` ko pehle character se initialize karo, lekin agar `source` empty hai toh `'\0'` (null character, jo End-Of-File ya EOF jaisa kaam karta hai) se initialize karo. `{}` empty body hai constructor ka.
- **English:** This is the member initializer list. Initialize the `source_` member with the input `source`. Initialize `current_pos_` to `0` (beginning). Initialize `current_char_` with the first character, but if `source` is empty, initialize it with `'\0'` (null character, which acts like End-Of-File or EOF). `{}` is the empty body of the constructor.

**Line 8: `void Lexer::advance()`**

- **Hinglish:** `advance` function ki definition. Iska kaam hai lexer ko source code mein ek character aage badhana.
- **English:** Definition of the `advance` function. Its job is to move the lexer one character forward in the source code.

**Line 10: `current_pos_++;`**

- **Hinglish:** `current_pos_` ko ek se badhao (increment karo).
- **English:** Increment `current_pos_` by one.

**Line 11: `if (current_pos_ >= source_.length())`**

- **Hinglish:** Check karo ki kya hum source code ke end tak pahunch gaye hain.
- **English:** Check if we have reached the end of the source code.

**Line 13: `current_char_ = '\0'; // EOF`**

- **Hinglish:** Agar end tak pahunch gaye, toh `current_char_` ko `'\0'` (EOF) set karo.
- **English:** If we reached the end, set `current_char_` to `'\0'` (EOF).

**Line 15: `else`**

- **Hinglish:** Nahi toh (agar end tak nahi pahuche).
- **English:** Otherwise (if we haven't reached the end).

**Line 17: `current_char_ = source_[current_pos_];`**

- **Hinglish:** `current_char_` ko source code mein nayi `current_pos_` wale character se update karo.
- **English:** Update `current_char_` with the character at the new `current_pos_` in the source code.

**Line 19: `}`**

- **Hinglish:** `advance` function khatm.
- **English:** `advance` function ends.

**Line 21: `void Lexer::skipWhitespace()`**

- **Hinglish:** `skipWhitespace` function ki definition. Yeh whitespace characters ko ignore karega.
- **English:** Definition of the `skipWhitespace` function. It will ignore whitespace characters.

**Line 23: `while (current_char_ != '\0' && std::isspace(current_char_))`**

- **Hinglish:** Jab tak `current_char_` EOF nahi hai AUR `current_char_` ek whitespace character hai (`std::isspace` se check kiya), tab tak loop chalao.
- **English:** Run the loop as long as `current_char_` is not EOF AND `current_char_` is a whitespace character (checked with `std::isspace`).

**Line 25: `advance();`**

- **Hinglish:** Agle character par jao.
- **English:** Go to the next character.

**Line 27: `}`**

- **Hinglish:** `while` loop khatm.
- **English:** `while` loop ends.

**Line 28: `}`**

- **Hinglish:** `skipWhitespace` function khatm.
- **English:** `skipWhitespace` function ends.

**Line 30: `void Lexer::skipComment()`**

- **Hinglish:** `skipComment` function ki definition. Yeh comments ko ignore karega.
- **English:** Definition of the `skipComment` function. It will ignore comments.

**Line 32: `if (current_char_ == '#')`**

- **Hinglish:** Agar `current_char_` hash (`#`) hai (comment shuru hota hai), toh...
- **English:** If `current_char_` is hash (`#`) (a comment starts), then...

**Line 34: `while (current_char_ != '\0' && current_char_ != '\n' && current_char_ != '\r')`**

- **Hinglish:** Jab tak `current_char_` EOF nahi hai AUR newline (`\n`) nahi hai AUR carriage return (`\r`) nahi hai, tab tak comment ke characters ko skip karo.
- **English:** Skip comment characters as long as `current_char_` is not EOF AND not newline (`\n`) AND not carriage return (`\r`).

**Line 36: `advance();`**

- **Hinglish:** Agle character par jao.
- **English:** Go to the next character.

**Line 38: `}`**

- **Hinglish:** Inner `while` loop khatm.
- **English:** Inner `while` loop ends.

**Line 40-47: `// Also consume the newline character(s) after the comment ...`**

- **Hinglish:** Comment ke baad aane wale newline character(s) ko bhi consume (skip) karo. Windows mein newline `\r\n` hota hai, Unix/Mac mein `\n`. Isliye dono cases handle kiye hain.
- **English:** Also consume (skip) the newline character(s) after the comment. In Windows, newline is `\r\n`, in Unix/Mac it's `\n`. So both cases are handled.

**Line 48: `}`**

- **Hinglish:** `if` condition (comment check) khatm.
- **English:** `if` condition (comment check) ends.

**Line 49: `}`**

- **Hinglish:** `skipComment` function khatm.
- **English:** `skipComment` function ends.

**Line 51: `std::string Lexer::getIdentifier()`**

- **Hinglish:** `getIdentifier` function ki definition. Yeh ek identifier (variable/function naam) ko padhega.
- **English:** Definition of the `getIdentifier` function. It will read an identifier (variable/function name).

**Line 53: `std::string result = "";`**

- **Hinglish:** Ek empty string `result` banayi, jismein identifier store hoga.
- **English:** An empty string `result` is created, where the identifier will be stored.

**Line 54: `while (current_char_ != '\0' && (std::isalnum(current_char_) || current_char_ == '_'))`**

- **Hinglish:** Jab tak `current_char_` EOF nahi hai AUR woh alphanumeric (`std::isalnum`) hai YA underscore (`_`) hai, tab tak loop chalao.
- **English:** Run the loop as long as `current_char_` is not EOF AND it is alphanumeric (`std::isalnum`) OR it is an underscore (`_`).

**Line 56: `result += current_char_;`**

- **Hinglish:** `current_char_` ko `result` string mein jod do.
- **English:** Append `current_char_` to the `result` string.

**Line 57: `advance();`**

- **Hinglish:** Agle character par jao.
- **English:** Go to the next character.

**Line 59: `}`**

- **Hinglish:** `while` loop khatm.
- **English:** `while` loop ends.

**Line 60: `return result;`**

- **Hinglish:** Padha hua identifier return karo.
- **English:** Return the read identifier.

**Line 61: `}`**

- **Hinglish:** `getIdentifier` function khatm.
- **English:** `getIdentifier` function ends.

**Line 63: `std::string Lexer::getNumber()`**

- **Hinglish:** `getNumber` function ki definition. Yeh ek number (integer ya decimal) ko padhega.
- **English:** Definition of the `getNumber` function. It will read a number (integer or decimal).

**Line 65: `std::string result = "";`**

- **Hinglish:** Number ko string form mein store karne ke liye empty `result` string.
- **English:** Empty `result` string to store the number in string form.

**Line 66: `bool has_decimal = false;`**

- **Hinglish:** Ek flag yeh track karne ke liye ki number mein decimal point (`.`) aa chuka hai ya nahi.
- **English:** A flag to track whether a decimal point (`.`) has already appeared in the number.

**Line 67: `while (current_char_ != '\0' && (std::isdigit(current_char_) || current_char_ == '.'))`**

- **Hinglish:** Jab tak `current_char_` EOF nahi hai AUR woh digit (`std::isdigit`) hai YA decimal point (`.`) hai, tab tak loop chalao.
- **English:** Run the loop as long as `current_char_` is not EOF AND it is a digit (`std::isdigit`) OR it is a decimal point (`.`).

**Line 69: `if (current_char_ == '.')`**

- **Hinglish:** Agar `current_char_` decimal point hai...
- **English:** If `current_char_` is a decimal point...

**Line 71: `if (has_decimal) break; // Cannot have more than one decimal point`**

- **Hinglish:** Agar `has_decimal` pehle se true hai (yaani ek decimal point aa chuka hai), toh loop tod do. Ek number mein ek se zyada decimal point nahi ho sakte.
- **English:** If `has_decimal` is already true (meaning one decimal point has already appeared), then break the loop. A number cannot have more than one decimal point.

**Line 72: `has_decimal = true;`**

- **Hinglish:** `has_decimal` ko true set karo, kyunki ab decimal point mil gaya hai.
- **English:** Set `has_decimal` to true, because a decimal point has now been found.

**Line 74: `}`**

- **Hinglish:** `if` (decimal check) khatm.
- **English:** `if` (decimal check) ends.

**Line 75: `result += current_char_;`**

- **Hinglish:** `current_char_` ko `result` mein jod do.
- **English:** Append `current_char_` to `result`.

**Line 76: `advance();`**

- **Hinglish:** Agle character par jao.
- **English:** Go to the next character.

**Line 78: `}`**

- **Hinglish:** `while` loop khatm.
- **English:** `while` loop ends.

**Line 79: `return result;`**

- **Hinglish:** Padha hua number (string form mein) return karo.
- **English:** Return the read number (in string form).

**Line 80: `}`**

- **Hinglish:** `getNumber` function khatm.
- **English:** `getNumber` function ends.

**Line 82: `std::vector<std::string> Lexer::tokenize()`**

- **Hinglish:** `tokenize` function ki definition. Yeh main function hai jo source code ko tokens mein convert karta hai.
- **English:** Definition of the `tokenize` function. This is the main function that converts source code into tokens.

**Line 84: `std::vector<std::string> tokens;`**

- **Hinglish:** Ek empty vector `tokens` banaya, jismein saare tokens store honge.
- **English:** An empty vector `tokens` is created, where all the tokens will be stored.

**Line 86: `while (current_char_ != '\0')`**

- **Hinglish:** Jab tak `current_char_` EOF nahi hai (yaani source code khatm nahi hua), tab tak loop chalao.
- **English:** Run the loop as long as `current_char_` is not EOF (i.e., the source code hasn't ended).

**Line 88: `if (std::isspace(current_char_))`**

- **Hinglish:** Agar `current_char_` whitespace hai...
- **English:** If `current_char_` is whitespace...

**Line 90: `skipWhitespace();`**

- **Hinglish:** Whitespace ko skip karo.
- **English:** Skip the whitespace.

**Line 91: `continue;`**

- **Hinglish:** Loop ki agli iteration par jao (current character process ho gaya).
- **English:** Go to the next iteration of the loop (the current character has been processed).

**Line 94: `if (current_char_ == '#')`**

- **Hinglish:** Agar `current_char_` hash (`#`) hai (comment)...
- **English:** If `current_char_` is hash (`#`) (comment)...

**Line 96: `skipComment();`**

- **Hinglish:** Comment ko skip karo.
- **English:** Skip the comment.

**Line 97: `continue;`**

- **Hinglish:** Loop ki agli iteration par jao.
- **English:** Go to the next iteration of the loop.

**Line 100: `if (std::isalpha(current_char_) || current_char_ == '_')`**

- **Hinglish:** Agar `current_char_` ek alphabet (`std::isalpha`) hai YA underscore (`_`) hai (identifier ki shuruwat)...
- **English:** If `current_char_` is an alphabet (`std::isalpha`) OR an underscore (`_`) (start of an identifier)...

**Line 102: `tokens.push_back(getIdentifier());`**

- **Hinglish:** `getIdentifier()` call karke identifier padho aur usko `tokens` vector mein add karo.
- **English:** Call `getIdentifier()` to read the identifier and add it to the `tokens` vector.

**Line 103: `continue;`**

- **Hinglish:** Loop ki agli iteration par jao.
- **English:** Go to the next iteration of the loop.

**Line 106: `if (std::isdigit(current_char_) || current_char_ == '.')`**

- **Hinglish:** Agar `current_char_` digit (`std::isdigit`) hai YA decimal point (`.`) hai (number ki shuruwat)...
- **English:** If `current_char_` is a digit (`std::isdigit`) OR a decimal point (`.`) (start of a number)...

**Line 108-114: `// Check if it's just a dot (operator) or start of a number ... else { tokens.push_back(getNumber()); continue; }`**

- **Hinglish:** Yahan check kiya ja raha hai ki kya `.` sirf ek operator hai ya number ka part hai. Agar `.` ke baad digit nahi hai, toh yeh ek operator ho sakta hai (jo abhi handle nahi kiya ja raha, isliye `if` block empty hai). Nahi toh, `getNumber()` call karke number padho aur `tokens` mein add karo.
- **English:** Here it checks if `.` is just an operator or part of a number. If there's no digit after `.`, it might be an operator (which is not currently handled, so the `if` block is empty). Otherwise, call `getNumber()` to read the number and add it to `tokens`.

**Line 117-123: `// Handle operators and parentheses ... tokens.push_back(std::string(1, current_char_)); advance(); continue;`**

- **Hinglish:** Operators `( ) + - * / < > , ;` ko handle karo. Yeh sab single character tokens hain. `current_char_` se ek character ki string banakar `tokens` mein add karo, phir `advance()` karo.
- **English:** Handle operators `( ) + - * / < > , ;`. These are all single character tokens. Create a single-character string from `current_char_`, add it to `tokens`, then call `advance()`.

**Line 126-127: `// If we reach here, it's an unknown character ... throw std::runtime_error(...)`**

- **Hinglish:** Agar upar ki koi bhi condition match nahi hui, toh iska matlab `current_char_` ek unknown character hai. Ek `std::runtime_error` throw karo (program ko error ke saath band karo) jismein unknown character aur uski position ki information ho.
- **English:** If none of the above conditions matched, it means `current_char_` is an unknown character. Throw a `std::runtime_error` (stop the program with an error) containing information about the unknown character and its position.

**Line 129: `}`**

- **Hinglish:** Main `while` loop (jo poore source code ko process kar raha tha) khatm.
- **English:** The main `while` loop (which was processing the entire source code) ends.

**Line 131: `return tokens;`**

- **Hinglish:** Tokens ka vector return karo.
- **English:** Return the vector of tokens.

**Line 132: `}`**

- **Hinglish:** `tokenize` function khatm.
- **English:** `tokenize` function ends.

---
