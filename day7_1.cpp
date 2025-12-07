#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>

std::string line;
std::vector<std::vector<bool>> splitter_map;
std::set<size_t> beams;

int splits;

void print_beams()
{
    for (auto& elem : beams)
        std::cout << elem << std::endl;
}

void print_splitter_map()
{
    for (auto& row : splitter_map)
    {
        for (auto&& elem: row)
            // std::cout << ((elem) ? '^' : '.');
            std::cout << elem;
    }
}

int main()
{
    std::getline(std::cin, line);
    beams.insert(std::distance(line.begin(), std::ranges::find(line, 'S')));
    std::getline(std::cin, line);

    while(std::getline(std::cin, line))
    {
        auto& row = splitter_map.emplace_back();
        for (auto& column_elem : line)
            row.emplace_back(column_elem == '^');
        std::getline(std::cin, line);
    }

    for (size_t i{0}; i < splitter_map.size(); ++i)
    {
        std::set<size_t> new_beams;
        for (auto& beam: beams)
        {
            if (splitter_map[i][beam])
            {
                splits++;
                new_beams.insert(beam - 1);
                new_beams.insert(beam + 1);
            }
            else
            {
                new_beams.insert(beam);
            }
        }
        beams = new_beams;
    }
    
    std::cout << splits << std::endl;
}