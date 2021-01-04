#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<math.h>
#include<string.h>
#include<conio.h>
#include<mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include "Digitalv.h"

#define Quit -1
#define Submit -2
#define Choose -3

#define BLACK 0 
#define BLUE 1 
#define GREEN 2 
#define CYAN 3 
#define RED 4 
#define MAGENTA 5 
#define BROWN 6 
#define LIGHTGRAY 7 
#define DARKGRAY 8 
#define LIGHTBLUE 9 
#define LIGHTGREEN 10 
#define LIGHTCYAN 11 
#define LIGHTRED 12 
#define LIGHTMAGENTA 13 
#define YELLOW 14 
#define WHITE 15 

int abs(int);
int keyControl(int,int,int,int,int*,int,int,int*);
void titleDraw();
int menuDraw(int,char*,int);
int infoDraw1();
int infoDraw2();
void init();
void going(int,int);
int startGame(int,int,int,int,int,int,int,int,int,int,int,int);
int printOverview(int,int,int,int,int,int,int,int,int,int,int,int);
int changeLevel(int,int,int,int,int,int,int,int,int,int,int,int);
int Broken(int,int,int,int,int,int);
int makingProblem();
int ectDraw(int,int,int,int,int,int,int,int);
void textcolor(int,int);
int combi(int,int);
void ItemDraw(int);
void eraser(int);
void Evaluate(int);
int ModeChoosing(int);
int timecheck(int,int,int);
void DrawGameOver();
void PlayBGM();
void Count(int,int,int,int,int,int,int,int,int,int,int,int);
void BackUp(int*,int*,int*,int*,int*,int,int*,int*,int*,int*,int*);
void wow();
void PatientEgg();
void format(int);
void PBroken(int,int);
void BackM(int *,char *);
void Master(char *);
int Critical(int);
int inchentStone(int *,int);
void weaponDraw(int);
void wEffect(int,int);
int weapon(int*,int*,int,int,int,int,int,int,int,int,int,int,int,int);
int desc(const void*, const void*);
int Bag(int);
void Fild();

char Check;
int item[1000000],iid,alpha,betha;
int checker,ban[100];

int main() {
	int menuCode=-1,re=30,i=0,Mode=0,wow2=0;
	char u[10]={};
	init();
	textcolor(WHITE,BLACK);
	BackM(&wow2,u);
	while(1){
		i=0;
		system("cls");
		if(menuCode==0 && Mode!=-1){
			system("cls");
			if(re!=100 && menuCode!=3) DrawGameOver();
			if(re==100){
				if(wow2==1) format(-2);
				memset(u,0,10);
				going(18,20);
				printf("Please Enter your name");
				going(8,22);
				printf("Your Name: ");
				while(1){
					going(19+i,22);
					if(i<10 && kbhit()){
						u[i]=_getwche();
		 				i++;
					}
			
		 			if(u[i-1]==13) break; //13==enter
		 			if(i==10){
		 				going(19,22);
		 				printf("                ");
		 				i=0;
				 		going(19,22);
				 		memset(u,0,10);
				 	}
				 	else if(u[i-1]==8){
				 		going(19+i-2,22);
				 		printf(" ");
						u[i-2]=0;
				 		if(i>=2) i-=2;
					}
				}
				FILE *fp;
				fp=fopen(".\\save\\wow.txt","w");
				fprintf(fp,"1\n");
				fprintf(fp,"%s",u);
				fclose(fp);
			}
			while(re!=100 && Mode!=-1){
				if(keyControl(1,0,0,0,0,-1,0,0)==Submit) break;
			}
		}
		
		system("cls");
		going(1,4);
		titleDraw();
		menuCode=menuDraw(re,u,wow2);
		if(menuCode==0){
			memset(item,-1,1000000);
			int stage=1,Level=1,EXP=0,EggHealth=1,original=0,stone=0,wlevel=1;
			int gotEXP=0,gotStone=0,percento=4;
			Mode=ModeChoosing(menuCode);
			if(Mode==-1) continue;
			clock_t time = clock();
			PlayBGM();
					
			BackUp(&stage,&Level,&EXP,&EggHealth,&original,Mode,&stone,&wlevel,&gotEXP,&gotStone,&percento);
			if(stage%7==0 && stage%5!=0 && stage%3!=0) {
				stage++;
				EggHealth=1,original=0,gotEXP=0,gotStone=0;
			}
			while(kbhit()==1) getch();
			re=startGame(Level,stage,EXP,Mode,time,percento,EggHealth,original,stone,wlevel,gotEXP,gotStone);
			checker=0;
		}
		else if(menuCode==1){
			int p;
			p=infoDraw1();
			while(1){
				if(p==1) p=infoDraw1();
				else if(p==2) p=infoDraw2();
				else break;
			}
			
		}
		else if(menuCode==-1 || menuCode==2) {
			system("cls");
			return 0;
		}
		else if(menuCode==3){
			int Mode=ModeChoosing(menuCode);
			format(Mode);
		}
	}
	return 0;
}

void format(int Mode){
	FILE *fp;
	if(Mode==-2) fp=fopen(".\\save\\Mode 1.txt","w");
	if(Mode==0) fp=fopen(".\\save\\Mode 2.txt","w");
	if(Mode==2) fp=fopen(".\\save\\Mode 3.txt","w");
	if(Mode==4) fp=fopen(".\\save\\Mode 4.txt","w");
	if(Mode!=-2) fprintf(fp,"0\n1\n1\n0\n1\n0\n0\n1\n0\n0\n4\n0");
	else fprintf(fp,"0\n1\n1\n0\n1\n0\n0\n1\n0\n0\n4\n0");
	fclose(fp);
	if(Mode<=0) return;
	FILE *f;
	if(Mode==2) f=fopen(".\\save\\Item 1.txt","w");
	if(Mode==4) f=fopen(".\\save\\Item 2.txt","w");
	fprintf(f," ");
	fclose(f);
	if(Mode==2) f=fopen(".\\save\\Ban 1.txt","w");
	if(Mode==4) f=fopen(".\\save\\Ban 2.txt","w");
	fprintf(f," ");
	fclose(f); 
}
void BackM(int *wow2,char *u){
	char wow1;
	FILE *fp;
	fp=fopen(".\\save\\wow.txt","r");
	fscanf(fp,"%c",&wow1);
	if(wow1=='0') *wow2=0;
	else *wow2=1;
	fscanf(fp,"%s",u);
	fclose(fp);
	if(*wow2==1) format(-2);
}

