#pragma once

#include "ngay_thang_nam.h"
#include "may_bay.h"
#include "hanh_khach.h"
#include <cstring>
#include <string>

struct DanhSachVe {
	int soLuongVe = 0;
	char **CMND = NULL;
};

struct ChuyenBay{
	char maChuyenBay[MAXMACB];
	NgayThangNam ngayKhoiHanh;
	char sanBayDen[MAXSANBAYDEN];
	// 0: huy chuyen, 1: con ve, 2: het ve, 3: hoan tat
	int trangThai = 1;
	char soHieuMayBay[MAXSOHIEU];
	DanhSachVe dsVe;
	// Ham test
	void toString() {
		std::cout << "Ma chuyen bay: " << maChuyenBay << 
		" - Ngay khoi hanh: "; 
		ngayKhoiHanh.toString();
		std::cout << "San bay den: " << sanBayDen << std::endl;
		std::cout << "Trang thai: " << trangThai << 
		" - So hieu may bay: " << soHieuMayBay << std::endl;
	}
};

struct NodeChuyenBay{
	ChuyenBay chuyenBay;
	NodeChuyenBay *next = NULL;	
};

typedef NodeChuyenBay* DanhSachChuyenBay;

/*************************************************************************************
 *									Xu ly Ve										 *
 *************************************************************************************/

void initDSVe(DanhSachVe &dsVe) {
	for(int i = 0; i < dsVe.soLuongVe; i++)
		dsVe.CMND[i] = NULL;
}

int soVeDaDat(DanhSachVe &dsVe) {
	int cnt = 0;
	for(int i = 0; i < dsVe.soLuongVe; i++)
		if(dsVe.CMND[i] != NULL) cnt++;
	return cnt;
}

void xuatDSVe(DanhSachVe &dsVe) {
	if(soVeDaDat(dsVe) == 0) {
		std::cout << "DANH SACH VE RONG!\n"; 
		return;
	}
	for(int i = 0; i < dsVe.soLuongVe; i++)
		if(dsVe.CMND[i] != NULL)
			std::cout << "SO VE: " << i + 1 << " - CMND: " << dsVe.CMND[i] << std::endl;
}

bool ktTonTaiCMNDTrongDSVe(DanhSachVe &dsVe, char* CMND) {
	for(int i = 0; i < dsVe.soLuongVe; i++) 
		if(dsVe.CMND[i] != NULL && strcmp(dsVe.CMND[i], CMND) == 0) return true;
	return false;
}

bool ktSoVeTrung(DanhSachVe &dsVe, int soVe) {
	return dsVe.CMND[soVe - 1] != NULL;
}

bool soVeHopLe(int soVe, DanhSachVe &dsVe) {
	if(!ktSoVeTrung(dsVe, soVe) && soVe <= dsVe.soLuongVe && soVe >= 1)
		return true;
	return false;
}

void themVe(int soVe, char *CMND, DanhSachVe &dsVe) {
		dsVe.CMND[soVe - 1] = new char[MAXCMND];
		strcpy(dsVe.CMND[soVe - 1], CMND);
}

int timKiemVe(char* CMND, DanhSachVe &dsVe) {
	for(int i = 0; i < dsVe.soLuongVe; i++)
		if(dsVe.CMND[i] != NULL && strcmp(dsVe.CMND[i], CMND) == 0) 
			return i;
	return -1;
}

/*
	Input:
		*cb: con tro tro den chuyen bay;
		*CMND: chuoi chung minh nhan dan;
		soVeMoi: so ve moi ma hanh khach muon cap nhat trong chuyen bay;
		*strErr: chuoi loi sau khi thuc hien xong ham;
	Output:
		false: Khong the cap nhat so ve moi, chuoi strErr tra ve loi;
		true: Cap nhat so ve moi thanh cong, chuoi strErr rong;
*/

bool capNhatDanhSachVe(ChuyenBay *cb, char* CMND, int soVeMoi, char* strErr) {
	strcpy(strErr, "");
	int viTri = timKiemVe(CMND, cb->dsVe);
	if(cb->trangThai == 2) {
		strcpy(strErr,"CHUYEN BAY HET VE, KHONG THE THAY DOI SO GHE!");
		return false;
	}
	if(viTri == -1) {
		strcpy(strErr,"SO CMND KHONG TON TAI TRONG DANH SACH VE!");
		return false;
	}
	if(!soVeHopLe(soVeMoi, cb->dsVe)) {
		strcpy(strErr,"SO VE KHONG HOP LE!");
		return false;
	}
	delete[] cb->dsVe.CMND[viTri];
	cb->dsVe.CMND[viTri] = NULL;
	themVe(soVeMoi, CMND, cb->dsVe);
	return true;
}

