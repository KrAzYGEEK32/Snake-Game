#include<iostream.h>
#include<fstream.h>
#include<string.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<stdlib.h>
#include<iomanip.h>
#include<stdio.h>
//globals
int bgc=12,fgc=14,color;

int limit,statlim=3,score=limit,egg[2],speed,gmod,snc;

int xcor1=10,ycor1=10,xcor2=500,ycor2=400,debu=0;

//prototypes
void insert(int turn[][3],int,int,int,int);
void highice();
void game();
void drawegg();
int close();
void grint();
void gameover();
void pause();
void redraw();
int menu();
void startup();
void score1();
void main();
void instruct();
void main1();

//classes
class  settings
{public:
 int gmode,gdif,sncolor;
 void inpsettings(int x,int y,int z);
 void assisettings();
 void changeset();
 char* getgdif(char* a);
 char* getgmode(char* a);
 char* getsnc(char* a);
 }set;

class highscore
{
public:
int gd[2][3];
char names[6][20];
void assihigh();
void inphighscore(char*,int);
void disphigh();
void cmphi();
}high;

class snake
{
 int cor[100][3];
 public:
  void assign();
  void draw();
  void move();
  void check();
  void turn(int x);
  void reassign();
  void egg1();
  void rearrange();
  void debug();
  };


//highscores class functions
void highscore::assihigh()
{for(int x=0;x<2;x++)
 for(int y=0;y<3;++y)
 gd[x][y]=0;
 for(x=0;x<6;x++)
 strcpy(names[x],"NONAME");
}
void highscore::cmphi()
{
 char namc[20];
 if(gd[gmod][set.gdif]<(limit-score)*2)
 {highice();
  closegraph();
  gotoxy(32,5);
  cprintf("NEW HIGHSCORE!!!");
  gotoxy(1,8);
  cprintf("Enter your name for the Hall Of Fame: ");
  //cout<<"/b /b";
  gets(namc);
  inphighscore(namc,(limit-score)*2);
  ofstream f1("highscores.dat",ios::out|ios::binary);
    f1.write((char*)&high,sizeof(high));
    f1.close();}
}


void highscore::inphighscore(char*name,int scor)
{
 gd[gmod][set.gdif]=scor;
 if(gmod==0)
 strcpy(names[set.gdif],name);
 else
 strcpy(names[3+set.gdif],name);
}
void highscore::disphigh()
{char a[20];
 closegraph();
 _setcursortype(_NOCURSOR);
 textcolor(MAGENTA);
 gotoxy(35,1);
 cprintf("HALL OF FAME");
 gotoxy(11,4);
 textcolor(CYAN);
 cprintf("Open Mode   ,Easy  :%s  -  %d",names[0],gd[0][0]);
 gotoxy(11,7);
 cprintf("Open Mode   ,Medium:%s - %d",names[1],gd[0][1]);
 gotoxy(11,10);
 cprintf("Open Mode   ,Hard  :%s - %d",names[2],gd[0][2]);
 gotoxy(11,13);
 cprintf("Closed Mode ,Easy  :%s - %d",names[3],gd[1][0]);
 gotoxy(11,16);
 cprintf("Closed Mode ,Medium:%s - %d",names[4],gd[1][1]);
 gotoxy(11,19);
 cprintf("Closed Mode ,Hard  :%s - %d",names[5],gd[1][2]);
 cout<<"\n\n\n\t\t\t\t";
 cprintf("BEAT THEM IF U CAN!!!");
 getch();
 }
//highscores class ends here

