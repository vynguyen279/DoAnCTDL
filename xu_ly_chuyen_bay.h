#pragma once
#include "chuyen_bay.h"
#include "may_bay.h"
#include "ngay_thang_nam.h"
#include "hanh_khach.h"
#include <cstring>

/*
	* Mang con tro tro toi cac chuyen bay trong danh sach chuyen bay
	* Tra ve danh sach nay khi nguoi dung muon tim mot chuyen bay thong qua
	* san bay den va thoi gian khoi hanh (1 san bay den -> nhieu chuyen bay) -> danh sach
	* 1 thoi gian khoi hanh -> nhieu chuyen bay -> danh sach
	* Tra ve con tro de thuan tien trong viec chinh sua cac truong
	
	Note: DanhSachTam khong tao moi cac vung nho cho cac con tro ma cac con tro nay tro toi
		di chi cua chuyen bay thoa man dieu kien san bay den hay thoi gian khoi hanh -> khong can giai phong vung nho
*/

struct DanhSachTam{
	ChuyenBay *cb[MAXTMP];
	int n = 0;
};

/*
	Input:
		dsCB: danh sach chuyen bay;
		maChuyenBay: ma cua chuyen bay can kiem tra;
	Output:
		false: khong ton tai chuyen bay voi ma chuyen bay la maChuyenBay;
		true: ton tai chuyen bay voi ma chuyen bay la maChuyenBay;
*/

bool ktTonTaiChuyenBay(DanhSachChuyenBay &dsCB, char* maChuyenBay) {
	NodeChuyenBay* nodeChay = dsCB;
	for(;nodeChay != NULL; nodeChay = nodeChay->next) {
		if(stricmp(nodeChay->chuyenBay.maChuyenBay, maChuyenBay) == 0)
			return true;
	}
	return false;
}

/*
	Input:
		cb: chuyen bay can kiem tra;
		dsCB: danh sach chuyen bay;
	Output:
		false: chuyen bay cb khong bi trung gio khoi hanh voi chuyen bay khac tren cung mot may bay;
		true: chuyen bay cb bi trung gio khoi hanh voi chuyen bay khac tren cung mot may bay;
*/

bool kt2CBTrenMBTrungGioKH(ChuyenBay cb, DanhSachChuyenBay &dsCB) {
	NodeChuyenBay *nodeChay = dsCB;
	for(; nodeChay != NULL; nodeChay = nodeChay->next) {
		if(stricmp(nodeChay->chuyenBay.soHieuMayBay, cb.soHieuMayBay) == 0) {
			if(ktCungNgayThangNamGioPhut(nodeChay->chuyenBay.ngayKhoiHanh, cb.ngayKhoiHanh)) 
				return true;
		}
	}
	return false;
}

void themPhanTuVaoDSTmp(ChuyenBay *cb, DanhSachTam &dsTmp) {
	dsTmp.cb[dsTmp.n++] = cb;
}

/*
	Input:
		*nodeCB: con tro node chuyen bay;
		dsCB: danh sach chuyen bay can them *nodeCB;
		dsMB: danh sach may bay de kiem tra ngoai le;
		dsTmp: danh sach tam de truy xuat theo index;
		*strErr: chuoi loi;
	Output:
		false: khong the them chuyen bay vao dsCB, strErr tra ve chuoi loi;
		true: them chuyen bay vao dsCB thanh cong, strErr rong;
*/

