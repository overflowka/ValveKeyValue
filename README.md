# ValveKeyValue
ValveKeyValue (aka vdf) parser in C++ Finally!

example:
```#include <iostream>
#include <fstream>
#include "KeyValue.h"

std::string readFile(const std::string &fileName) {
  std::ifstream file(fileName);
  std::string content((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());

  return content;
}

int main() {
  KeyValue kv;
  kv.parse(readFile("example.vdf"));
  std::cout << kv.encode() << std::endl;
  
  return 0;
}
