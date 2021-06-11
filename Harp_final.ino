#include <CD74HC4067.h>
int muxChannel[16][4]={ {0,0,0,0},//channel 0 
                          {1,0,0,0},//channel 1 
                          {0,1,0,0},//channel 2 
                          {1,1,0,0},//channel 3 
                          {0,0,1,0},//channel 4 
                          {1,0,1,0},//channel 5 
                          {0,1,1,0},//channel 6 
                          {1,1,1,0},//channel 7 
                          {0,0,0,1},//channel 8
                          {1,0,0,1},//channel 9
                          {0,1,0,1},//channel 10
                          {1,1,0,1},//channel 11
                          {0,0,1,1},//channel 12
                          {1,0,1,1},//channel 13
                          {0,1,1,1},//channel 14
                          {1,1,1,1} //channel 15
                          };
///multi1
int s0[4]={23,22,25,24};

///multi2
int s1[4]={4,5,6,7};

///multi3
int s2[4]={8,9,10,11};

//RGB diod
int anoda=51;
int G=50;
int R=48;
int B=49;

///Analog Signals
int SIG_pin0 = 0;
int SIG_pin1 = 1;
int SIG_pin2 = 2;

///Foot
int foot0 = 38;
int foot1 = 39;

///switch
int on_off = 53;

/////avrage values of multi0
int av_min0[16];
int av0[16];
int av_max0[16];

/////avrage values of multi1
int av_min1[16];
int av1[16];
int av_max1[16];

/////avrage values of multi2
int av_min2[16];
int av2[16];
int av_max2[16];

///memory of active strings
char acti0[16];//m0
char acti1[16];//m1
char acti2[16];//m2
int odchylenie[10];
int elements[15];
void setup() 
{
  
  pinMode(on_off, OUTPUT);
  digitalWrite(on_off, LOW);
  pinMode(foot0, OUTPUT);
  pinMode(foot1,INPUT);
  digitalWrite(foot0,HIGH);
  pinMode(anoda,OUTPUT);
  digitalWrite(anoda,HIGH);
  pinMode(R,OUTPUT);
  digitalWrite(R,LOW);
  pinMode(G,OUTPUT);
  digitalWrite(G,HIGH);
  pinMode(B,OUTPUT);
  digitalWrite(B,HIGH);
  for(int i=0;i<4;i++)
  {
    pinMode(s0[i], OUTPUT);
    digitalWrite(s0[i], LOW);
    pinMode(s1[i], OUTPUT);
    digitalWrite(s1[i], LOW);
    pinMode(s2[i], OUTPUT);
    digitalWrite(s2[i], LOW);
  }
  Serial.begin(9600);
  conf(av_max0, elements, 15, 16,s0,SIG_pin0);
  conf(av_max1, elements, 15, 16,s1,SIG_pin1);
  conf(av_max2, elements, 15, 16,s2,SIG_pin2);
  Serial.println("\nNow turn off the lights");
  digitalWrite(on_off,HIGH);
  Serial.println("Mesurement starts in:");
  for(int i=0;i<5;i++)
  {
   Serial.println(5-i);
   digitalWrite(R, !digitalRead(R));
   delay(1000);
  }
  digitalWrite(R,LOW);
  conf(av_min0, elements, 15, 16,s0,SIG_pin0);
  conf(av_min1, elements, 15, 16,s1,SIG_pin1);
  conf(av_min2, elements, 15, 16,s2,SIG_pin2);
  for(int i=0;i<16;i++)
   {
    av0[i]=(av_max0[i]+av_min0[i])*0.5;
    av1[i]=(av_max1[i]+av_min1[i])*0.5;
    av2[i]=(av_max2[i]+av_min2[i])*0.5;
   }
   
  for(int i=0;i<16;i++)
   {
    acti0[i]='0';
    acti1[i]='0';
    acti2[i]='0';
   }
  digitalWrite(on_off,LOW);
  digitalWrite(R,HIGH);
  digitalWrite(G,LOW);
}

void loop() 
{
    for(int i = 0; i < 16; i ++)
    { 
      int value0=readMux(i,s0, SIG_pin0);
      int value1=readMux(i,s1, SIG_pin1);
      int value2=readMux(i,s2, SIG_pin2);
      ///detection block multi 1
      if(av0[i]<value0 && acti0[i]=='0')
      {
         acti0[i]='1';
         Serial.println(100+i);
      }
      else if(acti0[i]=='1' && av0[i]>value0) acti0[i]='0';
      ///detection block  multi 2
      if(av1[i]<value1 && acti1[i]=='0')
      {
         acti1[i]='1';
         Serial.println(200+i);
      }
      else if(acti1[i]=='1' && av1[i]>value1) acti1[i]='0';
      ///detection block  multi 3
      if(av2[i]<value2 && acti2[i]=='0' && i<11)
      {
         acti2[i]='1';
         Serial.println(300+i);
      }
      else if(acti2[i]=='1' && av2[i]>value2) acti2[i]='0';
    
    } 

}
int readMux(int channel, int controlPin[], int SIG_pin)
{ 
  for(int i = 0; i < 4; i ++) //loop through the 4 sig 
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  int val = analogRead(SIG_pin); //read the value at the SIG pin 
  //delay(2);
  return val; //return the value 
 
} 
void conf(int av[], int elem[], int n, int m,int multi[],int SIG_pin)
{
  for(int j=0;j<m;j++)
  {
    for(int i=0;i<n;i++)
    {
      elem[i]=readMux(j,multi,SIG_pin);
      av[j]=av[j]+elem[i];
      delay(5);
    }
    av[j]=av[j]/n;
    Serial.print("\nAvrage per channel ");Serial.print(j);Serial.print(": ");Serial.print( av[j]); 
  }
  
}
