#undef UNICODE
#undef _UNICODE
#include<stdio.h>
#include<stdlib.h>
#include <graphics.h>		// 引用图形库头文件
#include <conio.h>
#include<time.h>
struct pai {
	int daXiao;
	int huaSe;
	int chu;
};
struct people {
	struct pai pai[20];
	int shu;
	int shen;
}wanJia,dian1,dian2;
struct suoYouPai {
	struct pai pai[54];
}quanBu;
struct dizhupai {
	struct pai dizhu[3];
}diZhuPai;
struct paiDui {
	int h;
	int dan;
	int daXiao[20];
	int con;
	struct people* ren;
}dui;
constexpr int ciDian[15] = { 3,4,5,6,7,8,9,10,11,12,13,1,2,14,15 };
/*----------------*/
void printGround();
void isDiZhu();
void printPai();
void paiChuShi();//把52张牌导入
void xiPai();	 //洗牌
void faPai();	//发牌（地主牌与3个人的牌分开）
void Swap(struct pai& a, struct pai& b);//交换牌
void sort_pai(struct pai *a,int len);//装牌
int xuanPai();//选牌并判断是否要出牌
int  chuPai(struct people &ren);//判断是否能出
int jieShu();
int  giuJu(const struct people* ren);
void printChuPai(const struct people* ren);
void printPaiH(struct pai p, int x, int y);
void comper(struct people& dian);
int  Pan_da_xiao(int* a,int con,int c);
int cidian(int a);
/*----------------*/
int main()
{
	char a;
	initgraph(950, 500);	// 创建绘图窗口，大小为 640x480 像素
	printGround();
	paiChuShi();//把52张牌导入
	xiPai();	 //洗牌
	faPai();
	printPai();
	isDiZhu();
	printPai();
	while (1)
	{
		if (xuanPai())
		{
			break;
		}
		printGround();
		printPai();
	}
	a=_getch();				// 按任意键继续
	closegraph();			// 关闭绘图窗口
	return 0;
}
int jieShu()
{
	if (wanJia.shu == 0)
		if (wanJia.shen == 0)
		{
			outtextxy(450, 200, "农民胜利");
			return 1;
		}
		else
		{
			outtextxy(450, 200, "地主胜利");
			return 1;
		}
	if (dian1.shu == 0)
		if (dian1.shen == 0)
		{
			outtextxy(450, 200, "农民胜利");
			return 1;
		}
		else
		{
			outtextxy(450, 200, "地主胜利");
			return 1;
		}
	if (dian2.shu == 0)
		if (dian2.shen == 0)
		{
			outtextxy(450, 200, "农民胜利");
			return 1;
		}
		else
		{
			outtextxy(450, 200, "地主胜利");
			return 1;
		}
	return 0;
}
void comper(struct people& dian)
{
	int i;
	if (dian.shu < dui.con&&dui.ren!=&dian)
		return;
	else
	{
		if (dui.ren == &dian)
			dui.con = 1;
		for (i = 0; i <= dian.shu - dui.con; i++)
		{
			for (int j = i; j < i + dui.con; j++)
			{
				dian.pai[j].chu = ~dian.pai[j].chu;
			}
			if (chuPai(dian))
			{
				break;
			}
		}
	}
}
void printChuPai(const struct people* ren)
{
	int con = 0;
	for (int i=0; i < ren->shu ; i++)
	{
		if (ren->pai[i].chu != 0)
		{
			fillrectangle(350+con*40, 80, 430+ con * 40,200 );
			printPaiH(ren->pai[i], 355 + con * 40, 150);
			con++;
		}
	}
	Sleep(1000);
}
int xuanPai() 
{
	fillrectangle(300, 220, 400, 290);
	fillrectangle(500, 220, 600, 290);
	outtextxy(330, 250, "不出");
	outtextxy(530, 250, "出");
	MOUSEMSG M;
	while (1)
	{
		M = GetMouseMsg();
		if ((M.x >= 300 && M.x <= 400) && (M.y >= 220 && M.y <= 290) && (M.uMsg == WM_LBUTTONDOWN))//bu chu
		{
			for (int i = 0; i < wanJia.shu; i++)
			{
				wanJia.pai[i].chu = 0;
			}
			comper(dian2);
			if (jieShu())
			{
				return 1;
			}
			comper(dian1);
			if (jieShu())
			{
				return 1;
			}
			break;
		}
		else
		if ((M.x >= 500 && M.x <= 600) && (M.y >= 220 && M.y <= 290) && (M.uMsg == WM_LBUTTONDOWN))//chu
		{
			if (chuPai(wanJia))
			{
				if (jieShu())
				{
					return 1;
				}
				comper(dian2);
				if (jieShu())
				{
					return 1;
				}
				comper(dian1);
				if (jieShu())
				{
					return 1;
				}
			}
			break;
		}
		else if ((M.x >= 80 && M.x <= wanJia.shu*40+80+40) && (M.y >= 300 && M.y <= 450) && (M.uMsg == WM_LBUTTONDOWN))
		{
			int a=M.x;
			a -= 80;
			wanJia.pai[(int)a / 40].chu = ~ wanJia.pai[(int)a / 40].chu;
			break;
		}
	}
	return 0;
}
int isShunZi(int b[],int con)
{
	int j,i,c[20]={0}, c1 = 0, min = 15, p = 0;
	for(j=0;j<con;j++)
		for (i = 0; i < 15; i++)
		{
			if (b[j] == ciDian[i])
			{
				c[c1++] = i;
				if (min > i)
				{
					min = i;
					p = c1 - 1;
				}
				break;
			}
		}
	i = p;
	j = (p+1) % c1;
	while (j != p)
	{
		if (c[i] + 1 != c[j])
			break;
		i = (i + 1) % c1;
		j = (j + 1) % c1;
	}
	if (j == p)
		return 1;
	else
		return 0;
}
int  giuJu(const struct people * ren)//单返回1 双返回2 三返回3 三代1返回4 三代2返回5 5顺子返回6 炸弹返回7 炸带双返回8 天王炸返回9 3联顺10 6顺反11 7顺反12 ...
{
	int i,a[20],con=0;
	for (i = 0; i < ren->shu; i++)
	{
		if(ren->pai[i].chu!=0)
		a[con++] = ren->pai[i].daXiao;
	}
	if (con == 0)
	{
		return 0;
	}
	if (con == 1)
	{
		return 1;
	}
	else if (con == 2)
	{
		if (a[0] == 14 && a[1] == 15)
			return 9;
		if (a[0] == a[1])
			return 2;
		else
		{
			return 0;
		}
	}
	else if (con == 3)
	{
		if (a[0] == a[1] && a[0] == a[2])
			return 3;
		else
			return 0;
	}
	else if (con == 4)
	{
		if (a[0] == a[1] && a[1] == a[2] && a[2] == a[3])
		{
			return 7;
		}
		else if ((a[0] == a[1] && a[0] == a[2]) || (a[1] == a[2] && a[1] == a[3]))
			return 4;
		else
			return 0;
	}
	else if (con == 5)
	{
		if (a[0] == a[1] && a[0] == a[2])
		{
			if (a[3] == a[4])
				return 5;
			return 0;
		}
		else if (a[2] == a[3] && a[2] == a[4])
		{
			if (a[0] == a[1])
				return 5;
			return 0;
		}
		else if (isShunZi(a, con))
		{
			return 6;
		}
		else
			return 0;
	}
	else if (con == 6)
	{
		if (a[0] == a[1] && a[1] == a[2] && a[2] == a[3])
		{
			return 8;
		}
		if (a[2] == a[3] && a[3] == a[4] && a[4] == a[5])
		{
			return 8;
		}
		if (a[0] == a[1] && a[1] == a[2] && a[3] == a[4] && a[4] == a[5])
			return 10;
		if (isShunZi(a, con))
			return 11;
		return 0;
	}
	else if (isShunZi(a, con))
		return con+5;
	return 0;
}
int  chuPai(struct people &ren)
{
	int i=0, a[20], con = 0,c=1,j;
	for (i = 0; i < ren.shu; i++)
	{
		if (ren.pai[i].chu != 0)
			a[con++] = ren.pai[i].daXiao;
	}
	c = giuJu(&ren);
	if (c == 0)
	{
		for (int i=0; i < ren.shu; i++)
		{
			ren.pai[i].chu = 0;
		}
		return 0;
	}
	if (dui.ren != NULL && dui.ren == &ren)
		dui.h = 0;
	if (dui.h == 0)
	{
		dui.ren = &ren;
		dui.h = 1;
		dui.dan = c;
		for (int i = 0; i < con; i++)
		{
			dui.daXiao[i] = a[i];
		}
		i = 0;
		j = ren.shu-1;
		while (i < j)
		{
			while (i < ren.shu && ren.pai[i].chu == 0)i++;
			while (j >= 0 && ren.pai[j].chu != 0)j--;
			if (i < j) {
				Swap(ren.pai[i],ren.pai[j]);
			}
		}
		printChuPai(&ren);
		ren.shu -= con;
		dui.con = con;
		sort_pai(ren.pai, ren.shu);
		return 1;
	}
	else
	{
		if (Pan_da_xiao(a,con,c))
		{

				dui.ren = &ren;
				dui.h = 1;
				dui.dan = c;
				for (int i = 0; i < con; i++)
				{
					dui.daXiao[i] = a[i];
				}
				i = 0;
				j = ren.shu - 1;
				while (i < j)
				{
					while (i < ren.shu && ren.pai[i].chu == 0)i++;
					while (j >= 0 && ren.pai[j].chu != 0)j--;
					if (i < j) {
						Swap(ren.pai[i], ren.pai[j]);
					}
				}
				printChuPai(&ren);
				ren.shu -= con;
				dui.con = con;
				sort_pai(ren.pai, ren.shu);
				return 1;
		}
		
	}
	for (int i = 0; i < ren.shu; i++)
	{
		ren.pai[i].chu = 0;
	}
	return 0;
}
int  Pan_da_xiao(int* a, int con ,int c)
{
	if (c == 9)
	{
		return 1;
	}
	else if (dui.dan == 7 && c == 7)
	{
		int i, D, A;
		for (i = 0; i <= 15; i++)
		{
			if (dui.daXiao[0] == ciDian[i])
				D = i;
			if (a[0] == ciDian[i])
				A = i;
		}
		if (A > D)
		{
			return 1;
		}
		else
			return 0;
	}
	else if (c == 7)
	{
		return 1;
	}
	else if (c == dui.dan)
	{
		int i, D, A;
		for (i = 0; i <= 15; i++)
		{
			if (dui.daXiao[0] == ciDian[i])
				D = i;
			if (a[0] == ciDian[i])
				A = i;
		}
		if (A > D)
		{
			return 1;
		}
		else
			return 0;
	}
	else
		return 0;
}
void isDiZhu()
{
	setlinecolor(RED);
	fillrectangle(300, 220, 400, 290);
	fillrectangle(500, 220, 600, 290);
	outtextxy(330,250 , "抢地主");
	outtextxy(530, 250, "不抢");
	MOUSEMSG M;
	while (1)
	{
		M = GetMouseMsg();
		if ((M.x >= 300 && M.x <= 400) && (M.y >= 220 && M.y <= 290)&&(M.uMsg== WM_LBUTTONDOWN))
		{
			wanJia.shu += 3;
			Swap(diZhuPai.dizhu[0], wanJia.pai[17]);
			Swap(diZhuPai.dizhu[1], wanJia.pai[18]);
			Swap(diZhuPai.dizhu[2], wanJia.pai[19]);
			sort_pai(wanJia.pai, wanJia.shu);
			wanJia.shen = 1;
			break;
		}
		if ((M.x >= 500 && M.x <= 600) && (M.y >= 220 && M.y <= 290) && (M.uMsg == WM_LBUTTONDOWN))
		{
			dian1.shu += 3;
			Swap(diZhuPai.dizhu[0], dian1.pai[17]);
			Swap(diZhuPai.dizhu[1], dian1.pai[18]);
			Swap(diZhuPai.dizhu[2], dian1.pai[19]);
			sort_pai(dian1.pai,dian1.shu);
			dian1.shen = 1;
			break;
		}
	}
	setbkcolor(GREEN);
	clearrectangle(300, 220, 400, 290);
	clearrectangle(500, 220, 600, 290);
}
void printGround()
{
	// 设置背景色为绿色
	setbkcolor(GREEN);
	// 用背景色清空屏幕
	cleardevice();
}
void printPaiH(struct pai p ,int x,int y)
{
	char a[5]="qwe", h=' ';
	char* s = a;
	if (p.daXiao < 10)
	{
		a[0] = (char)p.daXiao + '0';
		a[1] = '\0';
	}
	else
	{
		switch (p.daXiao)
		{
		case 10:a[0]='1';
			a[1] = '0';
			a[2] = '\0';
			break;
		case 11:a[0] = 'J';
			a[1] = '\0';
			break;
		case 12:a[0] = 'Q';
			a[1] = '\0';
			break;
		case 13:a[0] = 'K';
			a[1] = '\0';
			break;
		case 14:a[0] = 'X';
			a[1] = '\0';
			break;
		case 15:a[0] = 'D';
			a[1] = '\0';
			break;
		}
	}
	if (p.huaSe <= 2)
	{
		settextcolor(RED);
	}
	else
	{
		settextcolor(BLACK);
	}
	setbkcolor(WHITE);
	if(p.chu==0)
	outtextxy(x,y,s);
	else
		outtextxy(x, y-60, s);
	if (p.daXiao <= 13)
	{
		switch (p.huaSe)
		{
		case 1:h= 'T';
			break;
		case 2:h = 'F';
			break;
		case 3:h = 'T';
			break;
		case 4:h = 'M';
			break;
		}
		if(p.chu==0)
		outtextxy(x, y + 20, h);
		else
		{
			outtextxy(x, y -40, h);
		}
	}

}
void printPai()
{
	int i;
	setlinecolor(BLACK);
	for (i = 0; i < wanJia.shu; i++)
	{
		//setbkcolor(GREEN);
		//clearrectangle(80 + i * 40, 240, 160 + i * 40, 450);
		if(wanJia.pai[i].chu==0)
		fillrectangle(80 + i * 40, 300, 160 + i * 40, 450);
		else
			fillrectangle(80 + i * 40, 240, 160 + i * 40, 390);
		printPaiH(wanJia.pai[i], 90 + i * 40, 310);
	}
	for (i = 0; i < dian1.shu; i++)
	{
		fillrectangle(20 , 50 + i * 20, 60, 70+i*20);
		
	}
	for (i = 0; i < dian2.shu; i++)
	{
		fillrectangle(860, 50 + i * 20, 900, 70 + i * 20);
		
	}
}
void paiChuShi()
{
	int i, j, con=0;
	for (i = 1; i <= 13; i++)
	{
		for (j = 1; j <= 4; j++)
		{
			quanBu.pai[con].huaSe=j;
			quanBu.pai[con++].daXiao = i;
		}
	}
	quanBu.pai[con].huaSe = 3;
	quanBu.pai[con++].daXiao = 14;
	quanBu.pai[con].huaSe = 1;
	quanBu.pai[con++].daXiao = 15;
	if (con != 54)
	{
		printf("cuo wu");
	}
}
void xiPai()
{
	int i=53, j;
	srand(time(NULL));
	while (i--)
	{
		j = rand() % (i+1);
		Swap(quanBu.pai[i], quanBu.pai[j]);
	}
}
void Swap(struct pai& a, struct pai& b)
{
	int t;
	t = a.daXiao;
	a.daXiao = b.daXiao;
	b.daXiao = t;
	t = a.huaSe;
	a.huaSe = b.huaSe;
	b.huaSe = t;
	t = a.chu;
	a.chu = b.chu;
	b.chu = t;
}
void faPai()
{
	int i = 0,con=0;
	for (i = 0; i < 20; i++)
	{
		wanJia.pai[i].chu = 0;
	}
	wanJia.shen = 0;
	dian1.shen = 0;
	dian2.shen = 0;
	dui.h = 0;
	dui.ren = NULL;
	for (i = 0; i < 3; i++)
	{
		diZhuPai.dizhu[i].daXiao = quanBu.pai[i].daXiao;
		diZhuPai.dizhu[i].huaSe = quanBu.pai[i].huaSe;
	}
	for (con=0; i < 20; i++)
	{
		wanJia.pai[con].daXiao = quanBu.pai[i].daXiao;
		wanJia.pai[con++].huaSe = quanBu.pai[i].huaSe;
	}
	for (con=0; i < 20+17; i++)
	{
		dian1.pai[con].daXiao = quanBu.pai[i].daXiao;
		dian1.pai[con++].huaSe = quanBu.pai[i].huaSe;
	}
	for (con=0; i < 20+17+17; i++)
	{
		dian2.pai[con].daXiao = quanBu.pai[i].daXiao;
		dian2.pai[con++].huaSe = quanBu.pai[i].huaSe;
	}
	wanJia.shu = 17;
	dian2.shu = 17;
	dian1.shu = 17;
	sort_pai(wanJia.pai,17);
	sort_pai(dian1.pai, 17);
	sort_pai(dian2.pai, 17);
}
void sort_pai(struct pai* a, int len)
{
	int i;
	for (i = 0; i < len-1; i++)
	{
		if (cidian(a[i].daXiao) > cidian(a[i + 1].daXiao))
		{
			Swap(a[i], a[i + 1]);
			if (i != 0)i-=2;
		}
	}
}
int cidian(int a)
{
	for (int i = 0; i < 15; i++)
	{
		if (ciDian[i] == a)
			return i;
	}
}