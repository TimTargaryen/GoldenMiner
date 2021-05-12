#include"object.h"

class prop : public object {
	public:
		prop(int L = 0, int W = 0, int X = 0, int Y = 0, IMAGE* D = NULL, IMAGE* B = NULL, string M = "")
			: object(L, W, X, Y, D, B, M) {};
		bool click(MOUSEMSG now, List<gold>& mines, List<gold>& achieve, counter& cnt, bool is,
				   void (*func)(List<gold>& mines, List<gold>& achieve, counter& cnt, bool is), int& n) {
			bool x_in = (x <= now.x and now.x <= x + length);
			bool y_in = (y <= now.y and now.y <= y + width);
			if (x_in and y_in and now.uMsg == WM_LBUTTONDOWN and n>0) {
				n-=1; func(mines, achieve, cnt, is); return true;
			}
			else return false;
		}
};
