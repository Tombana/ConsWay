#include "CruxNPC.h"
#include <vector>
#include <iostream>


void NPC::move(Map* _mp, Pos2 target) {	
	switch(type){
		case HORSE://Horses are greedy
			{
			int bestSqDist=-1;
			Pos2 bestJmp;
			for(int dx=-2; dx<=2; dx++)
				for(int dy=-2; dy<=2; dy++) {
					if(dx*dx +dy*dy != 5) continue;
					Pos2 jmp(pos.x+dx,pos.y+dy);
					char type=_mp->val(jmp.x,jmp.y);
					if(type == 0 || type == '*' || type == '#') continue;
					if(bestSqDist < 0 || target.sqdist(jmp) < bestSqDist) {
						bestSqDist=target.sqdist(jmp);
						bestJmp=jmp;
					}
				}
			if(bestSqDist == -1) return;
			pos=bestJmp;
			}
			break;
		case GREEDY:
			{
			int dx=target.x-pos.x,dy=target.y-pos.y;
			dx=(dx<0)-(dx>0);
			dy=(dy<0)-(dy>0);
			Pos2 walk=Pos2(pos.x+dx,pos.y+dy);

			char type=_mp->val(walk.x,walk.y);
			if(type == '*' || type == '#' || type == 0) return;
			pos=walk;
			}
			break;
		case BFS:
			{
			vector<vector<int> > visited(_mp->getWidth(),vector<int>(_mp->getHeight(),0));

			vector<Pos2> q;
			q.push_back(pos);
			bool first=false;
			while(!q.empty()) {
				Pos2 top=q.back();
				if(top.x == pos.x && top.y == pos.y) {
					int val=visited[top.x][top.y];
					int dx=val%2;
					int dy=val/2;
					pos=Pos2(pos.x+dx,pos.y+dy);
					return;
				}
				q.pop_back();
				for(int dx=-1; dx<2;dx++)
					for(int dy=-1; dy<2; dy++) {
						char type=_mp->val(pos.x+dx,pos.y+dy);
						if(type == 0 || type == '#' || type == '*') continue;
						if(visited[pos.x+dx][pos.y+dy]) continue;
						int dir=visited[pos.x][pos.y];
						if(first)
							dir=(dx+1)/2+(dy+1);
						visited[pos.x+dx][pos.y+dy]=dir;
					}
				first=false;
			}
			}
			break;
		case RANDOM:
			{
			Pos2 walk(pos.x+(random()%3-1),pos.y+(random()%3-1));
			char type=_mp->val(walk.x,walk.y);
			if(type == 0 || type == '*' || type == '#') return;
			pos=walk;
			}
			break;
		case WALLBUG:
			{
			for(int dx=-1;dx<2;dx++)
				for(int dy=-1;dy<2; dy++) {
					if(dx*dx+dy*dy != 2) continue;

				}
			}
			break;
		default:
			break;

	}
}

NPC::NPC(NPCTYPE _type, Pos2 _pos) {
	type=_type;
	pos=_pos;
}


