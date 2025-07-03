#include "Game.h"


void Game::InitGameSession()
{
    // Main function for start and game restart
    // Game logic
    this->GameLost = false;
    this->PauseGame = false;
    this->RenderPopUpText = false;
    this->LMBPressed = false;
    this->EnemySpawnTimerMax = 50.f;
    this->EnemySpawnTimer = 0.f; 
    this->MaxEnemies = 6;
    this->MissedEnemies = 0;
    this->UserLevelPoints = 0;
    this->CurrentUserLevel = 1;
    this->LevelMaxPoints = 200;
    this->EnemyIdCounter = 0;
    this->DeltaTime = 0.f;
    this->InitGameScene();
    this->InitText();
    this->InitPlayerStartPosition();
    // Send all data to game manager and after spawn main player
    this->InitGameDataManager();
    this->SpawnPlayer();
}


void Game::RestartGame()
{
    this->InitGameSession();
}


void Game::initWindow()
{
	this->VideoMode.size.x = 1280;
	this->VideoMode.size.y = 720;
	this->GameWindow = new sf::RenderWindow(VideoMode, "SFML works!");
    this->GameWindow->setFramerateLimit(this->Framerate);
    this->GameWindow->setMouseCursorVisible(false);
    this->WindowSize = static_cast<sf::Vector2f>(VideoMode.size);
}

void Game::InitWorldSize()
{
    this->WorldBoundsBias = { 300.f, 300.f };
    this->WorldBounds = static_cast<sf::Vector2f>(this->VideoMode.size) + WorldBoundsBias;
}


void Game::InitText()
{
    this->InfoString.setCharacterSize(20);
    this->InfoString.setFillColor(sf::Color::White);
    this->InfoString.setString("Hello this is test text");

    this->GamePopUpText.setCharacterSize(120);
}

void Game::InitBackground()
{
    sf::Vector2f ScreenCenter;
    ScreenCenter.x = this->VideoMode.size.x / 2.f;
    ScreenCenter.y = this->VideoMode.size.y / 2.f;

    //this->BackgroundPlate.setPosition(ScreenCenter);
    sf::Vector2u BackgroundSize = this->BackgroundTexture.getSize();
    sf::Vector2f ImageOrigin = static_cast<sf::Vector2f>(BackgroundSize);
    ImageOrigin.x = BackgroundSize.x / 2.f;
    ImageOrigin.y = BackgroundSize.y / 2.f;

    //this->BackgroundPlate.setScale(sf::Vector2f{ 0.3f, 0.3f });
    this->BackgroundPlate.setOrigin(ImageOrigin);
    this->BackgroundPlate.setPosition(ScreenCenter);
}

void Game::InitCursor()
{
    HelperFunctions::RecenterSprite(this->CrosshairTexture, this->CrosshairSprite);
    this->CrosshairSprite.setScale(sf::Vector2f{ 0.4f, 0.4f });

}

void Game::InitPlayerStartPosition()
{
    sf::Vector2f Position;
    Position.x = this->VideoMode.size.x * 0.5f;
    Position.y = this->VideoMode.size.y - 100.f;
    this->PlayerStartPosition = Position;
}

void Game::InitGameDataManager()
{
    /* Should be initialized as last function*/
    this->GameDataManager->WorldBounds = this->WorldBounds;
    this->GameDataManager->WindowSize = this->WindowSize;
    this->GameDataManager->PlayerStartPosition = this->PlayerStartPosition;
    this->GameDataManager->MousePositionView = this->MousePositionView;
    this->GameDataManager->GameScene = this->GameScene;
}


void Game::InitGameScene()
{
    if (this->GameScene == nullptr)
    {
        this->GameScene = new Scene(this->MaxEnemies, 30);
    }
    else
    {
        GameScene->ClearScene();
    }
}


const bool Game::isRunning() const
{
	return this->GameWindow->isOpen();
}


void Game::update()
{
    /*
        Game update every tick?
    */
    this->UpdateGameSessionState();
    this->pollEvents();
    this->UpdateCursor();
    this->UpdateMousePositions();
    this->UpdateText();
}


