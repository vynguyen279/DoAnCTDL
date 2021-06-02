#include <iostream>
#include <cstring>
#include <stdlib.h>
#include "xu_ly_may_bay.h"
#include "xu_ly_chuyen_bay.h"
#include "dat_ve.h"
#include "io.h"

/*
Progblem

 Neu 2 chuyen bay co thoi gian khoi hanh khac nhau
 Mot hanh khach deu dat ve tren 2 chuyen bay do
 Thi cap nhat 1 trong 2 chuyen bay, chuyen bay nay khong the cung gio
 khoi hanh voi chuyen bay kia 

*/

using namespace std;

int main() {
	
	DanhSachMayBay dsMB;
	DanhSachChuyenBay dsCB = NULL;
	DanhSachHanhKhach dsHK = NULL;
	DanhSachTam dsTmp;
	NgayThangNam dt = newNgayThangNam(12,6,2021,3,3);
	
	layDSMayBay(dsMB);
	layDSChuyenBay(dsCB);
	layDSHK(dsHK);

//	 themMayBayHopLe(newMayBay("MB001", "MAY BAY DAN DUNG", 3), dsMB);
//	 themMayBayHopLe(newMayBay("MB002", "MAY BAY DAN DUNG", 3), dsMB);
//	 themMayBayHopLe(newMayBay("MB003", "MAY BAY DAN DUNG", 3), dsMB);
//	 themMayBayHopLe(newMayBay("MB004", "MAY BAY DAN DUNG", 3), dsMB);
//	 themMayBayHopLe(newMayBay("MB005", "MAY BAY DAN DUNG", 3), dsMB);
//	 themMayBayHopLe(newMayBay("MB006", "MAY BAY DAN DUNG", 3), dsMB);
//	 themMayBayHopLe(newMayBay("MB007", "MAY BAY DAN DUNG", 3), dsMB);
//	 themMayBayHopLe(newMayBay("MB008", "MAY BAY DAN DUNG", 3), dsMB);
//	 themMayBayHopLe(newMayBay("MB009", "MAY BAY DAN DUNG", 3), dsMB);

//
//	 themChuyenBayHopLe(newNodeChuyenBay(newChuyenBay("CB001", newNgayThangNam(1,6,2021, 3,3), "DA NANG", "MB001")), dsCB, dsMB);
//	 themChuyenBayHopLe(newNodeChuyenBay(newChuyenBay("CB002", newNgayThangNam(21,6,2021, 3,3), "TP HCM", "MB002")), dsCB, dsMB);
//	 themChuyenBayHopLe(newNodeChuyenBay(newChuyenBay("CB003", newNgayThangNam(19,7,2021, 3,3), "DA NANG", "MB003")), dsCB, dsMB);
//	 themChuyenBayHopLe(newNodeChuyenBay(newChuyenBay("CB004", newNgayThangNam(22,6,2021, 3,3), "DA NANG", "MB004")), dsCB, dsMB);
//	 themChuyenBayHopLe(newNodeChuyenBay(newChuyenBay("CB005", newNgayThangNam(10,7,2021, 3,3), "TP HCM", "MB005")), dsCB, dsMB);
//	 themChuyenBayHopLe(newNodeChuyenBay(newChuyenBay("CB006", newNgayThangNam(5,6,2021, 3,3), "DA NANG", "MB006")), dsCB, dsMB);
//	 themChuyenBayHopLe(newNodeChuyenBay(newChuyenBay("CB007", newNgayThangNam(30,7,2021, 3,3), "TAN SON NHAT", "MB007")), dsCB, dsMB);
//	 themChuyenBayHopLe(newNodeChuyenBay(newChuyenBay("CB008", newNgayThangNam(27,6,2021, 3,3), "DA NANG", "MB008")), dsCB, dsMB);
//	 themChuyenBayHopLe(newNodeChuyenBay(newChuyenBay("CB009", newNgayThangNam(14,7,2021, 3,3), "TAN SON NHAT", "MB001")), dsCB, dsMB);
//	 themChuyenBayHopLe(newNodeChuyenBay(newChuyenBay("CB010", newNgayThangNam(12,6,2021, 3,3), "DA NANG", "MB002")), dsCB, dsMB);
//	 themChuyenBayHopLe(newNodeChuyenBay(newChuyenBay("CB011", newNgayThangNam(15,7,2021, 3,3), "DA NANG", "MB003")), dsCB, dsMB);
//	 themChuyenBayHopLe(newNodeChuyenBay(newChuyenBay("CB012", newNgayThangNam(3,6,2021, 3,3), "TP HCM", "MB004")), dsCB, dsMB);
//	 themChuyenBayHopLe(newNodeChuyenBay(newChuyenBay("CB013", newNgayThangNam(4,7,2021, 3,3), "VUNG TAU", "MB005")), dsCB, dsMB);
//	 themChuyenBayHopLe(newNodeChuyenBay(newChuyenBay("CB014", newNgayThangNam(6,6,2021, 3,3), "TAN SON NHAT", "MB006")), dsCB, dsMB);
//	 themChuyenBayHopLe(newNodeChuyenBay(newChuyenBay("CB015", newNgayThangNam(31,7,2021, 3,3), "NOI BAI", "MB007")), dsCB, dsMB);
//	 themChuyenBayHopLe(newNodeChuyenBay(newChuyenBay("CB017", newNgayThangNam(25,6,2021, 18,0), "TP HCM", "MB008")), dsCB, dsMB);
	 dsTmp = dsNode2DsTmpConVe(dsCB);

//	datVe("123456789", 1, dsTmp.cb[0],dsHK, dsCB);
//	datVe("1234567891", 2, dsTmp.cb[0],dsHK, dsCB);
//	datVe("123456789", 1, dsTmp.cb[1],dsHK, dsCB);
//	char strErr[255];
//	if(!capNhatNgayThangNam(dsCB, dsTmp.cb[1],dt,strErr)) {
//		cout << strErr << endl;
//	}
//	xuatDSHKDuaVaoMaCB(dsCB, dsHK, "CB002");
//	capNhatDanhSachVe(dsTmp.cb[0], "126", 1);
//	themChuyenBayHopLe(newNodeChuyenBay(newChuyenBay("CB003", newNgayThangNam(23,4,2021, 18,54), "DA NANG", "MB001")), dsCB, dsMB);
//	datVe("128", dsHK, 1, dsTmp, 2, dsCB);
	
//	xuatDSMB(dsMB);
//	 xuatDSCB(dsCB, dsMB);
	xuatDSTmp(dsTmp);
	xuatDSHK(dsHK);
//	xuatDSHKDuaVaoMaCB(dsCB, dsHK, "CB001");
	// xuatDSCBConVeKhoiHanhTrongNgayDenNoi("DA NANG", dt, dsCB);
	ListHanhKhachThongKe list;
	xuatDSHKDuaVaoMaCB(dsCB, dsHK, "CB001", list);
	xuatListHKTK(list);
	
	luuDSMayBay(dsMB);
	luuDSChuyenBay(dsCB);
	luuDSHK(dsHK);
	
	clearDSHK(dsHK);
	clearDSCB(dsCB);
	clearDSMB(dsMB);
	clearDSTmp(dsTmp);
	
	return 0;
}
