# include <windows.h>
# include <stdlib.h>
# include <conio.h>
# include <time.h>
# include <cstring>
# include <cstdio>
# include <iostream>
#include <cstdlib>
#include <ctime>

#define N 32
using namespace std;

int gameover;
int x1,Y1;//设置随机值
int x, y;
long start;
//=====================================
//类的实现与应用
//==========================

//定义贪吃蛇的坐标
class snake_position
{
public:
	int x, y;
	snake_position(){};
	void initialize(int &);//坐标初始化
};


snake_position positon[(N - 2)*(N - 2) + 1];//定义贪吃蛇坐标类数组，有N-2*N-2个坐标

void snake_position::initialize(int &j)
{
	x = 1;
	y = j;
}


// 定义贪吃蛇的棋盘图
class snake_map
{
private:
	char s[N][N];//定义贪吃蛇棋盘
	int grade, length;
	int gamespeed;//定义时间间隔
	char direction;//确定初始移动方向；
	int head, tail;
	int score;
	bool gameatuo;
public:
	snake_map(int h = 4, int t = 1, int l = 4, char d = 77, int s = 0) :length(l), direction(d), head(h), tail(t), score(s){}
	void initialize();
	void show_game();
	int update_game();
	void setpoint();
	void getgrade();
	void display();

};
//定义初始化函数，将贪吃蛇的棋盘图进行初始化

void snake_map::initialize()
{
	int i, j;
	for (i = 1; i <= 3; i++)//将贪吃蛇界面中的初状态进行设置
	{
		s[1][i] = '*';

	}
	s[1][4] = '#';
	for (i = 1; i <= N - 2; i++)
	{
		for (j = 1; j <= N - 2; j++)
		{
			s[i][j] = ' ';
		}
	}
	for (i = 0; i <= N - 1; i++)
		s[0][i] = s[N - 1][i] = '-';//初始化贪吃蛇棋盘中的上下墙壁
	for (i = 1; i <= N - 2; i++)
		s[i][0] = s[i][N - 1] = '|';//初始化贪吃蛇棋盘左右边缘墙壁

}
//定义贪吃蛇棋盘信息

void snake_map::show_game()
{
	system("cls");//清屏
	int i, j;
	cout << endl;
	for (i = 0; i < N; i++)
	{
		cout << "\t";
		for (j = 0; j < N; j++)
			cout << s[i][j] << ' ';//输出贪吃蛇棋盘
		if (i == 2)cout << "\t 等级：" << grade;
		if (i == 6)cout << "\t速度：" << gamespeed;
		if (i == 10)cout << "\t得分:" << score;
		if (i == 14)cout << "\t暂停：按一下空格键";
		if (i == 18)cout << "\t继续：按两下空格键";
	    cout << endl;
	}
}


//输入选择等级
void snake_map::getgrade()
{
	cin >> grade;
	while (grade > 7 || grade < 1)
	{
		cout << "请输入数字1-7选择等级，输其他字符无效" << endl;
		cin >> grade;

	}
	switch (grade)
	{
	case 1:gamespeed = 1000; gameatuo = 0; break;
	case 2:gamespeed = 800; gameatuo = 0; break;
	case 3:gamespeed = 600; gameatuo = 0; break;
	case 4:gamespeed = 400; gameatuo = 0; break;
	case 5:gamespeed = 200; gameatuo = 0; break;
	case 6:gamespeed = 100; gameatuo = 0; break;
	case 7:gamespeed = 1; gameatuo = 0; break;
	}
}
//输出等级，得分情况以及称号
void snake_map::display()
{
	cout << "\n\t\t\t\t等级" << endl;
	cout << "\n\n\n\t\t\t\t速度" << gamespeed;
	cout << "\n\n\n\t\t\t\t得分" << score << endl;
}

//随机产生贪吃蛇的食物
void snake_map::setpoint()
{
	srand(time(0));
	do
	{
		x1 =rand() %(N - 2) + 1;
		Y1 =rand() % (N - 2) + 1;

	} while (s[x1][Y1] != ' ');
	s[x1][Y1] = '*';

}

