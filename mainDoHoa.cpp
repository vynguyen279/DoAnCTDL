#include "MainPage.h"


void drawDSCBFrame(short **mapID,Shape *shape,DanhSachTam &dsTmp, Board &boardCB,Input *inputFill, Input *input,int &numOfPage,int &presentPage){
	setfillstyle(1,WHITE);
	bar(251,0,MAX_W,130);
	setID(251,0,MAX_W - 251,130,-1,mapID);
	
	setText(6,10);
	outtextxy(410,-10,"DANH SACH CHUYEN BAY");
	Button pre_next[2] = {{640,50,25,25,BLUE_L,15,"<"},{720,50,25,25,BLUE_L,15,">"}};
	for(int i = 0;i <2;i++){
		setText(2,10,0,BLUE_L);
		drawButton(pre_next[i],ID_BUTTON_PRE+i,mapID);
		convertToShape(pre_next[i],shape[i+ID_BUTTON_PRE]);
	}
	
	setText();
	outtextxy(275,80,"NGAY GIO K.H:");	
	outtextxy(506,101,"SAN BAY DEN:");	
	Button buttonFill[4]= {
	{1105,60,70,30,BLUE_L,WHITE,"BO LOC"},
	{456,97,30,30,BLUE_L,BLUE_L,"X"},
	{1057,97,30,30,BLUE_L,BLUE_L,"X"},
	{1105,97,70,30,BLUE_L,WHITE,"HUY LOC"}
	};
	for(int i = 0; i< 4;i++){
	drawInput(inputFill[i],mapID,i+ID_INPUT_FILLTIMED_2);
	drawButton(buttonFill[i],ID_BUTTON_FILL_CB_2 + i,mapID);
	}
	
	makeBeautiFillInput(inputFill);

	
   	UpdateNumOfBoardDSCB(numOfPage, presentPage,dsTmp);
    drawBoard(boardCB, (presentPage - 1) * 10 + ID_BOARD, mapID, shape);
    outDSCB(boardCB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsTmp);
    
	Button mainButton[4] ={{0,0,0,0,0,0,"THEM CB"},{0,0,0,0,0,0,"HUY CB"},{0,0,0,0,0,0,"CAP NHAT"},{971,570,100,30,BLUE_L,BLUE_L,"XEM DSMB"}};
	for(int i = 0;i <4;i++){
		if(i < 3){
		mainButton[i].x1 = 455 + 180*i;
		mainButton[i].y1 = 480;
		mainButton[i].width = 160;
	    mainButton[i].height = 40;
	    mainButton[i].fillColor = BLUE_L;
	    mainButton[i].borderColor = WHITE;			
		}
        drawButton(mainButton[i], ID_BUTTON_ADD_CB_2 + i, mapID);
	}					
	drawInputPageQLCB(input,mapID,true);	
}

