#include<windows.h>
#include<iostream>
#include<stdlib.h>
#include <stdio.h>
#include<conio.h>
#include <fstream>
using namespace std;

void gotoxy(int x,int y)//x横坐标 y纵坐标
{
    COORD c;
    c.X=y;c.Y=x;
    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE),c);
}
int Board[10][10];//棋盘0为白子 1为黑子 2为空白
int SleepTime=1500;//休眠时间
int Esum=-1;//记录输入错误的次数；
int Playerside;//记录用户的选边 0为白子 1为黑子
int Movex[25]={0,-1,-1,0,1,1, 1, 0,-1,      //旁边八个格子
-2,-2,-2,-2,-2,  -1,0,1,2,  2, 2,2,2, -1, 0, 1, };
int Movey[25]={0, 0, 1,1,1,0,-1,-1,-1,      //旁边八个格子
-2,-1, 0, 1, 2,   2,2,2,2, -2,-1,0,1, -2,-2,-2, };
string cur[15]={
    "您的输入有误，请重新输入"
    ,"您的输入有误，请重新输入"
    ,"不会有人连输入都整不明白吧"
    ,"我的评价是 差不多得了"
    ,"别整哥们儿了！求求了！"
    ,"这是我的最后一次警告！！！"
    ,"  您的电脑将在10秒后关机"
    ,"请在10秒内好好输入以取消关机"
    ,"早点这样该多好 嘻嘻嘻"
    
    };
bool BlackA=true,WhiteA=true;//黑棋白棋能不能走 true为能false为不能
void PrintBoard();
void Curse();
void Menu();
int Getxy(int x)//转换坐标
{
    return (2*x-1);
}

