#include"object.h"

class hook : public object {
	public:
		bool being;//是否抓住物体
		bool status;//是否出钩
		
		hook(int L = 50, int W = 30, int X = 530, int Y = 80, IMAGE* D = all + 5, IMAGE* B = all + 36, string M = "") :
			object(L, W, X, Y, D, B, M) {
			being = false; status = false;
		}
		void seize(List<gold>& mines) {
			for (int i = 0; i < mines.size; i++) {
				int d=distance(mines[i].xc, mines[i].yc, xc, yc);
				if (d <= distance(mines[i].length/2,mines[i].width/2,0,0)) {
					mines[i].being = true; being = true;
				}
			}
		}//抓住判断
		void release(List<gold>& mines,List<gold>& achieve) {
			if (!being) return;
			bool out=false;
			if (400 <= xc and xc <= 700 and yc <= 100) out = true;
			for (int i = 0; i < mines.size; i++) 
				if (out and mines[i].being) {
					achieve.insert_front(mines[i]); 
					mines.remove(i);
					being = false;
				}
		}//储存
};
class miner{
	public:
		hook hook;
		object human;
		
		miner() : hook() , human(100, 100, 500, 0, all + 4, all+33, "") {};
		void show() { 
			human.show(); putimage(490, 100, all + 13);  hook.show();
		};
};