#pragma once
#include "may_bay.h"
#include "chuyen_bay.h"

bool ktMayBayDaCoChuyenBay(char *soHieuMB, DanhSachChuyenBay &dsCB) {
	NodeChuyenBay* nodeChay = dsCB;
	for(; nodeChay != NULL && strcmp(nodeChay->chuyenBay.soHieuMayBay, soHieuMB) != 0; nodeChay = nodeChay->next);
	return nodeChay != NULL;
}

bool xoaMayBayHopLe(char *soHieuMB, DanhSachMayBay &dsMB, DanhSachChuyenBay &dsCB, char* strErr) {
	if(ktMayBayDaCoChuyenBay(soHieuMB, dsCB)) {
		strcpy(strErr, "MAY BAY DANG CO CHUYEN BAY");
		return false;
	}
	int viTriXoa = timKiemMayBay(soHieuMB, dsMB);
	if(viTriXoa == -1) {
		strcpy(strErr, "KHONG TON TAI MAY BAY TRONG DANH SACH!");
		return false;
	}
	xoaMayBay(dsMB, viTriXoa);
	strcpy(strErr, "XOA MAY BAY THANH CONG!");
	return true;
}

bool themMayBayHopLe(MayBay mb, DanhSachMayBay &dsMB, char* strErr) {
	if(dsMB.n == MAXMAYBAY) {
		strcpy(strErr, "DANH SACH DAY!");
		return false;
	} 
	if(mb.soCho < MINSOCHO) {
		strcpy(strErr, "SO CHO TOI THIEU LA 20!");
		return false;
	}
	if(mb.soCho > MAXSOCHO) {
		strcpy(strErr, "SO CHO TOI DA LA 300!");
		return false;
	}	 
	if(timKiemMayBay(mb.soHieuMayBay, dsMB) != -1) {
		strcpy(strErr, "MAY BAY DA TON TAI!");
		return false;
	}
	themMayBay(mb, dsMB);	
	strcpy(strErr, "THEM MAY BAY THANH CONG!");
	return true;
}

bool capNhatMayBay(char* loaiMBMoi, int soChoMoi, DanhSachMayBay &dsMB,short ID, char* strErr) {

	if(ID < 0) {
		strcpy(strErr, "MAY BAY KHONG TON TAI!");
		return false;
	}
	capNhatLoaiMB(loaiMBMoi, ID, dsMB);
	if(soChoMoi < MINSOCHO) {
		strcpy(strErr, "SO CHO TOI THIEU LA 20!");
		return false;
	}
	if(soChoMoi > MAXSOCHO) {
	strcpy(strErr, "SO CHO TOI DA LA 300!");
	return false;
	}
	capNhatSoCho(soChoMoi, ID, dsMB);
	strcpy(strErr, "CAP NHAT MAY BAY THANH CONG!");
	return true;
}