void BackUp(int *stage,int *Level,int *EXP,int *EggHealth,int*original,int Mode,int*stone,int*wlevel,int*gotEXP,int*gotStone,int*percento){
	char pp[10]={};
	char stage1[10]={};
	char Level1[10]={};
	char EXP1[10]={};
	char item1[10]={};
	char EggHealth1[10]={};
	char original1[10]={};
	char stone1[10]={};
	char wlevel1[10]={};
	char gotEXP1[10]={};
	char gotStone1[10]={};
	char percento1[10]={};
	char iid1[10]={};
	char ban1[10]={};
	char ttime1[10]={};

	FILE *fp;
	if(Mode==-2) fp=fopen(".\\save\\Mode 1.txt","r");
	if(Mode==0) fp=fopen(".\\save\\Mode 2.txt","r");
	if(Mode==2) fp=fopen(".\\save\\Mode 3.txt","r");
	if(Mode==4) fp=fopen(".\\save\\Mode 4.txt","r");
	
	fscanf(fp,"%s",pp); //Trash
	fscanf(fp,"%s",stage1);
	fscanf(fp,"%s",Level1);
	fscanf(fp,"%s",EXP1);
	fscanf(fp,"%s",EggHealth1);
	fscanf(fp,"%s",original1);
	fscanf(fp,"%s",stone1);
	fscanf(fp,"%s",wlevel1);
	fscanf(fp,"%s",gotEXP1);
	fscanf(fp,"%s",gotStone1);	
	fscanf(fp,"%s",percento1);
	fscanf(fp,"%s",iid1);
	if(Mode==4) fscanf(fp,"%s",ttime1); 
	
	*stage=atoi(stage1);
	*Level=atoi(Level1);
	*EXP=atoi(EXP1);
	*EggHealth=atoi(EggHealth1);
	*original=atoi(original1);
	*stone=atoi(stone1);
	*wlevel=atoi(wlevel1);
	*gotEXP=atoi(gotEXP1);
	*gotStone=atoi(gotStone1);
	*percento=atoi(percento1);
	iid=atoi(iid1);
	fclose(fp);
	if(Mode<=0) return;
	
	FILE *f;
	if(Mode==2) f=fopen(".\\save\\Item 1.txt","r");
	if(Mode==4) f=fopen(".\\save\\Item 2.txt","r");
	int i=0;
	for(i=0;i<iid;i++){
		memset(item1,0,10);
		fscanf(f,"%s",item1);
		item[i]=atoi(item1);
	}
	fclose(f);
	if(Mode==2) f=fopen(".\\save\\Ban 1.txt","r");
	if(Mode==4) f=fopen(".\\save\\Ban 2.txt","r");
	for(i=0;i<iid;i++){
		memset(ban1,0,10);
		fscanf(f,"%s",ban1);
		ban[i]=atoi(ban1);
	}
	fclose(f);
}

void PlayBGM(){
	MCI_OPEN_PARMS m_mciOpenParms;
	MCI_PLAY_PARMS m_mciPlayParms;
	DWORD m_dwDeviceID;
	MCI_OPEN_PARMS mciOpen;
	MCI_PLAY_PARMS mciPlay;

	 mciOpen.lpstrElementName = ".\\music\\BGM.mp3";
	 mciOpen.lpstrDeviceType = "mpegvideo";
 
	 mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT|MCI_OPEN_TYPE,(DWORD)(LPVOID)&mciOpen);
 
	 int dwID = mciOpen.wDeviceID;
 
	  mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, // play & repeat
    	 (DWORD)(LPVOID)&m_mciPlayParms);
 
 
	/* mciSendCommandW(dwID, MCI_PAUSE, MCI_NOTIFY,
                (DWORD)(LPVOID)&m_mciPlayParms);     */// Pause
                                                
	/* mciSendCommandW(dwID, MCI_RESUME, 0, NULL);       */// resume
 
	/* mciSendCommandW(dwID, MCI_CLOSE, 0, NULL);        */// stop
}

void DrawGameOver(){
	going(0,5);
	printf("        ■■■■■   ■■■   ■        ■ ■■■■ \n");
	printf("        ■         ■      ■ ■■    ■■ ■       \n");
	printf("        ■  ■■■ ■■■■■ ■ ■  ■ ■ ■■■■ \n");
	printf("        ■      ■ ■      ■ ■  ■■  ■ ■       \n");
	printf("        ■■■■■ ■      ■ ■   ■   ■ ■■■■ \n");
	printf("\n");
	printf("           ■■■■ ■      ■ ■■■■ ■■■■  \n");
	printf("          ■      ■ ■    ■  ■       ■     ■ \n");
	printf("          ■      ■  ■  ■   ■■■■ ■■■■  \n");
	printf("          ■      ■   ■■    ■       ■    ■  \n");
	printf("           ■■■■     ■     ■■■■ ■     ■ \n\n\n");
	printf("                   press Enter to go Main");
}

void init(){
	system("mode con cols=60 lines=40 | title 알 까기");
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible=0;
	ConsoleCursor.dwSize=1;
	SetConsoleCursorInfo(consoleHandle,&ConsoleCursor);
}

void going(int x, int y){
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(consoleHandle,pos);
}

