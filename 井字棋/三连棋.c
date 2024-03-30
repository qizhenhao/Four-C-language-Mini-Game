#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>
/*定义棋盘*/
struct{
	int map[4][4];
	int gx,gy;   /*光标的位置*/
}map;
const int white='o',black='x';
int betterMove_x=2,betterMove_y=2;
int value;
/*************/
int  compterPlace();
int  personPlace(); 
void clearScreen();
void chuShiJieMian();
void printQiPan();
int moveGuang(int key,int zi);
int  panDuanVictory(int zi);
int  panDuanDraw();
int  IsEmpty(int x,int y);
int place(int zi,int x,int y);
int jieJu(int zi);
/***********/
int main()
{
	  chuShiJieMian();
	  int p,key=0,zi=white;
	  p=_getch();
	  if(p=='1')
	  {
	  	system("cls");
		while(1)
		{
		  	clearScreen();
			system("cls"); 
			printQiPan();
		  	key=_getch();
		  	if(moveGuang(key,zi))
		  	{
		  		if(jieJu(zi))
		  			return 0;
		  		if(zi==white)
		  			zi=black;
		  		else
		  			zi=white;
		  	}
		}
      }
      else if(p=='2')
      {
		system("cls");
      	while(1)
      	{
      		int i;
      		clearScreen();
			
      		printQiPan();
			key=_getch();
			if(moveGuang(key,zi))
		  	{
		  		if(jieJu(zi))
		  			return 0;
		  		compterPlace(zi==white?black:white,&betterMove_x,&betterMove_y,&value);
		  		place(zi==white?black:white,betterMove_x,betterMove_y);
			}
				if((i=jieJu(black))==1)
		  			return 0;
				else if(i==2)
				{
					printf("\n爱拼才会赢！！！");
					system("pause");
					return 0;
				}
		}
      }
}
int jieJu(int zi)
{
	if(panDuanVictory(zi))
	{
		printf("%c胜利",zi);
		system("pause");
		return 2;
	}
	else
	if(panDuanDraw())
	{
		printf("平局");
		system("pause");
		return 1;
	}
	return 0;
}
void clearScreen(){    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = { 0, 0 };    
    SetConsoleCursorPosition( hConsole, coordScreen );
}
int  IsEmpty(int x,int y)
{
	return map.map[x][y]==' ';
}
void chuShiJieMian()
{
	printf("         五子棋\n");
	printf("        1.人人对战\n");
	printf("        2.人机对战");
	int i,j;
	for(i=1;i<=3;i++)
	{
		for(j=1;j<=3;j++)
		{
			map.map[i][j]=' ';
		}
	} 
	map.gx=2;
	map.gy=2;
}
void printQiPan()
{
	int i,j;
	for(i=1;i<=3;i++)
	{
		for(j=1;j<=3;j++)
		{
			if(i==map.gx&&j==map.gy)
			{
				if(IsEmpty(map.gx,map.gy))
					printf("@");
				else
				{
					if(map.map[map.gx][map.gy]==white)
					{
						printf("O");
					}
					else
					{
						printf("X");
					}
				}
				
			}
			else
			{
				printf("%c",map.map[i][j]);
			}
			if(j!=3)
				printf("|");
			
		}
		printf("\n------\n");
	} 
}
int moveGuang(int key,int zi)
{

	switch(key)
	{
		case 119:
		case 72:
			if(map.gx!=1)
			map.gx--;
		break;
		case 97:
		case 75:
			if(map.gy!=1)
			map.gy--;
		break;
		case 80:
		case 115:
			if(map.gx!=3)
			map.gx++;
		break;
		case 100:
		case 77:
			if(map.gy!=3)
			map.gy++;
		break;
		case '0':
			return place(zi,map.gx,map.gy); 
	}
	return 0;
}
int  panDuanVictory(int zi)
{
	int i,j;
	for(i=1;i<=3;i++)
	{
		if(map.map[i][1]==zi&&map.map[i][2]==zi&&map.map[i][3]==zi)
		{
			return 1;
		}
	}
	for(j=1;j<=3;j++)
	{
		if(map.map[1][j]==zi&&map.map[2][j]==zi&&map.map[3][j]==zi)
		{
			return 1;
		}	
	}
	if(map.map[1][1]==zi&&map.map[2][2]==zi&&map.map[3][3]==zi)
	return 1;
	if(map.map[1][3]==zi&&map.map[2][2]==zi&&map.map[3][1]==zi)
	return 1;
	return 0;
}
int  panDuanDraw()
{
	int i,j;
	for(i=1;i<=3;i++)
	{
		for(j=1;j<=3;j++)
		{
			if(IsEmpty(i,j))
				return 0;
		}	
	}
	return 1;
}
int place(int zi,int x,int y)
{
	if(!IsEmpty(x,y))
		return 0;
	map.map[x][y]=zi;
	return 1;
}
int unPlace(int zi,int x,int y)
{
	if(IsEmpty(x,y))
		return 0;
	map.map[x][y]=' ';
	return 1;
	
}

int  compterPlace(int zi,int *x,int *y,int*value)
{
	int i,j,found,x1,y1;
	if(panDuanVictory(zi==white?black:white))
		*value=-1;
	else if(panDuanDraw())
		*value=0;
	else
	{
		*value=-1;
		for(i=1;i<=3;i++)
		{
			for(j=1;j<=3;j++)
			{
				if(IsEmpty(i,j))
				{
					place(zi,i,j);
					personPlace(zi==black?white:black,&x1,&y1,&found);
					unPlace(zi,i,j); 
				
					if(*value<=found)
					{
						*value=found;
						*x=i;
						*y=j;
						if(*value==1)
						return 0;
					}
				}
			}
		}
	
	}
}
int  personPlace(int zi,int*x,int*y,int*value)
{
	int i,j,found,x1,y1;
	if(panDuanVictory(zi==white?black:white))
		*value=1;
	else if(panDuanDraw())
		*value=0;
	else
	{
		*value=1;
		for(i=1;i<=3;i++)
		{
			for(j=1;j<=3;j++)
			{
				if(IsEmpty(i,j))
				{
					place(zi,i,j);
					compterPlace(zi==black?white:black,&x1,&y1,&found);
					unPlace(zi,i,j);
					
					if(*value>=found)
					{
						*value=found;
						*x=i;
						*y=j;
						if(*value==-1)
						return 0; 
					}	
				}
			}
		}
	}
}

