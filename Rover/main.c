/*******************************************************************************/
#define PA4					(*((volatile unsigned long *)0x40004040))
#define PA3					(*((volatile unsigned long *)0x40004020))
#define SYSCTL_RCGC2_R		(*((volatile unsigned long *)0x400FE108))
#define GPIO_PORTA_DATA_R	(*((volatile unsigned long *)0x400043FC))
#define GPIO_PORTA_DIR_R	(*((volatile unsigned long *)0x40004400))
#define GPIO_PORTA_AFSEL_R	(*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_PUR_R	(*((volatile unsigned long *)0x40004510))
#define GPIO_PORTA_DEN_R	(*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_CR_R		(*((volatile unsigned long *)0x40004524))
#define GPIO_PORTA_AMSEL_R	(*((volatile unsigned long *)0x40004528))
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define GPIO_PORTD_DATA_R	(*((volatile unsigned long *)0x400073FC))
#define GPIO_PORTD_DIR_R	(*((volatile unsigned long *)0x40007400))
#define GPIO_PORTD_AFSEL_R	(*((volatile unsigned long *)0x40007420))
#define GPIO_PORTD_PUR_R	(*((volatile unsigned long *)0x40007510))
#define GPIO_PORTD_DEN_R	(*((volatile unsigned long *)0x4000751C))
#define GPIO_PORTD_CR_R		(*((volatile unsigned long *)0x40007524))
#define GPIO_PORTD_AMSEL_R	(*((volatile unsigned long *)0x40007528))
/********************************************************************/
#define GPIO_PORTF_DATA_R	(*((volatile unsigned long *)0x400253FC))
#define	GPIO_PORTF_DIR_R	(*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R	(*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R	(*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R	(*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_CR_R		(*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R	(*((volatile unsigned long *)0x40025528))
/********************************************************************/
#define GPIO_PORTA_PCTL_R	(*((volatile unsigned long *)0x4000452C))
#define GPIO_PORTD_PCTL_R	(*((volatile unsigned long *)0x4000752C))
#define GPIO_PORTF_PCTL_R	(*((volatile unsigned long *)0x4002552C))
#define GPIO_PORTD_LOCK_R	(*((volatile unsigned long *)0x40007520))
#define GPIO_PORTF_LOCK_R	(*((volatile unsigned long *)0x40025520))
/*******************************************************************/
#define NVIC_ST_CTRL_R		(*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R	(*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R	(*((volatile unsigned long *)0xE000E018))
/*******************************************************************/
#define SYSCTL_RCC2_R		(*((volatile unsigned long *)0x400FE070))
#define	SYSCTL_RIS_R		(*((volatile unsigned long *)0x400FE050))
#define SYSCTL_RCC_R		(*((volatile unsigned long *)0x400FE060))
/*******************************************************************************/
#define T_S0	0
#define T_S1	0
#define T_S2 	0
#define T_S3 	0
#define T_S4 	0
#define T_S5 	0
#define T_S6 	0
#define n_p   100
#define T_t   2000
#define T_mt	4000
/******************************************************************************/
void Init_PORTA(void);
void Init_PORTD(void);
void Init_PORTF(void);
void PLL_Init_Clock(void);
void SysTick_Init(void);
void SysTick_Wait(unsigned long delay);
/******************************************************************************/
void MRamping(void);
void Foward(void);
void Backward(void);
void Left90(void);
void Right90(void);
void Left45(void);
void Right45(void);
/***********************0*******************************************************/
void delay(unsigned long msecs);  // Delay
/******************************************************************************/
struct State{
	void (*CmdPt)(void);
	unsigned long Time;
	unsigned long Next[32];
};
struct ServState{
	unsigned long flag;
	unsigned long duty;
	unsigned long Next[4];
};
/******************************************************************************/
typedef const struct State StateType;
typedef const struct ServState ServStateType;
StateType FSM[7]={
//                   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
  {&MRamping, T_S0, {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6}}, //
  {&Left45,   T_S1, {6,0,0,0,1,4,5,2,0,0,0,0,4,4,2,2,0,0,0,0,4,4,1,1,0,0,0,0,4,4,5,3}}, //
  {&Left90,   T_S2, {6,0,0,0,1,4,5,2,0,0,0,0,4,4,2,2,0,0,0,0,4,4,1,1,0,0,0,0,4,4,5,3}}, //
  {&Backward, T_S3, {1,2,4,5,1,2,4,5,1,2,3,4,5,1,2,3,4,5,1,2,4,5,1,2,4,5,1,2,4,5,1,3}}, //
  {&Right45,  T_S4, {6,0,0,0,1,4,5,2,0,0,0,0,4,4,2,2,0,0,0,0,4,4,1,1,0,0,0,0,4,4,5,3}}, //
  {&Right90,  T_S5, {6,0,0,0,1,4,5,2,0,0,0,0,4,4,2,2,0,0,0,0,4,4,1,1,0,0,0,0,4,4,5,3}},	//
  {&Foward,   T_S6, {6,6,6,6,1,4,5,2,6,6,6,6,4,4,2,2,6,6,6,6,4,4,1,1,6,6,6,6,4,4,5,3}}  //
};   //

