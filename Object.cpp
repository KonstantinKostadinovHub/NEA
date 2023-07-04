#include "Object.h"

#include "World.h"

#include <iostream>

Object::Object()
{
}

Component* Object::addComponent(COMPONENT_TYPE type)
{
	if (components.find(type) == components.end())
	{
		std::unique_ptr<Component> component;

		switch (type) {
		case COMPONENT_TYPE::MOVING:
			component = std::make_unique<Moving>();
			break;
		case COMPONENT_TYPE::TRANSFORM:
			component = std::make_unique<Transform>();
			break;
		case COMPONENT_TYPE::DAMAGEABLE:
			component = std::make_unique<Damageable>();
			break;
		case COMPONENT_TYPE::BEHAVIOUR:
			component = std::make_unique<Behaviour>();
			break;
		}

		components.insert({ type, std::move(component) });
		if (type == COMPONENT_TYPE::TRANSFORM) {
			transform = std::dynamic_pointer_cast<Transform>(components.at(type));
		}
		return components.at(type).get();
	}
	else {
		printf("Error: Component already added");
	}
}

Component* Object::addComponent(COMPONENT_TYPE type, Component* _comp)
{
	if (_comp == nullptr) {
		printf("Error: Component param is nullptr");
	}
	if (components.find(type) == components.end())
	{
		std::unique_ptr<Component> component;

		component.reset(_comp->clone());

		components.insert({ type, std::move(component)});
		
		if (type == COMPONENT_TYPE::TRANSFORM) {
			transform = std::dynamic_pointer_cast<Transform>(components.at(type));
		}

		return components.at(type).get();
	}
	else {
		printf("Error: Component already added");
	}
	return nullptr;
}
 
void Object::init()
{
}

void Object::draw()
{
	if (!transform.expired()) {

		sf::Texture texture;
		if (!texture.loadFromFile(transform.lock()->textureLocation)) {
			printf("ERROR");
		}
		sf::RectangleShape sprite({transform.lock()->rect.width, transform.lock()->rect.height});
		sprite.setTexture(&texture);
		sprite.setPosition({ transform.lock()->rect.left, transform.lock()->rect.top});
		World::draw(transform.lock()->sprite);
	}
	else {
		printf("FATAL ERROR: transform has expired before drawing");
	}
	if (components.find(COMPONENT_TYPE::DAMAGEABLE) != components.end()) {
		std::dynamic_pointer_cast<Damageable>(components.at(COMPONENT_TYPE::DAMAGEABLE))->draw();
	}
}

void Object::action()
{
	for (const auto& comp : components) {
		comp.second.get()->action();
	}
}

void Object::setTeam(int _team)
{
	team = _team;
	if (components.find(COMPONENT_TYPE::BEHAVIOUR) != components.end()) {
		dynamic_cast<Behaviour*>(components.at(COMPONENT_TYPE::BEHAVIOUR).get())->setTeam(team);
	}
	if (components.find(COMPONENT_TYPE::DAMAGEABLE) != components.end()) {
		dynamic_cast<Damageable*>(components.at(COMPONENT_TYPE::DAMAGEABLE).get())->setTeam(team);
	}
}

void Object::link(COMPONENT_TYPE type)
{
	transform = std::dynamic_pointer_cast<Transform>(components.at(COMPONENT_TYPE::TRANSFORM));

	switch (type) {
	case COMPONENT_TYPE::MOVING:
		dynamic_cast<Moving*>(components.at(COMPONENT_TYPE::MOVING).get())->
			link(std::dynamic_pointer_cast<Transform>(components.at(COMPONENT_TYPE::TRANSFORM)));
		break;
	case COMPONENT_TYPE::TRANSFORM:
		// none for transform
		break;
	case COMPONENT_TYPE::DAMAGEABLE:
		dynamic_cast<Damageable*>(components.at(COMPONENT_TYPE::DAMAGEABLE).get())->
			link(std::dynamic_pointer_cast<Transform>(components.at(COMPONENT_TYPE::TRANSFORM)));;
		break;
	case COMPONENT_TYPE::BEHAVIOUR:
		dynamic_cast<Behaviour*>(components.at(type).get())->link(
			std::dynamic_pointer_cast<Moving>(components.at(COMPONENT_TYPE::MOVING)), 
			std::dynamic_pointer_cast<Transform>(components.at(COMPONENT_TYPE::TRANSFORM))
		);
		break;
	}
}
