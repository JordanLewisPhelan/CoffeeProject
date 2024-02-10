/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps

	std::string fullTextEntry = testTextEntry();

	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible

		
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}

	if (sf::Keyboard::E == t_event.key.code && finishedTyping)
	{
		m_entryActive = true;
		finishedTyping = false;
	}

	if (sf::Keyboard::O == t_event.key.code && finishedTyping)
	{
		m_orderActive = true;
		finishedTyping = false;
	}

	if (sf::Keyboard::X == t_event.key.code && finishedTyping)
	{
		m_exitActive = true;
		finishedTyping = false;
	}

	if (sf::Keyboard::Space == t_event.key.code && !finishedTyping)
	{
		alternateTextSpeed();
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	if (m_entryActive)
	{
		drawTextEntry();
	}

	if (m_orderActive)
	{
		drawTextOrder();
	}

	if (m_exitActive)
	{
		drawTextExit();
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_window.draw(m_welcomeMessage);
	m_window.draw(m_logoSprite);


	m_window.draw(m_coffeeTextEntry);
	m_window.draw(m_coffeeTextOrder);
	m_window.draw(m_coffeeTextExit);

	// calls the remove text on displayed text
	if (finishedTyping)
	{
		removeText(displayedText, m_coffeeTextEntry);
		removeText(displayedText, m_coffeeTextOrder);
		removeText(displayedText, m_coffeeTextExit);
	}

	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	m_coffeeTextEntry.setFont(m_ArialBlackfont);
	m_coffeeTextEntry.setString("Default text");
	m_coffeeTextEntry.setPosition(50.0f, 350.0f);
	m_coffeeTextEntry.setCharacterSize(20U);
	m_coffeeTextEntry.setOutlineColor(sf::Color::White);
	m_coffeeTextEntry.setFillColor(sf::Color::Blue);
	m_coffeeTextEntry.setOutlineThickness(2.0f);

	m_coffeeTextOrder.setFont(m_ArialBlackfont);
	m_coffeeTextOrder.setString("Default text");
	m_coffeeTextOrder.setPosition(50.0f, 450.0f);
	m_coffeeTextOrder.setCharacterSize(20U);
	m_coffeeTextOrder.setOutlineColor(sf::Color::White);
	m_coffeeTextOrder.setFillColor(sf::Color::Blue);
	m_coffeeTextOrder.setOutlineThickness(2.0f);

	m_coffeeTextExit.setFont(m_ArialBlackfont);
	m_coffeeTextExit.setString("Default text");
	m_coffeeTextExit.setPosition(50.0f, 550.0f);
	m_coffeeTextExit.setCharacterSize(20U);
	m_coffeeTextExit.setOutlineColor(sf::Color::White);
	m_coffeeTextExit.setFillColor(sf::Color::Blue);
	m_coffeeTextExit.setOutlineThickness(2.0f);

	//	Initialized the coffee display text ^
	


	// Entry quote options here
	m_coffeeEntry.push_back("Hello There!");
	m_coffeeEntry.push_back("WHEW!! What a day, I need a coffee..");
	m_coffeeEntry.push_back("Ah my favourite coffee Shop in town.");
	
	// Order quote options here
	m_coffeeMiddle.push_back("Can I get a.. Cappuccino please?");
	m_coffeeMiddle.push_back("Hi, Latte when you can thank you!");
	m_coffeeMiddle.push_back("Heyy, can I get 2 shots of Espresso? NO ONE ISN'T ENOUGH!");
	m_coffeeMiddle.push_back("One Americano please, cream too please.");
	m_coffeeMiddle.push_back("Do you guys do Mochas by chance?");

	// Exit quote options here
	m_coffeeExit.push_back("Ahhhh, I needed that, see you soon guys!");
	m_coffeeExit.push_back("Oh no.. I am SO late for that meeting....");
	m_coffeeExit.push_back("Slan go foill!");
	m_coffeeExit.push_back("Thank you. *Whistling*");
}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	if (!m_logoTexture.loadFromFile("ASSETS\\IMAGES\\SFML-LOGO.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_logoSprite.setTexture(m_logoTexture);
	m_logoSprite.setPosition(100.0f, 180.0f);
}

// Text to be called when a customer Enters the shop
std::string Game::testTextEntry()
{
	std::string returnText;
	int random = rand() % m_coffeeEntry.size();
	
	returnText = m_coffeeEntry[random];

	return returnText;
}

// Text to be called when a customer makes an order
std::string Game::testTextMiddle()
{
	std::string returnText;
	int random = rand() % m_coffeeMiddle.size();

	returnText = m_coffeeMiddle[random];
	
	return returnText;
}

// text to be called upon a customer beginning to leave
std::string Game::testTextEnd()
{
	std::string returnText;
	int random = rand() % m_coffeeExit.size();

	returnText = m_coffeeExit[random];

	return returnText;
}


void Game::drawTextEntry()
{
	// prevents alteration of fulltext till its complete
	if (fullText == "")
	{
		fullText = testTextEntry();
	}
	
	// Check if there are characters left to display
	if (charIndexEntry < fullText.size())
	{
		if (textClock.getElapsedTime().asSeconds() >= typingSpeed)
		{
			displayedText += fullText[charIndexEntry];
			m_coffeeTextEntry.setString(displayedText);
			charIndexEntry++;
			textClock.restart();
		}
	}

	else if (charIndexEntry == fullText.size())
	{
		removeText(displayedText, m_coffeeTextEntry);
		if (displayedText == "")
		{
			setDefaults();
		}
	}
}


void Game::drawTextOrder()
{
	// Prevents alteration of FullText till its complete
	if (fullText == "")
	{
		fullText = testTextMiddle();
	}

	// Check if there are characters left to display
	if (charIndexOrder < fullText.size())
	{
		if (textClock.getElapsedTime().asSeconds() >= typingSpeed)
		{
			displayedText += fullText[charIndexOrder];
			m_coffeeTextOrder.setString(displayedText);
			charIndexOrder++;
			textClock.restart();
		}
	}

	else if (charIndexOrder == fullText.size())
	{
		removeText(displayedText, m_coffeeTextOrder);
		if (displayedText == "")
		{
			setDefaults();
		}
	}
}


void Game::drawTextExit()
{
	// Prevents fullText from changing quote until its done
	if (fullText == "")
	{
		fullText = testTextEnd();
	}

	// Check if there are characters left to display
	if (charIndexExit < fullText.size())
	{
		if (textClock.getElapsedTime().asSeconds() >= typingSpeed)
		{
			displayedText += fullText[charIndexExit];
			m_coffeeTextExit.setString(displayedText);
			charIndexExit++;
			textClock.restart();
		}
	}

	else if (charIndexExit == fullText.size())	// Sets flags to be inert or set to default
	{
		removeText(displayedText, m_coffeeTextExit);
		if (displayedText == "")	//checking if displayed text is empty
		{
			setDefaults();
		}
	}
}

// Changes text speed
void Game::alternateTextSpeed()
{
	if (typingSpeed == TYPE_SPEED_DEFAULT)
	{
		typingSpeed = TYPE_SPEED_INCREASED;
	}
}

// Removes the inputted text and its assosiated sf::Text after a set time has elapsed
void Game::removeText(std::string& t_quote, sf::Text& t_text)
{
	// Set the duration for text display
	sf::Time displayDuration = sf::seconds(5.0f); // Example: Text will be displayed for 5 seconds

	// Calculate the elapsed time since the text was displayed
	sf::Time elapsedTime = removalClock.getElapsedTime();

	// Check if the elapsed time exceeds the display duration
	if (elapsedTime >= displayDuration) {
		// If the elapsed time exceeds the duration, start removing characters gradually
		if (!t_quote.empty()) {
			t_quote.pop_back(); // Remove the last character from the displayed text
			t_text.setString(displayedText);
		}
		else
		{
			if (!textFullyRemoved)
			{
				if (charIndexExit == fullText.size() || charIndexEntry == fullText.size() ||
					charIndexOrder == fullText.size())
				{	// Sets flags to be inert or set to default
					setDefaults();
				}
			}
		}
	}
}

// intended to be used after a Quote is called and displayed
void Game::setDefaults()
{
	// Sets flags to be inert or set to default 
		displayedText = "";
		fullText = "";
		m_exitActive = false;
		m_entryActive = false;
		m_orderActive = false;
		finishedTyping = true;
		typingSpeed = TYPE_SPEED_DEFAULT;
		charIndexExit = 0;
		charIndexEntry = 0;
		charIndexOrder = 0;
		removalClock.restart();
	
}

