# lifestr
A C++ string wrapper with a lifetime counter – print it a limited number of times.

[![C++11](https://img.shields.io/badge/C%2B%2B-11-blue)](https://en.cppreference.com/w/cpp/11)
[![Code Size](https://img.shields.io/github/languages/code-size/0xA672/lifestr)](https://github.com/0xA672/lifestr)

## Lience
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

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

## More Examples：
### Reviving a Depleted String with addlife()
```cpp
lifestr msg("I'll be back", 1);
msg.print();            // life becomes 0
msg.print();            // no output

msg.addlife(2);         // revive with +2 life
msg.print();            // outputs again
```
### Safe Life Reduction with reducelife()
```cpp
lifestr note("Important", 3);
note.reducelife(10);    // life becomes 0, no exception thrown
std::cout << "Life after reduction: " << note.getlife() << '\n'; // 0
```
### Consuming Life Manually
```cpp
lifestr token("One-time token", 1);
if (token.consume()) {
    std::cout << "Token used: " << token.getstring() << '\n';
} else {
    std::cout << "Token already used.\n";
}
```
### Exhausting Life Immediately
```cpp
lifestr msg("I give up", 5);
msg.exhaust();
if (!msg.isalive()) {
    std::cout << "Life exhausted.\n";
}
```
### Progress Bar with lifepercentage()
```cpp
lifestr hp("Player", 30);
int maxHp = 100;
double percent = hp.lifepercentage(maxHp);
std::cout << "HP: " << hp.getlife() << "/" << maxHp 
          << " (" << percent << "%)\n";

// Simulate a visual bar
int barWidth = 20;
int filled = static_cast<int>(percent / 100 * barWidth);
std::cout << "[";
for (int i = 0; i < barWidth; ++i) {
    std::cout << (i < filled ? '#' : ' ');
}
std::cout << "]\n";
```
Output:
```rust
HP: 30/100 (30.0%)
[######              ]
```
### Using operator<< for Debugging (No Life Consumed)
```cpp
lifestr debug("Debug message", 3);
std::cout << "Current content: " << debug << '\n'; // life remains 3
std::cout << "Remaining life: " << debug.getlife() << '\n';
```
### Combining with std::optional for Automatic Cleanup
```cpp
#include <optional>

std::optional<lifestr> optMsg(std::in_place, "Temporary", 2);
while (optMsg->print()) {}

// Life depleted → destroy the object to free memory
if (!optMsg->isalive()) {
    optMsg.reset();
}
```


> [!IMPORTANT]
> Life exhaustion does **not** destroy the object.
> Use `setlife()` to revive it, or let it go out of scope to free memory.


