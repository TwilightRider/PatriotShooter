#include "Game.h"


void Game::InitGameSession()
{
    // Main function for start and game restart
    // Game logic
    this->GameLost = false;
    this->PauseGame = false;
    this->RenderPopUpText = false;
    this->LMBPressed = false;
    this->Health = 100;
    this->EnemySpawnTimerMax = 50.f;
    this->EnemySpawnTimer = 0.f; 
    this->MaxEnemies = 6;
    this->MissedEnemies = 0;
    this->UserLevelPoints = 0;
    this->CurrentUserLevel = 1;
    this->LevelMaxPoints = 200;
    this->EnemyIdCounter = 0;
    this->DeltaTime = 0.f;
    this->InitText();
    this->InitPlayerStartPosition();

    if (this->GameScene == nullptr)
    {
        this->GameScene = new Scene(this->MaxEnemies, 30);
    }
    else
    {
        GameScene->ClearScene();
    }
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
    delete this->Player;
    delete this->PlayerController;
	delete this->GameWindow;
    delete this->GameScene;
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


void Game::UpdateProjectiles()
{
    for (unsigned i = 0; i < this->GameScene->GetProjectiles().size(); i++)
    {
        Projectile* CurrentProjectile = this->GameScene->GetProjectiles()[i];
        CurrentProjectile->UpdateEntity();

        if (CurrentProjectile->bEntityHit || CurrentProjectile->GetEntityIsNeedToDestroy())
        {
            this->GameScene->RemoveFromScene(CurrentProjectile, i);
            delete CurrentProjectile;
        }
    }
}

void Game::UpdatePlayer()
{
    // Send data to player controller
    this->PlayerController->MousePosition = this->MousePositionView;
    this->PlayerController->GameScene = this->GameScene;
    this->PlayerController->WorldBounds = this->WorldBounds;
    this->PlayerController->DeltaTime = this->DeltaTime;
    this->PlayerController->UpdateMovement();

    this->Player->DeltaTime = this->DeltaTime;
    this->Player->UpdateEntity();
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
    NewEnemy->EnemyId = this->EnemyIdCounter;
    const sf::RectangleShape* EnemyRectangleShape = NewEnemy->GetCollisionShape();

    sf::Vector2f RandomPosition = { static_cast<float>(rand() % static_cast<int>(this->GameWindow->getSize().x - EnemyRectangleShape->getSize().x)), 
                                    -EnemyRectangleShape->getSize().y };

    NewEnemy->ForceSetPosition(RandomPosition);
    this->GameScene->AddObjectToScene(NewEnemy);
    //this->SendEnemiesToProjectiles();
}


void Game::SpawnPlayer()
{
    if (this->Player == nullptr)
    {
        this->Player = new TurretObject(this->PlayerStartPosition);
        this->Player->PosessedByPlayer = true;
    }
    else
    {
        this->Player->InitVariables();
        this->Player->ForceSetPosition(this->PlayerStartPosition);
    }

    if (this->PlayerController == nullptr)
    {
        this->PlayerController = new PlayerTurretController;
        
    }
    PlayerController->PlayerEntity = this->Player;
}


void Game::UpdateEnemies()
{
    /*
        Continuous function never stops
    */

    // Full stop enemy update if game lost
    if (this->GameLost)
    {
        return;
    }
    // Get ref to enemies here after deletion and spawn
    const std::vector<Enemy*>& Enemies = this->GameScene->GetEnemies();


    // Track if enemy has to be destroyed
    for (unsigned i = 0; i < Enemies.size(); i++)
    {
        Enemy* CurrentEnemy = Enemies[i];
        if (CurrentEnemy->GetEntityIsNeedToDestroy())
        {
            this->GameScene->RemoveFromScene(CurrentEnemy, i);
            delete CurrentEnemy;
            //this->SendEnemiesToProjectiles();
        }
    }

    // Track enemies count
    if (Enemies.size() < this->MaxEnemies)
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


    // Handle enemy hit
    for (unsigned i = 0; i < Enemies.size(); i++)
    {
        Enemy* CurrentEnemy = Enemies[i];
        if (!CurrentEnemy->bEntityHit)
        {
            continue;
        }
        // Register kill points
        this->UserLevelPoints += CurrentEnemy->KillReward;
        // Set pending removed
        CurrentEnemy->CallEntityDestruction();
        // Update complexity
        if (this->UserLevelPoints >= LevelMaxPoints)
        {
            // Increment level
            this->CurrentUserLevel += 1;
            // Reset level points
            this->UserLevelPoints = 0;
            
            std::cout << "Current Level:" << this->CurrentUserLevel << "\n";
        }
    }

    // Update entity here
    for (unsigned i = 0; i < Enemies.size(); i++)
    {
        // Get reference on enemy class
        Enemy* CurrentEnemyClass = Enemies[i];
        CurrentEnemyClass->UpdateEntity();
        // Get sf shape associated with class
        const sf::Sprite& EnemySprite = CurrentEnemyClass->GetEnemySprite();

        // if enemy is past the bottom
        if (EnemySprite.getPosition().y + CurrentEnemyClass->GetSize().y > this->GameWindow->getSize().y)
        {
            this->Health -= 5;
            this->MissedEnemies += 1;
            CurrentEnemyClass->CallEntityDestruction();
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
        this->UpdateEnemies();
        this->UpdateProjectiles();
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
    this->GameWindow->draw(this->Player->BaseSprite);
    this->GameWindow->draw(this->Player->TurretSprite);
}
 

void Game::RenderEnemies()
{
    for (Enemy* CurrentEnemy : this->GameScene->GetEnemies())
    {
        if (CurrentEnemy == nullptr)
        {
            continue;
        }
        this->GameWindow->draw(CurrentEnemy->GetEnemySprite());
        if (CurrentEnemy->bDrawDebugCollision)
        {
            this->GameWindow->draw(*CurrentEnemy->GetCollisionShape());
        }
    }
}


void Game::RenderProjectiles()
{
    for (Projectile* CurrentProjectile : this->GameScene->GetProjectiles())
    {
        if (CurrentProjectile == nullptr)
        {
            continue;
        }
        this->GameWindow->draw(CurrentProjectile->Sprite);
        if (CurrentProjectile->bDrawDebugCollision)
        {
            this->GameWindow->draw(*CurrentProjectile->GetCollisionShape());
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


