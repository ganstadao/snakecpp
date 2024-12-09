
#include<iostream>
#include<windows.h>
#include<vector>
#include<string>
#include<conio.h>
#include<ctime>
#include"basic.cpp"
using namespace std;

//贪吃蛇思路：需要一个容器来存放一列轨道
// 需要按下上下左右控制方向，不同方向加入新的蛇头，通过循环使蛇头被不断建立
// 需要一个随机出现的目标
// 当蛇经过目标时（坐标重合时）蛇的身体长度+1
//

struct S
{
	int x; int y;
};
//可移动变向小蛇类
class snake
{
protected:
	char key;
	int x, y, i,new_x,new_y,point=0;//定义坐标变量，循环变量
	int length;//定义蛇的初始长度
	vector<S> s;//蛇（蛇头为begin）
	vector<S>::iterator p,p1;//迭代器，用于遍历
	clock_t t1;//定义时间变量来控制移动和转向的间隔时间
public:
	snake(){}
	snake(int l,int xx,int yy)//初始长度，初始横纵坐标
	{
		hide_cursor();
		key = 'd';
		x = xx; y = yy;
		length = l;//初始化蛇长

		//初始化蛇，初始方向向右
		for (i = 0; i < length; ++i)
		{
			S temp;
			temp.x = x;
			temp.y = y;
			s.push_back(temp);
			x--;
			x--;
		}
		//至此初始的蛇已经被反向创建

		t1 = clock();//初始化时间变量
	}
	~snake()
	{
		show_cursor();
	}
	void move1()//判断输入的是什么，并根据不同的输入,将不同的新蛇头坐标压入容器
	{
		int prekey,aftkey;
		prekey = key;//这个变量用于判断前后两次key是否相反
		p = s.begin();
		if (_kbhit())
		{
			aftkey = _getch();//如果有输入，将接入的值赋给key，通过判断key的值来进行改变
		}
		if ((aftkey == 'd' && prekey != 'a') || (aftkey == 'w' && prekey != 's') 
			|| (aftkey == 'a' && prekey != 'd') || (aftkey == 's' && prekey != 'w'))//确保蛇不能沿着反方向走
		{
			key = aftkey;//当且仅当移动方向不是相反的时候才改变key的值成键盘按键
		}
		if (key == 'd')
		{
			S tempyou;
			new_x = p->x + 2;
			if (new_x >= 78)
			{
				tempyou.x = 2;
			}
			else
			{
				tempyou.x = new_x;
			}
			tempyou.y = p->y;
			s.insert(s.begin(), tempyou);//s.front()类型是S
			s.pop_back();
		}
		if (key == 'a')
		{
			S tempzuo;
			new_x = p->x - 2;
			if (new_x <= 2)
			{
				tempzuo.x = 78;
			}
			else
			{
				tempzuo.x = new_x;
			}
			tempzuo.y = p->y;
			s.insert(s.begin(), tempzuo);
			s.pop_back();
		}
		if (key == 'w')
		{
			S tempshang;
			new_y = p->y - 1;
			tempshang.x = p->x;
			if (new_y <= 2)
			{
				tempshang.y = 27;
			}
			else
			{
				tempshang.y = new_y;
			}
			s.insert(s.begin(), tempshang);
			s.pop_back();
		}
		if (key == 's')
		{
			S tempxia;
			new_y = p->y + 1;
			tempxia.x = p->x;
			if (new_y >= 27)
			{
				tempxia.y = 2;
			}
			else
			{
				tempxia.y = new_y;
			}
			s.insert(s.begin(), tempxia);
			s.pop_back();
		}
		t1 = clock();
	}
	void create(int x,int y)//在指定坐标创造单位蛇身
	{
		gotoxy(x, y);
		cout << "■";
	}
	void erase(int x, int y)//在指定坐标消除单位蛇身
	{
		gotoxy(x, y);
		cout << " ";
	}
	void browse1()//遍历一变产生新的
	{
		for (p = s.begin(); p != s.end(); ++p)
		{
			create(p->x, p->y);
		}
	}
	void browse2()//遍历一遍消除老的
	{
		for (p = s.begin(); p != s.end(); ++p)
		{
			erase(p->x, p->y);
		}
	}
	void check()//考虑游戏失败的条件
	{
		for (i = 1; i < s.size(); ++i)//撞到自己情况
		{
			if (s[0].x == s[i].x && s[0].y == s[i].y)
			{
				gotoxy(10, 10);
				cout << "撞到自己，游戏结束！";
				gotoxy(20, 20);
				exit(0);
			}
		}
	}
};

class food:public snake
{
protected:
	int x1; int y1;
public:
	food(int xxx, int yyy, int l, int xx, int yy):snake(l,xx,yy)//子类不能直接调用父类中的私有数据
	{
		x1 = xxx; y1 = yyy;
		gotoxy(x1, y1);
		cout << "◇";//初始化食物位置和食物
	}
	void createfood()//消除原有坐标的食物，在随机坐标创建新的食物
	{
		gotoxy(x1, y1);
		cout << " ";
		x1 = (rand() % 37) * 2+2;
		y1 = rand() % 24+3;
		gotoxy(x1, y1);
		cout << "◇";
	}
	void add()//食物被吃到后蛇的长度增加一格,分数增大1
	{
		srand(time(0));
		p = s.begin();
		if (s.front().x == x1 && s.front().y == y1)
		{
			createfood();//食物被吃到后食物的变化
			if (key == 'd')
			{
				S tempyou;
				new_x = p->x + 2;
				if (new_x >= 78)
				{
					tempyou.x = 2;
				}
				else{tempyou.x = new_x;}
				tempyou.y = p->y;
				s.insert(s.begin(), tempyou);//s.front()类型是S
			}
			if (key == 'a')
			{
				S tempzuo;
				new_x = p->x - 2;
				if (new_x <= 2)
				{
					tempzuo.x = 78;
				}
				else{tempzuo.x = new_x;}
				tempzuo.y = p->y;
				s.insert(s.begin(), tempzuo);
			}
			if (key == 'w')
			{
				S tempshang;
				new_y = p->y - 1;
				tempshang.x = p->x;
				if (new_y <= 2)
				{
					tempshang.y = 27;
				}
				else{tempshang.y = new_y;}
				s.insert(s.begin(), tempshang);
			}
			if (key == 's')
			{
				S tempxia;
				tempxia.x = p->x;
				new_y = p->y + 1;
				if (new_y >= 27)
				{
					tempxia.y = 2;
				}
				else{tempxia.y = new_y;}
				s.insert(s.begin(), tempxia);
			}
			point++; length++;
		}
	}
};

class menu :public food
{
protected:
public:
	menu(int xxx, int yyy, int l, int xx, int yy):food(xxx, yyy, l, xx, yy)
	{

	}
	//当识别到esc键时进入table，选择其中一项后跳出进行其他对应操作
	void table()
	{
		gotoxy(80, 3);
		cout << "1.退出游戏";
		gotoxy(80, 5);
		cout << "2.继续游戏";
	}
	void move()//总控函数
	{
		while (true)
		{
			if (GetAsyncKeyState(VK_ESCAPE))
			{
				table();
			}
			table();
			gotoxy(80, 7);
			cout << "小蛇长度：" << length;
			if (clock() - t1 > 100)
			{
				browse2();
				move1();
				browse1();
				add();
				check();
			}
			gotoxy(80, 9);
			cout << "得分：" << point;
			gotoxy(80, 11);
			cout << "按esc打开菜单";
		}
	}
};

int main()
{
	menu t1(50,10, 5, 20, 20);
	t1.move();
	return 0;
}
