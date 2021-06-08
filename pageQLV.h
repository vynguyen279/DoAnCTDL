
#pragma once
#include "reuse.h"
#include <math.h>
#define GRAY COLOR(156, 156, 156)


//===============ID DSCB================
#define ID_DSCB_BOARD_3 50
#define ID_DSCB_PRE_BUTTON_3 5 
#define ID_DSCB_NEXT_BUTTON_3 6  
#define ID_ENTER_BUTTON_3 7    //!
#define ID_MA_CB_INPUT_3 30
//===============ID DS HANH KHACH================
#define ID_DS_VE_BOARD_3 50
#define ID_DS_Ve_PRE_BUTTON_3 5
#define ID_DS_Ve_NEXT_BUTTON_3 6
#define ID_ORDER_TICKET_BUTTON_3 8 //!
#define ID_CANCEL_TICKET_BUTTON_3 9
#define ID_DSCB_BOARD_BUTTON_3 10 //!
#define ID_NAME_INPUT_3 31
#define ID_SEAT_NUMBER_INPUT_3 32
#define ID_CMND_INPUT_3 33
#define ID_GENDER_INPUT_3 34
//===============ID SEAT MAP================

#define ID_SEAT_MAP_PRE_BUTTON 5
#define ID_SEAT_MAP_NEXT_BUTTON 6
#define ID_CONFIRM_TICKET_BUTTON 11 //!
#define ID_CANCEL_BUTTON 12 //!
#define ID_FIRST_SEAT 50
#define ID_LAST_SEAT 409

//===========================PROTOTYPE========================================
void drawPageQLV_DSCB(short **mapID,Shape *shape);
void drawPageQLV_DSHK(short **mapID,Shape *shape);
void drawPageQLV_DatVe(short **mapID,Shape *shape);
//===========================XU LY=============================================
void colorNotWorkingSeat(Button *button,Shape *shape,short **mapID){
	int  inputSeat = 59; //dung ham get input
	int So_ghe_khong_hd = 72-inputSeat; 
	float n = So_ghe_khong_hd/6.0;
	int j = ceil(n)*6 - So_ghe_khong_hd;
	int i= 12-floor((So_ghe_khong_hd/6));
	if(inputSeat%6!=0)
	i--;
	short x,y;
	for( i ;i <12;i++){
		 x=450+40*i;
		for( j;j<6;j++){
			 y=175+45*j;
			 button[i].x1= x;
			button[i].y1 = y;
		    button[i].width = 35;
			button[i].height = 35;
			button[i].fillColor = GRAY;
			button[i].borderColor = GRAY; 
			drawButton(button[i],-1,mapID);
		    convertToShape(button[i], shape[-1]);
		}
		j=0;
	}
}
DanhSachTam dsCBConVe( DanhSachChuyenBay &dsCB) {
	DanhSachTam dsTmp;
	initDanhSachTam(dsTmp);
	NodeChuyenBay *nodeChay = dsCB;
	for(; nodeChay != NULL; nodeChay = nodeChay->next) {
		capNhatTrangThaiHoanTat(nodeChay->chuyenBay);
		if(nodeChay->chuyenBay.trangThai==1)
			themPhanTuVaoDSTmp(&(nodeChay->chuyenBay), dsTmp);
	}
	return dsTmp;
}
void resetNumber(){
	setfillstyle(1, 15);
    bar(450, 150, 450+480, 150+20);
}
void resetSeatMap(short **mapID){
	setfillstyle(1, 15);
    bar(445, 170, 445+500, 170+270);
    setID(445,170,501,300,-1,mapID);
}
void PrintPresentPage(short presentPage){
	short start = 1+12*(presentPage-1);
	short end = start+11;
	short count = 1;
	setText(2,10,0,15);
	char pchar[5];
   for(int i=start;i<=end;i++){
   	 	itoa(i,pchar,10);
     if(i>=10)
     outtextxy(455+40*(count-1), 150, pchar);
     else
   	 outtextxy(460+40*(count-1), 150, pchar);
   	 count++;
   }
}
void drawSeatMap(short **mapID, Shape *shape, short presentPage){
	Button button_seat[360];
    for(int i = 0;i<360;i++)
      	button_seat[i]={0,0,0,0,0,0};

	short x,y,ID,temp,vtr, tempVtr;
	for(int i = 0;i <12;i++){
		 x=450+40*i;
		 temp = 50+6*i+72*(presentPage-1);
		 tempVtr = 0+6*i+72*(presentPage-1);
		for(int j=0;j<6;j++){
			 y=175+45*j;
			 ID=temp+j;
			 vtr = tempVtr+j;
			button_seat[vtr].x1= x;
			button_seat[vtr].y1 = y;
		    button_seat[vtr].width = 35;
			button_seat[vtr].height = 35;
			button_seat[vtr].fillColor = 15;
			button_seat[vtr].borderColor = 0; 
			drawButton(button_seat[vtr],ID,mapID);///////////////////ID tu 50 
		    convertToShape(button_seat[vtr], shape[ID]);
        }
    }
}
void updateNumOfBoardDSCB_conve(int &numOfPage, int presentPage,DanhSachTam &dsTmp){
	numOfPage = (dsTmp.n - 1) / 10 + 1;
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
void outCB_conve(Board &board,DanhSachTam &dsTmp, short ID){
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
		    if(dsTmp.cb[ID]->trangThai == 1)	strcpy(trangThai,"CON VE");
            outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 4 * strlen(trangThai),
                      y1 + (board.heightOfLine) / 2 - 10, trangThai);						
        }        	
    }
} 

