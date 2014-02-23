#include "CruxMap.h"
#include "CruxCommon.h"

using namespace Crux;

typedef enum {
	HORSE=1,
	GREEDY,
	BFS,
	RANDOM,
	WALLBUG
} NPCTYPE;

class NPC {
	private:
	Pos2 pos;
	NPCTYPE type;
	
	public:
	void move(Map* _mp, Pos2 target);			
	NPC(NPCTYPE _type, Pos2 _pos);
	int getType() const {return type;}
	Pos2 getPos() const {return pos;}
};

