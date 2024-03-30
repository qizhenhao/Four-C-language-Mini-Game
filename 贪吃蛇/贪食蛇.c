#include<stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include<time.h> 
void clearScreen(){    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = { 0, 0 };    
    SetConsoleCursorPosition( hConsole, coordScreen );
} 
struct point{
	int x,y;
};
struct {
	struct point xy[100];
	int dir;
	int _long;
}snke;
struct {
	int x,y;
	int grade;
}food;
int map[50][100];
int graded=0;
/*----------------------·Ö¸îÏß-----------------------*/
int snk()		
{
	int i;
	snke.dir=3;
	snke.xy[0].x =10;
	snke.xy[0].y =10;
	snke.xy[1].x =10;
	snke.xy[1].y =9;
	snke.xy[2].x =10;
	snke.xy[2].y =8;
	snke.xy[3].x =10;
	snke.xy[3].y =7;
	snke._long=4;
	for(i=0;i<snke._long;i++)
	{	
		map[snke.xy[i].y][snke.xy[i].x]='@';
	}
}
int movsnk()		
{
	int i;
	map[snke.xy[snke._long-1].y][snke.xy[snke._long-1].x]=' ';
	for(i=snke._long-1;i>0;i--)
	{		
		snke.xy[i].x=snke.xy[i-1].x;
		snke.xy[i].y=snke.xy[i-1].y;
	}
	switch(snke.dir)
	{
		case 1: snke.xy[0].y-=1;break;
		case 2: snke.xy[0].x-=1;break;
		case 3: snke.xy[0].y+=1;break;
		case 4: snke.xy[0].x+=1;break;
	}
	map[snke.xy[0].y][snke.xy[0].x]='@';
}
int hua()
{
	int timme();
	int i,j;
	for(i=0;i<50;i++)
	{
		for(j=0;j<100;j++)
		{	
			printf("%c",map[i][j]);
			if(i==4&&j==99)
			{
				printf("you are grade:%d    ",graded);
			}
			if(i==5&&j==99)
			{
				timme();
			}
		
		}
		printf("\n");
	}
}
int mapp()
{
	int i,j;
	for(i=0;i<50;i++)
	{
		map[i][0]='#';
		map[i][99]='#';
	}
	for(i=0;i<100;i++)
	{
		map[0][i]='#';
		map[49][i]='#';
	}
	for(i=1;i<49;i++)
	{
		for(j=1;j<99;j++)
			map[i][j]=' ';
	}
	for(i=0;i<50;i++)
	{
		for(j=0;j<100;j++)
		{
			printf("%c",map[i][j]);

		}
		printf("\n");
	}
	
}
int key()
{
	char use=_getch();
	switch(use)
	{
		case'w':
		case'W':
		case 72:
			if(snke.dir!=3)
				snke.dir=1;
			break;
		case's':
		case'S':
		case 80:
			if(snke.dir!=1)
				snke.dir=3;
			break;
		case'a':
		case'A':
		case 75:
			if(snke.dir!=4)
				snke.dir=2;
			break;
		case'd':
		case'D':
		case 77:
			if(snke.dir!=2)
				snke.dir=4;
			break;
	}
}
int foood()
{
	food.grade=10;
	food.x=(int)rand()%100;
	food.y=(int)rand()%50;
	if(map[food.y][food.x]!=' ')
	foood();
}
int fooood()
{
	map[food.y][food.x]='*';
}
int foooood()
{
	if(snke.xy[0].x==food.x&&snke.xy[0].y==food.y){
		snke._long++;
		graded+=food.grade;
		return 1;
	}
	return 0;
}
int die()
{
	if(snke.xy[0].x==0||snke.xy[0].y==0||snke.xy[0].x==99||snke.xy[0].y==49)
	{
		printf("you are die");
		return 1;
	}
	return 0;
}
int timme()
{
	time_t now ;
    struct tm *tm_now ;
    time(&now) ;
    tm_now = localtime(&now) ;
	printf("now datetime: %d-%d-%d %d:%d:%d",tm_now->tm_year+1900, tm_now->tm_mon+1, tm_now->tm_mday, tm_now->tm_hour, tm_now->tm_min, tm_now->tm_sec) ;
}
int main()
{
	char use;
	mapp();
	snk();
	foood();
	while(1)
	{
		clearScreen();	
		movsnk();
		hua();
		if(_kbhit())
		{
			key();
		}
		
		fooood();
		if(foooood())
		{
			foood();
		}
		if(die())
		{
			break;
		}
		Sleep(100);
	
	}	
	

}
