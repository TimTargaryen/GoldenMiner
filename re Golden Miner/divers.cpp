#include<bits/stdc++.h>
#include<graphics.h>
#include<conio.h>
#define ddl1 30000
#define ddl2 20000

using namespace std;

IMAGE all[50];//全局图像
MOUSEMSG blank;//空白变量
int total_score=0;//分数
int barrel = 1;//炸药桶数目
int bomb = 1;//炸弹数目
int sand = 1;//沙漏数目
string name;//用户名
ifstream fin("./rank.txt");//文件流
ofstream fout("./rank.txt");//文件流
clock_t dt = 0;//时间差

void load() {
	loadimage(&(all[0]), _T("./miner_pictures/start.png"), 1280, 720);
	loadimage(&(all[1]), _T("./miner_pictures/startbottom2.png"), 200, 100);
	loadimage(&(all[2]), _T("./miner_pictures/level-background-0.jpg"), 1280, 720);
	loadimage(&(all[3]), _T("./miner_pictures/big_gold1.png"), 60, 60);
	loadimage(&(all[4]), _T("./miner_pictures/char1.jpg"), 100, 100);
	loadimage(&(all[5]), _T("./miner_pictures/hook.bmp"), 50, 30);
	loadimage(&(all[6]), _T("./miner_pictures/char2.jpg"), 100, 100);
	loadimage(&(all[7]), _T("./miner_pictures/clear.png"), 1280, 720);
	loadimage(&(all[8]), _T("./miner_pictures/small_stone.jpg"), 40, 40);
	loadimage(&(all[9]), _T("./miner_pictures/ranker.png"), 200, 100);
	loadimage(&(all[10]), _T("./miner_pictures/barrel.png"), 150, 200);
	loadimage(&(all[11]), _T("./miner_pictures/diamond.png"), 30, 25);
	loadimage(&(all[12]), _T("./miner_pictures/bakudan1.bmp"), 50, 100);
	loadimage(&(all[13]), _T("./miner_pictures/brick.png"), 120, 20);
	loadimage(&(all[14]), _T("./miner_pictures/level-background-1.jpg"), 1280, 720);
	loadimage(&(all[15]), _T("./miner_pictures/small_gold.bmp"), 40, 40);
	loadimage(&(all[16]), _T("./miner_pictures/bang_mask.png"), 100, 100);
	loadimage(&(all[17]), _T("./miner_pictures/sand.png"), 100, 100);
	loadimage(&(all[18]), _T("./miner_pictures/startbottom1.png"), 200, 100);
	loadimage(&(all[19]), _T("./miner_pictures/quit.png"), 200, 100);
	loadimage(&(all[20]), _T("./miner_pictures/stop.png"), 200, 100);
	loadimage(&(all[21]), _T("./miner_pictures/continue.png"), 200, 100);
	loadimage(&(all[22]), _T("./miner_pictures/panel.png"), 400, 500);
	loadimage(&(all[23]), _T("./miner_pictures/left.png"), 200, 100);
	loadimage(&(all[24]), _T("./miner_pictures/score.png"), 200, 100);
	loadimage(&(all[25]), _T("./miner_pictures/shop.png"), 1280, 720);
	loadimage(&(all[26]), _T("./miner_pictures/bang.png"), 100, 100);
	loadimage(&(all[27]), _T("./miner_pictures/ba.png"), 50, 50);
	loadimage(&(all[28]), _T("./miner_pictures/bo.png"), 50, 50);
	loadimage(&(all[29]), _T("./miner_pictures/sa.png"), 50, 50);
	loadimage(&(all[30]), _T("./miner_pictures/bakudan_mask.bmp"), 50, 100);
	loadimage(&(all[31]), _T("./miner_pictures/barrel_mask.png"), 150, 200);
	loadimage(&(all[32]), _T("./miner_pictures/big_gold_mask1.png"), 60, 60);
	loadimage(&(all[33]), _T("./miner_pictures/char1_mask.jpg"), 100, 100);
	loadimage(&(all[34]), _T("./miner_pictures/char2_mask.jpg"), 100, 100);
	loadimage(&(all[35]), _T("./miner_pictures/diamond_mask.png"), 30, 25);
	loadimage(&(all[36]), _T("./miner_pictures/hook_mask.bmp"), 50, 30);
	loadimage(&(all[37]), _T("./miner_pictures/small_gold_mask.bmp"), 40, 40);
	loadimage(&(all[38]), _T("./miner_pictures/small_stone_mask.jpg"), 40, 40);
	loadimage(&(all[39]), _T("./miner_pictures/sand1.png"), 100, 100);
}//图像加载函数
MOUSEMSG click() {
	MOUSEMSG m = blank;
	if (MouseHit()) m = GetMouseMsg();
	return m;
}//全局鼠标消息函数
void background(IMAGE* now) {
	putimage(0, 0, now);
}//背景函数
void exit() { exit(-1); }//重载exit
void enter() {
	Sleep(100);
	putimage(200, 300, all + 1);
	Sleep(100);
	cleardevice();
}//开始按钮的动画效果
TCHAR* s_t(string& words) {
	TCHAR wc[MAX_PATH];
	_stprintf_s(wc, MAX_PATH, _T("%S"), words.c_str());
	return wc;
}//字符格式转换
string t_s(TCHAR* STR) {
	int iLen = WideCharToMultiByte(CP_ACP, 0, STR, -1, NULL, 0, NULL, NULL);
	char* chRtn = new char[iLen * sizeof(char)];
	WideCharToMultiByte(CP_ACP, 0, STR, -1, chRtn, iLen, NULL, NULL);
	string str(chRtn);
	return str;
}//字符格式转换
int distance(int x1, int y1, int x2, int y2) {
	double d = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
	return (int)d;
}//距离计算函数