bool themChuyenBayHopLe(NodeChuyenBay* nodeCB, DanhSachChuyenBay &dsCB, DanhSachMayBay &dsMB, DanhSachTam &dsTmp, char* strErr) {
	strcpy(strErr, "THEM CHUYEN BAY THANH CONG!");
	int viTri = timKiemMayBay(nodeCB->chuyenBay.soHieuMayBay, dsMB);
	if(viTri == -1) {
		strcpy(strErr, "MAY BAY KHONG TON TAI!");
		return false;
	}
	if(ktTonTaiChuyenBay(dsCB, nodeCB->chuyenBay.maChuyenBay)) {
		strcpy(strErr, "CHUYEN BAY DA TON TAI!");
		return false;
	}
	if(ktNgayThangNamHopLe(nodeCB->chuyenBay.ngayKhoiHanh, strErr) == 0) return false;
	if(kt2CBTrenMBTrungGioKH(nodeCB->chuyenBay, dsCB) || ktHoanTat(nodeCB->chuyenBay.ngayKhoiHanh)) {
		strcpy(strErr, "THOI GIAN KHOI HANH KHONG HOP LE!");
		return false;
	}
	// Khoi tao danh sach ve
	nodeCB->chuyenBay.dsVe.soLuongVe = dsMB.mayBay[viTri]->soCho;
	nodeCB->chuyenBay.dsVe.CMND = new char*[nodeCB->chuyenBay.dsVe.soLuongVe];
	initDSVe(nodeCB->chuyenBay.dsVe);
	themChuyenBay(nodeCB, dsCB);
	themPhanTuVaoDSTmp(&(nodeCB->chuyenBay), dsTmp);
	return true;
}

void xuatDSTmp(DanhSachTam &dsTmp) {
	if(dsTmp.n == 0) {
		std::cout << "DANH SACH RONG!\n";
		return;
	}
	for(int i = 0; i < dsTmp.n; i++) {
		dsTmp.cb[i]->toString();
		xuatDSVe(dsTmp.cb[i]->dsVe);
		std::cout << std::endl;
	}
		
}

// Cap nhat trang thai het ve luc them ve vao chuyen bay
void capNhatTrangThaiHetVe(ChuyenBay &chuyenBay) {
	if(chuyenBay.dsVe.soLuongVe == soVeDaDat(chuyenBay.dsVe)) 
		chuyenBay.trangThai = 2;
} 

// Cap nhat trang thai hoan tat khi lay tu file ra hay duyet danh sach chuyen bay
void capNhatTrangThaiHoanTat(ChuyenBay &chuyenBay) {
	if(ktHoanTat(chuyenBay.ngayKhoiHanh))	
		chuyenBay.trangThai = 3;
}

/*
	Input:
		dsCB: danh sach chuyen bay;
	Output:
		dsTmp: danh sach tam (truy xuat thong qua index) ma moi phan tu trong danh sach tro den moi chuyen bay
			trong danh sach chuyen bay;
*/

DanhSachTam dsNode2DsTmp(DanhSachChuyenBay &dsCB) {
	DanhSachTam dsTmp;
	NodeChuyenBay *nodeChay = dsCB;
	for(; nodeChay != NULL; nodeChay = nodeChay->next) {
		capNhatTrangThaiHoanTat(nodeChay->chuyenBay);
		themPhanTuVaoDSTmp(&(nodeChay->chuyenBay), dsTmp);
	}
	return dsTmp;
}

/*
	Input:
		sanBayDen: san bay den cua chuyen bay;
		dsCB: danh sach chuyen bay;
	Output:
		dsTmp: danh sach tam (truy xuat qua index) ma moi phan tu cua danh sach tro den moi chuyen bay
			trong danh sach chuyen bay qua dieu kien co san bay den la sanBayDen;
*/

DanhSachTam dsCBvoiSanBayDen(char *sanBayDen, DanhSachChuyenBay &dsCB) {
	DanhSachTam dsTmp;
	NodeChuyenBay *nodeChay = dsCB;
	if(stricmp(sanBayDen, "ALL") == 0) dsTmp = dsNode2DsTmp(dsCB);
	else {
		for(; nodeChay != NULL; nodeChay = nodeChay->next) {
			capNhatTrangThaiHoanTat(nodeChay->chuyenBay);
			if(stricmp(sanBayDen, nodeChay->chuyenBay.sanBayDen) == 0) 
				themPhanTuVaoDSTmp(&(nodeChay->chuyenBay), dsTmp);
		}
	}
	return dsTmp;
}

