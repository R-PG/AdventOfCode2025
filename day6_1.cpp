#include <iostream>
#include <string>
#include <sstream>
#include <vector>

std::string line;
std::vector<std::vector<int>> operands;
std::vector<bool> problems; 

unsigned long long grand_total;

int main()
{
    while(std::getline(std::cin, line) && line.front() != '*')
    {
        auto& row = operands.emplace_back();
        std::istringstream iss(line);
        int op;
        while(iss >> op) {row.emplace_back(op);}
    }
    
    std::istringstream iss(line);
    char op;
    while(iss >> op) {problems.emplace_back(op == '*');}

    for (size_t j{0}; j < operands.front().size(); ++j)
    {
        unsigned long long op_res{problems[j]};
        for (size_t i{0}; i < operands.size(); ++i)
        {
            op_res = (problems[j]) ? op_res * operands[i][j] : op_res + operands[i][j];  
        }
        grand_total += op_res;
    }
    std::cout << grand_total << std::endl;
}