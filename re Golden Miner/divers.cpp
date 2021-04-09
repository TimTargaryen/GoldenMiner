#include<bits/stdc++.h>
#include<graphics.h>
#include<conio.h>
#include"object.h"
#define ddl1 30000

using namespace std;

IMAGE all[30];
IMAGE backups[40];//全局图像
MOUSEMSG blank;//空白变量
int total_score;

void load() {
	loadimage(&(all[0]), _T("D:\\miner_pictures\\start.png"), 1280, 720);
	loadimage(&(all[1]), _T("D:\\miner_pictures\\startbottom2.png"), 200, 100);
	loadimage(&(all[2]), _T("D:\\miner_pictures\\level-background-0.jpg"), 1280, 720);
	loadimage(&(all[3]), _T("D:\\miner_pictures\\big_gold.png"), 60, 60);
	loadimage(&(all[4]), _T("D:\\miner_pictures\\char1.jpg"), 100, 100);
	loadimage(&(all[5]), _T("D:\\miner_pictures\\hook.bmp"), 50, 30);
	loadimage(&(all[6]), _T("D:\\miner_pictures\\char2.jpg"), 100, 100);
	loadimage(&(all[7]), _T("D:\\miner_pictures\\clear.png"), 1280, 720);
	loadimage(&(all[8]), _T("D:\\miner_pictures\\small_stone.jpg"), 40, 40);
	loadimage(&(all[9]), _T("D:\\miner_pictures\\char1_mask.jpg"), 100, 100);
	loadimage(&(all[10]), _T("D:\\miner_pictures\\char2_mask.jpg"), 100, 100);
	loadimage(&(all[11]), _T("D:\\miner_pictures\\diamond.png"), 30, 25);
	loadimage(&(all[12]), _T("D:\\miner_pictures\\diamond_mask.png"), 30, 25);
	loadimage(&(all[13]), _T("D:\\miner_pictures\\hook_mask.bmp"), 50, 30);
	loadimage(&(all[14]), _T("D:\\miner_pictures\\level-background-1.jpg"), 1280, 720);
	loadimage(&(all[15]), _T("D:\\miner_pictures\\small_gold.bmp"), 40, 40);
	loadimage(&(all[16]), _T("D:\\miner_pictures\\small_gold_mask.bmp"), 40, 40);
	loadimage(&(all[17]), _T("D:\\miner_pictures\\small_stone_mask.jpg"), 40, 40);
	loadimage(&(all[18]), _T("D:\\miner_pictures\\startbottom1.png"), 200, 100);
	loadimage(&(all[19]), _T("D:\\miner_pictures\\quit.png"), 200, 100);
	loadimage(&(all[20]), _T("D:\\miner_pictures\\stop.png"), 200, 100);
	loadimage(&(all[21]), _T("D:\\miner_pictures\\continue.png"), 200, 100);
	loadimage(&(all[22]), _T("D:\\miner_pictures\\panel.png"), 400, 500);
	loadimage(&(all[23]), _T("D:\\miner_pictures\\left.png"), 200, 100);
	loadimage(&(all[24]), _T("D:\\miner_pictures\\score.png"), 200, 100);
	loadimage(&(all[2]), _T("D:\\miner_pictures\\level-background-0.jpg"), 1280, 720);
}//图像加载函数

MOUSEMSG click() {
	MOUSEMSG m=blank;
	if (MouseHit()) m = GetMouseMsg();
	return m;
}//全局鼠标消息函数
void background(IMAGE* now) {
	putimage(0, 0, now);
}//背景函数
void exit() { exit(-1); }//重载exit
void enter() {
	Sleep(100);
	putimage(200, 350, all + 1);
	Sleep(100);
	cleardevice();
}//开始按钮的动画效果
TCHAR* s_t(string& words) {
	TCHAR wc[MAX_PATH];
	_stprintf_s(wc, MAX_PATH, _T("%S"), words.c_str());
	return wc;
}//字符格式转换
void start() {
	object start_button(200, 100, 200, 350, all + 18, backups);
	object quit_button(200, 100, 200, 550, all + 19, backups);
	initgraph(1280, 720);
	background(all);
	start_button.show();
	quit_button.show();
	while (true) {
		MOUSEMSG m = click();
		if (start_button.click(m, enter)) break;
		else quit_button.click(m, exit);
	}
	srand(time(0));
}//开始界面函数
int distance(int x1, int y1, int x2, int y2) {
	double d = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
	return (int)d;
}//距离计算函数

