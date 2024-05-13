# Any

## Description
模仿标准库的`any`类，实现一个`Any`类，支持存储任意类型的数据。


## usage
```cpp
#include "Any.h"

#include <iostream>
#include <string>
#include <vector>

int main() {
  using ccutil::Any;
  std::vector<Any> v = {1, 2.5, std::string("Hello")};
  std::cout << v << std::endl;

  std::vector<Any> v2 = {std::string("Hello"), 2.5, 1};
  v.push_back(v2);

  std::cout << v << std::endl;
  return 0;
}
```