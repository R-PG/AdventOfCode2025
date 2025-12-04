#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

char c;
std::vector<char> battery_bank;
unsigned long long output_joltage;

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
        // std::cout << std::endl << std::endl;

        unsigned long long battery_joltage{0};
        unsigned long pending{12}, n{battery_bank.size()}, last{n - pending + 1}, i;
        auto largest_joltage_it = std::ranges::max_element(battery_bank.begin(), battery_bank.begin() + last);
        battery_joltage += (*largest_joltage_it - '0');
        i = std::ranges::distance(battery_bank.begin(), largest_joltage_it) + 1;
        pending--;
        last++;
        while (pending > 0)
        {
            battery_joltage *= 10;
            largest_joltage_it = std::ranges::max_element(battery_bank.begin() + i, battery_bank.begin() + last);
            battery_joltage += (*largest_joltage_it - '0');
            i = std::ranges::distance(battery_bank.begin(), largest_joltage_it) + 1;
            pending--;
            last++;
            
            // std::cout << battery_joltage << " pending: " << pending << " i: " << i << " last: " << last << std::endl;
        }

        // std::cout << std::endl;
        output_joltage += battery_joltage;

        battery_bank.clear();
    } while((c = std::getchar()) != EOF);
    std::cout << output_joltage << std::endl;
}