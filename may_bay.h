#pragma once

#include "chuyen_bay.h"
#define MAXMAYBAY 300
/*
v	2 chuyen bay cua cung 1 may bay khong trung h nhau
		{
			Xu ly trong ham themChuyenBayHopLe
			duyet danh sach chuyen bay, so sanh so hieu may bay,
				neu co cung so hieu may bay thi kt den ngay gio khoi hanh, 
					ney ngay gio khoi hanh cua 1 chuyen bay trong danh sach chuyen
		}
	
v	neu may bay dang co chuyen bay thi khong cho xoa
	neu hanh khach dat 2 ve tren cung 1 chuyen bay (Nhap vao ma chuyen bay va CMND)
	{
	
		Luu lai gio khoi hanh cua chuyen bay mang ma chuyen bay da nhap vao (gia su la dt1)
		Neu hanh khach chua ton tai trong danh sach hanh khach -> nhap vao thong tin va them vao danh
		sach hanh khach, dong thoi them ve nay vao chuyen bay
		Neu hanh khach da ton tai trong danh sach hanh khach -> xet danh sach ve tren chuyen bay
		neu ton tai CMND thi khong cho them
			Neu chua ton tai CMND trong danh sach ve cua chuyen bay mang ma chuyen bay nhap vao
			Xet cac chuyen bay khac xem co CMND nay hay khong
				neu khong thi them vao ds ve
				neu co thi kt xem gio khoi hanh cua chuyen bay nay co trung voi dt1 hay khong
					neu co thi khong cho them
					neu khong thi them vao ds ve
	}
	neu hanh khach dat 2 ve tren 2 may bay khac nhau nhung cung gio bay
*/

struct MayBay{
	char soHieuMayBay[15];
	char loaiMayBay[40];
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

void xoaMayBay(DanhSachMayBay &dsMayBay, int viTriXoa) {
		delete dsMayBay.mayBay[viTriXoa];
		for(int i = viTriXoa + 1; i < dsMayBay.n; i++)
			dsMayBay.mayBay[i - 1] = dsMayBay.mayBay[i];
		dsMayBay.n--;
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