/*
	Input:
		ngayKhoiHanh: ngay khoi hanh cua chuyen bay;
		dsCB: danh sach chuyen bay;
		*strErr: chuoi loi;
	Output:
		dsTmp: danh sach tam (truy xuat qua index) ma moi phan tu cua danh sach tro den moi chuyen bay
			trong danh sach chuyen bay qua dieu kien co ngay khoi hanh la ngayKhoiHanh;
*/

DanhSachTam dsCBvoiNgayKhoiHanh(NgayThangNam ngayKhoiHanh, DanhSachChuyenBay &dsCB, char* strErr) {
	DanhSachTam dsTmp;
	NodeChuyenBay *nodeChay = dsCB;
	if(ktNgayThangNamHopLe(ngayKhoiHanh, strErr)) {
		for(; nodeChay != NULL; nodeChay = nodeChay->next) {
			capNhatTrangThaiHoanTat(nodeChay->chuyenBay);
			if(ktCungNgayThangNam(ngayKhoiHanh, nodeChay->chuyenBay.ngayKhoiHanh))
				themPhanTuVaoDSTmp(&(nodeChay->chuyenBay), dsTmp);
		}
	}
	return dsTmp;
}

/*
	Input:
		sanBayDen: san bay den cua chuyen bay;
		ngayKhoiHanh: ngay khoi hanh cua chuyen bay;
		dsCB: danh sach chuyen bay;
	Output:
		dsTmp: danh sach tam (truy xuat qua index) ma moi phan tu cua danh sach tro den moi chuyen bay
			trong danh sach chuyen bay qua dieu kien co san bay den la sanBayDen va ngay khoi hanh la ngayKhoiHanh;
*/

DanhSachTam dsCBvoiNgayKhoiHanhVaSanBayDen(char *sanBayDen, NgayThangNam ngayKhoiHanh, DanhSachChuyenBay &dsCB) {
	DanhSachTam dsTmp;
	NodeChuyenBay *nodeChay = dsCB;
	for(; nodeChay != NULL; nodeChay = nodeChay->next) {
		capNhatTrangThaiHoanTat(nodeChay->chuyenBay);
		if(ktCungNgayThangNam(ngayKhoiHanh, nodeChay->chuyenBay.ngayKhoiHanh) 
			&& strcmp(sanBayDen, nodeChay->chuyenBay.sanBayDen) == 0)
			themPhanTuVaoDSTmp(&(nodeChay->chuyenBay), dsTmp);
	}
	return dsTmp;
}

/*
	Input:
		dsCB: danh sach chuyen bay;
	Output:
		dsTmp: danh sach tam (truy xuat thong qua index) ma moi phan tu trong danh sach tro den moi chuyen bay
			trong danh sach chuyen bay voi dieu kien trang thai cua chuyen bay == 1;
*/

DanhSachTam dsNode2DsTmpConVe(DanhSachChuyenBay &dsCB) {
	DanhSachTam dsTmp;
	NodeChuyenBay *nodeChay = dsCB;
	for(; nodeChay != NULL; nodeChay = nodeChay->next) {
		capNhatTrangThaiHoanTat(nodeChay->chuyenBay);
		if(nodeChay->chuyenBay.trangThai == 1)
			themPhanTuVaoDSTmp(&(nodeChay->chuyenBay), dsTmp);
	}
	return dsTmp;
}

/*
	Input:
		sanBayDen: san bay den cua chuyen bay;
		dsCB: danh sach chuyen bay;
	Output:
		dsTmp: danh sach tam (truy xuat qua index) ma moi phan tu cua danh sach tro den moi chuyen bay
			trong danh sach chuyen bay qua dieu kien trang thai cua chuyen bay == 1 va co san bay den la sanBayDen;
*/

