#include "MainPage.h"
void fillCBCV(Input *inputFill,bool &isInvalid,DanhSachChuyenBay &dsCB,DanhSachTam &dsFillTmp){
}
void lockPageQLV_QLCB(Button *pre_next, Button *fill,short **mapID){
	drawLockButton(pre_next[0],mapID);
	drawLockButton(pre_next[1],mapID);
	drawLockButton(fill[0],mapID);
	drawLockButton(fill[3],mapID);
	
}
void unlockPageQLV_QLCB(Button *pre_next, Button *fill,short **mapID){
	drawButton(pre_next[0],ID_BUTTON_PRE,mapID);
	drawButton(pre_next[1],ID_BUTTON_NEXT,mapID);
	drawButton(fill[0],ID_BUTTON_FILL_2,mapID);
	drawButton(fill[3],ID_BUTTON_UNFILL_2,mapID);
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
		//INHOVER
        if((ID_INPUT_FILLDAY_2 <= ID && ID <= ID_INPUT_FILLYEAR_2)){  //NGAY GIO CO KIEU HOVER KHAC
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
	        if((ID_INPUT_FILLDAY_2 <= lastID && lastID <= ID_INPUT_FILLYEAR_2)){ //NGAY GIO CO KIEU HOVER KHAC
	            setcolor(WHITE);
	            rectangle(shape[lastID].x1, shape[lastID].y1+shape[lastID].height, shape[lastID].x1 + shape[lastID].width, shape[lastID].y1+shape[lastID].height - 1);     	
			}
			else{
				
				if(lastID>=ID_INPUT_FILLDAY_2)
					setcolor(WHITE);      	
	            else
	                setcolor(BLUE_L);
	            rectangle(shape[lastID].x1, shape[lastID].y1, shape[lastID].x1 + shape[lastID].width, shape[lastID].y1 + shape[lastID].height);
			}

        }

    }
}
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
void checkEventPageQLV_DSCBCV(Shape *shape, short **mapID,Input *inputFill,Button *buttonFill, Button *pre_next, Board &boardCBCV){
	DanhSachMayBay dsMB;
	layDSMayBay(dsMB);
	DanhSachChuyenBay dsCB = NULL;
	layDSChuyenBay(dsCB);
	DanhSachTam dsCBTmp = dsCBConVe(dsCB);
	DanhSachTam dsTmp = dsCBTmp;
	DanhSachTam dsFillTmp;
	
    short ID = -1, lastID = -1, chooseID = -1;
    bool isInvalid = true;                                          //check xem du lieu can them,xoa,sua co hop le hay k
    bool unlockChoose = true;                                       //khi dang update hay del thi k cho chon may bay
    bool isEnter = false;                                           //check enter khi dang input
    bool isFill = false;                                            //quan ly fill
    int numOfPage = (dsTmp.n - 1) / 10 + 1, presentPage = 1; 		//quan ly so trang
    short maxChoose = 0;                                            //khong cho chon vao o khong co may bay
    
    updateNumOfBoardDSCB(numOfPage,presentPage,dsTmp);
	outDSCBCV(boardCBCV, 1, 10,dsTmp);
	
    clearmouseclick(WM_LBUTTONDOWN);	
	while(true){
		delay(DELAY_TO_CHECK_EVENT);
        checkHoverPageQLV_DSCB(ID, lastID, shape, mapID);
        lastID = ID;
	     if(ismouseclick(WM_LBUTTONDBLCLK) && chooseID != -1 && ID == chooseID){
			return;
        }   
		if(ismouseclick(WM_LBUTTONDOWN))
			{
				
				if(getpixel(725,540) == BLACK) //xoa thong bao
					outAlert(WHITE,"");
				
				
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
			                lockPageQLV_QLCB(pre_next,buttonFill,mapID);  
			            }
			            else if (chooseID != -1 && ID == chooseID && unlockChoose) //HUY CHON NEU CLICK VAO CB DANG CHON
			            { 
							setcolor(15);
							setfillstyle(1, 15);
							fillellipse(shape[chooseID%10 + 50].x1 - 13, shape[chooseID%10 + 50].y1 + 10, 5, 5);
							unlockChoose = true;
							chooseID = -1;
							unlockPageQLV_QLCB(pre_next,buttonFill,mapID);
			            }
	            	}
	            }				
				
				if(ID>=ID_BUTTON_PAGE_MAIN && ID<=ID_BUTTON_PAGE4 && ID != ID_BUTTON_PAGE_QLV ){            
            		return;
            	}
				switch(ID){
					case ID_BUTTON_STARTDATVE_3:
					case ID_BUTTON_DSHK_3:{
						if(chooseID ==-1){
							outAlert(RED,"VUI LONG CHON MAY BAY!");	
						}
						else
							return;
					}
					case ID_BUTTON_FILL_2:{  //FILL
						fillCBCV(inputFill,isInvalid,dsCB,dsFillTmp);
						if(isInvalid){
						presentPage = 1;
						isFill = true;
						dsTmp = dsFillTmp;
		                updateNumOfBoardDSCB(numOfPage, presentPage,dsTmp);                   
		                drawBoard(boardCBCV, (presentPage - 1) * 10 + ID_BOARD, mapID, shape);
		                outDSCBCV(boardCBCV, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsTmp);	
													
						}
						break;
					}
					case ID_BUTTON_UNFILL_2:{  //UNFILL
						if(isFill){
						presentPage = 1;
						isFill = false;
						dsTmp = dsCBTmp;	
		                updateNumOfBoardDSCB(numOfPage, presentPage,dsTmp);                   
		                drawBoard(boardCBCV, (presentPage - 1) * 10 + ID_BOARD, mapID, shape);
		                outDSCBCV(boardCBCV, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsTmp);
						for(int i = 0; i <4; i++){
							inputFill[i].lastL = 0;
							drawInput(inputFill[i],mapID,ID_INPUT_FILLDAY_2 + i);
						}
						makeBeautiFillInput(inputFill);								
						}
		
						break;
					}
					case ID_BUTTON_UNFILLTIME_2:{  // UNFILLTIME
						for(int i = 0; i < 3; i++){					
							inputFill[i].lastL = 0;
						}
						makeBeautiFillInput(inputFill);	
						break;
					}
					case ID_BUTTON_UNFILLPLACE_2:{  //UNFILLDES
						if(inputFill[3].lastL != 0)
						{
							inputFill[3].lastL = 0;
							drawInput(inputFill[3],mapID,ID_INPUT_FILLPLACE_2);
						}
						break;
					}																				
					case ID_BUTTON_PRE:{
						if (presentPage > 1)
                        {
                           presentPage--;         			               
   						   updateNumOfBoardDSCB(numOfPage,presentPage,dsTmp);
                           drawBoard(boardCBCV, (presentPage - 1) * 10 + ID_BOARD, mapID, shape);
                           outDSCBCV(boardCBCV, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsTmp);
            	        }
						break;
					}
					case ID_BUTTON_NEXT:{
                        if (presentPage < numOfPage)
                        {
                           presentPage++;  	                			               
                   	       updateNumOfBoardDSCB(numOfPage,presentPage,dsTmp);					         					                                       
                           drawBoard(boardCBCV, (presentPage - 1) * 10 + ID_BOARD, mapID, shape);
                           outDSCBCV(boardCBCV, 10 * (presentPage - 1) + 1, 10 * (presentPage),dsTmp);
				        }
                        break;
                    }
					case ID_INPUT_FILLDAY_2:{  //FILL DAY
						getInputPageQLCB(inputFill[0],ID,isEnter);
						if(inputFill[0].lastL * inputFill[1].lastL * inputFill[2].lastL !=0)   //fix lai ngay trong fill neu la nam nhuan
							fixNgayFill(inputFill);
						if (!isEnter)
		                    break;				
					
					}
					case ID_INPUT_FILLMONTH_2:{  //FILL MONTH
						getInputPageQLCB(inputFill[1],ID,isEnter);
						if(inputFill[0].lastL * inputFill[1].lastL * inputFill[2].lastL !=0)   
							fixNgayFill(inputFill);				
						if (!isEnter)
		                    break;
					}
					case ID_INPUT_FILLYEAR_2:{  //FILL YEAR
						getInputPageQLCB(inputFill[2],ID,isEnter);
						if(inputFill[0].lastL * inputFill[1].lastL * inputFill[2].lastL !=0)   
							fixNgayFill(inputFill);					
						if (!isEnter)
		                    break;
					}
					case ID_INPUT_FILLPLACE_2:{  //FILL DESTINATION
						getInputPageQLCB(inputFill[3],ID,isEnter);
						break;
					}                    
                    
					default:
						break;
				}
				clearmouseclick(WM_LBUTTONDOWN); 				 
			}
		clearmouseclick(WM_LBUTTONDBLCLK);	 	
	
	}	
}