void titleDraw(){
	printf("\n\n\n");
	printf("                          *****           \n");
	printf("                        **     **         \n");
	printf("                       **       **        \n");
	printf("                      **         **       \n");
	printf("                     **           **      \n");
	printf("                    **             **     \n");  
	printf("                    **             **     \n");
	printf("                     **           **      \n");
	printf("                      **         **       \n");
	printf("                        *********         \n");
}
void Master(char *name){
 	int i,l;
	l=strlen(name);
	going(24,27);
	printf("Egg Master");
	going(22,28);
	printf("┌──────────┐");
	going(22,29);
	printf("│ ");
	for(i=0;i<(10-l)/2+1;i++){
		printf(" ");
	}
	for(i=0;i<l;i++){
		printf("%c",name[i]);
	}
	for(i=0;i<(10-l)/2;i++){
		printf(" ");
	}
	going(33,29);
	printf("│");
	going(22,30);
	printf("└──────────┘");
 }
 
int menuDraw(int re,char *name,int pop){
	int x=25,y=20;
	going(x-3,y);
	printf("> Start Game");
	going(x-1,y+1);
	printf("Game Info");
	going(x-1,y+2);
	printf("End Game");
	going(1,39);
	printf("Beta 0.5.0");
	going(24,y+3);
	printf("Format");
	
	
	if(re==100 || pop){
		Master(name);
	}
	
	while(1){
		int n=keyControl(1,0,0,0,0,-1,0,0);
		switch(n){
			case Choose: {
				going(x-3,y);
				printf(" ");
				if(y<=22){
					going(x-3,++y);
					printf(">");
				}
				else if(y==23){
					going(x-3,y-=3);
					printf(">");
				}
				break;
			}
			case Submit: {
				return y-20;
			}
			case Quit: return -1;
		}
	}
}

int abs(int n){
	if(n<0) return -n;
	else return n;
}

void eraser(int p){
	if(p){
		going(10,18);
		printf("Your Answer: ");
	}
	going(23,18);
	printf("                        ");
	Sleep(800);
	going(22,23);
	printf("                        ");
	going(23,18);
	Check=127;
}

int Critical(int atk){
	going(22,23);
	textcolor(MAGENTA,YELLOW);
	printf("Critical!!");
	textcolor(WHITE,BLACK); 
	return atk*2;
}

int keyControl(int Stage,int wLevel,int answer,int Health,int *ich,int Mode,int ttime,int *ic){
	int i=0,sch,Attack=1.5*wLevel,aitem=-1,aans=abs(answer);
	char u[11]={},ans[10]={},t=0;
	sprintf(ans,"%d",answer);
	
	if(Stage%3==0) sch=1;
	else if(Stage%5==0) sch=2;
	else if(Stage%7==0) sch=3;
	else sch=0;
	
	if(sch==0 || sch==3 || Mode<=0) {
		while(!u[0]){
			if(kbhit()){
				u[0]=_getwch();
				break;
			}
			if(Mode==4 || (Mode==2 && sch==3 && Stage!=1)) {
				int y=timecheck(ttime,Stage,Mode);
				if(y==-1) return Quit;
				else if(y==1) return 1;
			}
			going(23,18);
		}
	}
	else if(sch==2 && Mode>=2){
		eraser(1);
		while(1){
			if(Mode==4 || (Mode==2 && sch==3 && Stage!=1)) {
				int y=timecheck(ttime,Stage,Mode);
				if(y==-1) return Quit;
				else if(y==1) return 1;
			}
			going(23+i,18);
			if(i<10 && kbhit()){
				u[i]=_getwche();
		 		i++;
			}
			if(u[i-1]==9) break;
		 	if(u[i-1]==13) break;
		 	if(i==10){ 
		 		going(23,18);
		 		printf("             ");
		 		i=0;
		 		going(22,18);
		 		memset(u,0,10);
		 	}
		 	else if(u[i-1]==8){
		 		going(23+i-2,18);
		 		printf(" ");
				u[i-2]=0;
		 		if(i>=2) i-=2;
			 }
		}
	}
	else if(sch==1 && Mode>=2){
		going(28,12);
		printf("%c",answer);
		eraser(0);
		while(t==0){
			if(kbhit()) t=getch();
			if(Mode==4 || (Mode==2 && sch==3 && Stage!=1)) {
				int y=timecheck(ttime,Stage,Mode);
				if(y==-1) return Quit;
				else if(y==1) return 1;
			}
			going(23,18);
		}
		sprintf(u,"%c",t);
	}
	
	t=u[0];
	u[i-1]=0;
	
	int a=(sch==1 || sch==2), b=(!strcmp(ans,u) || t==answer);
	
	if(Check==t && t!=32 && t!=13 && t!='=' && sch%3==0) return 0;
	Check=t;
	
	if(t==9 && Mode>=2){
		aitem=Bag(sch);
		system("mode con cols=60 lines=40 | title 알 까기");
		if(aitem==1) { 
			PlaySound(".\\music\\TicTok.wav", NULL, SND_ASYNC);
			return Health/2;
		}
		else if(aitem==2){
			ich[(*ic)++]=2;
			PlaySound(".\\music\\Freeze.wav",NULL, SND_ASYNC);
		} 
		else if(aitem==3) {
			ich[(*ic)++]=3;
			PlaySound(".\\music\\Block.wav",NULL, SND_ASYNC);
		}
	}
	if(t==13){
		if(!wLevel) return Submit;
		else return 0;
	}
	else if(!strcmp(u," ")){
		return Choose;
	}
	else if(!strcmp(u,"=") || t=='='){
		return Quit;
	}
	else if(b && a && Mode>=2 || aitem==0){
	
		going(22,22);
		printf("                      ");
		Evaluate(1);
		if(aitem==0) {
			PlaySound(".\\music\\ItemUse.wav", NULL, SND_ASYNC | SND_FILENAME);
		}
		if(sch==2) return Attack*aans;
		else if(sch==1) {
			if(answer<97) return Attack*(aans%63);
			else return Attack*(aans%95);
		}
	}
	else if(!b && a && Mode>=2 && aitem==-1 && t!='='){
		Evaluate(0);
		return 0;
	}
	else if((t>=65 && t<=90)|| (t>=97 && t<=122)){
		if(t=='q' && !wLevel) return 113;
		return Attack;
	}
	return 0;
}

