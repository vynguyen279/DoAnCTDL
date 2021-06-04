#pragma once

#include "chuyen_bay.h"
#include "configure.h"

struct MayBay{
	char soHieuMayBay[MAXSOHIEU];
	char loaiMayBay[MAXLOAIMB];
	int soCho;
	
	// Ham test
	void toString() {
		std::cout << "So hieu may bay: " << soHieuMayBay << " - Loai may bay: " << loaiMayBay
			<< " - So cho: " << soCho << std::endl;
	}
};

struct DanhSachMayBay{
	int n = 0;
	MayBay *mayBay[MAXMAYBAY];
};

MayBay newMayBay(char* soHieuMayBay, char* loaiMayBay, int soCho) {
	MayBay mayBay;
	strcpy(mayBay.soHieuMayBay, soHieuMayBay);
	strcpy(mayBay.loaiMayBay, loaiMayBay);
	mayBay.soCho = soCho;
	return mayBay;
}

int timKiemMayBay(char* soHieuMayBay, DanhSachMayBay &dsMayBay) {
	for(int i = 0; i  < dsMayBay.n; i++)
		if(strcmp(soHieuMayBay, dsMayBay.mayBay[i]->soHieuMayBay) == 0) return i;
	return -1;
}

void xuatDSMB(DanhSachMayBay &dsMayBay) {
	if(dsMayBay.n == 0) {
		std::cout << "DANH SACH MAY BAY RONG!\n";
		return;
	}
	for(int i = 0; i < dsMayBay.n; i++) 
		dsMayBay.mayBay[i]->toString();
	std::cout << std::endl;
}

void themMayBay(MayBay mb, DanhSachMayBay &dsMayBay) {
	dsMayBay.mayBay[dsMayBay.n] = new MayBay;
	*dsMayBay.mayBay[dsMayBay.n] = mb;
	dsMayBay.n++;
}

void xoaMayBay(DanhSachMayBay &dsMB, int viTriXoa) {
	delete dsMB.mayBay[viTriXoa];
	for(int i = viTriXoa + 1; i < dsMB.n; i++)
		dsMB.mayBay[i - 1] = dsMB.mayBay[i];
	dsMB.n--;
}

void capNhatLoaiMB(char *loaiMB, int viTri, DanhSachMayBay &dsMB) {
	strcpy(dsMB.mayBay[viTri]->loaiMayBay, loaiMB);
}

void capNhatSoCho(int soCho, int viTri, DanhSachMayBay &dsMB) {
	dsMB.mayBay[viTri]->soCho = soCho;
}

void clearDSMB(DanhSachMayBay &dsMB) {
	while(dsMB.n != 0) 
		xoaMayBay(dsMB, dsMB.n - 1);
} 