DanhSachTam dsCBvoiSanBayDenConVe(char *sanBayDen, DanhSachChuyenBay &dsCB) {
	DanhSachTam dsTmp;
	NodeChuyenBay *nodeChay = dsCB;
	if(stricmp(sanBayDen, "ALL") == 0) dsTmp = dsNode2DsTmp(dsCB);
	else {
		for(; nodeChay != NULL; nodeChay = nodeChay->next) {
			capNhatTrangThaiHoanTat(nodeChay->chuyenBay);
			if(stricmp(sanBayDen, nodeChay->chuyenBay.sanBayDen) == 0 && nodeChay->chuyenBay.trangThai == 1) 
				themPhanTuVaoDSTmp(&(nodeChay->chuyenBay), dsTmp);
		}
	}
	return dsTmp;
}

/*
	Input:
		ngayKhoiHanh: ngay khoi hanh cua chuyen bay;
		dsCB: danh sach chuyen bay;
		*strErr: chuoi loi;
	Output:
		dsTmp: danh sach tam (truy xuat qua index) ma moi phan tu cua danh sach tro den moi chuyen bay
			trong danh sach chuyen bay qua dieu kien trang thai cua chuyen bay == 1 va co ngay khoi hanh la ngayKhoiHanh;
*/

DanhSachTam dsCBvoiNgayKhoiHanhConVe(NgayThangNam ngayKhoiHanh, DanhSachChuyenBay &dsCB, char* strErr) {
	DanhSachTam dsTmp;
	NodeChuyenBay *nodeChay = dsCB;
	if(ktNgayThangNamHopLe(ngayKhoiHanh, strErr)) {
		for(; nodeChay != NULL; nodeChay = nodeChay->next) {
			capNhatTrangThaiHoanTat(nodeChay->chuyenBay);
			if(ktCungNgayThangNam(ngayKhoiHanh, nodeChay->chuyenBay.ngayKhoiHanh) && nodeChay->chuyenBay.trangThai == 1)
				themPhanTuVaoDSTmp(&(nodeChay->chuyenBay), dsTmp);
		}
	}
	return dsTmp;
}

/*
	Input:
		sanBayDen: san bay den cua chuyen bay;
		ngayKhoiHanh: ngay khoi hanh cua chuyen bay;
		dsCB: danh sach chuyen bay;
	Output:
		dsTmp: danh sach tam (truy xuat qua index) ma moi phan tu cua danh sach tro den moi chuyen bay
			trong danh sach chuyen bay qua dieu kien trang thai cua chuyen bay == 1,
			co san bay den la sanBayDen va ngay khoi hanh la ngayKhoiHanh;
*/

DanhSachTam dsCBvoiNgayKhoiHanhVaSanBayDenConVe(char *sanBayDen, NgayThangNam ngayKhoiHanh, DanhSachChuyenBay &dsCB) {
	DanhSachTam dsTmp;
	NodeChuyenBay *nodeChay = dsCB;
	for(; nodeChay != NULL; nodeChay = nodeChay->next) {
		capNhatTrangThaiHoanTat(nodeChay->chuyenBay);
		if(ktCungNgayThangNam(ngayKhoiHanh, nodeChay->chuyenBay.ngayKhoiHanh) 
			&& strcmp(sanBayDen, nodeChay->chuyenBay.sanBayDen) == 0 && nodeChay->chuyenBay.trangThai == 1)
			
			themPhanTuVaoDSTmp(&(nodeChay->chuyenBay), dsTmp);
	}
	return dsTmp;
}


void dsVeConTrongCuaCB(DanhSachTam &dsTmp, int viTri) {
	for(int i = 0; i < dsTmp.cb[viTri]->dsVe.soLuongVe; i++)
		if(dsTmp.cb[viTri]->dsVe.CMND[i] == NULL)
			std:: cout << i + 1 << std::endl;
}

int soLuongVeConTrongCuaCB(ChuyenBay cb) {
	int cnt = 0;
	for(int i = 0; i < cb.dsVe.soLuongVe; i++)
		if(cb.dsVe.CMND[i] == NULL) cnt++;
	return cnt;
}

