#pragma once
#include "QLVDSCB.h"
#include "QLVDSHK.h"
#include "QLVDatVe.h"

//==========================Page QLV=======================================

void drawPageQLV(short **mapID,Shape *shape){
    int x, y;
    short ID = -1, lastID = -1;
    clearmouseclick(WM_LBUTTONDOWN);
    drawPageQLV_DSCB(mapID,shape);
   while (1)
    {
        delay(DELAY_TO_CHECK_EVENT);
        lastID = ID;
        
        if (ismouseclick(WM_LBUTTONDOWN))
        {	
        	getIDMouseClick(ID,mapID);
		    if(ID>=ID_BUTTON_PAGE_MAIN && ID<=ID_BUTTON_PAGE4 && ID != ID_BUTTON_PAGE_QLV){            
            	return;
            } 
			clearmouseclick(WM_LBUTTONDOWN);
			switch (ID){
        	case ID_DSCB_BOARD_BUTTON_3:{
				drawPageQLV_DSCB(mapID,shape);	
        		break;
        	}
            case ID_ENTER_BUTTON_3:
            case ID_CONFIRM_TICKET_BUTTON:
			case ID_CANCEL_BUTTON:	
            {	
                drawPageQLV_DSHK(mapID,shape);
                
                break;
            }
            case ID_ORDER_TICKET_BUTTON_3:
            {	
                drawPageQLV_DatVe(mapID, shape);
                break;
            }
            default:
                break;
            }
        }
    }		
}