int timecheck(int ttime,int Stage,int Mode){
	going(25,2);
	double timec=(double)(clock()-ttime+alpha)/CLOCKS_PER_SEC;
	if(Stage%7) printf("%g",timec);
	else if(Stage%7==0 && Mode!=4) printf("%g",-timec);
	if(timec>=100) return Quit;
	else if(-timec<=0 && Stage%7==0) return 1;
	else return 0;
}

void Evaluate(int p){
	if(p) {
		going(22,23);
		textcolor(LIGHTCYAN,LIGHTBLUE);
		printf("Perfect!!!");
		PlaySound(".\\music\\Correct.wav", NULL, SND_ASYNC);
		textcolor(WHITE,BLACK); 
	}
	else {
		going(23,23);
		textcolor(YELLOW,LIGHTRED);
		printf("Oops!");
		PlaySound(".\\music\\Oops.wav", NULL, SND_ASYNC);
		textcolor(WHITE,BLACK);
	}
}

void textcolor(int foreG,int backG){
	int color=foreG+backG*16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}

int infoDraw1(){
	system("cls");
	printf("\n\n\n\n");
	printf(" _________________________________________________________\n");
	printf("|                         Control                         |\n");
	printf("|                                                         |\n");
	printf("|                   Attack:   English Key                 |\n");
	printf("|                                                         |\n");
	printf("|                     Move:   Space bar                   |\n");
	printf("|                                                         |\n");
	printf("|                   Choose:   ENTER                       |\n");
	printf("|                                                         |\n");
	printf("|            아이템 버리기:   'q'                         |\n");
	printf("|                                                         |\n");
	printf("|                    Erase:   Backspace                   |\n");
	printf("|                                                         |\n");
	printf("|                     Quit:   '='                         |\n");
	printf("|                                                         |\n");
	printf("|               Using item:   ENTER                       |\n");
	printf("|                                                         |\n");
	printf("|                      Bag:   TAB                         |\n");
	printf("|                                                         |\n");
	printf("|        ****연속으로 같은 키로 공격할 수 없음****        |\n");
	printf("|                                                         |\n");
	printf("|                Developer:   Cyanobacteria               |\n");
	printf("|                                                         |\n");
	printf("|                 ENTER 클릭시 메인으로    -> 다음 페이지 |\n");
	printf("|_________________________________________________________|\n");
	printf("|                                                         |\n");
	printf("|          □□□□□□□□□□■□■  □   □□□        |\n");
	printf("|          ■ ■■■■■■■■■■■■ □   □□□        |\n");
	printf("|          □  ■■■■■■■■■■■  ■                 |\n");
	printf("|          □   ■■■■■■■■■■   □     □          |\n");
	printf("|          □□□□    ■    □□□□  □   □□□        |\n");
	printf("|_________________________________________________________|\n");
	while(1){
		int t=keyControl(1,0,0,0,0,-1,-1,0);
		if(t==Submit) return 0; 
		else if(t==Choose) return 2;
	}
}

int infoDraw2(){
	system("cls");
	printf("\n\n\n\n");
	printf(" _________________________________________________________\n");
	printf("|                       간단한 설명                       |\n");
	printf("|                                                         |\n");
	printf("|        Stage%%3==0 -> 화면에 나오는 키 클릭              |\n");
	printf("|                                                         |\n");
	printf("|        Stage%%5==0 -> 간단한 문제                        |\n");
	printf("|                                                         |\n");
	printf("|        Stage%%7==0 -> 터치마다 EXP 획득(10초 제한시간)   |\n");
	printf("|                                                         |\n");
	printf("|        Patient Mode  = 달걀의 체력 9999999              |\n");
	printf("|                                                         |\n");
	printf("|        Original Mode = 순수한 달걀 깨기                 |\n");
	printf("|                                                         |\n");
	printf("|        Variety Mode  = 아이템 등장!!                    |\n");
	printf("|                                                         |\n");
	printf("|        Time Attack   = 시간제한 100초 && 아이템!        |\n");
	printf("|                                                         |\n");
	printf("| <-이전 페이지   ENTER 클릭시 메인으로                   |\n");
	printf("|_________________________________________________________|\n");
	
	while(1){
		int t=keyControl(1,0,0,0,0,-1,-1,0);
		if(t==Submit) return 0; 
		else if(t==Choose) return 1;
	}
	
}
int ModeChoosing(int menu){
	int x=25,y=18;
	system("cls");
	if(menu==3){
		going(11,10);
		printf("Choose which Mode you want to format");
	}
	going(x-3,y-2);
	printf("> Patient Mode");
	going(x-1,y);
	printf("Original Mode");
	going(x-1,y+2);
	printf("Variety Mode");
	going(x-1,y+4);
	printf("Time Attack");
	y=16;
	while(1){
		int n=keyControl(1,0,0,0,0,-1,-1,0);
		switch(n){
			case Choose: {
				going(x-3,y-2);
				printf(" ");
				if(y<=20){
					going(x-3,y);
					printf(" ");
					going(x-3,y+=2);
					printf(">");
				}
				else if(y==22){
					going(x-3,y);
					printf(" ");
					going(x-3,y-=6);
					printf(">");
				}
				break;
			}
			case Submit: {
				return y-18;
			}
			case Quit: {
				return -1;
				break;
			}
		}
	}	
}

int inchentStone(int *stone,int Level){
	srand(100*time(NULL)%107);
	int t=rand()%(Level%2+1)+1;
	*stone+=t;
	return t;
}

void weaponDraw(int p){
	going(0,6);
	if(p==1){
		printf("                             *             \n");
		printf("                            * *            \n");
		printf("                           *   *           \n");
		printf("                           *   *           \n");
		printf("                           *   *           \n");
		printf("                           *   *           \n");
		printf("                           *   *           \n");
		printf("                           *   *           \n");
		printf("                           *   *           \n");
		printf("                        ***********        \n");
		printf("                            * *            \n");
		printf("                            * *            \n");
		printf("                            ***            \n");
	}
	
	if(p==0){
		printf("                          *             \n");
		printf("                         * *            \n");
		printf("                        *   *           \n");
		printf("                        *   *           \n");
		printf("                        *****           \n");
		printf("                        **    **           \n");
		printf("                           *****           \n");
		printf("                           *   *           \n");
		printf("                           *   *           \n");
		printf("                        ***********        \n");
		printf("                            * *            \n");
		printf("                            * *            \n");
		printf("                            ***            \n");	
	}
}