//==========================Page QLV=======================================

void checkHoverPageQLV_DSHK(short &newID, short lastID, Shape *shape, short **mapID){
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
            if (lastID >= ID_NAME_INPUT_3)
                setcolor(WHITE);
            else
                setcolor(BLUE_L);
            rectangle(shape[lastID].x1, shape[lastID].y1, shape[lastID].x1 + shape[lastID].width, shape[lastID].y1 + shape[lastID].height);
        }

    }
}
void checkHoverPageQLV_DSCB(short &newID, short lastID, Shape *shape, short **mapID)
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
            if (lastID >= ID_MA_CB_INPUT_3)
                setcolor(WHITE);
            else
                setcolor(BLUE_L);
            rectangle(shape[lastID].x1, shape[lastID].y1, shape[lastID].x1 + shape[lastID].width, shape[lastID].y1 + shape[lastID].height);
        }

    }
}
void checkHoverPageQLV_DatVe(short &newID, short lastID, Shape *shape, short **mapID){
         if (ismouseclick(WM_MOUSEMOVE))
    {	
 			
		int x, y;
        getmouseclick(WM_MOUSEMOVE, x, y);
        newID = mapID[x][y];
        short ID = newID;
		   
        //IN HOVER: MOI HOVER DEU MAU DEN
        if (ID > 0 && ID != lastID)
        {    
           if(ID>=ID_FIRST_SEAT&&ID<=ID_LAST_SEAT)
             {
             	setfillstyle(1,BLUE_L);
             	bar(shape[ID].x1, shape[ID].y1, shape[ID].x1 + shape[ID].width+2, shape[ID].y1 + shape[ID].height+2);
			 }
           else{
             setcolor(BLACK);
             rectangle(shape[ID].x1, shape[ID].y1, shape[ID].x1 + shape[ID].width, shape[ID].y1 + shape[ID].height);
         }
        }
        //OUT HOVER :VOI INPUT SE TO LAI MAU DEN, VOI BUTTON SE TO LAI MAU BLUE_L
        if (ID != lastID && lastID > 0)
        {
            if (lastID >= ID_NAME_INPUT_3 && lastID <=ID_GENDER_INPUT_3){
                setcolor(WHITE);
                rectangle(shape[lastID].x1, shape[lastID].y1, shape[lastID].x1 + shape[lastID].width, shape[lastID].y1 + shape[lastID].height);
               }
             else if (lastID>=ID_BUTTON_PAGE_QLMB&&lastID<=ID_CANCEL_BUTTON){
                setcolor(BLUE_L);
                rectangle(shape[lastID].x1, shape[lastID].y1, shape[lastID].x1 + shape[lastID].width, shape[lastID].y1 + shape[lastID].height);
               } 
            else if(lastID>=ID_FIRST_SEAT&&lastID<=ID_LAST_SEAT){
                setfillstyle(1,WHITE);
             	bar(shape[lastID].x1, shape[lastID].y1, shape[lastID].x1 + shape[lastID].width+1, shape[lastID].y1 + shape[lastID].height+1);
             	setcolor(BLACK);
             	rectangle(shape[lastID].x1, shape[lastID].y1, shape[lastID].x1 + shape[lastID].width+1, shape[lastID].y1 + shape[lastID].height+1);
                }
		 }

    }
}



