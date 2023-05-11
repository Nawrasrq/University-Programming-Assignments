#include <iostream>
#include <fstream>
#include <string>

int main () {
  std::string line;
  std::ifstream test ("test.txt");
  if (test.is_open())
  {
    while(getline(test, line)){
      std::cout << line << '\n';
    }
    test.close();
  }

  return 0;
}