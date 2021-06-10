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
        
        if (ismouseclick(WM_LBUTTONDOWN) || ismouseclick(WM_LBUTTONDBLCLK))
        {	
        	getIDMouseClick(ID,mapID);
		    if(ID>=ID_BUTTON_PAGE_MAIN && ID<=ID_BUTTON_PAGE4 && ID != ID_BUTTON_PAGE_QLV){            
            	return;
            } 
			clearmouseclick(WM_LBUTTONDOWN);
			clearmouseclick(WM_LBUTTONDBLCLK);	
        	if(ID >= ID_BOARD){
				ID -= ID_BOARD;
				drawPageQLV_DatVe(mapID,shape);	
			}  			 	
			switch (ID){
        	case ID_DSCB_BOARD_BUTTON_3:{
				drawPageQLV_DSCB(mapID,shape);	
        		break;
        	}
            case ID_BUTTON_DSHK_3:	
            {	
                drawPageQLV_DSHK(mapID,shape);
                break;
            }
            case ID_BUTTON_STARTDATVE_3:
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



