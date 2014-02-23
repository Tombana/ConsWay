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

            void initialize();

            int getActionPoints() const { return actionPoints; }
            void setActionPoints(int _ap) { actionPoints = ap; }

            // this moves the player one square to the left,
            void move(DIRECTION dir, Map* map);

            // this makes the player use a certain ability, 
            // in a certain DIRECTION
            void useAbility(int id, DIRECTION dir);

        private:
            int actionPoints;
            vector<Ability*> abilities;

            Point position;
    };
}