void drawPageQLV_DSCB(short **mapID,Shape *shape){
	setDefaultRightFrame(mapID);	

	setText(6,10);
	outtextxy(310,-10,"DANH SACH CHUYEN BAY CON VE");
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
	drawInput(inputFill[i],mapID,i+ID_INPUT_FILLDAY_2);
	convertToShape(inputFill[i],shape[i+ID_INPUT_FILLDAY_2]);	
	drawButton(buttonFill[i],ID_BUTTON_FILL_2 + i,mapID);
	convertToShape(buttonFill[i],shape[i+ID_BUTTON_FILL_2]);	
	}
	makeBeautiFillInput(inputFill);
	setText();
	outtextxy(275,80,"NGAY GIO K.H:");	
	outtextxy(506,101,"SAN BAY DEN:");
	
	Board boardCBCV = {275,130,10,30,5,{125,125,180,350,120},{"MA CB","SO HIEU MB","NGAY GIO KHOI HANH","SAN BAY DEN","SO VE TRONG"}};
	drawBoard(boardCBCV,ID_BOARD,mapID,shape);
	setcolor(0);
    rectangle(275, 470, 1175, MAX_H);     

    Button mainButton[2] = {
    	{0,0,160,40,BLUE_L,BLUE_L,"TIEN HANH DAT VE"},
		{0,0,160,40,BLUE_L,BLUE_L,"DS HANH KHACH"}
	};
    for(int i = 0;i < 2; i++){
        mainButton[i].x1 = 520 + 200 * i;
        mainButton[i].y1 = 480;
        drawButton(mainButton[i], i + ID_BUTTON_STARTDATVE_3, mapID);
        convertToShape(mainButton[i], shape[i + ID_BUTTON_STARTDATVE_3]);    	
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


