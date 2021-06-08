#pragma once
#include "reuse.h"

//====================PROTOTYPE==================
void addMB(Input *input,bool &isInvalid,short ID,DanhSachMayBay &dsMB);
void chuanHoaInputQLMB(Input &input, short inputID);
void checkHoverPageQLMB(short &newID, short lastID, Shape *shape, short **mapID);
void checkEventPageQLMB(short **mapID, Shape *shape, Input *input, Button *mainButton, Board &BOARDMB,Button *pre_next);
void delMB(Input *input,bool &isInvalid,short ID,DanhSachMayBay &dsMB,DanhSachChuyenBay &dsCB);
void drawUpdateMBFrame(Input *input,short **mapID,Shape *shape,DanhSachChuyenBay &dsCB);
void drawDelMBFrame(short **mapID, Shape *shape, Input *input);
void drawPageQLMB(short **mapID,Shape *shape);
void drawPageQLMB(short **mapID, Shape *shape);
void getMBData(Input *input,short ID,short **mapID,DanhSachMayBay &dsMB);
void getInputPageQLMB(Input &input, short &inputID, bool &isEnter);
void lockPageQLMB(Button *pre_next,short **mapID);
void outMBUpdated(Board &board,DanhSachMayBay &dsMB,short chooseID)	;
void outDSMB(Board &board, int startMB, int endMB,DanhSachMayBay &dsMB);
void outMB(Board &board,DanhSachMayBay &dsMB, short ID);
void updateNumOfBoardDSMB(int &numOfPage, int &presentPage,DanhSachMayBay &dsMB);
void updateMB(Input *input,bool &isInvalid,short ID,DanhSachMayBay &dsMB);
void unlockPageQLMB(Button *pre_next,short **mapID);
void unChooseMB(Input *input, short &chooseID,bool &unlockChoose, Shape *shape, short **mapID);
		 


