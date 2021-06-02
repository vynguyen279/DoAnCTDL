#pragma once
#include "reuse.h"

//====================PROTOTYPE==================
void drawPageQLCB(short **, Shape *);
void checkEventPageQLCB(short **, Shape *, Input *, Button *, Board &);
void makeBeautiInputNgayGioKH(Input *input);
void makeBeautiLockInputNgayGioKH(Input *input);
void drawInputPageQLCB(Input *input,short **mapID,bool unlockInput );
void chuanHoaInputQLCB(Input &input,short inputID);
void fixNgay(Input *input);
void getCBData(Input *input,short ID,short **mapID,DanhSachChuyenBay &dsCB,DanhSachTam &dsTmp);
void checkHoverPageQLCB(short &ID, short lastID, Shape *shape, short **mapID);
void outNumOfBoardDSCB(int &numOfPage, int presentPage,DanhSachTam &dsTmp);
void drawUpdateCBFrame(Input *input,short **mapID,Shape *shape);
void drawCancelCBFrame(short **mapID, Shape *shape);
void updateCB(Input *input,bool &isInvalid,short chooseID,DanhSachMayBay &dsMB,DanhSachChuyenBay &dsCB,DanhSachTam &dsTmp);
void cancelCB(short ID,bool &isInvalid,DanhSachChuyenBay &dsCB,DanhSachTam &dsTmp);
void addCB(Input *input,bool &isInvalid, DanhSachMayBay &dsMB,DanhSachChuyenBay &dsCB,DanhSachTam &dsTmp);
void getInputPageQLCB(Input &input, short &inputID, bool &isEnter);
void outDSCB(Board &board, int startCB, int endCB,DanhSachTam &dsTmp);


//================================================

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
                else if ((ID_INPUT_DAY_2 <= inputID && inputID <= ID_INPUT_MINUTE_2) ||(ID_INPUT_FILLTIMED_2 <= inputID && inputID <= ID_INPUT_FILLTIMEY_2)  && '0' <= c && c <= '9')
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


void addCB(Input *input,bool &isInvalid, DanhSachMayBay &dsMB,DanhSachChuyenBay &dsCB,DanhSachTam &dsTmp)
{	
	char alert[40];
	NgayThangNam ngayKH = newNgayThangNam(atoi(input[2].s), atoi(input[3].s), atoi(input[4].s), atoi(input[5].s), atoi(input[6].s));
	ChuyenBay newCB = newChuyenBay(input[0].s,ngayKH, input[8].s, input[1].s);
	NodeChuyenBay *newNodeCB = newNodeChuyenBay(newCB);
	isInvalid = themChuyenBayHopLe(newNodeCB,dsCB, dsMB, dsTmp, alert);
	if(isInvalid) {
		luuDSChuyenBay(dsCB);
		outAlert(GREEN,alert);
	}
	else outAlert(RED,alert);	
			
}

void cancelCB(short ID,bool &isInvalid,DanhSachChuyenBay &dsCB,DanhSachTam &dsTmp){
	char alert[40];

	ID-= ID_BOARD_DSCB_2;  //lay ra ID cua CB trong dsCB
	isInvalid = huyChuyenBay(dsTmp.cb[ID],alert);	
	if(isInvalid){
		luuDSChuyenBay(dsCB);
		outAlert(GREEN,alert);
	}
	else outAlert(RED,alert);
	
}

void updateCB(Input *input,bool &isInvalid,short chooseID,DanhSachMayBay &dsMB,DanhSachChuyenBay &dsCB,DanhSachTam &dsTmp){
	char alert[40];
	NgayThangNam dtUpdate = newNgayThangNam(atoi(input[2].s), atoi(input[3].s), atoi(input[4].s), atoi(input[5].s), atoi(input[6].s));
	isInvalid = capNhatNgayThangNam(dsCB, dsTmp.cb[chooseID - ID_BOARD_DSCB_2], dtUpdate, alert);
	if(isInvalid) {
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

void outNumOfBoardDSCB(int &numOfPage, int presentPage,DanhSachTam &dsTmp){

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

void checkHoverPageQLCB(short &ID, short lastID, Shape *shape, short **mapID)
{

    if (ismouseclick(WM_MOUSEMOVE))
    {
        int x, y;
        getmouseclick(WM_MOUSEMOVE, x, y);
        ID = mapID[x][y];
        //IN HOVER: MOI HOVER DEU MAU DEN
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
void getCBData(Input *input,short ID,short **mapID,DanhSachChuyenBay &dsCB,DanhSachTam &dsTmp){

	
  //============================================== viet code get vi tri cua ma chuyen bay khi nguoi dungn hap shmb 
  	ID -= ID_BOARD_DSCB_2; //lay ra ID cua CB trong dsCB
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
