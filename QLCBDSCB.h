#pragma once
#include "reuse.h" 
//====================PROTOTYPE==================
void checkEventDSMBFrame(short **mapID,Shape *shape, DanhSachMayBay &dsMB,Input &inputSHMB,Board &boardMB,Button *pre_next,Button &buttonCloseDSMB);
void drawDSMBFrame(short **mapID, DanhSachMayBay &dsMB,Shape *shape,Input *input, Button *button);
void drawDSCBFrame(short **mapID,Shape *shape,DanhSachTam &dsTmp, Board &boardCB,Input *inputFill, Input *input,int &numOfPage,int &presentPage, Button *pre_next,Button *buttonFill,Button *mainButton);
void addCB(Input *input,bool &isInvalid, DanhSachMayBay &dsMB,DanhSachChuyenBay &dsCB,DanhSachTam &dsTmp);
void checkEventPageQLCB(short **mapID, Shape *shape, Input *input, Button *mainButton, Board &boardCB,Button *buttonFill,Input *inputFill,Button *pre_next);
void checkHoverPageQLCB(short &ID, short lastID, Shape *shape, short **mapID);
void chuanHoaInputQLCB(Input &input,short inputID);
void cancelCB(short ID,bool &isInvalid,DanhSachChuyenBay &dsCB,DanhSachTam &dsTmp);
void drawPageQLCB_DSCB(short **mapID,Shape *shape);
void drawInputPageQLCB(Input *input,short **mapID,bool unlockInput );
void drawUpdateCBFrame(Input *input,short **mapID,Shape *shape);
void drawCancelCBFrame(short **mapID, Shape *shape);
void fillCB(Input *input,bool &isInvalid,DanhSachChuyenBay &dsCB, DanhSachTam &dsFill);
void fixNgay(Input *input);
void fixNgayFill(Input *input);
void getCBData(Input *input,short chooseID,DanhSachChuyenBay &dsCB,DanhSachTam &dsTmp);
void getInputPageQLCB(Input &input, short &inputID, bool &isEnter);
void lockPageQLCB(Button *pre_next, Button *fill,Button &seeDSMB,short **mapID);
void makeBeautiInputNgayGioKH(Input *input);
void makeBeautiLockInputNgayGioKH(Input *input);
void makeBeautiFillInput(Input *input);
void outDSCB(Board &board, int startCB, int endCB,DanhSachTam &dsTmp);
void outCB(Board &board,DanhSachTam &dsTmp, short ID);
void outCBUpdated(Board &board,DanhSachTam &dsTmp,short ID);
void updateNumOfBoardDSCB(int &numOfPage, int presentPage,DanhSachTam &dsTmp);
void updateCB(Input *input,bool &isInvalid,short chooseID,DanhSachChuyenBay &dsCB,DanhSachTam &dsTmp);
void unChooseCB(Input *input, short &chooseID,bool &unlockChoose, Shape *shape, short **mapID);
void unlockPageQLCB(Button *pre_next, Button *fill,Button &seeDSMB,short **mapID);
//================================================

