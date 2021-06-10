#pragma once
#include "QLVreuse.h"
#include "QLCBDSCB.h"

//=====================PROTOTYPE=================
void drawPageQLV_DSCB(short **mapID,Shape *shape);

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




//==========================Page DS CB======================================



