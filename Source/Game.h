#pragma once
#include <iostream>
#include <vector>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Enemy.h"
#include "Projectile.h"
#include "TurretObject.h"
#include "Enums.h"
#include "HelperFunctions.h"
#include "Structs.h"
#include "ContentManager.h"
#include "PlayerTurretController.h"

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
	sf::Texture BackgroundTexture = ContentManager::GetInstance()->BackgroundTexture;
	sf::Sprite BackgroundPlate = HelperFunctions::ConstructSprite(BackgroundTexture);
	// Crosshair
	sf::Texture CrosshairTexture = ContentManager::GetInstance()->CrosshairTexture;
	sf::Sprite CrosshairSprite = HelperFunctions::ConstructSprite(CrosshairTexture);

	// Declare main player
	PlayerTurretController* PlayerController = nullptr;
	TurretObject* Player = nullptr;
	sf::Vector2f PlayerStartPosition;

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
	void InitPlayerStartPosition();
	void InitPlayerContoller();

	// Update methods
	void pollEvents();
	void SendDeltaTimeToEntities();
	void UpdateMousePositions();
	void UpdatePlayer();
	void UpdateProjectiles();
	void UpdateEnemies();
	void UpdateCursor();
	void UpdateText();
	void UpdateGameSessionState();

	// Rendering methods
	void RenderText();
	void RenderPlayer();
	void RenderEnemies();
	void RenderProjectiles();
	void RenderBackground();
	void RenderCursor();
	
	// Gameplay
	Enums::EnemyClass UpdateComplexityLevel();
	std::array<Enums::EnemyClass, 3> EnemyLevels = { Enums::EnemyClass::EASY, Enums::EnemyClass::MEDIUM, Enums::EnemyClass::HARD };
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
	float DeltaTime = 0.f;
	float GameTime = 0.f;
	const bool isRunning() const;

	// Methods
	void update();
	void RenderScene();
	void SpawmEnemy();
	void SpawnProjectile(const sf::Vector2f& StartPosition);
	void SpawnPlayer();
};

