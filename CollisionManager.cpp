#pragma once

#include "CollisionManager.h"

int frames = 0;
CollisionManager::CollisionManager() {}

void CollisionManager::addObject(UD* object) {
	objects.push_back(object);
}
void CollisionManager::checkCollision2D() {
    frames++;
    for (int i = 0; i < objects.size(); i++) {
        for (int j = i + 1; j < objects.size(); j++) {
            UD* a = objects[i];
            UD* b = objects[j];

            bool overlapX = std::abs(a->getPos().x - b->getPos().x) < (a->getWidth() + b->getWidth());
            bool overlapY = std::abs(a->getPos().y - b->getPos().y) < (a->getHeight() + b->getHeight());

            auto pair = std::make_pair(a, b);
            bool wasColliding = activeCollisions.count(pair) > 0;
            bool isColliding = overlapX && overlapY;

            if (isColliding && !wasColliding) {
                // Entered collision — fire once
                Collision col1(a);
                Collision col2(b);
                a->Collide(col2);
                b->Collide(col1);
                activeCollisions.insert(pair);
            }
            else if (!isColliding && wasColliding) {
                // Exited collision — clean up
                Collision col1(a);
                Collision col2(b);
                a->exitCollision(col2);
                b->exitCollision(col1);
                activeCollisions.erase(pair);
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