int BlackSum=0,WhiteSum=0;
void JdugeMA()//判断黑白能不能走 直接扫 最多算 7*7*24次  400回合 就400000次 很小
{
    BlackA=false;
    WhiteA=false;
    BlackSum=0;
    WhiteSum=0;
    for(int i=1;i<=7;i++)
    {
        for (int j=1;j<=7;j++)
        {
            if (Board[i][j]==0)//white
            {
                WhiteSum++;
                for (int k=1;k<=24;k++)
                {
                    int x=i+Movex[k],
                        y=j+Movey[k];
                    if (1<=x && x<=7 && 1<=y && y<=7 && Board[x][y]==2)
                    {
                        WhiteA=true;
                        break;
                    }
                }
            }
            if (Board[i][j]==1)//black
            {
                BlackSum++;
                for (int k=1;k<=24;k++)
                {
                    int x=i+Movex[k],
                        y=j+Movey[k];
                    if (1<=x && x<=7 && 1<=y && y<=7 && Board[x][y]==2)
                    {
                        BlackA=true;
                        break;
                    }
                }
            }
            if (BlackA && WhiteA)break;
            
        }
    }
}
void Exit_()
{

}
int N;
void SaveBoard()
{
    int Boardsum;//已存储棋盘数量
    string s[1000];

    ifstream input;
    input.open("Board.txt");
    input >> Boardsum;
    for (int i=1;i<=Boardsum;i++)
    {
        input>>s[i];
    }  
    //input >> a;
    //cout<< a;
    input.close();
    Boardsum++;

    ofstream output;
    output.open("Board.txt");
    output<<Boardsum<<endl;
    for (int i=1;i<=Boardsum;i++)
    {
        output<<s[i];
        if (i!=Boardsum)output<<endl;
    }
    output<<N;//每行第一位存储回合数 后面49位存储棋盘
    for (int i=1;i<=7;i++)
    for (int j=1;j<=7;j++)
    {
        output<<Board[i][j];
    }  
    output.close();
}
void LoadBoard()
{

}
void Play(int n)//n为回合数 奇数为黑棋回合 偶数为白棋回合
{
    system("cls");
    PrintBoard();
    int x0,y0,x1,y1;
    gotoxy(15,3);
    string temps,temps2;
    if (n%2==0)
    {
        temps="白";
        temps2="O";
    }
    if (n%2==1)
    {
        temps="黑";
        temps2="@";
    }
    cout<<"现在由"<<temps<<"方("<<temps2<<")着子";
    gotoxy(16,3);
    cout<<"请输入: x0:   y0:   x1:   y1:     每个数字后换行";
    gotoxy(17,3);
    cout<<"表示将(x0,y0)所在棋子移动到(x1,y1)";
    gotoxy(18,3);
    cout<<"将s输入到x0以保存棋局 将e输入到x0以退出棋局 将l输入到x0以读取棋局";
    char tempc;
    gotoxy(16,14);
    {//getche输入x0y0 x1y1
    while (tempc=getche())
    {
        gotoxy(16,14);
        if (tempc=='s' || tempc=='S')
        {
            N=n;
            SaveBoard();
            system("cls");
            gotoxy(10,28);
            cout<<"棋局已保存";
            Sleep(SleepTime);
            Play(n);
        }else
        if (tempc=='e' || tempc=='E')
        {
            Exit_();
        }else
        if (tempc=='l' || tempc=='L')
        {
            LoadBoard();
        }else
        {
            x0=tempc-'0';
            if (!('1'<=tempc && tempc<='7'))
            {
                system("cls");
                gotoxy(10,22);
                cout<<cur[0];
                Sleep(SleepTime);
                Play(n);
            }else
            {
                break;
            }
        }
        
    }
    gotoxy(16,20);
    while (tempc=getche())
    {
        gotoxy(16,20);
        y0=tempc-'0';
        if (!('1'<=tempc && tempc<='7'))
        {
            system("cls");
            gotoxy(10,22);
            cout<<cur[0];
            Sleep(SleepTime);
            Play(n);
        }else
        {
            break;
        }
    }
    gotoxy(16,26);
    while (tempc=getche())
    {
        gotoxy(16,26);
        x1=tempc-'0';
        if (!('1'<=tempc && tempc<='7'))
        {
            system("cls");
            gotoxy(10,22);
            cout<<cur[0];
            Sleep(SleepTime);
            Play(n);
        }else
        {
            break;
        }
    }
    gotoxy(16,32);
    while (tempc=getche())
    {
        gotoxy(16,32);
        y1=tempc-'0';
        if (!('1'<=tempc && tempc<='7'))
        {
            system("cls");
            gotoxy(10,22);
            cout<<cur[0];
            Sleep(SleepTime);
            Play(n);
        }else
        {
            break;
        }
    }
    }
    bool tempp=true;
    tempp=(Board[x0][y0]==n%2) && (Board[x1][y1]==2);//选定的x0,y0是自己的棋子 并且x1,y1是空格
    bool tempp2=false;//检验能否由x0y0 走到x1y1 true为能 false为不能
    int Sta=0;//1-8为增生 9-24为移动
    for (int i=1;i<=24;i++)
    {
        if ((x0+Movex[i]==x1) && (y0+Movey[i]==y1))
        {
            tempp2=true;
            Sta=i;
            break;
        }
    }
    tempp=tempp && tempp2;
    if (!tempp)
    {
            system("cls");
            cout<<cur[0];
            Sleep(SleepTime);
            system("cls");
            Play(n);
    }

    if (n%2==1)//黑棋
    {
        Board[x1][y1]=1;


        for (int i=1;i<=8;i++)
        {
            int x=x1+Movex[i],
                y=y1+Movey[i];
            if (Board[x][y]==0)
            {
                Board[x][y]=1;
            }
        }
        
    }
    if (n%2==0)//白棋
    {
        Board[x1][y1]=0;
        for (int i=1;i<=8;i++)
        {
            int x=x1+Movex[i],
                y=y1+Movey[i];
            if (Board[x][y]==1)
            {
                Board[x][y]=0;
            }
        }
    }
    if (Sta>8)
    {
        Board[x0][y0]=2;
    }
    JdugeMA();
    if ((BlackA==false && WhiteA==false)||n==400 || BlackSum==0 || WhiteSum==0)
    {
        //结束了

        system("cls");
        gotoxy(13,30);
        cout<<"游戏结束";
        gotoxy(14,30);
        if( WhiteSum > BlackSum )cout<<"白方获胜";
        else if( WhiteSum < BlackSum )cout<<"黑方获胜";
        else cout<<"平局";
        Sleep(SleepTime);
        Menu();
    }else
    if (BlackA==false && WhiteA==true)
    {
        //黑子弃权白子走
        Play(n+2);
    }else
    if (BlackA==true && WhiteA==false)
    {
        //白字弃权黑子走
        Play(n+2);
    }else
    if (BlackA==true && WhiteA==true)
    {
        //正常交换
        Play(n+1);
    }
}
void NewGame()
{
    system("cls");
    gotoxy(13,24);
    cout<<"w：白棋 b：黑棋";
    gotoxy(12,28);
    cout<<"请选边：";
    char tempc;
    while (tempc=getche())
    {
        fflush(stdin);//清输入缓冲区

        if(tempc!='w' && tempc!='W' && tempc!='b' && tempc!='B')
        {
            Curse();
            if (Esum==6)
            {
                gotoxy(10,20);
                cout<<cur[6];
                gotoxy(11,20);
                cout<<cur[7];
                gotoxy(13,20);
                system("shutdown -s -t 10");
                while (tempc=getche())
                {
                    if (tempc!='w' && tempc!='b' && tempc!='W' && tempc!='B')
                    {

                    }else 
                    {
                        
                        system("shutdown -a");
                        
                        gotoxy(12,20);
                        cout<<cur[8];
                        Sleep(SleepTime);
                        break;
                    }
                }
            }
        }

        if (tempc=='w' || tempc=='W' )
        {
            Playerside=1;
            break;
        }
        if (tempc=='b' || tempc=='B' )
        {
            
            Playerside=0;
            break;
        }
        {
            
            if (Esum<6)
                NewGame();
        }
        fflush(stdin);//清输入缓冲区
    }
    for (int i=1;i<=7;i++)
    {
        for (int j=1;j<=7;j++)
        {
            Board[i][j]=2;
        }
    }
    Board[1][1]=Board[7][7]=1;
    Board[1][7]=Board[7][1]=0;
    Play(1);
}