void checkEventPageQLCB(short **mapID, Shape *shape, Input *input, Button *mainButton, Board &boardCB,Button *buttonFill,Input *inputFill,Button *pre_next){	

	DanhSachMayBay dsMB;
	layDSMayBay(dsMB);
	DanhSachChuyenBay dsCB = NULL;
	layDSChuyenBay(dsCB);
	DanhSachTam dsFill; 
	DanhSachTam dsDefault = dsNode2DsTmp(dsCB);
	DanhSachTam dsTmp = dsDefault;                                  
    short ID = -1, lastID = -1, chooseID = -1;
    bool isInvalid = true;                                          //check xem du lieu can them,xoa,sua co hop le hay k
    bool unlockChoose = true;                                       //khi dang update hay del thi k cho chon may bay
    bool isEnter = false;                                           //check enter khi dang input
    bool isFill = false;                                            //quan ly fill
    int numOfPage = (dsTmp.n - 1) / 10 + 1, presentPage = 1; 		//quan ly so trang
    short maxChoose = 0;                                            //khong cho chon vao o khong co may bay
    updateNumOfBoardDSCB(numOfPage, presentPage,dsTmp);
    
	outDSCB(boardCB, 1, 10,dsTmp);
	clearmouseclick(WM_LBUTTONDOWN);
	clearmouseclick(WM_LBUTTONDBLCLK);
	while(true){
		delay(DELAY_TO_CHECK_EVENT);      
		checkHoverPageQLCB(ID,lastID,shape,mapID);
		lastID = ID;
        if(ismouseclick(WM_LBUTTONDBLCLK) && chooseID != -1 && ID == chooseID){
				return;
        }	
		if(ismouseclick(WM_LBUTTONDOWN)){
			if(getpixel(725,540) == BLACK){ //xoa thong bao
				outAlert(WHITE,"");
			}
			
			//xu ly chon            
            if (ID >= ID_BOARD)  
            {	
                maxChoose = dsTmp.n - 1 + ID_BOARD ;
            	if(ID <= maxChoose){
        
		            if (ID != chooseID && unlockChoose) //CHON CB MOI
		            {
		            	//to  
		                setcolor(0);
		                setfillstyle(1, 0);
		                fillellipse(shape[ID%10 + 50].x1 - 13, shape[ID%10 + 50].y1 + 10, 5, 5);
		                if (chooseID != -1)  //BO CHON CB CU NEU CHON CB MOI
		                { 
		            
		                    setcolor(15);
		                    setfillstyle(1, 15);
		                    fillellipse(shape[chooseID%10 + 50].x1 - 13, shape[chooseID%10 + 50].y1 + 10, 5, 5);
		                }
						chooseID = ID;   
		                getCBData(input,chooseID,dsCB,dsTmp);	                	
		                drawInputPageQLCB(input,mapID,false);
		                lockPageQLCB(pre_next,buttonFill,mainButton[3],mapID);	
		                    
		            }
		            else if (chooseID != -1 && ID == chooseID && unlockChoose) //HUY CHON NEU CLICK VAO CB DANG CHON
		            { 
						unChooseCB(input,chooseID,unlockChoose,shape,mapID);
						unlockPageQLCB(pre_next,buttonFill,mainButton[3],mapID);
		            }
            	}
            }
			//======================================================		
		
			
			switch (ID){
            case ID_BUTTON_PRE: //PRE PAGE
            {
                if (presentPage > 1)
                {
                    presentPage--;         			               
                   	updateNumOfBoardDSCB(numOfPage, presentPage,dsTmp);
                    drawBoard(boardCB, (presentPage - 1) * 10 + ID_BOARD, mapID, shape);
                    outDSCB(boardCB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsTmp);
                    
            	}
                break;
            }
            case ID_BUTTON_NEXT:  //NEXT PAGE
            {
                if (presentPage < numOfPage)
                {
                	
                    presentPage++;  	                			               
                   	updateNumOfBoardDSCB(numOfPage, presentPage,dsTmp);					         					                                       
                    drawBoard(boardCB, (presentPage - 1) * 10 + ID_BOARD, mapID, shape);
                    outDSCB(boardCB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsTmp);
				}
                break;
            }
			case ID_BUTTON_FILL_CB_2:{  //FILL
				fillCB(inputFill,isInvalid,dsCB,dsFill);
				if(isInvalid){
				presentPage = 1;
				isFill = true;
				dsTmp = dsFill;
                updateNumOfBoardDSCB(numOfPage, presentPage,dsTmp);                   
                drawBoard(boardCB, (presentPage - 1) * 10 + ID_BOARD, mapID, shape);
                outDSCB(boardCB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsTmp);	
											
				}
				break;
			}
			case ID_BUTTON_UNFILL_CB_2:{  //UNFILL
				if(isFill){
				presentPage = 1;
				isFill = false;
				dsTmp = dsDefault;	
                updateNumOfBoardDSCB(numOfPage, presentPage,dsTmp);                   
                drawBoard(boardCB, (presentPage - 1) * 10 + ID_BOARD, mapID, shape);
                outDSCB(boardCB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsTmp);
				for(int i = 0; i <4; i++){
					inputFill[i].lastL = 0;
					drawInput(inputFill[i],mapID,ID_INPUT_FILLTIMED_2 + i);
				}
				makeBeautiFillInput(inputFill);								
				}

				break;
			}
			case ID_BUTTON_UNFILLTIME_CB_2:{  // UNFILLTIME
				for(int i = 0; i < 3; i++){					
					inputFill[i].lastL = 0;
				}
				makeBeautiFillInput(inputFill);	
				break;
			}
			case ID_BUTTON_UNFILLDESTINATION_CB_2:{  //UNFILLDES
				if(inputFill[3].lastL != 0)
				{
					inputFill[3].lastL = 0;
					drawInput(inputFill[3],mapID,ID_INPUT_FILLDESTINATION_2);
				}
				break;
			}            
			case ID_BUTTON_ADD_CB_2: //THEM CB
			{		

                    addCB(input,isInvalid,dsMB,dsCB,dsDefault); 
										                                 
                    if(isInvalid){
                    	dsTmp = dsDefault;
						if(isFill){ 
							//huy fill
							isFill = false;
							presentPage = 1;	
							for(int i = 0; i <4; i++){
								inputFill[i].lastL = 0;
								drawInput(inputFill[i],mapID,ID_INPUT_FILLTIMED_2 + i);
							}
							makeBeautiFillInput(inputFill);							
						}
												 		                
		                updateNumOfBoardDSCB(numOfPage, presentPage,dsTmp);
		                
						if(presentPage == numOfPage){  //neu cung trang thi in ra cb moi them vao cuoi ds
							outCB(boardCB,dsTmp,dsTmp.n -1);
						}
						else{
		                    presentPage = numOfPage; 
		                	drawBoard(boardCB, (presentPage - 1) * 10 + ID_BOARD, mapID, shape);
		                    outDSCB(boardCB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsTmp);
							updateNumOfBoardDSCB(numOfPage, presentPage,dsTmp);							
						} 	  				

						for(int i = 0; i < 9; i++)
		            		input[i].lastL = 0;
						drawInputPageQLCB(input,mapID,true);							                    	
					}

				break;
			}
			case ID_BUTTON_CANCEL_CB_2: {	//HUY CB
				if(chooseID != -1){
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
				{
					unlockChoose = false;
					drawUpdateCBFrame(input,mapID,shape);
				}
				else{
					outAlert(RED,"VUI LONG CHON CHUYEN BAY!");					
				}
				
				break;
			}
			case ID_BUTTON_SEEDSMB_2:{  //XEM DSMB
				drawDSMBFrame(mapID,dsMB,shape,input,mainButton);
				getIDMouseClick(ID,mapID);
			}
			case ID_BUTTON_CLOSEDSMB_2:{  //DONG DSMB
				if(ID > ID_BUTTON_PAGE4)
				drawDSCBFrame(mapID,shape,dsTmp,boardCB,inputFill,input,numOfPage,presentPage,pre_next,buttonFill,mainButton);
				break;
			}						
			case ID_BUTTON_ACPCANCEL_CB_2:{  //XAC NHAN HUY
				cancelCB(chooseID,isInvalid,dsCB,dsTmp);		
                if(isInvalid){
				  		                
                    outCBUpdated(boardCB,dsTmp,chooseID);                  
		            unlockPageQLCB(pre_next,buttonFill,mainButton[3],mapID);
					unChooseCB(input,chooseID,unlockChoose,shape,mapID);  		            
                    resetButtonFrame(mapID); 
		            for(int i = 0; i < 3; i++){
						drawButton(mainButton[i], ID_BUTTON_ADD_CB_2 +i,mapID);	
		            }                    					                    	
				}				
				break;
			}			
			case ID_BUTTON_ACPUPDATE_CB_2:{  //LUU CAP NHAT
				
				updateCB(input,isInvalid,chooseID,dsCB,dsTmp);
                if(isInvalid){
 		            
		            outCBUpdated(boardCB,dsTmp,chooseID);
		            unlockPageQLCB(pre_next,buttonFill,mainButton[3],mapID);
					unChooseCB(input,chooseID,unlockChoose,shape,mapID);     
                    resetButtonFrame(mapID);
  		            for(int i = 0; i < 3; i++){
						drawButton(mainButton[i], ID_BUTTON_ADD_CB_2 +i,mapID);	
		            }  						                    	
				}
				break;
			}
			case ID_BUTTON_UNCANCEL_CB_2: //HUY HUY CB
			case ID_BUTTON_UNUPDATE_CB_2:{//HUY CAP NHAT
                unlockChoose = true;
                
                resetButtonFrame(mapID);
				for(int i = 0; i <3;i++)
					drawButton(mainButton[i], ID_BUTTON_ADD_CB_2 +i,mapID);
				getCBData(input,chooseID,dsCB,dsTmp);				            
                if(chooseID != -1)
                    getCBData(input,chooseID,dsCB,dsTmp);
                drawInputPageQLCB(input,mapID,false);                        			
				break;
			}
						
			case ID_INPUT_FILLTIMED_2:{  //FILL DAY
				getInputPageQLCB(inputFill[0],ID,isEnter);
				if(inputFill[0].lastL * inputFill[1].lastL * inputFill[2].lastL !=0)   //fix lai ngay trong fill neu la nam nhuan
					fixNgayFill(inputFill);
				if (!isEnter)
                    break;				
			
			}
			case ID_INPUT_FILLTIMEM_2:{  //FILL MONTH
				getInputPageQLCB(inputFill[1],ID,isEnter);
				if(inputFill[0].lastL * inputFill[1].lastL * inputFill[2].lastL !=0)   
					fixNgayFill(inputFill);				
				if (!isEnter)
                    break;
			}
			case ID_INPUT_FILLTIMEY_2:{  //FILL YEAR
				getInputPageQLCB(inputFill[2],ID,isEnter);
				if(inputFill[0].lastL * inputFill[1].lastL * inputFill[2].lastL !=0)   
					fixNgayFill(inputFill);					
				if (!isEnter)
                    break;
			}
			case ID_INPUT_FILLDESTINATION_2:{  //FILL DESTINATION
				getInputPageQLCB(inputFill[3],ID,isEnter);
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
			    if(input[2].lastL * input[3].lastL * input[4].lastL !=0) //fix lai ngay neu la nam nhuan
				fixNgay(input);					
                if (!isEnter)
                    break;	                
            }
			case ID_INPUT_MONTH_2 : //THANG
			{
				getInputPageQLCB(input[3], ID, isEnter);
			    if(input[2].lastL * input[3].lastL * input[4].lastL !=0) 
				fixNgay(input);					
                if (!isEnter)
                    break;	 			
			}  
			case ID_INPUT_YEAR_2: //NAM
            {
				getInputPageQLCB(input[4], ID, isEnter);
			    if(input[2].lastL * input[3].lastL * input[4].lastL !=0)
				fixNgay(input);					
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
				if(isEnter && chooseID == -1){
					
				}
				else 
				 break;
                
            }
			case ID_INPUT_DESTINATION_2: //SAN BAY DEN
            {   
				getInputPageQLCB(input[8], ID, isEnter);
                break;	
            }									            
						               
            default:
            	break;

			}
			
		    if((ID>=ID_BUTTON_PAGE_MAIN && ID<=ID_BUTTON_PAGE4 && ID != ID_BUTTON_PAGE_QLCB)){            
				clearDSMB(dsMB);
				clearDSCB(dsCB);
				clearDSTmp(dsFill);
				clearDSTmp(dsDefault);
            	return;
            }		
            if(ID >= ID_BUTTON_CANCEL_CB_2 && ID <= ID_BUTTON_UNUPDATE_CB_2){ //FIX LOI HOVER
				ID = -1;
				lastID = -1;
			}			
			clearmouseclick(WM_LBUTTONDOWN);
		}
		clearmouseclick(WM_LBUTTONDBLCLK);

	}
}
void drawPageQLCB_DSCB(short **mapID,Shape *shape){

	setDefaultRightFrame(mapID);	
	
	setText(6,10);
	outtextxy(410,-10,"DANH SACH CHUYEN BAY");
	Button pre_next[2] = {{640,50,25,25,BLUE_L,BLUE_L,"<"},{720,50,25,25,BLUE_L,BLUE_L,">"}};
	for(int i = 0;i <2;i++){
		drawButton(pre_next[i],ID_BUTTON_PRE+i,mapID);
		convertToShape(pre_next[i],shape[i+ID_BUTTON_PRE]);
	}

	setText();
	outtextxy(275,80,"NGAY GIO K.H:");	
	outtextxy(506,101,"SAN BAY DEN:");	
	Input inputFill[4] = {
	{275,97,2,45,0},	//ngay
	{325,97,2,45,0},	//thang
	{375,97,4,80,0},	//nam	
	{606,97,40,450,0},	//san bay den	
	};
	Button buttonFill[4]= {
	{1105,60,70,30,BLUE_L,WHITE,"BO LOC"},
	{456,97,30,30,BLUE_L,BLUE_L,"X"},
	{1057,97,30,30,BLUE_L,BLUE_L,"X"},
	{1105,97,70,30,BLUE_L,WHITE,"HUY LOC"}
	};
	for(int i = 0; i< 4;i++){
	inputFill[i].s = new char[inputFill[i].max+2];	
	drawInput(inputFill[i],mapID,i+ID_INPUT_FILLTIMED_2);
	convertToShape(inputFill[i],shape[i+ID_INPUT_FILLTIMED_2]);	
	drawButton(buttonFill[i],ID_BUTTON_FILL_CB_2 + i,mapID);
	convertToShape(buttonFill[i],shape[i+ID_BUTTON_FILL_CB_2]);	
	}
	makeBeautiFillInput(inputFill);
	
		
	Board boardCB = {275,130,10,30,5,{125,125,180,350,120},{"MA CB","SO HIEU MB","NGAY GIO KHOI HANH","SAN BAY DEN","TRANG THAI"}};
	drawBoard(boardCB,ID_BOARD,mapID,shape);	
	setcolor(0);
    rectangle(275, 470, 1175, MAX_H);  
    
	Button mainButton[4] ={
	{0, 0,160,40,BLUE_L,BLUE_L,"THEM CB"},
	{0, 0,160,40,BLUE_L,BLUE_L,"HUY CB"},
	{0, 0,160,40,BLUE_L,BLUE_L,"CAP NHAT"},
	{971,570,100,30,BLUE_L,BLUE_L,"XEM DSMB"}
	};

	for(int i = 0;i <4;i++){
		if(i < 3){
		mainButton[i].x1 = 455 + 180*i;
		mainButton[i].y1 = 480;			
		}
        drawButton(mainButton[i], ID_BUTTON_ADD_CB_2 + i, mapID);
        convertToShape(mainButton[i], shape[i+ID_BUTTON_ADD_CB_2]);
	}


	setText();
	outtextxy(400,575,"MA CB:");
	outtextxy(720,575,"SO HIEU:");
	outtextxy(352,610,"NGAY GIO K.H:");	
	outtextxy(755,610,"TRANG THAI:");
	outtextxy(350,645,"SAN BAY DEN:");	
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
	for(int i = 0; i< 9;i++){
	input[i].s = new char[input[i].max+2];	
	convertToShape(input[i],shape[i+ID_INPUT_MCB_2]);
	}
	drawInputPageQLCB(input,mapID,true);
	
	
	checkEventPageQLCB(mapID,shape,input,mainButton,boardCB,buttonFill,inputFill,pre_next);
	for (int i = 0; i < 9; i++){
		if(i<4)
			delete[] inputFill[i].s;
		delete[] input[i].s;
	}
	    		
}


//==========================DSMB===================================
void checkEventDSMBFrame(short **mapID,Shape *shape, DanhSachMayBay &dsMB,Input &inputSHMB,Board &boardMB,Button *pre_next,Button &buttonCloseDSMB){
	short ID = -1,lastID = -1, chooseID = -1;
	int numOfPage = (dsMB.n - 1) / 10 + 1, presentPage = 1; 
    short maxChoose = 0;                                             
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
	                    strcpy(inputSHMB.s,dsMB.mayBay[chooseID - ID_BOARD] -> soHieuMayBay);
	                    inputSHMB.lastL = strlen(inputSHMB.s);
	                    setText(1, 10);
	                    setfillstyle(1,WHITE);
						bar(inputSHMB.x1+1,inputSHMB.y1+1,inputSHMB.x1 + inputSHMB.width -1,inputSHMB.y1+29) ;
	                    outtextxy(inputSHMB.x1 + 10, inputSHMB.y1 + 5, inputSHMB.s);
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
        			getInputPageQLCB(inputSHMB, ID, isEnter);
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

    Button pre_next[2] = {{640, 90, 25, 25, BLUE_L, BLUE_L, "<"}, {720, 90, 25, 25, BLUE_L, BLUE_L, ">"}};
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

//==========================END===================================

void getInputPageQLCB(Input &input, short &inputID, bool &isEnter)
{
	int paddingLeft = 7;
	if(isEnter){ //INHOVER
		setcolor(BLACK);
        if((ID_INPUT_DAY_2 <= inputID && inputID <= ID_INPUT_MINUTE_2) || (inputID <= ID_INPUT_FILLTIMEY_2 && inputID >= ID_INPUT_FILLTIMED_2)){  //NGAY GIO CO KIEU HOVER KHAC          
            rectangle(input.x1 + 1, input.y1 + 28, input.x1 + input.width -1, input.y1+29);       	  
		}
        else        
		{
            rectangle(input.x1+1, input.y1 +1, input.x1 + input.width -1 , input.y1 + 29);
        }
	}
		
    isEnter = false;
    while (kbhit()) //NUOT PHIM
       char c = getch(); 
    setText(1, 10);
    input.s[input.lastL] = '|';
    input.s[input.lastL + 1] = '\0';   
    clearmouseclick(WM_LBUTTONDOWN);
    
    while (1)
    {
        outtextxy(input.x1 + paddingLeft, input.y1 + 5, input.s);
        delay(DELAY_TO_CHECK_EVENT);
        if (ismouseclick(WM_LBUTTONDOWN))
        { //CLICK trong khi nhap

	        //OUTHOVER
			setcolor(WHITE);
		    if((ID_INPUT_DAY_2 <= inputID && inputID <= ID_INPUT_MINUTE_2) || (inputID <= ID_INPUT_FILLTIMEY_2 && inputID >= ID_INPUT_FILLTIMED_2)){  //NGAY GIO CO KIEU HOVER KHAC          
		        rectangle(input.x1 + 1, input.y1 + 28, input.x1 + input.width - 1, input.y1+29);       	  
			}
		    else        
			{
		        rectangle(input.x1+1, input.y1 +1, input.x1 + input.width -1 , input.y1 + 29);
		    } 
			chuanHoaInputQLCB(input,inputID); 
			setcolor(BLACK);
    		outtextxy(input.x1 + paddingLeft, input.y1 + 5, input.s);			
            break;
        }        
        if (kbhit())
        {
            char c = getch();
            if (c == 13)
            { //ENTER khi nhap
                isEnter = true;
                
                //OUTHOVER
				setcolor(WHITE);
			    if((ID_INPUT_DAY_2 <= inputID && inputID <= ID_INPUT_MINUTE_2) || (inputID <= ID_INPUT_FILLTIMEY_2 && inputID >= ID_INPUT_FILLTIMED_2)){  //NGAY GIO CO KIEU HOVER KHAC          
			        rectangle(input.x1 + 1, input.y1 + 28, input.x1 + input.width - 1, input.y1+29);       	  
				}
			    else        
				{
			        rectangle(input.x1+1, input.y1 +1, input.x1 + input.width -1 , input.y1 + 29);
			    }                
 				chuanHoaInputQLCB(input,inputID);
 				setcolor(BLACK);
 				outtextxy(input.x1 + paddingLeft, input.y1 + 5, input.s);
            	inputID+=1;
            break;
            }
            if (('a' <= c && c <= 'z' || '0' <= c && c <= '9' || (c == ' ' && input.s[input.lastL - 1] != ' ' && input.lastL != 0)) && input.lastL < input.max)
            {
                if ((((inputID == ID_INPUT_MCB_2 ||inputID == ID_INPUT_SHMB_2)  && c != ' ') || inputID == ID_INPUT_DESTINATION_2 || inputID == ID_INPUT_FILLDESTINATION_2)&& input.lastL < input.max - 1 )
                { //may bay,so hieu,san bay den
                    if ('a' <= c && c <= 'z')
                    {
                        input.s[input.lastL] = c - ('a' - 'A');
                        input.lastL++;
                        input.s[input.lastL + 1] = '\0';
                    }
                    else
                    {
                        input.s[input.lastL] = c;
                        input.lastL++;
                        input.s[input.lastL + 1] = '\0';
                    }
                }
                else if (((ID_INPUT_DAY_2 <= inputID && inputID <= ID_INPUT_MINUTE_2) ||(ID_INPUT_FILLTIMED_2 <= inputID && inputID <= ID_INPUT_FILLTIMEY_2))  && '0' <= c && c <= '9')
                { //ngay-thang-nam
                    
                        input.s[input.lastL] = c;
                        input.lastL++;
                        input.s[input.lastL + 1] = '\0';
                        
                    outtextxy(input.x1 + paddingLeft, input.y1 +5, input.s);
                }
                
            }
            else if (c == 8 && input.lastL != 0) //bat phim backspace
            {   
				input.lastL--;
                input.s[input.lastL] = '|';
                input.s[input.lastL+1] = ' ';
                outtextxy(input.x1 + paddingLeft, input.y1 + 5, input.s);
                input.s[input.lastL+1] = '\0';
            }
        }
        else //con tro nhap nhay
        { 
            setcolor(0);
            input.s[input.lastL] = '|';
            delay(100);
            outtextxy(input.x1 + paddingLeft, input.y1 + 5, input.s);
            input.s[input.lastL] = ' ';
            delay(100);
            outtextxy(input.x1 + paddingLeft, input.y1 + 5, input.s);
        }
    }
}

void fillCB(Input *input,bool &isInvalid,DanhSachChuyenBay &dsCB, DanhSachTam &dsFill){
	bool isFillTime = true;
	bool isFillDestination = true;
	for(int i = 0; i<3;i++){
		if(input[i].lastL == 0)
			isFillTime = false;
	}
	if(input[3].lastL == 0)
		isFillDestination = false;
		
	if(isFillTime && isFillDestination){ //thoi gian va dia diem		
		NgayThangNam dtFill = newNgayThangNam(atoi(input[0].s), atoi(input[1].s), atoi(input[2].s));
        dsFill = dsCBvoiNgayKhoiHanhVaSanBayDen(input[3].s, dtFill,dsCB);
		isInvalid = true;
	}
	else if(isFillDestination){//dia diem	
	
		dsFill=dsCBvoiSanBayDen(input[3].s,dsCB);

		isInvalid = true;
	}
	else if(isFillTime){ //thoi gian
		
		NgayThangNam dtFill = newNgayThangNam(atoi(input[0].s), atoi(input[1].s), atoi(input[2].s));	
		dsFill = dsCBvoiNgayKhoiHanh(dtFill, dsCB);
		isInvalid = true;
		
	}
	else{
		isInvalid = false;
	}
	
}
void addCB(Input *input,bool &isInvalid, DanhSachMayBay &dsMB,DanhSachChuyenBay &dsCB,DanhSachTam &dsTmp)
{	
	isInvalid = true;	
	char alert[255];
	for(int i = 0; i < 9;i++){
		if(input[i].lastL ==0 ){
			isInvalid = false;
			strcpy(alert,"BAN CHUA NHAP DU THONG TIN!");
		}
	}
	if(isInvalid){
	NgayThangNam ngayKH = newNgayThangNam(atoi(input[2].s), atoi(input[3].s), atoi(input[4].s), atoi(input[5].s), atoi(input[6].s));
	ChuyenBay newCB = newChuyenBay(input[0].s,ngayKH, input[8].s, input[1].s);
	NodeChuyenBay *newNodeCB = newNodeChuyenBay(newCB);
	isInvalid = themChuyenBayHopLe(newNodeCB,dsCB, dsMB, dsTmp, alert);		
	}
	if(isInvalid) {
		luuDSChuyenBay(dsCB);
		outAlert(GREEN,alert);
	}
	else outAlert(RED,alert);	
			
}

void cancelCB(short chooseID,bool &isInvalid,DanhSachChuyenBay &dsCB,DanhSachTam &dsTmp){
	char alert[255];
    
	short ID=chooseID - ID_BOARD;  //lay ra ID cua CB trong dsCB
	isInvalid = huyChuyenBay(dsTmp.cb[ID],alert);	
	if(isInvalid){
		luuDSChuyenBay(dsCB);
		outAlert(GREEN,alert);
	}
	else outAlert(RED,alert);
	
}



void drawCancelCBFrame(short **mapID, Shape *shape)
{
	resetButtonFrame(mapID);
    Button del[2] = {{520, 480, 160, 40, BLUE_L, 15, "XAC NHAN"}, {740, 480, 160, 40, BLUE_L, 15, "HUY"}};
    for (int i = 0; i < 2; i++)
    {
        
        drawButton(del[i], ID_BUTTON_ACPCANCEL_CB_2 + i, mapID);
        convertToShape(del[i], shape[ID_BUTTON_ACPCANCEL_CB_2 + i]);
    }

}

void drawUpdateCBFrame(Input *input,short **mapID,Shape *shape){
	resetButtonFrame(mapID);
    Button del[2] = {{520, 480, 160, 40, BLUE_L, 15, "LUU"}, {740, 480, 160, 40, BLUE_L, 15, "HUY"}};
    for (int i = 0; i < 2; i++)
    {
        drawButton(del[i],ID_BUTTON_ACPUPDATE_CB_2 + i, mapID);
        convertToShape(del[i], shape[ID_BUTTON_ACPUPDATE_CB_2 + i]);
    }	
	for(int i = 2; i<=6;i++){
		drawInput(input[i],mapID,ID_INPUT_DAY_2 + i -2);
		makeBeautiInputNgayGioKH(input);
	}
}



void drawDSCBFrame(short **mapID,Shape *shape,DanhSachTam &dsTmp, Board &boardCB,Input *inputFill, Input *input,int &numOfPage,int &presentPage, Button *pre_next,Button *buttonFill,Button *mainButton){
	setfillstyle(1,WHITE);
	bar(251,0,MAX_W,130);
	setID(251,0,MAX_W - 251,130,-1,mapID);
	
	setText(6,10);
	outtextxy(410,-10,"DANH SACH CHUYEN BAY");
	for(int i = 0;i <2;i++){
		setText(2,10,0,BLUE_L);
		drawButton(pre_next[i],ID_BUTTON_PRE+i,mapID);
		convertToShape(pre_next[i],shape[i+ID_BUTTON_PRE]);
	}
	
	setText();
	outtextxy(275,80,"NGAY GIO K.H:");	
	outtextxy(506,101,"SAN BAY DEN:");	
	
	for(int i = 0; i< 4;i++){
	drawInput(inputFill[i],mapID,i+ID_INPUT_FILLTIMED_2);
	drawButton(buttonFill[i],ID_BUTTON_FILL_CB_2 + i,mapID);
	}
	
	makeBeautiFillInput(inputFill);

	
   	updateNumOfBoardDSCB(numOfPage, presentPage,dsTmp);
    drawBoard(boardCB, (presentPage - 1) * 10 + ID_BOARD, mapID, shape);
    outDSCB(boardCB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsTmp);
    
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

void updateNumOfBoardDSCB(int &numOfPage, int presentPage,DanhSachTam &dsTmp){

    numOfPage = (dsTmp.n - 1) / 10 + 1;
    char toChar[5];
    setText();
    setfillstyle(1, 15);
    bar(676, 50, 715, 90);
    itoa(presentPage, toChar, 10);
    outtextxy(675, 55, toChar);
    outtextxy(690, 55, "/");
    itoa(numOfPage, toChar, 10);
    outtextxy(705, 55, toChar);

}

void checkHoverPageQLCB(short &newID, short lastID, Shape *shape, short **mapID)
{

    if (ismouseclick(WM_MOUSEMOVE))
    {
        int x, y;
        getmouseclick(WM_MOUSEMOVE, x, y);
        newID = mapID[x][y];
    
        //IN HOVER: MOI HOVER DEU MAU DEN
        
    	short ID = newID;
        if(ID >= 60) //HOVER CHO BOARD
           	ID = ID%10 + 50;	
		if(lastID >= 60)
		   lastID = lastID%10 + 50;
		   
        if((ID_INPUT_DAY_2 <= ID && ID <= ID_INPUT_MINUTE_2) || (ID <= ID_INPUT_FILLTIMEY_2 && ID >= ID_INPUT_FILLTIMED_2)){  //NGAY GIO CO KIEU HOVER KHAC
            setcolor(BLACK);
            rectangle(shape[ID].x1, shape[ID].y1+shape[ID].height, shape[ID].x1 + shape[ID].width, shape[ID].y1+shape[ID].height - 1);       	  
		}
        else if (ID > 0 && ID != lastID)
        {
            setcolor(BLACK);
            rectangle(shape[ID].x1, shape[ID].y1, shape[ID].x1 + shape[ID].width, shape[ID].y1 + shape[ID].height);
        }
        //OUT HOVER :VOI INPUT SE TO LAI MAU DEN, VOI BUTTON SE TO LAI MAU BLUE_L
        if (ID != lastID && lastID > 0)
        {	
	        if((ID_INPUT_DAY_2 <= lastID && lastID <= ID_INPUT_MINUTE_2) || (lastID <= ID_INPUT_FILLTIMEY_2 && lastID >= ID_INPUT_FILLTIMED_2)){ //NGAY GIO CO KIEU HOVER KHAC
	            setcolor(WHITE);
	            rectangle(shape[lastID].x1, shape[lastID].y1+shape[lastID].height, shape[lastID].x1 + shape[lastID].width, shape[lastID].y1+shape[lastID].height - 1);     	
			}
			else{
				
				if(lastID>=ID_INPUT_FILLTIMED_2)
					setcolor(WHITE);      	
	            else
	                setcolor(BLUE_L);
	            rectangle(shape[lastID].x1, shape[lastID].y1, shape[lastID].x1 + shape[lastID].width, shape[lastID].y1 + shape[lastID].height);
			}

        }
    }
}

void outDSCB(Board &board, int startCB, int endCB,DanhSachTam &dsTmp){

    int x1, y1, x2 = board.x1, y2 = board.y1;
    for (int line = 0; line <= board.numOfLine && startCB-1 < dsTmp.n; line++)
    {
		
        y1 = y2;
        y2 += board.heightOfLine;
        x2 = board.x1;
        for (int col = 1; col <= board.numOfCol; col++)
        {
            x1 = x2;
            x2 += board.widthOfCol[col - 1];
            if (line >= 1)
               outCB(board,dsTmp,startCB -1);
			
        }
        if (line >= 1)
            startCB++;
    }
}
void getCBData(Input *input,short chooseID,DanhSachChuyenBay &dsCB,DanhSachTam &dsTmp){


  	short ID = chooseID - ID_BOARD; //lay ra ID cua CB trong dsCB
	strcpy(input[0].s,dsTmp.cb[ID]->maChuyenBay); //ma cb
	strcpy(input[1].s,dsTmp.cb[ID]->soHieuMayBay); //so hieu
	//ngay gio kh
	itoa(dsTmp.cb[ID]->ngayKhoiHanh.ngay, input[2].s, 10);
	itoa(dsTmp.cb[ID]->ngayKhoiHanh.thang, input[3].s, 10);
	itoa(dsTmp.cb[ID]->ngayKhoiHanh.nam, input[4].s, 10);
	itoa(dsTmp.cb[ID]->ngayKhoiHanh.gio, input[5].s, 10);
	itoa(dsTmp.cb[ID]->ngayKhoiHanh.phut, input[6].s,10);
	for(int i = 2;i<=6;i++){
		if(strlen(input[i].s) == 1){
			input[i].s[1] = input[i].s[0];
			input[i].s[2] = '\0';
			input[i].s[0] = '0';
		}
		
	}	
	//trang thai
	itoa(dsTmp.cb[ID]->trangThai, input[7].s,10);
	if(input[7].s[0] == '0') 	strcpy(input[7].s,"HUY CHUYEN");
	if(input[7].s[0] == '1')	strcpy(input[7].s,"CON VE");
	if(input[7].s[0] == '2')	strcpy(input[7].s,"HUY VE");
	if(input[7].s[0] == '3')	strcpy(input[7].s,"HOAN TAT");
	
	strcpy(input[8].s,dsTmp.cb[ID]->sanBayDen);	
	
    for (int i = 0; i < 9; i++){
        input[i].lastL = strlen(input[i].s); 
	}	
}

void fixNgay(Input *input){   //fix ngay sao cho phu hop voi nam do 
	int ngayTmp[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
	int namInput = atoi(input[4].s);
	if(namInput % 400 == 0 || namInput % 4 == 0 && namInput % 100 != 0)
		ngayTmp[2]++;
	if (atoi(input[2].s) > ngayTmp[atoi(input[3].s)]){
		itoa(ngayTmp[atoi(input[3].s)],input[2].s,10);
		outtextxy(input[2].x1 + 7,input[2].y1 + 5,input[2].s);
		
	}	
}


void chuanHoaInputQLCB(Input &input,short inputID){
   //sua lai ngay thang gio phut neu chi co 1 ki tu
    if (((ID_INPUT_DAY_2 <= inputID && inputID <= ID_INPUT_MINUTE_2 && inputID != ID_INPUT_YEAR_2) ||(ID_INPUT_FILLTIMED_2 <= inputID && inputID < ID_INPUT_FILLTIMEY_2)) && input.lastL == 1  )
    {
        input.lastL = 2;
        input.s[1] = input.s[0];
        input.s[0] = '0';
        input.s[2] = '\0';
    }
    //gioi han ngay
    if((inputID == ID_INPUT_DAY_2 || inputID == ID_INPUT_FILLTIMED_2) && input.lastL > 0){
    	if(atoi(input.s) == 0 ){
    		 input.s[1] ='1';
    	}
    	if(atoi(input.s) >31){
    		 input.s[0] ='3';
    		 input.s[1] ='1';
    	}            		
    }
    //gioi han thang
    if((inputID == ID_INPUT_MONTH_2 ||inputID == ID_INPUT_FILLTIMEM_2) && input.lastL > 0){
    	if(atoi(input.s) == 0){
    		 input.s[1] ='1';
    	}       
		if(atoi(input.s) >12){
			input.s[0] ='1';
			input.s[1] ='2';
		}     	
    }
    
    //gioi han gio
    if(inputID == ID_INPUT_HOUR_2){
    	if(atoi(input.s) >=24){
    		input.s[0] ='2';
    		input.s[1] ='3';
    	}            	
    }            
     //gioi han phut
    if(inputID == ID_INPUT_MINUTE_2){
    	if(atoi(input.s) >=60){
    		input.s[0] ='5';
    		input.s[1] ='9';
    	}            	
    }           
    //xoa khoang cach o cuoi chuoi
	if(input.s[input.lastL - 1] == ' ')
		input.lastL--;
	
	input.s[input.lastL] = '\0';                           
	
} 

void drawInputPageQLCB(Input *input,short **mapID,bool unlockInput ){
	if(input[7].lastL == 0)
		{
			strcpy(input[7].s,"CON VE");
			input[7].lastL = 6;	
		}
	if(unlockInput){
	   for(int i = 0; i < 9;i++){
    		drawInput(input[i],mapID,ID_INPUT_MCB_2+i);
    		if(i == 7)
    		drawLockInput(input[i],mapID);
    		
    	}
		makeBeautiInputNgayGioKH(input);	
	}
    else{
    	for(int i = 0; i < 9;i++){
    		drawLockInput(input[i],mapID);
    	}
		makeBeautiLockInputNgayGioKH(input);	
    }
	
}



void unlockPageQLCB(Button *pre_next, Button *fill,Button &seeDSMB,short **mapID){
	drawButton(pre_next[0],ID_BUTTON_PRE,mapID);
	drawButton(pre_next[1],ID_BUTTON_NEXT,mapID);
	drawButton(fill[0],ID_BUTTON_FILL_CB_2,mapID);
	drawButton(fill[3],ID_BUTTON_UNFILL_CB_2,mapID);
	drawButton(seeDSMB,ID_BUTTON_SEEDSMB_2,mapID);	
}



void outCBUpdated(Board &board,DanhSachTam &dsTmp,short chooseID){
	short ID=chooseID - ID_BOARD;
    short x1 = board.x1,
	 y1 = (ID%10 + 1) * board.heightOfLine + board.y1, 
	 x2 = x1, 
	 y2 = y1 +30;
 	setfillstyle(1,WHITE);	
    bar(x1,y1,x1+900,y1 + 30);
    setcolor(BLACK);
    for(int col = 1; col<=board.numOfCol; col++){
    	x2 += board.widthOfCol[col - 1];
    	rectangle(x1,y1, x2, y2);
    	x1 = x2;
    }
    outCB(board,dsTmp,ID);
}
 
void unChooseCB(Input *input, short &chooseID,bool &unlockChoose, Shape *shape, short **mapID){
    setcolor(15);
    setfillstyle(1, 15);
    fillellipse(shape[chooseID%10 + 50].x1 - 13, shape[chooseID%10 + 50].y1 + 10, 5, 5);
    unlockChoose = true;
    chooseID = -1;
    for(int i = 0; i < 9;i++)
    	input[i].lastL = 0;
	drawInputPageQLCB(input,mapID,true);
} 

void updateCB(Input *input,bool &isInvalid,short ID,DanhSachChuyenBay &dsCB,DanhSachTam &dsTmp){
	char alert[255];
	NgayThangNam dtUpdate = newNgayThangNam(atoi(input[2].s), atoi(input[3].s), atoi(input[4].s), atoi(input[5].s), atoi(input[6].s));
	isInvalid = capNhatNgayThangNam(dsCB, dsTmp.cb[ID - ID_BOARD], dtUpdate, alert);
	if(isInvalid) {
		luuDSChuyenBay(dsCB);
		outAlert(GREEN,alert);
	}
	else outAlert(RED,alert);	
} 
void fixNgayFill(Input *input){   //fix ngay sao cho phu hop voi nam do 
	int ngayTmp[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
	int namInput = atoi(input[2].s);
	if(namInput % 400 == 0 || namInput % 4 == 0 && namInput % 100 != 0)
		ngayTmp[2]++;
	if (atoi(input[0].s) > ngayTmp[atoi(input[1].s)]){
		itoa(ngayTmp[atoi(input[1].s)],input[0].s,10);
		outtextxy(input[0].x1 + 7,input[0].y1 + 5,input[0].s);
	}
			
}
void makeBeautiFillInput(Input *input){
	setfillstyle(1,15);
	setText(1, 10);
	bar(input[0].x1,input[0].y1,input[2].x1+input[2].width,input[2].y1+30);
	rectangle(input[0].x1,input[0].y1,input[2].x1+input[2].width,input[2].y1+30);
	outtextxy(316,102,"/");
	outtextxy(366,102,"/");	
	for(int i = 0; i<3;i++){
		if(input[i].lastL != 0)
		outtextxy(input[i].x1 + 7,input[i].y1 + 5,input[i].s);
	}			
}
void makeBeautiLockInputNgayGioKH(Input *input){
	setfillstyle(1,15);
	setText(1, 10, 8, 15);
	bar(input[2].x1,input[2].y1,input[4].x1+input[4].width,input[4].y1+30);
	rectangle(input[2].x1,input[2].y1,input[4].x1+input[4].width,input[4].y1+30);
	bar(input[5].x1,input[5].y1,input[6].x1+input[6].width,input[6].y1+30);
	rectangle(input[5].x1,input[5].y1,input[6].x1+input[6].width,input[6].y1+30);		
	outtextxy(491,610,"/");
	outtextxy(541,610,"/");
	outtextxy(635,610,"-");
	outtextxy(691,610,":");	
	for(int i = 2; i<=6;i++){
		if(input[i].lastL != 0)
		outtextxy(input[i].x1 + 7,input[i].y1 + 5,input[i].s);
	}
}

void makeBeautiInputNgayGioKH(Input *input){
 
	setfillstyle(1,15);
	setText(1, 10);
	bar(input[2].x1,input[2].y1,input[4].x1+input[4].width,input[4].y1+30);
	rectangle(input[2].x1,input[2].y1,input[4].x1+input[4].width,input[4].y1+30);
	bar(input[5].x1,input[5].y1,input[6].x1+input[6].width,input[6].y1+30);
	rectangle(input[5].x1,input[5].y1,input[6].x1+input[6].width,input[6].y1+30);		
	outtextxy(491,610,"/");
	outtextxy(541,610,"/");
	outtextxy(635,610,"-");
	outtextxy(691,610,":");	

	for(int i = 2; i<=6;i++){
		if(input[i].lastL != 0)
		outtextxy(input[i].x1 + 7,input[i].y1 + 5,input[i].s);
	}
}
void lockPageQLCB(Button *pre_next, Button *fill, Button &seeDSMB,short **mapID){
	drawLockButton(pre_next[0],mapID);
	drawLockButton(pre_next[1],mapID);
	drawLockButton(fill[0],mapID);
	drawLockButton(fill[3],mapID);
	drawLockButton(seeDSMB,mapID);
	
}

void outCB(Board &board,DanhSachTam &dsTmp, short ID){
	setText();
    short x1 = board.x1,
	y1 = (ID%10 + 1) * board.heightOfLine + board.y1, 
	x2 = x1;
    for(int col = 1; col<=board.numOfCol; col++){
    	x1 = x2;
    	x2 += board.widthOfCol[col - 1];          
        if (col == 1) //MA CB
        { 
            outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 4.5 * strlen(dsTmp.cb[ID]->maChuyenBay),
                      y1 + (board.heightOfLine) / 2 - 10, dsTmp.cb[ID]->maChuyenBay);
        }
        else if (col == 2) //SO HIEU
            outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 4.5 * strlen(dsTmp.cb[ID]->soHieuMayBay),
                      y1 + (board.heightOfLine) / 2 - 10, 	dsTmp.cb[ID]->soHieuMayBay);
        else if (col == 3)  //NGAY GIO KHOI HANH
        { 		
			char phut[5], gio[5],ngay[5],thang[5],nam[5],ngayGio[25];
			itoa(dsTmp.cb[ID]->ngayKhoiHanh.phut, phut, 10);
			itoa(dsTmp.cb[ID]->ngayKhoiHanh.gio, gio, 10);
			itoa(dsTmp.cb[ID]->ngayKhoiHanh.ngay, ngay, 10);
			itoa(dsTmp.cb[ID]->ngayKhoiHanh.thang, thang, 10);
			itoa(dsTmp.cb[ID]->ngayKhoiHanh.nam, nam, 10);
			if(strlen(ngay)==1)  {
				strcpy(ngayGio,"0");
				strcat(ngayGio,ngay);
			}
			else	strcpy(ngayGio,ngay);
			strcat(ngayGio,"/");
			if(strlen(thang) == 1) strcat(ngayGio,"0");
			strcat(ngayGio,thang);
			strcat(ngayGio,"/");
			strcat(ngayGio,nam);
			strcat(ngayGio," - ");
			if(strlen(gio) == 1) strcat(ngayGio,"0");
			strcat(ngayGio,gio);
			strcat(ngayGio,":");
			if(strlen(phut) == 1) strcat(ngayGio,"0");
			strcat(ngayGio,phut);
            outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 3 * strlen(ngayGio),
                      y1 + (board.heightOfLine) / 2 - 10, ngayGio);
        }
        else if (col == 4) //SAN BAY DEN
        { 

            outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 4.5 * strlen(dsTmp.cb[ID]->sanBayDen),
                      y1 + (board.heightOfLine) / 2 - 10, 	dsTmp.cb[ID]->sanBayDen);
        }
        else if (col == 5) //TRANG THAI
        { 	
    		char trangThai[15];
			if(dsTmp.cb[ID]->trangThai == 0) strcpy(trangThai,"HUY CHUYEN");
			if(dsTmp.cb[ID]->trangThai == 1)	strcpy(trangThai,"CON VE");
			if(dsTmp.cb[ID]->trangThai == 2)	strcpy(trangThai,"HUY VE");
			if(dsTmp.cb[ID]->trangThai == 3)	strcpy(trangThai,"HOAN TAT");
            outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 4 * strlen(trangThai),
                      y1 + (board.heightOfLine) / 2 - 10, trangThai);						
        }        	
    	
    }	
} 
