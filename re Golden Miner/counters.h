#include"object.h"

class counter
{
	public:
		object score_board;
		object time_board;
		clock_t now;
		clock_t zero_point;
		clock_t deadline;
		int score;
		counter(clock_t D=30000, int get=0): score_board(200,100,1000,100,all+24),
			time_board(200,100,1000,300,all+23 ) {
			now = 0; zero_point = 0; score = get; deadline = D;
		}
		void get_time() { now = clock(); }//更新时间
		void correction() { zero_point = clock(); }//零点校准
		bool countdown() {
			clock_t dt = now - zero_point;
			if (dt <= deadline) return false;
			else return true;
		}
		int countdown(List<gold>& achieve) {
			for (int i = 0; i < achieve.size; i++) 
				if (achieve[i].being) {
					switch (achieve[i].gender) {
					case 0:
						score += 50; break;
					case 1:
						score -= 10; break;
					case 2:
						score += 30; break;
					case 3:
						score += 100; break;
					}
					achieve[i].being = false;
				}
			return score;
		}//计分
		void show() {
			score_board.message = to_string(score);
			time_board.message = to_string((deadline-(now-zero_point))/1000);
			score_board.show(0,100); time_board.show(0,100);
		}
		~counter() {};
};