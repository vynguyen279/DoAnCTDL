#include "MainPage.h"


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
		
		char alert[40] = ""; 
		NgayThangNam dtFill = newNgayThangNam(atoi(input[0].s), atoi(input[1].s), atoi(input[2].s));	
		dsFill = dsCBvoiNgayKhoiHanh(dtFill, dsCB,alert);
		if(strlen(alert) == 0){
			isInvalid = true;
		}
		else if (strlen(alert) == 0){
			isInvalid = false;
			clearDSTmp(dsFill);
			outAlert(RED,alert);
		}
		
	}
	else{
		isInvalid = false;
	}
	
}
void drawLockButton(Button &button,short **mapID){

    if(button.content[0] == '<' || button.content[0] == '>')
    	setText(2, 10, 0, SILVER);
	else 
		setText(1, 11, 0, SILVER); 
    setfillstyle(1, SILVER);
    bar(button.x1, button.y1, button.x1 + button.width, button.y1 + button.height);
    //=========outButtonText===========
    
    if (strlen(button.content) < 8 || strlen(button.content) >= 13)
        outtextxy(button.x1 + button.width / 2 - 4.3 * strlen(button.content), button.y1 + (button.height) / 2 - 10, button.content);
    else if (strlen(button.content) < 13)
        outtextxy(button.x1 + button.width / 2 - 3.9 * strlen(button.content), button.y1 + (button.height) / 2 - 10, button.content);
    setcolor(SILVER);
    rectangle(button.x1, button.y1, button.x1 + button.width, button.y1 + button.height);
    setID(button.x1, button.y1, button.width, button.height, -1, mapID);			
}
void lockPageQLCB(Button *pre_next_Board, Button *fill,short **mapID){
	drawLockButton(pre_next_Board[0],mapID);
	drawLockButton(pre_next_Board[1],mapID);
	drawLockButton(fill[0],mapID);
	drawLockButton(fill[3],mapID);
	
	
}


void unlockPageQLCB(Button *pre_next_Board, Button *fill,short **mapID){
	drawButton(pre_next_Board[0],ID_BUTTON_PREBOARD_DSCB_2,mapID);
	drawButton(pre_next_Board[1],ID_BUTTON_NEXTBOARD_DSCB_2,mapID);
	drawButton(fill[0],ID_BUTTON_FILL_CB_2,mapID);
	drawButton(fill[3],ID_BUTTON_UNFILL_CB_2,mapID);	
}