void checkEventPageQLV_DSHK(Shape *shape, short **mapID){
    int x, y;
    short ID = -1, lastID = -1;
    clearmouseclick(WM_LBUTTONDOWN);	
	while(true){
		delay(DELAY_TO_CHECK_EVENT);
        checkHoverPageQLV_DSHK(ID, lastID, shape, mapID);
        lastID = ID;
		if(ismouseclick(WM_LBUTTONDOWN))
			{
				if(ID>=ID_BUTTON_PAGE_MAIN && ID<=ID_BUTTON_PAGE4 && ID != ID_BUTTON_PAGE_QLV){            
            		return;
            	}
				switch(ID){
					case ID_DSCB_BOARD_BUTTON_3:
					case ID_ORDER_TICKET_BUTTON_3 :{

						return;
					}
					default:
						break;
				}
					clearmouseclick(WM_LBUTTONDOWN);  				 
			}
	}	
}
void checkEventPageQLV_DatVe(Shape *shape, short **mapID){
    int x, y;
    short ID = -1, lastID = -1, presentPage = 1;
    short totalPage= 4;// dung ham lay so cho
    clearmouseclick(WM_LBUTTONDOWN);
	PrintPresentPage(presentPage);
	drawSeatMap(mapID,shape,presentPage);
	while(true){
		delay(DELAY_TO_CHECK_EVENT);
		checkHoverPageQLV_DatVe(ID, lastID, shape, mapID);
        lastID = ID;
        cout<<ID;
		if(ismouseclick(WM_LBUTTONDOWN))
			{
				cout<<ID;
				if(ID>=ID_BUTTON_PAGE_MAIN && ID<=ID_BUTTON_PAGE4 && ID != ID_BUTTON_PAGE_QLV){            
            		return;
            	}
				switch(ID){
					case ID_CONFIRM_TICKET_BUTTON:
					case ID_CANCEL_BUTTON :{
						return;
					}
					case ID_SEAT_MAP_PRE_BUTTON:{
						if(presentPage > 1){
							presentPage--;
							resetNumber();
							PrintPresentPage(presentPage);
//                            resetSeatMap(mapID);
//                            drawSeatMap(mapID,shape,presentPage);
						}
						break;
					}
					case ID_SEAT_MAP_NEXT_BUTTON:{
						if(presentPage < totalPage){
							presentPage++;
							resetNumber();
							PrintPresentPage(presentPage);
//							resetSeatMap(mapID);
//                            drawSeatMap(mapID,shape,presentPage);
						}
						break;
					}
					
					default:
						break;
				} 
					clearmouseclick(WM_LBUTTONDOWN); 
			}
	}
}
void checkEventPageQLV_DSCB(Shape *shape, short **mapID,Input *input, Button *pre_next_Board, Board &board_DSCB_conve){
	DanhSachMayBay dsMB;
	layDSMayBay(dsMB);
	DanhSachChuyenBay dsCB = NULL;
	layDSChuyenBay(dsCB);
	DanhSachTam dsDefault = dsNode2DsTmp(dsCB);
	DanhSachTam dsTmp = dsDefault;
	DanhSachTam dsFill;
	
    int x = 0, y = 0;
    short ID = -1, lastID = -1, presentPage=1,chooseID = -1;
    int numOfPage = (dsTmp.n - 1) / 10 + 1;
    
    updateNumOfBoardDSCB_conve(numOfPage, presentPage,dsTmp);
    drawBoard(board_DSCB_conve,ID_DSCB_BOARD_3,mapID,shape);
    dsFill = dsCBConVe(dsCB);
	outDSCB(board_DSCB_conve, 1, 10,dsFill);
	
    clearmouseclick(WM_LBUTTONDOWN);	
	while(true){
		delay(DELAY_TO_CHECK_EVENT);
        checkHoverPageQLV_DSCB(ID, lastID, shape, mapID);
        lastID = ID;
		if(ismouseclick(WM_LBUTTONDOWN))
			{
				cout << ismouseclick(WM_LBUTTONDOWN);
				if(ID>=ID_BUTTON_PAGE_MAIN && ID<=ID_BUTTON_PAGE4 && ID != ID_BUTTON_PAGE_QLV ){            
            		return;
            	}
				switch(ID){
					case ID_ENTER_BUTTON_3 :{
						return;
					}
					case ID_DSCB_PRE_BUTTON_3:{
						if (presentPage > 1)
                        {
                           presentPage--;         			               
                   	       updateNumOfBoardDSCB_conve(numOfPage, presentPage,dsTmp);
                           drawBoard(board_DSCB_conve, (presentPage - 1) * 10 + ID_DSCB_BOARD_3, mapID, shape);
                           outDSCB(board_DSCB_conve, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsFill);
            	        }
						break;
					}
					case ID_DSCB_NEXT_BUTTON_3:{
                        if (presentPage < numOfPage)
                        {
                           presentPage++;  	                			               
                   	       updateNumOfBoardDSCB_conve(numOfPage, presentPage,dsTmp);					         					                                       
                           drawBoard(board_DSCB_conve, (presentPage - 1) * 10 + ID_DSCB_BOARD_3, mapID, shape);
                           outDSCB(board_DSCB_conve, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsFill);
				        }
                        break;
                    }
                    	case ID_MA_CB_INPUT_3:{
				getCBData(input,chooseID,dsCB,dsTmp);				                                 			
				break;
			}
					default:
						break;
				}
				clearmouseclick(WM_LBUTTONDOWN); 				 
			}
	}	
}
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

