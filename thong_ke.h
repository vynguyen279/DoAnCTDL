#pragma once

#include <cstring>
#include "chuyen_bay.h"

struct NodeThongKe{
	char* soHieuMB[15];
	int soLanTH = 1;
};

struct ListThongKe{
	NodeThongKe node[300];
	int soLuong = 0;
};

void themNodeTKVaoList(ListThongKe &list, char* soHieuMB) {
	strcpy(list.node[list.soLuong++].soHieuMB, soHieuMB);
}

void thongKeMayBayThucHienNhieuChuyenBayNhat(DanhSachChuyenBay &dsCB, ListThongKe &listTK) {
	if(dsCB == NULL) {
		std::cout << "DANH SACH RONG!\n";
		return;
	}
	NodeChuyenBay* nodeChay = dsCB;
	bool tonTai;
	for(; nodeChay != NULL; nodeChay = nodeChay->next) {
		if(nodeChay->chuyenBay.trangThai == 3) {
			tonTai = false;
			for(int i = 0; i < listTK.soLuong; i++) {
			 if(strcmp(nodeChay->chuyenBay.soHieuMayBay, listTK.node[i].soHieuMB)) {
			 	tonTai = true;
			 	listTK.node[i].soLanTH++;
			 }
			}
			if(!tonTai) themNodeVaoTKList(listTK, nodeChay->chuyenBay.soHieuMayBay);
		}
	}
}

void rSapXepSoLanTHChuyenBayCuaMB(ListThongKe &listTK,int r, int l) {
	NodeThongKe node = listTK[(r + l)/2];
	int i = r;
	int j = l;
	while(j <= i) {
		while(listTK[i].node.soLanTH < node.soLanTH) i--;
		while(listTK[j].node.soLanTH > node.soLanTH) j++;
		if(j <= i) {
			NodeThongKe nodeTmp = listTK[i];
			listTK[i] = listTK[j];
			listTK[j] = nodeTmp;
			j++;i--;
		}
	}
	if(l < i) rSapXepSoLanTHChuyenBayCuaMB(listTK, i, l);
	if(j < r) rSapXepSoLanTHChuyenBayCuaMB(listTK, r, j);
}
