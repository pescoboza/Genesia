#ifndef ACTOR_BASE_H
#define ACTOR_BASE_H

#include <unordered_map>
#include <queue>
#include <SFML/Graphics.hpp>
#include "ActorComponent.h"

using ActorComponents = std::unordered_map<ActorComponentType, std::unique_ptr<ActorComponent_Base>>;
using DrawableComponents = std::deque<ActorComponent_Drawable*>; 

enum class OriginSetting {
	TopRightCorner,
	Center
};


class Actor_Base {
public:
	Actor_Base(const sf::Vector2f& t_position, const float& t_rotationDeg);
	void init();
	const sf::Vector2f& getPosition()const;
	const float& getRotation()const;
	void setPosition(const float& t_x, const float& t_y);
	void setRotation(const float& t_r);
	void rotate(const float& t_dr);
	void incrementPosition(const float& t_dx, const float& t_dy);
	bool insertComponent(const ActorComponentType& t_componentType, std::unique_ptr<ActorComponent_Base> t_component);
	void forceInsertComponent(const ActorComponentType& t_componentType, std::unique_ptr<ActorComponent_Base> t_component);
	bool removeComponent(const ActorComponentType& t_componentType);
	bool hasComponent(const ActorComponentType& t_componentType)const;
	std::unique_ptr<ActorComponent_Base> extractComponent(const ActorComponentType& t_componentType);
	void sendDrawableToFront(const ActorComponent_Drawable* t_component);
	void sendDrawableToBack(const ActorComponent_Drawable* t_component);
	static void swapComponent(const ActorComponentType& t_componentType, Actor_Base* t_act1, Actor_Base* t_act2);
	void purgeComponents();

	virtual void update();
	virtual void reset();

	virtual void draw();
	virtual void clear();

protected:
	ActorComponent_Base* seeComponent(const ActorComponentType& t_componentType);
	const ActorComponent_Base* seeComponent(const ActorComponentType& t_componentType)const;

	sf::Vector2f m_position;
	float m_rotation; // [0 360) clockwise
	ActorComponents m_components;
	DrawableComponents m_drawables;


};


#endif // !ACTOR_BASE_H