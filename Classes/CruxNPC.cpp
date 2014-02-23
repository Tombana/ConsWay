#include <CruxNPC.h>

void move(Map _mp, Pos2 target) {			
	switch type {
		case HORSE://Horses are greedy
			int bestSqDist=-1;
			Pos2 bestJmp;
			for(int dx=-2; dx<=2; dx++)
				for(int dy=-2; dy<=2; dy++) {
					if(dx*dx +dy*dy != 5) continue;
					Pos2 jmp(pos.x+dx,pos.y+dy);
					char type=_mp.val(jmp.x,jmp.y);
					if(type == -1 || type == '*') continue;
					if(bestSqDist < 0 || target.sqdist(jmp) < bestSqDist) {
						bestJmp=jmp;
					}
				}
			pos=bestJmp;
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

NPC(int _type, Pos2 _pos) {
	type=_type;
	pos=_pos;
}

~NPC() {

}

