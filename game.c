#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define BLACK 0x0000 		
#define GREEN 0x07E0 	
#define RED 0xF800 	 	
#define WHITE 0xFFFF	
#define LGRAY 0xC618 	
#define NAVY 0x000F 

// Define VGA display dimensions
#define VGA_WIDTH 320
#define VGA_HEIGHT 240
#define HEX3_HEX0_BASE			0xFF200020
#define HEX5_HEX4_BASE			0xFF200030
char seg7[10] =	{0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110,
						 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01100111};

// Define parameters
int foodx;
int foody;
int food = 0;
int score = 0;
int lifes = 10;
volatile int * KEY_ptr       =(volatile int *) 0xFF200050;  
volatile int * LEDR_ptr       = (volatile int *)0xFF200000; 

//-----------------------------------------------------------------------------------------------------------------------
// FUNCTION TO DRAW  EACH PIXEL
void write_pixel(int x, int y, int colour)
{
    volatile short *vga_addr = (volatile int *)(0x08000000 + (y << 10) + (x << 1));
    *vga_addr = colour;
}

//-----------------------------------------------------------------------------------------------------------------------
void draw_frame(){
    for(int i=0;i<320;i+=10){
        for(int j=0;j<240;j++){                             // FUNCTION TO DRAW THE FRAME OF THE  GAME
            write_pixel(i,j,0Xffff);
        }
		
    }
	for(int i=0;i<240;i+=10){
        for(int j=0;j<320;j++){
            write_pixel(j,i,0Xffff);
        }
		
    }
}

