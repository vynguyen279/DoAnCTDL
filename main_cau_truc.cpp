#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "xu_ly_may_bay.h"
#include "xu_ly_chuyen_bay.h"
#include "dat_ve.h"
#include "io.h"
#include "hash_table_may_bay.h"
#include "hash_table_hanh_khach.h"

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

int main() {
	DanhSachMayBay dsMB;
	DanhSachChuyenBay dsCB = NULL;
	DanhSachHanhKhach dsHK = NULL;
	
	DanhSachTam dsTmp;
	HashTableCustomer tableCustomer;
	HashTable table;
	
	initHashTableCustomer(tableCustomer);
	layDSMayBay(dsMB);
	layDSChuyenBay(dsCB);
	layDSHK(dsHK, tableCustomer);
	
	dsTmp = dsNode2DsTmp(dsCB);
	
	char strErr[255];
	
//	datVe("885110227780", hk, 3, dsTmp.cb[1], dsHK, dsCB, strErr);

//	hashDSHKToHashTable(dsHK, tableCustomer);
//	HanhKhach tmp = newHanhKhach("885110227780", "NGUYEN VAN", "A", 1);
//	capNhapHanhKhach(hk, tmp);
//	themHanhKhach(dsHK, newNodeHanhKhach(newHanhKhach("12345678912", "NGUYEN VAN", "XYZ", 1)), tableCustomer);
//	HanhKhach* hk = timKiemHanhKhach(dsHK, "12345678912");
//	datVe("12345678912", hk, 10, dsTmp.cb[1], dsHK, dsCB, strErr);
//	cout << strErr << endl;
	printHashTableCustomer(dsTmp.cb[1]->dsVe, tableCustomer);
//	xuatDSMB(dsMB);
//	xuatDSCB(dsCB, dsMB);
	xuatDSTmp(dsTmp);
	xuatDSHK(dsHK);
	
	
	luuDSMayBay(dsMB);
	luuDSChuyenBay(dsCB);
	luuDSHK(dsHK);
	
	clearDSMB(dsMB);
	clearDSCB(dsCB);
	clearDSHK(dsHK);



	return 0;
}
