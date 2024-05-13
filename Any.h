#include <iostream>
#include <vector>

namespace ccutil {
class Any {
 public:
  template <typename T>
  Any(const T& t) : base(new Derived<T>(t)) {}
  Any(const Any& other) : base(other.base->clone()) {}
  Any(Any&& other) : base(other.base) { other.base = nullptr; }

  Any& operator=(const Any& other) {
    delete base;
    base = other.base->clone();
    return *this;
  }
  Any& operator=(Any&& other) {
    delete base;
    base = other.base;
    other.base = nullptr;
    return *this;
  }

  struct Base {
    virtual Base* clone() = 0;
    virtual std::ostream& print(std::ostream& os) const = 0;

    virtual ~Base() {}
  };

  template <typename T>
  struct Derived : Base {
    T value;
    Derived(const T& v) : value(v) {}
    Base* clone() override { return new Derived<T>(value); }
    virtual std::ostream& print(std::ostream& os) const override {
      return os << value;
    }
  };

  Base* base;

  template <typename T>
  T get() {
    return static_cast<Derived<T>*>(base)->value;
  }

  virtual ~Any() { delete base; }
};

std::ostream& operator<<(std::ostream& os, const Any& any) {
  return any.base->print(os);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
  os << "[";
  for (size_t i = 0; i < v.size(); ++i) {
    os << v[i];
    if (i != v.size() - 1) {
      os << ", ";
    }
  }
  os << "]";
  return os;
}
}  // namespace ccutil