ServStateType ServFSM[5]={
	{0, 40000, {0,0,1,0}},
	{1, 60000, {1,1,2,0}},
	{1,100000, {2,2,3,1}},
	{1,145000, {3,3,4,2}},
	{0,180000, {4,4,4,3}}
};

/*******************************************************************************/
unsigned long S=0; //
volatile unsigned long Sensor=0; // Servo Reading
volatile unsigned long RSensor=0;
volatile unsigned long RSensorTmp=0;
/******************************************/
unsigned long SCtrl=0;
unsigned long ServTimeCnt=101;
unsigned long dir=00;
unsigned long Sflag=0x02;
unsigned long SServ=0;


int main(void){
  PLL_Init_Clock();
	SysTick_Init();
	S =0;       // Initial State
	Init_PORTA();
	Init_PORTD();
	Init_PORTF();
 // delay(1000);
  while(1){

	(FSM[S].CmdPt)();
	if(ServFSM[SServ].flag==1 && S==6)
		{Sensor=RSensor;
		}
 	S = FSM[S].Next[Sensor];

	if(S!=0){
			if(ServTimeCnt>=50){
				RSensorTmp=PA3>>3;
				RSensor=RSensor|(RSensorTmp<<SServ);
				Sflag=0x02;
				NVIC_ST_RELOAD_R = (ServFSM[SServ].duty)-1 ;
				NVIC_ST_CURRENT_R = 0;
				if(SServ==0){
					dir=0x00;
				}
				else if (SServ==4){
					dir=0x01;
				}
				SCtrl=Sflag|dir;
				SServ=ServFSM[SServ].Next[SCtrl];
				ServTimeCnt=0;
				PA4=0x10;
			}
			else{
				Sflag=0x00;
				if ((NVIC_ST_CTRL_R&0x00010000)!=0){
					if((ServTimeCnt&0x01)==1){
						NVIC_ST_RELOAD_R = (ServFSM[SServ].duty)-1;
						NVIC_ST_CURRENT_R = 0;  
						PA4=0x10;
					}
					else if((ServTimeCnt&0x01)==0){
						NVIC_ST_RELOAD_R = (1600000-ServFSM[SServ].duty)-1 ;
						NVIC_ST_CURRENT_R = 0;
						PA4=0x00;
					}
				ServTimeCnt++;
				}
		}

		}
  }
}

