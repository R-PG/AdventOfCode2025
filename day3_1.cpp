#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

char c;
std::vector<char> battery_bank;
int output_joltage;

int main()
{
    c = std::getchar();
    do
    {
        do
        {
            battery_bank.emplace_back(c);
        } while((c = std::getchar()) != '\n');

        // for (auto& elem : battery_bank)
        //     std::cout << elem;
        // std::cout << std::endl;

        auto largest_joltage_it = std::ranges::max_element(battery_bank.begin(), battery_bank.end() - 1);
        output_joltage += (*largest_joltage_it - '0') * 10;
        largest_joltage_it = std::ranges::max_element(largest_joltage_it + 1, battery_bank.end());
        output_joltage += + *largest_joltage_it - '0';

        // output_joltage += (*largest_joltage_it - '0') * 10 + *second_largest_joltage_it - '0';
        // std::cout << (*largest_joltage_it - '0') * 10 + *second_largest_joltage_it - '0' << std::endl;

        battery_bank.clear();
    } while((c = std::getchar()) != EOF);
    std::cout << output_joltage << std::endl;
}