void clearDSVe(DanhSachVe &dsVe) {
	for(int i = 0; i < dsVe.soLuongVe; i++) {
		if(dsVe.CMND[i] != NULL)
			delete []dsVe.CMND[i];
	}
	delete []dsVe.CMND;
}

/*************************************************************************************
 *								Xu ly chuyen bay									 *
 *************************************************************************************/

ChuyenBay newChuyenBay(char* maCB, NgayThangNam ngayKH, char* sanBayDen, char* soHieuMB) {
	ChuyenBay cb;
	strcpy(cb.maChuyenBay, maCB);
	strcpy(cb.sanBayDen, sanBayDen);
	strcpy(cb.soHieuMayBay, soHieuMB);
	cb.ngayKhoiHanh = ngayKH;
	return cb;
}

NodeChuyenBay *newNodeChuyenBay(ChuyenBay cb) {
	NodeChuyenBay *nodeCB = new NodeChuyenBay;
	nodeCB->chuyenBay = cb;
	return nodeCB;
}

void themDauDanhSach(NodeChuyenBay* nodeCB, DanhSachChuyenBay &dsCB) {
	nodeCB->next = dsCB;
	dsCB = nodeCB;
}

void themChuyenBay(NodeChuyenBay* nodeCB, DanhSachChuyenBay &dsCB) {
	if(dsCB == NULL) {
		themDauDanhSach(nodeCB, dsCB);
		return;
	}
	NodeChuyenBay* nodeChay = dsCB;
	while(nodeChay->next != NULL) nodeChay = nodeChay->next;
	nodeChay->next = nodeCB;
}

void xoaDau(DanhSachChuyenBay &dsCB) {
	NodeChuyenBay* nodeXoa = dsCB;
	dsCB = dsCB->next;
	clearDSVe(nodeXoa->chuyenBay.dsVe);
	delete nodeXoa;
}

bool xoaChuyenBay(char* maChuyenBay, DanhSachChuyenBay &dsCB, char* strErr) {
	strcpy(strErr, "");
	if(dsCB == NULL) {
		strcpy(strErr, "DANH SACH CHUYEN BAY RONG!");
		return false;
	}
	if(strcmp(dsCB->chuyenBay.maChuyenBay, maChuyenBay) == 0) {
		xoaDau(dsCB);
		return true;
	}
	NodeChuyenBay *nodeChay = dsCB;
	while( nodeChay->next != NULL && strcmp(nodeChay->next->chuyenBay.maChuyenBay, maChuyenBay) != 0) 
		nodeChay = nodeChay->next;
	
	if(strcmp(nodeChay->next->chuyenBay.maChuyenBay, maChuyenBay) == 0) {
		NodeChuyenBay *nodeXoa = nodeChay->next;
		nodeChay->next = nodeXoa->next;
		clearDSVe(nodeXoa->chuyenBay.dsVe);
		delete [] nodeXoa->chuyenBay.dsVe.CMND;
		delete nodeXoa;
		return true;
	}
	strcpy(strErr, "KHONG TON TAI CHUYEN BAY CAN XOA!");
	return false;
}

/*
	Input:
		*maChuyenBay: chuoi ma chuyen bay can tim kiem;
		dsCB: danh sach chuyen bay;
	Output:
		NULL neu chuyen bay voi ma chuyen bay la maChuyenBay khong ton tai trong dsCB;
		con tro tro den chuyen bay voi ma chuyen bay la maChuyenBay trong dsCB;
*/

ChuyenBay* timKiemChuyenBay(char* maChuyenBay, DanhSachChuyenBay &dsCB) {
		for(NodeChuyenBay *nodeChay = dsCB; nodeChay != NULL ; nodeChay = nodeChay->next) 
			if(strcmp(nodeChay->chuyenBay.maChuyenBay, maChuyenBay) == 0)
				return &(nodeChay->chuyenBay);
	return NULL;
}

bool huyChuyenBay(ChuyenBay *cb, char* strErr) {
	strcpy(strErr, "HUY THANH CONG!");
	if(cb->trangThai == 3) {
		strcpy(strErr, "CHUYEN BAY DA HOAN TAT, KHONG THE HUY!");
		return false;
	}
	cb->trangThai = 0;
	return true;
}

void clearDSCB(DanhSachChuyenBay &dsCB) {
	NodeChuyenBay *nodeXoa;
	while(dsCB != NULL) {
		nodeXoa = dsCB;
		dsCB = nodeXoa->next;
		clearDSVe(nodeXoa->chuyenBay.dsVe);
		delete nodeXoa;
	}
}
