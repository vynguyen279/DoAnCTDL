#pragma once
#include "reuse.h"

//====================PROTOTYPE==================
void drawPageQLMB(short **, Shape *, bool);
void drawUpdateMBFrame(short **, Shape *, Input *);
void drawDelMBFrame(short **, Shape *, Input *);
void getInputPageQLMB(Input &, short &, bool &);
void checkDelInvalidMB(Input *, bool &,DanhSachMayBay &,DanhSachChuyenBay &);
void checkAddInvalidMB(Input *, bool &,DanhSachMayBay &);
void checkUpdateInvalidMB(Input *, bool &, bool &,DanhSachMayBay &,DanhSachChuyenBay &);
void checkSaveInvalidMB(Input *, bool &);
void checkEventPageQLMB(short **, Shape *, Input *, Button *, Board &);
void checkHoverPageQLMB(short &, short, Shape *, short **);
void alertAddSuccess();
void alertUpdateSuccess();
void alertDelSuccess();
void addMB(Input *,DanhSachMayBay &);
void delMB(Input *,DanhSachMayBay &,DanhSachChuyenBay &);
void UpdateMB(Input *,DanhSachMayBay &);
void chuanHoaInputQLMB(Input &, short);
void outDSCB(Board &, int, int,DanhSachTam &);
void outDSMB(Board &, int, int,DanhSachMayBay &);
void getMBData(Input *,short, short **,DanhSachMayBay &);
void outNumOfBoardDSMB(int &, int &,DanhSachMayBay &);
//==========================================================