void wEffect(int p,int i){
	int j,k;
	for(j=0;j<39;j++){
		for(k=0;k<39;k++){
			if(abs(29-j)*abs(29-j)+abs(12-k)*abs(12-k)==i*i){
				going(j,k);
				printf("#");
			}
		}
	}
}

int weapon(int*stone,int*wlevel,int EXP,int Level,int Stage,int Mode,int ttime,int percento,int sssstone,int wwwlevel,int gotEXP,int gotStone,int EggHealth, int original){
	int y=23,q;
	going(16,y);
	printf("> Enchant");
	going(18,y+2);
	printf("NEXT STAGE");
	while(1){
		int t=keyControl(-1,0,0,0,0,-1,-1,0);
		switch(t){
			case Choose:
				going(16,y);
				printf(" ");
				if(y==23) y+=2;
				else y-=2;
				going(16,y);
				printf(">");
				break;
			case Submit:
				q=y-23;
				break;
			case Quit:
				return Quit;
		}
		if(q==2) return 1;
		else if(t==Submit) break;
	}
	srand(time(NULL)*22);
	going(16,27);
	int p0=(int)(2+(*wlevel-1)*0.7),p=rand()%p0,i;
	int t=(*wlevel)*((*wlevel)+1)/2;
	if(*stone>=t) {
		(*stone)-=t;
		system("cls");
		going(5,3);
		printf("남은 강화석 %d                    성공 확률 %g%%",*stone,(double)100/p0);
		going(5,2);
		printf("무기 레벨 %d",*wlevel);
		weaponDraw(1);
		for(i=0;i<2;i++){
			PlaySound(".\\music\\anvil.wav",NULL,SND_ASYNC);
			wEffect(1,7+i);
			wEffect(1,8+i);
			Sleep(500);
		}
		system("cls");
		if(p==0){
			(*wlevel)++;
			p0=(int)(2+(*wlevel-1)*0.7);
			going(5,3);
			printf("남은 강화석 %d                    성공 확률 %g%%",*stone,(double)100/p0);
			going(5,2);
			printf("무기 레벨 %d",*wlevel);
			weaponDraw(1);
		}
		else{
			going(5,3);
			printf("남은 강화석 %d                    성공 확률 %g%%",*stone,(double)100/p0);
			going(5,2);
			printf("무기 레벨 %d",*wlevel);
			weaponDraw(0);
		}
		for(i=7;i<=10;i++){
			wEffect(1,i);
		}
		if(p==0){
			PlaySound(".\\music\\XP.wav",NULL,SND_ASYNC);
		}
		else {
			PlaySound(".\\music\\anvilB.wav",NULL,SND_ASYNC);
		}
		Count(Stage,Level,EXP,EggHealth,original,Mode,*stone,*wlevel,gotEXP,gotStone,percento,ttime);
	}
	else {
		printf("강화석이 %d개 부족합니다.",t-*stone); 
	}
	weapon(stone,wlevel,EXP,Level,Stage,Mode,ttime,percento,sssstone,wwwlevel,gotEXP,gotStone,EggHealth,original);
}

int desc(const void *a,const void *b){
	if(*(int*)a<*(int*)b){
		return 1;
	}
	else if(*(int*)a>*(int*)b){
		return -1;
	}
	else return 0;
}
int Bag(int sch){
	int oops=0,timel;
	system("cls");
	system("mode con cols=60 lines=400 | title 알 까기-가방");
	int i=0,ch=0,c=1,n;
	int x=10,y=5;
	going(7,5);
	printf(">");
	while(i<=iid && sch>=0){
		going(10,5+c-1);
		if(item[i]==0) printf("%d. 수박바\n",c++,ch++);
		if(item[i]==1) printf("%d. 계시래모\n",c++,ch++);
		if(item[i]==2) printf("%d. 돌 먹은 눈사람\n",c++,ch++);
		if(item[i]==3) printf("%d. 네모네모\n",c++,ch++);
		i++;
	}
	
	if(ch==0) {
		going(10,5); 
		printf("아무것도 없습니다.");
	}
	going(10,5+c+1);
	printf("돌아가려면 '='을 누르세요."); 

	while(1){
		n=keyControl(-1,0,0,0,0,-1,0,0);
		while(kbhit()==1) getch();
		switch(n){
			case Choose: {
				going(x-3,y);
				printf(" ");
				if(y<5+c-2){
					going(x-3,++y);
					printf(">");
				}
				else if(y==5+c-2){
					going(x-3,y-=c-2);
					printf(">");
				}
				break;
			}
			case Submit: {
				int u=y-5;
				u=item[u];
				if(u!=0 || (u==0 && (sch==1 || sch==2))){
					item[y-5]=-1;
					qsort(item,100,4,desc);
					Fiid();
					return u;
				}
				else {
					oops=1;
					break;
				}
			}
			case Quit: {
				going(10,5);
				printf("                                "); 
				return -1;
				break;
			}
			case 113:{
				item[y-5]=-1;
				qsort(item,100,4,desc);
				Fiid();
				break;
			}
		}
		if(n==113) break;
		if(oops==1){
			going(10,5+c+3);
			printf("지금은 사용 못해요 ㅜㅜ");
			timel=clock()+CLOCKS_PER_SEC;
			oops=0;
		}
		if(timel-clock()<=0 && sch>=0) {
			going(10,5+c+3);
			printf("                                ");
		}
	}
	if(n==113) Bag(-1);
}

void Fiid(){
	int i=0;
	while(1){
		if(item[i]==-1) break;
		i++;
	}
	iid=i-1;
}

