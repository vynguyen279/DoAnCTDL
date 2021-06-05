#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include "xu_ly_may_bay.h"
#include "xu_ly_chuyen_bay.h"
#include "dat_ve.h"
#include "io.h"
#include "hash_table.h"

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
	int soCho = 20;
	char strErr[255];
	for(int i = 1; i <= 10; i++) {
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
	for(int i = 1; i <= 20; i++) { 
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
		
		ranSoHieu = rand() % (10 - 1 + 1) + 1;
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
	ListHanhKhachThongKe list;

	layDSMayBay(dsMB);
	layDSChuyenBay(dsCB);
	layDSHK(dsHK);
	
	dsTmp = dsNode2DsTmp(dsCB);
	
	NgayThangNam dt = newNgayThangNam(20,6,2021,15,00);
	
	//24 - 23  + 1 = 2
	char strErr[255];
	
	
//	datVe("036263053514", 5, dsTmp.cb[1], dsHK, dsCB, strErr);
//	capNhatNgayThangNam(dsCB, dsTmp.cb[0], dt, strErr);
//	dsHanhKhachThuoc1CB(dsCB, dsHK, "CB900", list, strErr);
//	cout << strErr << endl;
//	xuatListHKTK(lisdt);
//	cout << dsTmp.n << endl;	
	giaLapMayBay(dsMB);
	giaLapChuyenBay(dsCB, dsMB, dsTmp);
//	giaLapDSHK(dsHK);

//	initHashTable(table);
//	dsMBToHashTable(dsMB, table);
//	thongKeMBThucHienCB(table, dsCB);
//	quick_sort_so_hieu(table,0,MAXHASH - 1);
//	printHashTable(table);

//	NgayThangNam dt = newNgayThangNam(5,6,2021,19,00);
//	cout << ktTuongLai(dt) << endl;
//	datVe("011153052884", 1, dsTmp.cb[2], dsHK, dsCB, strErr);
//	huyChuyenBay(dsTmp.cb[29], strErr);
//	capNhatNgayThangNam(dsCB, dsTmp.cb[2],dt,strErr);
//	datVe("011153052884", 1, dsTmp.cb[0], dsHK, dsCB, strErr);
//	huyVe(dsTmp.cb[0], "12345678", dsHK, strErr);
//	themChuyenBayHopLe(
//			newNodeChuyenBay(
//				newChuyenBay("CB2222",dt,"TAN SON NHAT","MB009")
//			), dsCB, dsMB, dsTmp, strErr);
//	xuatDSMB(dsMB);
//	huyChuyenBay(dsTmp.cb[27], strErr);
	cout << strErr << endl;
	xuatDSCB(dsCB, dsMB);
//	xuatDSHK(dsHK);
//	xuatDSTmp(dsTmp);

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
	clearListHKTK(list);

	return 0;
}