void drawPageQLMB(short **mapID, Shape *shape, bool unlockcheckEvent){
    setDefaultRightFrame(mapID);

    setText(6, 10);
    outtextxy(455, 30, "DANH SACH MAY BAY");

    Button pre_next_Board[2] = {{640, 90, 25, 25, BLUE_L, 15, "<"}, {720, 90, 25, 25, BLUE_L, 15, ">"}};
    for (int i = 0; i < 2; i++)
    {
    
        drawButton(pre_next_Board[i], ID_BUTTON_NEXTBOARD_DSMB_1 + i, mapID);
        convertToShape(pre_next_Board[i], shape[ID_BUTTON_NEXTBOARD_DSMB_1 +i]);
    }

    Board board_DSMB = {275, 130, 10, 30, 4, {50, 300, 400, 150}, {"STT", "SO HIEU", "LOAI", "SO CHO"}};

	//chuc nang phim tat
	setText(5, 2, 0, BLUE_M);
    setfillstyle(1, BLUE_M);
    bar(0, 550, 250, MAX_H);
    outtextxy(70, 610, "DELETE   : XOA");
    rectangle(65,605,120,625);
    outtextxy(70, 640, "F1   : CAP NHAT");
	rectangle(65,635,85,655);
    
    setcolor(0);
    rectangle(275, 470, 1175, MAX_H);    
    
    Button Button_Add_Del_Update[3] = {{0, 0, 0, 0, 0, 0, "THEM"}, {0, 0, 0, 0, 0, 0, "XOA"}, {0, 0, 0, 0, 0, 0, "CAP NHAT"}};
    for (int i = 0; i < 3; i++)
    {
        Button_Add_Del_Update[i].x1 = 455 + 180 * i;
        Button_Add_Del_Update[i].y1 = 480;
        Button_Add_Del_Update[i].width = 160;
        Button_Add_Del_Update[i].height = 40;
        Button_Add_Del_Update[i].fillColor = BLUE_L;
        Button_Add_Del_Update[i].borderColor = 15;
        drawButton(Button_Add_Del_Update[i], i + ID_BUTTON_ADD_1, mapID);
        convertToShape(Button_Add_Del_Update[i], shape[i + ID_BUTTON_ADD_1]);
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
    
    	checkEventPageQLMB(mapID, shape, input, Button_Add_Del_Update, board_DSMB);
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

void checkEventPageQLMB(short **mapID, Shape *shape, Input *input, Button *Button_Add_Del_Update, Board &board_DSMB)
{
		
    DanhSachMayBay dsMB;
    layDSMayBay(dsMB);
	DanhSachChuyenBay dsCB = NULL;
	layDSChuyenBay(dsCB);
	DanhSachTam dsTmp = dsNode2DsTmp(dsCB);
    short ID = -1, lastID = -1, chooseID = -1;
    bool isInvalid = false;                                          //check xem du lieu can them,xoa,sua co hop le hay khong
    bool unlockChoose = true;                                       //khi dang update thi se khong cho chon may bay nua
    bool isEnter = false;                                           //check enter khi dang input
    bool unlockSoChoWhileUpdate = false;                             //khong cho chinh sua so cho khi dang co chuyen bay
    bool unlockKeyboardShortcut = true; 							//dang xoa thi khong duoc an phim cap nhat va nguoc lai
    int numOfPage = (dsMB.n - 1) / 10 + 1, presentPage = 1; 		//quan ly so trang
    int maxChoose = 0;                                              //khong cho chon vao o khong co may bay
    outNumOfBoardDSMB(numOfPage, presentPage,dsMB);
    drawBoard(board_DSMB, ID_BOARD_DSMB_1, mapID, shape);
    outDSMB(board_DSMB, 1, 10,dsMB);
    clearmouseclick(WM_LBUTTONDOWN);
    
    while (ID != -2)
    {
        delay(DELAY_TO_CHECK_EVENT);
        checkHoverPageQLMB(ID, lastID, shape, mapID);
        lastID = ID;
        if(kbhit() && !unlockKeyboardShortcut)     //NUOT PHIM DE KHONG BI LOI KHI AN NHIEU LAN PHIM TAT
			while (kbhit())	char c = getch();  

        if (ismouseclick(WM_LBUTTONDOWN))
        {
            
            //xu ly chon may bay

            if (ID >= ID_BOARD_DSMB_1)  
            {	
           		maxChoose = dsMB.n - 1 + ID_BOARD_DSMB_1;
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
	                    getMBData(input,chooseID,mapID,dsMB);
	                    for(int i  = 0; i < 3; i++)
	                        drawLockInput(input[i],mapID);
	                }
	                else if (chooseID != -1 && ID == chooseID && unlockChoose) //NHAP VAO CAI DANG CHON DE HUY
	                { 
	                    setcolor(15);
	                    setfillstyle(1, 15);
	                    fillellipse(shape[ID].x1 - 13, shape[ID].y1 + 10, 5, 5);
	                    chooseID = -1;
	                    for (int i = 0; i <= 2; i++)
	                    {
	                        input[i].lastL = 0;
	                        drawInput(input[i], mapID, ID_INPUT_SHMB_1 + i);
	                    }
	                }
            	}
            }
            
            //End xu ly chon may bay 
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
                    unlockChoose =  true;
                    chooseID = -1;
                    for(int i = 0; i < 3;i++){
                    	input[i].lastL = 0;
                    	drawInput(input[i],mapID,ID_INPUT_SHMB_1+i);                    	
                    }         		
                    outNumOfBoardDSMB(numOfPage, presentPage,dsMB);
                    drawBoard(board_DSMB, (presentPage - 1) * 10 + ID_BOARD_DSMB_1, mapID, shape);
                    outDSMB(board_DSMB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsMB);
                    
				}
                   

    
                break;
            }
            case 6:  //NEXT DSMB PAGE
            {
                if (presentPage < numOfPage)
                {
                    presentPage++;
                    unlockChoose =  true;
                    chooseID = -1;
                    for(int i = 0; i < 3;i++){
                    	input[i].lastL = 0;
                    	drawInput(input[i],mapID,ID_INPUT_SHMB_1+i);                    	
                    }                    
                    outNumOfBoardDSMB(numOfPage, presentPage,dsMB);  
                    drawBoard(board_DSMB, (presentPage - 1) * 10 + ID_BOARD_DSMB_1, mapID, shape);
                    outDSMB(board_DSMB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsMB);                 										
				}                       

                break;
            }
            case ID_BUTTON_ADD_1:  //THEM 
            { 
                
                checkAddInvalidMB(input, isInvalid,dsMB);
                if (isInvalid)
                {
                    addMB(input,dsMB);
                    drawPageQLMB(mapID, shape, false);
                    alertAddSuccess();
                    outNumOfBoardDSMB(numOfPage, presentPage,dsMB);
                    if (presentPage < numOfPage)
                        presentPage++;
                    drawBoard(board_DSMB, (presentPage - 1) * 10 + ID_BOARD_DSMB_1, mapID, shape);
                    outDSMB(board_DSMB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsMB);
                    outNumOfBoardDSMB(numOfPage, presentPage,dsMB);
                }
                break;
            }
            case ID_BUTTON_DEL_1: //XOA
            { 

                
                checkDelInvalidMB(input, isInvalid,dsMB,dsCB);
                if (isInvalid)
                {	
                    drawDelMBFrame(mapID, shape, input);
                    unlockChoose = false;
                    unlockKeyboardShortcut = false;
                    getMBData(input,chooseID,mapID,dsMB);
                    for (int i = 0; i < 3; i++)
                        drawLockInput(input[i], mapID);
                }
                break;
            }
            case ID_BUTTON_UPDATE_1: //CAP NHAT
            {            	
                checkUpdateInvalidMB(input, isInvalid, unlockSoChoWhileUpdate,dsMB,dsCB);
                if (isInvalid)
                {	                
                    drawUpdateMBFrame(mapID, shape, input);
                    unlockChoose = false;
                    unlockKeyboardShortcut = false;
                    getMBData(input,chooseID,mapID,dsMB);
                    drawLockInput(input[0], mapID);
                    if (!unlockSoChoWhileUpdate)
                        drawLockInput(input[1], mapID);
                        
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
                if (isEnter)
                {
                    isEnter = false;
                    if (mapID[562][525] == ID_BUTTON_ACPUPDATE_1)
                    {

                        unlockChoose = true;
                        chooseID = -1;
                        checkSaveInvalidMB(input, isInvalid);
                        if (isInvalid)
                        {
                            UpdateMB(input,dsMB);                          
                            outNumOfBoardDSMB(numOfPage, presentPage,dsMB);
                            drawBoard(board_DSMB, (presentPage - 1) * 10 + ID_BOARD_DSMB_1, mapID, shape);
                            outDSMB(board_DSMB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsMB);
                        }
                    }
                    else
                    {
                    
                        checkAddInvalidMB(input, isInvalid,dsMB);
                        if (isInvalid)
                        {
                            addMB(input,dsMB);
                            drawPageQLMB(mapID, shape, false);
                            alertAddSuccess();
                            outNumOfBoardDSMB(numOfPage, presentPage,dsMB);
                            if (presentPage < numOfPage)
                                presentPage++;
                            drawBoard(board_DSMB, (presentPage - 1) * 10 + ID_BOARD_DSMB_1, mapID, shape);
                            outDSMB(board_DSMB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsMB);
                            outNumOfBoardDSMB(numOfPage, presentPage,dsMB);
                        }
                    }
                }
                break;
            }
            case ID_BUTTON_ACPDEL_1://XAC NHAN XOA
            { 
                delMB(input,dsMB,dsCB);
                drawPageQLMB(mapID, shape, false);
                unlockChoose = true;
                unlockKeyboardShortcut = true;
                chooseID = -1;
                
                outNumOfBoardDSMB(numOfPage, presentPage,dsMB);
                if (presentPage > numOfPage)
                    presentPage--;
                outNumOfBoardDSMB(numOfPage, presentPage,dsMB);
                drawBoard(board_DSMB, (presentPage - 1) * 10 + ID_BOARD_DSMB_1, mapID, shape);
                outDSMB(board_DSMB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsMB);
				for(int i = 0 ; i < 3; i++)
					input[i].lastL = 0;               
                break;
            }
            case ID_BUTTON_ACPUPDATE_1: //LUU CAP NHAT
            {	        
                checkSaveInvalidMB(input, isInvalid);
                if (isInvalid)
                {
                    UpdateMB(input,dsMB);
                    drawPageQLMB(mapID, shape, false);
                    outNumOfBoardDSMB(numOfPage, presentPage,dsMB);
                    drawBoard(board_DSMB, (presentPage - 1) * 10 + ID_BOARD_DSMB_1, mapID, shape);
                    outDSMB(board_DSMB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsMB);
					for(int i = 0 ; i < 3; i++)
						input[i].lastL = 0;					    
                    unlockChoose = true;
                    unlockKeyboardShortcut = true;
                    chooseID = -1;
                }
                break;
            }
            case ID_BUTTON_UNDEL_1:
            case ID_BUTTON_UNUPDATE_1:
            {	//HUY XOA, CAP NHAT
            	
                resetButtonFrame(mapID);
                unlockChoose = true;
                unlockKeyboardShortcut = true;
                for (int i = 0; i < 3; i++)
                {
                    drawButton(Button_Add_Del_Update[i], ID_BUTTON_ADD_1 + i, mapID);
                    if (chooseID == -1)    
                        drawInput(input[i], mapID, ID_INPUT_SHMB_1 + i);
                    else
                    {
                        getMBData(input,chooseID,mapID,dsMB);
                        for (int i = 0; i < 3; i++);
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
        
        if (kbhit() && unlockKeyboardShortcut)
        {	
	 	           char c = getch();
	        if (c == 83)  //CHECK PHIM DELETE
	        {           	
	        
	            checkDelInvalidMB(input, isInvalid,dsMB,dsCB);
	            if (isInvalid)
	            {	
	            	
	                drawDelMBFrame(mapID, shape, input);
	                unlockChoose = false;
	                unlockKeyboardShortcut = false;
	                getMBData(input,chooseID,mapID,dsMB);
	                for (int i = 0; i < 3; i++)
	                    drawLockInput(input[i], mapID);
	            }
	        }
	        if (c == 59) //CHECK PHIM F1 (CAP NHAT)
	        {          	

	            checkUpdateInvalidMB(input, isInvalid, unlockSoChoWhileUpdate,dsMB,dsCB);
	            if (isInvalid)
	            {
	      			drawUpdateMBFrame(mapID, shape, input);
	                unlockChoose = false;
	                unlockKeyboardShortcut = false;
	                getMBData(input,chooseID,mapID,dsMB);
	                drawLockInput(input[0], mapID);
	                if (!unlockSoChoWhileUpdate)
	                    drawLockInput(input[1], mapID);
	            }
	        }
	    }				
        
    }
    clearDSMB(dsMB);
    clearDSCB(dsCB);
}
void checkHoverPageQLMB(short &ID, short lastID, Shape *shape, short **mapID)
{
	
    if (ismouseclick(WM_MOUSEMOVE))
    {	
 
		int x, y;
        getmouseclick(WM_MOUSEMOVE, x, y);
        ID = mapID[x][y]; 
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

void checkAddInvalidMB(Input *input, bool &isInvalid,DanhSachMayBay &dsMB)
{
	isInvalid = true;
    for (int i = 0; i < 3; i++)
    {
        if (input[i].lastL == 0)
            isInvalid = false;
    }
    MayBay newMB;
    if(isInvalid){
    	 if(timKiemMayBay(input[0].s, dsMB) != -1)
    	{
	        setText(1, 11, 12);
	        setfillstyle(1, 15);
	        bar(450, 530, 1000, 570);
	        outtextxy(590, 540, "THONG BAO: MAY BAY DA TON TAI!");
	        isInvalid = false;
	        return;
    	}
	}
    else
    {
        setText(1, 11, 12);
        setfillstyle(1, 15);
        bar(450, 530, 1000, 570);
        outtextxy(560, 540, "THONG BAO: BAN CHUA NHAP DU THONG TIN!");
    }
}

void addMB(Input *input,DanhSachMayBay &dsMB)
{	
    MayBay newMB;
    strcpy(newMB.soHieuMayBay, input[0].s);
    newMB.soCho = atoi(input[1].s);
    strcpy(newMB.loaiMayBay, input[2].s);
 //   themMayBayHopLe(newMB, dsMB);
    luuDSMayBay(dsMB);
}

void alertAddSuccess()
{
    setText(1, 11, 10);
    setfillstyle(1, 15);
    bar(450, 530, 1000, 570);
    outtextxy(570, 540, "THONG BAO: THEM MAY BAY THANH CONG!");
}

void checkDelInvalidMB(Input *input, bool &isInvalid,DanhSachMayBay &dsMB,DanhSachChuyenBay &dsCB)
{	
	isInvalid = true;
	setText(1, 11, 12);
	setfillstyle(1, 15);
	bar(450, 530, 1000, 570);	
    if (input[0].lastL == 0)
        isInvalid = false;
    if (isInvalid)
    {


        if (timKiemMayBay(input[0].s, dsMB) != -1)
        {
            if (ktMayBayDaCoChuyenBay(input[0].s, dsCB))
            {

                outtextxy(560, 540, "THONG BAO: MAY BAY DANG CO CHUYEN BAY!");
                isInvalid = false;
            }
        }
        else
        {
            outtextxy(580, 540, "THONG BAO: KHONG TIM THAY MAY BAY!");
            isInvalid = false;
        }
    }
    else
    {
        outtextxy(520, 540, "THONG BAO: VUI LONG NHAP SO HIEU HOAC CHON MAY BAY!");
    }
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



void delMB(Input *input,DanhSachMayBay &dsMB,DanhSachChuyenBay &dsCB)
{			
 //  xoaMayBayHopLe(input[0].s, dsMB, dsCB);
    luuDSMayBay(dsMB);
    luuDSChuyenBay(dsCB);
}


void checkUpdateInvalidMB(Input *input, bool &isInvalid, bool &unlockSoChoWhileUpdate,DanhSachMayBay &dsMB,DanhSachChuyenBay &dsCB)
{   
    isInvalid = true;
    unlockSoChoWhileUpdate = true;    
    if (input[0].lastL == 0)
        isInvalid = false;
    if (isInvalid)
    {

        if (timKiemMayBay(input[0].s, dsMB) != -1)
        {
            if (ktMayBayDaCoChuyenBay(input[0].s, dsCB))
            {
                unlockSoChoWhileUpdate = false;
            }
        }
        else
        {
            setText(1, 11, 12);
            setfillstyle(1, 15);
            bar(450, 530, 1000, 570);
            outtextxy(580, 540, "THONG BAO: KHONG TIM THAY MAY BAY!");
            isInvalid = false;
        }
    }
    else
    {
        setfillstyle(1, 15);
        bar(450, 530, 1000, 570);
        setText(1, 11, 12);
        outtextxy(520, 540, "THONG BAO: VUI LONG NHAP SO HIEU HOAC CHON MAY BAY!");
    }
}



void drawUpdateMBFrame(short **mapID, Shape *shape, Input *input)
{
    drawInput(input[1], mapID, ID_INPUT_SOCHO_1);
    drawInput(input[2], mapID, ID_INPUT_LMB_1);
    resetButtonFrame(mapID);
    Button del[2] = {{520, 480, 160, 40, BLUE_L, 15, "LUU"}, {740, 480, 160, 40, BLUE_L, 15, "HUY"}};
    for (int i = 0; i < 2; i++)
    {

        drawButton(del[i], ID_BUTTON_ACPUPDATE_1 + i, mapID);
        convertToShape(del[i], shape[ID_BUTTON_ACPUPDATE_1 + i]);
    }
}


void checkSaveInvalidMB(Input *input, bool &isInvalid)
{   
    isInvalid = true;      
    for (int i = 0; i < 3; i++)
    {
        if (input[i].lastL == 0)
            isInvalid = false;
        input[i].s[input[i].lastL] = '\0';
    }

    if (!isInvalid)
    {
		outAlert(RED,"BAN CHUA NHAP DU THONG TIN!");
    }
}



void UpdateMB(Input *input,DanhSachMayBay &dsMB)
{	

    int viTri = timKiemMayBay(input[0].s, dsMB);
    capNhatLoaiMB(input[2].s, viTri, dsMB);
    capNhatSoCho(atoi(input[1].s), viTri, dsMB);
    luuDSMayBay(dsMB);

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
            {
                setText();
                if (col == 1) //MA CB
                { 
                    outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 4.5 * strlen(dsTmp.cb[startCB - 1]->maChuyenBay),
                              y1 + (board.heightOfLine) / 2 - 10, dsTmp.cb[startCB - 1]->maChuyenBay);
                }
                else if (col == 2) //SO HIEU
                    outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 4.5 * strlen(dsTmp.cb[startCB - 1]->soHieuMayBay),
                              y1 + (board.heightOfLine) / 2 - 10, 	dsTmp.cb[startCB - 1]->soHieuMayBay);
                else if (col == 3)  //NGAY GIO KHOI HANH
                { 		
					char phut[5], gio[5],ngay[5],thang[5],nam[5],ngayGio[25];
					itoa(dsTmp.cb[startCB - 1]->ngayKhoiHanh.phut, phut, 10);
					itoa(dsTmp.cb[startCB - 1]->ngayKhoiHanh.gio, gio, 10);
					itoa(dsTmp.cb[startCB - 1]->ngayKhoiHanh.ngay, ngay, 10);
					itoa(dsTmp.cb[startCB - 1]->ngayKhoiHanh.thang, thang, 10);
					itoa(dsTmp.cb[startCB - 1]->ngayKhoiHanh.nam, nam, 10);
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
                    outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 2.5 * strlen(ngayGio),
                              y1 + (board.heightOfLine) / 2 - 10, ngayGio);
                }
                else if (col == 4) //SAN BAY DEN
                { 

                    outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 3.5 * strlen(dsTmp.cb[startCB - 1]->sanBayDen),
                              y1 + (board.heightOfLine) / 2 - 10, 	dsTmp.cb[startCB - 1]->sanBayDen);
                }
                else if (col == 5) //TRANG THAI
                { 	
            		char trangThai[15];
					if(dsTmp.cb[startCB - 1]->trangThai == 0) strcpy(trangThai,"HUY CHUYEN");
					if(dsTmp.cb[startCB - 1]->trangThai == 1)	strcpy(trangThai,"CON VE");
					if(dsTmp.cb[startCB - 1]->trangThai == 2)	strcpy(trangThai,"HUY VE");
					if(dsTmp.cb[startCB - 1]->trangThai == 3)	strcpy(trangThai,"HOAN TAT");
                    outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 3.5 * strlen(trangThai),
                              y1 + (board.heightOfLine) / 2 - 10, trangThai);						
                }                
            }
        }
        if (line >= 1)
            startCB++;
    }
}

            
void getMBData(Input *input,short ID,short **mapID,DanhSachMayBay &dsMB)
{


    ID -= ID_BOARD_DSMB_1; //lay ra vi tri cua MB trong ds
    if(input[0].lastL!=0)
    	ID = timKiemMayBay(input[0].s, dsMB);
    strcpy(input[0].s,dsMB.mayBay[ID]->soHieuMayBay);
    itoa(dsMB.mayBay[ID]->soCho, input[1].s, 10);
    strcpy(input[2].s,dsMB.mayBay[ID]->loaiMayBay);
    for(int i = 0; i <3;i++)
       input[i].lastL = strlen(input[i].s);
    
}    


