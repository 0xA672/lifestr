#ifndef LIFESTR_HPP
#define LIFESTR_HPP

#include <string>
#include <iostream>
#include <utility>
#include <stdexcept>

struct lifestr {
private: 
  std::string str;
  int life;

public:
  lifestr() : str(), life(0) {}
  
  lifestr(const std::string& s, int l) : str(s){setlife(l);}
  lifestr(const char* s, int l) : str(s ? s : ""){setlife(l);}

  lifestr(const lifestr& other) : str(other.str), life(other.life) {}
  
  lifestr(lifestr&& other) noexcept : str(std::move(other.str)), life(other.life) {
    other.life = 0;
  }
  
  lifestr& operator=(const lifestr& other) {
    if (this != &other) {
      str = other.str;
      life = other.life;
    }
    return *this;
  }
  
  lifestr& operator=(lifestr&& other) noexcept {
    if (this != &other) {
      str = std::move(other.str);
      life = other.life;
      other.life = 0;
    }
    return *this;
  }

  bool print() {
    return print(std::cout);
  }
  
  bool print(std::ostream& os) {
    if (life <= 0) return false;
    os << str << '\n';
    --life;
    return true;
  }

  const std::string& getstring() const { return str; }
  const char* cstr() const { return str.c_str(); }
  size_t length() const { return str.length(); }
  bool empty() const { return str.empty(); }
  
  void setstring(const std::string& s) { str = s; }
  void setstring(const char* s) { 
    if (s) str = s;
    else str.clear();
  }

  void setlife(int l) { 
    if (l < 0) {
      throw std::invalid_argument("Life cannot be negative");
    }
    life = l; 
  }
  
  int getlife() const { return life; }
  
  void addlife(int amount) {
    int newlife = life + amount;
    if (newlife < 0) {
      throw std::invalid_argument("Resulting life cannot be negative");
    }
    life = newlife;
  }
  
  void reducelife(int amount = 1) {
    if (amount > life) {
      life = 0;
    } else {
      life -= amount;
    }
  }
  
  void resetlife(int newlife) {
    if (newlife < 0) {
      throw std::invalid_argument("Life cannot be negative");
    }
    life = newlife;
  }
  
  bool isalive() const { return life > 0; }
  bool alive() const { return isalive(); }
  
  bool consume() {
    if (life <= 0) return false;
    --life;
    return true;
  }
  
  void exhaust() { life = 0; }
  
  double lifepercentage(int maxlife) const {
    if (maxlife <= 0) return 0.0;
    return static_cast<double>(life) / static_cast<double>(maxlife) * 100.0;
  }

  ~lifestr() = default;
  
  friend std::ostream& operator<<(std::ostream& os, const lifestr& ls) {
    os << ls.str;
    return os;
  }
};

#endif // LIFESTR_HPP
