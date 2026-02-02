#include <bits/stdc++.h>
using namespace std;

// use a hashmap for lazy deletion.
// when we cancel rider, we mark it for deletion.
// when pairing up, pop all marked for deletion riders from the queue first.

class RideSharingSystem {
public:
    unordered_set<int> existing_rid;
    deque<int> rid_queue, did_queue;
    
    RideSharingSystem() {
        
    }
    
    void addRider(int riderId) {
        existing_rid.insert(riderId);
        rid_queue.push_back(riderId);
    }
    
    void addDriver(int driverId) {
        did_queue.push_back(driverId);
    }
    
    vector<int> matchDriverWithRider() {
        while (!rid_queue.empty() && !existing_rid.contains(rid_queue.front())) {
            rid_queue.pop_front();
        }

        if (rid_queue.empty() || did_queue.empty()) return {-1, -1};

        int rid = rid_queue.front(); rid_queue.pop_front();
        int did = did_queue.front(); did_queue.pop_front();
        existing_rid.erase(rid);
        
        return {did, rid};
    }
    
    void cancelRider(int riderId) {
        existing_rid.erase(riderId);
    }
};

int main() {
    RideSharingSystem rideSharingSystem = RideSharingSystem(); // Initializes the system
    rideSharingSystem.addRider(8); // rider 8 joins the queue
    rideSharingSystem.addDriver(8); // driver 8 joins the queue
    rideSharingSystem.addDriver(6); // driver 6 joins the queue
    rideSharingSystem.matchDriverWithRider(); // returns [8, 8]
    rideSharingSystem.addRider(2); // rider 2 joins the queue
    rideSharingSystem.cancelRider(2); // rider 2 cancels
    cout << rideSharingSystem.matchDriverWithRider()[0] << endl; // returns [-1, -1]
}