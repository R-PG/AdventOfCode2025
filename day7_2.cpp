#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

std::string line;
std::vector<std::vector<bool>> splitter_map;
std::map<size_t,size_t> beams;

unsigned long long timelines;

void print_beams()
{
    for (auto& [beam,count] : beams)
        std::cout << beam << ":" << count << std::endl;
}

int main()
{
    std::getline(std::cin, line);
    beams.insert({std::distance(line.begin(), std::ranges::find(line, 'S')), 1});
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
        std::map<size_t,size_t> new_beams;
        for (auto& [beam,count] : beams)
        {
            if (splitter_map[i][beam])
            {
                new_beams[beam - 1] += count;
                new_beams[beam + 1] += count;
            }
            else
            {
                new_beams[beam] += count;
            }
        }
        beams = new_beams;
    }

    for (auto& [beam,count] : beams)
        timelines += count;
    
    std::cout << timelines << std::endl;
}