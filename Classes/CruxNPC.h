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
	void move(map _mp, point target);			
	NPC(int _type, point _pos);
	~NPC();
}

