#pragma once
#include <iostream>
#include <vector>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Enemy.h"
#include "Enums.h"
#include "HelperFunctions.h"
#include "Projectile.h"
#include "Structs.h"
#include "ContentManager.h"

/*Game instance class*/

// add delta time add projectile life time or kill zone
class Game
{
private:
	sf::RenderWindow* GameWindow;
	sf::Vector2f WorldBounds;
	sf::Vector2f WorldBoundsBias;
	sf::VideoMode VideoMode;
	
	// Text
	std::vector<sf::Text> UiText;

	// Resources //
	sf::Font Font = HelperFunctions::LoadFont("./Fonts/times.ttf");
	// Main info string temp
	sf::Text InfoString = HelperFunctions::ConstructText(Font);
	sf::Text GamePopUpText = HelperFunctions::ConstructText(Font);

	//Background
	const sf::Texture BackgroundTexture = HelperFunctions::LoadImage("./Images/T_Background.png");
	sf::Sprite BackgroundPlate = HelperFunctions::ConstructSprite(BackgroundTexture);
	// Crosshair
	const sf::Texture CrosshairTexture = HelperFunctions::LoadImage("./Images/T_Crosshair.png");
	sf::Sprite CrosshairSprite = HelperFunctions::ConstructSprite(CrosshairTexture);

	// Scene container
	Structs::Scene* GameScene = nullptr;
	
	// Game logic
	float EnemySpawnTimer;
	float EnemySpawnTimerMax;
	unsigned UserLevelPoints;
	unsigned MissedEnemies;
	unsigned MaxMissedEnemies;
	unsigned MaxEnemies;
	unsigned LevelMaxPoints;
	unsigned CurrentUserLevel;
	unsigned EnemyIdCounter;
	unsigned MaxProjectiles;
	unsigned Health;
	unsigned HealthDecrementRate;
	bool LMBPressed;
	bool GameLost;
	bool RenderPopUpText;

	// Flow control
	void RestartGame();
	bool PauseGame;
	
	// Mouse position
	sf::Vector2i MousePositionWindow;
	sf::Vector2f MousePositionView;

	// TEMPORAL Populate enemies for projectiles
	void SendEnemiesToProjectiles();

	// Init methods
	void InitGameSession();
	void initWindow();
	void InitWorldSize();
	void InitText();
	void InitBackground();
	void InitCursor();

	// Update methods
	void pollEvents();
	void UpdateMousePositions();
	void UpdateProjectiles();
	void UpdateEnemies();
	void UpdateCursor();
	void UpdateGameSessionState();

	// Rendering methods
	void RenderText();
	void RenderEnemies();
	void RenderProjectiles();
	void RenderBackground();
	void RenderCursor();
	
	// Gameplay
	Enums::EnemyClass UpdateComplexityLevel();
	std::vector<Enums::EnemyClass> EnemyLevels = { Enums::EnemyClass::EASY, Enums::EnemyClass::MEDIUM, Enums::EnemyClass::HARD };
	// Enemy weights
	struct EnemyWeights {
		std::array<float, 3> Level1 = { 100.f, 0.f, 0.f };
		std::array<float, 3> Level2 = { 85.f, 15.f, 0.f };
		std::array<float, 3> Level3 = { 60.f, 25.f, 15.f };
		std::array<float, 3> Level4 = { 45.f, 25.f, 20.f };
	};
	// Declare enemy weights struct
	EnemyWeights EnemyLevelBalance;
	

public:
	// Constructors / Destructors
	Game();
	virtual ~Game();

	char Framerate = 60;
	const bool isRunning() const;

	// Methods
	void update();
	void RenderScene();
	void SpawmEnemy();
};

