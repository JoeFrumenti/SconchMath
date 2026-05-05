#include "UD.h"

class Player1 : public UD {

private:
	int coins = 0;
public:
	void setParent(UD* parent) override {
		this->Parent = parent;
		coins = parent->getStats()["coins"];
	}


};