#pragma once

class Component {
public:
	virtual ~Component(){};
	virtual Component* clone() const = 0;

	virtual void action() = 0;
};