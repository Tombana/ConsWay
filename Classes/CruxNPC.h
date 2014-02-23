#include "CruxMap.h"
#include "CruxCommon.h"

using namespace Crux;

typedef enum NPCtype {
	HORSE,
	GREEDY,
	BFS,
	RANDOM,
	WALLBUG
};

class NPC {
	private:
	point pos;
	int type;
	
	public:
	void move(Map _mp, Pos2 target);			
	NPC(int _type, Pos2 _pos);
	~NPC();
}

