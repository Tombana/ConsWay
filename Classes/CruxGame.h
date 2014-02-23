// 'Game' contains the main game logic, and references to the 
// players, npcs, the map etc. The update function should be
// called with an elapsed time, and the main game logic will
// largely be contained in this function.

#include "CruxMap.h"
#include "CruxCommon.h"
#include "CruxPlayer.h"

#include <string>
using std::string;

namespace Crux
{
    typedef enum 
    {
        IDLE = 1,
        PLAYER_TURN,
        NPC_TURN,
        PLAYER_LOST,
        PLAYER_WON,
    } STATE;

    class GameDelegate
    {
        public: 
            GameDelegate() {};
            virtual ~GameDelegate() {};

            virtual void gameUpdated() = 0;
    };

    class Game
    {
        public:
            Game();
            ~Game();

            // this initializes the game, including the 
            // map, player, start and end points, etc.
            bool initialize(GameDelegate*  _delegate, string mapConfiguration);

            // finishes the player turn
            void finishTurn();

            // returns the current game state
            STATE getGameState() { return gameState; };

            // moves the player and updates game logic, checking if
            // player is still valid
            void move(DIRECTION dir);

            // this finishes a turn, and lets the NPCs do their moves
            void finishPlayerTurn();

            // returns the map
            Map* getMap() const { return map; };

            const Player* getPlayer() const { return &player; }

        private:
            // perform npc moves
            void performNPCMoves();
            // updates the game (one step)
            void update();

            // checks if the player is on a legal square. Note
            // that this can be the final square, so this should
            // be called before checkFinalSquare
            void checkLegalSquare();

            // checks if the player reached the final square
            void checkFinalSquare();
            int finalx;
            int finaly;

            // action points (player) per turn:
            int apPerTurn;

            // finishes the game, reinitialize??
            void gameOver();

            // map variables
            Map* map;

            // this gets set to false if the game is paused, or over.
            STATE gameState;
            
            // player
            Player* player;

            // delegate
            GameDelegate* delegate;
    };
}
