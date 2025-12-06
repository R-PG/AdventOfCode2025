#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

std::string line;
std::vector<std::string> operands;
std::vector<bool> problems; 

size_t column;

int read_next_cephalopod_number()
{
    int number{0};
    for (size_t i{0}; column < operands.front().size() && i < operands.size(); ++i)
    {
        number *= (operands[i][column] == ' ') ? 1 : 10;
        number += (operands[i][column] == ' ') ? 0 : operands[i][column] - '0';
    }
    column++;
    return number;
}

unsigned long long grand_total;

int main()
{
    while(std::getline(std::cin, line) && line.front() != '*')
    {
        std::ranges::reverse(line);
        operands.emplace_back(line);
    }
    
    std::istringstream iss(line);
    char op;
    while(iss >> op) {problems.emplace_back(op == '*');}
    std::ranges::reverse(problems);

    size_t problem_id{0};
    for (size_t j{0}; j < problems.size(); ++j)
    {
        unsigned long long op_res{problems[j]};
        int operand;

        while((operand = read_next_cephalopod_number()))
        {
            op_res = (problems[j]) ? op_res * operand : op_res + operand; 
        }
        
        grand_total += op_res;
    }
    std::cout << grand_total << std::endl;
}