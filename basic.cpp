//basic.cpp�ļ� 
//����ƶ���ָ�����괦
void gotoxy(int x,int y)
{
	HANDLE h;//���,���������
	COORD c;//�ṹ��,����ֵ
	c.X=x;
	c.Y=y;
	h=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h,c);
}

//���ع��
void hide_cursor()
{
	HANDLE	h_GAME = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor_info;
	GetConsoleCursorInfo(h_GAME,&cursor_info); 
	cursor_info.bVisible=false;					//����ʾ���
	SetConsoleCursorInfo(h_GAME,&cursor_info); 
}

//��ʾ���
void show_cursor()				
{
	HANDLE	h_GAME = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor_info;
	GetConsoleCursorInfo(h_GAME,&cursor_info); 
	cursor_info.bVisible=true;					//��ʾ���
	SetConsoleCursorInfo(h_GAME,&cursor_info); 
}

//�����ı���ɫ
void color(int a)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
}


