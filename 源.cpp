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
#define no 0
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
#define attack_common 21
#define attack_kick 22
#define attack_jump 23
#define attack_gun 24
#define role 31
#define backimage 32
#define MAX_ENEMIES 100
#define near 41
#define approaching 42
#define far 43
IMAGE Menu, Menu1, Backgroundimage1, Backgroundimage2, Backgroundimage3, Backgroundimage4, Backgroundimage5;
IMAGE player_shadow, player_stop_right, player_stop_left, player_walk_left, player_walk_right, player_run_right, player_run_left, player_jump_right, player_jump_left, player_beated_right, player_beated_left;
IMAGE player_attack_common_right, player_attack_common_left, player_attack_Fly_kick_left, player_attack_Fly_kick_right, player_attack_jump_left, player_attack_jump_right, player_rest_left, player_rest_right;
IMAGE player_in, player_fall_left, player_fall_right;
IMAGE blood[11];
IMAGE yilong1, yilong2, leftw, rightw, bs, jineng, leftdao, rightdao;
IMAGE gogo,beat,game_over;
IMAGE enemy_walk_left, enemy_walk_right, enemy_beated_right, enemy_beated_left, enemy_fall, enemy_stop_left, enemy_stop_right, enemy_fall_left, enemy_fall_right, enemy_run_right, enemy_run_left, enemy_attack_left, enemy_attack_right, enemy_rest_left, enemy_rest_right;
IMAGE boss_hit, boss_move, dns_move, dns_sleep;
IMAGE boss_talk, boss_warning;
IMAGE idol_talk, idol_warning;
IMAGE fat_walk_left, fat_walk_right, fat_run_left, fat_run_right, fat_down_right, fat_down_left, fat_stop_right, fat_stop_left, fat_attack_left, fat_attack_right, fat_die_left, fat_die_right,  fat_fall_right, fat_fall_left;
IMAGE boss_walk_left, boss_walk_right, boss_attack_common_left, boss_attack_common_right, boss_attack_gun_right, boss_attack_gun_left, boss_stop_left, boss_stop_right, boss_run_left, boss_run_right;
IMAGE boss_beated_left, boss_beated_right, boss_bullet_left, boss_bullet_right,  boss_die_left, boss_die_right, boom;
struct MUI {
	int x = 0;
	int y = 0;
	int px = 0;
	int py = 0;
}mu1;
struct BGI1 {
	int x = 0;
	int y = 0;
	int px = 0;
	int py = 0;
	int scene = 1;
}bg1, bg2, bg3, bg4, bg5;
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
	int is_attack = no;
	int to_next = no;
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
	int x = 2150;
	int y = 230;
	int px = 0;
	int py = 0;
	int direction = Left;
	int number = 0;
}bos;
struct End_Boss {
	int x = 2150;
	int y = 400;
	int px = 0;
	int py = 0;
	int direction = Left;
	int number = 0;
}boss_a, boss_t, idol_t;
struct End_Dns {
	int x = 2150;
	int y = 380;
	int px = 0;
	int py = 0;
	int direction = Left;
	int number = 0;
}dns;
struct X {
	int x = 900;
	int y = 300;
	int zy = -100;
	int px = 0;
	int py = 0;
	int life = 200;
	int wpy = 0;
	int fpy = 0;
	int rpy = 0;
	int bpy = 0;
	int dpy = 0;
	int state = walk;
	int number = 0;
	int direction = Right;
	int fattack = 0;
	int rattack = 0;
	int fbeated = 0;
	int range = far;
	int refresh = 0;
	struct Rectangle rect;
} fat;
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
enemy enemies[5];
int numEnemies = 0;
struct Boss
{
	int life = 500;
	int live = no;
	int x = 30000;
	int y;
	int py = 0;
	int px = 0;
	int state = walk;
	int refresh = 0;
	int is_attack = no;
	int directionx = Left;
	int directiony = Up;
	struct Rectangle rect;
}Boss;
struct Boss_bullet
{
	int live = no;
	int x;
	int y;
	int directionx = Left;
	int directiony = Up;
	int is_attack = no;
	struct Rectangle rect;
}Boss_bullet[4];
struct playsound {
	int player_attack_common1 = 0;
	int player_attack_common2 = 0;
	int player_attack_kick = 0;
	int player_beated = 0;
	int enemies_fall = 0;
	int enemies_beated = 0;
}music;
bool Timer(int ms, int id) {	//ms是延迟时间，id是定时器的编号
	static DWORD t[50];
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
void Boss_image(int Width, int Height, int left_x_deviation, int left_y_deviation, int right_x_deviation, int right_y_deviation, IMAGE rp, IMAGE lp) {//图像宽高，左右方向图片，左图微调，右图微调（默认填0）
	if (Boss.directionx == Right) {
		transparentimage(NULL, Boss.x + right_x_deviation, Boss.y + right_y_deviation, Boss.px, Boss.py, Width, Height, &rp, BLACK);
	}
	else if (Boss.directionx == Left) {
		transparentimage(NULL, Boss.x + left_x_deviation, Boss.y + left_y_deviation, Boss.px, Boss.py, Width, Height, &lp, BLACK);
	}
}
void Bossanimation(int initial, int maxhight, int movespeed, int delay) {//图像在图片的当前默认填XX.py,角色动画，图片最大长度，每帧移动长度，延迟，【（0，0，0）为一张图】
	Boss.py = initial;
	if (Boss.py < maxhight && Timer(delay, 55)) {
		Boss.py += movespeed;
	}
	if (Boss.py >= maxhight) {
		Boss.py = 0;
	}
}
void Boss_bullet_image()
{
	for (int i = 0; i < 4; i++)
	{
		if (Boss_bullet[i].live == yes)
		{
			if (Boss_bullet[i].directionx == Right)
			{
				transparentimage(NULL, Boss_bullet[i].x, Boss_bullet[i].y, 0, 0, 27, 12, &boss_bullet_left, BLACK);
			}
			else if (Boss_bullet[i].directionx == Left)
			{
				transparentimage(NULL, Boss_bullet[i].x, Boss_bullet[i].y, 0, 0, 27, 12, &boss_bullet_right, BLACK);
			}
		}
	}
}
void loading();
void initialize();
int menu();
int menu1();
int Begin();
int Begin2();
int Transition2_5();
void End();
void Top_Bottom(int limittop, int limitbottom);
void Blood();
void Playermove();
void Playerm(int v1, int v2, int direction, char type);
void Playerattack();
void Playerjump();
void Playeraction();
void Enemy_Distance(enemy enemies);
void Enemy_AI(enemy* enemies, int state);
void Boss_Distance(int distance_x, int distance_y, int distance);
void Boss_move();
void Enemy_move();
void Put_enemy();
void Role_range();
void Attack(enemy* enemies);
void Boss_AI(int state);
void Boss_move();
int Put_Boss();
void Boss_Attack();
void Boss_bullte_move();
void leve1_Background();
void leve1_Limitmove();
void leve1_Inputenemy();
void leve2_Background();
void leve2_Limitmove();
void leve2_Inputenemy();
void leve3_Background();
void leve3_Limitmove();
void leve3_Inputenemy();
void* Play_sound(void* args);
void* playBGM(void* args);
void* Shake(void* args);//震动
int Level();
int Leve2();
int Leve3();
int Leve4();
void Reset(int level);
int main() {
	int leve = 1;
	bg2.y = 200;
	initgraph(1036, 544);
	loading();
	int gamemenu = 1;
	while (gamemenu == 1) {
		BeginBatchDraw();
		cleardevice();
		transparentimage(NULL, 0, 0, 0, 0, 1036, 544, &Menu, BLACK);
		gamemenu = menu();
		EndBatchDraw();
	}
	int gamemenu1 = 1;
	while (gamemenu1 == 1) {
		BeginBatchDraw();
		cleardevice();
		transparentimage(NULL, 0, 0, 0, 0, 1036, 544, &Menu1, BLACK);
		gamemenu1 = menu1();
		EndBatchDraw();
	}
	int gamebegain = 1;
	while (gamebegain == 1) {
		BeginBatchDraw();
		cleardevice();
		gamebegain = Begin();
		EndBatchDraw();
		Sleep(16);
	}
	Reset(leve);
	pthread_t music; //定义线程ID
	//pthread_t BGM; //定义线程ID
	//pthread_create(&BGM, NULL, playBGM, NULL); //创建线程
	pthread_create(&music, NULL, Play_sound, NULL); //创建线程

	while (leve == 1) //场景2大楼外
	{
		BeginBatchDraw();
		cleardevice();
		leve = Level();
		if (pp.state != beated)
		{
			Playermove();
		}
		else if (pp.state == beated)
		{
			playanimation(pp.py, 0, 0, 0);
			player_image(140, 150, 10, 0, 0, 0, player_beated_right, player_beated_left);
		}
		Blood();
		EndBatchDraw();
		HpSleep(16);
	}
	Reset(leve);
	while (leve == 2) //场景3大楼内过场
	{
		BeginBatchDraw();
		cleardevice();
		//transparentimage(NULL, 200, 200, 0, 0, 124, 152, &enemy_walk_left, BLACK);
		leve = Begin2();
		EndBatchDraw();
		HpSleep(25);
	}
	Reset(leve);
	while (leve == 3) //场景3大楼内
	{
		BeginBatchDraw();
		cleardevice();
		leve = Leve2();
		if (pp.state != beated)
		{
			Playermove();
		}
		else if (pp.state == beated)
		{
			playanimation(pp.py, 0, 0, 0);
			player_image(140, 150, 10, 0, 0, 0, player_beated_right, player_beated_left);
		}
		Blood();
		EndBatchDraw();
		HpSleep(16);
	}
	Reset(leve);
	while (leve == 4)//场景4跳楼
	{
		BeginBatchDraw();
		cleardevice();
		//transparentimage(NULL, 200, 200, 0, 0, 124, 152, &enemy_walk_left, BLACK);
		leve = Transition2_5();
		transparentimage(NULL, bg5.x, bg5.y, 0, 0, 1028, 638, &Backgroundimage5, BLACK);
		transparentimage(NULL, bg4.x, bg4.y, bg4.px, bg4.py, 1922, 1536, &Backgroundimage4, BLACK);
		player_image(98, 178, 0, 0, 0, 0, player_in, player_in);
		Blood();
		EndBatchDraw();
		HpSleep(16);
	}
	Reset(leve);
	while (leve == 5) //场景5恐龙哥
	{
		BeginBatchDraw();
		cleardevice();
		leve = Leve3();
		if (pp.state != beated)
		{
			Playermove();
		}
		else if (pp.state == beated)
		{
			playanimation(pp.py, 0, 0, 0);
			player_image(140, 150, 10, 0, 0, 0, player_beated_right, player_beated_left);
		}
		Boss_Attack();
		Blood();
		EndBatchDraw();
		HpSleep(16);
	}
	Reset(leve);
	if (leve == 77)
	{
		transparentimage(NULL, 0, 0,0, 0, 1036, 544, &game_over, BLUE);
		system("pause");
	}
	if (leve == 111)
	{
		setbkmode(TRANSPARENT);// 字体透明
		settextstyle(100, 0, _T("黑体"));
		settextcolor(0xFFA500);
		outtextxy(250, 280, _T("Win!Win!Win!"));
		system("pause");
	}
}
void loading() {
	loadimage(&Menu, L"images/menu.png");
	loadimage(&Menu1, L"images/menu1.png");
	loadimage(&Backgroundimage1, L"images/backgroundimage1.png");
	loadimage(&Backgroundimage2, L"images/backgroundimage2.png");
	loadimage(&Backgroundimage3, L"images/backgroundimage3.png");
	loadimage(&Backgroundimage4, L"images/backgroundimage4.png");
	loadimage(&Backgroundimage5, L"images/backgroundimage5.png");
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
	loadimage(&player_fall_right, L"images/player/player-fall-right.png");
	loadimage(&player_fall_left, L"images/player/player-fall-left.png");
	loadimage(&player_in, L"images/player/log_in.png");
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
	loadimage(&boss_hit, L"images/Boss_end/boss_hit.png");
	loadimage(&boss_move, L"images/Boss_end/boss_move.png");
	loadimage(&dns_move, L"images/Boss_end/dns_move.png");
	loadimage(&dns_sleep, L"images/Boss_end/dns_sleep.png");
	loadimage(&boss_talk, L"images/Boss_talk/boss_talk.png");
	loadimage(&boss_warning, L"images/Boss_talk/boss_warning.png");
	loadimage(&idol_talk, L"images/idol_talk/idol_talk.png");
	loadimage(&idol_warning, L"images/idol_talk/idol_warning.png");
	loadimage(&fat_walk_left, L"images/1/pang/pang_walk_left.png");
	loadimage(&fat_walk_right, L"images/1/pang/pang_walk_right.png");
	loadimage(&fat_run_left, L"images/1/pang/pang_run_left.png");
	loadimage(&fat_run_right, L"images/1/pang/pang_run_right.png");
	loadimage(&fat_down_left, L"images/1/pang/pang_down_left.png");
	loadimage(&fat_down_right, L"images/1/pang/pang_down_right.png");
	loadimage(&fat_stop_left, L"images/1/pang/pang_stop_left.png");
	loadimage(&fat_stop_right, L"images/1/pang/pang_stop_right.png");
	loadimage(&fat_attack_left, L"images/1/pang/pang_attack_left.png");
	loadimage(&fat_attack_right, L"images/1/pang/pang_attack_right.png");
	loadimage(&fat_die_left, L"images/1/pang/pang_die_left.png");
	loadimage(&fat_die_right, L"images/1/pang/pang_die_right.png");
	loadimage(&fat_fall_right, L"images/1/pang/pang_fall_right.png");
	loadimage(&fat_fall_left, L"images/1/pang/pang_fall_left.png");
	loadimage(&boss_walk_left, L"images/Boss_end/walk_left.png");
	loadimage(&boss_walk_right, L"images/Boss_end/walk_right.png");
	loadimage(&boss_run_left, L"images/Boss_end/run_left.png");
	loadimage(&boss_run_right, L"images/Boss_end/run_right.png");
	loadimage(&boss_stop_left, L"images/Boss_end/stop_left.png");
	loadimage(&boss_stop_right, L"images/Boss_end/stop_right.png");
	loadimage(&boss_beated_left, L"images/Boss_end/beated_left.png");
	loadimage(&boss_beated_right, L"images/Boss_end/beated_right.png");
	loadimage(&boss_attack_common_left, L"images/Boss_end/attack_common_left.png");
	loadimage(&boss_attack_common_right, L"images/Boss_end/attack_common_right.png");
	loadimage(&boss_attack_gun_left, L"images/Boss_end/attack_gun_left.png");
	loadimage(&boss_attack_gun_right, L"images/Boss_end/attack_gun_right.png");
	loadimage(&boss_bullet_left, L"images/Boss_end/bullet_left.png");
	loadimage(&boss_bullet_right, L"images/Boss_end/bullet_right.png");
	loadimage(&boss_die_left, L"images/Boss_end/die_left.png");
	loadimage(&boss_die_right, L"images/Boss_end/die_right.png");
	loadimage(&boom, L"images/Boss_end/pow.png");
	loadimage(&beat, L"images/beat.png");
	loadimage(&game_over, L"images/game_over.png");
}
int menu() {
	int me = 1;
	if (GetAsyncKeyState('5') & 0x8000) {
		me = 0;
	}
	setbkmode(TRANSPARENT);// 字体透明
	settextstyle(40, 0, _T("黑体"));
	settextcolor(0xFFA500);
	outtextxy(450, 280, _T("5键继续"));

	return me;
}
int menu1() {
	int me1 = 1;
	if (GetAsyncKeyState('J') & 0x8000) {
		me1 = 0;
	}
	setbkmode(TRANSPARENT);// 字体透明
	settextstyle(40, 0, _T("黑体"));
	settextcolor(0xFFA500);
	outtextxy(430, 50, _T("J键开始"));
	return me1;
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
						lt.x += 20;
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
int Begin2()
{
	int bg2 = 2;
	static int i = 0;
	if (i == 0)
	{
		pp1.py = 0;
		i++;
	}

	transparentimage(NULL, bg3.x, bg3.y, bg3.px, bg3.py, 2246, 544, &Backgroundimage3, BLACK);
	transparentimage(NULL, pp1.x, pp1.y, pp1.px, pp1.py, 115, 160, &player_walk_right, BLACK);
	if (pp1.y <= 300 && Timer(25, 30))
	{
		pp1.y += 2;
	}
	if ((pp1.y >= 300 && pp1.x <= 200) && Timer(50, 31))
	{
		pp1.x += 10;
	}
	if (pp1.x >= 200)
	{
		pp.x = pp1.x;
		pp.y = pp1.y;
		bg2 = 3;
	}
	if (pp1.py >= 0 && Timer(100, 32))
	{
		pp1.py += 160;
		if (pp1.py >= 1760)
		{
			pp1.py = 0;
		}
	}
	return bg2;
}
int Transition2_5()
{
	if (bg4.y > -980)
	{
		bg4.y -= 10;
	}
	else
	{
		if (Timer(200, 60))
		{
			pp.py += 178;
			if (pp.py == 356)
			{
				pp.state = stop;
				return 5;
			}
		}
	}
	pp.direction = Right;
	if (bg4.y > -300)
	{
		bg5.x = 5;
		pp.x += 3;
	}
	return 4;
}
void End() {
	int ed = 1;
	static int t = 0;
	if (ed == 1) {
		transparentimage(NULL, bg5.x, bg5.y, 0, 0, 1028, 638, &Backgroundimage5, BLACK);
		transparentimage(NULL, bg4.x, bg4.y, bg4.px, bg4.py, 1922, 1536, &Backgroundimage4, BLACK);
		if (boss_a.x >= 750) {
			boss_a.x -= 7;
			transparentimage(NULL, bg4.x + 1460, dns.y, 0, 0, 250, 49, &dns_sleep, BLACK);
		}
		if (dns.x >= 570) {
			dns.x -= 10;
			transparentimage(NULL, bg4.x + 1460, dns.y, 0, 0, 250, 49, &dns_sleep, BLACK);
		}
		if (boss_a.x < 750) {
			transparentimage(NULL, boss_a.x - 600, boss_a.y - 200, idol_t.px, idol_t.py, 100, 100, &idol_talk, BLACK);
			if (idol_t.py < 400 && Timer(300, 35)) {
				idol_t.py += 100;
			}
			if (idol_t.py < 400) {
				transparentimage(NULL, boss_a.x - 450, boss_a.y - 200, 0, 0, 400, 93, &idol_warning, BLACK);
				transparentimage(NULL, 770, boss_a.y, 0, 0, 155, 200, &boss_move, BLACK);
				transparentimage(NULL, dns.x, dns.y, 0, 0, 250, 49, &dns_sleep, BLACK);
			}
			if (idol_t.py >= 400) {
				transparentimage(NULL, boss_a.x - 600, boss_a.y - 200, boss_t.px, boss_t.py, 100, 100, &boss_talk, BLACK);
				if (boss_t.py < 400 && Timer(400, 34)) {
					boss_t.py += 100;
				}
				if (boss_t.py < 400) {
					transparentimage(NULL, boss_a.x - 400, boss_a.y - 200, 0, 0, 400, 91, &boss_warning, BLACK);
					transparentimage(NULL, dns.x, dns.y, 0, 0, 250, 49, &dns_sleep, BLACK);
					transparentimage(NULL, boss_a.x, boss_a.y, 0, 0, 155, 200, &boss_move, BLACK);
				}
				if (boss_t.py >= 400) {
					if (boss_a.y > 250) {
						boss_a.y -= 1;
						transparentimage(NULL, dns.x, dns.y, 0, 0, 250, 49, &dns_sleep, BLACK);
						transparentimage(NULL, boss_a.x, boss_a.y, boss_a.px, boss_a.py, 155, 200, &boss_move, BLACK);
						if (boss_a.py >= 0 && Timer(100, 30)) {
							boss_a.py += 200;
							if (boss_a.py >= 1200) {
								boss_a.py = 0;
							}
						}
						if (boss_a.y <= 250) {
							boss_a.py = 0;
						}
					}
					if (boss_a.y <= 250) {
						if (boss_a.py < 1200) {
							transparentimage(NULL, 670, boss_a.y, boss_a.px, boss_a.py, 235, 200, &boss_hit, BLACK);
							if (boss_a.py >= 0 && Timer(300, 31)) {
								boss_a.py += 200;
							}
							transparentimage(NULL, dns.x, dns.y, 0, 0, 250, 49, &dns_sleep, BLACK);
						}
						if (boss_a.py >= 1200) {
							dns.x -= 5;
							if (t == 0)
							{
								Boss.x = boss_a.x;
								Boss.y = boss_a.y;
								Boss.live = yes;
								t++;
							}
							//transparentimage(NULL, 770, boss_a.y, 0, 0, 155, 200, &boss_move, BLACK);
							transparentimage(NULL, dns.x, dns.y-50, dns.px, dns.py, 190, 120, &dns_move, BLACK);
							if (dns.py >= 0 && Timer(100, 32)) {
								dns.py += 120;
								if (dns.py >= 480) {
									dns.py = 0;
								}
							}
						}

					}
				}
			}
		}
		//if (dns.x < 100) {
			//ed = 0;
		//}
	}

}
void Blood() {
	transparentimage(NULL, 0, 0, 0, 0, 258, 50, &blood[10 - pp.life], BLACK);
	for (int i = 0; i < numEnemies; i++)
	{
		Attack(&enemies[i]);
	}
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
}
void Top_Bottom(int limittop, int limitbottom) {
	bool keyStateW = GetKeyState('W') < 0;
	bool keyStateS = GetKeyState('S') < 0;

	if (pp.x <= 0 && (GetKeyState('A') < 0 || (pp.attacks == attack_kick && pp.direction == Left)))
	{
		pp.limitx = yes;
	}
	else
	{
		pp.limitx = no;
	}
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
	if (pp.to_next == no)
	{
		
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
	Playeraction();
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
	static int is_attack = no, isjump = no, j = 0, iscommonattack = no;
	static int attacking = no;
	if (pp.attacks == attack_common && GetAsyncKeyState('J') & 0x8000) {
		iscommonattack = yes;

	}
	else  if (GetKeyState('J') >= 0) {
		iscommonattack = no;
	}
	if ((GetAsyncKeyState('J') & 0x8000 || pp.attacks != 0) && attacking == no) {
		if (is_attack == no && pp.state != jump) {//只记录一次位
			pp.zy = pp.y;
			pp.py = 0;
			is_attack = yes;
		}
		switch (pp.state) {//不同状态下的攻击模型
		case walk:
			pp.attacks = attack_common;
			pp.state = attack;
			break;
		case stop:
			pp.attacks = attack_common;
			pp.state = attack;
			break;
		case rest:
			pp.attacks = attack_common;
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
		if (pp.rest_time <= Rest_Interval&&pp.to_next==no)
		{
			pp.state = stop;
		}
		else if(pp.to_next==no)
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
				is_attack = no;
				attacking = no;
				pp.py = 0;
				pp.state = stop;
			}
			break;
		case attack_common:
			if (j < 8) {
				j++;
			}
			else if (j >= 8 && iscommonattack == no) {//数据重置
				pp.attacks = 0;
				j = 0;
				attacking = no;
				pp.state = stop;
				is_attack = no;
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
	else if (isjump == 1) 
	{
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
	if (pp.to_next == yes)
	{
		isjump = 0;
	}
}
void Playeraction() {
	if (pp.state == jump || pp.attacks == attack_kick) {//影子
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
		case attack_common:
			playanimation(pp.py, 1078, 154, 150);
			player_image(232, 154, -130, 10, 0, 10, player_attack_common_right, player_attack_common_left);
			break;
		case attack_kick:
			playanimation(0, 0, 0, 0);
			player_image(125, 160, 0, 0, 0, 0, player_attack_Fly_kick_right, player_attack_Fly_kick_left);
			break;
		default:
			break;
		}
	default:
		break;
	}
	if (pp.state != stop && pp.state != rest)
	{
		pp.rest_time = 0;
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
		if (distance <= 120)
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
			if (random < 4)
			{
				enemies->state = stop;
			}
			else if (random < 7)
			{
				enemies->state = attack;
			}
			else if (random < 10) {
				enemies->state = rest;
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
void Enemy_move()
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
void Put_enemy()
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
			
				transparentimage(NULL, enemies[i].x + 20, enemies[i].y + 20, 0, 0, 64, 56, &beat, BLACK);
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
	fat.rect.top = fat.y;
	fat.rect.bottom = fat.y + 156;
	fat.rect.left = fat.x;
	fat.rect.right = fat.x + 114;
	for (int i = 0; i < numEnemies; i++)
	{
		enemies[i].rect.top = enemies[i].y;
		enemies[i].rect.bottom = enemies[i].y + 80;
		enemies[i].rect.left = enemies[i].x;
		enemies[i].rect.right = enemies[i].x + 124;
	}
	Boss.rect.top = Boss.y;
	Boss.rect.bottom = Boss.y + 200;
	Boss.rect.left = Boss.x;
	Boss.rect.right = Boss.x + 180;
	for (int i = 0; i < 4; i++)
	{
		Boss_bullet[i].rect.top = Boss_bullet[i].y;
		Boss_bullet[i].rect.bottom = Boss_bullet[i].y + 12;
		Boss_bullet[i].rect.left = Boss_bullet[i].x;
		Boss_bullet[i].rect.right = Boss_bullet[i].x + 27;
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
		case attack_common:
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
				pp.rect.top + 130,
				pp.rect.top + 170,
				pp.rect.right ,
				pp.rect.right + 50
				};
			}
			else if (pp.direction == Left)
			{
				pp_attack = {
				pp.rect.top + 130,
				pp.rect.top + 170,
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
			if (pp.attacks != attack_kick)
			{
				pp.state = beated;
			}
			pp.life--;
		}
		enemies->is_attack = yes;
	}
	else if (enemies->state != attack)
	{
		enemies->is_attack = no;
	}

}
void leve1_Background() {
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

}
void leve1_Limitmove() {
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
void leve1_Inputenemy()
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
void leve2_Background()
{
	static int t = 0;
	int bgspeed = 5;
	bool isAttackKick = (pp.attacks == attack_kick);
	bool isKeyPressD = (GetKeyState('D') < 0);
	bool isKeyPressLShift = (GetKeyState(VK_LSHIFT) & 0x8000);
	if (pp.x >= 450 && bg3.scene == 1) {
		bg3.scene = 2;
	}
	if (pp.x >= 450 && bg3.scene == 2 && bg3.x >= -1180 && (isKeyPressD && pp.state != attack || isAttackKick)) {
		pp.move = backimage;
	}
	else {
		pp.move = role;
	}

	if ((isAttackKick || isKeyPressD) && pp.move == backimage && pp.direction == Right) {
		int bg2XSpeed = isKeyPressLShift || isAttackKick ? bgspeed * 2 : bgspeed;
		bg3.x -= bg2XSpeed;
		fat.x -= bg2XSpeed;
		for (int i = 0; i < numEnemies; i++)
		{
			enemies[i].x -= bg2XSpeed;
		}
		if (bg3.x <= -1180)
		{
			bg3.scene = 3;
			if (t == 0)
			{
				fat.life = 300;
				fat.x = 300;
				fat.zy = -100;
				fat.fpy = 0;
				t++;
			}
		}
	}
}
void leve2_Limitmove()
{
	int topLimit = 200;
	int bottomLimit = 400;
	Top_Bottom(topLimit, bottomLimit);
	if (bg3.scene == 1) {
		if ((pp.state != jump && pp.y + pp.x < 430 && pp.attacks != attack_kick) || ((pp.state == jump || pp.attacks == attack_kick) && pp.zy + pp.x < 525)) {
			if (GetKeyState('A') < 0 || (pp.attacks == attack_kick && pp.direction == Left)) {
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
	}
	if (bg3.scene == 3) {
		if ((pp.state != jump && pp.y - pp.x < -550 && pp.attacks != attack_kick) || ((pp.state == jump || pp.attacks == attack_kick) && pp.zy - pp.x < -550)) {
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
	}
}
void leve2_Inputenemy()
{
	static int ss = 1;
	if (bg3.scene == 1 && ss == 1)
	{
		enemies[numEnemies].x = 1000;
		enemies[numEnemies].y = 350;
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
	else if (bg3.scene == 2 && ss == 2)
	{
	enemies[numEnemies].x = 1000;
	enemies[numEnemies].y = 350;
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
	enemies[numEnemies].x = 1000;
	enemies[numEnemies].y = 400;
	enemies[numEnemies].life = 100;
	enemies[numEnemies].type = 1;
	enemies[numEnemies].directionx = Left;
	enemies[numEnemies].directiony = Down;
	enemies[numEnemies].initial = 20;
	enemies[numEnemies].state = walk;
	enemies[numEnemies].refresh = 0;
	enemies[numEnemies].live = yes;
	enemies[numEnemies].is_attack = no;
	numEnemies++;
	ss = 3;
	}
	else if (bg3.scene == 3 && ss == 3)
	{
		enemies[numEnemies].x = -200;
		enemies[numEnemies].y = 350;
		enemies[numEnemies].life = 100;
		enemies[numEnemies].type = 1;
		enemies[numEnemies].directionx = Left;
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
void leve3_Background()
{
	int bgspeed = 5;
	bool isAttackKick = (pp.attacks == attack_kick);
	bool isKeyPressD = (GetKeyState('D') < 0);
	bool isKeyPressLShift = (GetKeyState(VK_LSHIFT) & 0x8000);

	if (pp.x >= 450 && bg4.scene == 1) {
		bg4.scene = 2;
	}

	if (pp.x >= 450 && bg4.scene == 2 && bg4.x >= -880 && (isKeyPressD && pp.state != attack || isAttackKick)) {
		pp.move = backimage;
	}
	else {
		pp.move = role;
	}
	if ((isAttackKick || isKeyPressD) && pp.move == backimage && pp.direction == Right) {
		int bg2XSpeed = isKeyPressLShift || isAttackKick ? bgspeed * 2 : bgspeed;
		int bg2YSpeed = isKeyPressLShift || isAttackKick ? 5 : 2;
		bg4.x -= bg2XSpeed;
		bg5.x -= bgspeed / 10;
		Boss.x -= bg2XSpeed;
		for (int i = 0; i < numEnemies; i++)
		{
			enemies[i].x -= bg2XSpeed;
		}
		if (bg4.x <= -880) {
			bg4.scene = 3;
		}
	}
}
void leve3_Limitmove()
{
	int topLimit = 250;
	int bottomLimit = 400;
	Top_Bottom(topLimit, bottomLimit);
	if (bg4.scene == 1) {
		if ((pp.state != jump && pp.y + 0.57 * pp.x < 420 && pp.attacks != attack_kick) || ((pp.state == jump || pp.attacks == attack_kick) && pp.zy + 0.57 * pp.x < 420)) {
			if (GetKeyState('A') < 0 || (pp.attacks == attack_kick && pp.direction == Left)) {
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
	}
	if (bg4.scene == 2) {
		if ((pp.state != jump && pp.y + 0.57 * pp.x < 420 + bg4.x && pp.attacks != attack_kick) || ((pp.state == jump || pp.attacks == attack_kick) && pp.zy + 0.57 * pp.x < 420 + bg4.x)) {
			if (GetKeyState('A') < 0 || (pp.attacks == attack_kick && pp.direction == Left)) {
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
	}
	if (bg4.scene == 3) {
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
	}
}
void leve3_Inputenemy()
{

}
void Boss_Distance(int distance_x, int distance_y, int distance)
{
	if (Boss.live == yes)
	{
		if (distance_x < 0)
		{
			Boss.directionx = Left;
		}
		else if (distance_x > 0)
		{
			Boss.directionx = Right;
		}
		if (distance_y < 0)
		{
			Boss.directiony = Up;
		}
		else if (distance_y > 0)
		{
			Boss.directiony = Down;
		}
		if (distance <= 80)
		{
			Boss_AI(near);

		}
		else if (distance <= 500)
		{
			Boss_AI(approaching);
		}
		else if (distance >= 500)
		{
			Boss_AI(far);
		}
	}
}
void Boss_AI(int state)
{
	Boss.refresh++;
	if (Boss.refresh >= 35 && Boss.life > 0 && Boss.live == yes)
	{
		Boss.refresh = 0;
		Boss.py = 0;
		srand(time(0)); // 初始化随机数生成器
		int random = rand() % 10;
		switch (state)//根据敌人与玩家的距离以及不同状态的权重更新敌人状态
		{
		case far:
			if (random < 3 && abs(pp.y - Boss.y) <= 30) {
				Boss.state = attack_gun;
			}
			else if (random < 5) {
				Boss.state = walk;
			}
			else if (random < 10) {
				Boss.state = run;
			}
			break;
		case approaching:
			if (random < 2)
			{
				Boss.state = run;
			}
			else if (random < 4 && abs(pp.y - Boss.y) <= 30) {
				Boss.state = attack_gun;
			}
			else if (random < 10) {
				Boss.state = walk;
			}
			break;
		case near:
			if (random < 2)
			{
				Boss.state = stop;
			}
			else if (random < 10) {
				Boss.state = attack_common;
			}

			break;
		default:
			break;
		}

	}
	else if (Boss.life <= 0 && Boss.live == yes)
	{
		if (Boss.live == yes)
		{
			Boss.py = 0;
			Boss.live = no;
		}
		Boss.state = fall;
	}
}
void Boss_move()
{
	int distance_y;
	int distance_x = (int)(pp.x - Boss.x);
	if (pp.state == jump || pp.attacks == attack_kick)
	{
		distance_y = (int)(pp.zy - Boss.y);
	}
	else
	{
		distance_y = (int)(pp.y - Boss.y);
	}
	int distance = (int)sqrt(pow(distance_x, 2) + pow(distance_y, 2));
	Boss_Distance(distance_x, distance_y, distance);
	switch (Boss.state)
	{
	case stop:
		break;
	case run:
		Boss.x += Boss.directionx * 6;
		Boss.y += Boss.directiony * 3;
		if (distance < 90)
		{
			Boss.refresh = 10;
			Boss.state = attack_common;
		}
		break;
	case walk:
		if (abs(distance_x) >= 80)
		{
			Boss.x += Boss.directionx * 1;
		}
		if (abs(distance_y) >= 20 && abs(distance_x) <= 300)
		{
			Boss.y += Boss.directiony * 1;
		}
		break;
	case beated:
		break;
	case fall:
		break;
	default:
		break;
	}
}
void Boss_Attack()
{
	Role_range();
	struct Rectangle pp_attack;
	struct Rectangle Boss_attack;
	if ((pp.state == attack || (pp.state == jump && pp.attacks == attack_jump)))
	{
		pp.is_attack == yes;
		switch (pp.attacks)
		{
		case attack_common:
			if (pp.direction == Right)
			{
				pp_attack = {
				pp.rect.top + 10,
				pp.rect.top + 30,
				pp.rect.right ,
				pp.rect.right + 60
				};
			}
			else if (pp.direction == Left)
			{
				pp_attack = {
				pp.rect.top + 10,
				pp.rect.top + 30,
				pp.rect.left - 60,
				pp.rect.left - 10
				};
			}
			if ((pp.py / 154) % 2 == 1)
			{
				if (pp_attack.top <= Boss.rect.bottom && pp_attack.bottom >= Boss.rect.top && pp_attack.left <= Boss.rect.right && pp_attack.right >= Boss.rect.left)
				{

					if (Boss.live == yes)
					{

						Boss.state = beated;

						Boss.life--;
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
			if (pp_attack.top <= Boss.rect.bottom && pp_attack.bottom >= Boss.rect.top && pp_attack.left <= Boss.rect.right && pp_attack.right >= Boss.rect.left)
			{

				if (Boss.live == yes)
				{
					Boss.state = beated;
					Boss.life--;
				}
			}
			break;
		case attack_kick:
			if (pp.direction == Right)
			{
				pp_attack = {
				pp.rect.top + 130,
				pp.rect.top + 170,
				pp.rect.right ,
				pp.rect.right + 50
				};
			}
			else if (pp.direction == Left)
			{
				pp_attack = {
				pp.rect.top + 130,
				pp.rect.top + 170,
				pp.rect.left - 50,
				pp.rect.left
				};
			}
			if (pp_attack.top <= Boss.rect.bottom && pp_attack.bottom >= Boss.rect.top && pp_attack.left <= Boss.rect.right && pp_attack.right >= Boss.rect.left)
			{

				if (Boss.live == yes)
				{
					Boss.state = beated;
					Boss.life--;
				}
			}
			break;
		default:
			break;
		}
	}
	if (Boss.state == attack_common && Boss.is_attack == no && Boss.py == 400)
	{
		if (Boss.directionx == Right)
		{
			Boss_attack = {
				Boss.rect.top + 10,
				Boss.rect.top + 40,
				Boss.rect.right,
				Boss.rect.right + 80
			};
		}
		else if (Boss.directionx == Left)
		{
			Boss_attack = {
				Boss.rect.top + 10,
				Boss.rect.top + 40,
				Boss.rect.left - 80,
				Boss.rect.left
			};
		}
		if (Boss_attack.top <= pp.rect.bottom && Boss_attack.bottom >= pp.rect.top && Boss_attack.left <= pp.rect.right && Boss_attack.right >= pp.rect.left)
		{
			if (pp.attacks != attack_kick)
			{
				pp.state = beated;
			}
			pp.life--;
		}
		Boss.is_attack = yes;
	}
	else if (Boss.state != attack_common || (Boss.state == attack_common && Boss.py == 0))
	{
		Boss.is_attack = no;
	}
	for (int i = 0; i < 4; i++)
	{
		Boss_bullet[i].rect.top = Boss_bullet[i].y;
		Boss_bullet[i].rect.bottom = Boss_bullet[i].y + 12;
		Boss_bullet[i].rect.left = Boss_bullet[i].x;
		Boss_bullet[i].rect.right = Boss_bullet[i].x + 27;
		if (Boss_bullet[i].rect.top <= pp.rect.bottom && Boss_bullet[i].rect.bottom >= pp.rect.top && Boss_bullet[i].rect.left <= pp.rect.right && Boss_bullet[i].rect.right >= pp.rect.left && Boss_bullet[i].live == yes)
		{
			if (pp.attacks != attack_kick)
			{
				pp.state = beated;
			}
			pp.life--;
			Boss_bullet[i].live = no;
		}
	}
}
void Boss_bullte_move()
{
	for (int i = 0; i < 4; i++)
	{
		if (Boss_bullet[i].live == yes)
		{
			Boss_bullet[i].x += Boss_bullet[i].directionx * 20;
		}
		if (Boss_bullet[i].directionx == Left && Boss_bullet[i].x <= 0)
		{
			Boss_bullet[i].live = no;
		}
		else if (Boss_bullet[i].directionx == Right && Boss_bullet[i].x >= 1150)
		{
			Boss_bullet[i].live = no;
		}
	}
}
int Put_Boss()
{
	static int t = 0;
	int Offset = 0;
	Boss_bullet_image();
		switch (Boss.state)
		{
		case stop:
			Bossanimation(0, 0, 0, 100);
			Boss_image(163, 200, 0, 0, 0, 0, boss_stop_right, boss_stop_left);
			break;
		case walk:
			Bossanimation(Boss.py, 1200, 200, 100);
			Boss_image(155, 200, 0, 0, 0, 0, boss_walk_right, boss_walk_left);
			break;
		case run:
			Bossanimation(Boss.py, 1200, 200, 100);
			Boss_image(150, 200, 0, 0, 0, 0, boss_run_right, boss_run_left);
			break;
		case beated:
			Bossanimation(0, 0, 0, 100);
			Boss_image(136, 178, 0, 0, 0, 0, boss_beated_right, boss_beated_left);
			transparentimage(NULL, Boss.x + 20, Boss.y + 20, 0, 0, 64, 56, &beat, BLACK);
			break;
		case attack_common:
			Bossanimation(Boss.py, 600, 200, 200);
			Boss_image(309, 200, 0, 0, 0, 0, boss_attack_common_right, boss_attack_common_left);
			break;
		case attack_gun:
			Bossanimation(0, 0, 0, 0);
			Boss_image(151, 200, 0, 0, 0, 0, boss_attack_gun_right, boss_attack_gun_left);
			if (Boss.refresh % 20 == 0)
			{
				Boss_bullet[Boss.refresh / 10].directionx = Boss.directionx;
				Boss_bullet[Boss.refresh / 10].live = yes;
				if (Boss.directionx == Left)
				{
					transparentimage(NULL, Boss.x - 20, Boss.y + 40, 0, 0, 66, 33, &boom, BLACK);
					Boss_bullet[Boss.refresh / 10].x = Boss.x - 27;

				}
				else if (Boss.directionx == Right)
				{
					transparentimage(NULL, Boss.x + 140, Boss.y + 40, 0, 0, 66, 33, &boom, BLACK);
					Boss_bullet[Boss.refresh / 10].x = Boss.x + 151;
				}
				Boss_bullet[Boss.refresh / 10].y = Boss.y + 60;
			}
			break;
		case fall:
			
			t++;
			if(Boss.x<800)
			
			if (t < 30)
			{
				Boss.x -= Boss.directionx * 2;
				Boss.py = 0;
				if (t >= 15)
				{
					Boss.py = 178;
				}
				Boss.y -= 5;
			}
			else if (t < 60)
			{
				Boss.x -= Boss.directionx * 2;
				Boss.py = 356;
				if (t >= 45)
				{
					Boss.py = 534;
				}
				Boss.y += 5;
			}
			else if (t < 62)
			{
				Boss.py = 712;
			}
			else if (t < 70)
			{
				Boss.y -= 2;
				Boss.py = 534;
			}
			else if (t < 78)
			{
				Boss.x -= Boss.directionx * 1;
				Boss.y += 2;
				Boss.py = 534;
			}
			else if (t < 80)
			{
				Boss.x -= Boss.directionx * 1;
				Boss.py = 712;
			}
			else if (t < 82)
			{
				Boss.x -= Boss.directionx * 1;
				Boss.py = 534;
			}
			else if (t  <90 )
			{
				Boss.x -= Boss.directionx * 1;
				Boss.py = 712;
			}
			else if (t >= 90)
			{
				return 111;
			}
			Boss_image(298, 178, -50, 0, 0, 0, boss_die_right, boss_die_left);
			Sleep(100);
			break;
		default:
			break;
		
	}
	return 5;
}
void pang() {
	if (fat.zy <= 350)
	{
		if (fat.x >= pp.x)
		{
			fat.direction = Right;
			transparentimage(NULL, fat.x, fat.zy, fat.px, fat.fpy, 170, 138, &fat_fall_right, BLACK);
		}
		else {
			fat.direction = Left;
			transparentimage(NULL, fat.x, fat.zy, fat.px, fat.fpy, 170, 138, &fat_fall_left, BLACK);
		}

		if (Timer(25, 24))
		{
			fat.zy += 10;
		}
		if (fat.zy >= 300)
		{
			fat.fpy = 138;
		}

	}
	else
	{
		fat.refresh++;
		Role_range();
		struct Rectangle pp_attack;
		struct Rectangle fat_attack;
		if (fat.life > 0)
		{
			if (fat.life > 0 && abs(fat.x - pp.x) > 150)
			{
				if (fat.x >= pp.x)
				{
					fat.direction = Right;
					fat.rattack = 0;
				}
				else {
					fat.direction = Left;
					fat.rattack = 0;
				}
			}
			srand(time(0)); // 初始化随机数生成器
			int random = rand() % 10;
			if (abs(fat.x - pp.x) > 500)
			{
				fat.range = far;
			}
			if (abs(fat.x - pp.x) > 250 && abs(fat.x - pp.x) < 500)
			{
				fat.range = approaching;
			}
			if (abs(fat.x - pp.x) < 250)
			{
				fat.range = near;
			}
			if (fat.state == walk)
			{
				if (fat.direction == Right)
				{
					if(fat.state!=beated)
					fat.x -= 2;
				}
				else
				{
					if (fat.state != beated)
					fat.x += 2;
				}
			}
			else if (fat.state == run)
			{
				if (fat.direction == Right)
				{
					if (fat.state != beated)
					fat.x -= 5;
				}
				else
				{
					if (fat.state != beated)
					fat.x += 5;
				}
			}
			if (fat.range == near)
			{
				if (fat.y >= pp.y)
				{
					if (fat.state != beated && fat.state != attack)
					if (pp.attacks != attack_kick&& pp.attacks != jump)fat.y -= 1;
				}
				else
				{
					if (fat.state != beated&& fat.state!=attack)
					if (pp.attacks != attack_kick && pp.attacks != jump)fat.y += 1;
				}
			}
			if (fat.refresh >= 35)
			{
				switch (fat.range)
				{
				case far://远
					if (random < 5) {
						fat.state = walk;
					}
					else if (random < 8) {
						fat.state = run;
					}
					else if (random < 10) {
						fat.state = stop;
					}
					break;
				case approaching://靠近
					if (random < 5) {
						fat.state = walk;
					}
					else if (random < 8) {
						fat.state = run;
					}
					break;
				case near://附近
					if (random < 3) {
						fat.state = walk;
					}
					else if (random < 8) {
						fat.state = run;
					}
					else if (random < 10) {
						fat.state = attack;
					}
					break;
				default:
					break;
				}
				fat.refresh = 0;
			}
		}
		else {
			fat.state = fall;
		}
		if (pp.state == attack || (pp.state == jump && pp.attacks == attack_jump))
		{
			switch (pp.attacks)
			{
			case attack_common:
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
					if (pp_attack.top <= fat.rect.bottom && pp_attack.bottom >= fat.rect.top && pp_attack.left <= fat.rect.right && pp_attack.right >= fat.rect.left)
					{

						if (fat.life > 0)
						{
							fat.state = beated;
							fat.life--;

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
				if (pp_attack.top <= fat.rect.bottom && pp_attack.bottom >= fat.rect.top && pp_attack.left <= fat.rect.right && pp_attack.right >= fat.rect.left)
				{
					if (fat.life > 0)
					{
						fat.state = beated;
						fat.life--;
					}
				}
				fat.fbeated = 1;
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
				if (pp_attack.top <= fat.rect.bottom && pp_attack.bottom >= fat.rect.top && pp_attack.left <= fat.rect.right && pp_attack.right >= fat.rect.left)
				{

					if (fat.life > 0)
					{
						fat.state = beated;
						fat.life--;
					}
				}
				fat.fbeated = 1;
				break;
			default:
				break;
			}
		}
		else if (pp.state != attack || (jump && pp.attacks == attack_jump))
		{
			fat.fbeated = 0;
		}
		if (fat.state == attack && fat.fattack == 0)
		{
			if (fat.direction == Left)
			{
				fat_attack = {
					fat.rect.top,
					fat.rect.top,
					fat.rect.right,
					fat.rect.right
				};
			}
			else if (fat.direction == Right)
			{
				fat_attack = {
					fat.rect.top,
					fat.rect.top,
					fat.rect.left ,
					fat.rect.left
				};
			}
			if (fat_attack.top <= pp.rect.bottom && fat_attack.bottom >= pp.rect.top && fat_attack.left <= pp.rect.right && fat_attack.right >= pp.rect.left)
			{
				if (pp.attacks != attack_kick)
				{
					pp.state = beated;
				}
				pp.life--;
			}
			fat.fattack = 1;
		}
		else if (fat.state != attack)
		{
			fat.fattack = 0;
		}
		if (fat.state == run && fat.rattack == 0)
		{
			if (fat.direction == Left)
			{
				fat_attack = {
					fat.rect.top ,
					fat.rect.bottom,
					fat.rect.right,
					fat.rect.right
				};
				fat.rattack = 0;
			}
			else if (fat.direction == Right)
			{
				fat_attack = {
					fat.rect.top ,
					fat.rect.bottom,
					fat.rect.left,
					fat.rect.left
				};
				fat.rattack = 0;
			}
			if (fat_attack.top <= pp.rect.bottom && fat_attack.bottom >= pp.rect.top && fat_attack.left <= pp.rect.right && fat_attack.right >= pp.rect.left)
			{
				if (pp.attacks != attack_kick)
				{
					pp.state = beated;
				}
				pp.life--;
				fat.rattack = 1;
			}

		}
		if (fat.state != run)
		{
			fat.rattack = 0;
		}
		switch (fat.state)
		{
		case walk://走路
			if (fat.direction == Right) {
				transparentimage(NULL, fat.x, fat.y, fat.px, fat.wpy, 114, 160, &fat_walk_right, BLACK);
				if (fat.wpy >= 0 && Timer(70, 16) && fat.number == 0)
				{
					fat.wpy += 160;
					if (fat.wpy == 800)
					{
						fat.number++;
					}
				}
				if (fat.wpy <= 800 && Timer(70, 17) && fat.number == 1)
				{
					fat.wpy -= 160;
					if (fat.wpy == 0)
					{
						fat.number--;
					}
				}

			}
			else if (fat.direction == Left) {
				transparentimage(NULL, fat.x, fat.y, fat.px, fat.wpy, 114, 160, &fat_walk_left, BLACK);
				if (fat.wpy >= 0 && Timer(70, 18) && fat.number == 0)
				{
					fat.wpy += 160;
					if (fat.wpy == 800)
					{
						fat.number++;
					}
				}
				if (fat.wpy <= 800 && Timer(70, 19) && fat.number == 1)
				{
					fat.wpy -= 160;
					if (fat.wpy == 0)
					{
						fat.number--;
					}
				}
			}
			break;
		case stop://停止
			if (fat.direction == Right) {

				transparentimage(NULL, fat.x, fat.y, fat.px, fat.py, 114, 156, &fat_stop_right, BLACK);
			}
			else if (fat.direction == Left) {
				transparentimage(NULL, fat.x, fat.y, fat.px, fat.py, 114, 156, &fat_stop_left, BLACK);
			}
			break;
		case run://跑步

			if (fat.direction == Right) {

				transparentimage(NULL, fat.x, fat.y, fat.px, fat.rpy, 186, 146, &fat_run_right, BLACK);
				if (fat.rpy >= 0 && Timer(50, 20))
				{
					fat.rpy += 146;
					if (fat.rpy >= 1022)
					{
						fat.rpy = 0;
					}
				}
			}
			else if (fat.direction == Left) {

				transparentimage(NULL, fat.x, fat.y, fat.px, fat.rpy, 186, 146, &fat_run_left, BLACK);
				if (fat.rpy >= 0 && Timer(50, 21))
				{
					fat.rpy += 146;
					if (fat.rpy >= 1022)
					{
						fat.rpy = 0;
					}
				}
			}
			break;

		case attack://攻击
			if (fat.direction == Right) {

				transparentimage(NULL, fat.x - 25, fat.y, fat.px, fat.py, 214, 182, &fat_attack_right, BLACK);
			}
			else if (fat.direction == Left) {
				transparentimage(NULL, fat.x - 25, fat.y, fat.px, fat.py, 214, 182, &fat_attack_left, BLACK);
			}
			break;
		case beated://被攻击
			if (fat.direction == Right) {
				transparentimage(NULL, fat.x, fat.y + 25, fat.px, fat.bpy, 130, 138, &fat_down_right, BLACK);
			}
			else if (fat.direction == Left) {
				transparentimage(NULL, fat.x, fat.y + 25, fat.px, fat.bpy, 130, 138, &fat_down_left, BLACK);
			}
			break;
		case fall://死亡
			if (fat.direction == Right) {
				transparentimage(NULL, fat.x, fat.y + 50, fat.px, fat.dpy, 208, 138, &fat_die_right, BLACK);
				if (fat.dpy >= 0 && Timer(200, 22))
				{
					fat.dpy += 138;
					if (fat.dpy == 414)
					{
						fat.dpy -= 138;
					}

				}
			}
			else if (fat.direction == Left) {
				transparentimage(NULL, fat.x, fat.y + 50, fat.px, fat.dpy, 208, 138, &fat_die_left, BLACK);
				if (fat.dpy >= 0 && Timer(200, 23))
				{
					fat.dpy += 138;
					if (fat.dpy == 414)
					{
						fat.dpy -= 138;
					}
				}
			}
			break;
		default:
			break;
		}

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
	static int player_att = no, player_be = no;
	static int enemies_att[5] = { no }, enemies_be[5] = { no }, enemies_fa[5] = { no };

	while (1)
	{
		if (pp.state != attack)
		{
			player_att = no;
		}
		else if (pp.state == attack && player_att == no)
		{
			if (pp.attacks == attack_kick) {
				music.player_attack_kick = yes;
			}
			if (pp.attacks == attack_common)
			{
				if (pp.py <= 154) {
					music.player_attack_common1 = yes;
				}
				else if (pp.py >= 6 * 154) {
					music.player_attack_common2 = yes;
				}
			}
			player_att = yes;
		}
		if (pp.state != beated)
		{
			player_be = no;
		}
		else if (pp.state == beated && player_be == no)
		{
			music.player_beated = yes;
			player_be = yes;
		}
		for (int i = 0; i < numEnemies; i++)
		{
			if (enemies[i].state != beated)
			{
				enemies_be[i] = no;
			}
			else if (enemies[i].state == beated && enemies_be[i] == no)
			{
				music.enemies_beated = yes;
				enemies_be[i] = yes;
			}
			if (enemies[i].live == no && enemies_fa[i] == no)
			{
				music.enemies_fall = yes;
				enemies_fa[i] = yes;
			}
		}
		if (music.player_attack_common1 == yes)
		{
			mciSendString(L"close attack_common1 ", NULL, 0, NULL);
			mciSendString(L"open music/player/attack_common1.wav alias attack_common1", NULL, 0, NULL);
			mciSendString(L"play attack_common1 ", NULL, 0, NULL);
			music.player_attack_common1 = no;
		}
		if (music.player_attack_common2 == yes)
		{
			mciSendString(L"close attack_common2 ", NULL, 0, NULL);
			mciSendString(L"open music/player/attack_common2.wav alias attack_common2", NULL, 0, NULL);
			mciSendString(L"play attack_common2 ", NULL, 0, NULL);
			music.player_attack_common2 = no;
		}
		if (music.player_attack_kick == yes)
		{
			mciSendString(L"close kick ", NULL, 0, NULL);
			mciSendString(L"open music/player/kick.wav alias kick", NULL, 0, NULL);
			mciSendString(L"play kick ", NULL, 0, NULL);
			music.player_attack_kick = no;
		}
		if (music.player_beated == yes)
		{
			mciSendString(L"close beated ", NULL, 0, NULL);
			mciSendString(L"open music/player/beated.wav alias beated", NULL, 0, NULL);
			mciSendString(L"play beated ", NULL, 0, NULL);
			music.player_beated = no;
		}
		if (music.enemies_beated == yes)
		{
			mciSendString(L"close enemies_beated", NULL, 0, NULL);
			mciSendString(L"open music/enemy/enemies_beated.wav alias enemies_beated", NULL, 0, NULL);
			mciSendString(L"play enemies_beated", NULL, 0, NULL);
			music.enemies_fall = no;
		}
		if (music.enemies_fall == yes)
		{
			mciSendString(L"close enemies_fall", NULL, 0, NULL);
			mciSendString(L"open music/enemy/enemies_fall.wav alias enemies_fall", NULL, 0, NULL);
			mciSendString(L"play enemies_fall", NULL, 0, NULL);
			music.enemies_fall = no;
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
int Level()
{
	leve1_Background();
	leve1_Limitmove();
	leve1_Inputenemy();
	Enemy_move();
	transparentimage(NULL, bg1.x, bg1.y, 0, 0, 1336, 472, &Backgroundimage1, BLACK);
	transparentimage(NULL, bg2.x, bg2.y, bg2.px, bg2.py, 3319, 481, &Backgroundimage2, BLACK);
	Put_enemy();
	if ((pp.x > 760 && bg2.scene == 3 && enemies[0].live == 0 && enemies[1].live == 0 && enemies[2].live == 0 && enemies[3].live == 0 && enemies[4].live == 0) || GetAsyncKeyState('N') & 0x8000)
	{
		static int t = 0;
		if (pp.state == attack)
		{
			loadimage(&Backgroundimage2, L"images/backgroundimage2-2.png");
			t = 1;
		}
		if (t >= 30 || GetAsyncKeyState('N') & 0x8000)
		{
			return 2;
		}
		if (t >= 1)
		{
			pp.x += 2;
			pp.to_next = yes;
			pp.state = walk;
			t++;
		}
	}
	if (GetAsyncKeyState('P') & 0x8000)
	{
		pp.life = 10;
	}
	if (pp.life <= 0)
	{
		return 77;
	}
	return 1;

}
int Leve2()
{

	leve2_Background();
	leve2_Limitmove();
	leve2_Inputenemy();
	Enemy_move();
	transparentimage(NULL, bg3.x, bg3.y, bg3.px, bg3.py, 2246, 544, &Backgroundimage3, BLACK);
	Put_enemy();
	pang();
	if ((pp.x > 760&& bg3.scene == 3 && enemies[0].live == 0 && enemies[1].live == 0 && enemies[2].live == 0 && enemies[3].live == 0 && fat.life <= 0) || GetAsyncKeyState('N') & 0x8000)
	{
		static int t = 0;
		if (pp.state == attack)
		{
			loadimage(&Backgroundimage3, L"images/backgroundimage3_2.png");
			t = 1;
		}
		if (pp.state == jump)
		{
			t++;
			pp.x += 5;
			pp.y -= 2;
			pp.to_next = yes;
			pp.state = jump;
		}
		if (t >= 30 || GetAsyncKeyState('N') & 0x8000)
		{
			return 4;
		}
	}
	if (GetAsyncKeyState('P') & 0x8000)
	{
		pp.life = 10;
	}
	if (pp.life <= 0)
	{
		return 77;
	}
	return 3;

}
int Leve3()
{
	static int animation = 1, t = 50;
	leve3_Background();
	leve3_Limitmove();
	leve3_Inputenemy();
	Boss_move();
	Boss_bullte_move();
	transparentimage(NULL, bg5.x, bg5.y, 0, 0, 1028, 638, &Backgroundimage5, BLACK);
	transparentimage(NULL, bg4.x, bg4.y, bg4.px, bg4.py, 1922, 1536, &Backgroundimage4, BLACK);
	if (bg4.scene == 3)
	{
		End();
	}
	else if (bg4.scene == 2)
	{
		transparentimage(NULL, bg4.x + 1460, dns.y, 0, 0, 250, 49, &dns_sleep, BLACK);
	}
	if (GetAsyncKeyState('P') & 0x8000)
	{
		pp.life = 10;
	}
	if (pp.life <= 0)
	{
		return 77;
	}
	return Put_Boss();
}
void Reset(int level)
{
	numEnemies = 0;
	pp.py = 0;
	pp.to_next = no;
	pp.state = stop;
	if (level == 2)
	{
		pp1.x = 100;
		pp1.y = 230;
	}
	else if (level == 4)
	{
		pp.x = 200;
	}
	else if (level == 5)
	{
		pp.py = 0;
	}
}