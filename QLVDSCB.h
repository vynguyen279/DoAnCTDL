#pragma once
#include "QLVreuse.h"


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


