#pragma once

#include "QLVreuse.h"


void checkHoverPageQLV_DSHK(short &newID, short lastID, Shape *shape, short **mapID){
      if (ismouseclick(WM_MOUSEMOVE))
    {	
 			
		int x, y;
        getmouseclick(WM_MOUSEMOVE, x, y);
        newID = mapID[x][y];
        short ID = newID;
        
        if(ID >= 60) //HOVER CHO BOARD
           	ID = ID%10 + 50;	
		if(lastID >= 60)
		   lastID = lastID%10 + 50;
		   
        //IN HOVER: MOI HOVER DEU MAU DEN
        if (ID > 0 && ID != lastID)
        {
            setcolor(BLACK);
            rectangle(shape[ID].x1, shape[ID].y1, shape[ID].x1 + shape[ID].width, shape[ID].y1 + shape[ID].height);
        }
        //OUT HOVER :VOI INPUT SE TO LAI MAU DEN, VOI BUTTON SE TO LAI MAU BLUE_L
        if (ID != lastID && lastID > 0)
        {
            if (lastID >= ID_NAME_INPUT_3)
                setcolor(WHITE);
            else
                setcolor(BLUE_L);
            rectangle(shape[lastID].x1, shape[lastID].y1, shape[lastID].x1 + shape[lastID].width, shape[lastID].y1 + shape[lastID].height);
        }

    }
}

void checkEventPageQLV_DSHK(Shape *shape, short **mapID){
    int x, y;
    short ID = -1, lastID = -1;
    clearmouseclick(WM_LBUTTONDOWN);	
	while(true){
		delay(DELAY_TO_CHECK_EVENT);
        checkHoverPageQLV_DSHK(ID, lastID, shape, mapID);
        lastID = ID;
		if(ismouseclick(WM_LBUTTONDOWN))
			{
				if(ID>=ID_BUTTON_PAGE_MAIN && ID<=ID_BUTTON_PAGE4 && ID != ID_BUTTON_PAGE_QLV){            
            		return;
            	}
				switch(ID){
					case ID_DSCB_BOARD_BUTTON_3:
					case ID_ORDER_TICKET_BUTTON_3 :{

						return;
					}
					default:
						break;
				}
					clearmouseclick(WM_LBUTTONDOWN);  				 
			}
	}	
}

//===========================Page Ds Hanh Khach TrongCB==========================

void drawPageQLV_DSHK(short **mapID,Shape *shape){
	setDefaultRightFrame(mapID);	

	setText(5,10);
	outtextxy(550,0,"DANH SACH VE");
	Button pre_next_Board[2] = {{640, 90, 25, 25, BLUE_L, 15, "<"}, {720, 90, 25, 25, BLUE_L, 15, ">"}};
    for (int i = 0; i < 2; i++)
    {
        setText(2, 10, 0, BLUE_L);
        drawButton(pre_next_Board[i], ID_DS_Ve_PRE_BUTTON_3 + i, mapID);//////////ID
        convertToShape(pre_next_Board[i], shape[i + ID_DS_Ve_PRE_BUTTON_3]);//////////ID
    }

	setcolor(0);
    rectangle(270, 45, 270+900, 45+40);
    setText(1,10,0,15);
	outtextxy(280, 55,"Ma CB:");
	setText(4,10,0,15);
	outtextxy(522, 47,"|");
	setText(1,10,0,15);
	outtextxy(538, 55,"Ngay Gio KH:");
	setText(4,10,0,15);
	outtextxy(857, 47,"|");
	setText(1,10,0,15);
	outtextxy(870, 55,"San Bay Den:");

	Board boardDsCB = {275,130,10,30,5,{60,110,330,100,300},{"STT","SO VE","HO VA TEN","PHAI","CMND"}};
	drawBoard(boardDsCB,ID_DS_VE_BOARD_3,mapID,shape);///////////////////ID

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
	    Button_Order_Cancel[i].borderColor = BLUE_L;
        drawButton(Button_Order_Cancel[i], ID_ORDER_TICKET_BUTTON_3 + i, mapID);///////////////////ID
        convertToShape(Button_Order_Cancel[i], shape[ID_ORDER_TICKET_BUTTON_3+i]);///////////////////ID
	}
	Input input_page_ve[4] = {
	{475, 570, 25, 350, 0},  // ho ten
	{920,570,4,70,0},	//so cho
	{440,620,20,300,0},	//cmnd
	{920,620,4,70,0}	//phai
	};
	for(int i = 0; i< 4;i++){
	input_page_ve[i].s = new char[input_page_ve[i].max+2];	
    drawInput(input_page_ve[i], mapID, i + ID_NAME_INPUT_3);///////////////////ID
    convertToShape(input_page_ve[i], shape[i + ID_NAME_INPUT_3]);///////////////////ID
	}
	setText();
	outtextxy(388,575,"HO VA TEN:");
	outtextxy(858,575,"SO CHO:");
	outtextxy(388,625,"CMND:");
	outtextxy(875,625,"PHAI:");
	
	checkEventPageQLV_DSHK(shape,mapID);
	for(int i =0; i<4;i++)
		delete[] input_page_ve[i].s;
		

}
