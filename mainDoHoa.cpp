#include "MainPage.h"


void drawDSCBFrame(short **mapID,Shape *shape,DanhSachTam &dsTmp, Board &board_DSCB,Input *inputFill, Input *input,int &numOfPage,int &presentPage){
	setfillstyle(1,WHITE);
	bar(251,0,MAX_W,130);
	setID(251,0,MAX_W - 251,130,-1,mapID);
	
	setText(6,10);
	outtextxy(410,-10,"DANH SACH CHUYEN BAY");
	Button pre_next_Board[2] = {{640,50,25,25,BLUE_L,15,"<"},{720,50,25,25,BLUE_L,15,">"}};
	for(int i = 0;i <2;i++){
		setText(2,10,0,BLUE_L);
		drawButton(pre_next_Board[i],ID_BUTTON_PREBOARD_2+i,mapID);
		convertToShape(pre_next_Board[i],shape[i+ID_BUTTON_PREBOARD_2]);
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
    drawBoard(board_DSCB, (presentPage - 1) * 10 + ID_BOARD_DSCB_2, mapID, shape);
    outDSCB(board_DSCB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsTmp);
    
	Button button_Add_Cancel_Update_SeeDSMB[4] ={{0,0,0,0,0,0,"THEM CB"},{0,0,0,0,0,0,"HUY CB"},{0,0,0,0,0,0,"CAP NHAT"},{971,570,100,30,BLUE_L,BLUE_L,"XEM DSMB"}};
	for(int i = 0;i <4;i++){
		if(i < 3){
		button_Add_Cancel_Update_SeeDSMB[i].x1 = 455 + 180*i;
		button_Add_Cancel_Update_SeeDSMB[i].y1 = 480;
		button_Add_Cancel_Update_SeeDSMB[i].width = 160;
	    button_Add_Cancel_Update_SeeDSMB[i].height = 40;
	    button_Add_Cancel_Update_SeeDSMB[i].fillColor = BLUE_L;
	    button_Add_Cancel_Update_SeeDSMB[i].borderColor = WHITE;			
		}
        drawButton(button_Add_Cancel_Update_SeeDSMB[i], ID_BUTTON_ADD_CB_2 + i, mapID);
	}					
	drawInputPageQLCB(input,mapID,true);	
}

void checkEventDSMBFrame(short **mapID,Shape *shape, DanhSachMayBay &dsMB,Input *input,Board &board_DSMB,Button *pre_next_Board,Button &buttonCloseDSMB,bool &isreturn){
	short ID = -1, lastID = -1, chooseID = -1;
	int numOfPage = (dsMB.n - 1) / 10 + 1, presentPage = 1; 		//quan ly so trang
    short maxChoose = 0;                                              //khong cho chon vao o khong co may bay
    bool isEnter = false;
    isreturn = false;
    updateNumOfBoardDSMB(numOfPage, presentPage,dsMB);
    outDSMB(board_DSMB, 1, 10,dsMB);
    clearmouseclick(WM_LBUTTONDOWN);   
	while(true){
        delay(DELAY_TO_CHECK_EVENT);
        checkHoverPageQLMB(ID, lastID, shape, mapID);
        lastID = ID;
        if (ismouseclick(WM_LBUTTONDOWN)) {
        	//huy chon
        	if(chooseID != -1){
        		setcolor(15);
	            setfillstyle(1, 15);
	            fillellipse(shape[chooseID%10 + 50].x1 - 13, shape[chooseID%10 + 50].y1 + 10, 5, 5);
				chooseID = -1;	
        	}
            if (ID >= ID_BOARD_DSMB_1)   //chon may bay
            {	
           		maxChoose = dsMB.n - 1 + ID_BOARD_DSMB_2;
            	if(ID <= maxChoose){
	                
	                if (ID != chooseID) //CHON CAI MOI
	                {
						setcolor(0);
	                    setfillstyle(1, 0);
	                    fillellipse(shape[ID%10 + 50].x1 - 13, shape[ID%10 + 50].y1 + 10, 5, 5);	                                   
	                    chooseID = ID;
	                    strcpy(input[1].s,dsMB.mayBay[chooseID - ID_BOARD_DSMB_1] -> soHieuMayBay);
	                    input[1].lastL = strlen(input[1].s);
	                    setText(1, 10);
	                    outtextxy(input[1].x1 + 10, input[1].y1 + 5, input[1].s);
	                }
            	}
            }
			if(ID>=ID_BUTTON_PAGE_MAIN && ID<=ID_BUTTON_PAGE4 && ID != ID_BUTTON_PAGE_QLCB){            
		    	isreturn = true;
            	return;
            }
				
        	switch(ID){
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
   					
	}
	
}
void drawDSMBFrame(short **mapID, DanhSachMayBay &dsMB,Shape *shape,Input *input, Button *button, bool &isreturn){
	setfillstyle(1,WHITE);
	bar(251,0,MAX_W,130);
	setID(251,0,MAX_W - 251,130,-1,mapID);
	
	
    setText(6, 10);
    outtextxy(455, 30, "DANH SACH MAY BAY");

    Button pre_next_Board[2] = {{640, 90, 25, 25, BLUE_L, 15, "<"}, {720, 90, 25, 25, BLUE_L, 15, ">"}};
    for (int i = 0; i < 2; i++)
    {
    
        drawButton(pre_next_Board[i], ID_BUTTON_PREBOARD_2 + i, mapID);
        convertToShape(pre_next_Board[i], shape[ID_BUTTON_PREBOARD_2 +i]);
    }

    Board board_DSMB = {275, 130, 10, 30, 4, {50, 300, 400, 150}, {"STT", "SO HIEU", "LOAI", "SO CHO"}};
    drawBoard(board_DSMB, ID_BOARD_DSMB_2, mapID, shape);
    

    drawInputPageQLCB(input,mapID,false);
    drawInput(input[1],mapID,ID_INPUT_SHMB_2);
    for(int i = 0; i < 3; i++)
        drawLockButton(button[i],mapID);
        
    Button buttonCloseDSMB  = {971,570,100,30,BLUE_L,BLUE_L,"DONG DSMB"};
	    drawButton(buttonCloseDSMB,ID_BUTTON_CLOSEDSMB_2,mapID);
		    
	checkEventDSMBFrame(mapID, shape,dsMB, input, board_DSMB,pre_next_Board, buttonCloseDSMB,isreturn);
}
int main(){	
	drawMainPage();
	getch();
	return 0;
}