//settings class functions
char* settings::getgmode(char* a)
 {if(gmode==0)
  strcpy(a,"Open Mode");
 else
 strcpy(a,"Closed Mode");
 return a;
 }
 char* settings::getgdif(char* a)
 {switch(gdif)
  {case 0:strcpy(a,"Easy");
	  break;
   case 1:strcpy(a,"Medium");
	  break;
   case 2:strcpy(a,"Hard");
	  break;
  }
 return a;
}
 char* settings::getsnc(char* a)
 {switch(sncolor)
  {
   case 0:strcpy(a,"Blue");break;
   case 1:strcpy(a,"Green");break;
   case 2:strcpy(a,"Cyan");break;
   case 3:strcpy(a,"Red");break;
   case 4:strcpy(a,"Magenta");break;
   }
  return a;
 }
void settings::inpsettings(int x,int y,int z)
{
 gmode=x;
 gdif=y;
 sncolor=z;
}
void settings::assisettings()
{ gmod=gmode;
  switch(gdif)
  {case 0:speed=60;break;
   case 1:speed=45;break;
   case 2:speed=30;break;
  }
  snc=sncolor+1;
}
void settings::changeset()
{
 closegraph();
 char a1[50];
 _setcursortype(_NOCURSOR);
 textcolor(bgc);
 gotoxy(36,1);
 cprintf("SETTINGS");
 gotoxy(27,3);
 cprintf("Game Mode   :");
 gotoxy(21,5);
 cprintf("Game Difficulty   :");
 gotoxy(25,7);
 cprintf("Snake Color   :");
 textcolor(fgc);
 gotoxy(40,3);
 cprintf("   %s",getgmode(a1));
 textcolor(bgc);
 gotoxy(40,5);
 cprintf("   %s",getgdif(a1));
 gotoxy(40,7);
 cprintf("   %s",getsnc(a1));
 int x=gmode,a;
 textcolor(fgc);
 do{
    a=getch();
    if(a==0)getch();
    gotoxy(40,3);
    cout<<"               ";
    if(a!=13)
    gmode=++x%2;
    gotoxy(40,3);
    cprintf("   %s",getgmode(a1));
    }while(a!=13);
    textcolor(bgc);
    gotoxy(40,3);
    cprintf("   %s",getgmode(a1));
    textcolor(fgc);
    x=gdif;
    gotoxy(40,5);
    cprintf("   %s",getgdif(a1));
 do{
    a=getch();
    if(a==0)getch();
    gotoxy(40,5);
    cout<<"           ";
    if(a!=13)
    gdif=++x%3;
    gotoxy(40,5);
    cprintf("   %s",getgdif(a1));
    }while(a!=13);
    textcolor(bgc);
    gotoxy(40,5);
    cprintf("   %s",getgdif(a1));
    textcolor(fgc);
    x=sncolor;
	gotoxy(40,7);
    cprintf("   %s",getsnc(a1));
    do{
    a=getch();
    if(a==0)getch();
    gotoxy(40,7);
    cout<<"           ";
    if(a!=13)
    sncolor=++x%5;
    gotoxy(40,7);
    cprintf("   %s",getsnc(a1));
    }while(a!=13);
    assisettings();
    ofstream f1("settings.dat",ios::out|ios::binary);
    f1.write((char*)&set,sizeof(set));
    f1.close();
    }
//settings class ends here

//snake class functions
void snake::assign()
{ int y=0;limit=statlim,score=limit;
 for(int x=0;x<100;x++)
  {cor[x][y]=1000;cor[x][y+1]=1000;cor[x][y+2]=77;}
  cor[0][0]=(xcor2/2)-5;cor[0][1]=(ycor2/2)-5;
  for(int z=1;z<=limit+1;z++)
  {cor[z][y]=cor[z-1][y]-10;cor[z][y+1]=cor[z-1][y+1];}
  }
void snake::reassign()
{ int y=0,z=limit+1;
  switch(cor[z-1][2])
  {
  case 77:cor[z][y]=cor[z-1][y]-10;cor[z][y+1]=cor[z-1][y+1];  //right
	     break;
     case 80:cor[z][y]=cor[z-1][y];cor[z][y+1]=cor[z-1][y+1]-10;//down
	     break;
     case 72:cor[z][y]=cor[z-1][y];cor[z][y+1]=cor[z-1][y+1]+10;//up
	     break;
     case 75:cor[z][y]=cor[z-1][y]+10;cor[z][y+1]=cor[z-1][y+1];  //left
	     break;
 }
 cor[z][2]=cor[z-1][2];
 }
