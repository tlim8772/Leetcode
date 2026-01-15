#include <bits/stdc++.h>
using namespace std;

template<typename K, typename V>
struct Node {
    Node<K,V> *left = nullptr, *right = nullptr;
    K key;
    V val;

    Node();

    Node(K key, V val): key(key), val(val) {};
};

// queue is empty iff front becomes nullptr or back becomes nullptr (or both).
// put and get counts as used, so must put to the back
template <typename K, typename V>
struct LRU {
    int capacity;
    V null_val;
    Node<K, V> *front = nullptr, *back = nullptr;
    unordered_map<K, Node<K, V>*> store;

    LRU(int cap, V null_val): capacity(cap), null_val(null_val) {}

    // does not remove the entry in store.
    void remove(Node<K, V>* node_ptr) {
        auto& [left, right, k, v] = *node_ptr;
        if (left != nullptr) left->right = right;
        if (right != nullptr) right->left = left;
        if (front == node_ptr) front = right;
        if (back == node_ptr) back = left;

        // remember to set left, right to nullptr, otherwise we may have 'extended' the list
        // when we move this node to the back.
        left = nullptr, right = nullptr;
    }

    void add_back(Node<K, V>* node_ptr) {
        if (back != nullptr) {
            back->right = node_ptr;
            node_ptr->left = back;
        }
        back = node_ptr;
        if (front == nullptr) front = node_ptr;
    }

    V get(K key) {
        if (!store.contains(key)) return null_val;
        auto node_ptr = store[key];
        remove(node_ptr);
        add_back(node_ptr);
        return node_ptr->val;
    }

    void put(K key, V val) {
        if (store.contains(key)) {
            auto node_ptr = store[key];
            node_ptr->val = val;
            remove(node_ptr);
            add_back(node_ptr);
        } else {
            auto node_ptr = new Node(key, val);
            store[key] = node_ptr;
            add_back(node_ptr);
            
            if (store.size() > capacity) {
                auto temp = front;
                store.erase(front->key);
                remove(front);
                delete temp;
            } 
        }
       
    }

    ~LRU() {
        auto curr = front;
        while (curr != nullptr) {
            auto temp = curr;
            curr = curr->right;
            delete temp;
        }
    }
};


class LRUCache {
public:
    LRU<int, int> lru;
    
    LRUCache(int capacity): lru(capacity, -1) {}
    
    int get(int key) {
        return lru.get(key);
    }
    
    void put(int key, int value) {
        lru.put(key, value);
    }
};

int main() {
    LRUCache lru(3);
    lru.put(1, 1);
    lru.put(2, 2);
    lru.put(3, 3);
    lru.put(4, 4);
    cout << lru.get(4) << endl;
    cout << lru.get(3) << endl;
    cout << lru.get(2) << endl;
    cout << lru.get(1) << endl;
}