//==========================Page DS CB======================================

void drawPageQLV_DSCB(short **mapID,Shape *shape){
	setDefaultRightFrame(mapID);	

	setText(6,10);
	outtextxy(410,30,"DANH SACH CHUYEN BAY");
	Button pre_next_Board[2] = {{640,90,25,25,BLUE_L,15,"<"},{720,90,25,25,BLUE_L,15,">"}};
	for(int i = 0;i <2;i++){
		setText(2,10,0,BLUE_L);
		drawButton(pre_next_Board[i],ID_DSCB_PRE_BUTTON_3+i,mapID);///////////////////ID
		convertToShape(pre_next_Board[i],shape[i+ID_DSCB_PRE_BUTTON_3]);///////////////////ID
	}


	Board board_DSCB_conve = {275,130,10,30,5,{125,125,180,350,120},{"MA CB","SO HIEU MB","NGAY GIO KHOI HANH","SAN BAY DEN","TRANG THAI"}};

	setcolor(0);
    rectangle(275, 470, 1175, MAX_H);     


	Input input[1]= {625,569,15,250,0};
	input[0].s = new char[input[0].max+2];	
    drawInput(input[0], mapID,ID_MA_CB_INPUT_3);///////////////////ID
    convertToShape(input[0], shape[ID_MA_CB_INPUT_3]);///////////////////ID
	setText();
	outtextxy(500,575,"MA CHUYEN BAY:");

	Button Enter_button[1] ={890,568,50,30,BLUE_L,BLUE_L,">>"} ;
 	setText(2, 10, 0, BLUE_L);
    drawButton(Enter_button[0], ID_ENTER_BUTTON_3 , mapID);
    convertToShape(Enter_button[0], shape[ID_ENTER_BUTTON_3]);
    
    checkEventPageQLV_DSCB(shape,mapID,input, pre_next_Board,board_DSCB_conve);
    
    delete[] input[0].s;
}

