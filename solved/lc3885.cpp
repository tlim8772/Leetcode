#include <bits/stdc++.h>
using namespace std;

// use a set to order {priority, eventId} in increasing order.
// use a hashmap to store eventId -> priority so we can easily update priority.

struct Cmp {
    bool operator()(const pair<int, int>& p1, const pair<int, int>& p2) const {
        return (p1.first < p2.first) || (p1.first == p2.first && p1.second > p2.second);
    }
};

class EventManager {
public:
    set<pair<int, int>, Cmp> order;
    unordered_map<int, int> id_to_priority;
    
    EventManager(vector<vector<int>>& events) {
        for (const auto& e : events) {
            id_to_priority[e[0]] = e[1];
            order.insert({e[1], e[0]});
        }
    }
    
    void updatePriority(int eventId, int newPriority) {
        if (!id_to_priority.contains(eventId)) return;
        int p = id_to_priority[eventId];
        order.erase({p, eventId});
        id_to_priority[eventId] = newPriority;
        order.insert({newPriority, eventId});
    }
    
    int pollHighest() { 
        if (order.size() == 0) return -1;
        auto it = --order.end();
        auto [p, id] = *it;
        order.erase(it);
        return id;
    }
};

int main() {
    vector<vector<int>> events = {{1, 1}, {2, 0}, {3, 10}};
    EventManager em(events);
};