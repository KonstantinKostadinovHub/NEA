#include "Moving.h"

void Moving::action()
{
    if (!destination.expired() && !isStunned() && !transform.expired()) {
        sf::Vector2f vel;
        vel = makeUnit(destination.lock()->getPosition() - transform.lock()->getPosition()) * speed;
        transform.lock()->move(vel);
    }
}

bool Moving::isStunned()
{
    return false;
}

