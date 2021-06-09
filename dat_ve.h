#pragma once
#include "xu_ly_chuyen_bay.h"
#include "hash_table_hanh_khach.h"
#include "xu_ly_hanh_khach.h"
#include "configure.h"

bool datVe(char *CMND, HanhKhach *hk, int soVe, ChuyenBay *cb, DanhSachHanhKhach &dsHK, DanhSachChuyenBay &dsCB, char* strErr) {
	strcpy(strErr, "DAT VE THANH CONG!");
	if(hk == NULL) {
		themVeVaoChuyenBay(CMND, soVe, cb);
		return true;
	}
	if(ktTonTaiCMNDTrongDSVe(cb->dsVe, CMND)) {
		strcpy(strErr, "MOI HANH KHACH CHI DUOC DAT 1 VE TREN MOT CHUYEN BAY!");
		return false;
	} else {
		char maCBTrung[MAXMACB];
		strcpy(maCBTrung, "");
		if(kt2CBHonNhauDISTGio(dsCB, CMND, *cb, maCBTrung)) {
			themVeVaoChuyenBay(CMND, soVe, cb);
			return true;
		}
		strcat(strErr, "TRUNG GIO KHOI HANH VOI CHUYEN BAY ");
		strcat(strErr, maCBTrung);
		return false;
	}
}

bool huyVe(ChuyenBay *cb, char *CMND, DanhSachHanhKhach &dsHK, HashTableCustomer &table, char* strErr) {
	int i = timKiemVe(CMND, cb->dsVe);
	if(i == -1) {
		strcpy(strErr, "CMND KHONG TON TAI TRONG DANH SACH VE!");
		return false;
	}
	delete []cb->dsVe.CMND[i];
	cb->dsVe.CMND[i] = NULL;
	xoaHanhKhach(dsHK, CMND, table);
	if(cb->trangThai == HETVE) cb->trangThai = CONVE;
	strcpy(strErr, "HUY VE THANH CONG!");
	return true;
}
