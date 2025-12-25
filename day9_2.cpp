#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <ranges>
#include <set>
#include <vector>
#include <unordered_map>

using tile_t = long long;
using coord_t = std::pair<tile_t, tile_t>; 

long long max_area;

void print_tiles(std::vector<std::pair<tile_t, tile_t>>& tiles)
{
    for (auto& elem : tiles)
        std::cout << elem.first << ":" << elem.second << std::endl;

    std::set<std::pair<tile_t, tile_t>> set_tiles(tiles.begin(), tiles.end());

    for (tile_t j{0}; j <= std::ranges::max(set_tiles, {}, &std::pair<tile_t, tile_t>::second).second; ++j)
    {
        for (tile_t i{0}; i <= std::ranges::max(set_tiles, {}, &std::pair<tile_t, tile_t>::first).first; ++i)
        {
            if (set_tiles.contains({i,j}))
                std::cout << "#";
            else
                std::cout << ".";
        }
        std::cout << std::endl;
    }
}

void print_coord(coord_t coord)
{
    std::cout << "First: " << coord.first << " Second: " << coord.second << std::endl;
}

// Returns position of hits along the memeber axis in convex hull 
const std::vector<tile_t> trace_ray(const std::set<coord_t>& convex_hull, coord_t p, coord_t grid_limit, 
    tile_t coord_t::* member)
{
    // std::cout << "RAY TRACING" << std::endl;

    p.*member = 0;
    std::vector<tile_t> hits;

    for (; p <= grid_limit; p.*member += 1)
    {     
        if (convex_hull.contains(p))
            hits.emplace_back(p.*member);
    }
    return hits;
}

std::vector<coord_t> get_intervals(const std::vector<tile_t>& ray_hits, tile_t coord_t::* member)
{
    size_t i{0};
    std::vector<coord_t> intervals;

    auto criteria = [](auto const& x, auto const& y) {return std::abs(x - y) != 1;};

    if (ray_hits.empty())
        return intervals;

    auto current = ray_hits.begin();

    do
    {
        auto found = std::ranges::adjacent_find(current, ray_hits.end(), criteria);

        if (found == ray_hits.end())
        {
            intervals.emplace_back(coord_t{*current, ray_hits.back()});
        }
        else
        {
            found = std::ranges::adjacent_find(found + 1, ray_hits.end(), criteria);
            if (found == ray_hits.end())
            {
                intervals.emplace_back(coord_t{*current, ray_hits.back()});
            }
            else
            {
                intervals.emplace_back(coord_t{*current, *(found)});
            }
        }
        
        if (found != ray_hits.end())
            current = found + 1;
        else
            break;
    }
    while(true);

    return intervals;
}

int main()
{
    std::vector<coord_t> red_tiles;  
    {
        std::string line;

        while (std::getline(std::cin, line))
        {
            std::istringstream iss(line);
            double x, y;
            iss >> x;
            iss.ignore();
            iss >> y;
            red_tiles.emplace_back(x,y);
        }
    }

    std::vector<tile_t> x_values;
    std::vector<tile_t> y_values;
    std::vector<std::pair<tile_t, tile_t>> compressed_red_tiles;
    {  
        std::set<tile_t> x_values_set(std::views::keys(red_tiles).begin(), std::views::keys(red_tiles).end());
        std::set<tile_t> y_values_set(std::views::values(red_tiles).begin(), std::views::values(red_tiles).end());

        for (auto& [x, y] : red_tiles)
        {
            compressed_red_tiles.emplace_back(std::distance(x_values_set.begin(), std::ranges::find(x_values_set, x)),
            std::distance(y_values_set.begin(), std::ranges::find(y_values_set, y)));
        }

        x_values.assign(x_values_set.begin(), x_values_set.end());
        y_values.assign(y_values_set.begin(), y_values_set.end());
    }

    std::set<std::pair<tile_t, tile_t>> convex_hull;

    // Construct convex hull
    {
        auto it = std::next(compressed_red_tiles.begin());
        while (it != compressed_red_tiles.end())
        {
            auto prev_it = std::prev(it);
            coord_t new_coord{*it};
            tile_t coord_t::* member = (it->first == prev_it->first) ? &coord_t::second : &coord_t::first;

            tile_t start = std::min((*it).*member, (*prev_it).*member);
            tile_t end   = std::max((*it).*member, (*prev_it).*member);

            for (tile_t pos = start; pos <= end; ++pos)
            {
                new_coord.*member = pos;
                convex_hull.emplace(new_coord);
            }

            it++;
        }
    }

    // std::vector<coord_t> convex_hull_vector(convex_hull.begin(), convex_hull.end());
    // print_tiles(convex_hull_vector);

    coord_t grid_limit{std::ranges::max(convex_hull | std::views::keys), 
        std::ranges::max(convex_hull | std::views::values)};

    std::unordered_map<tile_t, std::vector<coord_t>> intervals_set;

    for (size_t i{0}; i < compressed_red_tiles.size(); ++i)
        for (size_t j{i + 1}; j < compressed_red_tiles.size(); ++j)
        {
            bool inside{true};

            // Min value in each axis
            coord_t min{std::min(compressed_red_tiles[i].first, compressed_red_tiles[j].first),
            std::min(compressed_red_tiles[i].second, compressed_red_tiles[j].second)};

            // Max value in each axis
            coord_t max{std::max(compressed_red_tiles[i].first, compressed_red_tiles[j].first),
            std::max(compressed_red_tiles[i].second, compressed_red_tiles[j].second)};

            for (tile_t k{min.second}; inside && k <= max.second; ++k)
            {
                std::vector<coord_t> intervals;

                if (intervals_set.contains(k))
                {
                    intervals = intervals_set[k];
                }
                else
                {
                    auto ray = trace_ray(convex_hull, {0,k}, grid_limit, &coord_t::first);
                    intervals = get_intervals(ray, &coord_t::first);
                    intervals_set.emplace(k, intervals);
                }

                auto it = std::ranges::lower_bound(intervals, max.first, {}, &coord_t::second);
                if (it == intervals.end() || !(it->first <= min.first))
                {
                    inside = false;
                }       
            }

            if (inside)
            {
                max_area = std::max(max_area,
                (std::abs(x_values[compressed_red_tiles[i].first] - x_values[compressed_red_tiles[j].first]) + 1) * 
                (std::abs(y_values[compressed_red_tiles[i].second] - y_values[compressed_red_tiles[j].second]) + 1));
            }
        }

    std::cout << max_area << std::endl;
}