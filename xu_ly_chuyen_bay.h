#pragma once
#include "chuyen_bay.h"
#include "may_bay.h"
#include "ngay_thang_nam.h"
#include "hanh_khach.h"
#include "configure.h"
#include <cstring>

struct DanhSachTam{
	ChuyenBay *cb[MAXTMP];
	int n = 0;
};

void initDanhSachTam(DanhSachTam &dsTmp) {
	for(int i = 0; i < MAXTMP; i++) 
		dsTmp.cb[i] = NULL;
}

void themPhanTuVaoDSTmp(ChuyenBay *cb, DanhSachTam &dsTmp) {
	dsTmp.cb[dsTmp.n++] = cb;
}

void themPhanTuVaoDSTmpCoThuTu(ChuyenBay *cb, DanhSachTam &dsTmp) {
	int i = 0;
	for(; i < dsTmp.n && ktDt2LonHonDt(dsTmp.cb[i]->ngayKhoiHanh, cb->ngayKhoiHanh); i++);
	dsTmp.n++;
	for(int j = dsTmp.n - 1; j > i; j--) dsTmp.cb[j] = dsTmp.cb[j - 1];
	dsTmp.cb[i] = cb;
	
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

void clearDSTmp(DanhSachTam &dsTmp) {
	for(int i = 0; i < dsTmp.n; i++) 
		dsTmp.cb[i] = NULL;
	dsTmp.n = 0;
}

bool kt2CBHonNhauDISTGio(DanhSachChuyenBay &dsCB, char* CMND, ChuyenBay cb, char* strErr) {
	NodeChuyenBay *nodeChay = dsCB;
	for(; nodeChay != NULL; nodeChay = nodeChay->next) {
		if(
			strcmp(nodeChay->chuyenBay.maChuyenBay, cb.maChuyenBay) != 0
			&& nodeChay->chuyenBay.trangThai != HUYCHUYEN
			&& nodeChay->chuyenBay.trangThai != HOANTAT
		) {
			if(timKiemVe(CMND, cb.dsVe) != -1) {
				if(
					!ktDt2LonHonDISTGioDt(nodeChay->chuyenBay.ngayKhoiHanh, cb.ngayKhoiHanh)
					&& !ktDt2LonHonDISTGioDt(cb.ngayKhoiHanh, nodeChay->chuyenBay.ngayKhoiHanh)
				) {
					strcpy(strErr, nodeChay->chuyenBay.maChuyenBay);
					return false;		
				}	
			}
		}
	}
	return true;
}

bool kt2CBTrenMBHonNhauDISTGio(ChuyenBay cb, DanhSachChuyenBay &dsCB, char* strErr) {
	NodeChuyenBay *nodeChay = dsCB;
	for(; nodeChay != NULL; nodeChay = nodeChay->next) {
		if(
            strcmp(nodeChay->chuyenBay.soHieuMayBay, cb.soHieuMayBay) == 0 
			&& strcmp(nodeChay->chuyenBay.maChuyenBay, cb.maChuyenBay) != 0 
			&& nodeChay->chuyenBay.trangThai != HUYCHUYEN
			&& nodeChay->chuyenBay.trangThai != HOANTAT
        ) {
            if(
                !ktDt2LonHonDISTGioDt(nodeChay->chuyenBay.ngayKhoiHanh, cb.ngayKhoiHanh)
                && !ktDt2LonHonDISTGioDt(cb.ngayKhoiHanh, nodeChay->chuyenBay.ngayKhoiHanh)
            ) {
                if(ktDt2LonHonDt(nodeChay->chuyenBay.ngayKhoiHanh, cb.ngayKhoiHanh)) {
                    strcpy(strErr, "TRONG THOI GIAN THUC HIEN BAY CUA CHUYEN BAY ");
                    strcat(strErr, nodeChay->chuyenBay.maChuyenBay);
                    strcat(strErr, " THUOC MAY BAY ");
                    strcat(strErr, cb.soHieuMayBay);
                    strcat(strErr, "!");
                    return false;
                }
                if(ktDt2LonHonDt(cb.ngayKhoiHanh, nodeChay->chuyenBay.ngayKhoiHanh)) {
                    char strDay[100];
                    dinhDangNgayThangNam(strDay, nodeChay->chuyenBay.ngayKhoiHanh);
                    strcpy(strErr, "KHONG DU THOI GIAN DE THUC HIEN CHUYEN BAY, MAY BAY ");
                    strcat(strErr, cb.soHieuMayBay);
                    strcat(strErr, " CO CHUYEN BAY ");
                    strcat(strErr, nodeChay->chuyenBay.maChuyenBay);
                    strcat(strErr, " VAO LUC ");
                    strcat(strErr, strDay);
                    strcat(strErr, "!");
                    return false;
                }
            }
		}
	}
	return true;
}

bool themChuyenBayHopLe(NodeChuyenBay* nodeCB, DanhSachChuyenBay &dsCB, DanhSachMayBay &dsMB, DanhSachTam &dsTmp, char* strErr) {
	int viTri = timKiemMayBay(nodeCB->chuyenBay.soHieuMayBay, dsMB);
	if(viTri == -1) {
		strcpy(strErr, "MAY BAY KHONG TON TAI!");
		return false;
	}
	if(timKiemChuyenBay(nodeCB->chuyenBay.maChuyenBay, dsCB) != NULL) {
		strcpy(strErr, "CHUYEN BAY DA TON TAI!");
		return false;
	}
    if(!ktTuongLai(nodeCB->chuyenBay.ngayKhoiHanh)) {
    	strcpy(strErr, "NGAY KHOI HANH PHAI LA MOT NGAY TRONG TUONG LAI!");
    	return false;
	}
	if(!kt2CBTrenMBHonNhauDISTGio(nodeCB->chuyenBay, dsCB, strErr)) return false;
	// Khoi tao danh sach ve
	nodeCB->chuyenBay.dsVe.soLuongVe = dsMB.mayBay[viTri]->soCho;
	nodeCB->chuyenBay.dsVe.ve = new Ve[nodeCB->chuyenBay.dsVe.soLuongVe];
	themChuyenBay(nodeCB, dsCB);
	themPhanTuVaoDSTmp(&(nodeCB->chuyenBay), dsTmp);
	strcpy(strErr, "THEM CHUYEN BAY THANH CONG!");
	return true;
}

// Cap nhat trang thai het ve luc them ve vao chuyen bay
void capNhatTrangThaiHetVe(ChuyenBay &cb) {
	if(cb.dsVe.soLuongVe == cb.dsVe.n) 
		cb.trangThai = HETVE;
} 

// Cap nhat trang thai hoan tat khi lay tu file ra hay duyet danh sach chuyen bay
void capNhatTrangThaiHoanTat(ChuyenBay &cb) {
	if(ktHoanTat(cb.ngayKhoiHanh))	
		cb.trangThai = HOANTAT;
}

DanhSachTam dsNode2DsTmp(DanhSachChuyenBay &dsCB) {
	DanhSachTam dsTmp;
	initDanhSachTam(dsTmp);
	NodeChuyenBay *nodeChay = dsCB;
	for(; nodeChay != NULL; nodeChay = nodeChay->next) {
		capNhatTrangThaiHoanTat(nodeChay->chuyenBay);
		themPhanTuVaoDSTmp(&(nodeChay->chuyenBay), dsTmp);
	}
	return dsTmp;
}

DanhSachTam dsCBvoiSanBayDen(char *sanBayDen, DanhSachChuyenBay &dsCB) {
	DanhSachTam dsTmp;
	initDanhSachTam(dsTmp);
	NodeChuyenBay *nodeChay = dsCB;
	if(strcmp(sanBayDen, "ALL") == 0) dsTmp = dsNode2DsTmp(dsCB);
	else {
		for(; nodeChay != NULL; nodeChay = nodeChay->next) {
			capNhatTrangThaiHoanTat(nodeChay->chuyenBay);
			if(strcmp(sanBayDen, nodeChay->chuyenBay.sanBayDen) == 0) 
				themPhanTuVaoDSTmp(&(nodeChay->chuyenBay), dsTmp);
		}
	}
	return dsTmp;
}

DanhSachTam dsCBvoiNgayKhoiHanh(NgayThangNam ngayKhoiHanh, DanhSachChuyenBay &dsCB) {
	DanhSachTam dsTmp;
	initDanhSachTam(dsTmp);
	NodeChuyenBay *nodeChay = dsCB;
	for(; nodeChay != NULL; nodeChay = nodeChay->next) {
		capNhatTrangThaiHoanTat(nodeChay->chuyenBay);
		if(ktCungNgayThangNam(ngayKhoiHanh, nodeChay->chuyenBay.ngayKhoiHanh))
			themPhanTuVaoDSTmp(&(nodeChay->chuyenBay), dsTmp);
	}
	return dsTmp;
}

DanhSachTam dsCBvoiNgayKhoiHanhVaSanBayDen(char *sanBayDen, NgayThangNam ngayKhoiHanh, DanhSachChuyenBay &dsCB) {
	DanhSachTam dsTmp;
	initDanhSachTam(dsTmp);
	NodeChuyenBay *nodeChay = dsCB;
	for(; nodeChay != NULL; nodeChay = nodeChay->next) {
		capNhatTrangThaiHoanTat(nodeChay->chuyenBay);
		if(ktCungNgayThangNam(ngayKhoiHanh, nodeChay->chuyenBay.ngayKhoiHanh) 
			&& strcmp(sanBayDen, nodeChay->chuyenBay.sanBayDen) == 0)
			themPhanTuVaoDSTmp(&(nodeChay->chuyenBay), dsTmp);
	}
	return dsTmp;
}

DanhSachTam dsNode2DsTmpConVe(DanhSachChuyenBay &dsCB) {
	DanhSachTam dsTmp;
	initDanhSachTam(dsTmp);
	NodeChuyenBay *nodeChay = dsCB;
	for(; nodeChay != NULL; nodeChay = nodeChay->next) {
		capNhatTrangThaiHoanTat(nodeChay->chuyenBay);
		if(nodeChay->chuyenBay.trangThai == CONVE)
			themPhanTuVaoDSTmp(&(nodeChay->chuyenBay), dsTmp);
	}
	return dsTmp;
}

DanhSachTam dsCBvoiSanBayDenConVe(char *sanBayDen, DanhSachChuyenBay &dsCB) {
	DanhSachTam dsTmp;
	initDanhSachTam(dsTmp);
	NodeChuyenBay *nodeChay = dsCB;
	if(strcmp(sanBayDen, "ALL") == 0) dsTmp = dsNode2DsTmpConVe(dsCB);
	else {
		for(; nodeChay != NULL; nodeChay = nodeChay->next) {
			capNhatTrangThaiHoanTat(nodeChay->chuyenBay);
			if(strcmp(sanBayDen, nodeChay->chuyenBay.sanBayDen) == 0 && nodeChay->chuyenBay.trangThai == CONVE) 
				themPhanTuVaoDSTmp(&(nodeChay->chuyenBay), dsTmp);
		}
	}
	return dsTmp;
}

DanhSachTam dsCBvoiNgayKhoiHanhConVe(NgayThangNam ngayKhoiHanh, DanhSachChuyenBay &dsCB) {
	DanhSachTam dsTmp;
	initDanhSachTam(dsTmp);
	NodeChuyenBay *nodeChay = dsCB;
	for(; nodeChay != NULL; nodeChay = nodeChay->next) {
		capNhatTrangThaiHoanTat(nodeChay->chuyenBay);
		if(ktCungNgayThangNam(ngayKhoiHanh, nodeChay->chuyenBay.ngayKhoiHanh) && nodeChay->chuyenBay.trangThai == CONVE)
			themPhanTuVaoDSTmp(&(nodeChay->chuyenBay), dsTmp);
	}
	return dsTmp;
}

DanhSachTam dsCBvoiNgayKhoiHanhVaSanBayDenConVe(char *sanBayDen, NgayThangNam ngayKhoiHanh, DanhSachChuyenBay &dsCB) {
	DanhSachTam dsTmp;
	initDanhSachTam(dsTmp);
	NodeChuyenBay *nodeChay = dsCB;
	for(; nodeChay != NULL; nodeChay = nodeChay->next) {
		capNhatTrangThaiHoanTat(nodeChay->chuyenBay);
		if(ktCungNgayThangNam(ngayKhoiHanh, nodeChay->chuyenBay.ngayKhoiHanh) 
			&& strcmp(sanBayDen, nodeChay->chuyenBay.sanBayDen) == 0 && nodeChay->chuyenBay.trangThai == CONVE)
			themPhanTuVaoDSTmp(&(nodeChay->chuyenBay), dsTmp);
	}
	return dsTmp;
}

void themVeVaoChuyenBay(Ve ve, ChuyenBay *cb) {
	themVe(ve, cb->dsVe);
	capNhatTrangThaiHetVe(*cb);
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

bool capNhatNgayThangNam(DanhSachChuyenBay &dsCB, ChuyenBay *cb, NgayThangNam dt, char* strErr) {
	if(cb->trangThai == HUYCHUYEN) {
		strcpy(strErr, "CHUYEN BAY DA BI HUY!");
		return false;
	}
	if(cb->trangThai == HOANTAT) {
		strcpy(strErr, "CHUYEN BAY DA HOAN TAT!");
		return false;
	}
	if(!ktTuongLai(dt)) {
    	strcpy(strErr, "NGAY KHOI HANH PHAI LA MOT NGAY TRONG TUONG LAI!");
    	return false;
	}
	NgayThangNam dtTmp = cb->ngayKhoiHanh;
	cb->ngayKhoiHanh = dt;
	// Xu ly 1 may bay co 2 chuyen bay cung gio khoi hanh sau khi cap nhat lai ngay khoi hanh
	if(!kt2CBTrenMBHonNhauDISTGio(*cb, dsCB, strErr)) {
		cb->ngayKhoiHanh = dtTmp;
		return false;
	}
	// Xu ly 1 trong cac hanh khach tren chuyen bay chinh sua ngay khoi hanh trung voi ngay khoi hanh cua
	// chuyen bay ma hanh khach dat truoc do
	for(int i = 0; i < cb->dsVe.n; i++) {
		if(!kt2CBHonNhauDISTGio(dsCB, cb->dsVe.ve[i].CMND, *cb, strErr)) {
			cb->ngayKhoiHanh = dtTmp;
			char str[255];
			strcpy(str, "HANH KHACH CO SO CMND ");
			strcat(str, cb->dsVe.ve[i].CMND);
			strcat(str, " BI TRUNG GIO KHOI HANH VOI CHUYEN BAY ");
			strcat(str, strErr);
			strcat(str, "!");
			strcpy(strErr, str);
			return false;
		}
	}
	strcpy(strErr, "CAP NHAT THANH CONG!");
	return true;
}