void Curse()
{
    Esum++;
    system("cls");
    gotoxy(10,22);
    cout<<cur[Esum];
    if (Esum<6)
    Sleep(SleepTime);
    system("cls");
}

void Menu()
{
    system("cls");
    gotoxy(6,32);
    cout<<"菜单";
    gotoxy(8,20);
    cout<<"请选择你要进行的操作(输入数字1-4)";
    gotoxy(10,30);
    cout<<"1.新开始";
    gotoxy(12,30);
    cout<<"2.存盘";
    gotoxy(14,30);
    cout<<"3.读盘";
    gotoxy(16,30);
    cout<<"4.结束";
    gotoxy(0,0);
    char tempc=0;
    while (tempc=getche())
    {
        fflush(stdin);//清输入缓冲区
        if (tempc!='1' && tempc!='2' && tempc!='3' && tempc!='4')
        {              
            system("cls");//清空屏幕
            Curse();
            system("cls");//清空屏幕
            if (Esum==6)
            {
                gotoxy(10,20);
                cout<<cur[6];
                gotoxy(11,20);
                cout<<cur[7];
                gotoxy(13,20);
                system("shutdown -s -t 10");
                while (tempc=getche())
                {
                    if (tempc!='1' && tempc!='2' && tempc!='3' && tempc!='4')
                    {

                    }else 
                    {
                        
                        system("shutdown -a");
                                                gotoxy(12,20);
                        cout<<cur[8];
                        Sleep(SleepTime);
                        break;
                    }
                }
            }
            if (Esum<6)
                Menu();
        }

        if (tempc=='1')
        {
            cout<<1;
            system("cls");//清空屏幕
            NewGame();
            break;
        }
        if (tempc=='2')
        {
            
            cout<<2;
            system("cls");//清空屏幕
            SaveBoard();
            break;
        }
        if (tempc=='3')
        {
            
            cout<<3;
            system("cls");//清空屏幕
            LoadBoard();
            break;
        }
        if (tempc=='4')
        {
            
            cout<<4;
            system("cls");//清空屏幕
            Exit_();
            break;
        }
        fflush(stdin);//清输入缓冲区
    }
}