/********************************************************************/
void MRamping(void){
		unsigned long npulses=50;
		unsigned long dutypul=0;
		PA4=0x00;
		GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R&(~(0x1C));
		GPIO_PORTA_DATA_R=GPIO_PORTA_DATA_R&(~(0x04));
		GPIO_PORTD_DATA_R=GPIO_PORTD_DATA_R&(~(0xC0));
		GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R|(0x1C);
		GPIO_PORTA_DATA_R=GPIO_PORTA_DATA_R|(0x00);
		GPIO_PORTD_DATA_R=GPIO_PORTD_DATA_R|(0x80);
		while(npulses>dutypul){
			GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R&(~(0x0C));
			delay(npulses-dutypul);
			GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R|(0x0C);
			delay(dutypul);
			dutypul++;
		}
}
void Foward(void){
		GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R&(~(0x1C));
		//delay(50);
		GPIO_PORTA_DATA_R=GPIO_PORTA_DATA_R&(~(0x04));
		GPIO_PORTD_DATA_R=GPIO_PORTD_DATA_R&(~(0xC0));

		GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R|(0x1C);
		GPIO_PORTA_DATA_R=GPIO_PORTA_DATA_R|(0x00);
		GPIO_PORTD_DATA_R=GPIO_PORTD_DATA_R|(0x80);
		//delay(1500);


}
void Backward(void){
		unsigned long cnt=0;
		GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R&(~(0x1C));
		while(cnt<n_p)
		{
			PA4=0x10;
			SysTick_Wait( 100000);
			PA4=0x00;
		  SysTick_Wait(1500000);
			cnt++;
		}
		delay(150);
		GPIO_PORTA_DATA_R=GPIO_PORTA_DATA_R&(~(0x04));
		GPIO_PORTD_DATA_R=GPIO_PORTD_DATA_R&(~(0xC0));
		GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R|(0x0C);
		GPIO_PORTA_DATA_R=GPIO_PORTA_DATA_R|(0x04);
		GPIO_PORTD_DATA_R=GPIO_PORTD_DATA_R|(0x40);
		delay(5000);
		Sensor=0;
		RSensor=0;
		SServ=0;
		GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R&(~(0x0C));
		delay(1000);
}
void Right90(void){
		unsigned long cnt=0;
		GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R&(~(0x1C));
		while(cnt<n_p)
		{
			PA4=0x10;
			SysTick_Wait( 100000);
			PA4=0x00;
		  SysTick_Wait(1500000);
			cnt++;
		}

		delay(250);
		GPIO_PORTA_DATA_R=GPIO_PORTA_DATA_R&(~(0x04));
		GPIO_PORTD_DATA_R=GPIO_PORTD_DATA_R&(~(0xC0));

		GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R|(0x1C);
		GPIO_PORTA_DATA_R=GPIO_PORTA_DATA_R|(0x00);
		GPIO_PORTD_DATA_R=GPIO_PORTD_DATA_R|(0x40);
		delay(5000);
		GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R&(~(0x0C));
		Sensor=0;
		RSensor=0;
		SServ=0;
		RSensorTmp=0;
		delay(1000);
}
void Left90(void){
		unsigned long cnt=0;
		GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R&(~(0x1C));
		while(cnt<n_p)
		{
			PA4=0x10;
			SysTick_Wait( 100000);
			PA4=0x00;
		  SysTick_Wait(1500000);
			cnt++;
		}

		delay(250);
		GPIO_PORTA_DATA_R=GPIO_PORTA_DATA_R&(~(0x04));
		GPIO_PORTD_DATA_R=GPIO_PORTD_DATA_R&(~(0xC0));

		GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R|(0x0C);
		GPIO_PORTA_DATA_R=GPIO_PORTA_DATA_R|(0x04);
		GPIO_PORTD_DATA_R=GPIO_PORTD_DATA_R|(0x80);
		delay(5000);
		GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R&(~(0x0C));
		Sensor=0;
		RSensor=0;
		SServ=0;
		RSensorTmp=0;
		delay(1000);
}
void Right45(void){
		unsigned long cnt=0;
		GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R&(~(0x1C));
		while(cnt<n_p)
		{
			PA4=0x10;
			SysTick_Wait( 100000);
			PA4=0x00;
		  SysTick_Wait(1500000);
			cnt++;
		}
		delay(150);
		GPIO_PORTA_DATA_R=GPIO_PORTA_DATA_R&(~(0x04));
		GPIO_PORTD_DATA_R=GPIO_PORTD_DATA_R&(~(0xC0));

		GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R|(0x1C);
		GPIO_PORTA_DATA_R=GPIO_PORTA_DATA_R|(0x00);
		GPIO_PORTD_DATA_R=GPIO_PORTD_DATA_R|(0x40);
		delay(2500);
		GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R&(~(0x0C));
		Sensor=0;
		RSensor=0;
		SServ=0;
		RSensorTmp=0;
		delay(1000);
}
void Left45(void){
		unsigned long cnt=0;
		GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R&(~(0x1C));
		while(cnt<n_p)
		{
			PA4=0x10;
			SysTick_Wait( 100000);
			PA4=0x00;
		  SysTick_Wait(1500000);
			cnt++;
		}
		delay(150);
		GPIO_PORTA_DATA_R=GPIO_PORTA_DATA_R&(~(0x04));
		GPIO_PORTD_DATA_R=GPIO_PORTD_DATA_R&(~(0xC0));

		GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R|(0x1C);
		GPIO_PORTA_DATA_R=GPIO_PORTA_DATA_R|(0x00);
		GPIO_PORTD_DATA_R=GPIO_PORTD_DATA_R|(0x40);
		delay(2500);
		GPIO_PORTF_DATA_R=GPIO_PORTF_DATA_R&(~(0x0C));
		Sensor=0;
		RSensor=0;
		RSensorTmp=0;
		SServ=0;
		delay(1000);
}
/*******************************************************************/
void delay(unsigned long msecs){
  unsigned long count;
  while(msecs > 0 ) {
    count = 4000; //4000 is set to wait 1ms
    while (count > 0) {
      count--;
    }
    msecs--;
  }
}

