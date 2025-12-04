#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

unsigned long long output_joltage;

int main()
{
    char c;

    while((c = std::getchar()) != EOF)
    {
        std::vector<char> battery_bank;
        do
        {
            battery_bank.emplace_back(c);
        } while((c = std::getchar()) != '\n');

        unsigned long long battery_joltage{0};
        unsigned long pending{12}, n{battery_bank.size()}, last{n - pending + 1}, i{0};
        
        while (pending > 0)
        {
            battery_joltage *= 10;
            auto largest_joltage_it = std::ranges::max_element(battery_bank.begin() + i, battery_bank.begin() + last);
            battery_joltage += (*largest_joltage_it - '0');
            i = std::ranges::distance(battery_bank.begin(), largest_joltage_it) + 1;
            pending--;
            last++;
        }

        output_joltage += battery_joltage;
    }
    std::cout << output_joltage << std::endl;
}