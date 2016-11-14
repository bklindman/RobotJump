# include  "acllib.h"

# include <time.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>



int x = 400;
int y = 600;
int t=0;
int a[100],b[100][100];
int n=60,m=80;
int i,j,l=0;
int k=0;

ACL_Image img;
ACL_Sound sound;
#define KEY_E 18


void begingame();
void paint();



void paint()
{
	float p;
	int q,i1,j1;
    beginPaint();

    clearDevice();
	setBrushColor(BLUE);
	if (t<=10) {p=20*t-1*t*t; k=0;}
	 else {p=100-1*(t-10)*(t-10);l=0;}
	rectangle(x-10,y-p-10,x+10,y-p+10);

	setBrushColor(RED);
	  for (i=1;i<=n+10;i=i+1)
	{
	  for (j=1;j<=a[i];j++)
	   roundrect(b[i][j]*10-30,(i-10)*10+p*l-5,b[i][j]*10+30,(i-10)*10+p*l+5,5,10);
	}

	
	if (t==10 && l==1) {
		               
							for (i=70;i>=11;i--)
							{a[i]=a[i-10];
							for (j=1;j<=a[i];j++)
							  b[i][j]=b[i-10][j];}
						for (i=1;i<=10;i=i+2)
						{ a[i]=1+(int)(rand()%1);
		                    for (j=1;j<=a[i];j++)
			                  b[i][j]=1+(int)(rand()%80);
						}
						l=0;
	                   }


	 if (t-10>=0)  {
            q=(y-p+14)/10+10;
			for (j=1;j<=a[q];j++)
				if ((x>=b[q][j]*10-30) && (x<=b[q][j]*10+30)) {t=0;
					                                     y=y-p;
														 l=1;
					                                 
														 k=1;
				                                         break;}
			q=(y-p+16)/10+10;
			for (j=1;j<=a[q];j++)
				if ((x>=b[q][j]*10-30) && (x<=b[q][j]*10+30)) {t=0;
					                                     y=y-p;
														 l=1;
					                                 
														 k=1;
				                                         break;}
			                     
	                              }



	 if ((t==28) && (k==0)) { paintText(400, 300, "The Game Over"); cancelTimer(1); }
	

    endPaint();
}



void TimerEvent(int number)
{
    t=t+1;	
	t=t%30;
	paint();
 
}

void keyboardevent(int key, int event)
{
	if(event!=KEY_DOWN)
        return;
	if(key==VK_SPACE)
	{begingame();cancelTimer(2);}
	else {  
		switch(key)
    {
    case VK_LEFT:
        x-=50;if (x<0) x=800;
        break;
    case VK_RIGHT:
        x+=50;if (x>800) x=0;
        break;
	}
	

}
}

void begingame()
{

    x=400;y=600;
	
	
	srand((int)time(NULL));
	for (i=1;i<=n+10;i=i+2) 
	{
		a[i]=1+(int)(rand()%1);
		for (j=1;j<=a[i];j++)
			b[i][j]=1+(int)(rand()%80);
	}
	a[70]=a[70]+1;
	b[70][a[70]]=400;
	
	
   startTimer(1,32);
}

int Setup()
{
	

	initWindow("image",DEFAULT,DEFAULT,800,600);

	registerTimerEvent(TimerEvent);
	
	loadImage("image.jpg",&img);

	 beginPaint();
    putImageScale(&img,0,0,800,600);
    endPaint();

	loadSound("sound.mp3",&sound);
	playSound(sound,1);
	
	registerKeyboardEvent(keyboardevent);
    return 0;


}