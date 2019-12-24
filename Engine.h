#ifndef  ENGINE_H
#define ENGINE_H

#include <vector>
#include <unordered_set>
#include <functional>
#include <unordered_map>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>


using Actors = std::vector<std::unique_ptr<Actor>>; // Contains all the actors in the current simulation


class Engine {

	static const KeyNames s_keyNames;
	static const ActionNames s_actionNames;

	// State of the simulation engine
	enum class State {
		INIT,
		PAUSED,
		RUNNING
	};



	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	sf::Text m_guiText;
	sf::View m_view;

	State m_state;
	unsigned m_fpsLimit;

	Actors  m_actors;

	KeyBindings m_keybindings;

	sf::Clock m_clock;
	sf::Time m_elapsed;

public:
	Engine(const sf::Vector2u& t_windowSize, const std::string& t_windowName);
	void init();
	void run(); // Contains the main loop


	void render();
	void update();
	void lateUpdate();
	const sf::RenderWindow& getWindow()const;
	sf::Time getElapsed()const;

private:
	void handleInput(sf::Keyboard::Key t_key, bool t_pressed);
	void processEvents(const float& t_dt);
	void handleInput(const sf::Keyboard::Key& t_key, const float&  s_dt, bool t_pressed);
	void render();
	
	Action Engine::getActionId(const std::string& t_actionName) {


	// Inout actions that can be queued by user inputs (real tim actions take in delta time)
	void Action_Pause();
	void Action_MoveViewLeft(float t_dt);
	void Action_MoveViewRight(float t_dt);
	void Action_MoveViewUp(float t_dt);
	void Action_MoveViewDown(float t_dt);
	void Action_ResetView();
	void Action_ZoomIn(float t_dt);
	void Action_ZoomOut(float t_dt);
	void Action_ResetZoom();
	void Action_Save();
	void Action_Quit();
};

#endif // ! ENGINE_H