void snake::draw()
 {
  int y=0;
  for(int x=0;x<=limit+1;x++)
  { if(x==0)
    {
     setcolor(snc);
     circle(cor[x][y],cor[x][y+1],5);
     setfillstyle(SOLID_FILL,snc);
     floodfill(cor[x][y],cor[x][y+1],snc);
     }
     else
    {
     setcolor(snc+8);
     circle(cor[x][y],cor[x][y+1],5);
     setfillstyle(SOLID_FILL,snc+8);
     floodfill(cor[x][y],cor[x][y+1],snc+8);
     setcolor(BLACK);
     setfillstyle(SOLID_FILL,BLACK);
     switch(cor[x][y+2])
    {
     case 77:circle(cor[x][y]-10<xcor1?xcor2-5:cor[x][y]-10,cor[x][y+1],5);
	     floodfill(cor[x][y]-10<xcor1?xcor2-5:cor[x][y]-10,cor[x][y+1],BLACK);
	     break;
     case 80:circle(cor[x][y],cor[x][y+1]-10<ycor1?ycor2-5:cor[x][y+1]-10,5);
	     floodfill(cor[x][y],cor[x][y+1]-10<ycor1?ycor2-5:cor[x][y+1]-10,BLACK);
	     break;
     case 72:circle(cor[x][y],cor[x][y+1]+10>ycor2?ycor1+5:cor[x][y+1]+10,5);
	     floodfill(cor[x][y],cor[x][y+1]+10>ycor2?ycor1+5:cor[x][y+1]+10,BLACK);
	     break;
     case 75:circle(cor[x][y]+10>xcor2?xcor1+5:cor[x][y]+10,cor[x][y+1],5);
	     floodfill(cor[x][y]+10>xcor2?xcor1+5:cor[x][y]+10,cor[x][y+1],BLACK);
	     break;
    }
     }
    }
   redraw();
   }
