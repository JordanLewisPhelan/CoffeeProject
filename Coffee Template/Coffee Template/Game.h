/// <summary>
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include <ctime>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	// These were used for debugging and displaying it on button press,
	// Simply add the calls used here, into the FSM function for each
	// state, i.e, ordering, Entering, Exiting
	void processEvents();
	void processKeys(sf::Event t_event);

	// Here just add as needed to the game, into the related functions
	void update(sf::Time t_deltaTime);
	void render();
	void setupSprite();

	// These are what is needed for the text to run
	void setupFontAndText();
	
	void drawTextEntry();
	void drawTextOrder();
	void drawTextExit();
	void alternateTextSpeed();
	void removeText(std::string&, sf::Text&);
	void setDefaults();
	// just for clarity these functions should be part of game as m_window is needed,
	// Alternatively add sf::RenderWindow& to the functions as needed
	void adaptTextBox(sf::Text& text);
	// These only need it as textBox needs it
	std::string testTextEntry();
	std::string testTextMiddle();
	std::string testTextEnd();


	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen


	sf::Clock removalClock;		//Clock to remove text after time has elapsed
	sf::Clock textClock;		//clock to help enforce a text speed


	sf::Text m_coffeeTextEntry;	//text used for Entry
	sf::Text m_coffeeTextOrder;	//text used for Order
	sf::Text m_coffeeTextExit;	//text used for Exit


	std::vector<std::string> m_coffeeEntry;		// Vector of possible quotes a customer can use upon Entry
	std::vector<std::string> m_coffeeMiddle;	// Vector of possible quotes a customer can use upon Ordering
	std::vector<std::string> m_coffeeExit;		// Vector of possible quotes a customer can use upon Exiting


	unsigned charIndexEntry = 0;					// current displayed character text limit
	unsigned charIndexOrder = 0;					// current displayed character text limit
	unsigned charIndexExit = 0;						// current displayed character text limit
	std::string displayedText = "";					// current displayed text
	std::string fullText = "";						// Will contain full text

	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game

	// Flags here used to check which if any should be called 
	bool m_entryActive = false;
	bool m_orderActive = false;
	bool m_exitActive = false;
	bool finishedTyping = true;
	bool textFullyRemoved = false;
	bool textBoxDisplayed = false;	// set to ensure that the shape only appears if the text is visible

	double const TYPE_SPEED_DEFAULT = 0.1;
	double const TYPE_SPEED_INCREASED = 0.001;
	double typingSpeed = 0.1; // Characters per second

};

#endif // !GAME_HPP

