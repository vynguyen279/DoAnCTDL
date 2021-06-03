#include "hanh_khach.h"
#include "xu_ly_chuyen_bay.h"
//https://paste.ubuntu.com/p/y5xY8xvStc/
/*
	Ham tra ve gia tri true or false
	Neu co hanh khach trong danh sach (hk != NULL) -> true
	Neu khong (hk == NULL) -> false

	Xu ly ben do hoa
	Ham -> true -> dua thong tin hanh khach len man hinh de kiem tra
	Ham -> false -> yeu cau nguoi dung nhap du thong tin cac truong
*/

/*
	Sau khi hanh khach nhap vao thong tin hoac kiem tra thong tin, cap nhat thong tin
	hanh khach thanh cong thi chuyen layout sang dat ve
	Nguoi dat ve tien hanh click vao 1 ghe trong man hinh voi so ghe nhat dinh
	(Neu ghe da co nguoi dat thi mau do, ghe chua co nguoi dat thi mau xanh)
	So ve lay tu thao tac click vao cua nguoi dat ve
*/

bool datVe(char *CMND, int soVe, ChuyenBay *cb, DanhSachHanhKhach &dsHK, DanhSachChuyenBay &dsCB, char* strErr) {
	HanhKhach* hk = timKiemHanhKhach(dsHK, CMND);
	if(hk == NULL) {
		return themVeVaoChuyenBay(CMND, soVe, cb, strErr);
	}
	strcpy(strErr, "");
	// Ton tai CMND trong danh sach ve cua chuyen bay dang chon
	if(ktTonTaiCMNDTrongDSVe(cb->dsVe, CMND)) {
		strcpy(strErr, "MOI HANH KHACH CHI DUOC DAT 1 VE!");
		return false;
	} 
	/*
		* Neu khong ton tai CMND trong danh sach ve cua chuyen bay dang chon
	 	* Ta xet trong danh sach ve cua tung may bay trong danh sach may bay
	 		* Neu CMND nay ton tai trong danh sach ve cua mot chuyen bay nao do trong danh sach may bay
	 			* Lay ngay gio khoi hanh cua chuyen bay dang chon va ngay gio khoi hanh cua chuyen bay trong danh
	 			sach may bay so sanh
	 				* Neu ma ngay gio khoi hanh cua 2 chuyen bay trung nhau thi khong cho dat ve
	*/
	else {
		
		char maCBTrung[MAXMACB];
		if(!ktCBTrungGioVoiCBKhac(dsCB,CMND, *cb, maCBTrung)) {
			return themVeVaoChuyenBay(CMND, soVe, cb, strErr);
		}
		
		strcat(strErr, "TRUNG GIO KHOI HANH VOI CHUYEN BAY ");
		strcat(strErr, maCBTrung);
		return false;
	}
}