void checkEventDSMBFrame(short **mapID,Shape *shape, DanhSachMayBay &dsMB,Input &inputSHMB,Board &boardMB,Button *pre_next,Button &buttonCloseDSMB){
	short ID = -1,lastID = -1, chooseID = -1;
	int numOfPage = (dsMB.n - 1) / 10 + 1, presentPage = 1; 		//quan ly so trang
    short maxChoose = 0;                                              //khong cho chon vao o khong co may bay
    bool isEnter = false;
    updateNumOfBoardDSMB(numOfPage, presentPage,dsMB);
    outDSMB(boardMB, 1, 10,dsMB);
    clearmouseclick(WM_LBUTTONDOWN);
	clearmouseclick(WM_LBUTTONDBLCLK);
	while(true){
        delay(DELAY_TO_CHECK_EVENT);
        checkHoverPageQLMB(ID, lastID, shape, mapID);
        lastID = ID;
        if(ismouseclick(WM_LBUTTONDBLCLK) && chooseID != -1 && ID == chooseID){
				return;
        }
				
        if (ismouseclick(WM_LBUTTONDOWN)) {
        	//huy chon
            if (ID >= ID_BOARD)   //chon may bay
            {	
           		maxChoose = dsMB.n - 1 + ID_BOARD;
           	
            	if(ID <= maxChoose){

	                if (ID != chooseID) //CHON CAI MOI
	                {
	                                   
	                    chooseID = ID;
	                    strcpy(input[1].s,dsMB.mayBay[chooseID - ID_BOARD] -> soHieuMayBay);
	                    input[1].lastL = strlen(input[1].s);
	                    setText(1, 10);
	                    setfillstyle(1,WHITE);
						bar(input[1].x1+1,input[1].y1+1,input[1].x1 + input[1].width -1,input[1].y1+29) ;
	                    outtextxy(input[1].x1 + 10, input[1].y1 + 5, input[1].s);
	                }
	                
            	}
            	
            }
			if(ID>=ID_BUTTON_PAGE_MAIN && ID<=ID_BUTTON_PAGE4 && ID != ID_BUTTON_PAGE_QLCB){            
            	return;
            }
				
        	switch(ID){
	            case ID_BUTTON_PRE: //PRE DSMB PAGE
	            {
	                if (presentPage > 1)
	                {
	                    presentPage--;           
	                    updateNumOfBoardDSMB(numOfPage, presentPage,dsMB);  
	                    drawBoard(boardMB, (presentPage - 1) * 10 + ID_BOARD, mapID, shape);
	                    outDSMB(boardMB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsMB); 
	                    
					}
	                break;
	            }
				case ID_BUTTON_NEXT: //PRE DSMB PAGE
	            {
	                if (presentPage < numOfPage)
	                {
	                    presentPage++;           
	                    updateNumOfBoardDSMB(numOfPage, presentPage,dsMB);  
	                    drawBoard(boardMB, (presentPage - 1) * 10 + ID_BOARD, mapID, shape);
	                    outDSMB(boardMB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsMB); 
	                    
					}
	                break;
	            }         		
        		case ID_INPUT_SHMB_2:{
        			getInputPageQLCB(input[1], ID, isEnter);
        			if(!isEnter)
        			break;
        		}
        		case ID_BUTTON_CLOSEDSMB_2:{
        			return;
        		}
        		default:
        			break;
        	}
        	
			clearmouseclick(WM_LBUTTONDOWN);
	 
        }
        clearmouseclick(WM_LBUTTONDBLCLK);
   					
	}
	
}
void drawDSMBFrame(short **mapID, DanhSachMayBay &dsMB,Shape *shape,Input *input, Button *button){
	setfillstyle(1,WHITE);
	bar(251,0,MAX_W,130);
	setID(251,0,MAX_W - 251,130,-1,mapID);
	
	
    setText(6, 10);
    outtextxy(455, 30, "DANH SACH MAY BAY");

    Button pre_next[2] = {{640, 90, 25, 25, BLUE_L, 15, "<"}, {720, 90, 25, 25, BLUE_L, 15, ">"}};
    for (int i = 0; i < 2; i++)
    {
    
        drawButton(pre_next[i], ID_BUTTON_PRE + i, mapID);
        convertToShape(pre_next[i], shape[ID_BUTTON_PRE +i]);
    }

    Board boardMB = {275, 130, 10, 30, 4, {50, 300, 400, 150}, {"STT", "SO HIEU", "LOAI", "SO CHO"}};
    drawBoard(boardMB, ID_BOARD, mapID, shape);
    

    drawInputPageQLCB(input,mapID,false);
    drawInput(input[1],mapID,ID_INPUT_SHMB_2);
    for(int i = 0; i < 3; i++)
        drawLockButton(button[i],mapID);
        
    Button buttonCloseDSMB  = {971,570,100,30,BLUE_L,BLUE_L,"DONG DSMB"};
    	convertToShape(buttonCloseDSMB,shape[ID_BUTTON_CLOSEDSMB_2]); 
	    drawButton(buttonCloseDSMB,ID_BUTTON_CLOSEDSMB_2,mapID);
		    
	checkEventDSMBFrame(mapID, shape,dsMB, input[1], boardMB,pre_next, buttonCloseDSMB);
}

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
int main(){	
	drawMainPage();
	getch();
	return 0;
}


