
#include "GameObject.h"
#include "ObjectManager.h"
#include <vector>

class CollisionManager {
private:
	std::vector<GameObject> objects;
	std::vector<GameObject> coins;
public:
	CollisionManager() {

	}

	void addObject(GameObject& object) {
		objects.push_back(object);
	}

	void addCoin(GameObject& coin) {
		coins.push_back(coin);
		std::cout << coin.getId();
	}

	void checkCollision() {
		auto& objManager = ObjectManager::getInstance();
		for (auto& obj : objects) {
			glm::vec2 objCenter = obj.getCenter();
			for (GameObject& coin : coins) {
				float coinsize = 1;
				glm::vec2 coinCenter = coin.getCenter();
				if (objCenter.x > coinCenter.x - coinsize
					&& objCenter.x < coinCenter.x + coinsize
					&& objCenter.y <coinCenter.y + coinsize
					&& objCenter.y >coinCenter.y - coinsize)
				{
					coin.destroy();
					objManager.removeObject(coin.getId());
					removeObject(coin.getId());
				}

			}
		}
	}

	void removeObject(int id) {

		std::vector<GameObject> temp;
		for (GameObject& obj : coins) {

			if (obj.id != id) {
				temp.push_back(obj);
			}

			coins = temp;
		}
	}
};