void Game::pollEvents()
{
    // Event polling
    while (const std::optional event = this->GameWindow->pollEvent())
    {
        const auto* keyPressed = event->getIf<sf::Event::KeyPressed>();
        if (event->is<sf::Event::Closed>())
        {
            GameWindow->close();
            break;
        }
        // Track keyboard
        else if (keyPressed)
        {
            if (keyPressed->code == sf::Keyboard::Key::Escape)
            {
                GameWindow->close();
                break;
            }
            else if (keyPressed->code == sf::Keyboard::Key::R)
            {
                this->RestartGame();
            }
            else if (keyPressed->code == sf::Keyboard::Key::P)
            {
                if (this->PauseGame == false)
                {
                    this->PauseGame = true;
                }
                else
                {
                    this->PauseGame = false;
                }
            }
        }

        else if (const auto* LmbEvent = event->getIf<sf::Event::MouseButtonPressed>())
        {
            // Handle custom LMB events here
            //std::cout << "PRESSED" << std::endl;
            if (!this->PauseGame)
            {
                //this->SpawnProjectile(this->Player->GetPosition());
            }
        }
    }
}


void Game::UpdateMousePositions()
{
    this->MousePositionWindow = sf::Mouse::getPosition(*this->GameWindow);
    this->MousePositionView = this->GameWindow->mapPixelToCoords(this->MousePositionWindow);
}


void Game::UpdateScene()
{
    if (this->GameLost)
    {
        return;
    }
    this->GameScene->UpdateScene();
}


void Game::UpdatePlayer()
{
    this->MainPlayer->UpdateEntity();
    // Update text user points and level
    this->UserLevelPoints = this->MainPlayer->PlayerPoints;
    this->CurrentUserLevel = this->MainPlayer->PlayerLevel;
    this->Health = this->MainPlayer->Health;

    // Update complexity
    if (this->MainPlayer->PlayerPoints >= LevelMaxPoints)
    {
        this->MainPlayer->PlayerPoints = 0;
        this->MainPlayer->PlayerLevel += 1;
        std::cout << "Current Level:" << this->CurrentUserLevel << "\n";
    }
}


void Game::SpawmEnemy()
{
    /*
        Spawns enemies and sets their positions to random random
        rand() return big numbers not from 0 to 1
    */
    
    // Notificate scene changed
    // Register Id
    this->EnemyIdCounter += 1;
    // Call enemy handler to define which level of enemy to spawn
    Enums::EnemyClass EnemyLevel = this->UpdateComplexityLevel();
    // Construct enemy
    Enemy* NewEnemy = new Enemy(EnemyLevel);
    NewEnemy->MainPlayer = this->MainPlayer;
    NewEnemy->EnemyId = this->EnemyIdCounter;
    const sf::RectangleShape* EnemyRectangleShape = NewEnemy->GetCollisionShape();

    sf::Vector2f RandomPosition = { static_cast<float>(rand() % static_cast<int>(this->GameWindow->getSize().x - EnemyRectangleShape->getSize().x)), 
                                    -EnemyRectangleShape->getSize().y };

    NewEnemy->ForceSetPosition(RandomPosition);
}


void Game::SpawnPlayer()
{
    if (this->MainPlayer == nullptr)
    {
        this->MainPlayer = new Player();
    }
    else
    {
        this->MainPlayer->InitVariables();
    }

}


void Game::HandleEnemyCounts()
{
    // Track enemies count
    EnemyCount = this->GameScene->GetCountByClassName("Enemy");
    if (this->EnemyCount < this->MaxEnemies)
    {
        if (this->EnemySpawnTimer >= this->EnemySpawnTimerMax)
        {
            this->SpawmEnemy();
            this->EnemySpawnTimer = 0.f;
        }
        else
        {
            this->EnemySpawnTimer += 1.f;
        }
    }
}


Enums::EnemyClass Game::UpdateComplexityLevel()
{
    std::array<float, 3> CurrentWeights; 
    switch (this->CurrentUserLevel) 
    {
    case 1:
        CurrentWeights = this->EnemyLevelBalance.Level1;
        break;
    case 2:
        CurrentWeights = this->EnemyLevelBalance.Level2;
        break;
    case 3:
        CurrentWeights = this->EnemyLevelBalance.Level3;
        break;
    case 4:
        CurrentWeights = this->EnemyLevelBalance.Level4;
        break;
    default:
        CurrentWeights = this->EnemyLevelBalance.Level4;
        break;
    }

    // Create sum of weights
    float WeightsSum = 0.f;
    for (float Weight : CurrentWeights)
    {
        WeightsSum += Weight;
    }
    
    // Get random value [0, weights_sum]
    const float Random = ((float)rand() / RAND_MAX) * WeightsSum;
    float WeightAccumulation = 0.f;

    for (unsigned i = 0; i < CurrentWeights.size(); i++)
    {
        WeightAccumulation += CurrentWeights[i];
        if (WeightAccumulation >= Random)
        {
            return this->EnemyLevels[i];
        }
    }
    std::cout << "Can't find enemy level" << std::endl;
    return this->EnemyLevels[0];
}


