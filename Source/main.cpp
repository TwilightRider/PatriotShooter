#include "Game.h"
#include <SFML/System/Clock.hpp>
#include "ContentManager.h"
#include "EntityManager.h"
#include "HelperFunctions.h"


int main()
{
    // Create game instance
    Game game = {};
    // Initialize content manager singleton
    ContentManager* ContentManager = ContentManager::GetInstance();
    EntityManager* EntityManager = EntityManager::GetInstance();

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
        game.DeltaTime = DeltaTime;
        game.GameTime = GameTime.getElapsedTime().asSeconds();
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
