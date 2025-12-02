#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <map>
#include <vector>
#include <set>

std::string line;
unsigned long long first, last, prefix, sum;
char sep;
int n;

// factor we can have a number repeated in a number with n digits
// N / factor := number of digits of the number that can be repeated
std::map<int, std::vector<int>> integer_factorization = {
    {1, {}},
    {2, {2}},
    {3, {3}},
    {4, {4, 2}},
    {5, {5}},
    {6, {6, 3, 2}},
    {7, {7}},
    {8, {8, 4, 2}},
    {9, {9, 3}},
    {10, {10, 5, 2}}};

std::set<unsigned long long> invalid_ids;

int number_of_digits(unsigned long long a)
{
    if (a == 0)
    {
        return 1;
    }
    else
    {
        int n{0};
        while (a > 0)
        {
            a /= 10;
            n++;
        }
        return n;
    }
}

inline unsigned long long first_ndigits(unsigned long long a, int ndigits, int n)
{
    return (a - (a % (int)std::pow(10, ndigits - n))) / std::pow(10, ndigits - n);
}

inline unsigned long long construct_number(unsigned long long a, int factor)
{
    unsigned long long number{a};
    factor--;
    while (factor > 0)
    {
        number = number * std::pow(10, number_of_digits(a)) + a;
        factor--;
    }
    return number;
}

const bool PARTONE = false;

int main()
{
    if (PARTONE)
    {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        do
        {
            iss >> first;
            iss >> sep;
            iss >> last;
            n = number_of_digits(last);
            if (n % 2 != 0)
            {
                prefix = std::pow(10, n / 2) - 1;
            }
            else
            {
                prefix = first_ndigits(last, n, n / 2);
            }

            unsigned long long candidate = construct_number(prefix, 2);
            do
            {
                if (first <= candidate && candidate <= last)
                {
                    sum += candidate;
                }
                prefix--;
                candidate = construct_number(prefix, 2);
            } while (first <= candidate);

        } while (iss >> sep);
        std::cout << sum << std::endl;
    }
    else
    {

        std::getline(std::cin, line);
        std::istringstream iss(line);
        do
        {
            iss >> first;
            iss >> sep;
            iss >> last;
            n = number_of_digits(last);

            do
            {
                // Try to find invalid ids for numbers repeating factor times
                for (int factor : integer_factorization[n])
                {
                    prefix = first_ndigits(last, n, n / factor);
                    unsigned long long candidate = construct_number(prefix, factor);

                    do
                    {
                        if (first <= candidate && candidate <= last)
                        {
                            invalid_ids.insert(candidate);
                        }
                        prefix--;
                        candidate = construct_number(prefix, factor);
                    } while (first <= candidate && std::pow(10, n / factor - 1) <= prefix);
                }
                n--;
            } while (first <= std::pow(10, n) - 1);

            for (unsigned long long id : invalid_ids)
            {
                sum += id;
            }
            invalid_ids.clear();

        } while (iss >> sep);
        std::cout << sum << std::endl;
    }
}