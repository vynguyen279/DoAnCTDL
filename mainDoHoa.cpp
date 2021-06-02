#include "MainPage.h"
void checkEventPageQLCB(short **mapID, Shape *shape, Input *input, Button *button_Add_Cancel_Update, Board &board_DSCB){	

	DanhSachMayBay dsMB;
	layDSMayBay(dsMB);
	DanhSachChuyenBay dsCB = NULL;
	layDSChuyenBay(dsCB);
	DanhSachTam dsTmp = dsNode2DsTmp(dsCB);
	
    short ID = -1, lastID = -1, chooseID = -1;
    bool isInvalid = true;                                          //check xem du lieu can them,xoa,sua co hop le hay khong
    bool unlockChoose = true;                                       //khi dang update thi se khong cho chon may bay nua
    bool isEnter = false;                                           //check enter khi dang input
    bool unlockKeyboardShortcut = true;
    int numOfPage = (dsTmp.n - 1) / 10 + 1, presentPage = 1; 		//quan ly so trang
    short maxChoose = 0;                                              //khong cho chon vao o khong co may bay
    outNumOfBoardDSCB(numOfPage, presentPage,dsTmp);

	drawBoard(board_DSCB,ID_BOARD_DSCB_2,mapID,shape);
	outDSCB(board_DSCB, 1, 10,dsTmp);


	clearmouseclick(WM_LBUTTONDOWN);
	while(true){
		delay(DELAY_TO_CHECK_EVENT);      
		checkHoverPageQLCB(ID,lastID,shape,mapID);
		lastID = ID;			
		if(ismouseclick(WM_LBUTTONDOWN)){
			if(getpixel(725,540) == BLACK){ //xoa thong bao
				outAlert(WHITE,"");
			}
			
			//xu ly chon            
            if (ID >= ID_BOARD_DSCB_2)  
            {	
            	maxChoose = dsTmp.n - 1 + ID_BOARD_DSCB_2 ;
            	if(ID <= maxChoose){
            	
		            setcolor(0);
		            setfillstyle(1, 0);
		            if (ID != chooseID && unlockChoose) //CHON CAI MOI
		            {
		                setcolor(0);
		                setfillstyle(1, 0);
		                fillellipse(shape[ID].x1 - 13, shape[ID].y1 + 10, 5, 5);
		                if (chooseID != -1)  //BO CHON CAI CU NEU CHON CAI MOI
		                { 
		                    setcolor(15);
		                    setfillstyle(1, 15);
		                    fillellipse(shape[chooseID].x1 - 13, shape[chooseID].y1 + 10, 5, 5);
		                }
						chooseID = ID;           
		                getCBData(input,chooseID,mapID,dsCB,dsTmp);
		                    
		            }
		            else if (chooseID != -1 && ID == chooseID && unlockChoose) //NHAP VAO CAI DANG CHON DE HUY
		            { 
		                setcolor(15);
		                setfillstyle(1, 15);
		                fillellipse(shape[ID].x1 - 13, shape[ID].y1 + 10, 5, 5);
		                chooseID = -1;
		                for(int i = 0; i < 9;i++)
		                	input[i].lastL = 0;
						drawInputPageQLCB(input,mapID,true);
		                makeBeautiInputNgayGioKH(input,mapID);
		            }
            	}
            }
			//end xu ly chon			
		    if(ID>=ID_BUTTON_PAGE_MAIN && ID<=ID_BUTTON_PAGE4 && ID != ID_BUTTON_PAGE_QLCB){            
				clearDSMB(dsMB);
				clearDSCB(dsCB);
				clearDSTmp(dsTmp);
            	return;
            }		
			
			switch (ID){
            case ID_BUTTON_PREBOARD_DSCB_2: //PRE PAGE
            {
                if (presentPage > 1)
                {
                    presentPage--;
                    unlockChoose = true;
                    if(chooseID!= -1){
                     chooseID = -1;  	
                     for(int i = 0; i < 9; i++)
		            	 input[i].lastL = 0;	
                    }	
                  	drawInputPageQLCB(input,mapID,true);  			               
                    outNumOfBoardDSCB(numOfPage, presentPage,dsTmp);
                    drawBoard(board_DSCB, (presentPage - 1) * 10 + ID_BOARD_DSCB_2, mapID, shape);
                    outDSCB(board_DSCB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsTmp);
                    
            	}
                break;
            }
            case ID_BUTTON_NEXTBOARD_DSCB_2:  //NEXT PAGE
            {
                if (presentPage < numOfPage)
                {
                    presentPage++;           
                    unlockChoose = true;
                    if(chooseID!= -1){
                     chooseID = -1;  	
                     for(int i = 0; i < 9; i++)
		            	 input[i].lastL = 0;	
                    }					                  
					drawInputPageQLCB(input,mapID,true);                      
                    outNumOfBoardDSCB(numOfPage, presentPage,dsTmp);                   
                    drawBoard(board_DSCB, (presentPage - 1) * 10 + ID_BOARD_DSCB_2, mapID, shape);
                    outDSCB(board_DSCB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsTmp);
				}
                break;
            }
			case ID_BUTTON_ADD_CB_2: //THEM
			{		
                    addCB(input,isInvalid,dsMB,dsCB,dsTmp); 					                                 
                    if(isInvalid){  		                
		                outNumOfBoardDSCB(numOfPage, presentPage,dsTmp);	  				
						if (presentPage < numOfPage)
                        presentPage++;  
                    	drawBoard(board_DSCB, (presentPage - 1) * 10 + ID_BOARD_DSCB_2, mapID, shape);
	                    outDSCB(board_DSCB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsTmp);
	                    outNumOfBoardDSCB(numOfPage, presentPage,dsTmp);
						for(int i = 0; i < 9; i++)
		            	 input[i].lastL = 0;
						drawInputPageQLCB(input,mapID,true);							                    	
					}

				break;
			}
			case ID_BUTTON_CANCEL_CB_2: {	//HUY CB
				if(chooseID != -1){
					//cap nhat
					unlockChoose = false;					
					drawCancelCBFrame(mapID,shape);					
				}
				else{
					outAlert(RED,"VUI LONG CHON CHUYEN BAY!");
				}
				break;
			}
						
			case ID_BUTTON_UPDATE_CB_2:{  //CAP NHAT 
				if(chooseID!= -1)
				{  //cap nhat cb thi khong can ve lai bang
					drawUpdateCBFrame(input,mapID,shape);
				}
				else{
					outAlert(RED,"VUI LONG CHON CHUYEN BAY!");					
				}
				
				break;
			}
			case ID_BUTTON_ACPCANCEL_CB_2:{  //XAC NHAN HUY
				cancelCB(chooseID,isInvalid,dsCB,dsTmp);
                if(isInvalid){  		                
		            unlockChoose = true;
		            unlockKeyboardShortcut = true;
		            chooseID = -1;
		            resetButtonFrame(mapID);                      			
	                outNumOfBoardDSCB(numOfPage, presentPage,dsTmp);
	                if (presentPage > numOfPage)
	                    presentPage--;										
                	drawBoard(board_DSCB, (presentPage - 1) * 10 + ID_BOARD_DSCB_2, mapID, shape);
                    outDSCB(board_DSCB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsTmp);
                    outNumOfBoardDSCB(numOfPage, presentPage,dsTmp);
		            for(int i = 0; i < 9; i++){
		            	input[i].lastL = 0;	
						if(i<3)
						drawButton(button_Add_Cancel_Update[i], ID_BUTTON_ADD_CB_2 +i,mapID);	
		            }
		            drawInputPageQLCB(input,mapID,true);                      
					                    	
				}				
				break;
			}			
			case ID_BUTTON_ACPUPDATE_CB_2:{  //XAC NHAN CAP NHAT
				updateCB(input,isInvalid,chooseID,dsMB,dsCB,dsTmp);
                if(isInvalid){  		                
		            unlockChoose = true;
		            unlockKeyboardShortcut = true;	
					chooseID = -1;	
					resetButtonFrame(mapID);
                    drawBoard(board_DSCB, (presentPage - 1) * 10 + ID_BOARD_DSCB_2, mapID, shape);												
                    outDSCB(board_DSCB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsTmp);
		            for(int i = 0; i < 9; i++){
		            	input[i].lastL = 0;	
						if(i<3)
						drawButton(button_Add_Cancel_Update[i], ID_BUTTON_ADD_CB_2 +i,mapID);	
		            }
		            drawInputPageQLCB(input,mapID,false);						                    	
				}
				break;
			}
			case ID_BUTTON_UNCANCEL_CB_2: //HUY HUY
			case ID_BUTTON_UNUPDATE_CB_2:{//HUY CAP NHAT
                unlockChoose = true;
                unlockKeyboardShortcut = true;
                resetButtonFrame(mapID);
				for(int i = 0; i <3;i++)
					drawButton(button_Add_Cancel_Update[i], ID_BUTTON_ADD_CB_2 +i,mapID);
                drawInputPageQLCB(input,mapID,false);                        			
				break;
			}
						
			case ID_BUTTON_FILL_CB_2:{  //FILL
				if(chooseID!= -1)
				{
//					fillCB(input,isInvalid,chooseID,dsMB,dsCB,dsTmp);
	                outDSCB(board_DSCB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsTmp);
				}
				
				break;
			}			            
			case ID_INPUT_MCB_2:  //MA CB
            {
				getInputPageQLCB(input[0], ID, isEnter);
                if (!isEnter)
                    break;	 				
               
            }
			case ID_INPUT_SHMB_2: //SO HIEU MB
			{	
				getInputPageQLCB(input[1], ID, isEnter);
                if (!isEnter)
                    break;	 			
			}
			case ID_INPUT_DAY_2: // NGAY
            {
				getInputPageQLCB(input[2], ID, isEnter);
                if (!isEnter)
                    break;	                
            }
			case ID_INPUT_MONTH_2 : //THANG
			{
				getInputPageQLCB(input[3], ID, isEnter);
                if (!isEnter)
                    break;	 			
			}  
			case ID_INPUT_YEAR_2: //NAM
            {
				getInputPageQLCB(input[4], ID, isEnter);
				if(input[2].lastL!= 0 && input[3].lastL != 0 && input[4].lastL !=0)  //fix lai ngay neu nguoi dung nhap nam nhuan
						fixNgay(input,mapID);	
                if (!isEnter)
                    break;	               
            }
			case ID_INPUT_HOUR_2: //GIO
            {
				getInputPageQLCB(input[5], ID, isEnter);
                if (!isEnter)
                    break;	                 
            }
			case ID_INPUT_MINUTE_2: //PHUT
            {
				getInputPageQLCB(input[6], ID, isEnter);
				if(ID == ID_INPUT_STATUS_2) ID++;  //nhay den input SAN BAY DEN khi chua chon cb nao
				if(isEnter){
				if (mapID[580][500] == ID_BUTTON_ACPUPDATE_CB_2){
					updateCB(input,isInvalid,chooseID,dsMB,dsCB,dsTmp);
		            if(isInvalid){  		                
			            unlockChoose = true;
			            unlockKeyboardShortcut = true;		
						resetButtonFrame(mapID);							
		                outDSCB(board_DSCB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsTmp);
			            for(int i = 0; i < 3; i++){
							drawButton(button_Add_Cancel_Update[i], ID_BUTTON_ADD_CB_2 +i,mapID);	
			            }
			            drawInputPageQLCB(input,mapID,false);						                    	
					}
					break;
					}
				}
                else
                    break;	                
            }
			case ID_INPUT_DESTINATION_2: //SAN BAY DEN
            {   
				getInputPageQLCB(input[8], ID, isEnter);
                if (isEnter){                 	//neu enter thi thuc hien them chuyen bay 
                	isEnter = false;
                    addCB(input,isInvalid,dsMB,dsCB,dsTmp); 					                                 
                    if(isInvalid){  		                
		                outNumOfBoardDSCB(numOfPage, presentPage,dsTmp);  				
						if (presentPage < numOfPage)
                        presentPage++;  
                    	drawBoard(board_DSCB, (presentPage - 1) * 10 + ID_BOARD_DSCB_2, mapID, shape);
	                    outDSCB(board_DSCB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsTmp);
	                    outNumOfBoardDSCB(numOfPage, presentPage,dsTmp);	                    	
					}
                }

                else
                    break;	
            }									            
						               
            default:
            	break;

			}
            if(ID >= ID_BUTTON_CANCEL_CB_2 && ID <= ID_BUTTON_UNUPDATE_CB_2){ //fix loi hover
				ID = -1;
				lastID = -1;
			}			
			clearmouseclick(WM_LBUTTONDOWN);
		}
		
	}


}

