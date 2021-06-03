#pragma once
#include "pageQLMB.h"
#include "pageQLCB.h"
#include "pageQLV.h"
#include "page4.h"

//====================PROTOTYPE==================
void drawMainPage();
void drawMainMenu(short **);
void drawMainInfor();
void checkEventMainPage(short **, Shape *);
//===============================================
void checkEventMainPage(short **mapID, Shape *shape)
{
    int x, y;
    short ID = -1, lastID = -1;
     clearmouseclick(WM_LBUTTONDOWN);
    while (1)
    {
        delay(DELAY_TO_CHECK_EVENT);
        checkHoverPageQLMB(ID, lastID, shape, mapID);
        lastID = ID;
        if (ismouseclick(WM_LBUTTONDOWN))
        {
			getIDMouseClick(ID,mapID);
			clearmouseclick(WM_LBUTTONDOWN);
			switch (ID){
        	case 0:{
            	setDefaultRightFrame(mapID);
                drawMainInfor();
        		break;
        	}
            case 1:
            {	
                drawPageQLMB(mapID, shape, true);
                
                break;
            }
            case 2:
            {	
                drawPageQLCB(mapID, shape);
// 				drawPageQLV(mapID, shape, true);
                break;
            }
            case 3:
            {	

//				drawPageSeatMap(mapID, shape, true);
               
                break;
            }
            case 4:
            {	
//            	drawPageVe(mapID, shape, true);

                break;
            }
            default:
                break;
            }
        }
    }
}
void drawMainPage()
{
    openGraph();
    //========MapID=========
    short **mapID = new short *[MAX_W + 1];
    for (int x = 0; x <= MAX_W; x++)
    {
        mapID[x] = new short[MAX_H + 1];
    }
    setID(0, 0, MAX_W, MAX_H, -1, mapID);

    //========MapID=========

    drawMainInfor();
    drawMainMenu(mapID);

    //=======deleteMapID=============
    for (short x = 0; x <= MAX_W; x++)
    {
        delete[] mapID[x];
    }
    delete[] mapID;
}


void drawMainMenu(short **mapID){

    setfillstyle(1, BLUE_M);
    bar(0, 0, 250, MAX_H);
    Shape shape[MAX_SHAPE];
    
    Button button[5] = {
        {60, 30, 120, 50, BLUE_M, BLUE_M, ""},
        {0, 0, 0, 0, BLUE_L, BLUE_L, "QUAN LY MAY BAY"},
        {0, 0, 0, 0, BLUE_L, BLUE_L, "QUAN LY CHUYEN BAY"},
        {0, 0, 0, 0, BLUE_L, BLUE_L, "QUAN LY VE"},
        {0, 0, 0, 0, BLUE_L, BLUE_L, "THONG KE"}};

    for (int i = 0; i <= 4; i++)
    {
        if (i > 0)
        {

            button[i].x1 = 0;
            button[i].y1 = 130 + 80 * (i - 1) + 20 * (i - 1);
            button[i].width = 249;
            button[i].height = 80;
        }
        drawButton(button[i], ID_BUTTON_PAGE_MAIN + i, mapID);
        convertToShape(button[i], shape[i+ID_BUTTON_PAGE_MAIN]);
    }
    setText(5, 10, 0, BLUE_M);
    outtextxy(70, 30, "MENU");
    
    checkEventMainPage(mapID, shape);
}

void drawMainInfor()
{

    setcolor(0);
    rectangle(485, 135, 985, 455);
    rectangle(500, 150, 1000, 470);

    char coverContent[][50] = {
        "GIANG VIEN: LUU NGUYEN KY THU",
        "BO MON: CTDL&GT",
        "TAC GIA 1: PHAM VAN THUAN",
        "TAC GIA 2: BUI TUAN HUNG",
        "TAC GIA 3: NGUYEN THI YEN VY",
        "FLIGHT", "MANAGER"};
    for (int i = 0; i < 5; i++)
    {
        setText(1, 8);
        outtextxy(600, 270 + i * 20, coverContent[i]);
    }

    setText(7, 10);
    outtextxy(470, 100, coverContent[5]);
    setText(4, 10);
    outtextxy(480, 160, coverContent[6]);
}
