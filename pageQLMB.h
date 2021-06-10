#pragma once
#include "QLMBThongKe.h"
#include "QLMBDSMB.h"


//====================PROTOTYPE==================

void drawPageQLMB(short **mapID,Shape *shape);

//================================================
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