//==========================================================
void checkEventPageQLMB(short **mapID, Shape *shape, Input *input, Button *mainButton, Board &boardMB,Button *pre_next)
{
		
    DanhSachMayBay dsMB;
    layDSMayBay(dsMB);
	DanhSachChuyenBay dsCB = NULL;
	layDSChuyenBay(dsCB);
	
    short ID = -1, lastID = -1, chooseID = -1;
    bool isInvalid = false;                                          //check xem du lieu can them,xoa,sua co hop le hay khong
    bool unlockChoose = true;                                       //khi dang update thi se khong cho chon may bay nua
    bool isEnter = false;                                           //check enter khi dang input
    int numOfPage = (dsMB.n - 1) / 10 + 1, presentPage = 1; 		//quan ly so trang
    short maxChoose = 0;                                              //khong cho chon vao o khong co may bay
    updateNumOfBoardDSMB(numOfPage, presentPage,dsMB);
    
    outDSMB(boardMB, 1, 10,dsMB);
    
    clearmouseclick(WM_LBUTTONDOWN);   
    while (true)
    {
        delay(DELAY_TO_CHECK_EVENT);
        checkHoverPageQLMB(ID, lastID, shape, mapID);
        lastID = ID;
 

        if (ismouseclick(WM_LBUTTONDOWN))
        {
			if(getpixel(725,540) == BLACK){ //xoa thong bao
				outAlert(WHITE,"");
			}        	
            
            if (ID >= ID_BOARD)   //chon may bay
            {	
           		maxChoose = dsMB.n - 1 + ID_BOARD;
            	if(ID <= maxChoose){
	                if (ID != chooseID && unlockChoose) //CHON CAI MOI
	                {
	                    setcolor(0);
	                    setfillstyle(1, 0);
	                    fillellipse(shape[ID%10 + 50].x1 - 13, shape[ID%10 + 50].y1 + 10, 5, 5);
	                    if (chooseID != -1)  //BO CHON CAI CU NEU CHON CAI MOI
	                    { 
	                    	//xoa
	                        setcolor(15);
	                        setfillstyle(1, 15);
	                        fillellipse(shape[chooseID%10 + 50].x1 - 13, shape[chooseID%10 + 50].y1 + 10, 5, 5);
	                    }                                   
	                    chooseID = ID;
	                    getMBData(input,chooseID,mapID,dsMB);
	                    lockPageQLMB(pre_next,mapID);
	                    for(int i  = 0; i < 3; i++)
	                        drawLockInput(input[i],mapID);
	                }
	                else if (chooseID != -1 && ID == chooseID && unlockChoose) //NHAP VAO CAI DANG CHON DE HUY
	                { 
						unChooseMB(input,chooseID,unlockChoose,shape,mapID);
						unlockPageQLMB(pre_next,mapID);

	                }
            	}
            }
            //===============================================
            
		    if(ID>=ID_BUTTON_PAGE_MAIN && ID<=ID_BUTTON_PAGE4 && ID != ID_BUTTON_PAGE_QLMB){            
		    	clearDSMB(dsMB);
		    	clearDSCB(dsCB);
            	return;
            }             
            switch (ID)
            {
            case 5: //PRE DSMB PAGE
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
            case 6:  //NEXT DSMB PAGE
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
            case ID_BUTTON_ADD_1:  //THEM 
            { 
                
                addMB(input,isInvalid,chooseID,dsMB);
                if (isInvalid)
                {
                	
                    updateNumOfBoardDSMB(numOfPage, presentPage,dsMB);
					if(presentPage == numOfPage){  //neu cung trang thi in ra cb moi them vao cuoi ds
						outMB(boardMB,dsMB,dsMB.n-1);
					}
					else{	
						presentPage = numOfPage;
	                    drawBoard(boardMB, (presentPage - 1) * 10 + ID_BOARD, mapID, shape);
	                    outDSMB(boardMB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsMB);
	                    updateNumOfBoardDSMB(numOfPage, presentPage,dsMB);	
					}
					for(int i = 0 ; i<3; i++){
						input[i].lastL = 0;
						drawInput(input[i],mapID,ID_INPUT_SHMB_1+i); 
					}                    

                }
                break;
            }
            case ID_BUTTON_DEL_1: //XOA
            { 

				if(chooseID != -1){
					unlockChoose = false;					
					
					drawDelMBFrame(mapID,shape,input);					
				}
				else{
					outAlert(RED,"BAN CHUA CHON MAY BAY!");
				}
				break;

            }
            case ID_BUTTON_UPDATE_1: //CAP NHAT
            {            	
            	//neu da chon chuyen bay thi moi cho cap nhat
				if(chooseID!= -1)
				{
					unlockChoose = false;
					drawUpdateMBFrame(input,mapID,shape,dsCB);
				}
				else{
					outAlert(RED,"BAN CHUA CHON MAY BAY!");					
				}
                break;
            }
            case ID_INPUT_SHMB_1: //SO HIEU
            {
                getInputPageQLMB(input[0],ID, isEnter);
                if (!isEnter)
                    break;	 
            }
            case ID_INPUT_SOCHO_1: //SO CHO
            {
				
                getInputPageQLMB(input[1], ID, isEnter);
                if (!isEnter)
                    break;	 
            }
            case ID_INPUT_LMB_1: //LOAI
            {
            	
                getInputPageQLMB(input[2],ID, isEnter);
                break;
            }
            case ID_BUTTON_ACPDEL_1://XAC NHAN XOA
            { 
				delMB(input,isInvalid,chooseID,dsMB,dsCB);
				if(isInvalid){
					unlockPageQLMB(pre_next,mapID);
					unChooseMB(input,chooseID,unlockChoose,shape,mapID);  		            
					updateNumOfBoardDSMB(numOfPage, presentPage,dsMB);
					if (presentPage > numOfPage)
                    	presentPage--;
                    updateNumOfBoardDSMB(numOfPage, presentPage,dsMB);
					drawBoard(boardMB, (presentPage - 1) * 10 + ID_BOARD, mapID, shape);
	                outDSMB(boardMB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsMB);
	                resetButtonFrame(mapID);
					for(int i = 0 ; i < 3; i++)
						drawButton(mainButton[i], ID_BUTTON_ADD_1 +i,mapID);	
					
						    	
				}
		        
          
                break;
            }
            case ID_BUTTON_ACPUPDATE_1: //LUU CAP NHAT
            {	        
 				updateMB(input,isInvalid,chooseID, dsMB);
                if (isInvalid)
                {
                    outMBUpdated(boardMB,dsMB,chooseID);  		            
		            outMBUpdated(boardMB,dsMB,chooseID);
		            unlockPageQLMB(pre_next,mapID);
					unChooseMB(input,chooseID,unlockChoose,shape,mapID);					
					resetButtonFrame(mapID);
		            for(int i = 0; i < 3; i++){
						drawButton(mainButton[i], ID_BUTTON_ADD_1 +i,mapID);	
		            }				    
                }
                break;
            }
            case ID_BUTTON_UNDEL_1:
            case ID_BUTTON_UNUPDATE_1:
            {	//HUY XOA, HUY CAP NHAT
            	
                resetButtonFrame(mapID);
                unlockChoose = true;
                for (int i = 0; i < 3; i++)
                {
                    drawButton(mainButton[i], ID_BUTTON_ADD_1 + i, mapID);                
                    if (chooseID == -1)    
                        drawInput(input[i], mapID, ID_INPUT_SHMB_1 + i);
                    else if(chooseID != -1)
                    {
                        getMBData(input,chooseID,mapID,dsMB);
                        drawLockInput(input[i], mapID);               
                    }
                }
                break;
            }
            default:
                break;
            }
            
            if(ID >= ID_BUTTON_DEL_1 && ID <= ID_BUTTON_UNUPDATE_1){ //fix loi hover
				ID = -1;
				lastID = -1;
			}
            clearmouseclick(WM_LBUTTONDOWN);
        }
				
        
    }
}
void drawPageQLMB(short **mapID, Shape *shape){
    setDefaultRightFrame(mapID);

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
    
    setcolor(0);
    rectangle(275, 470, 1175, MAX_H);    
    
    Button mainButton[3] = {{0, 0, 0, 0, 0, 0, "THEM"}, {0, 0, 0, 0, 0, 0, "XOA"}, {0, 0, 0, 0, 0, 0, "CAP NHAT"}};
    for (int i = 0; i < 3; i++)
    {
        mainButton[i].x1 = 455 + 180 * i;
        mainButton[i].y1 = 480;
        mainButton[i].width = 160;
        mainButton[i].height = 40;
        mainButton[i].fillColor = BLUE_L;
        mainButton[i].borderColor = 15;
        drawButton(mainButton[i], i + ID_BUTTON_ADD_1, mapID);
        convertToShape(mainButton[i], shape[i + ID_BUTTON_ADD_1]);
    }
    setText();
    outtextxy(385, 575, "SO HIEU:");
    outtextxy(830, 575, "SO CHO:");
    outtextxy(410, 625, "LOAI:");
    Input input[3] = {{450, 570, 15, 190,0 }, {890, 570, 4, 80, 0}, {450, 620, 40, 520, 0}};
    for (int i = 0; i < 3; i++)
    {	
        input[i].s = new char[input[i].max + 2];
        drawInput(input[i], mapID, i + ID_INPUT_SHMB_1);
        convertToShape(input[i], shape[i + ID_INPUT_SHMB_1]);
    }
    
    	checkEventPageQLMB(mapID, shape, input, mainButton, boardMB,pre_next);
    	for(int i = 0;i<3;i++)
    		delete[] input[i].s;
}
void getInputPageQLMB(Input &input, short &inputID, bool &isEnter)
{
    int paddingLeft = 10;
	if(isEnter){ //INHOVER
		setcolor(BLACK);
        rectangle(input.x1+1, input.y1 +1, input.x1 + input.width -1 , input.y1 + 29);
	}    
	isEnter = false;	
    while (kbhit())
        char c = getch(); //======nuot phim
    setText(1, 10);
    input.s[input.lastL] = '|';
    input.s[input.lastL + 1] = '\0';
    clearmouseclick(WM_LBUTTONDOWN);
    while (1)
    {
        outtextxy(input.x1 + paddingLeft, input.y1 + 5, input.s);
        delay(DELAY_TO_CHECK_EVENT);       
        if (ismouseclick(WM_LBUTTONDOWN))
        { //============ CLICK trong khi nhap du lieu
            chuanHoaInputQLMB(input,inputID);
            outtextxy(input.x1 + paddingLeft, input.y1 + 5, input.s);
            break;
        }
        
        if (kbhit())
        {
            char c = getch();
            if (c == 13)
            { //ENTER khi nhap du lieu
                isEnter = true;
                //OUTHOVER
               	setcolor(WHITE);
        		rectangle(input.x1+1, input.y1 +1, input.x1 + input.width -1 , input.y1 + 29); 
                chuanHoaInputQLMB(input,inputID);
                setcolor(BLACK);
                outtextxy(input.x1 + paddingLeft, input.y1 + 5, input.s);
                inputID+=1;
                break;
            }
            if (('a' <= c && c <= 'z' || '0' <= c && c <= '9' || (c == ' ' && input.s[input.lastL - 1] != ' ' && input.lastL != 0)) && input.lastL < input.max)
            {
                if (inputID == ID_INPUT_LMB_1 && input.lastL < input.max - 1 || inputID == ID_INPUT_SHMB_1 && input.lastL < input.max - 1 && c != ' ')
                { //xu ly Input loai may bay va so hieu

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
                else if (inputID == ID_INPUT_SOCHO_1 && '0' <= c && c <= '9')
                { //xu ly Input so cho
                    if (input.lastL == 0 && c == '0') ;// khong nhan so 0 o dau 
                    else
                    {
                        input.s[input.lastL] = c;
                        input.lastL++;
                        input.s[input.lastL + 1] = '\0';
                    }
                    outtextxy(input.x1 + paddingLeft, input.y1 + 5, input.s);
                }
            }
            else if (c == 8 && input.lastL != 0)
            { //======bat phim backspace
				input.lastL--;
                input.s[input.lastL] = '|';
                input.s[input.lastL+1] = ' ';
                outtextxy(input.x1 + paddingLeft, input.y1 + 5, input.s);
                input.s[input.lastL+1] = '\0';
            }
        }
        else
        { //======con tro nhap nhay
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

void lockPageQLMB(Button *pre_next,short **mapID){
	drawLockButton(pre_next[0],mapID);
	drawLockButton(pre_next[1],mapID);
}

 void unChooseMB(Input *input, short &chooseID,bool &unlockChoose, Shape *shape, short **mapID){
    setcolor(15);
    setfillstyle(1, 15);
    fillellipse(shape[chooseID%10 + 50].x1 - 13, shape[chooseID%10 + 50].y1 + 10, 5, 5);
    unlockChoose = true;
    chooseID = -1;
    for(int i = 0; i < 3;i++){
    	input[i].lastL = 0;
    	drawInput(input[i], mapID, ID_INPUT_SHMB_1 + i);
    }
    	
	
}  
			 
void unlockPageQLMB(Button *pre_next,short **mapID){
	drawButton(pre_next[0],ID_BUTTON_PRE,mapID);
	drawButton(pre_next[1],ID_BUTTON_NEXT,mapID);
}
void outMBUpdated(Board &board,DanhSachMayBay &dsMB,short chooseID){
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
    outMB(board,dsMB,ID);
}

void checkHoverPageQLMB(short &newID, short lastID, Shape *shape, short **mapID)
{
	
    if (ismouseclick(WM_MOUSEMOVE))
    {	
 			
		int x, y;
        getmouseclick(WM_MOUSEMOVE, x, y);
        newID = mapID[x][y];
        short ID = newID;
        
        if(ID >= 60) //HOVER CHO BOARD
           	ID = ID%10 + 50;	
		if(lastID >= 60)
		   lastID = lastID%10 + 50;
		   
        //IN HOVER: MOI HOVER DEU MAU DEN
        if (ID > 0 && ID != lastID)
        {
            setcolor(BLACK);
            rectangle(shape[ID].x1, shape[ID].y1, shape[ID].x1 + shape[ID].width, shape[ID].y1 + shape[ID].height);
        }
        //OUT HOVER :VOI INPUT SE TO LAI MAU DEN, VOI BUTTON SE TO LAI MAU BLUE_L
        if (ID != lastID && lastID > 0)
        {
            if (lastID >= ID_INPUT_SHMB_1)
                setcolor(WHITE);
            else
                setcolor(BLUE_L);
            rectangle(shape[lastID].x1, shape[lastID].y1, shape[lastID].x1 + shape[lastID].width, shape[lastID].y1 + shape[lastID].height);
        }

    }
}
//================= THEM, XOA, CAP NHAT MAY BAY ===============



void addMB(Input *input,bool &isInvalid,short chooseID,DanhSachMayBay &dsMB)
{	
    MayBay newMB;
    strcpy(newMB.soHieuMayBay, input[0].s);
    newMB.soCho = atoi(input[1].s);
    strcpy(newMB.loaiMayBay, input[2].s);
	short ID=chooseID - ID_BOARD;//lay ra vi tri cua MB trong ds
	char alert[255];
    isInvalid = themMayBayHopLe(newMB, dsMB,alert);
	if(isInvalid) {
		luuDSMayBay(dsMB);
		outAlert(GREEN,alert);
	}
	else outAlert(RED,alert);	
}



void drawDelMBFrame(short **mapID, Shape *shape, Input *input)
{
    resetButtonFrame(mapID);
    Button del[2] = {{520, 480, 160, 40, BLUE_L, 15, "XAC NHAN"}, {740, 480, 160, 40, BLUE_L, 15, "HUY"}};
    for (int i = 0; i < 2; i++)
    {
        drawButton(del[i], ID_BUTTON_ACPDEL_1 + i, mapID);
        convertToShape(del[i], shape[ID_BUTTON_ACPDEL_1 + i]);
    }

}



void delMB(Input *input,bool &isInvalid,short chooseID,DanhSachMayBay &dsMB,DanhSachChuyenBay &dsCB)
{			
    
	short ID=chooseID - ID_BOARD;//lay ra vi tri cua MB trong ds
	char alert[255];
    isInvalid = xoaMayBayHopLe(input[0].s, dsMB, dsCB,ID,alert);
	if(isInvalid) {
		luuDSMayBay(dsMB);
		luuDSChuyenBay(dsCB);
		outAlert(GREEN,alert);
	}
	else outAlert(RED,alert);	
}


void drawUpdateMBFrame(Input *input,short **mapID,Shape *shape,DanhSachChuyenBay &dsCB)
{
    resetButtonFrame(mapID);
    Button del[2] = {{520, 480, 160, 40, BLUE_L, 15, "LUU"}, {740, 480, 160, 40, BLUE_L, 15, "HUY"}};
    for (int i = 0; i < 2; i++)
    {
        drawButton(del[i], ID_BUTTON_ACPUPDATE_1 + i, mapID);
        convertToShape(del[i], shape[ID_BUTTON_ACPUPDATE_1 + i]);
    }
    

    if (ktMayBayDaCoChuyenBay(input[0].s,dsCB))
    {
        drawLockInput(input[1], mapID);
    }
    else 
    	drawInput(input[1], mapID, ID_INPUT_SOCHO_1);
    drawInput(input[2], mapID, ID_INPUT_LMB_1);

}
void updateMB(Input *input,bool &isInvalid,short chooseID,DanhSachMayBay &dsMB)
{	
	short ID=chooseID - ID_BOARD;//lay ra vi tri cua MB trong ds
	char alert[255];
	isInvalid = capNhatMayBay(input[2].s, atoi(input[1].s),dsMB,ID,alert);
	if(isInvalid) {
		luuDSMayBay(dsMB);
		outAlert(GREEN,alert);
	}
	else outAlert(RED,alert);	
}


void getMBData(Input *input,short chooseID,short **mapID,DanhSachMayBay &dsMB)
{
	short ID=chooseID - ID_BOARD; //lay ra vi tri cua MB trong ds
    strcpy(input[0].s,dsMB.mayBay[ID]->soHieuMayBay);
    itoa(dsMB.mayBay[ID]->soCho, input[1].s, 10);
    strcpy(input[2].s,dsMB.mayBay[ID]->loaiMayBay);
    for(int i = 0; i <3;i++)
       input[i].lastL = strlen(input[i].s);   
}    


void updateNumOfBoardDSMB(int &numOfPage, int &presentPage,DanhSachMayBay &dsMB)
{
    numOfPage = (dsMB.n - 1) / 10 + 1;
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

void outMB(Board &board,DanhSachMayBay &dsMB, short ID){
    char toChar[5];
	setText();
    short x1 = board.x1,
	y1 = (ID%10 + 1) * board.heightOfLine + board.y1, 
	x2 = x1;
   for(int col = 1; col<=board.numOfCol; col++){
   		x1 = x2;
    	x2 += board.widthOfCol[col - 1];    
        if (col == 1) //STT
        { 
            itoa(ID+1, toChar, 10);
            outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 3 * strlen(toChar),
                      y1 + (board.heightOfLine) / 2 - 10, toChar);
        }
        else if (col == 2) //SO HIEU
            outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 4.5 * strlen(dsMB.mayBay[ID]->soHieuMayBay),
                      y1 + (board.heightOfLine) / 2 - 10, dsMB.mayBay[ID]->soHieuMayBay);
        else if (col == 3) //LOAI
        { 
            outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 4 * strlen(dsMB.mayBay[ID]->loaiMayBay),
                      y1 + (board.heightOfLine) / 2 - 10, dsMB.mayBay[ID]->loaiMayBay);
        }
        else if (col == 4) //SOCHO
        { 
            itoa(dsMB.mayBay[ID]->soCho, toChar, 10);
            outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 3.5 * strlen(toChar),
                      y1 + (board.heightOfLine) / 2 - 10, toChar);
        }
    	
   }
}

void outDSMB(Board &board, int startMB, int endMB,DanhSachMayBay &dsMB)
{
	 int x1, y1, x2 = board.x1, y2 = board.y1;
    for (int line = 0; line <= board.numOfLine && startMB-1 < dsMB.n; line++)
    {
		
        y1 = y2;
        y2 += board.heightOfLine;
        x2 = board.x1;
        for (int col = 1; col <= board.numOfCol; col++)
        {
            x1 = x2;
            x2 += board.widthOfCol[col - 1];
            if (line >= 1)
               outMB(board,dsMB,startMB -1);
			
        }
        if (line >= 1)
            startMB++;
    }
}
void chuanHoaInputQLMB(Input &input, short inputID){
	//xoa khoang cach o cuoi chuoi
	if(input.s[input.lastL - 1] == ' ')
		input.lastL--;
	input.s[input.lastL] = '\0';                               
}