//===========================Page Ds Hanh Khach TrongCB==========================

void drawPageQLV_DSHK(short **mapID,Shape *shape){
	setDefaultRightFrame(mapID);	

	setText(5,10);
	outtextxy(550,0,"DANH SACH VE");
	Button pre_next_Board[2] = {{640, 90, 25, 25, BLUE_L, 15, "<"}, {720, 90, 25, 25, BLUE_L, 15, ">"}};
    for (int i = 0; i < 2; i++)
    {
        setText(2, 10, 0, BLUE_L);
        drawButton(pre_next_Board[i], ID_DS_Ve_PRE_BUTTON_3 + i, mapID);//////////ID
        convertToShape(pre_next_Board[i], shape[i + ID_DS_Ve_PRE_BUTTON_3]);//////////ID
    }

	setcolor(0);
    rectangle(270, 45, 270+900, 45+40);
    setText(1,10,0,15);
	outtextxy(280, 55,"Ma CB:");
	setText(4,10,0,15);
	outtextxy(522, 47,"|");
	setText(1,10,0,15);
	outtextxy(538, 55,"Ngay Gio KH:");
	setText(4,10,0,15);
	outtextxy(857, 47,"|");
	setText(1,10,0,15);
	outtextxy(870, 55,"San Bay Den:");

	Board boardDsCB = {275,130,10,30,5,{60,110,330,100,300},{"STT","SO VE","HO VA TEN","PHAI","CMND"}};
	drawBoard(boardDsCB,ID_DS_VE_BOARD_3,mapID,shape);///////////////////ID

	setcolor(0);
    rectangle(275, 470, 1175, MAX_H);  

	Button Button_Order_Cancel[3] ={{0,0,0,0,0,0,"DAT VE"},{0,0,0,0,0,0,"HUY VE"},{0,0,0,0,0,0,"DS CHUYEN BAY"}} ;
	for(int i = 0;i <3;i++){
		setText(1,11,0,BLUE_L);
		Button_Order_Cancel[i].x1 = 475 + 180*i;
		Button_Order_Cancel[i].y1 = 480;
		Button_Order_Cancel[i].width = 160;
	    Button_Order_Cancel[i].height = 40;
	    Button_Order_Cancel[i].fillColor = BLUE_L;
	    Button_Order_Cancel[i].borderColor = BLUE_L;
        drawButton(Button_Order_Cancel[i], ID_ORDER_TICKET_BUTTON_3 + i, mapID);///////////////////ID
        convertToShape(Button_Order_Cancel[i], shape[ID_ORDER_TICKET_BUTTON_3+i]);///////////////////ID
	}
	Input input_page_ve[4] = {
	{475, 570, 25, 350, 0},  // ho ten
	{920,570,4,70,0},	//so cho
	{440,620,20,300,0},	//cmnd
	{920,620,4,70,0}	//phai
	};
	for(int i = 0; i< 4;i++){
	input_page_ve[i].s = new char[input_page_ve[i].max+2];	
    drawInput(input_page_ve[i], mapID, i + ID_NAME_INPUT_3);///////////////////ID
    convertToShape(input_page_ve[i], shape[i + ID_NAME_INPUT_3]);///////////////////ID
	}
	setText();
	outtextxy(388,575,"HO VA TEN:");
	outtextxy(858,575,"SO CHO:");
	outtextxy(388,625,"CMND:");
	outtextxy(875,625,"PHAI:");
	
	checkEventPageQLV_DSHK(shape,mapID);
	for(int i =0; i<4;i++)
		delete[] input_page_ve[i].s;
		

}

//===========================PageSeatMap===================