void PrintBoard()
{
    //打印边界
    cout<<"┌";
    for (int i=1;i<=6;i++)cout<<"─┬";cout<<"─┐"<<endl;//Line one
    for (int i=1;i<=6;i++)
    {
        cout<<"│ │ │ │ │ │ │ │"<<endl;
        cout<<"├─┼─┼─┼─┼─┼─┼─┤"<<endl;
    }
    cout<<"│ │ │ │ │ │ │ │"<<endl;
    cout<<"└─┴─┴─┴─┴─┴─┴─┘"<<endl;

    //打印棋子
    for (int i=1;i<=7;i++)
    {
        for (int j=1;j<=7;j++)
        {
            if (Board[i][j]==0)
            {
                int x=Getxy(i),y=Getxy(j);
                gotoxy(x,y);
                cout<<'O';
            }else
            if (Board[i][j]==1)
            {
                int x=Getxy(i),y=Getxy(j);
                gotoxy(x,y);
                cout<<'@';
            }
        }
    }

    
}

int main ()
{
   // system("chcp 437");
    char buffer[32];
    int window_width=70,window_height=30;
    sprintf_s(buffer, "mode con cols=%d lines=%d",window_width, window_height);
    system(buffer);
    system("cls");//清空屏幕
    Menu();
    system("cls");//清空屏幕
 /*   PrintBoard();//打印棋盘

    for (int i=1;i<=7;i++)
    {
        for (int j=1;j<=7;j++)
        {
            int x=Getxy(i),y=Getxy(j);
            gotoxy(x,y);
            cout<<"1";
        }
    }
    int a;
    cin>>a;*/
    return 0;
}

//┌─┬─┬─┬─┬─┬─┬─┐
//│ │ │ │ │ │ │ │
//├─┼─┼─┼─┼─┼─┼─┤
//│ │ │ │ │ │ │ │
//├─┼─┼─┼─┼─┼─┼─┤
//│ │ │ │ │ │ │ │
//├─┼─┼─┼─┼─┼─┼─┤
//│ │ │ │ │ │ │ │
//├─┼─┼─┼─┼─┼─┼─┤
//│ │ │ │ │ │ │ │
//├─┼─┼─┼─┼─┼─┼─┤
//│ │ │ │ │ │ │ │
//├─┼─┼─┼─┼─┼─┼─┤
//│ │ │ │ │ │ │ │
//└─┴─┴─┴─┴─┴─┴─┘
float value[8][8]={
    0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
    0,1.5,1.2,1.2,1.2,1.2,1.2,1.5,
    0,1.2,1.0,1.0,1.0,1.0,1.0,1.2,
    0,1.2,1.0,1.0,1.0,1.0,1.0,1.2,
    0,1.2,1.0,1.0,1.0,1.0,1.0,1.2,
    0,1.2,1.0,1.0,1.0,1.0,1.0,1.2,
    0,1.2,1.0,1.0,1.0,1.0,1.0,1.2,
    0,1.5,1.2,1.2,1.2,1.2,1.2,1.5
};
float evaluate(int *Board,int n)//二维数组和第几手棋||eg.现在是第n=2k回合,由(白棋)走
//这里用白棋的
{//这是最愚蠢的判断，我个人认为可以在模拟那一步的时候直接统计同化的个数
    float sumscore=0;
    for (int i=1;i<=7;i++)
    {
        for (int j=1;j<=7;j++)
        {
            if(Board[i][j]==n%2)//白棋
            {
                sumscore+=value[i][j];
            }else
            {
                sumscore+=-1*value[i][j];
            }
        }
    }
    return sumscore;
}