int startGame(int Level,int Stage,int EXP,int Mode,int ttime,int percento,int EggHealth,int original,int stone,int wlevel,int gotEXP,int gotStone){
	system("cls");
	srand(time(NULL)*234);
	if(EggHealth==1 && Mode>=0) EggHealth=(rand()%(100*wlevel*wlevel))+50*wlevel*wlevel;
	if(!original) original=EggHealth;
	
	int atk=0,music=0,mungtung=1,sch,ich[100],ic=0;
	int TimeLimit=clock()+10*CLOCKS_PER_SEC,tl,qwerty=1;
	memset(ich,-1,100);
	
	if(Stage==0) sch=-1;
	else if(Stage%3==0) sch=1;
	else if(Stage%5==0) sch=2;
	else if(Stage%7==0) sch=3;
	else sch=0;
	
	if(Mode==-2 && EggHealth==1) {
		EggHealth=9999999;
		original=9999999;
		Stage--;
	}
	if(Mode==0 && !original) {
		EggHealth*=5;
		original=EggHealth;
	}
	if(Mode>=2 && EggHealth==original){
		if(sch==2) EggHealth/=5;
		else if(sch==1) EggHealth/=2;
	}
	if(Mode==2 && sch==3){
		EggHealth=9999999;
		going(10,5);
		printf("Special Stage");
	}
	if(EggHealth>0){
		if(Mode==-2){
			PatientEgg();
			going(10,3);
			printf("Egg Health: %d",EggHealth);
		}
		else{
			going(10,2);
			printf("Stage %d",Stage++);		
			going(10,3);
			printf("Egg Health: %d",EggHealth);
			titleDraw();
 			if(ectDraw(Level,atk,EXP,Mode,ttime,stone,wlevel,Stage)==Quit && Mode==4) return Quit;
		}	
		Count(Stage-1,Level,EXP,EggHealth,original,Mode,stone,wlevel,gotEXP,gotStone,percento,ttime);
	}	
	
	while(1 && EggHealth>0){
		checker=1;
		
		if(sch==2 && Mode>=2) {
			qwerty=0;
			atk=keyControl(Stage-1,wlevel,makingProblem(),EggHealth,ich,Mode,ttime,&ic);
		}
		else if(sch==1 && Mode){
			qwerty=0;
			char eng=rand()%26+65;
			while(eng=='q'){
				eng=rand()%26+65;
			}
			if(rand()%2) eng+=32;
			atk=keyControl(Stage-1,wlevel,eng,EggHealth,ich,Mode,ttime,&ic);
		}
		else {
			if(sch!=3) atk=keyControl(Stage-1,wlevel,0,EggHealth,ich,Mode,ttime,&ic);
			else if(sch==3 && Mode!=-2) atk=keyControl(Stage-1,wlevel,0,EggHealth,ich,Mode,TimeLimit,&ic);
		}
		if(atk==1 && sch==3) break;
		if(atk==-1) return 0;
		int i=0;
		for(i=0;i<=ic;i++){
			if(ich[i]==2) atk*=2;
			if(ich[i]==3) {
				percento/=2;
				ich[i]=-1;
			}
		}
		
		if(sch==3 && Mode==2){
			atk*=10;
			EggHealth=9999999+10*atk;
			EXP+=rand()%(10*Level);
			int Limit=50*Level*(Level+1)/2;
			if(EXP>=Limit) {
				EXP-=Limit;
				Level++;
			}
		}
		
		if(Mode!=-2 && ectDraw(Level,atk,EXP,Mode,ttime,stone,wlevel,Stage)==Quit && Mode==4) return Quit;
		
		while(kbhit()==1) getch(); 
		if(clock()-tl>=0 && qwerty && Mode!=-2){
			going(22,23);
			printf("                                  ");
		} 
		if(rand()%10==0 && atk>0 && Mode!=-2) {
			atk=Critical(atk);
			tl=clock()+400;
		}
		
		EggHealth-=atk;
		if(EggHealth<=0) break;
		
		going(10,3);
		printf("                                   ");
		going(10,3);
		if(sch==3 && Mode==2) printf("Egg Health: %d",9999999);
		else printf("Egg Health: %d",EggHealth);
		
		if(Mode>=0) titleDraw();
		if(Mode==2 && sch==3 && timecheck(TimeLimit, Stage-1,Mode)) break;
		if(Mode!=-2) music=Broken(EggHealth,original,music,Stage-1,atk,Level);
		else PBroken(EggHealth,original);
		
		if(atk>0) {
			Count(Stage-1,Level,EXP,EggHealth,original,Mode,stone,wlevel,gotEXP,gotStone,percento,ttime);
			PlaySound(".\\music\\Touch.wav", NULL, SND_ASYNC | SND_FILENAME|SND_NOSTOP);
		}
	}
	
	if(Mode==-2) {
		wow();
		while(kbhit()==1) getch();
		return 100;
	}  
	
	if(gotStone==0) gotStone=inchentStone(&stone,Level);
	if(gotEXP==0) {
		gotEXP=(rand()%(10*(Stage/5+1)))+10*(Stage/5+1)+1;
		EXP+=gotEXP;
	}
	
	Count(Stage-1,Level,EXP,EggHealth,original,Mode,stone,wlevel,gotEXP,gotStone,percento,ttime);
	int p=printOverview(Stage,Level,gotEXP,EXP,percento,Mode,ttime,stone,wlevel,gotStone,EggHealth,original);
	if(p==1) return 0;
}

void wow(){
	going(13,12);
	printf("Your Name will appear in main");
	going(24,13);
	printf("Thanks!");
	going(18,14);
	printf("     press ENTER\n");
	while(1){
		if(keyControl(1,0,0,0,0,-1,-1,0) ==Submit){
			break;
		}
	}
}

