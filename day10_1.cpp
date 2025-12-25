#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>
#include <queue>

int bfs(const std::vector<std::vector<bool>>& adjacency_matrix, int node_id)
{
    size_t n{adjacency_matrix.size()};
    std::vector<bool> not_visited(n, true);
    std::vector<int> dist(n);
    std::queue<std::pair<size_t,int>> q;

    q.push({node_id, 0});
    not_visited[node_id] = false;
    dist[node_id] = 0;

    while(!q.empty())
    {
        auto [current_node, current_dist] = q.front();
        q.pop();

        for (size_t i{0}; i < n; ++i)
        {
            if (not_visited[i] && adjacency_matrix[current_node][i])
            {
                q.push({i, current_dist + 1});
                not_visited[i] = false;
                dist[i] = current_dist + 1;

                if (i == 0)
                    return current_dist + 1;
            }

        }
    }
    
    return std::numeric_limits<int>::max();
}

int main()
{
    std::string line;
    int total_button_presses{0};
    while(std::getline(std::cin, line))
    {
        size_t indicator_lights_size{line.find(']') - 1};

        int start_pattern{0};
        for (int i{1}; line[i] != ']'; i++)
        {
            if (line[i] == '#')
            {
                start_pattern += (1 << std::abs(i - 1 - (int)(indicator_lights_size - 1)));
            }
        }

        std::vector<std::vector<int>> buttons;
        size_t start = line.find('(');
        while (start != std::string::npos)
        {
            size_t end = line.find(')', start);
            std::istringstream iss(line.substr(start + 1, end));
            
            auto& current_buttons = buttons.emplace_back();

            int toggle_light, total{0};
            for(; (iss >> toggle_light); current_buttons.emplace_back(toggle_light), iss.ignore());
            
            start = line.find('(', end); 
        }

        std::vector<std::vector<bool>> adjacency_matrix(1 << indicator_lights_size, 
            std::vector<bool>(1 << indicator_lights_size));
            
        for (int i{0}; i < adjacency_matrix.size(); ++i)
        {
            for (const auto& button : buttons)
            {
                int total{0};
                for (const auto& indicator_light : button)
                {
                    total += (1 << std::abs(indicator_light - (int)(indicator_lights_size - 1)));
                }
                adjacency_matrix[i][total ^ i] = true;
            }
        }

        total_button_presses += bfs(adjacency_matrix, start_pattern);
    }

    std::cout << total_button_presses << std::endl;
}