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
int x1,Y1;//�������ֵ
int x, y;
long start;
//=====================================
//���ʵ����Ӧ��
//==========================

//����̰���ߵ�����
class snake_position
{
public:
	int x, y;
	snake_position(){};
	void initialize(int &);//�����ʼ��
};


snake_position positon[(N - 2)*(N - 2) + 1];//����̰�������������飬��N-2*N-2������

void snake_position::initialize(int &j)
{
	x = 1;
	y = j;
}


// ����̰���ߵ�����ͼ
class snake_map
{
private:
	char s[N][N];//����̰��������
	int grade, length;
	int gamespeed;//����ʱ����
	char direction;//ȷ����ʼ�ƶ�����
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
//�����ʼ����������̰���ߵ�����ͼ���г�ʼ��

void snake_map::initialize()
{
	int i, j;
	for (i = 1; i <= 3; i++)//��̰���߽����еĳ�״̬��������
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
		s[0][i] = s[N - 1][i] = '-';//��ʼ��̰���������е�����ǽ��
	for (i = 1; i <= N - 2; i++)
		s[i][0] = s[i][N - 1] = '|';//��ʼ��̰�����������ұ�Եǽ��

}
//����̰����������Ϣ

void snake_map::show_game()
{
	system("cls");//����
	int i, j;
	cout << endl;
	for (i = 0; i < N; i++)
	{
		cout << "\t";
		for (j = 0; j < N; j++)
			cout << s[i][j] << ' ';//���̰��������
		if (i == 2)cout << "\t �ȼ���" << grade;
		if (i == 6)cout << "\t�ٶȣ�" << gamespeed;
		if (i == 10)cout << "\t�÷�:" << score;
		if (i == 14)cout << "\t��ͣ����һ�¿ո��";
		if (i == 18)cout << "\t�����������¿ո��";
	    cout << endl;
	}
}


//����ѡ��ȼ�
void snake_map::getgrade()
{
	cin >> grade;
	while (grade > 7 || grade < 1)
	{
		cout << "����������1-7ѡ��ȼ����������ַ���Ч" << endl;
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
//����ȼ����÷�����Լ��ƺ�
void snake_map::display()
{
	cout << "\n\t\t\t\t�ȼ�" << endl;
	cout << "\n\n\n\t\t\t\t�ٶ�" << gamespeed;
	cout << "\n\n\n\t\t\t\t�÷�" << score << endl;
}

//�������̰���ߵ�ʳ��
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
	while ((gameover = (clock() - start <= gamespeed)) && !kbhit());//kbhit()�������ڼ�⵱ǰ�Ƿ��м������룬�����򷵻�һ����0ֵ�����򷵻�0ֵ��
	//����а������»���ʱ�䳬���Զ�ǰ��ʱ����������ֹѭ��
	if (gameover)
	{
		getch();
		key = getch();
	}
	if (key == ' ')
	{
		while (getch() != ' '){};//����ʵ�ֵ��ǰ��ո����ͣ�����ո������Ĺ��ܣ�
	}
	else
		direction = key;
	switch (direction)
	{
	case 72: x = positon[head].x - 1; y = positon[head].y; break;//����
	case 80:x = positon[head].x + 1; y = positon[head].y; break;//����
	case 75:x = positon[head].x; y = positon[head].y - 1; break;//����
	case 77:x = positon[head].x; y = positon[head].y + 1; break;//����

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
		s[x][y] ='#';//������ͷ;
		s[positon[head].x][positon[head].y] = '*';//��*�����ͷ����Ϊ����
		head = (head + 1) % ((N - 2)*(N - 2));//��ȡ��ͷ����
		positon[head].x = x;
		positon[head].y = y;
		show_game();
		gameover = 1;
		score += grade * 20;
		setpoint();//�����µ�*
	}
	else//����*
	{
		s[positon[tail].x][positon[tail].y] = ' ';//����β�ÿ�
		tail = (tail + 1) % ((N - 2)*(N - 2));//������β����
		s[positon[head].x][positon[head].y] = '*';//����ͷ����Ϊ����
		head = (head + 1) % ((N - 2)*(N - 2));
		positon[head].x = x;
		positon[head].y = y;
		s[positon[head].x][positon[head].y] = '#';//������ͷ
		gameover = 1;

	}
	return gameover;

}

int main()
{
	char ctn = 'y';
	int nodead;
	cout << "\n\n\n\n\n\t\t\t ��ӭ����̰������Ϸ" << endl;//��ӭ����
	cout << "\n\n\n\t\t\t ����������Ͽ�ʼ������" << endl;//׼����ʼi
	getch();
	while (ctn == 'y')
	{
		system("cls");
		snake_map snake;
		snake.initialize();
		cout << "\n\n����������ѡ����Ϸ�ȼ��� " << endl;
		cout << "\n\n\n\t\t\t:�ȼ�һ���ٶ�1000 \n\n\t\t\2.�ȼ������ٶ�800 \n\n\t\t3.�ȼ������ٶ�600";
		cout << "\n\n\t\t4.�ȼ��ģ��ٶ�400\n\n\t\t5�ȼ��壺�ٶ�200\n\n\t\t6�ȼ������ٶ�100\n\n\t\t7.�Զ�����ģʽ" << endl;
		snake.getgrade();
		for (int i = 1; i <= 4; i++)
		{
			positon[i].initialize(i);//�����ʼ��
		}
		snake.setpoint();
		do
		{
			snake.show_game();
			nodead = snake.update_game();
		} while (nodead);

		system("cls");//����
		cout << "\n\n\n\t\t\tGameover!\n\n" << endl;
		snake.display();//����ȼ��͵÷����
		cout << "\n\n\n\t\t �Ƿ�ѡ�������Ϸ������y����,n�˳�" << endl;

		cin >> ctn;


	}
	return 0;

}