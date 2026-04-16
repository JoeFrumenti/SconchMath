
#include <OpenGL/GameObject.cpp>
#include <vector>

class CollisionManager {
private:
	std::vector<GameObject> objects;
	std::vector<GameObject> coins;
public:
	CollisionManager() {

	}

	void addObject(GameObject object) {
		objects.push_back(object);
	}

	void addCoin(GameObject coin) {
		coins.push_back(coin);
	}

	void checkCollision() {
		for(auto& obj:objects){
			glm::vec2 objCenter = obj.getCenter();
			for (auto& coin : coins) {
				float coinsize = 1;
				glm::vec2 coinCenter = coin.getCenter();
				if (objCenter.x > coinCenter.x - coinsize 
					&& objCenter.x < coinCenter.x + coinsize 
					&& objCenter.y <coinCenter.y + coinsize
					&& objCenter.y >coinCenter.y - coinsize)
				{
					coin.destroy();
				}
				
			}
		}
	}

};