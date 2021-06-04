#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include "xu_ly_may_bay.h"
#include "xu_ly_chuyen_bay.h"
#include "dat_ve.h"
#include "io.h"
#include "hash_table.h"


#define MAX_RANMB 5
#define MAX_RANCB 5
using namespace std;



void int2str(int s, char* res) {
  itoa(s,res,10);
  res = strrev(res);	
  while(strlen(res) < 3)
    strcat(res, "0");
  res = strrev(res);
}

void giaLapMayBay(DanhSachMayBay &dsMB) {
	char str[255];
	char tmp[255];
	int soCho = 0;
	char strErr[255];
	srand(time(NULL));
	for(int i = 1; i <= MAX_RANMB;i++) {
		
		soCho = rand() % (280)+ 20;
	    strcpy(str, "MB");
	    int2str(i, tmp);
	    strcat(str, tmp);
	    themMayBayHopLe(newMayBay(str, "MAY BAY DAN DUNG", soCho), dsMB, strErr);
	    cout << str << " " << strErr << endl;
	}
}

void giaLapChuyenBay(DanhSachChuyenBay &dsCB, DanhSachMayBay &dsMB, DanhSachTam &dsTmp) {
	char str[255];
	char str2[255];
	char tmp[255];
	char strErr[255];
	srand(time(NULL));
	int ngaytmp[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
	char *sanBayDen[] = {
		"DA NANG",
		"TAN SON NHAT",
		"NOI BAI",
		"CAM RANH",
		"PHU QUOC"
	};
	int ranSanBay;
	int ranSoHieu;
	int ngay, thang, nam, gio, phut;
	NgayThangNam dt;
	for(int i = 1; i <= MAX_RANCB; i++) { 
		// random thoi gian khoi hanh
		nam = 2021;
		thang = rand() % (12 - 6 + 1) + 6;
		ngay = rand() % (ngaytmp[thang] - 4 + 1) + 4;
		gio = rand() % (24 - 1 + 1) + 1;
		phut = rand() & 59;
		// random san bay den
		ranSanBay = rand() % 5;
		// random soHieu
		
		strcpy(str, "MB");
		strcpy(str2, "CB");
		
		ranSoHieu = rand() % (MAX_RANMB - 1 + 1) + 1;
	    int2str(ranSoHieu, tmp);
	    strcat(str, tmp);
	    
	    int2str(i, tmp);
	    strcat(str2, tmp);
	    
	    dt = newNgayThangNam(ngay, thang, nam, gio, phut);
	    
	    themChuyenBayHopLe(
			newNodeChuyenBay(
				newChuyenBay(str2,dt,sanBayDen[ranSanBay],str)
			), dsCB, dsMB, dsTmp, strErr);
			
		cout << str2 << " " << strErr << endl;
		dt.toString();
		cout << endl;
	}
}
void randomCMND(char *CMND) {
	char buff[2];
	int randNum;
	strcpy(CMND, "");
	srand(time(NULL));
	for(int i = 1; i <= 12; i++) {
		randNum = rand() % 9;
		itoa(randNum,buff,10);
		strcat(CMND, buff);
	}
	cout << CMND << endl;
}

void giaLapDSHK(DanhSachHanhKhach &dsHK) {
	char CMND[MAXCMND];
	int phai;
	char *ho[] = {
		"NGUYEN VAN",
		"PHAM VAN",
		"LE THI",
		"NGUYEN THI",
		"HUYNH VAN",
		"CAO THI",
	};
	char *ten[] = {
		"A",
		"B",
		"C",
		"D",
		"E",
		"F"
	};
	
	int iTen, iHo;
	srand(time(NULL));
	for(int i = 1; i <= 20; i++) {
		randomCMND(CMND);
		phai = rand() % 2;
		iHo = rand() % 6;
		iTen = rand() % 6;
		themHanhKhach(dsHK, newHanhKhach(CMND, ho[iHo], ten[iTen], phai));
		system("pause");
	}
}

int main() {
	
	DanhSachMayBay dsMB;
	DanhSachChuyenBay dsCB = NULL;
	DanhSachHanhKhach dsHK = NULL;
	DanhSachTam dsTmp;
	HashTable table;

	layDSMayBay(dsMB);
	layDSChuyenBay(dsCB);
	layDSHK(dsHK);
	
	dsTmp = dsNode2DsTmp(dsCB);
//	cout << dsTmp.n << endl;
	
	giaLapMayBay(dsMB);
	giaLapChuyenBay(dsCB, dsMB, dsTmp);
//	giaLapDSHK(dsHK);

//	xuatDSMB(dsMB);
//	xuatDSCB(dsCB, dsMB);
//	xuatDSHK(dsHK);
	xuatDSTmp(dsTmp);

//	initHashTable(table);
//	dsMBToHashTable(dsMB, table);
//	printHashTable(table);
//	thongKeMBThucHienCB(table, dsCB);
	
	luuDSMayBay(dsMB);
	luuDSChuyenBay(dsCB);
	luuDSHK(dsHK);

	
	clearDSHK(dsHK);
	clearDSCB(dsCB);
	clearDSMB(dsMB);
	clearDSTmp(dsTmp);

	
	return 0;
}