void snake::move()
 { int y=0;
  for(int x=0;x<=limit+1;x++)
  { switch(cor[x][y+2])
    {
     case 77:cor[x][y]+=10;  //right
	     break;
     case 80:cor[x][y+1]+=10;//down
	     break;
     case 72:cor[x][y+1]-=10;//up
	     break;
     case 75:cor[x][y]-=10;  //left
	     break;
    }
  }
}
void snake::check()
{
if(cor[0][0]==egg[0]&&cor[0][1]==egg[1])
 {egg1();limit++;reassign();}
 for(int x=0;x<=limit+1;x++)
 {if((cor[0][0]==cor[x+1][0]&&cor[0][1]==cor[x+1][1]))
      {gameover();}
 if(gmod==0)
 {cor[x][0]=cor[x][0]>xcor2-5?xcor1+5:cor[x][0];
 cor[x][1]=cor[x][1]>ycor2-5?ycor1+5:cor[x][1];
 cor[x][0]=cor[x][0]<xcor1+5?xcor2-5:cor[x][0];
 cor[x][1]=cor[x][1]<ycor1+5?ycor2-5:cor[x][1];
  if(((cor[0][1]==165||cor[0][1]==235)&&(cor[0][0]>=185&&cor[0][0]<=315))||((cor[0][1]>325||cor[0][1]<85)&&(cor[0][0]==15||cor[0][0]==495))||((cor[0][1]==15||cor[0][1]==395)&&(cor[0][0]>435||cor[0][0]<75)))
 gameover();}
 else
 {
 if(cor[x][0]>xcor2||cor[x][0]<xcor1||cor[x][1]>ycor2||cor[x][1]<ycor1)
  {gameover();}
  }
 }
}
void snake::turn(int dir)
{ int x,turns=0,tcor[100][3];
  if(cor[0][2]!=dir)
   if(dir==72||dir==80||dir==77||dir==75)
  {if((cor[0][2]==72&&dir!=80)||(cor[0][2]==77&&dir!=75)||(cor[0][2]==80&&dir!=72)||(cor[0][2]==75&&dir!=77))
   {
   tcor[0][0]=cor[0][0];tcor[0][1]=cor[0][1];tcor[0][2]=dir;
   for(x=0;x<=limit+1;x++)
   {
    for(int i=0;i<=turns;i++)
    {for(int y=0;y<=limit+1;y++)
     {if(cor[y][0]==tcor[i][0]&&cor[y][1]==tcor[i][1])
      cor[y][2]=tcor[i][2];}
      if(cor[limit+1][0]==tcor[i][0]&&cor[limit+1][1]==tcor[i][1])
      {tcor[i][0]=1000;tcor[i][1]=1000;}}
	score1();
	move();
	check();
	draw();
     if(debu==1)
     debug();
    if(kbhit())
    {int a=getch();
      if(a==0)
      {dir=getch();
      if(cor[0][2]!=dir)
      if(dir==72||dir==80||dir==77||dir==75)
     {if((cor[0][2]==72&&dir!=80)||(cor[0][2]==77&&dir!=75)||(cor[0][2]==80&&dir!=72)||(cor[0][2]==75&&dir!=77))
     {
     insert(tcor,cor[0][0],cor[0][1],dir,++turns);
     x=-1;
     }
     }
     }
     if(a==13)
     if(close()==0)
      { high.cmphi();main1();}
     else redraw();
     if(a==32)
     {pause();
      cleardevice();
      redraw();
	   }
     }

    delay(speed);
    fflush(stdin);
    }
 }}
}

void snake::egg1()
{
 int x=xcor2/10,y=ycor2/10;
 again:
 egg[0]=(random(x-2)*10)+xcor1+5;
 egg[1]=(random(y-2)*10)+ycor1+5;
 for(int a=0;a<=limit+1;a++)
 {if(cor[a][0]==egg[0]&&cor[a][1]==egg[1])
  goto again;
 }
 if(gmod==0)
 if(((egg[1]==165||egg[1]==235)&&(egg[0]>=185&&egg[0]<=315))||((egg[1]>325||egg[1]<75)&&(egg[0]==15||egg[0]==495))||((egg[1]==15||egg[1]==395)&&(egg[0]>435||egg[0]<75)))
  goto again;
 rcolor:
 color=random(16);
 if(color==0||color==16)
 goto rcolor;
 drawegg();
 }

void snake::rearrange()
{for(int x=1;x<=limit+1;x++)
{switch(cor[x][2])
{
 case 77:cor[x][0]=cor[x][0]>xcor2?xcor1+5:cor[x-1][0]-10;cor[x][1]=cor[x-1][1];cor[x][2]=cor[x-1][2];
	 break;
 case 72:cor[x][1]=cor[x][1]<0?ycor2-5:cor[x-1][1]+10;cor[x][0]=cor[x-1][0];cor[x][2]=cor[x-1][2];
	 break;


 case 80:cor[x][1]=cor[x][1]>ycor2?ycor1+5:cor[x-1][1]-10;cor[x][0]=cor[x-1][0];cor[x][2]=cor[x-1][2];
	 break;
 case 75:cor[x][0]=cor[x][0]<0?xcor2-5:cor[x-1][0]+10;cor[x][1]=cor[x-1][1];cor[x][2]=cor[x-1][2];
	break;
}
cor[x][0]=cor[x][0]<0?xcor2+cor[x][0]:cor[x][0];
cor[x][0]=cor[x][0]>xcor2?cor[x][0]-xcor2:cor[x][0];
cor[x][1]=cor[x][1]<0?ycor2+cor[x][1]:cor[x][1];
cor[x][1]=cor[x][1]>ycor2?cor[x][1]-ycor2:cor[x][1];
}
}
void snake::debug()
{ cout<<"   ";
 for(int x=0;x<=limit+1;x++)
  {cout<<cor[x][0]<<" "<<cor[x][1]<<" "<<cor[x][2]<<"\n";
  }
 gotoxy(1,1);
}
//snake class ends here