bool themVeVaoChuyenBay(char *CMND, int soVe, ChuyenBay *cb, char* strErr) {
	strcpy(strErr, "THEM VE THANH CONG!");
	if(!soVeHopLe(soVe, cb->dsVe)) {
		strcpy(strErr, "SO VE KHONG HOP LE!");
		return false;
	}
	themVe(soVe, CMND, cb->dsVe);
	capNhatTrangThaiHetVe(*cb);
	return true;
}

void xuatDSCB(DanhSachChuyenBay &dsCB, DanhSachMayBay &dsMB) {
	if(dsCB == NULL) {
		std::cout << "DANH SACH CHUYEN BAY RONG!\n";
		return;
	}
	for(NodeChuyenBay *nodeChuyenBay = dsCB; nodeChuyenBay != NULL; nodeChuyenBay = nodeChuyenBay->next) {
		nodeChuyenBay->chuyenBay.toString();
		xuatDSVe(nodeChuyenBay->chuyenBay.dsVe);
		std::cout << std::endl;
	}
}

/*
	Input:
		dsCB: danh sach chuyen bay;
		CMND: so chung minh nhan dan;
		cb : chuyen bay;
		maCB: ma chuyen bay bi trung gio khoi hanh;
	Output:
		false: chuyen bay cb khong bi trung gio khoi hanh voi chuyen bay khac, tham bien maCB la rong;
		true: chuyen bay cb bi trung gio khoi hanh voi chuyen bay khac, tham bien maCB la ma chuyen bay trung;
*/

bool ktCBTrungGioVoiCBKhac(DanhSachChuyenBay &dsCB, char* CMND, ChuyenBay cb, char* maCB) {
	NodeChuyenBay *nodeChay = dsCB;
	for(; nodeChay != NULL; nodeChay = nodeChay->next) {
		if(ktTonTaiCMNDTrongDSVe(nodeChay->chuyenBay.dsVe, CMND) 
			&& stricmp(nodeChay->chuyenBay.maChuyenBay, cb.maChuyenBay) != 0) {
				
			if(ktCungNgayThangNamGioPhut(nodeChay->chuyenBay.ngayKhoiHanh, cb.ngayKhoiHanh)) {
				strcpy(maCB, nodeChay->chuyenBay.maChuyenBay);
				return true;
			}
		}
	}
	return false;
}

/*
	Input:
		*cb: con tro chuyen bay can huy ve;
		*CMND: chuoi chung minh nhan dan;
		dsHK: danh sach hanh khach de cap nhat lai hanh khach;
		*strErr: chuoi loi;
	Output:
		false: huy ve khong thanh cong, strErr tra ve loi;
		true: huy ve thanh cong, strErr rong;
*/

bool huyVe(ChuyenBay *cb, char *CMND, DanhSachHanhKhach &dsHK, char* strErr) {
	strcpy(strErr, "HUY VE THANH CONG!");
	int i = timKiemVe(CMND, cb->dsVe);
	if(i == -1) {
		strcpy(strErr, "CMND KHONG TON TAI TRONG DANH SACH VE!");
		return false;
	}
	delete []cb->dsVe.CMND[i];
	cb->dsVe.CMND[i] = NULL;
	xoaHanhKhach(dsHK, CMND);
	if(cb->trangThai == 2) cb->trangThai = 1;
	return true;
}

