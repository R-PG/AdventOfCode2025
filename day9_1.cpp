#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

std::string line;

using coord_t = std::tuple<long long,long long>;
std::vector<coord_t> red_tiles;

long long max_area;

int main()
{
    while(std::getline(std::cin, line))
    {
        std::istringstream iss(line);
        double x, y, z;
        iss >> x;
        iss.ignore();
        iss >> y;
        red_tiles.emplace_back(coord_t{x,y});
    }

    for (size_t i{0}; i < red_tiles.size(); ++i)
        for (size_t j{0}; j < red_tiles.size(); ++j)
        {
            max_area = std::max(max_area, 
                (std::abs(std::get<0>(red_tiles[i]) - std::get<0>(red_tiles[j])) + 1)
            * (std::abs(std::get<1>(red_tiles[i]) - std::get<1>(red_tiles[j])) + 1));
        }

    std::cout << max_area << std::endl;
}