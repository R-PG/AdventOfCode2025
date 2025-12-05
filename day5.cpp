#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

std::string line;

struct Range
{
    unsigned long long lower;
    unsigned long long upper;

    bool operator==(const Range& other) const
    {
        return lower == other.lower && upper == other.upper; 
    }
};

unsigned long long& lower(Range& range) {return range.lower;}
unsigned long long& upper(Range& range) {return range.upper;}

void print(Range& range)
{
    std::cout << range.lower << "-" << range.upper << std::endl;
}

void print(std::vector<Range>& ranges)
{
    std::cout << "RANGES" << std::endl;
    for (auto& range : ranges)
        print(range);
    std::cout << std::endl;
}

using range_t = std::pair<unsigned long long, unsigned long long>;
std::vector<Range> ranges;
unsigned long long fresh;

const bool PARTONE = false;

int main()
{
    while(std::getline(std::cin, line) && not line.empty())
    {
        std::istringstream iss(line);
        unsigned long long input_lower, input_upper;
        iss >> input_lower;
        iss.ignore();
        iss >> input_upper;

        ranges.emplace(ranges.begin(), Range{input_lower,input_upper});
        std::ranges::sort(ranges, std::less{}, &Range::upper);

        auto it = std::find(ranges.begin(), ranges.end(), Range{input_lower,input_upper});

        if ((it + 1) != ranges.end() && input_upper >= lower(*(it + 1)))
        {
            if (input_lower < lower(*(it + 1)))
            {
                lower(*(it + 1)) = input_lower;
                input_upper = upper(*(it + 1));
            }
            ranges.erase(it);
            it = std::find(ranges.begin(), ranges.end(), Range{input_lower,input_upper});
        }

        if (it != ranges.end() && it != ranges.begin() && input_lower <= upper(*(it - 1)))
        {
            if (input_lower < lower(*(it - 1)))
            {
                upper(*(it - 1)) = input_upper;
                lower(*(it - 1)) = input_lower;   
            }
            else
            {
                upper(*(it - 1)) = input_upper;
            }
            ranges.erase(it);
        }
    }

    //     while(std::getline(std::cin, line))
    // {
    //     std::istringstream iss(line);
    //     unsigned long long input_lower, input_upper;
    //     iss >> input_lower;
    //     iss >> input_upper;
        
    //     auto it = std::ranges::lower_bound(ranges, input_upper, std::less{}, &Range::upper);
        
    //     if (input_lower < lower(it))
    //     {
    //         if (input_upper < lower(it))
    //         {
                
    //         }
    //         else
    //         {
    //             lower(it) = input_lower;
    //         }
    //     }
    // }

    // print(ranges);

    if (PARTONE)
    {
        while(std::getline(std::cin, line))
        {
            std::istringstream iss(line);
            unsigned long long ingredient_id;
            iss >> ingredient_id;

            auto it = std::ranges::lower_bound(ranges, ingredient_id, std::less{}, &Range::upper);
            
            if (it != ranges.end() && it->lower <= ingredient_id)
                fresh++;
        }
        std::cout << fresh << std::endl;
    }
    else
    {
        for (auto& [lower, upper] : ranges)    
            fresh += upper - lower;
        fresh += ranges.size();
        std::cout << fresh << std::endl;
    }
}