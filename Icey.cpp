#include "Icey.h"


Icey::Icey(){
	ourModel = new Model("C:/Users/joefr/source/repos/SconchMath/assets/Models/ice.obj");
	tags.push_back("Icey");
	width = 0.5;
	height = 0.5;
	UDManager::getInstance().addUD(this);
}

void Icey::Collide(Collision col){
	BouncingCube* ob = dynamic_cast<BouncingCube*>(col.obj);
	BouncingCube* par = dynamic_cast<BouncingCube*>(Parent);

	for (auto& tag : col.obj->getTags())
	{
		if (tag == "bcube" && col.obj != Parent && !(ob->getFrozen())) {
				
			ob->freeze(par->getStats().debuffTime);
			par->getStats().debuffTime += 0.2f;
			freezeTime = std::min(freezeTime + 0.3f, 2.0f);

		}
	}
}