void drawPageQLV_DatVe(short **mapID,Shape *shape){
	setDefaultRightFrame(mapID);	

	setText(6,10);
	outtextxy(500,5,"SO DO CHO NGOI");
	setcolor(0);
    rectangle(270, 85, 270+900, 85+50);
    setText(1,10,0,15);
	outtextxy(280, 101,"Ma CB:");
	setText(4,10,0,15);
	outtextxy(522, 94,"|");
	setText(1,10,0,15);
	outtextxy(538, 101,"Ngay Gio KH:");
	setText(4,10,0,15);
	outtextxy(857, 94,"|");
	setText(1,10,0,15);
	outtextxy(870, 101,"San Bay Den:");
	setText(3,10,0,15);
	outtextxy(420, 179,"A");
    outtextxy(420, 179+45, "B");
    outtextxy(420, 177+46*2, "C");
    outtextxy(420, 177+46*3, "D");
    outtextxy(420, 177+46*4, "E");
    outtextxy(420, 177+46*5, "F");
  
    
    	Button pre_next_Board[2] = {{375,290,25,25,BLUE_L,15,"<"},{957,290,25,25,BLUE_L,15,">"}};
	for(int i = 0;i <2;i++){
		setText(2,10,0,BLUE_L);
		drawButton(pre_next_Board[i],ID_SEAT_MAP_PRE_BUTTON+i,mapID);///////////////////ID
		convertToShape(pre_next_Board[i],shape[i+ID_SEAT_MAP_PRE_BUTTON]);///////////////////ID
	}

	//================CHU THICH=====================

	setText(1,10,0,15);
	outtextxy(1040, 200, "Chu Thich");
    setfillstyle(1, BLUE_L);
    bar(1015, 250, 1015+30, 250+30);
    setText(1,11,0,15);
	outtextxy(1053, 252, ": Ghe da duoc dat");
	setfillstyle(1, GRAY);
    bar(1015, 285, 1015+30, 285+30);
	outtextxy(1053, 287, ": Ghe khong hoat dong");
	setfillstyle(1, WHITE);
    bar(1015, 320, 1015+30, 320+30);
    rectangle(1015, 320, 1015+30, 320+30);
	outtextxy(1053, 325, ": Ghe con trong");

	setText(6,10);
    rectangle(275, 470, 1175, MAX_H); 

 	Button Button_Order_Cancel[2] ={{0,0,0,0,0,0,"XAC NHAN"},{0,0,0,0,0,0,"HUY"}} ;
	for(int i = 0;i <2;i++){
	setText(1, 11, 0, BLUE_L);
        Button_Order_Cancel[i].x1 = 565 + 180 * i;
        Button_Order_Cancel[i].y1 = 480;
        Button_Order_Cancel[i].width = 160;
        Button_Order_Cancel[i].height = 40;
        Button_Order_Cancel[i].fillColor = BLUE_L;
        Button_Order_Cancel[i].borderColor = BLUE_L;
        drawButton(Button_Order_Cancel[i],i+ID_CONFIRM_TICKET_BUTTON, mapID);///////////////////ID
        convertToShape(Button_Order_Cancel[i],shape[i+ID_CONFIRM_TICKET_BUTTON]);
	}
	Input input_page_ve[4] = {
	{470, 570, 25, 350, 0},  // ho ten
	{917,570,4,70,0},	//so cho
	{440,620,20,300,0},	//cmnd
	{900,620,4,70,0}	//phai
	};

	for(int i = 0; i< 4;i++){
	input_page_ve[i].s = new char[input_page_ve[i].max+2];	
    drawInput(input_page_ve[i], mapID, i + ID_NAME_INPUT_3);///////////////////ID
    convertToShape(input_page_ve[i], shape[i + ID_NAME_INPUT_3]);///////////////////ID
	}
	setText();
	outtextxy(388,575,"HO VA TEN:");
	outtextxy(858,575,"SO CHO:");
	outtextxy(388,625,"CMND:");
	outtextxy(858,625,"PHAI:");
	
	checkEventPageQLV_DatVe(shape,mapID);
	for(int i =0; i<4;i++)
		delete[] input_page_ve[i].s	;
	
	
}