void outCB(Board &board,DanhSachTam &dsTmp, short ID){
	setText();
	ID-=ID_BOARD_DSCB_2;
    short x1 = board.x1,
	 y1 = (ID%10 + 1) * board.heightOfLine + board.y1, 
	 x2 = x1, 
	 y2 = y1 +30;
    for(int col = 1; col<=board.numOfCol; col++){
    	x2 += board.widthOfCol[col - 1];
    	rectangle(x1,y1, x2, y2);
    	 
               
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
					strcat(ngayGio,thang);              setText();
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
                    outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 2.5 * strlen(ngayGio),
                              y1 + (board.heightOfLine) / 2 - 10, ngayGio);
                }
                else if (col == 4) //SAN BAY DEN
                { 

                    outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 3.5 * strlen(dsTmp.cb[ID]->sanBayDen),
                              y1 + (board.heightOfLine) / 2 - 10, 	dsTmp.cb[ID]->sanBayDen);
                }
                else if (col == 5) //TRANG THAI
                { 	
            		char trangThai[15];
					if(dsTmp.cb[ID]->trangThai == 0) strcpy(trangThai,"HUY CHUYEN");
					if(dsTmp.cb[ID]->trangThai == 1)	strcpy(trangThai,"CON VE");
					if(dsTmp.cb[ID]->trangThai == 2)	strcpy(trangThai,"HUY VE");
					if(dsTmp.cb[ID]->trangThai == 3)	strcpy(trangThai,"HOAN TAT");
                    outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 3.5 * strlen(trangThai),
                              y1 + (board.heightOfLine) / 2 - 10, trangThai);						
                }
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

                    outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 3.5 * strlen(dsTmp.cb[ID]->sanBayDen),
                              y1 + (board.heightOfLine) / 2 - 10, 	dsTmp.cb[ID]->sanBayDen);
                }
                else if (col == 5) //TRANG THAI
                { 	
            		char trangThai[15];
					if(dsTmp.cb[ID]->trangThai == 0) strcpy(trangThai,"HUY CHUYEN");
					if(dsTmp.cb[ID]->trangThai == 1)	strcpy(trangThai,"CON VE");
					if(dsTmp.cb[ID]->trangThai == 2)	strcpy(trangThai,"HUY VE");
					if(dsTmp.cb[ID]->trangThai == 3)	strcpy(trangThai,"HOAN TAT");
                    outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 3.5 * strlen(trangThai),
                              y1 + (board.heightOfLine) / 2 - 10, trangThai);						
                }  	
    		 x1 = x2;
    }	
} 
void outCBUpdated(Board &board,DanhSachTam &dsTmp,short ID){
	setText();
	ID-=ID_BOARD_DSCB_2;
    short x1 = board.x1,
	 y1 = (ID%10 + 1) * board.heightOfLine + board.y1, 
	 x2 = x1, 
	 y2 = y1 +30;
 	setfillstyle(1,WHITE);	
    bar(x1,y1,x1+900,y1 + 30);
    for(int col = 1; col<=board.numOfCol; col++){
    	x2 += board.widthOfCol[col - 1];
    	rectangle(x1,y1, x2, y2);
    	 
               
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
					strcat(ngayGio,thang);              setText();
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
                    outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 2.5 * strlen(ngayGio),
                              y1 + (board.heightOfLine) / 2 - 10, ngayGio);
                }
                else if (col == 4) //SAN BAY DEN
                { 

                    outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 3.5 * strlen(dsTmp.cb[ID]->sanBayDen),
                              y1 + (board.heightOfLine) / 2 - 10, 	dsTmp.cb[ID]->sanBayDen);
                }
                else if (col == 5) //TRANG THAI
                { 	
            		char trangThai[15];
					if(dsTmp.cb[ID]->trangThai == 0) strcpy(trangThai,"HUY CHUYEN");
					if(dsTmp.cb[ID]->trangThai == 1)	strcpy(trangThai,"CON VE");
					if(dsTmp.cb[ID]->trangThai == 2)	strcpy(trangThai,"HUY VE");
					if(dsTmp.cb[ID]->trangThai == 3)	strcpy(trangThai,"HOAN TAT");
                    outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 3.5 * strlen(trangThai),
                              y1 + (board.heightOfLine) / 2 - 10, trangThai);						
                }
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

                    outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 3.5 * strlen(dsTmp.cb[ID]->sanBayDen),
                              y1 + (board.heightOfLine) / 2 - 10, 	dsTmp.cb[ID]->sanBayDen);
                }
                else if (col == 5) //TRANG THAI
                { 	
            		char trangThai[15];
					if(dsTmp.cb[ID]->trangThai == 0) strcpy(trangThai,"HUY CHUYEN");
					if(dsTmp.cb[ID]->trangThai == 1)	strcpy(trangThai,"CON VE");
					if(dsTmp.cb[ID]->trangThai == 2)	strcpy(trangThai,"HUY VE");
					if(dsTmp.cb[ID]->trangThai == 3)	strcpy(trangThai,"HOAN TAT");
                    outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 3.5 * strlen(trangThai),
                              y1 + (board.heightOfLine) / 2 - 10, trangThai);						
                }  	
    		 x1 = x2;
    }
}
 
