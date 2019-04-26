#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>

#define up 'w'
#define down 's'
#define left 'a'
#define right 'd'
#define stop 'p'
const int GameOver = 0;

void WelcomeUI();        //开始界面
void SetCursorXY(int x,int y);      //设置光标位置
void DrawWallInXYPos(int x,int y);  //在xy位置绘制墙壁
void DrawBorder();       //绘制墙壁
void CreateFood();       //创建食物
int  SnakeMoveControl(); //控制蛇的移动
bool IsDead();           //判断蛇是否死亡
void ShowGameOverUI();   //显示结束界面
void MovingBody();       //蛇移动身体
void Eating();           //吃

typedef struct _SnakeBody
{
	int x;
	int y;
	struct _SnakeBody *next;
}snakeBody;

snakeBody *head,*tail;

struct Food
{
	int x;
	int y;
}food;

char name[20];
int  score = 0;
char click = 1;//这是ascii码
int  speed=0

int main()
{
	system("color 0B");
	system("mode con cols=100 lines=30");
	WelcomeUI();
	DrawBorder();
	CreateFood();
	if(SnakeMoveControl()==0)
		return 0;

	return 0;
}

/********************************/

void SetCursorXY(int x,int y)
{
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput,pos);
}

void WelcomeUI()
{
	SetCursorXY(22,5);
	printf("/******************************************************/");
	SetCursorXY(22,17);
	printf("/******************************************************/");
	SetCursorXY(27,8);
	printf("Welcome To The Game Of Greedy Snake");
	SetCursorXY(20,11);
	printf("请在英文输入法中操作，反向移动等于吃到自己，WASD控制，P暂停");
	SetCursorXY(27,14);
	printf("Please Enter Your Name:");
	scanf("%s",&name,10);
	system("cls");
}

void DrawWallInXYPos(int x,int y)
{
	SetCursorXY(x,y);
	printf("■");
}

void DrawSnakeHead(int x,int y)
{
	SetCursorXY(x,y);
	printf("●");
}

void DrawBorder()
{
	for(int i=0;i<58;i+=2)
	{
		DrawWallInXYPos(i,0);
		DrawWallInXYPos(i,26);
	}

	for(int y=0;y<26;y++)
	{
		DrawWallInXYPos(0,y);
		DrawWallInXYPos(56,y);
	}

	SetCursorXY(63,10);
	printf("hello %s,Welcome To Play",name);
	SetCursorXY(63,15);
	printf("Your Score Is:%d   =￣ω￣=",score);
	SetCursorXY(63,20);
	printf("This Game Is Created By CaoHao");

	head = (snakeBody*)malloc(sizeof(snakeBody));
	head->x = 16;
	head->y = 15;
	//DrawSnakeHead(head->x,head->y);
	//SetCursorXY(head->x,head->y);
	tail = (snakeBody*)malloc(sizeof(snakeBody));
	snakeBody *p = (snakeBody*)malloc(sizeof(snakeBody));
	snakeBody *q = (snakeBody*)malloc(sizeof(snakeBody));
	p->x = 16;
	p->y = 16;
	//DrawWallInXYPos(p->x,p->y);
	q->x = 16;
	q->y = 17;
	head->next = p;
	p->next = q;
	q->next = tail;
	tail->next = NULL;
	tail->x = 4;
	tail->y = 2;

	//DrawWallInXYPos(q->x,q->y);
	//SetCursorXY(head->x,head->y);

}

void CreateFood()
{
	srand((int)time(NULL));
label:
	food.y = rand() % 25 + 1;
	food.x = rand() % 53 + 2;
	if(food.x % 2 != 0)
	{
		food.x = food.x + 1;
	}
	snakeBody *judge = head;
	while(1)  //遍历排除蛇身重复
	{
		if(judge->next == NULL) break;
		if(food.x == judge->x && food.y == judge->y)
		{
			goto label;
		}
		judge = judge->next;
	}
	SetCursorXY(food.x,food.y);
	printf("⊙");
}

int SnakeMoveControl()
{
	char c;
	while(1)
	{
		if(IsDead()) return GameOver;//死亡
		if(_kbhit())
		{
			click = _getch();
		}
		MovingBody();
		Eating();
	}
	return 1;
}

bool IsDead()
{
	if(head->x == 0 || head->x == 56 || head->y == 0 || head->y == 26)
	{
		ShowGameOverUI();
		return true;
	}
	snakeBody *p = head->next;//这是指向第二节身子的指针
	while(1)
	{
		if(p->next == NULL)break;
		if(head->x == p->x && head->y == p->y)
		{
			ShowGameOverUI();
			return true;
		}
		p=p->next;
	}

	return false;
}

void ShowGameOverUI()
{
	system("cls");
	SetCursorXY(15,10);
	printf("/*****************************************/");
	SetCursorXY(15,20);
	printf("/*****************************************/");
	SetCursorXY(18,14);
	printf("Game Over      o(*￣V￣*)o");
	SetCursorXY(20,16);
	printf("Your Score is %d    xiuxiuxiu",score);
	SetCursorXY(18,18);
	printf("还不错哦，   继续努力o(n_n)o");
	SetCursorXY(0,27);
	system("pause");
}

void MovingBody()
{
	
}

void Eating()
{
	
}