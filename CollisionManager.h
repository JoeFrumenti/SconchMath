#pragma once
#include "UD.h"
#include "UDManager.h"
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include "Collision.h"

struct PairHash {
    size_t operator()(const std::pair<UD*, UD*>& p) const {
        auto h1 = std::hash<UD*>{}(p.first);
        auto h2 = std::hash<UD*>{}(p.second);
        return h1 ^ (h2 << 32 | h2 >> 32);
    }
};

class CollisionManager {
private:
    std::vector<UD*> objects;
    std::set<std::pair<UD*, UD*>> activeCollisions;
    std::unordered_map<long long, std::vector<UD*>> grid;
    std::unordered_set<std::pair<UD*, UD*>, PairHash> checkedPairs;
public:
    CollisionManager();
    static CollisionManager& getInstance() {
        static CollisionManager instance;
        return instance;
    }
    void addObject(UD* object);
    void checkCollision2D();
    void removeObject(int id);
};