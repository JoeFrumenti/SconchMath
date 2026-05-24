#pragma once
#pragma once
#include "CollisionManager.h"
#include <unordered_map>
#include <unordered_set>

// ------------------------------------------------------------------
// Spatial hash grid for broad-phase collision culling.
// Cell size should be roughly 2× your average object diameter.
// ------------------------------------------------------------------



int frames = 0;

CollisionManager::CollisionManager() {}

void CollisionManager::addObject(UD* object) {
    objects.push_back(object);
}

void CollisionManager::checkCollision2D() {
    frames++;
    const float CELL_SIZE = 64.0f;

    // Reuse allocations from last frame instead of reallocating
    grid.clear();
    checkedPairs.clear();
    grid.reserve(objects.size() * 2);

    auto cellKey = [&](int cx, int cy) -> long long {
        return ((long long)(uint32_t)cx << 32) | (uint32_t)cy;
        };

    for (UD* obj : objects) {
        float x = obj->getPos().x;
        float y = obj->getPos().y;
        float hw = obj->getWidth();   // assuming half-extents; adjust if full width
        float hh = obj->getHeight();

        int x0 = (int)std::floor((x - hw) / CELL_SIZE);
        int x1 = (int)std::floor((x + hw) / CELL_SIZE);
        int y0 = (int)std::floor((y - hh) / CELL_SIZE);
        int y1 = (int)std::floor((y + hh) / CELL_SIZE);

        for (int cx = x0; cx <= x1; ++cx)
            for (int cy = y0; cy <= y1; ++cy)
                grid[cellKey(cx, cy)].push_back(obj);
    }

    // --- Check only pairs that share a cell ---
    // Use a seen-set so we don't fire the same pair twice
    std::unordered_set<std::pair<UD*, UD*>, PairHash> checkedPairs;
    checkedPairs.reserve(objects.size() * 4);

    for (auto& entry : grid) {
        auto& cell = entry.second;
        for (size_t i = 0; i < cell.size(); ++i) {
            for (size_t j = i + 1; j < cell.size(); ++j) {
                UD* a = cell[i];
                UD* b = cell[j];

                // Canonical order so (a,b) and (b,a) map to the same key
                if (a > b) std::swap(a, b);
                if (!checkedPairs.insert({ a, b }).second)
                    continue; // already tested this frame

                bool overlapX = std::abs(a->getPos().x - b->getPos().x) < (a->getWidth() + b->getWidth());
                bool overlapY = std::abs(a->getPos().y - b->getPos().y) < (a->getHeight() + b->getHeight());

                auto pair = std::make_pair(a, b);
                bool wasColliding = activeCollisions.count(pair) > 0;
                bool isColliding = overlapX && overlapY;

                if (isColliding && !wasColliding) {
                    Collision col1(a), col2(b);
                    a->Collide(col2);
                    b->Collide(col1);
                    activeCollisions.insert(pair);
                }
                else if (!isColliding && wasColliding) {
                    Collision col1(a), col2(b);
                    a->exitCollision(col2);
                    b->exitCollision(col1);
                    activeCollisions.erase(pair);
                }
            }
        }
    }
}


void CollisionManager::removeObject(int id) {
    UD* removed = nullptr;

    // capture the pointer before removing
    for (auto& obj : objects) {
        if (obj->getId() == id) {
            removed = obj;
            break;
        }
    }

    // fix: assignment is outside the loop
    objects.erase(
        std::remove_if(objects.begin(), objects.end(),
            [id](UD* obj) { return obj->getId() == id; }),
        objects.end()
    );

    if (removed) {
        for (auto it = activeCollisions.begin(); it != activeCollisions.end(); ) {
            if (it->first == removed || it->second == removed)
                it = activeCollisions.erase(it);
            else
                ++it;
        }
    }
}
