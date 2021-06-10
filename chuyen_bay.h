#pragma once

#include "ngay_thang_nam.h"
#include "may_bay.h"
#include "hanh_khach.h"
#include <cstring>
#include <string>

struct Ve {
	char CMND[MAXCMND];
	int soVe;
};

struct DanhSachVe {
	int soLuongVe = 0;
	int n = 0;
	Ve *ve;
};

struct ChuyenBay{
	char maChuyenBay[MAXMACB];
	NgayThangNam ngayKhoiHanh;
	char sanBayDen[MAXSANBAYDEN];
	int trangThai = CONVE;
	char soHieuMayBay[MAXSOHIEU];
	DanhSachVe dsVe;
	// Ham test
	void toString() {
		std::cout << "Ma chuyen bay: " << maChuyenBay << 
		" - Ngay khoi hanh: "; 
		ngayKhoiHanh.toString();
		std::cout << " San bay den: " << sanBayDen << std::endl;
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

Ve newVe(int soVe, char* CMND) {
	Ve ve;
	ve.soVe = soVe;
	strcpy(ve.CMND, CMND);
	return ve;
}

void xuatDSVe(DanhSachVe &dsVe) {
	if(dsVe.n == 0) {
		std::cout << "DANH SACH VE RONG!\n"; 
		return;
	}
	for(int i = 0; i < dsVe.n; i++)
		std::cout << "SO VE: " << dsVe.ve[i].soVe << " - CMND: " << dsVe.ve[i].CMND << std::endl;
}

void themVe(Ve ve, DanhSachVe &dsVe) {
	dsVe.ve[dsVe.n++] = ve;
}

void xoaVe(DanhSachVe &dsVe, int ID) {
	for(int i = ID; i < dsVe.n; i++)
		dsVe.ve[i] = dsVe.ve[i + 1];
	dsVe.n--;
}

int timKiemVe(char* CMND, DanhSachVe &dsVe) {
	for(int i = 0; i < dsVe.n; i++)
		if(strcmp(dsVe.ve[i].CMND, CMND) == 0) return i;
	return -1;
}

bool capNhatVe(ChuyenBay *cb, char* CMND, int soVeMoi, char* strErr) {	
	if(cb->trangThai == HETVE) {
		strcpy(strErr,"CHUYEN BAY HET VE, KHONG THE THAY DOI SO GHE!");
		return false;
	}
	int viTri = timKiemVe(CMND, cb->dsVe);
	if(viTri == -1) {
		strcpy(strErr,"SO CMND KHONG TON TAI TRONG DANH SACH VE!");
		return false;
	}
	// soVeMoi luon luon hop le
	cb->dsVe.ve[viTri].soVe = soVeMoi;
	strcpy(strErr, "CAP NHAT VE THANH CONG!");
	return true;
}

void clearDSVe(DanhSachVe &dsVe) {
	delete []dsVe.ve;
}

/*************************************************************************************
 *								  Chuyen bay     									 *
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

///

void themChuyenBayCoThuTu(NodeChuyenBay *nodeCB, DanhSachChuyenBay &dsCB) {
	if(dsCB == NULL || !ktDt2LonHonDt(dsCB->chuyenBay.ngayKhoiHanh, nodeCB->chuyenBay.ngayKhoiHanh)) {
		themDauDanhSach(nodeCB, dsCB);
		return;
	}
	NodeChuyenBay* nodeChay = dsCB;
	while(nodeChay->next != NULL && ktDt2LonHonDt(nodeChay->next->chuyenBay.ngayKhoiHanh, nodeCB->chuyenBay.ngayKhoiHanh))
		nodeChay = nodeChay->next;
	if(nodeChay->next != NULL) 
		nodeCB->next = nodeChay->next;
	nodeChay->next = nodeCB;
}

///

ChuyenBay* timKiemChuyenBay(char* maChuyenBay, DanhSachChuyenBay &dsCB) {
		for(NodeChuyenBay *nodeChay = dsCB; nodeChay != NULL ; nodeChay = nodeChay->next) 
			if(strcmp(nodeChay->chuyenBay.maChuyenBay, maChuyenBay) == 0)
				return &(nodeChay->chuyenBay);
	return NULL;
}

bool huyChuyenBay(ChuyenBay *cb, char* strErr) {
	if(cb->trangThai == HOANTAT) {
		strcpy(strErr, "CHUYEN BAY DA HOAN TAT, KHONG THE HUY!");
		return false;
	}
	if(cb->trangThai == HUYCHUYEN) {
		strcpy(strErr, "CHUYEN BAY DA BI HUY TRUOC DO!");
		return false;
	}
	cb->trangThai = HUYCHUYEN;
	strcpy(strErr, "HUY CHUYEN BAY THANH CONG!");
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
