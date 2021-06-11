#pragma once

#include "QLVreuse.h"

//===========================XU LY=============================================

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
void drawSeatMap(short **mapID, Shape *shape, short presentPage,Button *button_seat,short totalPage){
    int  inputSeat = 150; //dung ham get input
	int So_ghe_khong_hd = totalPage*72-inputSeat; 
    short lastID = 50+totalPage*72-1;
	short x,y,ID,temp,vtr, tempVtr, countID=16;
	for(int i = 0;i <12;i++){
		 x=450+40*i;
		 temp = 50+6*i+72*(presentPage-1);
		 tempVtr = 0+6*i+72*(presentPage-1);
		for(int j=0;j<6;j++){
			 y=175+45*j;
			 ID=temp+j;
			 vtr = tempVtr+j;
			 if(ID>=(lastID-So_ghe_khong_hd+1)&&ID<=lastID){
			     button_seat[vtr].x1= x;
			     button_seat[vtr].y1 = y;
		         button_seat[vtr].width = 35;
		         button_seat[vtr].height = 36;
			     button_seat[vtr].fillColor = GRAY;
			     button_seat[vtr].borderColor = GRAY; 
			     drawButton(button_seat[vtr],-2,mapID);
			     convertToShape(button_seat[vtr], shape[-2]);
			 } 
			  else{
			    button_seat[vtr].x1= x;
			    button_seat[vtr].y1 = y;
		        button_seat[vtr].width = 35;
			    button_seat[vtr].height = 35;
			    button_seat[vtr].fillColor = 15;
		 	    button_seat[vtr].borderColor = 0; 
			    drawButton(button_seat[vtr],ID,mapID);
			    convertToShape(button_seat[vtr], shape[countID]);
				countID++;
                 }
                 if(countID==31) countID=35;
       }   
   }
}
short convertIDToShapeID(short ID){
	  int newID;	  
      if(ID>=50&&ID<=64)
      newID= ID-34;
      else if(ID>=65&&ID<=121)
      newID = ID-30;   
      else if(ID>121){
      	do{
      		ID=ID-72;
      	 }
			  while(ID>121) ;
      if(ID>=50&&ID<=64) 
      newID= ID-34;
      else if(ID>=65&&ID<=121)
      newID = ID-30;
  }
        return  newID;
}
void getInputPageQLV_DatVe(Input &input, short &inputID, bool &isEnter){
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
                if (inputID == ID_NAME_INPUT_3 && input.lastL < input.max - 1  && c != ' ')
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
                else if(inputID == ID_GENDER_INPUT_3 && input.lastL < input.max - 1 && c != ' '){
                	if ('a' <= c && c <= 'z')
                    {
                        input.s[input.lastL] = c - ('a' - 'A');
                        input.lastL++;
                        input.s[input.lastL + 1] = '\0';
                    }
				}
                else if (inputID == ID_CMND_INPUT_3 && '0' <= c && c <= '9')
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




//============================HOVER-Event====================================
void checkHoverPageQLV_DatVe(short &newID, short lastID, Shape *shape, short **mapID, short totalPage){
       if (ismouseclick(WM_MOUSEMOVE))
    {	
 			
		int x, y;
        getmouseclick(WM_MOUSEMOVE, x, y);
        newID = mapID[x][y];
        short ID = newID;
		int  inputSeat = 300; //dung ham get input
     	int So_ghe_khong_hd = totalPage*72-inputSeat; 
        int endID = 50+totalPage*72-1;   
        //IN HOVER: MOI HOVER DEU MAU DEN
        if (ID > 0 && ID != lastID)
        {    
           if(ID>=ID_FIRST_SEAT&&ID<=endID-So_ghe_khong_hd)
             {
             	setfillstyle(1,BLUE_L);
             	bar(shape[convertIDToShapeID(ID)].x1, shape[convertIDToShapeID(ID)].y1, shape[convertIDToShapeID(ID)].x1 + shape[convertIDToShapeID(ID)].width+2, shape[convertIDToShapeID(ID)].y1 + shape[convertIDToShapeID(ID)].height+2);
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
             else if (lastID>=ID_BUTTON_PAGE_QLMB&&lastID<=ID_VIEW_DSHK_SEATMAP_BUTTON){
                setcolor(BLUE_L);
                rectangle(shape[lastID].x1, shape[lastID].y1, shape[lastID].x1 + shape[lastID].width, shape[lastID].y1 + shape[lastID].height);
               } 
            else if(lastID>=ID_FIRST_SEAT&&lastID<=endID-So_ghe_khong_hd){
                setfillstyle(1,WHITE);
             	bar(shape[convertIDToShapeID(lastID)].x1, shape[convertIDToShapeID(lastID)].y1, shape[convertIDToShapeID(lastID)].x1 + shape[convertIDToShapeID(lastID)].width+1, shape[convertIDToShapeID(lastID)].y1 + shape[convertIDToShapeID(lastID)].height+1);
             	setcolor(BLACK);
             	rectangle(shape[convertIDToShapeID(lastID)].x1, shape[convertIDToShapeID(lastID)].y1, shape[convertIDToShapeID(lastID)].x1 + shape[convertIDToShapeID(lastID)].width+1, shape[convertIDToShapeID(lastID)].y1 + shape[convertIDToShapeID(lastID)].height+1);
                }
		 }

    }
}

void checkEventPageQLV_DatVe(Shape *shape, short **mapID,Button *button_seat, Input* input_page_ve){
    int x, y;
    short ID = -1, lastID = -1, presentPage = 1;
    bool unlockChoose = true;
    bool isEnter = false;   
    short totalPage= floor(150/72)+1;// dung ham lay so cho
	PrintPresentPage(presentPage);
	drawSeatMap(mapID,shape,presentPage,button_seat,totalPage);
	clearmouseclick(WM_LBUTTONDOWN);
	while(true){
		delay(DELAY_TO_CHECK_EVENT);
		checkHoverPageQLV_DatVe(ID, lastID, shape, mapID,totalPage);
        lastID = ID;
		if(ismouseclick(WM_LBUTTONDOWN))
			{
				cout<<ID;
				if(ID>=ID_BUTTON_PAGE_MAIN && ID<=ID_BUTTON_PAGE4 && ID != ID_BUTTON_PAGE_QLV){            
            		return;
            	}
            	if(ismouseclick(WM_LBUTTONDOWN)){
			if(getpixel(725,540) == BLACK){ //xoa thong bao
				outAlert(WHITE,"");
			}
				switch(ID){
					case ID_VIEW_DSCB_SEATMAP_BUTTON:
					case ID_VIEW_DSHK_SEATMAP_BUTTON :{

						return;
					}
					case ID_SEAT_MAP_PRE_BUTTON:{
						if(presentPage > 1){
							presentPage--;
							resetNumber();
							PrintPresentPage(presentPage);
                           resetSeatMap(mapID);
                            drawSeatMap(mapID,shape,presentPage,button_seat,totalPage);
						}
						break;
					}
					case ID_SEAT_MAP_NEXT_BUTTON:{
						if(presentPage < totalPage){
							presentPage++;
							resetNumber();
							PrintPresentPage(presentPage);
							resetSeatMap(mapID);
                           drawSeatMap(mapID,shape,presentPage,button_seat,totalPage);
						}
						break;
					}
					case ID_DATVE_SEATMAP_BUTTON:{
                         return;
					}
					case ID_CONFIRM_TICKET_BUTTON:
					case ID_CANCEL_BUTTON:{		
						  	return;
						break;
					}
					case ID_NAME_INPUT_3:{
						getInputPageQLV_DatVe(input_page_ve[0], ID, isEnter);
                        if (!isEnter)
						break;
					}
					case ID_CMND_INPUT_3:{
						getInputPageQLV_DatVe(input_page_ve[2], ID, isEnter);
                        if (!isEnter)
						break;
					}
					case ID_GENDER_INPUT_3:{
						getInputPageQLV_DatVe(input_page_ve[3], ID, isEnter);
                        if (!isEnter)
						break;
					}
					default:
						break;
				} 
					clearmouseclick(WM_LBUTTONDOWN); 
	}
}
}
}


//===========================PageSeatMap===================
void drawConfirmSeatMap(short **mapID, Shape *shape){
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
	
	Button button_seat[360];
    for(int i = 0;i<360;i++)
      	button_seat[i]={0,0,0,0,0,0};

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
    
    Button del[2] = {{520, 480, 160, 40, BLUE_L, 15, "XAC NHAN"}, {740, 480, 160, 40, BLUE_L, 15, "HUY"}};
    for (int i = 0; i < 2; i++)
    {
        drawButton(del[i], ID_CONFIRM_TICKET_BUTTON + i, mapID);
        convertToShape(del[i], shape[ID_CONFIRM_TICKET_BUTTON + i]);
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
	
	checkEventPageQLV_DatVe(shape,mapID,button_seat,input_page_ve);
	for(int i =0; i<4;i++)
		delete[] input_page_ve[i].s	;
	
	
}

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
	
	Button button_seat[360];
    for(int i = 0;i<360;i++)
      	button_seat[i]={0,0,0,0,0,0};

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
    
    Button Main_Button_SeatMap[3] = {{0, 0, 0, 0, 0, 0, "DAT VE"}, {0, 0, 0, 0, 0, 0, "XEM DSCB"}, {0, 0, 0, 0, 0, 0, "XEM DSHK"}};
    for (int i = 0; i < 3; i++)
    {
        Main_Button_SeatMap[i].x1 = 455 + 180 * i;
        Main_Button_SeatMap[i].y1 = 480;
        Main_Button_SeatMap[i].width = 160;
        Main_Button_SeatMap[i].height = 40;
        Main_Button_SeatMap[i].fillColor = BLUE_L;
        Main_Button_SeatMap[i].borderColor = 15;
        drawButton(Main_Button_SeatMap[i], i + ID_DATVE_SEATMAP_BUTTON, mapID);
        convertToShape(Main_Button_SeatMap[i], shape[i + ID_DATVE_SEATMAP_BUTTON]);
    }
	Input input_page_ve[4] = {
	{470, 570, 45, 350, 0},  // ho ten
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
	
	checkEventPageQLV_DatVe(shape,mapID,button_seat,input_page_ve);
	for(int i =0; i<4;i++)
		delete[] input_page_ve[i].s	;
	
	
}
