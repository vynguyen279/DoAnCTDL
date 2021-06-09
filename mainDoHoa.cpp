#include "MainPage.h"

void checkEventPageQLMB_ThongKe(short **mapID, Shape *shape, Button &mainButton, Board &boardMB,Button *pre_next){

	DanhSachMayBay dsMB;
	layDSMayBay(dsMB);
	short ID = -1,lastID = -1;	
	int numOfPage = (dsMB.n - 1) / 10 + 1, presentPage = 1; 
    updateNumOfBoardDSMB(numOfPage, presentPage,dsMB);
    outDSMB(boardMB, 1, 10,dsMB);
	while(true){
        delay(DELAY_TO_CHECK_EVENT);
        checkHoverPageQLMB(ID, lastID, shape, mapID);
        lastID = ID;
	
        if (ismouseclick(WM_LBUTTONDOWN)) {

			if((ID>=ID_BUTTON_PAGE_MAIN && ID<=ID_BUTTON_PAGE4 && ID != ID_BUTTON_PAGE_QLMB) || ID == ID_BUTTON_CLOSETHONGKE_1){            
            	return;
            }

	    if(ID == ID_BUTTON_PRE) //PRE DSMB PAGE
	            {
	                if (presentPage > 1)
	                {
	                    presentPage--;           
	                    updateNumOfBoardDSMB(numOfPage, presentPage,dsMB);  
	                    drawBoard(boardMB, (presentPage - 1) * 10 + ID_BOARD, mapID, shape);
	                    outDSMB(boardMB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsMB); 
	                    
					}

	            }
		if(ID == ID_BUTTON_NEXT) //PRE DSMB PAGE
            {
                if (presentPage < numOfPage)
                {
                    presentPage++;           
                    updateNumOfBoardDSMB(numOfPage, presentPage,dsMB);  
                    drawBoard(boardMB, (presentPage - 1) * 10 + ID_BOARD, mapID, shape);
                    outDSMB(boardMB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsMB); 
                    
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
			
    Board boardMB = {275, 130, 10, 30, 2, {600, 300}, {"SO HIEU MAY BAY", "SO LUOT THUC HIEN CHUYEN BAY"}};
    drawBoard(boardMB, ID_BOARD, mapID, shape);
    Button mainButton = {620, 560, 160, 40, BLUE_L, WHITE, "QUAN LY MAY BAY"};
    drawButton(mainButton,ID_BUTTON_CLOSETHONGKE_1, mapID);
    convertToShape(mainButton, shape[ID_BUTTON_CLOSETHONGKE_1]);
    
    setcolor(0);
    rectangle(275, 470, 1175, MAX_H);  	
    
	checkEventPageQLMB_ThongKe(mapID, shape, mainButton, boardMB,pre_next);

}



void drawPageQLMB(short **mapID,Shape *shape){
    int x, y;
    short ID = -1, lastID = -1;
	drawPageQLMB_DSMB(mapID,shape);                
   while (1)
    {
        delay(DELAY_TO_CHECK_EVENT);
        lastID = ID;       
        if (ismouseclick(WM_LBUTTONDOWN))
        {
				
        	getIDMouseClick(ID,mapID);
        	
		    if(ID>=ID_BUTTON_PAGE_MAIN && ID<=ID_BUTTON_PAGE4 && ID != ID_BUTTON_PAGE_QLMB){          
            	return;
            }
			clearmouseclick(WM_LBUTTONDOWN);	 
			if(ID == ID_BUTTON_CLOSETHONGKE_1)
            {	
                drawPageQLMB_DSMB(mapID,shape);
            
            }
			if(ID == ID_BUTTON_THONGKE_1)
            {	
                drawPageQLMB_ThongKe(mapID,shape);
            
            }            
        }

    }		
}

int main(){	
	drawMainPage();
	getch();
	return 0;
}


