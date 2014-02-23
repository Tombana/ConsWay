#include <CruxNPC.h>

void move(Map _mp, Point target) {			
	switch type {
		case HORSE://Horses are greedy
			int bestSqDist=-1;
			int bestdx, bestdy;
			for(int dx=-2; dx<=2; dx++)
				for(int dy=-2; dy<=2; dy++) {
					if(dx*dx +dy*dy != 5) continue;
					Point jmp(pos.x+dx,pos.y+dy);
					char type=_mp.val(jmp.x,jpm.y);
					if(type == -1 || type == '*') continue;
					if(bestSqDist < 0 || target.sqdist(jmp) < bestSqDist) {
						
					}
				}
		break;
		case GREEDY:

		break;
		case BFS:

		break;
		case RANDOM:

		break;
		case WALLBUG:

		break;

	}
}

NPC(int _type, Point _pos) {
	type=_type;
	pos=_pos;
}

~NPC() {

}

