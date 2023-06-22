#include<stdio.h>
#include<easyx.h>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<math.h>
#include <mmsystem.h>
#include <pthread.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "MSIMG32.LIB")
#define yes 1
#define no -1
#define Left -1
#define Right 1
#define Up -2
#define Down 2
#define stop 11
#define walk 12
#define run 13
#define jump 14
#define attack 15
#define beated 16
#define fall 17
#define rest 18
#define attack_commom 21
#define attack_kick 22
#define attack_jump 23
#define role 31
#define backimage 32
#define MAX_ENEMIES 100
#define near 41
#define approaching 42
#define far 43
IMAGE Backgroundimage1, Backgroundimage2;
IMAGE player_shadow, player_stop_right, player_stop_left, player_walk_left, player_walk_right, player_run_right, player_run_left, player_jump_right, player_jump_left, player_beated_right, player_beated_left;
IMAGE player_attack_common_right, player_attack_common_left, player_attack_Fly_kick_left, player_attack_Fly_kick_right, player_attack_jump_left, player_attack_jump_right, player_rest_left, player_rest_right;
IMAGE blood[11];
IMAGE yilong1, yilong2, leftw, rightw, bs, jineng, leftdao, rightdao;
IMAGE gogo;
IMAGE enemy_walk_left, enemy_walk_right, enemy_beated_right, enemy_beated_left, enemy_fall, enemy_stop_left, enemy_stop_right, enemy_fall_left, enemy_fall_right, enemy_run_right, enemy_run_left, enemy_attack_left, enemy_attack_right, enemy_rest_left, enemy_rest_right;
struct BGI1 {
	int x = 0;
	int y = 0;
	int px = 0;
	int py = 0;
	int scene = 1;
}bg1, bg2;
struct Rectangle {
	int top;    // 上边界
	int bottom; // 下边界
	int left;   // 左边界
	int right;  // 右边界

};
struct player {
	int x = 1600;
	int y = 280;
	int px = 0;
	int py = 0;
	int zy = 0;
	int life = 10;
	int direction = Right;//主角朝向
	int state = stop;
	int attacks = 0;
	int move = role;
	int limitx = no;
	int limity = no;
	int rest_time = 0;
	int is_attack=no;
	struct Rectangle rect;
}pp;
struct player1 {
	int x = 1800;
	int y = 280;
	int px = 0;
	int py = 0;
	int zy = 0;
	int life = 100;
	int direction = Right;//主角朝向
	int state = stop;
	int attacks = 0;
}pp1;
struct YI {
	int x = 0;
	int y = 100;
	int px = 0;
	int py = 0;
}yi1, yi2;
struct XG {
	int x = 0;
	int y = 100;
	int px = 0;
	int py = 0;
	int direction = Left;
	int number = 0;
}lt, rt;
struct XG1 {
	int x = 300;
	int y = 100;
	int px = 0;
	int py = 0;
	int number = 0;
}lt1, rt1;
struct BS {
	int x = 2050;
	int y = 230;
	int px = 0;
	int py = 0;
	int direction = Left;
	int number = 0;
}bos;
typedef struct enemy
{
	int life;
	int x;
	int y;
	int py;
	int px;
	int type;
	int directionx;
	int directiony;
	int initial;
	int state;
	int refresh;
	int live;
	int is_attack;
	struct Rectangle rect;
} enemy;
enemy enemies[10];
int numEnemies = 0;
bool Timer(int ms, int id) {	//ms是延迟时间，id是定时器的编号
	static DWORD t[10];
	if (clock() - t[id] > ms) {
		t[id] = clock();
		return true;
	}
	return false;
}
void HpSleep(int ms)// 精确延时函数(可以精确到 1ms，精度 ±1ms)
{
	static clock_t oldclock = clock();		// 静态变量，记录上一次 tick

	oldclock += ms * CLOCKS_PER_SEC / 1000;	// 更新 tick

	if (clock() > oldclock)					// 如果已经超时，无需延时
		oldclock = clock();
	else
		while (clock() < oldclock)			// 延时
			Sleep(1);						// 释放 CPU 控制权，降低 CPU 占用率，精度 10~16ms
}
void transparentimage(IMAGE* dstimg, int x, int y, int px, int py, int Width, int Height, IMAGE* srcimg, UINT transparentcolor) {
	//图片位置，图形在图片的位置，图形高宽
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	// 使用 Windows GDI 函数实现透明位图
	TransparentBlt(dstDC, x, y, Width, Height, srcDC, px, py, Width, Height, transparentcolor);
}
void player_image(int Width, int Height, int left_x_deviation, int left_y_deviation, int right_x_deviation, int right_y_deviation, IMAGE rp, IMAGE lp) {//图像宽高，左右方向图片，左图微调，右图微调（默认填0）
	if (pp.direction == Right) {
		transparentimage(NULL, pp.x + right_x_deviation, pp.y + right_y_deviation, pp.px, pp.py, Width, Height, &rp, BLACK);
	}
	else if (pp.direction == Left) {
		transparentimage(NULL, pp.x + left_x_deviation, pp.y + left_y_deviation, pp.px, pp.py, Width, Height, &lp, BLACK);
	}
}
void playanimation(int initial, int maxhight, int movespeed, int delay) {//图像在图片的当前默认填XX.py,角色动画，图片最大长度，每帧移动长度，延迟，【（0，0，0）为一张图】
	pp.py = initial;
	if (pp.py < maxhight && Timer(delay, 50)) {
		pp.py += movespeed;
	}
	if (pp.py >= maxhight) {
		pp.py = 0;
	}
}
void Enemyanimation(enemy* enemies, int initial, int maxhight, int movespeed, int delay, int id) {//图像在图片的当前默认填XX.py,角色动画，图片最大长度，每帧移动长度，延迟，【（0，0，0）为一张图】
	enemies->py = initial;
	if (enemies->py < maxhight && Timer(delay, id)) {
		enemies->py += movespeed;
	}
	if (enemies->py >= maxhight) {
		enemies->py = 0;
	}
}
void Enemy_image(enemy enemies, int width, int height, IMAGE rp, IMAGE lp) {//图像宽高，左右方向图片，
	if (enemies.directionx == Right) {
		transparentimage(NULL, enemies.x, enemies.y, enemies.px, enemies.py, width, height, &rp, BLACK);
	}
	else if (enemies.directionx == Left) {
		transparentimage(NULL, enemies.x, enemies.y, enemies.px, enemies.py, width, height, &lp, BLACK);
	}
}
void loading();
void initialize();
int Begin();
void Top_Bottom(int limittop, int limitbottom);
void Blood();
void Playermove();
void Playerm(int v1, int v2, int direction, char type);
void Playerattack();
void Playerjump();
void Playeraction();
void Background();
void Limitmove();
void Inputenemy();
void Enemy_Distance(enemy enemies);
void Enemy_AI(enemy* enemies, int state);
void Enemymove();
void Putenemy();
void Role_range();
void Attack(enemy* enemies);
void* Play_sound(void* args);
void* playBGM(void* args);
void* Shake(void* args);//震动
void Level();
int main() {
	bg2.y = 200;
	initgraph(1036, 544);
	loading();
	int gamebegain = 1;

	while (gamebegain == 1) {
		BeginBatchDraw();
		cleardevice();
		//transparentimage(NULL, 200, 200, 0, 0, 124, 152, &enemy_walk_left, BLACK);
		gamebegain = Begin();
		EndBatchDraw();
		HpSleep(1);
	}
	while (1) {
		BeginBatchDraw();
		cleardevice();
		Level();
		if (pp.state != beated)
		{
			Playermove();
		}
		Blood();
		Playeraction();
		EndBatchDraw();
		HpSleep(16);
	}
}
void loading() {
	loadimage(&Backgroundimage1, L"images/backgroundimage1.png");
	loadimage(&Backgroundimage2, L"images/backgroundimage2.png");
	loadimage(&player_stop_right, L"images/player/player-stop-right.png");
	loadimage(&player_stop_left, L"images/player/player-stop-left.png");
	loadimage(&player_walk_right, L"images/player/player-walk-right.png");
	loadimage(&player_walk_left, L"images/player/player-walk-left.png");
	loadimage(&player_run_right, L"images/player/player-run-right.png");
	loadimage(&player_run_left, L"images/player/player-run-left.png");
	loadimage(&player_shadow, L"images/player/shadow.png");
	loadimage(&player_jump_right, L"images/player/player-jump-right.png");
	loadimage(&player_jump_left, L"images/player/player-jump-left.png");
	loadimage(&player_attack_common_right, L"images/player/player-attack-common-right.png");
	loadimage(&player_attack_common_left, L"images/player/player-attack-common-left.png");
	loadimage(&player_attack_Fly_kick_left, L"images/player/player-attack-Fly-kick-left.png");
	loadimage(&player_attack_Fly_kick_right, L"images/player/player-attack-Fly-kick-right.png");
	loadimage(&player_attack_jump_right, L"images/player/player-attack-jump-right.png");
	loadimage(&player_attack_jump_left, L"images/player/player-attack-jump-left.png");
	loadimage(&player_rest_right, L"images/player/rest_right.png");
	loadimage(&player_rest_left, L"images/player/rest_left.png");
	loadimage(&player_beated_right, L"images/player/beated_right.png");
	loadimage(&player_beated_left, L"images/player/beated_left.png");
	loadimage(&blood[0], L"images/player/blood0.png");
	loadimage(&blood[1], L"images/player/blood1.png");
	loadimage(&blood[2], L"images/player/blood2.png");
	loadimage(&blood[3], L"images/player/blood3.png");
	loadimage(&blood[4], L"images/player/blood4.png");
	loadimage(&blood[5], L"images/player/blood5.png");
	loadimage(&blood[6], L"images/player/blood6.png");
	loadimage(&blood[7], L"images/player/blood7.png");
	loadimage(&blood[8], L"images/player/blood8.png");
	loadimage(&blood[9], L"images/player/blood9.png");
	loadimage(&blood[10], L"images/player/blood10.png");
	loadimage(&yilong1, L"images/kc/yi1.png");
	loadimage(&yilong2, L"images/kc/yi2.png");
	loadimage(&leftw, L"images/kc/leftw.png");
	loadimage(&rightw, L"images/kc/rightw.png");
	loadimage(&bs, L"images/kc/bs.png");
	loadimage(&jineng, L"images/kc/jineng.png");
	loadimage(&leftdao, L"images/kc/leftdao.png");
	loadimage(&rightdao, L"images/kc/rightdao.png");
	loadimage(&gogo, L"images/item/gogo.png");
	loadimage(&gogo, L"images/item/gogo.png");
	loadimage(&enemy_walk_left, L"images/enemy/walk_left.png");
	loadimage(&enemy_walk_right, L"images/enemy/walk_right.png");
	loadimage(&enemy_run_left, L"images/enemy/run_left.png");
	loadimage(&enemy_run_right, L"images/enemy/run_right.png");
	loadimage(&enemy_stop_right, L"images/enemy/stop_right.png");
	loadimage(&enemy_stop_left, L"images/enemy/stop_left.png");
	loadimage(&enemy_attack_right, L"images/enemy/attack_right.png");
	loadimage(&enemy_attack_left, L"images/enemy/attack_left.png");
	loadimage(&enemy_beated_right, L"images/enemy/beated_right.png");
	loadimage(&enemy_beated_left, L"images/enemy/beated_left.png");
	loadimage(&enemy_fall_left, L"images/enemy/fall_left.png");
	loadimage(&enemy_fall_right, L"images/enemy/fall_right.png");
	loadimage(&enemy_rest_left, L"images/enemy/rest_left.png");
	loadimage(&enemy_rest_right, L"images/enemy/rest_right.png");

}
int Begin() {
	int bg = 1;
	if (bg2.x >= -1520) {
		bg1.x -= 1;
		bg2.x -= 10;
		pp1.x -= 10;
	}
	transparentimage(NULL, bg1.x, bg1.y, 0, 0, 1336, 472, &Backgroundimage1, BLACK);
	transparentimage(NULL, bg2.x, bg2.y, bg2.px, bg2.py, 3319, 481, &Backgroundimage2, BLACK);
	transparentimage(NULL, pp1.x, pp1.y, pp1.px, pp1.py, 225, 170, &jineng, BLACK);
	transparentimage(NULL, pp1.x, pp1.y + 150, 0, 0, 75, 16, &player_shadow, BLACK);
	transparentimage(NULL, yi1.x, yi1.y, yi1.px, yi1.py, 195, 56, &yilong1, BLACK);
	transparentimage(NULL, yi2.x, yi2.y + 500, yi2.px, yi2.py, 195, 56, &yilong2, BLACK);
	if (yi1.x < 1300)
	{
		static int t1 = 1;
		yi1.x += 25;
		if (yi1.py >= 0 && Timer(150, 2))
		{
			yi1.py += 56 * t1;
		}
		if (yi1.py > 224)
		{
			t1 = -1;
			yi1.py += 56 * t1;
		}
	}
	if (yi2.x < 1300)
	{
		static int t2 = 1;
		yi2.x += 15;
		yi2.y -= 15;
		if (yi2.py >= 0 && Timer(150, 3))
		{
			yi2.py += 56 * t2;
		}
		if (yi2.py > 224)
		{
			t2 = -1;
			yi2.py += 56 * t2;
		}
	}
	transparentimage(NULL, lt.x - 780, lt.y + 150, lt.px, lt.py, 124, 152, &leftw, BLACK);
	transparentimage(NULL, lt.x - 850, lt.y + 200, lt.px, lt.py, 124, 152, &leftw, BLACK);
	transparentimage(NULL, lt.x - 780, lt.y + 230, lt.px, lt.py, 124, 152, &leftw, BLACK);
	if (lt.direction == Left)
	{
		lt.x += 4;
		if (lt.x > 500 && lt.py >= 0 && Timer(150, 4))
		{
			lt.py += 152;
		}
		else if (lt.py >= 912)
		{
			lt.py = 0;
		}
		if (lt.x > 850)
		{
			lt.direction = Right;
		}
	}

	transparentimage(NULL, rt.x + 1910, rt.y + 150, rt.px, rt.py, 124, 152, &rightw, BLACK);
	transparentimage(NULL, rt.x + 1980, rt.y + 200, rt.px, rt.py, 124, 152, &rightw, BLACK);
	transparentimage(NULL, rt.x + 1910, rt.y + 230, rt.px, rt.py, 124, 152, &rightw, BLACK);
	if (rt.direction == Left) {
		rt.x -= 10;
		if (rt.x < -1520)
		{
			rt.direction = Right;
		}
	}
	transparentimage(NULL, bos.x, bos.y, bos.px, bos.py, 170, 244, &bs, BLACK);
	if (bos.direction == Left) {
		bos.x -= 10;
		if (bos.x < 630)
		{
			bos.direction = Right;
		}
	}
	else
	{
		static int t3 = 1;
		if (lt.x >= 850)
		{
			if (bos.py >= 0 && Timer(200, 5))
			{
				t3 = 1;
				bos.x += 30;
				bos.py += 244 * t3;
				if (bos.py >= 732)
				{
					if (rt.x > -1650)
					{
						rt.x -= 10;
						lt.x += 30;
						if (rt.py < 1064 && Timer(25, 6))
						{
							rt.py += 152;
							lt.py += 152;
						}
					}
					if (bos.py >= 1952)
					{
						for (int i = 0; i < 4; i++)
						{
							t3 = -1;
							bos.py += 244 * t3;
							bos.number++;
						}

					}
				}
			}


		}
	}
	if (pp1.py >= 170)
	{
		transparentimage(NULL, lt1.x - 300, lt1.y + 150, lt1.px, lt1.py, 250, 120, &leftdao, BLACK);
		transparentimage(NULL, lt1.x - 350, lt1.y + 200, lt1.px, lt1.py, 250, 120, &leftdao, BLACK);
		transparentimage(NULL, lt1.x - 300, lt1.y + 230, lt1.px, lt1.py, 250, 120, &leftdao, BLACK);
		if (Timer(50, 8) && lt1.number == 0)
		{
			if (lt1.y > 0) {
				lt1.y -= 25;
				lt1.x -= 20;
			}
			else if (lt1.y == 0)
			{
				lt1.number++;
			}
		}
		else if (Timer(50, 9) && lt1.number == 1)
		{
			if (lt1.y < 140)
			{
				lt1.y += 20;
			}
			else if (lt1.y == 140)
			{
				lt1.number++;
			}
			lt1.py = 120;
		}
		else if (Timer(50, 10) && lt1.number == 2)
		{
			if (lt1.y > 100)
			{
				lt1.y -= 20;
			}
			else if (lt1.y == 100)
			{
				lt1.number++;
			}
			lt1.py = 240;
		}
		else if (Timer(50, 11) && lt1.number == 3)
		{
			if (lt1.y < 140)
			{
				lt1.y += 20;
			}
			else if (lt1.y == 140)
			{
				lt1.py = 360;
			}
		}
	}
	if (pp1.py >= 340)
	{
		transparentimage(NULL, rt1.x + 0, rt1.y + 150, rt1.px, rt1.py, 250, 120, &rightdao, BLACK);
		transparentimage(NULL, rt1.x + 0, rt1.y + 200, rt1.px, rt1.py, 250, 120, &rightdao, BLACK);
		transparentimage(NULL, rt1.x + 0, rt1.y + 230, rt1.px, rt1.py, 250, 120, &rightdao, BLACK);
		if (Timer(50, 12) && rt1.number == 0)
		{
			if (rt1.y > 0) {
				rt1.y -= 25;
				rt1.x += 20;
			}
			else if (rt1.y == 0)
			{
				rt1.number++;
			}
		}
		else if (Timer(50, 13) && rt1.number == 1)
		{
			if (rt1.y < 140)
			{
				rt1.y += 20;
			}
			else if (rt1.y == 140)
			{
				rt1.number++;
			}
			rt1.py = 120;
		}
		else if (Timer(50, 14) && rt1.number == 2)
		{
			if (rt1.y > 100)
			{
				rt1.y -= 20;
			}
			else if (rt1.y == 100)
			{
				rt1.number++;
			}
			rt1.py = 240;
		}
		else if (Timer(50, 15) && rt1.number == 3)
		{
			if (rt1.y < 140)
			{
				rt1.y += 20;
			}
			else if (rt1.y == 140)
			{
				rt1.py = 360;
			}
		}
	}
	if (pp1.py >= 0 && Timer(100, 7) && bos.number >= 3)
	{
		pp1.py += 170;
	}
	if (pp1.py > 1190)
	{
		pp.x = pp1.x;
		bg = 0;
	}
	return bg;
}
void Blood() {
	transparentimage(NULL, 0, 0, 0, 0, 258, 50, &blood[10-pp.life], BLACK);
	for (int i = 0; i < numEnemies; i++)
	{
		Attack(&enemies[i]);
	}
}
void Top_Bottom(int limittop, int limitbottom) {
	bool keyStateW = GetKeyState('W') < 0;
	bool keyStateS = GetKeyState('S') < 0;

	pp.limitx = (pp.x <= 0 && (GetKeyState('A') < 0 || pp.attacks == attack_kick)) ? yes : no;

	if ((pp.state != jump && ((pp.y <= limittop && keyStateW) || (pp.y >= limitbottom && keyStateS))) ||
		(pp.state == jump && ((pp.zy <= limittop && keyStateW) || (pp.zy >= limitbottom && keyStateS)))) {
		pp.limity = yes;
	}
	else {
		pp.limity = no;
	}
}
void Playermove() {
	Playerattack();
	Playerjump();
	if (pp.state != attack)
	{
		if (GetAsyncKeyState('A') & GetAsyncKeyState('D') & 0x8000) {
			if (pp.state != jump)
				pp.state = stop;
		}
		else if (GetKeyState('A') < 0) {
			Playerm(5, 10, Left, 'x');
		}
		else if (GetKeyState('D') < 0) {
			Playerm(5, 10, Right, 'x');
		}

		if (GetAsyncKeyState('W') & GetAsyncKeyState('S') & 0x8000) {
			if (pp.state != jump)
				pp.state = stop;
		}
		else if (GetAsyncKeyState('W') & 0x8000) {
			Playerm(5, 10, Up, 'y');
		}
		else if (GetAsyncKeyState('S') & 0x8000) {
			Playerm(5, 10, Down, 'y');
		}
	}
}
void Playerm(int v1, int v2, int direction, char type) {
	if (direction == Left || direction == Right) {
		pp.direction = direction;
	}
	switch (type) {
	case 'x':
		if (GetKeyState(VK_LSHIFT) & 0x8000) {
			if (pp.move == role && pp.limitx == no)
				pp.x += direction * v2;
			if (pp.state != jump)
				pp.state = run;
		}
		else {
			if (pp.move == role && pp.limitx == no)
				pp.x += direction * v1;
			if (pp.state != jump)
				pp.state = walk;
		}
		break;
	case 'y':
		if (GetKeyState(VK_LSHIFT) & 0x8000) {
			if (pp.state != jump) {
				if (pp.limity == no)
					pp.y += direction * v2 / 2;
				pp.state = run;
			}
			else if (pp.state == jump && pp.move == role && pp.limity == no) {
				pp.y += direction * v2 / 2;
				pp.zy += direction * v2 / 2;
			}
		}
		else {
			if (pp.state != jump) {
				if (pp.limity == no)
					pp.y += direction * v1 / 2;
				pp.state = walk;
			}
			else if (pp.state == jump && pp.move == role && pp.limity == no) {
				pp.y += direction * v1 / 2;
				pp.zy += direction * v1 / 2;
			}
		}
		break;
	default:
		break;
	}
}
void Playerattack() {
	int Rest_Interval = 100;
	static int t = 30, ax = 20, ay = 20, g = 1;
	static int isattack = no, isjump = no, j = 0, iscommonattack = no;
	static int attacking = no;
	if (pp.attacks == attack_commom && GetAsyncKeyState('J') & 0x8000) {
		iscommonattack = yes;
	}
	else  if (GetKeyState('J') >= 0) {
		iscommonattack = no;
	}
	if ((GetAsyncKeyState('J') & 0x8000 || pp.attacks != 0) && attacking == no) {
		if (isattack == no && pp.state != jump) {//只记录一次位
			pp.zy = pp.y;
			isattack = yes;
			pp.py = 0;
		}
		switch (pp.state) {//不同状态下的攻击模型
		case walk:
			pp.attacks = attack_commom;
			pp.state = attack;
			break;
		case stop:
			pp.attacks = attack_commom;
			pp.state = attack;
			break;
		case rest:
			pp.attacks = attack_commom;
			pp.state = attack;
			break;
		case run:
			pp.attacks = attack_kick;
			pp.state = attack;
			break;
		case jump:
			if (isjump == no) {//只记录一次位
				isjump = yes;
				pp.py = 0;
			}
			pp.attacks = attack_jump;
		default:
			break;
		}
	}
	else if (pp.state != jump) {
		pp.rest_time++;
		if (pp.rest_time <= Rest_Interval)
		{
			pp.state = stop;
		}
		else
		{
			pp.state = rest;
			if (pp.rest_time >= Rest_Interval + 75)
			{
				pp.rest_time = 0;
			}
		}
	}
	if (pp.state == attack || pp.state == jump) {
		switch (pp.attacks)
		{
		case attack_kick:

			if (g < t && Timer(25, 99)) {

				if (g <= t / 2) {
					pp.y -= t - g - t / 2;
				}
				else if (g <= t + 1) {
					pp.y += g - t / 2;
				}
				g++;

				switch (pp.direction)
				{
				case Left:
					if (pp.limitx == no) {
						pp.x -= ax;
					}
					break;
				case Right:
					if (pp.limitx == no && pp.move == role) {
						pp.x += ax;
					}
					break;
				default:
					break;

				}
			}
			if (g >= t) {//数据重置
				pp.attacks = 0;
				g = 1;
				isattack = no;
				attacking = no;
				pp.py = 0;
				pp.state = stop;
			}
			break;
		case attack_commom:
			if (j < 8) {
				j++;
			}
			else if (j >= 8 && iscommonattack == no) {//数据重置
				pp.attacks = 0;
				j = 0;
				attacking = no;
				pp.state = stop;
				isattack = no;
				pp.py = 0;
			}
			break;
		case attack_jump:
			if (pp.state != jump) {
				pp.state = stop;
				attacking = no;
				isjump = no;
				pp.py = 0;
			}
			break;
		default:
			break;
		}
	}
}
void Playerjump() {
	static int isjump = 0, g = 1, t = 40;

	if (GetAsyncKeyState('K') & 0x8000 && pp.state != jump && isjump == 0) {
		pp.zy = pp.y;
		pp.state = jump;
		isjump = 1;
		pp.py = 0;
	}
	else if (isjump == 1) {
		if (g <= t && Timer(25, 98)) {
			if (g <= t / 2) {
				if (g >= t / 4)
					pp.py = 180;
				pp.y -= t - g - t / 2;
			}
			else if (g > t / 2 && g <= t + 1) {
				pp.y += g - t / 2;
				if (g <= 3 * t / 4)
					pp.py = 360;
				else if (g >= 3 * t / 4)
					pp.py = 180;
			}
			g++;
		}
		else if (g > t) {
			isjump = 0;
			g = 0;
			pp.state = stop;
			pp.attacks = 0;
			pp.py = 0;
		}
	}
}
void Playeraction() {
	static int time_beated = 0;
	if (pp.state == beated)
	{
		time_beated++;
		if (time_beated >= 20)
		{
			pp.state = stop;
			time_beated = 0;
	}
	}
	if (pp.state == jump || pp.attacks == attack_kick) {
		transparentimage(NULL, pp.x + 20, pp.zy + 150, 0, 0, 75, 16, &player_shadow, BLACK);
	}
	else {
		transparentimage(NULL, pp.x + 20, pp.y + 150, 0, 0, 75, 16, &player_shadow, BLACK);
	}
	switch (pp.state)
	{
	case walk://走路
		playanimation(pp.py, 1600, 160, 50);
		player_image(110, 160, 0, 0, 0, 0, player_walk_right, player_walk_left);
		break;
	case stop://停止
		playanimation(pp.py, 0, 0, 0);
		player_image(98, 160, 0, 0, 0, 0, player_stop_right, player_stop_left);
		break;
	case run://跑步
		playanimation(pp.py, 1120, 160, 100);
		player_image(160, 150, -50, 0, 0, 0, player_run_right, player_run_left);
		break;
	case rest://休息
		playanimation(pp.py, 640, 160, 300);
		player_image(96, 160, 10, 0, 0, 0, player_rest_right, player_rest_left);
		break;
	case beated://受击
		playanimation(pp.py, 0, 0, 0);
		player_image(140, 150, 10, 0, 0, 0, player_beated_right, player_beated_left);
		break;
	case jump://跳跃
		if (pp.attacks == attack_jump) {
			playanimation(0, 0, 0, 0);
			player_image(235, 160, -20, 0, 0, 0, player_attack_jump_right, player_attack_jump_left);
		}
		else {
			playanimation(pp.py, 540, 0, 0);
			player_image(126, 180, 0, 0, 0, 0, player_jump_right, player_jump_left);
		}
		break;
	case attack://攻击
		switch (pp.attacks)
		{
		case attack_commom:
			playanimation(pp.py, 1078, 154, 100);
			player_image(232, 154, -130, 10, 0, 10, player_attack_common_right, player_attack_common_left);
			break;
		case attack_kick:
			playanimation(0, 0, 0, 0);
			player_image(125, 160, 0, 0, 0, 0, player_attack_Fly_kick_right, player_attack_Fly_kick_left);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	if (pp.state != stop && pp.state != rest)
	{
		pp.rest_time = 0;
	}
}
void Background() {
	int bgspeed = 5;
	bool isAttackKick = (pp.attacks == attack_kick);
	bool isKeyPressD = (GetKeyState('D') < 0);
	bool isKeyPressLShift = (GetKeyState(VK_LSHIFT) & 0x8000);

	if (pp.x >= 450 && bg2.scene == 1) {
		bg2.scene = 2;
	}

	if (pp.x >= 450 && bg2.scene == 2 && bg2.x >= -2150 && (isKeyPressD && pp.state != attack || isAttackKick)) {
		pp.move = backimage;
	}
	else {
		pp.move = role;
	}

	if ((isAttackKick || isKeyPressD) && pp.move == backimage && pp.direction == Right) {
		int bg2XSpeed = isKeyPressLShift || isAttackKick ? bgspeed * 2 : bgspeed;
		int bg2YSpeed = isKeyPressLShift || isAttackKick ? 5 : 2;

		bg2.x -= bg2XSpeed;
		bg1.x -= bgspeed / 10;
		for (int i = 0; i < numEnemies; i++)
		{
			enemies[i].x -= bg2XSpeed;
		}
		if (bg2.x >= -2150) {
			if (bg2.x < -1750 && bg2.x > -1930) {
				bg2.y -= bg2YSpeed;
				pp.y -= bg2YSpeed;
				pp.zy -= bg2YSpeed;
				for (int i = 0; i < numEnemies; i++)
				{
					enemies[i].y -= bg2YSpeed;
				}
			}
		}
		else {
			bg2.scene = 3;
		}
	}
	Limitmove();

}
void Limitmove() {
	const int TOP_LIMIT_DEFAULT = 210;
	const int BOTTOM_LIMIT_DEFAULT = 330;

	int topLimit = TOP_LIMIT_DEFAULT;
	int bottomLimit = BOTTOM_LIMIT_DEFAULT;

	switch (bg2.scene) {
	case 1:
		break;
	case 2:
		topLimit += (bg2.y - 200);
		bottomLimit += (bg2.y - 200);
		break;
	case 3:
		topLimit = 130;
		bottomLimit = 340;
		break;
	default:
		break;
	}

	Top_Bottom(topLimit, bottomLimit);

	if (bg2.scene == 2 && bg2.x < -1800) {
		if ((pp.state != jump && (pp.y <= topLimit && GetKeyState('W') < 0)) || ((pp.y >= bottomLimit - 0.46 * (bg2.y - 200)) && GetKeyState('S') < 0)) {
			pp.limity = yes;
		}
		else if ((pp.state == jump && (pp.zy <= topLimit && GetKeyState('W') < 0)) || ((pp.zy >= bottomLimit - 0.46 * (bg2.y - 200)) && GetKeyState('S') < 0)) {
			pp.limity = yes;
		}
		else if (pp.x > 500 - (-1800 - bg2.x)) {
			pp.limity = no;
		}
	}

	if (bg2.scene == 3) {
		if ((pp.state != jump && pp.y - 0.46 * pp.x < -50 && pp.attacks != attack_kick) || ((pp.state == jump || pp.attacks == attack_kick) && pp.zy - 0.46 * pp.x < -50)) {
			if (GetKeyState('D') < 0 || (pp.attacks == attack_kick && pp.direction == Right)) {
				pp.limitx = yes;
			}
			else if (GetKeyState('S') > 0) {
				pp.limitx = no;
			}

			if (GetKeyState('W') < 0) {
				pp.limity = yes;
			}
			else if (GetKeyState('S') > 0) {
				pp.limity = no;
			}
		}

		if ((pp.state != jump && pp.y - 0.46 * pp.x > 200 && pp.attacks != attack_kick) || ((pp.state == jump || pp.attacks == attack_kick) && pp.zy - 0.46 * pp.x > 200)) {
			if (GetKeyState('A') < 0 || (pp.attacks == attack_kick && pp.direction == Left)) {
				pp.limitx = yes;
			}
			else {
				pp.limitx = no;
			}

			if (GetKeyState('S') < 0) {
				pp.limity = yes;
			}
			else {
				pp.limity = no;
			}
		}
	}
}
void Inputenemy()
{
	static int ss = 1;
	if (bg2.scene == 1 && ss == 1)
	{
		enemies[numEnemies].x = 1000;
		enemies[numEnemies].y = 300;
		enemies[numEnemies].life = 100;
		enemies[numEnemies].type = 1;
		enemies[numEnemies].directionx = Left;
		enemies[numEnemies].directiony = Up;
		enemies[numEnemies].initial = 50;
		enemies[numEnemies].state = walk;
		enemies[numEnemies].refresh = 0;
		enemies[numEnemies].live = yes;
		enemies[numEnemies].is_attack = no;
		numEnemies++;
		ss = 2;
	}
	else if (bg2.scene == 2 && ss == 2)
	{
		enemies[numEnemies].x = 1000;
		enemies[numEnemies].y = 300;
		enemies[numEnemies].life = 100;
		enemies[numEnemies].type = 1;
		enemies[numEnemies].directionx = Left;
		enemies[numEnemies].directiony = Up;
		enemies[numEnemies].initial = 20;
		enemies[numEnemies].state = walk;
		enemies[numEnemies].refresh = 0;
		enemies[numEnemies].live = yes;
		enemies[numEnemies].is_attack = no;
		numEnemies++;
		enemies[numEnemies].x = -170;
		enemies[numEnemies].y = 300;
		enemies[numEnemies].life = 100;
		enemies[numEnemies].type = 1;
		enemies[numEnemies].directionx = Right;
		enemies[numEnemies].directiony = Down;
		enemies[numEnemies].initial = 20;
		enemies[numEnemies].state = walk;
		enemies[numEnemies].refresh = 0;
		enemies[numEnemies].live = yes;
		enemies[numEnemies].is_attack = no;
		numEnemies++;
		ss = 3;
	}
	else if (bg2.scene == 3 && ss == 3)
	{
		enemies[numEnemies].x = -200;
		enemies[numEnemies].y = 200;
		enemies[numEnemies].life = 100;
		enemies[numEnemies].type = 1;
		enemies[numEnemies].directionx = Right;
		enemies[numEnemies].directiony = Down;
		enemies[numEnemies].initial = 20;
		enemies[numEnemies].state = walk;
		enemies[numEnemies].refresh = 0;
		enemies[numEnemies].live = yes;
		enemies[numEnemies].is_attack = no;
		numEnemies++;
		enemies[numEnemies].x = -250;
		enemies[numEnemies].y = 250;
		enemies[numEnemies].life = 100;
		enemies[numEnemies].type = 1;
		enemies[numEnemies].directionx = Right;
		enemies[numEnemies].directiony = Down;
		enemies[numEnemies].initial = 20;
		enemies[numEnemies].state = walk;
		enemies[numEnemies].refresh = 0;
		enemies[numEnemies].live = yes;
		enemies[numEnemies].is_attack = no;
		numEnemies++;
		ss = 0;
	}
}
void Enemy_Distance(enemy* enemies, int distance_x, int distance_y, int distance)
{
	if (enemies->live == yes)
	{
		if (distance_x < 0)
		{
			enemies->directionx = Left;
		}
		else if (distance_x > 0)
		{
			enemies->directionx = Right;
		}
		if (distance_y < 0)
		{
			enemies->directiony = Up;
		}
		else if (distance_y > 0)
		{
			enemies->directiony = Down;
		}
		if (distance <= 100)
		{
			Enemy_AI(enemies, near);

		}
		else if (distance <= 500)
		{
			Enemy_AI(enemies, approaching);
		}
		else if (distance >= 500)
		{
			Enemy_AI(enemies, far);
		}
	}
}
void Enemy_AI(enemy* enemies, int state)
{
	static int random_num = 0;
	if (enemies->refresh >= 35 && enemies->life > 0 && enemies->live == yes)
	{
		random_num++;
		enemies->py = 0;
		srand(time(0) + random_num); // 初始化随机数生成器
		int random = rand() % 10;
		switch (state)//根据敌人与玩家的距离以及不同状态的权重更新敌人状态
		{
		case far:
			if (random < 3) {
				enemies->state = rest;
			}
			else if (random < 5) {
				enemies->state = walk;
			}
			else if (random < 10) {
				enemies->state = run;
			}
			break;
		case approaching:
			if (random < 2)
			{
				enemies->state = stop;
			}
			else if (random < 4) {
				enemies->state = rest;
			}
			else if (random < 10) {
				enemies->state = walk;
			}
			break;
		case near:
			if (random < 2)
			{
				enemies->state = stop;
			}
			else if (random < 5)
			{
				enemies->state = attack;
			}
			else if (random < 7) {
				enemies->state = rest;
			}
			else if (random < 10) {
				enemies->state = walk;
			}

			break;
		default:
			break;
		}
		enemies->refresh = 0;
	}
	else if (enemies->life <= 0 && enemies->live == yes)
	{
		if (enemies->live == yes)
		{
			enemies->py = 0;
			enemies->live = no;
		}
		enemies->state = fall;
	}
	enemies->refresh++;
}
void Enemymove()
{
	for (int i = 0; i < numEnemies; i++)
	{
		int distance_y;
		int distance_x = (int)(pp.x - enemies[i].x);
		if (pp.state == jump || pp.attacks == attack_kick)
		{
			distance_y = (int)(pp.zy - enemies[i].y);
		}
		else
		{
			distance_y = (int)(pp.y - enemies[i].y);
		}
		int distance = (int)sqrt(pow(distance_x, 2) + pow(distance_y, 2));
		if (enemies[i].initial >= 0)
		{
			enemies[i].state = run;
			enemies[i].initial--;
			if (enemies[i].initial <= 0)
			{
				enemies[i].py = 0;
			}
		}
		else
		{
			Enemy_Distance(&enemies[i], distance_x, distance_y, distance);
		}
		switch (enemies[i].state)
		{
		case stop:
			break;
		case run:
			enemies[i].x += enemies[i].directionx * 5;
			break;
		case walk:
			if (abs(distance_x) >= 80)
			{
				enemies[i].x += enemies[i].directionx * 1;
			}
			if (abs(distance_y) >= 20 && abs(distance_x) <= 300)
			{
				enemies[i].y += enemies[i].directiony * 1;
			}
			break;
		case beated:
			break;
		case fall:
			if (enemies[i].py <= 240)
			{
				if (bg2.scene == 3 && enemies[i].y - 0.46 * enemies[i].x < -30)
				{

				}
				else
				{
					if (enemies[i].py == 0 || enemies[i].py == 240)
					{
						enemies[i].x -= 2 * enemies[i].directionx;
					}
				}
			}
			break;
		default:
			break;
		}
	
	}
}
void Putenemy()
{

	for (int i = 0; i < numEnemies; i++)
	{
		int Offset = 0;
		switch (enemies[i].state)
		{
		case stop:
			Enemyanimation(&enemies[i], 0, 0, 0, 0, i);
			Enemy_image(enemies[i], 124, 152, enemy_stop_right, enemy_stop_left);
			break;
		case walk:
			Enemyanimation(&enemies[i], enemies[i].py, 1064, 152, 100, i);
			Enemy_image(enemies[i], 124, 152, enemy_walk_right, enemy_walk_left);
			break;
		case run:
			Enemyanimation(&enemies[i], enemies[i].py, 852, 142, 100, i);
			Enemy_image(enemies[i], 172, 142, enemy_run_right, enemy_run_left);
			break;
		case beated:
			Enemyanimation(&enemies[i], 0, 0, 0, 0, i);
			Enemy_image(enemies[i], 128, 152, enemy_beated_right, enemy_beated_left);
			break;
		case attack:
			Enemyanimation(&enemies[i], 0, 0, 0, 0, i);
			Enemy_image(enemies[i], 192, 150, enemy_attack_right, enemy_attack_left);
			break;
		case fall:
			if (enemies[i].py == 120 || enemies[i].py == 360)
			{
				Offset = 50;
			}
			if (enemies[i].py <= 240)
			{
				Enemyanimation(&enemies[i], enemies[i].py, 480, 120, 200, i);
			}
			if (enemies[i].directionx == Right) {
				transparentimage(NULL, enemies[i].x, enemies[i].y + Offset, enemies[i].px, enemies[i].py, 250, 120, &enemy_fall_right, BLACK);
			}
			else if (enemies[i].directionx == Left) {
				transparentimage(NULL, enemies[i].x, enemies[i].y + Offset, enemies[i].px, enemies[i].py, 250, 120, &enemy_fall_left, BLACK);
			}
			break;
		case rest:
			Enemyanimation(&enemies[i], enemies[i].py, 750, 150, 75, i);
			Enemy_image(enemies[i], 122, 150, enemy_rest_right, enemy_rest_left);
			break;
		default:
			Enemyanimation(&enemies[i], 0, 0, 0, 0, i);
			Enemy_image(enemies[i], 124, 152, enemy_stop_right, enemy_stop_left);
			break;
		}
	}
}
void Role_range()
{
	pp.rect.top = pp.y;
	pp.rect.bottom = pp.y + 80;
	pp.rect.left = pp.x;
	pp.rect.right = pp.x + 100;

	for (int i = 0; i < numEnemies; i++)
	{
		enemies[i].rect.top = enemies[i].y;
		enemies[i].rect.bottom = enemies[i].y + 80;
		enemies[i].rect.left = enemies[i].x;
		enemies[i].rect.right = enemies[i].x + 124;

	}
}
void Attack(enemy* enemies)
{
	Role_range();
	struct Rectangle pp_attack;
	struct Rectangle enemies_attack;
	if ((pp.state == attack || (pp.state == jump && pp.attacks == attack_jump)))
	{
		pp.is_attack == yes;
		switch (pp.attacks)
		{
		case attack_commom:
			if (pp.direction == Right)
			{
				pp_attack = {
				pp.rect.top + 10,
				pp.rect.top + 30,
				pp.rect.right ,
				pp.rect.right + 80
				};
			}
			else if (pp.direction == Left)
			{
				pp_attack = {
				pp.rect.top + 10,
				pp.rect.top + 30,
				pp.rect.left - 80,
				pp.rect.left
				};
			}
			if ((pp.py / 154) % 2 == 1)
			{
				if (pp_attack.top <= enemies->rect.bottom && pp_attack.bottom >= enemies->rect.top && pp_attack.left <= enemies->rect.right && pp_attack.right >= enemies->rect.left)
				{

					if (enemies->live == yes)
					{
						enemies->state = beated;
						enemies->life--;
					}
				}
			}
			break;
		case attack_jump:
			if (pp.direction == Right)
			{
				pp_attack = {
				pp.rect.top + 60,
				pp.rect.top + 90,
				pp.rect.right ,
				pp.rect.right + 50
				};
			}
			else if (pp.direction == Left)
			{
				pp_attack = {
				pp.rect.top + 60,
				pp.rect.top + 90,
				pp.rect.left - 50,
				pp.rect.left
				};
			}
			if (pp_attack.top <= enemies->rect.bottom && pp_attack.bottom >= enemies->rect.top && pp_attack.left <= enemies->rect.right && pp_attack.right >= enemies->rect.left)
			{

				if (enemies->live == yes)
				{
					enemies->state = beated;
					enemies->life--;
				}
			}
			break;
		case attack_kick:
			if (pp.direction == Right)
			{
				pp_attack = {
				pp.rect.top + 80,
				pp.rect.top + 100,
				pp.rect.right ,
				pp.rect.right + 50
				};
			}
			else if (pp.direction == Left)
			{
				pp_attack = {
				pp.rect.top + 80,
				pp.rect.top + 100,
				pp.rect.left - 50,
				pp.rect.left
				};
			}
			if (pp_attack.top <= enemies->rect.bottom && pp_attack.bottom >= enemies->rect.top && pp_attack.left <= enemies->rect.right && pp_attack.right >= enemies->rect.left)
			{

				if (enemies->live == yes)
				{
					enemies->state = beated;
					enemies->life--;
				}
			}
			break;
		default:
			break;
		}
	}
	if (enemies->state == attack && enemies->is_attack == no)
	{
		if (enemies->directionx == Right)
		{
			enemies_attack = {
				enemies->rect.top + 10,
				enemies->rect.top + 30,
				enemies->rect.right,
				enemies->rect.right + 50
			};
		}
		else if (enemies->directionx == Left)
		{
			enemies_attack = {
				enemies->rect.top + 10,
				enemies->rect.top + 30,
				enemies->rect.left - 50,
				enemies->rect.left
			};
		}
		if (enemies_attack.top <= pp.rect.bottom && enemies_attack.bottom >= pp.rect.top && enemies_attack.left <= pp.rect.right && enemies_attack.right >= pp.rect.left)
		{
			pp.state = beated;
			pp.life--;
		}
		enemies->is_attack = yes;
	}
	else if (enemies->state != attack)
	{
		enemies->is_attack = no;
	}

}
void* playBGM(void* args) {

	while (1) {

		mciSendString(L"open music/BGM.wav alias BGM", NULL, 0, NULL);
		//播放音效
		mciSendString(L"play BGM repeat", NULL, 0, NULL);
	}
}
void* Play_sound(void* args) {
	static int t = 0;
	static int ifattack = 1;
	while (1) {
		//如果攻击，就播放音效
		if (pp.attacks != attack_kick) {//确保只播放一次，避免卡顿与延迟
			ifattack = 1;
		}
		switch (pp.attacks)
		{
		case  attack_kick:
			if (ifattack == 1) {
				mciSendString(L"close kick", NULL, 0, NULL);
				//打开音效文件
				mciSendString(L"open music/player/Fly_kick.wav alias kick", NULL, 0, NULL);
				//播放音效
				mciSendString(L"play kick", NULL, 0, NULL);
				ifattack = 0;
			}
			break;
		case attack_commom:
			if (pp.py == 154) {
				if (Timer(20, 1))
					t++;
				mciSendString(L"close commom1", NULL, 0, NULL);
				mciSendString(L"open music/player/attack_commom1.wav alias commom1", NULL, 0, NULL);
				mciSendString(L"play commom1", NULL, 0, NULL);
			}
			else if (pp.py == 6 * 154) {
				mciSendString(L"close commom2", NULL, 0, NULL);
				mciSendString(L"open music/player/attack_commom2.wav alias commom2", NULL, 0, NULL);
				mciSendString(L"play commom2", NULL, 0, NULL);
				t = 0;
			}
			break;
		default:
			break;
		}
	}
}
void* Shake(void* args) {
	while (1) {
		if (GetAsyncKeyState('I') & 0x8000) {
			RECT rect;//RECT是一个矩形结构体，相当于保存矩形边框的四个坐标
			HWND hwnd = NULL, oldhwnd = NULL;//两个窗口句柄
			int x, y, width, height;//保存窗口横纵坐标及高度，宽度
			int i;
			for (i = 0; i < 3; i++)
			{
				hwnd = GetForegroundWindow();//获取活动窗口句柄
				if (hwnd != oldhwnd)
				{
					GetWindowRect(hwnd, &rect);//获取指定窗口位置
					x = rect.left;
					y = rect.top;
					width = rect.right - x;
					height = rect.bottom - y;
					oldhwnd = hwnd;//把刚刚获取的句柄保存起来
				}
				MoveWindow(hwnd, x - 3, y, width, height, TRUE);
				MoveWindow(hwnd, x - 3, y - 3, width, height, TRUE);
				MoveWindow(hwnd, x, y - 3, width, height, TRUE);
				MoveWindow(hwnd, x, y, width, height, TRUE);

			}
		}
	}
}
void Level()
{
	Background();
	Inputenemy();
	Enemymove();
	transparentimage(NULL, bg1.x, bg1.y, 0, 0, 1336, 472, &Backgroundimage1, BLACK);
	transparentimage(NULL, bg2.x, bg2.y, bg2.px, bg2.py, 3319, 481, &Backgroundimage2, BLACK);
	Putenemy();

}