char key;

int snake_map::update_game()
{
	gameover = 1;
	key = direction;
	start = clock();
	while ((gameover = (clock() - start <= gamespeed)) && !kbhit());//kbhit()函数用于检测当前是否有键盘输入，若有则返回一个非0值，否则返回0值；
	//如果有按键按下或者时间超过自动前进时间间隔，则终止循环
	if (gameover)
	{
		getch();
		key = getch();
	}
	if (key == ' ')
	{
		while (getch() != ' '){};//这里实现的是按空格键暂停，按空格间继续的功能，
	}
	else
		direction = key;
	switch (direction)
	{
	case 72: x = positon[head].x - 1; y = positon[head].y; break;//向上
	case 80:x = positon[head].x + 1; y = positon[head].y; break;//向下
	case 75:x = positon[head].x; y = positon[head].y - 1; break;//向左
	case 77:x = positon[head].x; y = positon[head].y + 1; break;//向右

	}
	if (!(direction == 72 || direction == 80 || direction == 75 || direction == 77))
	{
		gameover = 0;
	}
	else if (x == 0 || x == N - 1 || y == 0 || y == N - 1)
		gameover = 0;
	else if ((s[x][y]!= ' ')&&(!(x == x1&&y == Y1)))
		gameover = 0;
	else if (x == x1&& y == Y1)
	{
		length++;
		if (length >= 8 && gameover)
		{
			length -= 8;
			grade++;
			if (gamespeed >= 200)
				gamespeed -= 200;
			else
				gamespeed = 100;

		}
		s[x][y] ='#';//更新蛇头;
		s[positon[head].x][positon[head].y] = '*';//吃*后的蛇头将变为蛇身
		head = (head + 1) % ((N - 2)*(N - 2));//获取蛇头坐标
		positon[head].x = x;
		positon[head].y = y;
		show_game();
		gameover = 1;
		score += grade * 20;
		setpoint();//产生新的*
	}
	else//不吃*
	{
		s[positon[tail].x][positon[tail].y] = ' ';//将蛇尾置空
		tail = (tail + 1) % ((N - 2)*(N - 2));//更新蛇尾坐标
		s[positon[head].x][positon[head].y] = '*';//将蛇头更新为蛇身
		head = (head + 1) % ((N - 2)*(N - 2));
		positon[head].x = x;
		positon[head].y = y;
		s[positon[head].x][positon[head].y] = '#';//更新舌头
		gameover = 1;

	}
	return gameover;

}

int main()
{
	char ctn = 'y';
	int nodead;
	cout << "\n\n\n\n\n\t\t\t 欢迎进入贪吃蛇游戏" << endl;//欢迎界面
	cout << "\n\n\n\t\t\t 按任意键马上开始。。。" << endl;//准备开始i
	getch();
	while (ctn == 'y')
	{
		system("cls");
		snake_map snake;
		snake.initialize();
		cout << "\n\n请输入数字选择游戏等级： " << endl;
		cout << "\n\n\n\t\t\t:等级一：速度1000 \n\n\t\t\2.等级二：速度800 \n\n\t\t3.等级三：速度600";
		cout << "\n\n\t\t4.等级四：速度400\n\n\t\t5等级五：速度200\n\n\t\t6等级六：速度100\n\n\t\t7.自动升级模式" << endl;
		snake.getgrade();
		for (int i = 1; i <= 4; i++)
		{
			positon[i].initialize(i);//坐标初始化
		}
		snake.setpoint();
		do
		{
			snake.show_game();
			nodead = snake.update_game();
		} while (nodead);

		system("cls");//清屏
		cout << "\n\n\n\t\t\tGameover!\n\n" << endl;
		snake.display();//输出等级和得分情况
		cout << "\n\n\n\t\t 是否选择继续游戏？输入y继续,n退出" << endl;

		cin >> ctn;


	}
	return 0;

}