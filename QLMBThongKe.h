#pragma once
#include "reuse.h"
#include "QLMBDSMB.h"
//====================PROTOTYPE==================

void outTK(Board &board,HashTable &table, int ID);
void outDSTK(Board &board, int startMB, int endMB,HashTable &table,int dsMB_n);
void updateNumOfBoardDSTK(int &numOfPage, int &presentPage,HashTable &table, int dsMB_n);
void checkEventPageQLMB_ThongKe(short **mapID, Shape *shape, Button &mainButton, Board &boardTK,Button *pre_next);
void drawPageQLMB_ThongKe(short **mapID, Shape *shape);


void outTK(Board &board,HashTable &table, int ID){
    char toChar[5];
	setText();
    short x1 = board.x1,
	y1 = (ID%10 + 1) * board.heightOfLine + board.y1, 
	x2 = x1;
   for(int col = 1; col<=board.numOfCol; col++){
   		x1 = x2;
    	x2 += board.widthOfCol[col - 1];    

        if (col == 1) //SO HIEU
            outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 4.5 * strlen(table[ID].soHieu),
                      y1 + (board.heightOfLine) / 2 - 10, table[ID].soHieu);
        else if (col == 2) //SO LUOT
        { 
            itoa(table[ID].soLanTH, toChar, 10);
            outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 3.5 * strlen(toChar),
                      y1 + (board.heightOfLine) / 2 - 10, toChar);
        } 	
   }
}

void outDSTK(Board &board, int startMB, int endMB,HashTable &table,int dsMB_n){

    int x1, y1, x2 = board.x1, y2 = board.y1;
    for (int line = 0; line <= board.numOfLine && startMB-1 < dsMB_n; line++)
    {
		
        y1 = y2;
        y2 += board.heightOfLine;
        x2 = board.x1;
        for (int col = 1; col <= board.numOfCol; col++)
        {
            x1 = x2;
            x2 += board.widthOfCol[col - 1];
            if (line >= 1)
               outTK(board,table,startMB -1);
			
        }
        if (line >= 1)
            startMB++;
    }
}

void updateNumOfBoardDSTK(int &numOfPage, int &presentPage,HashTable &table, int dsMB_n)
{
    numOfPage = (dsMB_n - 1) / 10 + 1;
    char toChar[5];
    setText();
    setfillstyle(1, 15);
    bar(676, 90, 715, 115);
    itoa(presentPage, toChar, 10);
    outtextxy(675, 95, toChar);
    outtextxy(675 + 15, 95, "/");
    itoa(numOfPage, toChar, 10);
    outtextxy(675 + 30, 95, toChar);
}
void checkEventPageQLMB_ThongKe(short **mapID, Shape *shape, Button &mainButton, Board &boardTK,Button *pre_next){

	DanhSachMayBay dsMB;
	layDSMayBay(dsMB);
	DanhSachChuyenBay dsCB = NULL;
	layDSChuyenBay(dsCB);
	HashTable table;
	thongKeMBThucHienCB(table, dsCB, dsMB);		
	short ID = -1,lastID = -1;	
	int numOfPage = (dsMB.n - 1) / 10 + 1, presentPage = 1; 
    updateNumOfBoardDSTK(numOfPage, presentPage,table,dsMB.n);
    outDSTK(boardTK, 1, 10,table,dsMB.n);

	while(true){
        delay(DELAY_TO_CHECK_EVENT);
        checkHoverPageQLMB(ID, lastID, shape, mapID); 	
        lastID = ID;
	
        if (ismouseclick(WM_LBUTTONDOWN)) {

			if((ID>=ID_BUTTON_PAGE_MAIN && ID<=ID_BUTTON_PAGE4 && ID != ID_BUTTON_PAGE_QLMB) || ID == ID_BUTTON_CLOSETHONGKE_1){            
            	return;
            }

	    if(ID == ID_BUTTON_PRE) //PRE 
	            {
	                if (presentPage > 1)
	                {
	                    presentPage--;           
	                    updateNumOfBoardDSTK(numOfPage, presentPage,table,dsMB.n);  
	                    drawBoard(boardTK, (presentPage - 1) * 10 + ID_BOARD, mapID, shape);
	                    outDSTK(boardTK, 10 * (presentPage - 1) + 1, 10 * (presentPage),table,dsMB.n); 
	                    
					}

	            }
		if(ID == ID_BUTTON_NEXT) //NEXT
            {
                if (presentPage < numOfPage)
                {
                    presentPage++;           
                    updateNumOfBoardDSTK(numOfPage, presentPage,table,dsMB.n);  
                    drawBoard(boardTK, (presentPage - 1) * 10 + ID_BOARD, mapID, shape);
                    outDSTK(boardTK, 10 * (presentPage - 1) + 1, 10 * (presentPage),table,dsMB.n); 
                    
				}
            }         		

			clearmouseclick(WM_LBUTTONDOWN);
	 
        }
   					
	}
	
}
                                    	
void drawPageQLMB_ThongKe(short **mapID, Shape *shape){
    setDefaultRightFrame(mapID);

    setText(6, 10);
    outtextxy(455, 30, "THONG KE TAN XUAT");
	
    Button pre_next[2] = {{640, 90, 25, 25, BLUE_L, 15, "<"}, {720, 90, 25, 25, BLUE_L, 15, ">"}};
    for (int i = 0; i < 2; i++)
    {
    
        drawButton(pre_next[i], ID_BUTTON_PRE + i, mapID);
        convertToShape(pre_next[i], shape[ID_BUTTON_PRE +i]);
    }
			
    Board boardTK = {275, 130, 10, 30, 2, {600, 300}, {"SO HIEU MAY BAY", "SO LUOT THUC HIEN CHUYEN BAY"}};
    drawBoard(boardTK, ID_BOARD, mapID, shape);
    
    Button mainButton = {620, 560, 160, 40, BLUE_L, WHITE, "QUAN LY MAY BAY"};
    drawButton(mainButton,ID_BUTTON_CLOSETHONGKE_1, mapID);
    convertToShape(mainButton, shape[ID_BUTTON_CLOSETHONGKE_1]);
    
    setcolor(0);
    rectangle(275, 470, 1175, MAX_H);  	
    
	checkEventPageQLMB_ThongKe(mapID, shape, mainButton, boardTK,pre_next);

}
