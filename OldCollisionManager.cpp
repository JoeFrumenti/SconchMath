
#include "GameObject.h"
#include "ObjectManager.h"
#include <vector>

class OldCollisionManager {
private:
	std::vector<GameObject> objects;
	std::vector<GameObject> coins;
public:
	OldCollisionManager() {

	}

	void addObject(GameObject& object) {
		objects.push_back(object);
	}

	void addCoin(GameObject& coin) {
		coins.push_back(coin);
	}

	void checkCollision() {
		auto& objManager = ObjectManager::getInstance();
		float coinsize = 1.4;
		for (auto& obj : objects) {
			glm::vec2 objCenter = obj.getCenter();
			for (GameObject& coin : coins) {
				coin.spin();
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