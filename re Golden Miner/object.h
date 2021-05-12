#ifndef OBJECT_H
#define OBJECT_H

using namespace std;

class object {
	public:
		int length; int width;//尺寸
		int x; int y;//生成坐标
		int xc; int yc;//中心坐标
		IMAGE* display;//对应图片
		IMAGE* backup;//遮罩
		string message;//文字显示
		object(int L = 0, int W = 0, int X = 0, int Y = 0, IMAGE* D = NULL, IMAGE* B = NULL, string M = "") {
			length = L; width = W;
			x = X; y = Y;
			xc = x + length / 2; yc = y + width / 2;
			display = D; backup = B; message = M;
		}//带参构造
		virtual void show(int dx = 0, int dy = 0, int sx = 40, int sy = 40) {
			if (backup == NULL) putimage(x, y, display);
			else {
				putimage(x, y, backup, SRCAND);
				putimage(x, y, display, SRCINVERT);
			}
			setbkmode(TRANSPARENT);
			settextstyle(sx, sy, _T("宋体"));
			settextcolor(YELLOW);
			outtextxy(x + dx, y + dy, s_t(message));
		}//展示信息
		virtual void update(int dx = 0, int dy = 0) {
			x += dx; y += dy; xc += dx; yc += dy;
		}//位置更新
		virtual bool click(MOUSEMSG now, void (*func)()) {
			bool x_in = (x <= now.x and now.x <= x + length);
			bool y_in = (y <= now.y and now.y <= y + width);
			if (x_in and y_in and now.uMsg == WM_LBUTTONDOWN) {
				func(); return true;
			}
			else return false;
		}//点击方法，接受一种触发结果,返回是否点击的判断
		~object() {}
};

#endif 