//standalone functions start here
void redraw()
{ drawegg();
  if(gmod==1)setlinestyle(0,0,3);
  if(gmod==0)
  {// middle lines
   rectangle(180,160,320,170);
   floodfill(205,165,color);
   rectangle(180,240,320,230);
   floodfill(185,235,color);
   //top left corner
   rectangle(10,10,20,80);
   floodfill(15,15,color);
   rectangle(20,10,70,20);
   floodfill(30,15,color);
   //bottom left corner
   rectangle(10,330,20,400);
   floodfill(15,375,color);
   rectangle(20,390,70,400);
   floodfill(25,395,color);
   //bottom right corner
   rectangle(490,330,500,400);
   floodfill(495,375,color);
   rectangle(440,390,490,400);
   floodfill(475,395,color);
   //top right corner
   rectangle(500,10,490,80);
   floodfill(495,25,color);
   rectangle(440,20,500,10);
   floodfill(475,15,color);
   }
   rectangle(xcor1,ycor1,xcor2,ycor2);
   setlinestyle(0,0,1);
}

void highice()
{int x=0;
 while(x<50)
 {++x;
  cleardevice();
  setcolor(x);
  settextstyle(4,0,x<9?x:8);
  outtextxy(100,100,"HIGHSCORE");
  delay(100);
  }
abc:
if(getch()!=13)goto abc;
}
void pause()
{
      setcolor(4);
      outtextxy(100,400,"PAUSE");
      pause:
      int cd=getch();
      if(cd!=32)
      goto pause;
 }

 void drawegg()
 {
 setcolor(color);
 circle(egg[0],egg[1],5);
 setfillstyle(SOLID_FILL,color);
 floodfill(egg[0],egg[1],color);
 }

void gameover()
{setcolor(4);
   outtextxy(100,450,"GAME OVER!");
   abd:
   if(getch()!=13)goto abd;
   closegraph();
   _setcursortype(_NOCURSOR);
   gotoxy(34,11);
   textcolor(random(16));
   cprintf("Your Score is:");
   gotoxy(40,14);
   textcolor(random(16));
   cprintf("%d",(limit-score)*2 );
   abc:
   if(getch()!=13)goto abc;
   grint();
   high.cmphi();
   main1();}
void insert(int turn[][3],int xcor,int ycor,int dir,int index)
{
 turn[index][0]=xcor;
 turn[index][1]=ycor;
 turn[index][2]=dir;
}
void grint()
{ int gd=DETECT,gm;
  initgraph(&gd,&gm,"..//BGI");
}

int menu()
{
 grint();
 int inp=0,cmd=1;
 settextstyle(2,0,7);
 while(inp!=13)
 {
 switch(inp)
 {
  case 72:cmd--;break;
  case 80:cmd++;break;
 }
 if(cmd>5)cmd=1;
 if(cmd<1)cmd=5;
 switch(cmd)
 {
  case 1:setcolor(fgc);outtextxy(100,100,"Start");setcolor(bgc); outtextxy(100,120,"Instructions");outtextxy(100,140,"Settings");outtextxy(100,160,"Hall Of Fame");outtextxy(100,180,"Exit");break;  case 2:setcolor(bgc);outtextxy(100,100,"Start");setcolor(fgc);outtextxy(100,120,"Instructions");setcolor(bgc);outtextxy(100,140,"Settings");outtextxy(100,160,"Hall Of Fame");outtextxy(100,180,"Exit");break;
  case 3:setcolor(bgc);outtextxy(100,100,"Start");outtextxy(100,120,"Instructions");setcolor(fgc);outtextxy(100,140,"Settings");setcolor(bgc);outtextxy(100,160,"Hall Of Fame");outtextxy(100,180,"Exit");break;
  case 4:setcolor(bgc);outtextxy(100,100,"Start");outtextxy(100,120,"Instructions");outtextxy(100,140,"Settings");setcolor(fgc);outtextxy(100,160,"Hall Of Fame");setcolor(bgc);outtextxy(100,180,"Exit");break;
  case 5:setcolor(bgc);outtextxy(100,100,"Start");outtextxy(100,120,"Instructions");outtextxy(100,140,"Settings");outtextxy(100,160,"Hall Of Fame");setcolor(fgc);outtextxy(100,180,"Exit");break;
  }

 inp=getch();}
 return cmd;}

