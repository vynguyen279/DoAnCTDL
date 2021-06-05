#pragma once
#include <winbgim.h>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include "io.h"
using namespace std;

#define BLUE_M COLOR(51,187,219)
#define BLUE_L COLOR(163,232,255)
#define BLUE_D COLOR(101,204,206)
#define BLACK 0
#define GREEN 10
#define RED 12
#define WHITE 15
#define GRAY 8
#define SILVER 7
#define MAX_W 1200
#define MAX_H 700
#define DELAY_TO_CHECK_EVENT 0.0001 
#define MAX_SHAPE 100
#define DEFAULT_ID -1

#define ID_BUTTON_PAGE_MAIN 0
#define ID_BUTTON_PAGE_QLMB 1
#define ID_BUTTON_PAGE_QLCB 2
#define ID_BUTTON_PAGE_QLV 3
#define ID_BUTTON_PAGE4 4


#define ID_BUTTON_PREBOARD_DSMB_1 5
#define ID_BUTTON_NEXTBOARD_DSMB_1 6
#define ID_BUTTON_ADD_1 7
#define ID_BUTTON_DEL_1 8
#define ID_BUTTON_UPDATE_1 9
#define ID_BUTTON_ACPDEL_1 10
#define ID_BUTTON_UNDEL_1 11
#define ID_BUTTON_ACPUPDATE_1 12
#define ID_BUTTON_UNUPDATE_1 13
#define ID_INPUT_SHMB_1 31 
#define ID_INPUT_SOCHO_1 32
#define ID_INPUT_LMB_1 33
#define ID_BOARD_DSMB_1 50 

#define ID_BUTTON_PREBOARD_DSCB_2 5
#define ID_BUTTON_NEXTBOARD_DSCB_2 6
#define ID_BUTTON_FILL_CB_2 7
#define ID_BUTTON_UNFILLTIME_CB_2 8
#define ID_BUTTON_UNFILLDESTINATION_CB_2 9
#define ID_BUTTON_UNFILL_CB_2 10
#define ID_BUTTON_ADD_CB_2 11
#define ID_BUTTON_CANCEL_CB_2 12
#define ID_BUTTON_UPDATE_CB_2 13
#define ID_BUTTON_ACPCANCEL_CB_2 14
#define ID_BUTTON_UNCANCEL_CB_2 15
#define ID_BUTTON_ACPUPDATE_CB_2 16
#define ID_BUTTON_UNUPDATE_CB_2 17
#define ID_INPUT_FILLTIMED_2 30
#define ID_INPUT_FILLTIMEM_2 31
#define ID_INPUT_FILLTIMEY_2 32
#define ID_INPUT_FILLDESTINATION_2 33
#define ID_INPUT_MCB_2 34
#define ID_INPUT_SHMB_2 35
#define ID_INPUT_DAY_2 36
#define ID_INPUT_MONTH_2 37
#define ID_INPUT_YEAR_2 38
#define ID_INPUT_HOUR_2 39
#define ID_INPUT_MINUTE_2 40
#define ID_INPUT_STATUS_2 41
#define ID_INPUT_DESTINATION_2 42
#define ID_BOARD_DSCB_2 50
/************************************************
khai bao o nho cho input nhieu hon maxkitu + 1 de lam con tro nhap nhay nhung van chi duoc nhap maxkitu

************************************************/



//===================== Struct =================
struct Shape{
	short x1,y1,width,height;
}; 
struct Button{
	short
	x1,y1,
	width,
	height;
	int 
	fillColor,
	borderColor;
	char content[50];
};

struct Board{
	short
	x1,y1,
	numOfLine,    //LINE 0 = HEADER 
	heightOfLine,  
	numOfCol,
	widthOfCol[10];
	char header[10][50];
};

struct Input{
	short
	x1,y1,
	max,
	width,
	lastL;
	char *s;
};
//=====================================


//====================PROTOTYPE==================
void convertToShape(Input &input,Shape &shape);
void convertToShape(Button &button,Shape &shape);
void drawLockInput(Input &input, short **mapID);
void drawInput(Input &input, short **mapID, short ID);
void drawBoard(Board &board, short ID, short **mapID, Shape *shape);
void drawButton(Button &button, short ID, short **mapID);
void getIDMouseClick(short &ID, short **mapID);
void setID(short x1, short y1, short width, short height, short ID, short **mapID);
void setText(short size, short font,int textColor,int bkColor);
void setDefaultRightFrame(short **mapID);
void resetButtonFrame(short **mapID);
void outAlert(int color, char *alert);
void openGraph();
//=================================================
void openGraph(){
	initwindow(MAX_W,MAX_H);	
	setbkcolor(15);
	cleardevice();
	setbkcolor(15);
}

void setText(short size = 1, short font= 11,int textColor = BLACK,int bkColor = WHITE){
	settextstyle(font,0,size);
	setcolor(textColor);                   
	setbkcolor(bkColor);
}

void outAlert(int color, char *alert){
	setText(1, 11, color);
    setfillstyle(1, WHITE);
    bar(280, 530, 1175, 565);
    outtextxy(725-strlen(alert)*4,540,alert);
    if(alert!="")
	putpixel(725,540,BLACK);	   
}

void convertToShape(Button &button,Shape &shape){
	shape.x1 = 	button.x1;
	shape.y1 = 	button.y1;
	shape.width = 	button.width;
	shape.height = 	button.height;
	
}
void convertToShape(Input &input,Shape &shape){ 
	shape.x1 = 	input.x1+1;
	shape.y1 = 	input.y1+1;
	shape.width = 	input.width-2;
	shape.height = 	28;
}