void Game::UpdateCursor()
{
    this->CrosshairSprite.setPosition(this->MousePositionView);
}


void Game::UpdateText()
{
    std::string PlayerInfo = "Score: " + std::to_string(this->UserLevelPoints);
    this->InfoString.setString(PlayerInfo);
}


void Game::UpdateGameSessionState()
{
    // Handle gameplay update
    if (!this->GameLost && !this->PauseGame)
    {
        //this->UpdateEnemies();
        //this->UpdateProjectiles();
        this->HandleEnemyCounts();
        this->UpdateScene();
        
        this->UpdatePlayer();
        this->RenderPopUpText = false;
    }

    // Handle lost game
    if (this->Health <= 0)
    {
        this->GameLost = true;
        this->PauseGame = true;
        this->GamePopUpText.setString("You lost");
        this->GamePopUpText.setFillColor(sf::Color::Red);
        this->RenderPopUpText = true;
    }
    // Handle paused game
    else if (!this->GameLost && this->PauseGame)
    {
        this->GamePopUpText.setString("Paused");
        this->GamePopUpText.setFillColor(sf::Color::Blue);
        this->RenderPopUpText = true;
    }

    // Continue to update game data
    this->UpdateDataManager();
}


void Game::UpdateDataManager()
{
    // Mouse data to exchange manager
    GameDataManager->MousePositionView = this->MousePositionView;
    // Notify if window and world sizes changed?
    this->GameDataManager->WorldBounds = this->WorldBounds;
    this->GameDataManager->WindowSize = this->WindowSize;
}


/// 
/// Render zone
/// 
void Game::RenderText()
{
    this->GameWindow->draw(this->InfoString); 
    if (this->RenderPopUpText)
    {
        this->GameWindow->draw(this->GamePopUpText);
    }
    
}


void Game::RenderPlayer()
{
    this->GameWindow->draw(this->MainPlayer->PlayerTurret->BaseSprite);
    this->GameWindow->draw(this->MainPlayer->PlayerTurret->TurretSprite);
}
 

void Game::RenderEnemies()
{
    for (IEntity* CurrentEntity : this->GameScene->GetEntities())
    {
        if (CurrentEntity == nullptr)
        {
            continue;
        }
        // TODO make better renderer
        if (CurrentEntity->GetClassName() == "Enemy")
        {
            Enemy* AsEnemy = static_cast<Enemy*>(CurrentEntity);
            this->GameWindow->draw(AsEnemy->GetEnemySprite());
            if (AsEnemy->bDrawDebugCollision)
            {
                this->GameWindow->draw(*AsEnemy->GetCollisionShape());
            }
        }
    }
}


void Game::RenderProjectiles()
{
    for (IEntity* CurrentEntity : this->GameScene->GetEntities())
    {
        if (CurrentEntity == nullptr)
        {
            continue;
        }
        // TODO make better renderer
        if (CurrentEntity->GetClassName() == "Projectile")
        {
            Projectile* AsProjectile = static_cast<Projectile*>(CurrentEntity);
            this->GameWindow->draw(AsProjectile->Sprite);
            if (AsProjectile->bDrawDebugCollision)
            {
                this->GameWindow->draw(*AsProjectile->GetCollisionShape());
            }
        }
    }
}


void Game::RenderBackground()
{
    this->GameWindow->draw(this->BackgroundPlate);
}


void Game::RenderCursor()
{
    this->GameWindow->draw(this->CrosshairSprite);
}


void Game::RenderScene()
{
    /*
        - clear old frame
        - render objects
        - displace frame in window
    */

    this->GameWindow->clear();

    // Render background
    this->RenderBackground();
    
    // Draw game objects
    this->RenderPlayer();
    this->RenderEnemies();
    this->RenderProjectiles();

    // Draw ui last
    this->RenderText();

    // Render cursor
    this->RenderCursor();

    this->GameWindow->display();

}


// Constructor / Destructor
Game::Game()
{
    this->GameWindow = nullptr;
    this->initWindow();
    this->InitWorldSize();
    this->InitBackground();
    this->InitCursor();
    this->InitGameSession();
}


Game::~Game()
{
    delete this->MainPlayer;
    delete this->GameWindow;
    delete this->GameScene;
}
