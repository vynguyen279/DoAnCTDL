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

int soVeConTrong(DanhSachVe &dsVe) {
	int cnt = 0;
	for(int i = 0; i < dsVe.soLuongVe; i++)
		if(dsVe.CMND[i] == NULL) cnt++;
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
		if(dsVe.CMND[i] != NULL && stricmp(dsVe.CMND[i], CMND) == 0) return true;
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
		if(dsVe.CMND[i] != NULL && stricmp(dsVe.CMND[i], CMND) == 0) 
			return i;
	return -1;
}

bool capNhatDanhSachVe(ChuyenBay *cb, char* CMND, int soVeMoi, char* strErr) {	
	if(cb->trangThai == HETVE) {
		strcpy(strErr,"CHUYEN BAY HET VE, KHONG THE THAY DOI SO GHE!");
		return false;
	}
	int viTri = timKiemVe(CMND, cb->dsVe);
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
	strcpy(strErr, "CAP NHAT VE THANH CONG!");
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
			if(stricmp(nodeChay->chuyenBay.maChuyenBay, maChuyenBay) == 0)
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