#include"List.h"
#include"gold.h"
#include"miner.h"
#include"counters.h"

void stop() {
	object panel(400, 500, 300, 200, all + 22, backups + 31);
	object continue_button(200, 100, 400, 300, all + 21, backups + 32);
	object quit_button(200, 100, 400, 500, all + 19, backups + 33);
	panel.show(); continue_button.show(); quit_button.show();
	while (true) {
		FlushBatchDraw();
		MOUSEMSG m = click();
		if (continue_button.click(m, cleardevice)) {
			FlushMouseMsgBuffer(); Sleep(100);  break;
		}
		else quit_button.click(m, exit);
	}
}//暂停函数
void show(List<gold>& mines, List<gold>& achieve,
	counter& cnt, miner& miner, object& stop_button) {
	background(all + 2);
	for (int i = 0; i < mines.size; i++) mines[i].show();
	miner.show(); cnt.show(); stop_button.show();
	line(525, 80, miner.hook.xc, miner.hook.yc);
}//图像刷新
void coord_update(List<gold>& mines,miner& miner,int dx,int dy) {
	for (int i = 0; i < mines.size; i++) if (mines[i].being) {
		mines[i].update(dx, dy); mines[i].move(0, 0);
	}
	miner.hook.update(dx, dy); miner.hook.move(0, 0);
}
void hooking(List<gold>& mines, List<gold>& achieve,
	counter& cnt, miner& miner, object& stop_button, long i, double angle) {
	int edge = false; miner.hook.status = true; bool back = false;
	while (!cnt.countdown(ddl1)) {
		Sleep(10); FlushBatchDraw();
		MOUSEMSG m = click(); cnt.get_time();
		show(mines, achieve, cnt, miner, stop_button); 
		if (stop_button.click(m, stop)) continue;
		
		int dx = (5 * cos(angle)); int dy = (5 * sin(angle));
		edge += (20 >= miner.hook.xc or miner.hook.xc >= 1000 or miner.hook.yc >= 700 or miner.hook.yc <= 100);
		
		miner.hook.seize(mines);
		if (edge) coord_update(mines, miner, pow(-1, edge) * dx, pow(-1, edge) * dy);
		else if (miner.hook.being) coord_update(mines, miner, -dx, -dy);
		else coord_update(mines, miner, dx, dy);
		
		for (int i = 0; i < mines.size; i++)
			if (450 <= mines[i].xc and mines[i].xc <= 650 and mines[i].yc <= 150) {
				miner.hook.release(mines, achieve); mines[i].being = false;
			}
		if (edge and 450 <= miner.hook.xc and miner.hook.xc <= 650 and miner.hook.yc <= 100) break;
		if (edge >= 2) break;
		if (!cnt.countdown(ddl1)) break;
	}
	miner.hook.being = false;
}
void process1() {
	List<gold> mines(20); List<gold> achieve(0);
	counter cnt; miner miner;
	object stop_button(200, 100, 1000, 500, all + 20, NULL, "");
	
	BeginBatchDraw(); cnt.correction();
	for (long i = 0 ; !cnt.countdown(ddl1) ; i++) {
		Sleep(1); FlushBatchDraw(); cnt.get_time();
		
		int hook_x = 520 + 50 * cos(0.52 + fmod(0.01 * i, 2.10));
		int hook_y = 80 + 50 * sin(0.52 + fmod(0.01 * i, 2.10));
		int hook_dx = hook_x - miner.hook.x; int hook_dy = hook_y - miner.hook.y;
		MOUSEMSG m = click();
		show(mines, achieve, cnt, miner, stop_button); 
		if(stop_button.click(m,stop)) continue;
		if (m.uMsg == WM_LBUTTONDOWN)
			hooking(mines, achieve, cnt, miner, stop_button, i, 0.52 + fmod((double)i, 2.62));
		else miner.hook.swing(i, hook_dx, hook_dy);
		cnt.countdown(achieve);  cnt.show();
	}
}//简单关卡
void process2() {
}//困难关卡
void cut() {
	object continue_button(); object end_button();

}//转场函数
int main() 
{
	load();
	start();
	process1();

	_getch();
	return 0;
}