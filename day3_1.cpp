#include <iostream>
#include <vector>
#include <algorithm>

int output_joltage;

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

        auto largest_joltage_it = std::ranges::max_element(battery_bank.begin(), battery_bank.end() - 1);
        output_joltage += (*largest_joltage_it - '0') * 10;
        largest_joltage_it = std::ranges::max_element(largest_joltage_it + 1, battery_bank.end());
        output_joltage += + *largest_joltage_it - '0';

        battery_bank.clear();
    }
    std::cout << output_joltage << std::endl;
}