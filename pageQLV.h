#pragma once
#include "reuse.h"

//====================PROTOTYPE==================
void drawPageQLV(short **, Shape *, bool);
void drawPageSeatMap(short **mapID,Shape *shape,bool unlockCheck);
void drawPageVe(short **mapID,Shape *shape,bool unlockCheckMouse);
void drawPageQLV(short **mapID,Shape *shape,bool unlockCheck);
void checkEventPageQLV(short **mapID, Shape *shape, Input *input, Board &board_DSCB);
void checkHoverPageQLV(short &ID, short lastID, Shape *shape, short **mapID);
//=================================================

void checkHoverPageQLV(short &ID, short lastID, Shape *shape, short **mapID){
}

void checkEventPageQLV(short **mapID, Shape *shape, Input *input, Board &board_DSCB){
}


void drawPageQLV(short **mapID,Shape *shape,bool unlockCheck){
	setDefaultRightFrame(mapID);	
	
	//chuc nang phim tat
	setText(5, 2, 0, BLUE_M);
    setfillstyle(1, BLUE_M);
    bar(0, 550, 250, MAX_H);
    outtextxy(70, 610, "DELETE   : XOA");
    rectangle(65,605,120,625);
    outtextxy(70, 640, "F1   : HIEU CHINH");
	rectangle(65,635,85,655);
	
	setText(6,10);
	outtextxy(410,30,"DANH SACH CHUYEN BAY");
	Button pre_next_Board[2] = {{640,90,25,25,BLUE_L,15,"<"},{720,90,25,25,BLUE_L,15,">"}};
	for(int i = 0;i <2;i++){
		setText(2,10,0,BLUE_L);
		drawButton(pre_next_Board[i],5+i,mapID);///////////////////ID
		convertToShape(pre_next_Board[i],shape[i+5]);///////////////////ID
	}

		
	Board board_DSCB_conve = {275,130,10,30,5,{125,125,180,350,120},{"MA CB","SO HIEU MB","NGAY GIO KHOI HANH","SAN BAY DEN","TRANG THAI"}};
	drawBoard(board_DSCB_conve,70,mapID,shape);///////////////////ID
	
	setcolor(0);
    rectangle(275, 470, 1175, MAX_H-20);  
    

	Input input[1] = {660,570,15,0,0};
	input[0].s = new char[input[0].max+2];	
    drawInput(input[0], mapID,7);///////////////////ID
    convertToShape(input[0], shape[7]);///////////////////ID
	
	outtextxy(500,575,"MA CHUYEN BAY:");
	if(unlockCheck)
 	checkEventPageQLV(mapID,shape,input,board_DSCB_conve);
 	
}

//===========================Page Ds Hanh Khach TrongCB==========================

void drawPageVe(short **mapID,Shape *shape,bool unlockCheckMouse){
	setDefaultRightFrame(mapID);	
	
	//chuc nang phim tat
	setText(5, 2, 0, BLUE_M);
    setfillstyle(1, BLUE_M);
    bar(0, 550, 250, MAX_H);
    outtextxy(70, 610, "DELETE   : XOA");
    rectangle(65,605,120,625);
    outtextxy(70, 640, "F1   : HIEU CHINH");
	rectangle(65,635,85,655);
	
	setText(6,10);
	outtextxy(560,30,"DANH SACH VE");
	Button pre_next_Board[2] = {{700,90,25,25,BLUE_L,15,"<"},{760,90,25,25,BLUE_L,15,">"}};
	for(int i = 0;i <2;i++){
		setText(2,10,0,BLUE_L);
		drawButton(pre_next_Board[i],8+i,mapID);///////////////////ID
		convertToShape(pre_next_Board[i],shape[i+8]);///////////////////ID
	}

		
	Board boardDsCB = {275,130,10,30,4,{150,330,120,300},{"SO VE","HO VA TEN","PHAI","CMND"}};
	drawBoard(boardDsCB,50,mapID,shape);///////////////////ID
	
	setcolor(0);
    rectangle(275, 470, 1175, MAX_H);  
    
	Button Button_Order_Cancel[3] ={{0,0,0,0,0,0,"DAT VE"},{0,0,0,0,0,0,"HUY VE"},{0,0,0,0,0,0,"DS CHUYEN BAY"}} ;
	for(int i = 0;i <3;i++){
		setText(1,11,0,BLUE_L);
		Button_Order_Cancel[i].x1 = 475 + 180*i;
		Button_Order_Cancel[i].y1 = 480;
		Button_Order_Cancel[i].width = 160;
	    Button_Order_Cancel[i].height = 40;
	    Button_Order_Cancel[i].fillColor = BLUE_L;
	    Button_Order_Cancel[i].borderColor = 15;
        drawButton(Button_Order_Cancel[i], 10 + i, mapID);///////////////////ID
        convertToShape(Button_Order_Cancel[i], shape[10+i]);///////////////////ID
	}

	Input input_page_ve[4] = {
	{500, 570, 25, 0, 0},  // ho ten
	{930,570,4,0,0},	//so cho
	{440,625,20,0,0},	//cmnd
	{910,625,4,0,0}	//phai
	};
	for(int i = 0; i< 4;i++){
	input_page_ve[i].s = new char[input_page_ve[i].max+2];	
    drawInput(input_page_ve[i], mapID, i + 12);///////////////////ID
    convertToShape(input_page_ve[i], shape[i + 12]);///////////////////ID
	}
	
	outtextxy(380,575,"HO VA TEN:");
	outtextxy(850,575,"SO CHO:");
	outtextxy(380,630,"CMND:");
	outtextxy(850,630,"PHAI:");
 	
}

