#include <iostream>
#include <string>
#include <sstream>

std::string line;
int dial{50}, password{0}, clicks;
char rotation;

inline int modulo(int a, int b) {
  const int result = a % b;
  return result >= 0 ? result : result + b;
}

int main()
{
    // while(std::getline(std::cin, line))
    // {
    //     std::istringstream iss(line);
    //     iss >> rotation;
    //     iss >> clicks;
    //     dial += (rotation == 'L') ? -clicks : clicks;
    //     dial = modulo(dial, 100);
    //     password += int(dial == 0);
    // }
    while(std::getline(std::cin, line))
    {
        std::istringstream iss(line);
        iss >> rotation;
        iss >> clicks;
        while (clicks > 0)
        {
            dial += (rotation == 'L') ? -1 : 1;
            password += int(dial % 100 == 0);
            clicks--;
        }
        if (dial > 0 && dial < 100)
        {
            dial = modulo(dial, 100);
            password += int(dial == 0);
        }
        else
        {
            dial = modulo(dial, 100);
        }
    }
    std::cout << password << std::endl;
}