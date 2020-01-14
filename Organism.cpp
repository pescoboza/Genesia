#include <exception>
#include "Actor_Base.h"
#include "Organism.h"
#include "MathHelpers.h"
#include "Utilities.h"
#include "SharedContext.h"
#include "Engine.h"

static const float S_TIME_ZERO{ 0.f };
static const std::string S_DEFAULT_TEXTURE{ "Texture_organism" };
static const float S_TEXT_OFFSET_FACTOR{ 1.1f };
static const sf::Color S_DEFAULT_COLOR{ 255,255,255,255 };
static const float S_DEFAULT_SIZE{ 1.f };
static const float S_DEFAULT_DESTRUCTION_DELAY{ 10.f };

////////////////////////////////////////////////////////////
Organism::Organism(
	SharedContext& t_context,
	const std::string& t_name,
	const sf::Vector2f& t_position,
	const float& t_rotation,
	const float& t_age) :
	Actor_Base(t_context, t_position, t_rotation, S_DEFAULT_COLOR, S_DEFAULT_TEXTURE, sf::IntRect(), true, true),
	m_name{ t_name },
	m_age{ t_age },
	m_ai{ nullptr },
	m_destructionDelay{S_DEFAULT_DESTRUCTION_DELAY}
{
	m_text.setString(m_name);
	setColorRGB(m_color); //Also write the HSL color
	m_ai = std::make_unique<Ai_Organism>(this);
}

////////////////////////////////////////////////////////////
OrganismPtr Organism::makeDefaultClone(SharedContext& t_context, const std::string& t_name, const sf::Vector2f& t_position, const float& t_rotation, const float& t_age) {
	auto o{ std::make_unique<Organism>(t_context, t_name, t_position, t_rotation, t_age) };
	for (const auto& it : Trait_Base::getVitalTraits()) {
		o->m_traits.addTrait(std::move(Trait_Base::cloneDefaultTrait(it)));
	}
	o->m_traits.onOrganismConstruction(o.get(), 0.f); // Update all the traits
	return std::move(o);
}

////////////////////////////////////////////////////////////
OrganismPtr Organism::makeDefaultOffpring(SharedContext& t_context, const std::string& t_name, const sf::Vector2f& t_position, const float& t_rotation, const float& t_age) {
	auto o{ std::make_unique<Organism>(t_context, t_name, t_position, t_rotation, t_age) };
	for (const auto& it : Trait_Base::getVitalTraits()) {
		o->m_traits.addTrait(std::move(Trait_Base::reproduceDefaultTrait(t_context, it)));
	}
	o->m_traits.onOrganismConstruction(o.get(), 0.f); // Update all the traits
	return std::move(o);
}

////////////////////////////////////////////////////////////
const HSL& Organism::getColorHSL()const { return m_hslColor; }

////////////////////////////////////////////////////////////
void Organism::setColorHSL(const float& t_h, const float& t_s, const float& t_l) {
	m_hslColor.Hue = t_h;
	m_hslColor.Saturation = t_h;
	m_hslColor.Luminance = t_l;
	m_color = m_hslColor.TurnToRGB();
}

////////////////////////////////////////////////////////////
const sf::Color& Organism::getColorRGB()const { return m_color; }

////////////////////////////////////////////////////////////
void Organism::setColorRGB(const sf::Color& t_color) {
	m_color = t_color;
	m_hslColor = HSL::TurnToHSL(t_color);
}

////////////////////////////////////////////////////////////
const float& Organism::getMovementSpeed()const { return m_trait_movementSpeed; }

////////////////////////////////////////////////////////////
void Organism::setMovementSpeed(const float& t_movementSpeed) { m_trait_movementSpeed = t_movementSpeed; }

////////////////////////////////////////////////////////////
const float& Organism::getRotationSpeed()const { return m_trait_turningSpeed; }

////////////////////////////////////////////////////////////
void Organism::setRotationSpeed(const float& t_rotationSpeed) { m_trait_turningSpeed = t_rotationSpeed; }

////////////////////////////////////////////////////////////
const float& Organism::getAge()const { return m_age; }

////////////////////////////////////////////////////////////
void Organism::setAge(const float& t_age) { m_age = t_age; }

////////////////////////////////////////////////////////////
const float& Organism::getSize()const { return m_trait_size; }

////////////////////////////////////////////////////////////
void Organism::setSize(const float& t_size) { m_trait_size = t_size; }

////////////////////////////////////////////////////////////
const std::string& Organism::getName()const { return m_name; }

////////////////////////////////////////////////////////////
void Organism::setName(const std::string& t_name) { m_name = t_name; }

////////////////////////////////////////////////////////////
void Organism::update(const float& t_elapsed) {
	// Update the organism's age
	m_age += t_elapsed;
	if (m_age >= m_trait_lifespan && !m_isDead) { die(); }
	if (m_isDead) {
		if (m_destructionDelay <= 0.f) { m_destroy = true; }
		m_destructionDelay -= t_elapsed;
		return;
	}// Dead organisms do not move, they just wait to decompose.

	// Update all the traits' effects
	m_traits.update(this, t_elapsed);

	// Update the organim's ai
	m_ai->update(this, t_elapsed);

	// Lower level update (position, rotation ...)
	Actor_Base::update(t_elapsed);
}

////////////////////////////////////////////////////////////
ActorPtr Organism::clone() {
	auto o{ std::make_unique<Organism>(m_context, m_name, m_position, m_rotation, m_age) };
	o->m_traits = std::move(*m_traits.clone().release()); // Pass unique ptr to regular member
	o->m_traits.onOrganismConstruction(o.get(),0.f); // Update "OnConstruction" traits
	return std::move(o);
}

////////////////////////////////////////////////////////////
void Organism::die() {
	m_isDead = true;
	m_name += " (dead)";
	m_text.setString(m_name);
}