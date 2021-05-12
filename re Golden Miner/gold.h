
#include"object.h"

class gold: public object
{
	public:
		int gender;//种类
		bool being;//是否被抓到
		gold() {
			switch (rand() % 6) {
				case 0: 
					display = all + 3; length = 60; width = 60; gender = 0;
					backup = all + 32; break;//生成大金块
				case 1: 
					display = all + 8; length = 40; width = 40; gender = 1;
					backup = all + 38; break;//生成石头
				case 2: 
					display = all + 15; length = 40; width = 40; gender = 2;
					backup = all + 37; break;//生成小金块
				case 3: 
					display = all + 11; length = 30; width = 25; gender = 3;
					backup = all + 35; break;//生成钻石
				case 4: 
					display = all + 15; length = 40; width = 40; gender = 2;
					backup = all + 37; break;//生成小金块，概率加大
				case 5: 
					display = all + 8; length = 40; width = 40; gender = 1;
					backup = all + 38; break;//生成石头，概率加大
			};
			x = rand()%900; y = 150+rand()%500;
			xc = x + length / 2; yc = y + width / 2;
			being = false;
		}//带参构造
		~gold() {};
};