//===========================PageSeatMap===================

void drawPageSeatMap(short **mapID,Shape *shape,bool unlockCheck){
		setDefaultRightFrame(mapID);	
	
	//chuc nang phim tat
	setText(5, 2, 0, BLUE_M);
    setfillstyle(1, BLUE_M);
    bar(0, 550, 250, MAX_H);
    outtextxy(70, 610, "DELETE   : XOA");
    rectangle(65,605,120,625);
    outtextxy(70, 640, "F1   : HIEU CHINH");
	rectangle(65,635,85,655);
	
	setText(6,10);
	outtextxy(500,5,"SO DO CHO NGOI");
	
	Button pre_next_Board[2] = {{680,70,25,25,BLUE_L,15,"<"},{740,70,25,25,BLUE_L,15,">"}};
	for(int i = 0;i <2;i++){
		setText(2,10,0,BLUE_L);
		drawButton(pre_next_Board[i],13+i,mapID);///////////////////ID
		convertToShape(pre_next_Board[i],shape[i+13]);///////////////////ID
	}
	setcolor(0);
    rectangle(270, 120, 270+900, 120+50);
    setText(1,10,0,15);
	outtextxy(280, 132,"Ma CB:");
	setText(4,10,0,15);
	outtextxy(522, 126,"|");
	setText(1,10,0,15);
	outtextxy(538, 132,"Ngay Gio KH:");
	setText(4,10,0,15);
	outtextxy(857, 126,"|");
	setText(1,10,0,15);
	outtextxy(870, 132,"San Bay Den:");
	setText(3,10,0,15);
	outtextxy(456, 230,"A");
    outtextxy(456, 230+45, "B");
    outtextxy(456, 230+46*2, "C");
    outtextxy(456, 230+46*3, "D");
     outtextxy(456, 230+46*4, "E");
    
    Button button_seat[60];
    for(int i = 0;i<60;i++){
    	button_seat[i]={0,0,0,0,0,0};
	}
	
	int x,y;
	for(int i = 0;i <12;i++){
		 x=500+40*i;
		for(int j=0;j<5;j++){
			 y=230+45*j;
			button_seat[i].x1= x;
			button_seat[i].y1 = y;
		    button_seat[i].width = 35;
			button_seat[i].height = 35;
			button_seat[i].fillColor = 15;
			button_seat[i].borderColor = 0; 
			drawButton(button_seat[i],77,mapID);///////////////////ID

 
    rectangle(270, 510, 270+900, 510+300);
 
 	Button Button_Order_Cancel[2] ={{0,0,0,0,0,0,"XAC NHAN"},{0,0,0,0,0,0,"HUY"}} ;
	for(int i = 0;i <2;i++){
		setText(1,11,0,BLUE_L);
		Button_Order_Cancel[i].x1 = 550 + 180*i;
		Button_Order_Cancel[i].y1 = 525;
		Button_Order_Cancel[i].width = 160;
	    Button_Order_Cancel[i].height = 40;
	    Button_Order_Cancel[i].fillColor = BLUE_L;
	    Button_Order_Cancel[i].borderColor = 15;
        drawButton(Button_Order_Cancel[i], 10 + i, mapID);///////////////////ID
        convertToShape(Button_Order_Cancel[i], shape[10+i]);///////////////////ID
	}
	
	Input input_page_ve[4] = {
	{500, 610, 25, 0, 0},  // ho ten
	{937,610,4,0,0},	//so cho
	{447,650,20,0,0},	//cmnd
	{914,650,4,0,0}	//phai
	};
	
	for(int i = 0; i< 4;i++){
	input_page_ve[i].s = new char[input_page_ve[i].max+2];	
    drawInput(input_page_ve[i], mapID, i + 12);///////////////////ID
    convertToShape(input_page_ve[i], shape[i + 12]);///////////////////ID
	}
	
	outtextxy(388,615,"HO VA TEN:");
	outtextxy(858,615,"SO CHO:");
	outtextxy(388,653,"CMND:");
	outtextxy(858,653,"PHAI:");
	}	
	}
}

