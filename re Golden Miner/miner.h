#include"object.h"
extern IMAGE backups[40];
extern IMAGE all[30];
extern int distance(int x1, int y1, int x2, int y2);


class hook : public object 
{
	public:
		bool being;//是否抓住物体
		bool status;//是否出钩
		hook(int L = 50, int W = 30, int X = 525, int Y = 80, IMAGE* D = all+5,
			IMAGE* B = backups+30 , string M=""): 
			object(L,W,X,Y,D,B,M) {
			being = false; status = false;
		}
		void seize(List<gold>& mines) {
			for (int i = 0; i < mines.size; i++) {
				int d=distance(mines[i].xc, mines[i].yc, xc, yc);
				if (d <  length/2) {
					mines[i].being = true;
					being = true;
				}
			}
		}//抓住判断
		void release(List<gold>& mines,List<gold>& achieve) {
			if (!being) return;
			bool out=false;
			if (400 <= xc and xc <= 700 and yc <= 100) out = true;
			for (int i = 0; i < mines.size; i++) {
				if (out and mines[i].being) {
					if (achieve.size == 0)achieve.insert_as_front(mines[i]);
					else achieve.insert_succ(0, mines[i]);
					mines[i].dispair();
					mines.remove(i);
				}
			}
		}//储存
		void swing(int i,int dx ,int dy) {
			//rotateimage(display , all+5, 0.00001*(0.52 + fmod(0.01 * i, 2.12)), YELLOW, false, true);
			move(dx, dy);
		};
};

class miner
{
	public:
		hook hook;
		object human;
		miner() : hook(), human(100, 100, 500, 0, all + 4, (IMAGE*)0, "") {};
		void hooking() {
		}
		void show() {
			 human.show(); hook.show();
		}
};