void PatientEgg(){
	going(0,5);
 printf("                       ********                          \n");
 printf("                   *****......*****                      \n");
 printf("                 **:..............:**.                   \n");
 printf("               **....................**.                 \n");
 printf("             **........................**                \n");
 printf("            *::.:........................**              \n");
 printf("           *.:............................**             \n");
 printf("          *...:::..........................**            \n");
 printf("         * .. ... ..........................**           \n");
 printf("        *....................................**          \n");
 printf("       **. .................................:.**         \n");   
 printf("       *. ..................................::.*         \n");
 printf("      *:. ...................................:.**        \n");
 printf("      *.  ...................................::.*        \n"); //18,8
 printf("     **.  ...................................::.*        \n"); //19
 printf("     **.  ..................................:::.*        \n"); //20
 printf("     **.  ..................................:::.*        \n"); //21
 printf("     **.  ..................................:::.*        \n"); //22
 printf("      *.. .................................::::.*        \n");
 printf("      *..  ..............................:.::::*         \n");
 printf("      **.. .............................::.:::.*         \n");
 printf("       **..............................:::.:::.*         \n");
 printf("        **............................::.::::.*          \n");
 printf("          **........................:::.::::.*           \n");
 printf("           **:..................::::::.::::.*            \n");
 printf("             ***.::::::::::::::::::::..::.**             \n");
 printf("               ****::.::::::::::::..:::***               \n");
 printf("                  *****::::::::******                    \n");
 printf("                       **********                        \n");
}

void PBroken(int EggHealth,int original){
	int temp=original-EggHealth;
	int div=original/48;
	int mun=temp/div,i=mun/7;
	
	if(mun%7==0 && mun!=0) mun++;
	if(mun%7==1) going(7+i*6,18);
	if(mun%7==2) going(8+i*6,19);
	if(mun%7==3) going(9+i*6,20);
	if(mun%7==4) going(10+i*6,21);
	if(mun%7==5) going(11+i*6,20);
	if(mun%7==6) going(12+i*6,19);
	if(mun%7!=0) printf("#");
}


void Count(int stage,int Level,int EXP,int EggHealth,int original,int Mode,int stone,int wlevel,int gotEXP,int gotStone,int percento,int ttime){
	char touch[10]={};
	FILE *fp1;
	if(Mode==-2) fp1=fopen(".\\save\\Mode 1.txt","r");
	if(Mode==0) fp1=fopen(".\\save\\Mode 2.txt","r");
	if(Mode==2) fp1=fopen(".\\save\\Mode 3.txt","r");
	if(Mode==4) fp1=fopen(".\\save\\Mode 4.txt","r");
	fscanf(fp1,"%s",touch);
	fclose(fp1);
	
	int touch1=atoi(touch);
	touch1++;
	
	FILE *fp;
	if(Mode==-2) fp=fopen(".\\save\\Mode 1.txt","w");
	if(Mode==0) fp=fopen(".\\save\\Mode 2.txt","w");
	if(Mode==2) fp=fopen(".\\save\\Mode 3.txt","w");
	if(Mode==4) fp=fopen(".\\save\\Mode 4.txt","w");
	
	fprintf(fp,"%d     \n",touch1);
	fprintf(fp,"%d     \n",stage);
	fprintf(fp,"%d     \n",Level);
	fprintf(fp,"%d     \n",EXP);
	fprintf(fp,"%d     \n",EggHealth);
	fprintf(fp,"%d     \n",original);
	fprintf(fp,"%d     \n",stone);
	fprintf(fp,"%d     \n",wlevel);
	fprintf(fp,"%d     \n",gotEXP);
	fprintf(fp,"%d     \n",gotStone);
	fprintf(fp,"%d     \n",percento);
	fprintf(fp,"%d     \n",iid); 
	fclose(fp);
	if(Mode<=0) return 0;
	FILE *f;
	if(Mode==2) f=fopen(".\\save\\Item 1.txt","w");
	if(Mode==4) f=fopen(".\\save\\Item 2.txt","w");
	int i=0;
	for(i=0;i<iid;i++){
		fprintf(f,"%d\n",item[i]);
	}
	fclose(f);
	if(Mode==2) f=fopen(".\\save\\Ban 1.txt","w");
	if(Mode==4) f=fopen(".\\save\\Ban 2.txt","w");
	for(i=0;i<100;i++){
		fprintf(f,"%d\n",ban[i]);
	}
	fclose(f);
}

int ectDraw(int Level, int Attack,int EXP,int Mode,int ttime,int stone,int wlevel,int stage){
	going(5,19);
	printf("Level %d",Level);
	going(5,20);
	printf("EXP ");
	int Limit=50*Level*(Level+1)/2,i,j;
	for(i=0;i<EXP/(Limit/10);i++){
		printf("■");
	}
	for(j=0;j<10-i;j++){
		printf("□");
	}
	going(5,21);
	printf("                          ");
	going(5,21);
	printf("Attack %d",Attack);
	going(5,22);
	printf("강화석 %d",stone);
	going(15,22);
	printf("무기 레벨 %d",wlevel);
	going(10,2);
	printf("Stage %d",stage-1);
	if(Mode==4) {
		if(timecheck(ttime,-1,Mode)==-1) return Quit;
	}
	return 0;
}

 
int Broken(int EggHealth,int original,int music,int Stage,int atk,int Level){
	int temp=original-EggHealth;
	int div=original/8;
	int mun=temp/div,a;
	
	if(music!=mun && Stage%3!=0 && Stage%5!=0 && atk==Level*2) PlaySound(".\\music\\Broken.wav", NULL, SND_ASYNC);
	switch(mun){
		case 8:{
			going(7,14);
			printf("               **      *  **	     \n");
		}
		case 7:{
			going(7,13);
			printf("              **  *     *  **      \n");
		}
		case 6:{
			going(7,12);
			printf("             **   **   *    **     \n"); 
		}
		case 5:{
			going(7,11);
			printf("             **     *  *    **     \n");  
		}
		case 4:{
			going(7,10);
			printf("              **     **    **      \n");
		}
		case 3:{
			going(7,9);
			printf("               **    *    **       \n");
		}
		case 2:{
			going(7,8);
			printf("                **    *  **        \n");
		}
		case 1:{
			going(7,7);
			printf("                 **  *  **         \n");
		}
	}
	return mun;
}

