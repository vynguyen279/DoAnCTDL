#include "hanh_khach.h"
#include "xu_ly_chuyen_bay.h"

bool datVe(char *CMND, int soVe, ChuyenBay *cb, DanhSachHanhKhach &dsHK, DanhSachChuyenBay &dsCB, char* strErr) {
	HanhKhach* hk = timKiemHanhKhach(dsHK, CMND);
	if(hk == NULL) {
		return themVeVaoChuyenBay(CMND, soVe, cb, strErr);
	}
	strcpy(strErr, "");
	if(ktTonTaiCMNDTrongDSVe(cb->dsVe, CMND)) {
		strcpy(strErr, "MOI HANH KHACH CHI DUOC DAT 1 VE TREN MOT CHUYEN BAY!");
		return false;
	} 
	else {
		char maCBTrung[MAXMACB];
		strcpy(maCBTrung, "");
		if(kt2CBHonNhauDISTGio(dsCB,CMND, *cb, maCBTrung)) {
			return themVeVaoChuyenBay(CMND, soVe, cb, strErr);
		}
		strcat(strErr, "TRUNG GIO KHOI HANH VOI CHUYEN BAY ");
		strcat(strErr, maCBTrung);
		return false;
	}
}

bool huyVe(ChuyenBay *cb, char *CMND, DanhSachHanhKhach &dsHK, char* strErr) {
	int i = timKiemVe(CMND, cb->dsVe);
	if(i == -1) {
		strcpy(strErr, "CMND KHONG TON TAI TRONG DANH SACH VE!");
		return false;
	}
	delete []cb->dsVe.CMND[i];
	cb->dsVe.CMND[i] = NULL;
	xoaHanhKhach(dsHK, CMND);
	if(cb->trangThai == 2) cb->trangThai = 1;
	strcpy(strErr, "HUY VE THANH CONG!");
	return true;
}
