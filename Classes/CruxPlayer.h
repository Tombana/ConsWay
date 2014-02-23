#include "CruxCommon.h"
#include "CruxAbility.h"
#include "CruxMap.h"

namespace Crux
{
    class Player
    {
        public:
            Player();
            ~Player();

            // initialize the player, maybe we want a player
            // configurationfile at some point
            void initialize();

            // this moves the player one square to the left,
            void move(DIRECTION dir, Map* map);

            // this makes the player use a certain ability, 
            // in a certain DIRECTION, and updates the players AP
            void useAbility(int id, DIRECTION dir);

            int getActionPoints() const { return actionPoints; }
            void setActionPoints(int _ap) { actionPoints = ap; }

            Point getPosition() const { return position };

        private:
            // A player has a certain amount of action points (AP)
            // per turn, this gets reset by the game
            int actionPoints;

            // A player has a certain amount of abilities, which can
            // be called by id (1, 2, 3, ...) by the game
            vector<Ability*> abilities;

            // the current position of the player is the grid point (tile)
            // it currently stands on
            Point position;
    };
}
