
#include<iostream>
#include<windows.h>
#include<vector>
#include<string>
#include<conio.h>
#include<ctime>
#include"basic.cpp"
using namespace std;

//̰����˼·����Ҫһ�����������һ�й��
// ��Ҫ�����������ҿ��Ʒ��򣬲�ͬ��������µ���ͷ��ͨ��ѭ��ʹ��ͷ�����Ͻ���
// ��Ҫһ��������ֵ�Ŀ��
// ���߾���Ŀ��ʱ�������غ�ʱ���ߵ����峤��+1
//

struct S
{
	int x; int y;
};
//���ƶ�����С����
class snake
{
protected:
	char key;
	int x, y, i,new_x,new_y,point=0;//�������������ѭ������
	int length;//�����ߵĳ�ʼ����
	vector<S> s;//�ߣ���ͷΪbegin��
	vector<S>::iterator p,p1;//�����������ڱ���
	clock_t t1;//����ʱ������������ƶ���ת��ļ��ʱ��
public:
	snake(){}
	snake(int l,int xx,int yy)//��ʼ���ȣ���ʼ��������
	{
		hide_cursor();
		key = 'd';
		x = xx; y = yy;
		length = l;//��ʼ���߳�

		//��ʼ���ߣ���ʼ��������
		for (i = 0; i < length; ++i)
		{
			S temp;
			temp.x = x;
			temp.y = y;
			s.push_back(temp);
			x--;
			x--;
		}
		//���˳�ʼ�����Ѿ������򴴽�

		t1 = clock();//��ʼ��ʱ�����
	}
	~snake()
	{
		show_cursor();
	}
	void move1()//�ж��������ʲô�������ݲ�ͬ������,����ͬ������ͷ����ѹ������
	{
		int prekey,aftkey;
		prekey = key;//������������ж�ǰ������key�Ƿ��෴
		p = s.begin();
		if (_kbhit())
		{
			aftkey = _getch();//��������룬�������ֵ����key��ͨ���ж�key��ֵ�����иı�
		}
		if ((aftkey == 'd' && prekey != 'a') || (aftkey == 'w' && prekey != 's') 
			|| (aftkey == 'a' && prekey != 'd') || (aftkey == 's' && prekey != 'w'))//ȷ���߲������ŷ�������
		{
			key = aftkey;//���ҽ����ƶ��������෴��ʱ��Ÿı�key��ֵ�ɼ��̰���
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
			s.insert(s.begin(), tempyou);//s.front()������S
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
	void create(int x,int y)//��ָ�����괴�쵥λ����
	{
		gotoxy(x, y);
		cout << "��";
	}
	void erase(int x, int y)//��ָ������������λ����
	{
		gotoxy(x, y);
		cout << " ";
	}
	void browse1()//����һ������µ�
	{
		for (p = s.begin(); p != s.end(); ++p)
		{
			create(p->x, p->y);
		}
	}
	void browse2()//����һ�������ϵ�
	{
		for (p = s.begin(); p != s.end(); ++p)
		{
			erase(p->x, p->y);
		}
	}
	void check()//������Ϸʧ�ܵ�����
	{
		for (i = 1; i < s.size(); ++i)//ײ���Լ����
		{
			if (s[0].x == s[i].x && s[0].y == s[i].y)
			{
				gotoxy(10, 10);
				cout << "ײ���Լ�����Ϸ������";
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
	food(int xxx, int yyy, int l, int xx, int yy):snake(l,xx,yy)//���಻��ֱ�ӵ��ø����е�˽������
	{
		x1 = xxx; y1 = yyy;
		gotoxy(x1, y1);
		cout << "��";//��ʼ��ʳ��λ�ú�ʳ��
	}
	void createfood()//����ԭ�������ʳ���������괴���µ�ʳ��
	{
		gotoxy(x1, y1);
		cout << " ";
		x1 = (rand() % 37) * 2+2;
		y1 = rand() % 24+3;
		gotoxy(x1, y1);
		cout << "��";
	}
	void add()//ʳ�ﱻ�Ե����ߵĳ�������һ��,��������1
	{
		srand(time(0));
		p = s.begin();
		if (s.front().x == x1 && s.front().y == y1)
		{
			createfood();//ʳ�ﱻ�Ե���ʳ��ı仯
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
				s.insert(s.begin(), tempyou);//s.front()������S
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
	//��ʶ��esc��ʱ����table��ѡ������һ�����������������Ӧ����
	void table()
	{
		gotoxy(80, 3);
		cout << "1.�˳���Ϸ";
		gotoxy(80, 5);
		cout << "2.������Ϸ";
	}
	void move()//�ܿغ���
	{
		while (true)
		{
			if (GetAsyncKeyState(VK_ESCAPE))
			{
				table();
			}
			table();
			gotoxy(80, 7);
			cout << "С�߳��ȣ�" << length;
			if (clock() - t1 > 100)
			{
				browse2();
				move1();
				browse1();
				add();
				check();
			}
			gotoxy(80, 9);
			cout << "�÷֣�" << point;
			gotoxy(80, 11);
			cout << "��esc�򿪲˵�";
		}
	}
};

int main()
{
	menu t1(50,10, 5, 20, 20);
	t1.move();
	return 0;
}
