#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define frameX 10//�������Ͻǵ�X���� 
#define frameY 10//�������Ͻǵ�y����
#define Wide 40//��ȣ�һ���������2��
#define High 20//�߶� 
int score;
int a[20][20];//����ͼ,��Ϊ1����������������ߵĽڵ� 
int direction;//����1~4˳ʱ�� 
typedef struct f//ˮ�� 
{
	int x,y;
}Furit;
Furit temp;
typedef struct node//�����ߵ�ÿ��ڵ� 
{
	int x,y;//�ڵ��λ��
	struct node *next;//��һ���ڵ�
}Node,*pHead;
void Move(pHead p);//�ƶ� 
void Create(pHead p);
void hideCursor();
int gotoxy(int x,int y);
int color(int c);
void Drawframe();
void welcome();//��ӭ����
void GamePlay();//��Ϸ��ʼ
void Clean();//����̰���ߵĹ켣 
void Print();//��ӡ̰���� 
void Gameover();
void Insert(pHead p);//�ӳ�̰����
void fruit();//���ɡ�ˮ����
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
		case 1://���� 
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
		case 2://���� 
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
		case 3://����
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
		case 4://����
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
				printf("��"); 
			}
			else if(a[i][j]==1)
			{
				gotoxy(2*i+frameX+2,j+frameY+1);
				color(9);
				printf("��");
			}
		}
	}
	gotoxy(60,14);
	color(4);
	printf("���ڵĵ÷���:%d",score);
	
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
	stime=clock();//��ʼ��stime 
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
	srand(time(NULL));//��ʼ���������������һ�����������ߵ����� 
	p->x=rand()%15+1;//x���귶ΧΪ5~15
	p->y=rand()%15+1;//yҲһ��
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
				printf("��");
			}
			else if(j==frameY||j==frameY+High/2+1)
			{
				gotoxy(i,j);
				color(14);
				printf("��");
			}
		}
	}
	gotoxy(16,12);
	color(11);
	printf("1.��ʼ��Ϸ");
	gotoxy(36,12);
	color(12);
	printf("2.�˳���Ϸ");
	gotoxy(frameX+Wide/2-4,frameY+High/2+2);
	color(10);
	printf("��ѡ��:[ ]\b\b");
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
				printf("��");
			}
			else if(j==frameY||j==frameY+High+1)
			{
				gotoxy(i,j);
				color(14);
				printf("��");
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
