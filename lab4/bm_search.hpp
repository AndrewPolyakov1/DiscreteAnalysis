#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

void BadCharacter(const std::vector<std::string> &pattern, std::map<std::string, int> &BCmap)
{
    for (int i = 0; i < (int)pattern.size() - 1; ++i)
        BCmap[pattern[i]] = i;
}

void GoodSuffix(const std::vector<std::string> &pattern, std::vector<int> &GSvec)
{
    int n = (int)pattern.size();
    int left = 0;
    int right = 0;

    std::vector<int> Zfunction(n, 0);
    for (int i = 1; i < n; ++i)
    {
        if (i <= right)
            Zfunction[i] = std::min(right - i + 1, Zfunction[i - left]);

        while (i + Zfunction[i] < n && (pattern[n - 1 - Zfunction[i]] == pattern[n - 1 - (i + Zfunction[i])]))
            Zfunction[i]++;

        if (i + Zfunction[i] - 1 > right)
        {
            left = i;
            right = i + Zfunction[i] - 1;
        }
    }
    std::vector<int> N(Zfunction.rbegin(), Zfunction.rend());
    std::vector<int> Lbig(n + 1, n);

    int j;
    for (int i = 0; i < n - 1; ++i)
    {
        j = n - N[i];
        Lbig[j] = i;
    }

    std::vector<int> Lsmall(n + 1, n);
    for (int i = n - 1; i >= 0; i--)
    {
        j = n - i;
        if (N[j - 1] == j) Lsmall[i] = (j - 1);
        else  Lsmall[i] = Lsmall[i + 1];
    }
    for (int i = 0; i < n + 1; ++i)
        if (Lbig[i] == n) Lbig[i] = Lsmall[i];

    for (auto &x : Lbig)
        if (x != n) x = n - 1 - x;

    GSvec = Lbig;
}

std::vector<int> Search(std::vector<std::string> &pattern, std::vector<std::string> &txt)
{
    std::map<std::string, int> BCmap;
    BadCharacter(pattern, BCmap);

    std::vector<int> GSvec(pattern.size() + 1, pattern.size());
    GoodSuffix(pattern, GSvec);

    std::vector<int> result;
    int j, bound = 0, shift = 0;
    for (int i = 0; i < 1 + (int)txt.size() - (int)pattern.size();)
    {
        for (j = pattern.size() - 1; j >= bound; j--)
        {
            if (pattern[j] != txt[i + j])
            {
                break;
            }
        }
        if (j < bound)
        {
            result.push_back(i);
            bound = pattern.size() - GSvec[0];
            j = -1;
        }
        else
        {
            bound = 0;
        }
        if (j < bound)
        {
            shift = GSvec[j + 1];
        }
        else
        {
            shift = std::max({1, GSvec[j + 1], j - BCmap[txt[i + j]]});
        }
        i += shift;
    }

    return result;
}