void outNumOfBoardDSMB(int &numOfPage, int &presentPage,DanhSachMayBay &dsMB)
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

void outDSMB(Board &board, int startMB, int endMB,DanhSachMayBay &dsMB)
{
    char toChar[5];
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
            {
                setText();
                if (col == 1) //STT
                { 
                    itoa(startMB, toChar, 10);
                    outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 3 * strlen(toChar),
                              y1 + (board.heightOfLine) / 2 - 10, toChar);
                }
                else if (col == 2) //SO HIEU
                    outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 4.5 * strlen(dsMB.mayBay[startMB - 1]->soHieuMayBay),
                              y1 + (board.heightOfLine) / 2 - 10, dsMB.mayBay[startMB - 1]->soHieuMayBay);
                else if (col == 3) //LOAI
                { 
                    outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 4 * strlen(dsMB.mayBay[startMB - 1]->loaiMayBay),
                              y1 + (board.heightOfLine) / 2 - 10, dsMB.mayBay[startMB - 1]->loaiMayBay);
                }
                else if (col == 4) //SOCHO
                { 
                    itoa(dsMB.mayBay[startMB - 1]->soCho, toChar, 10);
                    outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 3.5 * strlen(toChar),
                              y1 + (board.heightOfLine) / 2 - 10, toChar);
                }
            }
        }
        if (line >= 1)
            startMB++;
    }
}
void chuanHoaInputQLMB(Input &input, short inputID){
    //gioi han lai so cho
    if (inputID == ID_INPUT_SOCHO_1 && input.lastL > 0 && atoi(input.s) < 20)
    {
        input.lastL = 2;
        input.s[0] = '2';
        input.s[1] = '0';
        input.s[2] = '\0';
    }
    else if (inputID == ID_INPUT_SOCHO_1 && atoi(input.s) > 300)
    {	
    	if(input.lastL>3){
    		setfillstyle(1,15);
    		bar(input.x1+1,input.y1+1,input.x1 + input.width -1, input.y1+29);
    	}
        input.lastL = 3;
        input.s[0] = '3';
        input.s[1] = '0';
        input.s[2] = '0';
        input.s[3] = '\0';
       	
		    
    }
	//xoa khoang cach o cuoi chuoi
	if(input.s[input.lastL - 1] == ' ')
		input.lastL--;
	
	input.s[input.lastL] = '\0';                               
}