void startup()
{
 fstream setting("settings.dat",ios::in|ios::binary);
 if(!setting)
 {setting.open("settings.dat",ios::out|ios::binary|ios::noreplace);
 set.inpsettings(0,0,RED);
 setting.write((char*)&set,sizeof(set));
 setting.close();
 setting.open("settings.dat",ios::in|ios::binary); }
 fstream hig("highscores.dat",ios::in|ios::binary);
 if(!hig)
 {hig.open("highscores.dat",ios::out|ios::binary|ios::noreplace);
  high.assihigh();
  hig.write((char*)&high,sizeof(high));
  hig.close();
  hig.open("highscores.dat",ios::in|ios::binary);
 }
 hig.read((char*)&high,sizeof(high));
 setting.read((char*)&set,sizeof(set));
 set.assisettings();
 delay(2000);
  char geek[5],ere[5];
  int tru=0;
 settextstyle(0,0,6);
 setlinestyle(0,0,3);
 geek[5]='\0';
  setcolor(4);
  rectangle(1,1,639,479);
  setfillstyle(1,4);
  floodfill(620,420,4);
  for(int m=0;m<=60;m++)
 {setcolor(14);
  outtextxy(200,100,geek);
  strcpy(ere,geek);
  for(int i=tru;i<=4;i++)
  geek[i]=random(91-65)+65;
  delay(50);
  setcolor(4);
  outtextxy(200,100,ere);
  switch(m)
  {case 20:geek[0]='G';tru++;break;
   case 30:geek[1]='E';tru++;break;
   case 40:geek[2]='E';tru++;break;
   case 50:geek[3]='K';tru++;break;
   case 60:geek[4]='S';tru++;break;
   }}
  setcolor(14);
  outtextxy(200,100,geek);
  fflush(stdin);
  setcolor(1);
  settextstyle(1,0,7);
  char prod[11]="PRODUCTIONS";
  for(int ord=0;ord<=5;++ord)
  {char pl[2]={prod[5-ord],'\0'};
   char ll[2]={prod[5+ord],'\0'};
   outtextxy(300-(ord*40),200,pl);
   outtextxy(300+(ord*40),200,ll);
   delay(400);}
   setcolor(9);
   settextstyle(1,0,4);
   outtextxy(235,280,"PRESENTS");
   //sleep(4);
  cleardevice();
 for(int x=1;x<=9;x++)
 {setcolor(4);
 settextstyle(4,0,x);
 outtextxy(130,100,"SNAKE");
 delay(100);
 setcolor(0);
 settextstyle(4,0,x);
 outtextxy(130,100,"SNAKE");
  }
 x=1;
while(x<50)
 {
 setcolor(x);
 settextstyle(4,0,9);
 outtextxy(130,100,"SNAKE");
 setcolor(4);
 delay(100);
 setcolor(0);
 outtextxy(130,100,"SNAKE");
  x++;
  }
 fflush(stdin);
 flushall();
 }