//--------------------------------------------------------------------------------------------------------------------------
/* use write_pixel to set entire screen to black (does not clear the character buffer) */
void clear_screen()
{
    int x, y;
    for (x = 0; x < 320; x++)
    {
        for (y = 0; y < 240; y++)
        {
            write_pixel(x, y, 0);
            // if()
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------
// Function to draw a box
void draw_box(int a, int colour, int b, int length, int width)
{
    int x, y;
    for (y = b+1; y < b + length; y++)
    {
        for (x = a+1; x < a + width; x++)
        {
            write_pixel(x, y, colour);
        }
    }
}


//---------------------------------------------------------------------------------------------------------------------------
// FUNCTION TO ERASE THE BOX

void erase_box(int a, int b, int length, int width)
{
    int x, y;
    for (y = b+1; y < b + length; y++)
    {
        for (x = a+1; x < a + width; x++)
        {
            write_pixel(x, y, 0);
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------
// FUNCTION TO CREATE THE FOOD RANDOMLY

void create_food(){
    foodx= rand()%32;
    foody =rand()%24;
    draw_box(foodx*10,RED,foody*10,10,10);
}

//---------------------------------------------------------------------------------------------------------------------------
// FUNCTION TO DRAW SANKE HORIZONTAL

void draw_snake_htl(int a,int b,int s){
	for(int i=0;i<s;i++){
		draw_box(a+10*i,GREEN,b,10,10);
    }
        if((a+(s-1)*10>=foodx*10 && a<=foodx*10) && b==foody*10){
            food=0;
            lifes=10;
            score++;
        }
	
}

//-----------------------------------------------------------------------------------------------------------------------------
// FUNCTION TO DRAW SNAKE VERTICAL

void draw_snake_vert(int a,int b,int s)	{
	for(int j=0;j<s;j++){
		draw_box(a,GREEN,b+j*10,10,10);
    }
        if(a==foodx*10 && (b<=foody*10 && b+(s-1)*10>=foody*10)){
            food=0;
            lifes=10;
            score++;
        }
	
}


//----------------------------------------------------------------------------------------------------------------------------
// FUNCTION TO CHANGE THE DIRECTION DOWN

int change_direction_down(int a,int b){
        int l1=a;
	    int h1=b;
        int i=4;
        while(i!=0){
            draw_snake_htl(a,h1,i);
			draw_snake_vert(l1+40,b,5-i);
            for(int j=0;j<10000000;j++){

            }
            erase_box(a,h1,10,10);
            a=a+10;
			i--;
        }
	return a;
}

//----------------------------------------------------------------------------------------------------------------------------
// FUNCTION TO CHANGE THE DIRECTION TO LEFT

int change_direction_left(int a,int b){
        int l1=a;
	    int h1=b;
        int i=4;
        while(i!=0){
            draw_snake_htl(a,h1+40,5-i);
			draw_snake_vert(l1,b,i);
            for(int j=0;j<10000000;j++){

            }
            erase_box(l1,b,10,10);
            b=b+10;
			i--;
        }
	return b;
}

//-----------------------------------------------------------------------------------------------------------------------------
// FUNCTION TO CHANGE THE POINTERS

void change_direction(int *up,int *down,int *left,int *right,int *change,int *curr_dir){
	if(*KEY_ptr==3 && curr_dir!=3){
		*up=1;
		*down=0;
		*left=0;
		*right=0;
		*change=1;
	}	
	else if(*KEY_ptr==2 && curr_dir!=2){
		*up=0;
		*down=1;
		*left=0;
		*right=0;
		*change=1;
	}
	else if(*KEY_ptr==1 && curr_dir!=1){
		*up=0;
		*down=0;
		*left=1;
		*right=0;
		*change=1;
	}
	else if(*KEY_ptr==4 && curr_dir!=4){
		*up=0;
		*down=0;
		*left=0;
		*right=1;
		*change=1;
	}
}

//----------------------------------------------------------------------------------------------------------------------
// FUNCTION TO CALCULATE THE SCORE

void score_cal(){
	volatile int * HEX3_HEX0_ptr = (int *) HEX3_HEX0_BASE;
    int sum=score;
    int i=0;
    for (i = 0; sum > 9; i++)
		sum-= 10;
	*HEX3_HEX0_ptr = seg7[i] << 8;
	*HEX3_HEX0_ptr |= seg7[sum];
}


//------------------------------------------------------------------------------------------------------------------------
// FUNCTION TO DRAW TH END PAGE OF THE GAME

void draw_end(){
       int x, y;
    for (x = 0; x < 320; x++)
    {
        for (y = 0; y < 240; y++)
        {
            write_pixel(x, y,GREEN);
            // if()
        }
    }
	draw_box(32,BLACK,105, 31, 6);
	draw_box(26,BLACK, 100, 6, 18 );
   
	draw_box(62,BLACK,105, 31, 6);
	draw_box(46,BLACK,105, 31, 6);
	draw_box(46, BLACK,117, 6, 16);
 
	draw_box(78,BLACK, 105, 6, 18 );
	draw_box(72,BLACK, 105, 30,6 );
	draw_box(78,BLACK,117,6,12);
	draw_box(78,BLACK, 129, 6, 18);
   
	draw_box(124, BLACK, 105, 6, 18);
	draw_box(118, BLACK,105, 30, 6);
	draw_box(124, BLACK, 117, 6,12);
	draw_box(124, BLACK,129, 6, 18);
 
	draw_box(148,BLACK, 105, 30, 6 );
	draw_box(154,BLACK, 111, 6, 6);
	draw_box(160,BLACK, 117, 6, 6);
	draw_box(166,BLACK,105, 30, 6);
 
	draw_box(178,  BLACK,105, 30,6);
	draw_box(184, BLACK,105, 6,12 );
	draw_box(184, BLACK,129, 6,12);
	draw_box(196, BLACK,111, 18,6);
}

//--------------------------------------------------------------------------------------------------------------------
// FUNCTION TO CALCULATE THE LIFES REMAINING
void lifes_cal(){
    int p=1;
    for(int i=0;i<lifes;i++){
        p=p*2;
    }
   *LEDR_ptr=p-1;
}

//------------------------------------------------------------------------------------------------------------------------

// MAIN FUNCTION

int main()
{

    int up=0;
	int down=0;
	int change=0;
	int left=1;
	int right=0;
	int curr_dir=3;
	clear_screen();
    draw_frame();
    int a=0,b=0;
    while(1){
        if(food==0){
            create_food();
            food++;
        }
		change_direction(&up,&down,&left,&right,&change,&curr_dir);
        if(a>320){
            a= 0;
		}
	    if(b>200){
			erase_box(a,b,10,10);
			erase_box(a,b+10,10,10);
			erase_box(a,b+20,10,10);
			b=0;
		}
        if(left==1){
		   if(change==1){
            b=change_direction_left(a,b);
            lifes--;
            curr_dir=3;
			change=0;
        }	
        draw_snake_htl(a,b,5);
			 for(int i=0;i<1000000;i++){
        }
		erase_box(a,b,10,10);
               a=a+10;
       }
       else if(down==1){
        if(change==1){
            a=change_direction_down(a,b);
            lifes--;
            curr_dir=2;
			change=0;
        }
         draw_snake_vert(a,b,5);
        for(int i=0;i<1000000;i++){

        }
		erase_box(a,b,10,10);
               b=b+10;
       
	   }
       score_cal();
       if(lifes>=0){
       lifes_cal();
       }
       if(lifes<0){
        draw_end();
        return 0;
       }
	}

   return 0;
}