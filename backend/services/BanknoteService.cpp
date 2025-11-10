#include "backend/services/BanknoteService.h"
#include "backend/Exceptions.h"
#include <map>

BanknoteService::BanknoteService(IBanknoteRepository& repo) : _repo(repo) 
{}

void BanknoteService::doDispense(int amount)
{
    std::vector<std::pair<Denominations, int>> counts = _repo.getAllCounts();
    std::vector<std::pair<Denominations, int>> toDispense;
    if (!findComb(amount, counts, toDispense))
    {
        throw Exceptions::NoSuchCash;
    }
    for (const auto& pair : toDispense)
    {
        Denominations denom = pair.first;
        int count = pair.second;
        int newCount = _repo.getCount(denom) - count;
        if (newCount < 0)
        {
            throw Exceptions::NoSuchCash;
        }
        _repo.setCount(denom, newCount);
    }
}

bool BanknoteService::findComb(int target, 
    const std::vector<std::pair<Denominations, int>>& notes,
    std::vector<std::pair<Denominations, int>>& res)
{
    const int n = notes.size();
    if (target < 0) return false;

    std::vector<bool> dp(target + 1, false);
    dp[0] = true;

    std::vector<std::pair<int, int>> path(target + 1, { -1, -1 });
    path[0] = { 0, -1 };

    for (int i = 0; i < n; ++i)
    {
        const auto& note = notes[i];

        if ((int)note.first <= 0 || note.second <= 0) continue;

        std::vector<int> used(target + 1, 0);

        for (int s = (int)note.first; s <= target; ++s)
        {
            if (!dp[s] && dp[s - (int)note.first] && used[s - (int)note.first] < note.second)
            {
                dp[s] = true;
                used[s] = used[s - (int)note.first] + 1;
                path[s] = { s - (int)note.first, i };
            }
        }
    }

    if (!dp[target])
    {
        return false;
    }

    std::vector<int> take(n, 0);
    int cur = target;

    while (cur > 0)
    {
        std::pair<int, int> p = path[cur];
        int prev = p.first;
        int idx = p.second;

        if (prev < 0 || idx < 0)
        {
            return false;
        }

        ++take[idx];
        cur = prev;
    }

    std::map<int, int> byValue;
    for (int i = 0; i < n; ++i)
    {
        if (take[i] > 0)
        {
            byValue[(int)notes[i].first] += take[i];
        }
    }

    for (auto& pair : byValue)
    {
        int v = pair.first;
        int c = pair.second;
        res.push_back({ (Denominations)v, c });
    }
    return true;
}