void score1()
{
 textcolor(YELLOW);
 gotoxy(76,1);
 cout<<"Score";
 gotoxy(78,2);
 cout<<(limit-score)*2;
 gotoxy(77,4);
 cout<<"High";
 gotoxy(76,5);
 cout<<"Score";
 gotoxy(78,6);
 cout<<high.gd[set.gmode][set.gdif];
 }


void main()
{
 randomize();
 grint();
 fflush(stdin);
 startup();
 fflush(stdin);
 men:
 int cmd=menu();
 cleardevice();
 switch(cmd)
 {
  case 1:game();goto men;
  case 2:instruct();goto men;
  case 3:set.changeset();goto men;
  case 4:high.disphigh();goto men;
  case 5:if(close()==0)exit(0);
	else goto men;
	}
 }
void main1()
{ fflush(stdin);
 men:
 int cmd=menu();
 cleardevice();
 switch(cmd)
 {
  case 1:game();goto men;
  case 2:instruct();goto men;
  case 3:set.changeset();goto men;
  case 4:high.disphigh();goto men;
  case 5:if(close()==0)exit(0);
	 else goto men;
  }
 }
 void game()
 {
 int x=1,dir;
 snake obj1;
 obj1.assign();
 obj1.egg1();
 redraw();
 while(x==1)
 {score1();
  obj1.move();
 obj1.check();
 obj1.draw();
  if(debu==1)
  obj1.debug();
 delay(speed);
 if(kbhit())
 {int a=getch();
    if(a==0)
  {dir=getch();
   {if(dir==72||dir==80||dir==77||dir==75)
 {obj1.turn(dir);
   redraw();}}}
  if(a==13)
    {if(close()==0)
    {high.cmphi();main1();}
    else redraw();
    }
    if(a==32)
     {pause();
      cleardevice();
      redraw();

     }
    }

  flushall();
  }
}
int close()
{     cleardevice();
      setcolor(bgc);
      outtextxy(200,200,"do you really want to quit?");
      int ab=0,abc=0;
      while(ab!=13)
      {
       switch(ab)
       {case 72:abc--;break;
	case 80:abc++;break;
       }
      abc=abc<0?1:abc;
      abc=abc>1?0:abc;
      switch(abc)
      {case 0:setcolor(fgc);outtextxy(200,220,"Yes");setcolor(bgc);outtextxy(200,240,"No");break;
       case 1:setcolor(bgc);outtextxy(200,220,"Yes");setcolor(fgc);outtextxy(200,240,"No");break;
      }
   ab=getch();
 }
fflush(stdin);
cleardevice();
return abc;
}

void instruct()
{
 closegraph();
 _setcursortype(_NOCURSOR);
 gotoxy(34,1);
 textcolor(RED);
 cprintf("INSTRUCTIONS");
 textcolor(MAGENTA);
 gotoxy(1,3);
 cprintf("As you know,this is a snake game and you are supposed to gulp down as many eggs");
 gotoxy(1,4);
 cprintf("as you can.The more you eat,the longer you get,the higher you score.");
 gotoxy(1,7);
 cprintf("The simplest controls are ready for you to use:");
 gotoxy(1,9);
 cout<<"\t\t\t\t";
 cprintf("Movement - Arrow keys");
 gotoxy(1,11);
 cout<<"\t\t\t\t";
 cprintf("Pause - Space");
 gotoxy(1,13);
 cout<<"\t\t\t\t";
 cprintf("Exit - Enter");
 gotoxy(1,15);
 cprintf("Tweak settings to your favorite in the settings menu.");
 gotoxy(1,19);
 textcolor(YELLOW);
 cout<<"\t\t\t\t";
 cprintf("ENJOY THE GAME!");
 gotoxy(38,22);
 textcolor(BLUE);
 cprintf("ABOUT");
 gotoxy(1,23);
 textcolor(LIGHTBLUE);
 cout<<"\t\t\t";
 cprintf("Devoloped by:GEEK'S PRODUCTIONS");
 getch();
 grint();
 }