/*******************************************************************/
void Init_PORTA(void){
	volatile unsigned long delay=0;
	SYSCTL_RCGC2_R=SYSCTL_RCGC2_R|0x01;
	delay=SYSCTL_RCGC2_R;
	GPIO_PORTA_AMSEL_R = 0x00;
	GPIO_PORTA_PCTL_R = 0x00000000;
	GPIO_PORTA_DIR_R = 0x14;
	GPIO_PORTA_AFSEL_R = 0x00;
	GPIO_PORTA_PUR_R = 0x00;
	GPIO_PORTA_DEN_R = 0xFF;
}

void Init_PORTD(void){
	volatile unsigned long delay=0;
	SYSCTL_RCGC2_R=SYSCTL_RCGC2_R|0x08;
	delay=SYSCTL_RCGC2_R;
	GPIO_PORTD_LOCK_R = 0x4C4F434B;
	GPIO_PORTD_CR_R = 0xFF;
	GPIO_PORTD_AMSEL_R = 0x00;
	GPIO_PORTD_PCTL_R = 0x00000000;
	GPIO_PORTD_DIR_R = 0xC0;
	GPIO_PORTD_AFSEL_R = 0x00;
	GPIO_PORTD_PUR_R = 0x00;
	GPIO_PORTD_DEN_R = 0xFF;
}

void Init_PORTF(void){
	volatile unsigned long delay=0;
	SYSCTL_RCGC2_R=SYSCTL_RCGC2_R|0x20;
	delay=SYSCTL_RCGC2_R;
	GPIO_PORTF_LOCK_R = 0x4C4F434B;
	GPIO_PORTF_CR_R = 0x1F;
	GPIO_PORTF_AMSEL_R = 0x00;
	GPIO_PORTF_PCTL_R = 0x00000000;
	GPIO_PORTF_DIR_R = 0x1C;
	GPIO_PORTF_AFSEL_R = 0x00;
	GPIO_PORTF_PUR_R = 0x00;
	GPIO_PORTF_DEN_R = 0xFF;
}

void SysTick_Init(void){
  NVIC_ST_CTRL_R = 0;               
  NVIC_ST_CTRL_R = 0x00000005;      
}

void SysTick_Wait(unsigned long delay){
  NVIC_ST_RELOAD_R = delay-1;  
  NVIC_ST_CURRENT_R = 0;      
  while((NVIC_ST_CTRL_R&0x00010000)==0){
  }
}

void PLL_Init_Clock(void){
  SYSCTL_RCC2_R |=  0x80000000;  
  SYSCTL_RCC2_R |=  0x00000800; 
  SYSCTL_RCC_R = (SYSCTL_RCC_R &~0x000007C0)+ 0x00000540;   // 10101, configure for 16 MHz crystal
  SYSCTL_RCC2_R &= ~0x00000070; 
  SYSCTL_RCC2_R &= ~0x00002000;
  SYSCTL_RCC2_R |= 0x40000000;   // use 400 MHz PLL
  SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~ 0x1FC00000) + (4<<22);      // configure for 80 MHz clock
  while((SYSCTL_RIS_R&0x00000040)==0){};  // wait for PLLRIS bit
  // 6) enable use of PLL by clearing BYPASS
  SYSCTL_RCC2_R &= ~0x00000800;
}