bool xuatDSHKDuaVaoMaCB(DanhSachChuyenBay &dsCB,DanhSachHanhKhach &dsHK, char* maCB, ListHanhKhachThongKe &listTK, char* strErr) {
	strcpy(strErr, "");
	ChuyenBay *cb = timKiemChuyenBay(maCB, dsCB);
	if(cb == NULL) {
		strcpy(strErr, "CHUYEN BAY KHONG TON TAI!");
		return false;
	}
	HanhKhach *hk;
	listTK.hanhKhachTK = new HanhKhachThongKe[cb->dsVe.soLuongVe];
	for(int i = 0; i < cb->dsVe.soLuongVe; i++) {
		if(cb->dsVe.CMND[i] != NULL) {
			hk = timKiemHanhKhach(dsHK, cb->dsVe.CMND[i]);
			themVaoListHKTK(newHanhKhachThongKe(*hk, i + 1), listTK);
		}
	}
	return true;
}
/*
	Input:
		dsCB : danh sach chuyen bay
		cb : chuyen bay lay tu su kien lick cua user
		dt: ngay thang nam muon cap nhat
		strErr: chuoi loi tra ra sau khi goi ham
	Output:
		false: cap nhat that bai, chuoi loi strErr co gia tri;
		true: cap nhat thanh cong, chuoi loi strErr rong;
*/

bool capNhatNgayThangNam(DanhSachChuyenBay &dsCB, ChuyenBay *cb, NgayThangNam dt, char* strErr) {
	// Xu ly 1 may bay co 2 chuyen bay cung gio khoi hanh sau khi cap nhat lai ngay khoi hanh
	strcpy(strErr, "CAP NHAT THANH CONG!");
	NodeChuyenBay* nodeChay = dsCB;
	for(; nodeChay != NULL; nodeChay = nodeChay->next) {
		if(stricmp(nodeChay->chuyenBay.soHieuMayBay, cb->soHieuMayBay) == 0 
			&& stricmp(nodeChay->chuyenBay.maChuyenBay, cb->maChuyenBay) != 0) {
		
			if(ktCungNgayThangNamGioPhut(nodeChay->chuyenBay.ngayKhoiHanh, dt)) {
				char str1[255];
				strcpy(str1, "");
				strcat(str1, "CAP NHAT THAT BAI!\n");
				strcat(str1,"MAY BAY ");
				strcat(str1,nodeChay->chuyenBay.soHieuMayBay);
				strcat(str1, " DA CO CHUYEN BAY ");
				strcat(str1, nodeChay->chuyenBay.maChuyenBay);
				strcpy(strErr, str1);
				return false;
			}
		}
	}
	// Xu ly 1 trong cac hanh khach tren chuyen bay chinh sua ngay khoi hanh trung voi ngay khoi hanh cua
	// chuyen bay ma hanh khach dat truoc do
	char maCBTrung[MAXMACB];
	NgayThangNam dtTmp = cb->ngayKhoiHanh;
	cb->ngayKhoiHanh = dt;
	for(int i = 0; i < cb->dsVe.soLuongVe; i++) {
		if(cb->dsVe.CMND[i] != NULL) {
			if(ktCBTrungGioVoiCBKhac(dsCB,cb->dsVe.CMND[i],*cb,maCBTrung)) {
				char str[255];
				strcpy(str, "");
				strcat(str, "CAP NHAT THAT BAI!\nHANH KHACH CO SO CMND");
				strcat(str, cb->dsVe.CMND[i]);
				strcat(str, " BI TRUNG GIO KHOI HANH VOI CHUYEN BAY ");
				strcat(str, maCBTrung);
				strcpy(strErr, str);
				cb->ngayKhoiHanh = dtTmp;
				return false;
			}
		}
	}
	if(!ktNgayThangNamHopLe(dt, strErr) || ktHoanTat(dt)) {
		strcpy(strErr,"THOI GIAN KHOI HANH KHONG HOP LE!\n");
		return false;
	}
	cb->ngayKhoiHanh = dt;
	return true;
}

int timKiemChuyenBayTrenDsTmp(char* maCB, DanhSachTam &dsTmp, char* strErr) {
	strcpy(strErr, "CHUYEN BAY KHONG TON TAI!");
	int viTri = -1;
	for(int i = 0; i < dsTmp.n; i++) {
		if(stricmp(dsTmp.cb[i]->maChuyenBay, maCB) == 0) {
			viTri = i;
			strcpy(strErr, "");
			break;
		}
	}
	return viTri;
}

void clearDSTmp(DanhSachTam &dsTmp) {
	dsTmp.n = 0;
}