#include"object.h"
#include"List.h"
#include"gold.h"
#include"miner.h"
#include"counters.h"
#include"prop.h"

void ranker() {
	cleardevice();
	object continue_button(200, 100, 450, 600, all + 21);
	string temp; fin >> temp; 
	TCHAR* info = s_t(temp);
	while (true) {
		MOUSEMSG m = click(); FlushBatchDraw();
		background(all); continue_button.show();
		outtextxy(50, 450, info);
		if (continue_button.click(m, cleardevice)) break;
	}
}//排行榜函数
void start() {
	object start_button(200, 100, 200, 300, all + 18);
	object ranker_button(200, 100, 200, 450, all + 9);
	object quit_button(200, 100, 200, 600, all + 19);
	TCHAR name1[20];
	
	initgraph(1280, 720); background(all);
	start_button.show(); 
	quit_button.show(); 
	ranker_button.show();
	InputBox(name1, 20, L"Please enter you name", L"start", 0, 0, 0);
	name = t_s(name1); fout << name <<" : ";
	
	while (true) {
		MOUSEMSG m = click();
		if (start_button.click(m, enter)) break;
		else if (ranker_button.click(m, ranker)) break;
		else quit_button.click(m, exit);
	}
	srand(time(0));
}//开始界面函数
void stop() {
	object panel(400, 500, 300, 200, all + 22);
	object continue_button(200, 100, 400, 300, all + 21);
	object quit_button(200, 100, 400, 500, all + 19);
	clock_t t1 = clock();
	
	panel.show(); 
	continue_button.show(); 
	quit_button.show();
	while (true) {
		FlushBatchDraw(); 
		MOUSEMSG m = click();
		
		if (continue_button.click(m, cleardevice)) {
			FlushMouseMsgBuffer(); 
			Sleep(100);  break;
		}
		else quit_button.click(m, exit);
	}

	clock_t t2 = clock();
	dt = t2 - t1;
}//暂停函数
void show(List<gold>& mines, List<gold>& achieve, 
		  counter& cnt, miner& miner, object& stop_button,
		  prop& p1, prop& p2, prop& p3) {
	background(all + 2);
	for (int i = 0; i < mines.size; i++) mines[i].show();
	miner.show(); cnt.show(); stop_button.show();
	p1.message = to_string(barrel);
	p2.message = to_string(bomb);
	p3.message = to_string(sand);
	p1.show(0, 50); p2.show(0, 50); p3.show(0, 50);
	line(530, 80, miner.hook.xc, miner.hook.y);
}//图像刷新
void coord_update(List<gold>& mines, miner& miner, int dx, int dy) {
	for (int i = 0; i < mines.size; i++) 
		if (mines[i].being) mines[i].update(dx, dy); 
	miner.hook.update(dx, dy); 
}//座标更新
void bang(List<gold>& mines, List<gold>& achieve, counter& cnt, bool is) {
	for (int i = 0; i < mines.size; i++)
		if (mines[i].gender == 1) {
			putimage(mines[i].x-40, mines[i].y-50, all + 16, SRCAND);
			putimage(mines[i].x-40, mines[i].y-50, all + 26, SRCINVERT);
			FlushBatchDraw();
			achieve.insert_front(mines[i]);
			Sleep(300); cnt.deadline += 300;
			mines[i].being = false;
			mines.remove(i);
			if (is) break;
		}
}//炸药爆炸
void delay(List<gold>& mines, List<gold>& achieve, counter& cnt, bool is) {
	cnt.deadline += 15000; 
}//沙漏延时
void swing(List<gold>& mines, List<gold>& achieve,
		   counter& cnt, miner& miner, object& stop_button, 
		   int dx, int dy, prop& p1, prop& p2, prop& p3) {
	coord_update(mines, miner, dx, dy);
	show(mines, achieve, cnt, miner, stop_button, p1, p2, p3);
}//摇摆函数
void hooking(List<gold>& mines, List<gold>& achieve,
	         counter& cnt, miner& miner, object& stop_button, 
	         long i, double angle, prop& p1, prop& p2, prop& p3) {
	int edge = 0; 
	miner.hook.status = true; 
	bool back = false;

	while (!cnt.countdown()) {
		Sleep(10); FlushBatchDraw(); 
		MOUSEMSG m = click(); cnt.get_time();
		cnt.deadline += dt; dt = 0;
		
		show(mines, achieve, cnt, miner, stop_button, p1, p2, p3); 
		if ((cnt.now % 400) < 200) {
			putimage(500, 0, all + 34, SRCAND);
			putimage(500, 0, all + 6, SRCINVERT);
		}
		else {
			putimage(500, 0, all + 33, SRCAND);
			putimage(500, 0, all + 4, SRCINVERT);
		}
		line(530, 80, miner.hook.xc, miner.hook.y);
		
		int dx = (6 * cos(angle)); int dy = (6 * sin(angle));
		edge += (20 >= miner.hook.xc or miner.hook.xc >= 1000 
			     or miner.hook.yc >= 700 or miner.hook.yc <= 100);//触边次数公式

		if (stop_button.click(m, stop)) continue; 
		miner.hook.seize(mines);
		if (edge) coord_update(mines, miner, pow(-1, edge) * dx, pow(-1, edge) * dy);
		else if (miner.hook.being) coord_update(mines, miner, -dx, -dy);
		else coord_update(mines, miner, dx, dy);
		
		for (int i = 0; i < mines.size; i++)
			if (450 <= mines[i].xc and mines[i].xc <= 650 and mines[i].yc <= 150) 
				miner.hook.release(mines, achieve); 
		if (edge and 450 <= miner.hook.xc and 
			miner.hook.xc <= 650 and miner.hook.yc <= 100) break;
		if (edge >= 2) break; if (cnt.countdown()) break;
	}
	miner.hook.status = false;
}//挖矿函数
void process(bool hard) {
	if (hard) *(all + 2) = *(all + 14);
	long ddl;
	if (hard) ddl = ddl2;
	else ddl = ddl1;

	List<gold> mines(20); List<gold> achieve(0);
	counter cnt(ddl,total_score); miner miner;
	object stop_button(200, 100, 1000, 500, all + 20, NULL, "");
	prop p1(50, 50, 300, 0, all + 27, NULL, to_string(barrel));
	prop p2(50, 50, 400, 0, all + 28, NULL, to_string(bomb));
	prop p3(50, 50, 700, 0, all + 29, NULL, to_string(sand));
	
	BeginBatchDraw(); 
	cnt.correction();
	for (long i = 0; !cnt.countdown(); i++) {
		Sleep(1); FlushBatchDraw(); cnt.get_time();
		cnt.deadline += dt; dt = 0;
		
		double angle = (abs(0.26 + fmod(0.01 * i, 5.24) + 5.5 - fmod(0.01 * i, 5.24)) - 
			            abs(0.26 + fmod(0.01 * i, 5.24) - 5.5 + fmod(0.01 * i, 5.24))) / 2;//当前角度公式
		int hook_x = 530 + 50 * cos(angle); int hook_y = 80 + 50 * sin(angle);
		int hook_dx = hook_x - miner.hook.xc; int hook_dy = hook_y - miner.hook.yc;//当前位移改变量公式
		MOUSEMSG m = click();
		
		show(mines, achieve, cnt, miner, stop_button, p1, p2, p3);
		if (stop_button.click(m, stop)) continue;
		if (p1.click(m, mines, achieve, cnt, false, bang, barrel)) continue;
		if (p2.click(m, mines, achieve, cnt, true, bang, bomb)) continue;
		if (p3.click(m, mines, achieve, cnt, false, delay, sand)) continue;
		
		if (m.uMsg == WM_LBUTTONDOWN) {
			hooking(mines, achieve, cnt, miner, stop_button, i, angle, p1, p2, p3);
			miner.hook.status = true;
		}
		else swing(mines, achieve, cnt, miner, stop_button, hook_dx, hook_dy, p1, p2, p3);
		cnt.countdown(achieve);  
		cnt.show();
	}
	total_score += cnt.score;
}//关卡
void end() {
	counter cnt(3000); 
	cnt.correction();
	while (!cnt.countdown()) {
		FlushBatchDraw(); cnt.get_time(); 
		background(all + 7);
		
		settextstyle(40, 40, _T("宋体")); 
		settextcolor(YELLOW);
		string info = "SCORE:";
		string str_score = to_string(total_score);
		outtextxy(200, 450, s_t(info)); outtextxy(300, 550, s_t(str_score));
	}
	fout << total_score << "points" << endl;
	closegraph(); 
	fin.close(); fout.close();
	exit();
}//结尾函数
void buy1(){
	if (total_score < 100) return;
	total_score -= 100; 
	sand += 1;
}
void buy2() {
	if (total_score < 10) return;
	total_score -= 10; 
	bomb += 1;
}
void buy3() {
	if (total_score < 50) return;
	total_score -= 50; 
	barrel+= 1;
}
void cut() {
	object continue_button(200, 100, 300, 600, all + 21); 
	object end_button(200, 100, 600, 600, all + 19);
	object points_button(200, 100, 970, 100, all + 24, NULL, to_string(total_score));
	object sand_button(100, 100, 100, 430, all + 17, all+39, to_string(100));
	object bomb_button(40, 100, 350, 430, all + 12, all+30, to_string(10));
	object barrel_button(150, 200, 550, 330, all + 10, all+31, to_string(50));

	while (true) {
		MOUSEMSG m = click(); 
		
		FlushBatchDraw();
		background(all + 25); 
		continue_button.show(); 
		end_button.show(); 
		points_button.show(0,100);
		sand_button.show(0, 100); 
		barrel_button.show(40, 200);
		bomb_button.show(0, 100);
		
		if (continue_button.click(m, cleardevice)) break;
		else if (sand_button.click(m, buy1)) continue;
		else if (bomb_button.click(m, buy2)) continue;
		else if (barrel_button.click(m, buy3)) continue;
		else end_button.click(m, end);
		
		points_button.message = to_string(total_score);
	}
}//转场函数
int main()
{
	load();
	start();
	
	for (int i = 0; i < 6; i++) {
		if (i < 3) process(false);
		else process(true);
		if (i != 5) cut();
	}
	end();
	
	return 0;
}//驱动主函数