#pragma once
#include "QLCBDSCB.h"
#include "QLVDatVe.h"
//====================PROTOTYPE==================

void drawPageQLCB(short **mapID,Shape *shape);

//================================================

void drawPageQLCB(short **mapID,Shape *shape){
    int x, y;
    short ID = -1, lastID = -1;
	drawPageQLCB_DSCB(mapID,shape);                
   while (1)
    {
        delay(DELAY_TO_CHECK_EVENT);
        lastID = ID;
         if(ismouseclick(WM_LBUTTONDBLCLK)){
        	getIDMouseClick(ID,mapID);
			clearmouseclick(WM_LBUTTONDBLCLK);
        	if(ID >= ID_BOARD){
				ID -= ID_BOARD;
				drawPageQLV_DatVe(mapID,shape);	
			}	
        }       
        if (ismouseclick(WM_LBUTTONDOWN))
        {
				
        	getIDMouseClick(ID,mapID);
        	
		    if(ID>=ID_BUTTON_PAGE_MAIN && ID<=ID_BUTTON_PAGE4 && ID != ID_BUTTON_PAGE_QLCB){          
            	return;
            }
			clearmouseclick(WM_LBUTTONDOWN);	 
			if(ID == ID_CONFIRM_TICKET_BUTTON || ID == ID_CANCEL_BUTTON)
            {	
                drawPageQLCB_DSCB(mapID,shape);
            
            }
        }

    }		
}