void setID(short x1, short y1, short width, short height, short ID, short **mapID)
{
    for (short x = x1; x <= x1 + width; x++)
        for (short y = y1; y <= y1 + height; y++)
            mapID[x][y] = ID;
}

void drawButton(Button &button, short ID, short **mapID)
{   
    
    if(button.content[0] == '<' || button.content[0] == '>')
    	setText(2, 10, 0, button.fillColor);
	else 
		setText(1, 11, 0, button.fillColor); 
    setfillstyle(1, button.fillColor);
    bar(button.x1, button.y1, button.x1 + button.width, button.y1 + button.height);
    //=========outButtonText===========
    
    if (strlen(button.content) < 8 || strlen(button.content) >= 13)
        outtextxy(button.x1 + button.width / 2 - 4.3 * strlen(button.content), button.y1 + (button.height) / 2 - 10, button.content);
    else if (strlen(button.content) < 13)
        outtextxy(button.x1 + button.width / 2 - 3.9 * strlen(button.content), button.y1 + (button.height) / 2 - 10, button.content);
    setcolor(button.borderColor);
    rectangle(button.x1, button.y1, button.x1 + button.width, button.y1 + button.height);
    setID(button.x1, button.y1, button.width, button.height, ID, mapID);
}
void drawLockButton(Button &button,short **mapID){

    if(button.content[0] == '<' || button.content[0] == '>')
    	setText(2, 10, 0, SILVER);
	else 
		setText(1, 11, 0, SILVER); 
    setfillstyle(1, SILVER);
    bar(button.x1, button.y1, button.x1 + button.width, button.y1 + button.height);
    //=========outButtonText===========
    
    if (strlen(button.content) < 8 || strlen(button.content) >= 13)
        outtextxy(button.x1 + button.width / 2 - 4.3 * strlen(button.content), button.y1 + (button.height) / 2 - 10, button.content);
    else if (strlen(button.content) < 13)
        outtextxy(button.x1 + button.width / 2 - 3.9 * strlen(button.content), button.y1 + (button.height) / 2 - 10, button.content);
    setcolor(SILVER);
    rectangle(button.x1, button.y1, button.x1 + button.width, button.y1 + button.height);
    setID(button.x1, button.y1, button.width, button.height, -1, mapID);			
}

void drawBoard(Board &board, short ID, short **mapID, Shape *shape)
{
    int x1, y1, x2 = board.x1, y2 = board.y1,x = 50;
    setfillstyle(1,15);
	bar(252,130,1176,460);
    for (int line = 0; line <= board.numOfLine; line++)
    {
        y1 = y2;
        y2 += board.heightOfLine;
        x2 = board.x1;
        for (int col = 1; col <= board.numOfCol; col++)
        {
            x1 = x2;
            x2 += board.widthOfCol[col - 1];

            if (line == 0)
            {
                //=====out header
                setfillstyle(1, BLUE_L);
                bar(x1, y1, x2, y2);
                setText(1, 11, 0, BLUE_L);
                if (strlen(board.header[col - 1]) < 10)
                    outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 4.5 * strlen(board.header[col - 1]),
                              y1 + (board.heightOfLine) / 2 - 10, board.header[col - 1]);
                else
                    outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 3.5 * strlen(board.header[col - 1]),
                              y1 + (board.heightOfLine) / 2 - 10, board.header[col - 1]);
            }

            //============in khung
            rectangle(x1,y1, x2, y2);
        }

        //=====SET LINE ID
        if (line >= 1)
        {
            for (int y = y1; y <= y2; y++)
                for (int x = board.x1; x <= x2; x++)
                    mapID[x][y] = ID + line - 1;
                        

            //=====ADD TO SHAPE
            if(ID<=59){          	
		        shape[line + x - 1].x1 = board.x1 + 1;
		        shape[line + x - 1].y1 = y1 + 1;
		        shape[line + x - 1].width = x2 - board.x1 - 2;
		        shape[line + x - 1].height = y2 - y1 - 2;           	
            }

        }
    }
}


void drawInput(Input &input, short **mapID, short ID)
{
    setfillstyle(1, 15);
    bar(input.x1, input.y1, input.x1 + input.width, input.y1 + 30);
    setcolor(0);
    rectangle(input.x1, input.y1, input.x1 + input.width, input.y1 + 30);
    setID(input.x1, input.y1, input.width, 30, ID, mapID);
    setText(1, 10);
    if (input.lastL != 0)
        outtextxy(input.x1 + 10, input.y1 + 5, input.s);
    else
    	input.s[0] = '\0';
}

void getIDMouseClick(short &ID, short **mapID)
{
    int x, y;
    getmouseclick(WM_LBUTTONDOWN, x, y);
    ID = mapID[x][y];
}

void drawLockInput(Input &input, short **mapID)
{
    setfillstyle(1, 15);
    bar(input.x1, input.y1, input.x1 + input.width, input.y1 + 30);
	setText(1, 10, GRAY, 15);
    rectangle(input.x1, input.y1, input.x1 + input.width, input.y1 + 30); 
    setID(input.x1, input.y1, input.width, 30, -1, mapID);
    if (input.lastL != 0)
        outtextxy(input.x1 + 10, input.y1 + 5, input.s);
}

void resetButtonFrame(short **mapID){ 
    setfillstyle(1, 15);
    bar(280, 475, 1175, 525);
    setID(280, 475, 895, 50, -1, mapID);
}

void setDefaultRightFrame(short **mapID)
{
    setID(251, 0, 949, MAX_H, -1, mapID);
    setfillstyle(1, 15);
    bar(251, 0, MAX_W, MAX_H);
}
