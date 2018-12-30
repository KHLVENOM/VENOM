#include<windows.h>
#include<time.h>
#include<stdlib.h>
#include<conio.h>
#include<bits/stdc++.h>
using namespace std;
string word1[5]={"","开始游戏","新手教程","游戏设置","退出游戏"};
string word2[5]={"","经典模式","无尽模式","街机模式","天梯模式"};
string word3[7]={"","无敌版","简单","中等","困难","炼狱","不可战胜的"};
int wdd1=1,wdd2=1,wdd3=1,ts=0;
int mv1[4]={-1,0,0,1},mv2[4]={0,-1,1,0};
int special=0,tankxy[2]={35,19},tankpk[2];
bool body[2][40][24];
int stop[2]={0,0},tfangxiang=1;
int tbehave=0;
bool canatack=0,tt=0,endt=0,lelt=0,bbb=0;
int paonum=0,mark=0;
int paoxy[1000000][3],paofx[1000000][2],fangxiang=4,world[40][24];
int pxy[2]={1,1},px[5]={0,-1,1,0,0},py[5]={0,0,0,-1,1},mouse[2]={2,22};
char ch;
bool exit1=0,breeak=0,breaak2=0,breeak3=0;
int Modelice[6]={0,100,200,300,500,INT_MAX};
double Modellife[6]={2000000000,100,40,30,25,20};
double Modellife___[6]={100000000,5,2,1.5,1.25,1};
double Modeldamage[6]={50,5,1,0.8,0.5,0.25};
int Mod=2;
double plife=Modelice[Mod];
double tlife=200;
void coutlife();
void HideCursor();
void gotoxy();
void color(); 
void coutplayer(int fx,int x,int y,int cr,int asd);
void cutp(int fx,int x,int y,int asd);
void move();
void go();
void drawtitle();
void start();
void mennu(int ch);
void mainmenu();
void color(int a);
void gotoxy(int x,int y);
void pao(int fx,int x,int y,int cr);
void paomove();
inline void Done(){
	MessageBox(NULL,TEXT("完成"),TEXT("提示"),0|MB_SETFOREGROUND);
}
void dixing(){
	for(int i=1;i<39;i++)
	for(int j=1;j<23;j++)
	world[i][j]=255;
	world[1][11]=world[2][11]=world[3][11]=world[4][11]=0; 
    world[7][1]=world[7][2]=world[7][3]=world[7][4]=0; 
	world[8][16]=world[8][17]=world[8][15]=world[18][7]=0;
	world[10][31]=world[19][39]=world[19][38]=world[17][24]=0;
	world[17][23]=world[17][22]=world[17][21]=world[17][20]=0;
	world[17][25]=world[17][19]=world[17][18]=world[34][10]=0;
	world[33][10]=world[32][10]=world[31][10]=world[30][10]=0;
	world[29][15]=world[29][16]=world[29][17]=world[29][18]=0;
	world[29][19]=world[29][20]=world[25][6]=world[26][6]=0;
	world[27][6]=world[28][6]=world[29][6]=world[30][6]=0;
}
void tmove(int px,int py,int tx,int ty){
	int tmove[2]={0,0};
	if((px-tx)<=(py-ty)){
		if(px<=tx)tmove[0]=(-1);
		else tmove[0]=1;
		switch(tmove[0]){
		case -1:
		tfangxiang=2;
		if(world[tx-1][ty+1]!=255||world[tx][ty]!=255||world[tx][ty+2]!=255||world[tx-1][ty+1]!=15||world[tx][ty]!=15||world[tx][ty+2]!=15)
			tmove[0]++; 
		break;
		case 1:
		tfangxiang=3;
		if(world[tx+3][ty+1]!=255||world[tx+2][ty]!=255||world[tx+2][ty+2]!=255||world[tx+3][ty+1]!=15||world[tx+2][ty]!=15||world[tx+2][ty+2]!=15)
			tmove[0]--;
		break;
		}
	}
	if(tmove[0]==0){
		if(py<=ty)tmove[1]=(-1);
		else tmove[1]=1;
		switch(tmove[1]){
		case -1:
		tfangxiang=1;
		if(world[tx+1][ty]!=255||world[tx][ty-1]!=255||world[tx+2][ty-1]!=255)tmove[1]++;
		break;
		case 1:
		tfangxiang=4;
		if(world[tx+1][ty+3]!=255||world[tx][ty+2]!=255||world[tx+2][ty+2]!=255)tmove[1]--;
		break;
	}
}
if(tmove[1]==0&&tmove[0]==0){
	if(px<=tx){
		if(world[tx+3][ty+1]!=255||world[tx+2][ty]!=255||world[tx+2][ty+2]!=255)
			tmove[0]--;
		else
			tmove[0]=1;
	}
	switch(tmove[0]){
		case -1:
		tfangxiang=2;
		if(world[tx-1][ty+1]!=255||world[tx][ty]!=255||world[tx][ty+2]!=255)tmove[0]++;
		break;
		case 1:
		tfangxiang=3;
		if(world[tx+3][ty+1]!=255||world[tx+2][ty]!=255||world[tx+2][ty+2]!=255)tmove[0]--;
		break;
	}
}
	tankxy[0]+=tmove[0];
	tankxy[1]+=tmove[1];
}
void tmove2(int tx,int ty){
	int tmove[2]={0,0};
	if(rand()%2==0){
		tmove[0]=(rand()%3-1);
		switch(tmove[0]){
			case -1:
			tfangxiang=2;
			if(world[tx-1][ty+1]!=255||world[tx][ty]!=255||world[tx][ty+2]!=255)tmove[0]++;
			break;
			case 1:
			tfangxiang=3;
			if(world[tx+3][ty+1]!=255||world[tx+2][ty]!=255||world[tx+2][ty+2]!=255)tmove[0]--;
			break;
		}
	}
	if(tmove[0]==0){
		tmove[1]=rand()%3-1;
		switch(tmove[1]){
		case -1:
		tfangxiang=1;
		if(world[tx+1][ty]!=255||world[tx][ty-1]!=255||world[tx+2][ty-1]!=255)tmove[1]++;
		break;
		case 1:
		tfangxiang=4;
		if(world[tx+1][ty+3]!=255||world[tx][ty+2]!=255||world[tx+2][ty+2]!=255)tmove[1]--;
		break;
	}
}
	tankxy[0]+=tmove[0];
	tankxy[1]+=tmove[1];
}
void atack(int fx,int px,int py,int tx,int ty){
	canatack=0;
	if(px+1>=tx&&tx>=px-1){
		if(px==tx)canatack=1;
		if(py<ty){
			if(fx==1){
				pao(fx,tx,ty,238);
				paonum++;
			}else
				tfangxiang=1;
		}else{
			if(fx==4){
				pao(fx,tx,ty,238);
				paonum++;
			}else
				tfangxiang=4;
		}
	} 
	if(py+1>=ty&&ty>=py-1){
		if(py==ty)canatack=1;
		if(px<tx){
			if(fx==2){
				pao(fx,tx,ty,238);
				paonum++;
			}else{
				tfangxiang=2;
			}
		}else{
			if(fx==3){
				pao(fx,tx,ty,238);
				paonum++;
			}else{
			tfangxiang=3;
		}
	}
}
}
void paokou(int fx,int x,int y){
	switch(fx){
		case 1:
		tankpk[0]=x+1;
		tankpk[1]=y;
		break;
		case 2:
		tankpk[0]=x;
		tankpk[1]=y+1;
		break;
		case 3:
		tankpk[0]=x+2;
		tankpk[1]=y+1;
		break;
		case 4:
		tankpk[0]=x+1;
		tankpk[1]=y+2;
		break;
	}
}
void tank(){
	if(canatack==0)cutp(tfangxiang,tankxy[0],tankxy[1],1);
	if(canatack==0){
	if(abs(pxy[0]-tankxy[0])<=20&&abs(pxy[1]-tankxy[1])<=10)
	tmove(pxy[0],pxy[1],tankxy[0],tankxy[1]);
	else tmove2(tankxy[0],tankxy[1]);
	}
	paokou(tfangxiang,tankxy[0],tankxy[1]);
	atack(tfangxiang,pxy[0],pxy[1],tankxy[0],tankxy[1]);
	coutplayer(tfangxiang,tankxy[0],tankxy[1],204,1);
}
void pao(int fx,int x,int y,int cr){
	switch(fx){
		case 1:
		paofx[paonum][0]=0;
		paofx[paonum][1]=-1;
		paoxy[paonum][0]=x+1;
		paoxy[paonum][1]=y;
		paoxy[paonum][2]=cr;
		break;
		case 2:
		paofx[paonum][0]=-1;
		paofx[paonum][1]=0;
		paoxy[paonum][0]=x;
		paoxy[paonum][1]=y+1;
		paoxy[paonum][2]=cr;
		break;
		case 3:
		paofx[paonum][0]=1;
		paofx[paonum][1]=0;
		paoxy[paonum][0]=x+2;
		paoxy[paonum][1]=y+1;
		paoxy[paonum][2]=cr;
		break;
		case 4:
		paofx[paonum][0]=0;
		paofx[paonum][1]=1;
		paoxy[paonum][0]=x+1;
		paoxy[paonum][1]=y+2;
		paoxy[paonum][2]=cr;
		break;
	}
}
void paomove(){
	for(int a=0;a<paonum;a++){
		gotoxy(paoxy[a][0],paoxy[a][1]);
		color(255);
		if(paoxy[a][0]==pxy[0]&&paoxy[a][1]==pxy[1])
		color(17);
		if(paoxy[a][0]==tankpk[0]&&paoxy[a][1]==tankpk[1])
		color(204);
		cout<<"■";
	}
	for(int a=0;a<paonum;a++){
	paoxy[a][0]+=paofx[a][0],paoxy[a][1]+=paofx[a][1];
	if(world[paoxy[a][0]][paoxy[a][1]]!=255){
		if(body[0][paoxy[a][0]][paoxy[a][1]])plife--;
		if(body[1][paoxy[a][0]][paoxy[a][1]])tlife-=Modeldamage[Mod];
		paonum--;
		for(int q=a;q<paonum;q++){
			paoxy[q][0]=paoxy[q+1][0];
			paoxy[q][1]=paoxy[q+1][1];
			paoxy[q][2]=paoxy[q+1][2];
			paofx[q][0]=paofx[q+1][0];
			paofx[q][1]=paofx[q+1][1];
		}
	}
		if(body[0][paoxy[a][0]][paoxy[a][1]]==1){
		plife--;
		paonum--;
		for(int q=a;q<paonum;q++){
			paoxy[q][0]=paoxy[q+1][0];
			paoxy[q][1]=paoxy[q+1][1];
			paoxy[q][2]=paoxy[q+1][2];
			paofx[q][0]=paofx[q+1][0];
			paofx[q][1]=paofx[q+1][1];
		}
	}
		if(body[1][paoxy[a][0]][paoxy[a][1]]==1){
		if(paoxy[a][2]==68)
		tlife-=Modeldamage[Mod];
		else {
		stop[0]=20;
		stop[1]=20;
		}
		paonum--;
		for(int q=a;q<paonum;q++){
			paoxy[q][0]=paoxy[q+1][0];
			paoxy[q][1]=paoxy[q+1][1];
			paoxy[q][2]=paoxy[q+1][2];
			paofx[q][0]=paofx[q+1][0];
			paofx[q][1]=paofx[q+1][1];
		}
	}
	}
		for(int a=0;a<paonum;a++){
		gotoxy(paoxy[a][0],paoxy[a][1]);
		color(paoxy[a][2]);
		cout<<"■";
	}
}
void coutdixing(){
	system("cls");
	for(int i=0;i<24;i++)
	for(int y=0;y<40;y++){
		color(world[y][i]);
		cout<<"■";
	}
} 
void HideCursor(){
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void gotoxy(int x,int y){
	COORD pos;
	pos.X=x*2;
	pos.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
void color(int a){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
}
void coutplayer(int fx,int x,int y,int cr,int asd){
	switch(fx){
	case 1:
	for(int i=0;i<3;i++)
	for(int h=1;h<3;h++){
		gotoxy(x+i,y+h);
		color(cr);
		cout<<"■";
		body[asd][x+i][y+h]=1;
	}
	gotoxy(x+1,y);
	color(cr);
	cout<<"■";
	body[asd][x+1][y]=1;
	break;
	case 2:
	for(int i=1;i<3;i++)
	for(int h=0;h<3;h++){
		gotoxy(x+i,y+h);
		color(cr);
		cout<<"■";
		body[asd][x+i][y+h]=1;
	}
	gotoxy(x,y+1);
	color(cr);
	cout<<"■";
	body[asd][x][y+1]=1;
	break;
	case 3:
	for(int i=0;i<2;i++)
	for(int h=0;h<3;h++){
		gotoxy(x+i,y+h);
		color(cr);
		cout<<"■";
		body[asd][x+i][y+h]=1;
	}
	gotoxy(x+2,y+1);
	color(cr);
	cout<<"■";
	body[asd][x+2][y+1]=1;
	break;
	case 4:
	for(int i=0;i<3;i++)
		for(int h=0;h<2;h++){
			gotoxy(x+i,y+h);
			color(cr);
			cout<<"■";
			body[asd][x+i][y+h]=1;
		}
		gotoxy(x+1,y+2);
		color(cr);
		cout<<"■";
		body[asd][x+1][y+2]=1;
	}
}
void cutp(int fx,int x,int y,int asd){
	for(int i=0;i<3;i++)
	for(int h=0;h<3;h++){
		gotoxy(x+i,y+h);
		color(world[x+i][y+h]);
		cout<<"■";
		body[asd][x+i][y+h]=0;
	}
} 
void move(int ch){
	switch(ch){
		case 'w':
		if(world[pxy[0]][pxy[1]]==255&&world[pxy[0]+1][pxy[1]-1]==255&&world[pxy[0]+2][pxy[1]]==255)
		pxy[1]--;
		fangxiang=1;
		break;
		case 'a':
		if(world[pxy[0]][pxy[1]]==255&&world[pxy[0]-1][pxy[1]+1]==255&&world[pxy[0]][pxy[1]+2]==255)
		pxy[0]--;
		fangxiang=2;
		break;
		case 'd':
		if(world[pxy[0]+2][pxy[1]]==255&&world[pxy[0]+3][pxy[1]+1]==255&&world[pxy[0]+2][pxy[1]+2]==255)
		pxy[0]++;
		fangxiang=3;
		break;
		case 's':
		if(world[pxy[0]][pxy[1]+2]==255&&world[pxy[0]+1][pxy[1]+3]==255&&world[pxy[0]+2][pxy[1]+2]==255)
		pxy[1]++;
		fangxiang=4;
		break;
		default:break;
		}
	}
void coutlife(){
	gotoxy(0,23);
	for(int i=0;i<(plife)/Modellife___[Mod];i++){
		color(17);
		cout<<"■";
	}
	for(int i=(plife)/Modellife___[Mod];i<40-(tlife)/10;i++){
		color(255);
		cout<<"■";
	}
	gotoxy(40-(tlife)/10,23);
	for(int i=0;i<(tlife)/10;i++){
		color(204);
		cout<<"■";
	}
}
void go(int Mod,int tt,int endt,int lelt){
	int wait=Modelice[Mod];
	tlife=200;
	coutplayer(fangxiang,pxy[0],pxy[1],17,0);
	while(1){
		if(endt==1){
			gotoxy(1,22);
			color(243);
			cout<<"你的分数："<<mark;
		}
		if(mark%5==0&&mark!=0&&bbb==0){
			if(plife>=Modellife[Mod]-10){
				plife=Modellife[Mod];
				bbb=1;
			}else{
				for(int i=1;i<=10;i++){
					plife+=1;
					coutlife();
					Sleep(10);
				}
				bbb=1;
			}
		}
		if(!stop[0])tank();
		else{
			stop[0]--;
			if(stop[1]){
				stop[1]--;
			coutplayer(tfangxiang,tankxy[0],tankxy[1],188,1);
		}
		else coutplayer(tfangxiang,tankxy[0],tankxy[1],204,1);
		}
		for(int i=0;i<5;i++){
			if(wait<Modelice[Mod])wait++;
			gotoxy(1,21);
			color(243);
			cout<<"冷却：";
			if(Modelice[Mod]-wait>=2147483647)
				cout<<-1;
			else
				if(Modelice[Mod]-wait<100&&Modelice[Mod]-wait>=10)
					gotoxy(4,21),cout<<"0"<<Modelice[Mod]-wait;
				else
					if(Modelice[Mod]-wait<10)
						gotoxy(4,21),cout<<"00"<<Modelice[Mod]-wait;
					else
						cout<<Modelice[Mod]-wait;
			if(kbhit()){
				ch=getch();
				if(ch=='j'){
					pao(fangxiang,pxy[0],pxy[1],68);
					paonum++;
				}
				if(ch=='k'&&wait==Modelice[Mod]){
					pao(fangxiang,pxy[0],pxy[1],30);
					paonum++;
					wait=0;
				}
				if(paonum)paomove();
				if(ch!=106)cutp(fangxiang,pxy[0],pxy[1],0);
				move(ch);
			}
			coutlife();
			coutplayer(fangxiang,pxy[0],pxy[1],17,0);
			if(paonum)paomove();
			Sleep(30);
			HideCursor();
			if(plife<=0){
				coutlife();
				MessageBox(NULL,TEXT("你输了！"),TEXT("提示"),MB_SETFOREGROUND|MB_OK);
				return ;
			}
			if(tlife<=0){
				coutlife();
				if(endt==1){
					cutp(fangxiang,tankxy[0],tankxy[1],0);
					tankxy[0]=35;
					tankxy[1]=19;
					memset(body,0,sizeof(body));
				
					tlife=200;
					mark++;
					bbb=0;
				}else{
					MessageBox(NULL,TEXT("你赢了！"),TEXT("提示"),MB_SETFOREGROUND|MB_OK);
					return ;
				}
			}
	    }
	}
}
void drawtitle(){
	for(int i=6;i<=10;i++)
		gotoxy(i,5),cout<<"■";
	for(int i=6;i<=11;i++)
		gotoxy(8,i),cout<<"■";
	gotoxy(13,5);cout<<"■";
	gotoxy(14,5);cout<<"■";
	for(int i=6;i<=11;i++)
		gotoxy(12,i),cout<<"■";
	gotoxy(13,8);cout<<"■";
	gotoxy(14,8);cout<<"■";
	for(int i=6;i<=11;i++)
		gotoxy(15,i),cout<<"■";
	for(int i=5;i<=11;i++)
		gotoxy(17,i),cout<<"■";
	for(int i=5;i<=11;i++)
		gotoxy(21,i),cout<<"■";
	for(int i=1;i<=3;i++)
		gotoxy(17+i,6+i),cout<<"■";
	for(int i=5;i<=11;i++)
		gotoxy(23,i),cout<<"■";
	for(int i=1;i<=4;i++)
		gotoxy(28-i,4+i),cout<<"■";
	for(int i=1;i<=3;i++)
		gotoxy(24+i,8+i),cout<<"■";
	gotoxy(29,5);cout<<"■";
	gotoxy(29,6);cout<<"■";
	for(int i=32;i<=34;i++)
		gotoxy(i,5),cout<<"■";
	gotoxy(31,6);cout<<"■";
	gotoxy(31,7);cout<<"■";
	gotoxy(32,8);cout<<"■";
	gotoxy(33,8);cout<<"■";
	gotoxy(34,9);cout<<"■";
	gotoxy(34,10);cout<<"■";
	for(int i=31;i<=33;i++)
		gotoxy(i,11),cout<<"■";
	for(int i=12;i<=16;i+=2)
		for(int j=13;j<=18;j++)
			gotoxy(i,j),cout<<"■";
	gotoxy(13,19);cout<<"■";
	gotoxy(15,19);cout<<"■";
	gotoxy(19,13);cout<<"■";
	gotoxy(20,13);cout<<"■";
	for(int i=14;i<=19;i++)
		gotoxy(18,i),cout<<"■";
	gotoxy(19,16);cout<<"■";
	gotoxy(20,16);cout<<"■";
	for(int i=14;i<=19;i++)
		gotoxy(21,i),cout<<"■";
	for(int i=13;i<=19;i++)
		gotoxy(23,i),cout<<"■";
	for(int i=13;i<=16;i+=3)
		for(int j=24;j<=26;j++)
			gotoxy(j,i),cout<<"■";
	gotoxy(26,14);cout<<"■";
	gotoxy(26,15);cout<<"■";
	for(int i=17;i<=19;i++)
		gotoxy(25,i),cout<<"■";
	gotoxy(26,19);cout<<"■";
	for(int i=13;i<=17;i++)
		gotoxy(28,i),cout<<"■";
	gotoxy(28,19);cout<<"■";
}
void mennu3(char ch){
	switch(ch){
		case 106:
		if(mouse[1]==5){
			Mod=0;
			breeak3=1;
			return ;
		}
		if(mouse[1]==7){
			Mod=1;
			breeak3=1;
			return ;
		}
		if(mouse[1]==9){
			Mod=2;
			breeak3=1;
			return ;
		}
		if(mouse[1]==11){
			Mod=3;
			breeak3=1;
			return ;
		}
		if(mouse[1]==13){
			Mod=4;
			breeak3=1;
			return ;
		}
		if(mouse[1]==15){
			Mod=5;
			breeak3=1;
			return ;
		}
		break;
		case 119:
		if(mouse[1]==5)break;
		gotoxy(5,mouse[1]);
		wdd3--;
		color(115);
		cout<<word3[wdd3+1];
		mouse[1]-=2;
		break;
		case 115:
		if(mouse[1]==15)break;
		gotoxy(5,mouse[1]);
		wdd3++;
		color(115);
		cout<<word3[wdd3-1];
		mouse[1]+=2;
		break;
		case 27:
		breeak3=1;
		return ;
		default:break;
	}
}
void setting(){
	system("cls");
	gotoxy(5,5);
	color(126);
	cout<<"无敌版";
	gotoxy(5,7);
	color(115);
	cout<<"简单";
	gotoxy(5,9);
	cout<<"中等";
	gotoxy(5,11);
	cout<<"困难";
	gotoxy(5,13);
	cout<<"炼狱";
	gotoxy(5,15);
	cout<<"不可战胜"; 
	mouse[1]=5;
	breeak3=0;
	while(1){
		if(kbhit()){
			ch=getch();
			mennu3(ch);
			if(breeak3==1){
				Done();
				break;
			}
			gotoxy(5,mouse[1]);
			color(126);
			cout<<word3[wdd3];
		}
		HideCursor();
    }
}
void level(){
	dixing();
	coutdixing();
	go(Mod,tt,endt,lelt);
}
void tiktok(){
	dixing();
	coutdixing();
	go(Mod,tt,endt,lelt);
}
void nonend(){
	dixing();
	coutdixing();
	endt=1;
	go(Mod,tt,endt,lelt);
}
void help(){
	MessageBox(NULL,TEXT("KHL出品"),TEXT("新手帮助"),MB_SETFOREGROUND|MB_OK);
	MessageBox(NULL,TEXT("    在菜单选择界面按A、D控制左右，按J确定，按键盘左上角Esc返回。在战斗界面，按WSAD控制上下左右，J发子弹，K发射冰冻弹。"),TEXT("新手帮助"),MB_SETFOREGROUND|MB_OK);
}
void fille(){
	dixing();
	coutdixing();
	go(Mod,tt,endt,lelt);
}
void mennu2(char ch){
	switch(ch){
		case 106:
		if(mouse[0]==2){
			fille();
			breaak2=1;
			return ;
		}
		if(mouse[0]==12){
			nonend();
			breaak2=1;
			return ;
		}
		if(mouse[0]==22){
			tiktok();
			breaak2=1; 
			return ;
		} 
		if(mouse[0]==32){
			level();
			breaak2=1; 
			return ;
		} 
		break;
		case 97:
		if(mouse[0]==2)break;
		wdd2--;
		gotoxy(mouse[0]+1,22);
		color(120);
		cout<<word2[wdd2+1];
		mouse[0]-=10;
		break;
		case 100:
		if(mouse[0]==32)break;
		gotoxy(mouse[0]+1,22);
		wdd2++;
		color(120);
		cout<<word2[wdd2-1];
		mouse[0]+=10;
		break;
		case 27:
		breaak2=1;
		return ;
		default:break;
	}
}
void start(){
	system("cls");
	color(153); 
	drawtitle();
	gotoxy(3,22);
	color(126);
	cout<<"经典模式";
	gotoxy(13,22);
	color(120);
	cout<<"无尽模式";
	gotoxy(23,22);
	cout<<"街机模式";
	gotoxy(33,22);
	cout<<"天梯模式";
	mouse[0]=2;
	breaak2=0;
	while(1){
		if(kbhit()){
			ch=getch();
			mennu2(ch);
			if(breaak2==1)break;
			gotoxy(mouse[0]+1,22);
			color(126);
			cout<<word2[wdd2];
		}
		HideCursor();
    }
}
void mennu(char ch){
	switch(ch){
		case 106:
		if(mouse[0]==2){
			start();
			breeak=1;
			return ;
		}
		if(mouse[0]==12){
			help();
			breeak=1;
			return ;
		}
		if(mouse[0]==22){
			setting();
			breeak=1;
			return ;
		}
		if(mouse[0]==32){
			exit1=1;
			breeak=1;
			return ;
		}
		break;
		case 97:
		if(mouse[0]==2)break;
		gotoxy(mouse[0]+1,22);
		wdd1--;
		color(120);
		cout<<word1[wdd1+1];
		mouse[0]-=10;
		break;
		case 100:
		if(mouse[0]==32)break;
		gotoxy(mouse[0]+1,22);
		wdd1++;
		color(120);
		cout<<word1[wdd1-1];
		mouse[0]+=10;
		break;
		default:
		break;
	}
}
void mainmenu(){
	gotoxy(3,22);
	color(126);
	cout<<"开始游戏";
	color(120);
	gotoxy(13,22);
	cout<<"新手教程";
	gotoxy(23,22);
	cout<<"游戏设置";
	gotoxy(33,22);
	cout<<"退出游戏";
	color(126);
	mouse[0]=2;
	breeak=0;
	while(1){
		if(kbhit()){
			ch='@';
			ch=getch();
			mennu(ch);
			if(breeak==1)
				break;
			gotoxy(mouse[0]+1,22);
			color(126);
			cout<<word1[wdd1];
		}
		HideCursor();
    }
}
void mem(){
	system("cls");
	system("color 7C");
	tfangxiang=1;
	canatack=0;
	memset(body,0,sizeof(body));
	ch='@';
	tt=endt=lelt=0;
	mark=paonum=0;
	wdd1=wdd2=wdd3=1;
	stop[0]=0;
	pxy[0]=pxy[1]=1;
	tankxy[0]=35;
	tankxy[1]=19;
	plife=Modellife[Mod];
	tlife=200;
}
int main(void)
{
	help();
	while(exit1==0)
	{
		mem();
		gotoxy(1,1);
		HideCursor();
		color(204);
		drawtitle();
		mainmenu();
	}
	return 0;
} 