void drawPageQLCB(short **mapID,Shape *shape){

	setDefaultRightFrame(mapID);	
	
	//chuc nang phim tat
	setText(5, 2, 0, BLUE_M);
    setfillstyle(1, BLUE_M);
    bar(0, 550, 250, MAX_H);
    outtextxy(70, 610, "DELETE   : XOA");
    rectangle(65,605,120,625);
    outtextxy(70, 640, "F1   : CAP NHAT");
	rectangle(65,635,85,655);
	
	setText(6,10);
	outtextxy(410,-10,"DANH SACH CHUYEN BAY");
	Button pre_next_Board[2] = {{640,50,25,25,BLUE_L,15,"<"},{720,50,25,25,BLUE_L,15,">"}};
	for(int i = 0;i <2;i++){
		setText(2,10,0,BLUE_L);
		drawButton(pre_next_Board[i],ID_BUTTON_PREBOARD_DSCB_2+i,mapID);
		convertToShape(pre_next_Board[i],shape[i+ID_BUTTON_PREBOARD_DSCB_2]);
	}

		
	Board board_DSCB = {275,130,10,30,5,{125,125,180,350,120},{"MA CB","SO HIEU MB","NGAY GIO KHOI HANH","SAN BAY DEN","TRANG THAI"}};
	
	setcolor(0);
    rectangle(275, 470, 1175, MAX_H);  
	Button button_Add_Cancel_Update[4] ={{0,0,0,0,0,0,"THEM CB"},{0,0,0,0,0,0,"HUY CB"},{0,0,0,0,0,0,"CAP NHAT"}};
	for(int i = 0;i <3;i++){
		setText(1,11,0,BLUE_L);
		button_Add_Cancel_Update[i].x1 = 455 + 180*i;
		button_Add_Cancel_Update[i].y1 = 480;
		button_Add_Cancel_Update[i].width = 160;
	    button_Add_Cancel_Update[i].height = 40;
	    button_Add_Cancel_Update[i].fillColor = BLUE_L;
	    button_Add_Cancel_Update[i].borderColor = WHITE;
        drawButton(button_Add_Cancel_Update[i], ID_BUTTON_ADD_CB_2 + i, mapID);
        convertToShape(button_Add_Cancel_Update[i], shape[i+ID_BUTTON_ADD_CB_2]);
	}
		
	Input input[9] = {
	{450,570,15,190,0},  // ma cb
	{780,570,15,190,0},	//so hieu
	{450,605,2,45,0},	//ngay
	{500,605,2,45,0},	//thang
	{550,605,4,80,0},	//nam
	{650,605,2,45,0},	//gio
	{700,605,2,45,0},	//phut
	{845,605,10,125,0},	//trang thai
	{450,640,40,520,0},	//san bay den
	};
	
	setText();
	outtextxy(400,575,"MA CB:");
	outtextxy(720,575,"SO HIEU:");
	outtextxy(352,610,"NGAY GIO K.H:");	
	outtextxy(755,610,"TRANG THAI:");
	outtextxy(350,645,"SAN BAY DEN:");
	for(int i = 0; i< 9;i++){
	input[i].s = new char[input[i].max+2];	
	convertToShape(input[i],shape[i+ID_INPUT_MCB_2]);
	}
	drawInputPageQLCB(input,mapID,true);
	

	Input inputFill[4] = {
	{275,97,2,45,0},	//ngay
	{325,97,2,45,0},	//thang
	{375,97,4,80,0},	//nam	
	{606,97,40,450,0},	//san bay den	
	};
	setText();
	outtextxy(275,80,"NGAY GIO K.H:");	
	outtextxy(506,101,"SAN BAY DEN:");
	Button buttonFill[4]= {{1110,60,65,30,BLUE_L,WHITE,"BO LOC"},{456,97,30,30,BLUE_L,WHITE,"X"},{1057,97,30,30,BLUE_L,WHITE,"X"},{1110,97,65,30,BLUE_L,WHITE,"HUY LOC"}};
	for(int i = 0; i< 4;i++){
	inputFill[i].s = new char[input[i].max+2];	
	drawInput(inputFill[i],mapID,i+ID_INPUT_FILLTIME_2);
	convertToShape(inputFill[i],shape[i+ID_INPUT_FILLTIME_2]);	
	drawButton(buttonFill[i],ID_BUTTON_UNFILLTIME_CB_2 + i,mapID);
	convertToShape(buttonFill[i],shape[i+ID_BUTTON_UNFILLTIME_CB_2]);	
	}
	setfillstyle(1,15);
	setText(1, 10);
	bar(inputFill[0].x1,inputFill[0].y1,inputFill[2].x1+inputFill[2].width,inputFill[2].y1+30);
	rectangle(inputFill[0].x1,inputFill[0].y1,inputFill[2].x1+inputFill[2].width,inputFill[2].y1+30);
		
	outtextxy(316,102,"/");
	outtextxy(366,102,"/");	

	
	for(int i = 0; i<=2;i++){
		if(inputFill[i].lastL != 0)
		outtextxy(inputFill[i].x1 + 7,inputFill[i].y1 + 5,inputFill[i].s);
	}	
	setfillstyle(1,BLACK);
	checkEventPageQLCB(mapID,shape,input,button_Add_Cancel_Update,board_DSCB);
	for (int i = 0; i < 9; i++)
	    delete[] input[i].s;		
}
int main(){	
	drawMainPage();
	getch();
	return 0;
}

Button button1 = {x1,y1,width,height,...};
setID(button1.x1,button1.y1,button.width,button.height,ID,mapID);



