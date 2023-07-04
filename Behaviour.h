#pragma once

#include "Moving.h"

class Behaviour : public Component {
public:
	Behaviour() {};
	virtual ~Behaviour() {};

	void link(std::shared_ptr<Moving> _moving, std::shared_ptr<Transform> _transform) {
		moving = _moving;
        transform = _transform;
	}

    void setTeam(int t) { team = t; }


    // check for possible error with our components
    // find the closest object that can be our target
	void action(){
        auto _moving = moving.lock();
        auto _transform = transform.lock();
        if (_moving && _transform) {
            // do not switch our current destination if there is one
            // this is a mechanic from the actual game called "locking"
            if (!_moving->destination.lock()) {
                int minDistance = INT_MAX;
                int dist = 0;
                std::shared_ptr<Transform> currDest;
                const int ourPosX = _transform->getPosition().x;
                const int ourPosY = _transform->getPosition().y;

                // search all damageable components
                for (const auto& obj : Damageable::all) {
                    // TODO: filter based on our behaviour
                    if (obj->team != team) {
                        dist = distance(ourPosX, ourPosY, obj->transform->getPosition().x, obj->transform->getPosition().y);
                        if (dist < minDistance) { minDistance = dist; currDest = obj->transform; }
                    }
                }

                if (currDest) {
                    _moving->destination = currDest;
                }

            }
        }
        else {
            // if we end up here, there is a big memory leak in the code
            printf("FATAL ERROR: components Moving and Transform deleted not at the same time as Behaviour");
        }
    };
    Behaviour* clone() const override { return new Behaviour(*this); }
private:
	std::weak_ptr<Moving> moving;
	std::weak_ptr<Transform> transform;
    int team;
};