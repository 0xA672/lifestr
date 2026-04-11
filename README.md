# lifestr
A C++ string wrapper with a lifetime counter – print it a limited number of times.

[![C++11](https://img.shields.io/badge/C%2B%2B-11-blue)](https://en.cppreference.com/w/cpp/11)

```cpp
#include "lifestr.hpp"
```
Example:
```cpp
#include <iostream>
#include "lifestr.hpp"

int main() {
    lifestr msg("Hello, world!", 3);  

    while (msg.print()) {}

    if (!msg.print()) {
        std::cout << "No more prints available.\n";
    }

    return 0;
}
```
Output:
```rust
Hello, world!
Hello, world!
Hello, world!
No more prints available.
```

## API Reference 
### `lifestr()`
Constructs an empty string with life = 0.

### `lifestr(const std::string& s, int l)`
Constructs with a string s and initial life l. Throws std::invalid_argument if l < 0.

### `lifestr(const char* s, int l)`
Constructs with a C-string s and initial life l. If s is nullptr, treats it as empty string. Throws if l < 0.

### `lifestr(const lifestr& other)`
Copy constructor. Copies both string and life value.

### `lifestr(lifestr&& other) noexcept`
Move constructor. Transfers string and life, then sets other.life = 0.

### `lifestr& operator=(const lifestr& other)`
Copy assignment operator. Copies both string and life value from `other`.

### `lifestr& operator=(lifestr&& other) noexcept`
Move assignment operator. Transfers string and life from `other`, then sets `other.life = 0`.

### `bool print()`
Prints the stored string followed by a newline to `std::cout`. If `life > 0`, decrements life by 1 and returns `true`. Otherwise, returns `false` and outputs nothing.

### `bool print(std::ostream& os)`
Prints the stored string followed by a newline to the given output stream `os`. Life decrement behavior is the same as `print()`.

### `const std::string& getstring() const`
Returns a const reference to the underlying `std::string`.

### `const char* cstr() const`
Returns a pointer to a null-terminated C-string representation of the stored string.

### `size_t length() const`
Returns the length of the stored string.

### `bool empty() const`
Returns `true` if the stored string is empty.

### `void setstring(const std::string& s)`
Replaces the stored string with `s`.

### `void setstring(const char* s)`
Replaces the stored string with C-string `s`. If `s` is `nullptr`, the string becomes empty.

### `void setlife(int l)`
Sets the life counter to `l`. Throws `std::invalid_argument` if `l` is negative.

### `int getlife() const`
Returns the current life value.

### `void addlife(int amount)`
Adds `amount` to the current life. Throws `std::invalid_argument` if the resulting life would be negative.

### `void reducelife(int amount = 1)`
Safely subtracts `amount` from life. Life will never drop below 0.

### `void resetlife(int newlife)`
Resets the life counter to `newlife`. Throws `std::invalid_argument` if `newlife` is negative.

### `bool isalive() const`
Returns `true` if life is greater than 0.

### `bool consume()`
Attempts to consume 1 life. If `life > 0`, decrements life and returns `true`; otherwise returns `false`.

### `void exhaust()`
Sets the life counter to 0 immediately.

### `double lifepercentage(int maxlife) const`
Returns the current life as a percentage of `maxlife` (range 0.0 to 100.0). Returns `0.0` if `maxlife <= 0`.

### `~lifestr()`
Default destructor.

### `friend std::ostream& operator<<(std::ostream& os, const lifestr& ls)`
Inserts the stored string into the output stream `os`. **Does not consume life**.

> [!IMPORTANT]
> Life exhaustion does **not** destroy the object.
> Use `setlife()` to revive it, or let it go out of scope to free memory.

## Lience
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