int printOverview(int Stage,int Level,int gotEXP,int EXP,int percento,int Mode,int ttime,int stone,int wlevel,int tont,int EggHealth,int original){
	system("cls");
	srand(time(NULL)*12);
	
	printf("\n\n");
	printf("          Stage %d\n\n",Stage-1);
	printf("          +EXP %d       +강화석 %d\n\n",gotEXP,tont);
	printf("          현재 강화석: %d\n\n",stone);

	if((rand()%percento>=0 && Mode) || (checker==0 && Mode)) {
		int y=item[iid];
		if(checker){
			do{
				y=rand()%4;
			}while(ban[y]==-1);
			if(y==3){
				ban[y]=-1;
			}
			item[++iid]=y;
			qsort(item,100,4,desc);
			Fiid();
		}
		if(item[iid]!=-1) printf("          아이템 얻음!!\n\n");
		ItemDraw(y);
	}
	Count(Stage-1,Level,EXP,EggHealth,original,Mode,stone,wlevel,gotEXP,tont,percento,ttime);
	int p=changeLevel(EXP,Level,Stage,Mode,ttime,percento,stone,wlevel,gotEXP,tont,EggHealth,original);
	if(p==0) return 1;
	else return 0;
}

int changeLevel(int EXP,int Level,int Stage,int Mode,int ttime,int percento,int stone,int wlevel,int gotEXP,int gotStone,int EggHealth, int original){
	int Limit=50*Level*(Level+1)/2,y;
	if(EXP>=Limit) {
		EXP-=Limit;
		Level++;
		printf("          Level Up  %d --> %d\n\n",Level-1,Level);
		PlaySound(".\\music\\Level Up.wav", NULL, SND_ASYNC | SND_ALIAS);
	}
	else printf("          %d EXP left for next Level\n\n",Limit-EXP);
	
	y=weapon(&stone,&wlevel,EXP,Level,Stage,Mode,ttime,percento,stone,wlevel,gotEXP,gotStone,EggHealth,original);
	if(y==Quit) return 0;
		
	if(!y){
		going(15,10);
		printf("press ENTER");
		while(1){
			if(Mode==4) {
				int y=timecheck(ttime,Stage,Mode);
				Count(Stage-1,Level,EXP,EggHealth,original,Mode,stone,wlevel,gotEXP,gotStone,percento,ttime);
				if(y==-1) return 0;
			}
			int p=keyControl(1,0,0,0,0,-1,-1,0);
			if(p==Submit) break;
		}	
	}
	
	startGame(Level,Stage,EXP,Mode,ttime,percento,1,0,stone,wlevel,0,0);
	return 1;
}


int makingProblem(){
	srand(time(NULL));
	int percent=rand()%6;
	
	going(8,16);
	printf("                                        ");  
	going(8,17);
	printf("                                        ");
	going(8,16);
	
	if(percent==0) {
		int a=rand()%50+1,b=rand()%25+1;
		printf("             x - %d = %d",a,b);
		return a+b;
	}
	if(percent==1) {
		long long int a=rand()%3+2,b=rand()%4+1,c=pow(a,b);
		printf("             log %d to %d",a,c);
		return b;
	}
	if(percent==2) {
		int a=rand()%10+1,b=rand()%20+1;
		printf("       기울기를 구하시오 y = %dx + %d",a,b);
		return a;
	}
	if(percent==3) {
		int a=rand()%5+1,b=rand()%10*a+a;
		printf("         x 절편은? y = %dx + %d",a,b);
		return -b/a;  
	}
	if(percent==4){
		int a=rand()%4+1,b=rand()%4+1;
		if(rand()%2) a=-a;
		if(rand()%2) b=-b;
		if(a>0 && b>0) printf("     작은 근을 구하시오 x^2-%d*x+%d=0",a+b,a*b);
		else if(a+b<0 && a*b>0) printf("     작은 근을 구하시오 at x^2+%d*x+%d=0",-(a+b),a*b);
		else if(a+b>0 && a*b<0) printf("     작은 근을 구하시오 at x^2-%d*x-%d=0",a+b,-a*b);
		else printf("     작은 근을 구하시오 at x^2+%dx-%d=0",-(a+b),-a*b);
		if(a>b) return b;
		else return a;
	}

	if(percent==5){
		int a=rand()%5+1,b=rand()%a;
		printf("    조합을 계산하라 ( %d )",a);
		going(8,17);
		printf("                    ( %d )",b);
		return combi(a,b);
	}
}

int combi(int a,int b){
	if(b==0||b==a) return 1;
	if(b==1||b==a-1) return a;
	return combi(a-1,b-1)+combi(a-1,b);
}

void ItemDraw(int tem){
	printf("\n");
	if(tem==0){
		printf("           **    \n");
        printf("          *  *   \n");
        printf("         *    *    문제 하나를 그냥 맞게 해줌\n");
		printf("        ******** \n"); 
		printf("           **    \n");
		printf("           **    \n");
		printf("         수박바  \n");
	}
	else if(tem==1){
		printf("          *****   \n");
        printf("           * *    \n"); 
        printf("            *     달걀의 체력/2\n");
        printf("           * *    \n");
        printf("          *****   \n");
        printf("         계시래모 \n");
	}
	else if(tem==2){
		printf("            ***      \n");
        printf("           *   *     \n");
        printf("            * *      \n");
        printf("           *   *     한 스테이지 동안 공격력 *2\n"); 
        printf("          *     *    \n");
        printf("           *   *     \n");
        printf("       돌 먹은 눈사람\n");
	}
	else if(tem==3){
		printf("           *****    \n");
        printf("           *   *    아이템 나올 확률*2(영구)\n"); 
        printf("           *****    \n");
        printf("          네모네모  \n"); 
	}
	else return;
	printf("\n");
} 

/*
음원 출처
[1] BGM 
Song : 세상을 뒤바꿀 음악 - 장난감 마을
Follow Artist : https://bit.ly/2Qm2k4R
Music promoted by DayDreamSound : https://youtu.be/sRsSoXLrZns 
*/
