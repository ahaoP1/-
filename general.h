#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define frameX 10//窗口左上角的X坐标 
#define frameY 10//窗口左上角的y坐标
#define Wide 40//宽度（一个■宽度是2）
#define High 20//高度 
int score;
int a[20][20];//坐标图,若为1则在这个坐标上有蛇的节点 
int direction;//方向1~4顺时针 
typedef struct f//水果 
{
	int x,y;
}Furit;
Furit temp;
typedef struct node//定义蛇的每块节点 
{
	int x,y;//节点的位置
	struct node *next;//下一个节点
}Node,*pHead;
void Move(pHead p);//移动 
void Create(pHead p);
void hideCursor();
int gotoxy(int x,int y);
int color(int c);
void Drawframe();
void welcome();//欢迎界面
void GamePlay();//游戏开始
void Clean();//清理贪吃蛇的轨迹 
void Print();//打印贪吃蛇 
void Gameover();
void Insert(pHead p);//加长贪吃蛇
void fruit();//生成“水果”
void fruit()
{
	
	srand(time(NULL));
	temp.x=rand()%18+1;
	temp.y=rand()%18+1;
	while(a[temp.x][temp.y]==1)
	{
		temp.x=rand()%18+1;
		temp.y=rand()%18+1;
	}
	
	a[temp.x][temp.y]=2;
} 
void Insert(pHead p)
{
	Node *pNew,*r;
	r=p;
	pNew=(Node*)malloc(sizeof(Node));
	pNew->next=NULL;
	while(r->next!=NULL)
	{
		r=r->next;
	}
	r->next=pNew;
	r->next->x=r->x;
	r->next->y=r->y;
	r=r->next;
}
void Gameover()
{
	score=0;
	direction=0; 
	int i,j;
	for(i=0;i<20;i++)
	{
		for(j=0;j<20;j++)
		{
			a[i][j]=0;
		}
	}
	system("cls");
	welcome();
}
void Move(pHead p)
{
	int tempX,tempY; 
	Node *r;
	r=p;
	switch(direction)
	{
		case 1://向上 
			if(p->y==0||a[p->x][p->y-1]==1)
			{
				Gameover();
				break;
			}
			a[p->x][p->y]=0;
			tempX=p->x;
			tempY=p->y;
			p->y--;
			a[p->x][p->y]=1;
			break;
		case 2://向右 
			if(p->x==19||a[p->x+1][p->y]==1)
			{
				Gameover();
				break;
			}
			tempX=p->x;
			tempY=p->y;
			a[p->x][p->y]=0;
			p->x++;
			a[p->x][p->y]=1;
			break;
		case 3://向下
			if(p->y==19||a[p->x][p->y+1]==1)
			{
				Gameover();
				break;
			}
			tempX=p->x;
			tempY=p->y;
			a[p->x][p->y]=0;
			p->y++;
			a[p->x][p->y]=1;
			break;
		case 4://向左
			if(p->x==0||a[p->x-1][p->y]==1)
			{
				Gameover();
				break;
			}
			tempX=p->x;
			tempY=p->y;
			a[p->x][p->y]=0;
			p->x--;
			a[p->x][p->y]=1;
	}
	while(r->next!=NULL)
	{
		int posX,posY;
		a[r->next->x][r->next->y]=0;
		posX=r->next->x;
		posY=r->next->y;
		r->next->x=tempX;
		r->next->y=tempY;
		tempX=posX;
		tempY=posY;
		a[r->next->x][r->next->y]=1;
		r=r->next;
	}
	if(p->x==temp.x&&p->y==temp.y)
	{
		Insert(p);
		a[temp.x][temp.y]=1;
		score++;
		fruit();
	}
}
void Print()
{
	int i,j;
	for(i=0;i<20;i++)
	{
		for(j=0;j<20;j++)
		{
			if(a[i][j]==2)
			{
				gotoxy(2*i+frameX+2,j+frameY+1);
				color(7);
				printf("□"); 
			}
			else if(a[i][j]==1)
			{
				gotoxy(2*i+frameX+2,j+frameY+1);
				color(9);
				printf("■");
			}
		}
	}
	gotoxy(60,14);
	color(4);
	printf("现在的得分是:%d",score);
	
}
void Clean()
{
	int i,j;
	for(i=0;i<20;i++)
	{
		for(j=0;j<20;j++)
		{
			if(a[i][j]==1)
			{
				gotoxy(2*i+frameX+2,j+frameY+1);
				printf("  ");
			}
		}
	}	
}
void GamePlay()
{
	clock_t stime=0,ftime=0;
	system("cls");
	hideCursor();
	pHead p;
	p=(Node*)malloc(sizeof(Node));
	p->next=NULL;
	Drawframe();
	Create(p);
	stime=clock();//初始化stime 
	fruit();
	while(1)
	{
		ftime=clock();
		Print();
		if(kbhit())
		{
			char ch=getch();
			switch(ch)
			{
				case 72:
					if(direction!=3)
					direction=1;	
					break;
				case 77:
					if(direction!=4)
					direction=2;	
					break;
				case 80:
					if(direction!=1)
					direction=3;
					break;
				case 75:
					if(direction!=2)
					direction=4;
					break;
			}
		}
		if(ftime-stime>=200)
		{
			Clean();
			Move(p);
			stime=clock();	
		}
	}
} 
void Create(pHead p)
{
	srand(time(NULL));//初始化随机函数，方便一会儿随机生成蛇的坐标 
	p->x=rand()%15+1;//x坐标范围为5~15
	p->y=rand()%15+1;//y也一样
	a[p->x][p->y]=1;
}
void hideCursor()
{
	CONSOLE_CURSOR_INFO info;
	info.dwSize=1;
	info.bVisible=0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&info);
}
void welcome()
{
	int i,j;
	int n;
	for(i=frameX;i<=frameX+Wide+2;i+=2)
	{
		for(j=frameY;j<=frameY+High/2+1;j++)
		{
			if(i==frameX||i==frameX+Wide+2)
			{
				gotoxy(i,j);
				color(14);
				printf("□");
			}
			else if(j==frameY||j==frameY+High/2+1)
			{
				gotoxy(i,j);
				color(14);
				printf("□");
			}
		}
	}
	gotoxy(16,12);
	color(11);
	printf("1.开始游戏");
	gotoxy(36,12);
	color(12);
	printf("2.退出游戏");
	gotoxy(frameX+Wide/2-4,frameY+High/2+2);
	color(10);
	printf("请选择:[ ]\b\b");
	scanf("%d",&n);
	switch(n)
	{
		case 2:
			exit(0);
			break;
		case 1:
			GamePlay();
			break;
	}
} 
void Drawframe()
{
	int i,j;
	for(i=frameX;i<=frameX+Wide+2;i+=2)
	{
		for(j=frameY;j<=frameY+High+1;j++)
		{
			if(i==frameX||i==frameX+Wide+2)
			{
				gotoxy(i,j);
				color(14);
				printf("□");
			}
			else if(j==frameY||j==frameY+High+1)
			{
				gotoxy(i,j);
				color(14);
				printf("□");
			}
		}
	}
}
int gotoxy(int x,int y)
{
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