void unChooseCB(Input *input, short &chooseID,bool &unlockChoose, Shape *shape, short **mapID){
    setcolor(15);
    setfillstyle(1, 15);
    fillellipse(shape[chooseID].x1 - 13, shape[chooseID].y1 + 10, 5, 5);
    unlockChoose = true;
    chooseID = -1;
    for(int i = 0; i < 9;i++)
    	input[i].lastL = 0;
	drawInputPageQLCB(input,mapID,true);
	
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
void checkEventPageQLCB(short **mapID, Shape *shape, Input *input, Button *button_Add_Cancel_Update, Board &board_DSCB,Button *buttonFill,Input *inputFill,Button *pre_next_Board){	

	DanhSachMayBay dsMB;
	layDSMayBay(dsMB);
	DanhSachChuyenBay dsCB = NULL;
	layDSChuyenBay(dsCB);
	DanhSachTam dsFill; 
	DanhSachTam dsDefault = dsNode2DsTmp(dsCB);
	DanhSachTam dsTmp = dsDefault;
    short ID = -1, lastID = -1, chooseID = -1;
    bool isInvalid = true;                                          //check xem du lieu can them,xoa,sua co hop le hay khong
    bool unlockChoose = true;                                       //khi dang update thi se khong cho chon may bay nua
    bool isEnter = false;                                           //check enter khi dang input
    bool unlockKeyboardShortcut = true;
    bool isFill = false;
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
		                drawInputPageQLCB(input,mapID,false);
		                lockPageQLCB(pre_next_Board,buttonFill,mapID);	
		                    
		            }
		            else if (chooseID != -1 && ID == chooseID && unlockChoose) //NHAP VAO CAI DANG CHON DE HUY
		            { 
						unChooseCB(input,chooseID,unlockChoose,shape,mapID);
						unlockPageQLCB(pre_next_Board,buttonFill,mapID);
		            }
            	}
            }
			//end xu ly chon			
		    if(ID>=ID_BUTTON_PAGE_MAIN && ID<=ID_BUTTON_PAGE4 && ID != ID_BUTTON_PAGE_QLCB){            
				clearDSMB(dsMB);
				clearDSCB(dsCB);
				clearDSTmp(dsTmp);
				clearDSTmp(dsFill);
				clearDSTmp(dsDefault);
            	return;
            }		
			
			switch (ID){
            case ID_BUTTON_PREBOARD_DSCB_2: //PRE PAGE
            {
                if (presentPage > 1)
                {
                    presentPage--;         			               
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
                   	outNumOfBoardDSCB(numOfPage, presentPage,dsTmp);					         					                                       
                    outNumOfBoardDSCB(numOfPage, presentPage,dsTmp);                   
                    drawBoard(board_DSCB, (presentPage - 1) * 10 + ID_BOARD_DSCB_2, mapID, shape);
                    outDSCB(board_DSCB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsTmp);
				}
                break;
            }
			case ID_BUTTON_ADD_CB_2: //THEM CB
			{		

                    addCB(input,isInvalid,dsMB,dsCB,dsDefault); 					                                 
                    if(isInvalid){
                    	
						if(isFill){ 
							//huy fill
							dsTmp = dsDefault;
							isFill = false;
							presentPage = 1;	
							for(int i = 0; i <4; i++){
								inputFill[i].lastL = 0;
								drawInput(inputFill[i],mapID,ID_INPUT_FILLTIMED_2 + i);
							}
							makeBeautiFillInput(inputFill);							
						}
												 		                
		                outNumOfBoardDSCB(numOfPage, presentPage,dsTmp);
						if(presentPage == numOfPage){
							//in ra chuyen bay moi them vao cuoi danh sach
							
							
						}
						else{
		                    presentPage = numOfPage; 
		                	drawBoard(board_DSCB, (presentPage - 1) * 10 + ID_BOARD_DSCB_2, mapID, shape);
		                    outDSCB(board_DSCB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsTmp);
							outNumOfBoardDSCB(numOfPage, presentPage,dsTmp);								
						} 	  				

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
					outAlert(RED,"BAN CHUA CHON CHUYEN BAY!");
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
					outAlert(RED,"BAN CHUA CHON CHUYEN BAY!");					
				}
				
				break;
			}
			case ID_BUTTON_ACPCANCEL_CB_2:{  //XAC NHAN HUY
				cancelCB(chooseID,isInvalid,dsCB,dsTmp);		
                if(isInvalid){  		                
		            unlockKeyboardShortcut = true;
                    outCBUpdated(board_DSCB,dsTmp,chooseID);                  
		            unlockPageQLCB(pre_next_Board,buttonFill,mapID);
					unChooseCB(input,chooseID,unlockChoose,shape,mapID);  		            
                    resetButtonFrame(mapID); 
		            for(int i = 0; i < 3; i++){
						drawButton(button_Add_Cancel_Update[i], ID_BUTTON_ADD_CB_2 +i,mapID);	
		            }                    					                    	
				}				
				break;
			}			
			case ID_BUTTON_ACPUPDATE_CB_2:{  //XAC NHAN CAP NHAT
				
				updateCB(input,isInvalid,chooseID,dsMB,dsCB,dsTmp);
                if(isInvalid){

                    outCBUpdated(board_DSCB,dsTmp,chooseID);  		            
		            outCBUpdated(board_DSCB,dsTmp,chooseID);
		            unlockPageQLCB(pre_next_Board,buttonFill,mapID);
					unChooseCB(input,chooseID,unlockChoose,shape,mapID);     
                    resetButtonFrame(mapID);
		            for(int i = 0; i < 3; i++){
						drawButton(button_Add_Cancel_Update[i], ID_BUTTON_ADD_CB_2 +i,mapID);	
		            }  						                    	
				}
				break;
			}
			case ID_BUTTON_UNCANCEL_CB_2: //HUY HUY CB
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
				fillCB(inputFill,isInvalid,dsCB,dsFill);
				if(isInvalid){
				presentPage = 1;
				isFill = true;
				dsTmp = dsFill;
                outNumOfBoardDSCB(numOfPage, presentPage,dsTmp);                   
                drawBoard(board_DSCB, (presentPage - 1) * 10 + ID_BOARD_DSCB_2, mapID, shape);
                outDSCB(board_DSCB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsTmp);	
											
				}
				break;
			}
			case ID_BUTTON_UNFILL_CB_2:{  //UNFILL
				if(isFill){
				presentPage = 1;
				isFill = false;
				dsTmp = dsDefault;	
                outNumOfBoardDSCB(numOfPage, presentPage,dsTmp);                   
                drawBoard(board_DSCB, (presentPage - 1) * 10 + ID_BOARD_DSCB_2, mapID, shape);
                outDSCB(board_DSCB, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsTmp);
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
			case ID_INPUT_FILLTIMED_2:{  //FILL DAY
				getInputPageQLCB(inputFill[0],ID,isEnter);
				if(inputFill[0].lastL * inputFill[1].lastL * inputFill[2].lastL !=0)   //fix lai ngay trong fill neu nguoi dung nhap nam nhuan
					fixNgayFill(inputFill);		
				break;
			}
			case ID_INPUT_FILLTIMEM_2:{  //FILL MONTH
				getInputPageQLCB(inputFill[1],ID,isEnter);
				if(inputFill[0].lastL * inputFill[1].lastL * inputFill[2].lastL !=0)   
					fixNgayFill(inputFill);				
				break;
			}
			case ID_INPUT_FILLTIMEY_2:{  //FILL YEAR
				getInputPageQLCB(inputFill[2],ID,isEnter);
				if(inputFill[0].lastL * inputFill[1].lastL * inputFill[2].lastL !=0)   
					fixNgayFill(inputFill);					
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
			    if(input[2].lastL * input[3].lastL * input[4].lastL !=0) //fix lai ngay neu nguoi dung nhap nam nhuan
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

	//FILLT
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
	setText();
	outtextxy(275,80,"NGAY GIO K.H:");	
	outtextxy(506,101,"SAN BAY DEN:");		
		
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
	
	
	checkEventPageQLCB(mapID,shape,input,button_Add_Cancel_Update,board_DSCB,buttonFill,inputFill,pre_next_Board);
	for (int i = 0; i < 9; i++)
	    delete[] input[i].s;		
}
int main(){	
	drawMainPage();
	getch();
	return 0;
}




