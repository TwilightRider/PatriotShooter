#include "Game.h"
#include <SFML/System/Clock.hpp>
#include "ContentManager.h"

#include "EntityManager.h"
#include "HelperFunctions.h"
#include "GameDataManager.h"


int main()
{
    // Create game instance
    Game game = {};

    // Initializa singletons
    ContentManager* ContentManager = ContentManager::GetInstance();
    EntityManager* EntityManager = EntityManager::GetInstance();
    GameDataManager* GameDataManager = GameDataManager::GetInstance();

    // Timers
    sf::Clock DeltaTimer;
    sf::Clock GameTime;
    float DeltaTime = 0.f;

    // Game Loop
    while (game.isRunning())
    {
        // Register Delta Seconds
        DeltaTime = DeltaTimer.getElapsedTime().asSeconds();
        DeltaTimer.restart();
        game.DeltaTime = DeltaTime; // check if we need it here
        game.GameTime = GameTime.getElapsedTime().asSeconds(); // Not implemented
        GameDataManager->DeltaTime = DeltaTime;
        //LOG("GameTime:", std::to_string(GameTime.getElapsedTime().asSeconds()) );
        // 
        // Update events
        game.update();

        // Render commands
        game.RenderScene();
        
    }

    // Game End
    return 0;
}
