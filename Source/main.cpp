#include "Game.h"
#include "ContentManager.h"


int main()
{
    // Create game instance
    Game game = {};
    // Initialize content manager singleton
    ContentManager* ContentManager = ContentManager::GetInstance();

    // Game Loop
    while (game.isRunning())
    {
        // Update events
        game.update();

        // Render commands
        game.RenderScene();
    }

    // Game End
    return 0;
}
