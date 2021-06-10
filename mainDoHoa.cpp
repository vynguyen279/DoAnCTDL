#include "MainPage.h"
void outCBCV(Board &board,DanhSachTam &dsTmp, short ID){
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
        else if (col == 5) //SO VE TRONG
        { 	
    		char soVeTrong[5];
			itoa(soVeConTrong(dsTmp.cb[ID] ->dsVe),soVeTrong,10);
            outtextxy(x1 + board.widthOfCol[col - 1] / 2 - 4 * strlen(soVeTrong),
                      y1 + (board.heightOfLine) / 2 - 10, soVeTrong);						
        }        	
    	
    }	
}
void outDSCBCV(Board &board, int startCB, int endCB,DanhSachTam &dsTmp){

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
               outCBCV(board,dsTmp,startCB -1);
			
        }
        if (line >= 1)
            startCB++;
    }
}
void checkEventPageQLV_DSCBCV(Shape *shape, short **mapID,Input *inputFill,Button *buttonFill, Button *pre_next, Board &boarCBCV){
	DanhSachMayBay dsMB;
	layDSMayBay(dsMB);
	DanhSachChuyenBay dsCB = NULL;
	layDSChuyenBay(dsCB);
	DanhSachTam dsCBCV = dsCBConVe(dsCB);
	DanhSachTam dsTmp = dsCBCV;
	DanhSachTam dsFill;
	
    short ID = -1, lastID = -1, presentPage=1,chooseID = -1;
    int numOfPage = (dsTmp.n - 1) / 10 + 1;
    
    updateNumOfBoardDSCB(numOfPage,presentPage,dsTmp);
    drawBoard(boarCBCV,ID_BOARD,mapID,shape);
	outDSCBCV(boarCBCV, 1, 10,dsTmp);
	
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
					case ID_BUTTON_DATVE_3:
					case ID_BUTTON_DSHK_3:{
						
						return;
					}
					
					case ID_BUTTON_PRE:{
						if (presentPage > 1)
                        {
                           presentPage--;         			               
   						   updateNumOfBoardDSCB(numOfPage,presentPage,dsTmp);
                           drawBoard(boarCBCV, (presentPage - 1) * 10 + ID_BOARD, mapID, shape);
                           outDSCBCV(boarCBCV, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsTmp);
            	        }
						break;
					}
					case ID_BUTTON_NEXT:{
                        if (presentPage < numOfPage)
                        {
                           presentPage++;  	                			               
                   	       updateNumOfBoardDSCB(numOfPage,presentPage,dsTmp);					         					                                       
                           drawBoard(boarCBCV, (presentPage - 1) * 10 + ID_BOARD, mapID, shape);
                           outDSCBCV(boarCBCV, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsTmp);
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

void drawPageQLV_DSCB(short **mapID,Shape *shape){
	setDefaultRightFrame(mapID);	

	setText(6,10);
	outtextxy(410,-10,"DANH SACH CB CON VE");
	Button pre_next[2] = {{640,50,25,25,BLUE_L,BLUE_L,"<"},{720,50,25,25,BLUE_L,BLUE_L,">"}};
	for(int i = 0;i <2;i++){
		drawButton(pre_next[i],ID_BUTTON_PRE+i,mapID);
		convertToShape(pre_next[i],shape[i+ID_BUTTON_PRE]);
	}

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
	drawInput(inputFill[i],mapID,i+ID_INPUT_FILLTIMED_3);
	convertToShape(inputFill[i],shape[i+ID_INPUT_FILLTIMED_3]);	
	drawButton(buttonFill[i],ID_BUTTON_FILL_3 + i,mapID);
	convertToShape(buttonFill[i],shape[i+ID_BUTTON_FILL_3]);	
	}
	makeBeautiFillInput(inputFill);
	setText();
	outtextxy(275,80,"NGAY GIO K.H:");	
	outtextxy(506,101,"SAN BAY DEN:");
	
	Board boardCBCV = {275,130,10,30,5,{125,125,180,350,120},{"MA CB","SO HIEU MB","NGAY GIO KHOI HANH","SAN BAY DEN","SO VE TRONG"}};

	setcolor(0);
    rectangle(275, 470, 1175, MAX_H);     

    Button mainButton[2] = {
    	{0,0,160,40,BLUE_L,BLUE_L,"DAT VE"},
		{0,0,160,40,BLUE_L,BLUE_L,"DS HANH KHACH"}
	};
    for(int i = 0;i < 2; i++){
        mainButton[i].x1 = 520 + 200 * i;
        mainButton[i].y1 = 480;
        drawButton(mainButton[i], i + ID_BUTTON_DATVE_3, mapID);
        convertToShape(mainButton[i], shape[i + ID_BUTTON_DATVE_3]);    	
    }
    checkEventPageQLV_DSCBCV(shape,mapID,inputFill,buttonFill, pre_next,boardCBCV);
 	for (int i = 0; i < 4; i++)
	    delete[] inputFill[i].s;
}




int main(){	
	drawMainPage();
	getch();
	return 0;
}


