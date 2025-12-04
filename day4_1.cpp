#include <iostream>
#include <vector>

int accesible_rolls;
std::vector<std::vector<bool>> grid;

int main()
{
    char c;

    while((c = std::getchar()) != EOF)
    {
        auto& current_row = grid.emplace_back();
        do
        {
            current_row.emplace_back(c == '@');
        } while((c = std::getchar()) != '\n');
    }

    size_t dim_x{grid.size()};
    size_t dim_y{grid[0].size()};

    // check corners
    if (grid[0][0] && 
        grid[0][1] +  
        grid[1][0] + grid[1][1] < 4)
        accesible_rolls++;
    
    if (grid[0][dim_x - 1] && 
        grid[0][dim_x - 2] +  
        grid[1][dim_x - 1] + grid[1][dim_x - 2] < 4)
        accesible_rolls++;

    if (grid[dim_y - 1][0] && 
        grid[dim_y - 1][1] +  
        grid[dim_y - 2][0] + grid[dim_y - 2][1] < 4)
        accesible_rolls++;

    if (grid[dim_y - 1][dim_x - 1] && 
        grid[dim_y - 1][dim_x - 2] +  
        grid[dim_y - 2][dim_x - 1] + grid[dim_x - 2][1] < 4)
        accesible_rolls++;

    // First row
    for (size_t j{1}; j < grid[0].size() - 1; ++j)
    {
        if (grid[0][j] && 
            grid[0][j - 1] + grid[0][j + 1] + 
            grid[1][j - 1] + grid[1][j] + grid[1][j + 1] < 4)
            accesible_rolls++;
    }

    // First column
    for (size_t i{1}; i < grid[0].size() - 1; ++i)
    {
        if (grid[i][0] && 
            grid[i - 1][0] + grid[i + 1][0] + 
            grid[i - 1][1] + grid[i][1] + grid[i + 1][1] < 4)
            accesible_rolls++;
    }

    // Middle rows aqnd columns
    for (size_t i{1}; i < grid[0].size() - 1; ++i)
        for (size_t j{1}; j < grid[0].size() - 1; ++j)
        {
            if (grid[i][j] && 
                grid[i - 1][j - 1] + grid[i - 1][j] + grid[i - 1][j + 1] + 
                grid[i][j - 1] + grid[i][j + 1] + 
                grid[i + 1][j - 1] + grid[i + 1][j] + grid[i + 1][j + 1] < 4)
                accesible_rolls++;
        }

    // Last row
    for (size_t j{1}; j < grid[0].size() - 1; ++j)
    {
        if (grid[dim_x - 1][j] && 
            grid[dim_x - 1][j - 1] + grid[dim_x - 1][j + 1] + 
            grid[dim_x - 2][j - 1] + grid[dim_x - 2][j] + grid[dim_x - 2][j + 1] < 4)
            accesible_rolls++;
    }

    // Last column
    for (size_t i{1}; i < grid[0].size() - 1; ++i)
    {
        if (grid[i][dim_y - 1] && 
            grid[i - 1][dim_y - 1] + grid[i + 1][dim_y - 1] + 
            grid[i - 1][dim_y - 2] + grid[i][dim_y - 2] + grid[i + 1][dim_y - 2] < 4)
            accesible_rolls++;
    }
        
    std::cout << accesible_rolls << std::endl;
}