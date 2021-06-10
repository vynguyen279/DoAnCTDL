#pragma once
#include "xu_ly_chuyen_bay.h"
#include "hash_table_hanh_khach.h"
#include "xu_ly_hanh_khach.h"
#include "configure.h"

bool datVe(char *CMND, HanhKhach *hk, int soVe, ChuyenBay *cb, DanhSachHanhKhach &dsHK, DanhSachChuyenBay &dsCB, char* strErr) {
	strcpy(strErr, "DAT VE THANH CONG!");
	if(hk == NULL) {
		themVeVaoChuyenBay(newVe(soVe, CMND), cb);
		return true;
	}
	if(timKiemVe(CMND, cb->dsVe) != -1) {
		strcpy(strErr, "MOI HANH KHACH CHI DUOC DAT 1 VE TREN MOT CHUYEN BAY!");
		return false;
	} else {
		char maCBTrung[MAXMACB];
		strcpy(maCBTrung, "");
		if(kt2CBHonNhauDISTGio(dsCB, CMND, *cb, maCBTrung)) {
			themVeVaoChuyenBay(newVe(soVe, CMND), cb);
			return true;
		}
		strcat(strErr, "TRUNG GIO KHOI HANH VOI CHUYEN BAY ");
		strcat(strErr, maCBTrung);
		return false;
	}
}

bool huyVe(ChuyenBay *cb, int ID, DanhSachHanhKhach &dsHK, HashTableCustomer &table, char* strErr) {
	xoaHanhKhach(dsHK, cb->dsVe.ve[ID].CMND, table);
	xoaVe(cb->dsVe, ID);
}
