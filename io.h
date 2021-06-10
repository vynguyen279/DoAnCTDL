#pragma once

#include <fstream>
#include <cstring>
#include "xu_ly_may_bay.h"
#include "xu_ly_chuyen_bay.h"
#include "hash_table_hanh_khach.h"


/*************************************************************************************
 *					          	    	Xu ly danh sach may bay									               *
 *************************************************************************************/

void luuDSMayBay(DanhSachMayBay &dsMB) {
	std::fstream f("danh_sach_may_bay.txt", std::ios::out | std::ios::binary);
	if(f.fail()) {
		std::cout << "LOI FILE!!\n";
		return;
	}

	for(int i = 0; i < dsMB.n; i++)
		f.write((char*)(dsMB.mayBay[i]), sizeof(MayBay));
	f.close();
}

void layDSMayBay(DanhSachMayBay &dsMB) {
	std::fstream f("danh_sach_may_bay.txt", std::ios::in | std::ios::binary);
	if(f.fail()) {
		std::cout << "LOI FILE!!\n";
		return;
	}
	MayBay mb;
	while(f.read((char*)&mb, sizeof(MayBay)))
		themMayBay(mb, dsMB);
	f.close();
}

/*************************************************************************************
 *																Xu ly danh sach ve																 *
 *************************************************************************************/


void luuDSVe(DanhSachVe &dsVe, std::fstream &f) {
	f.write((char*) &(dsVe.soLuongVe), sizeof(int));
	f.write((char*) &(dsVe.n), sizeof(int));
	for(int i = 0; i < dsVe.n; i++)
		f.write((char*) &(dsVe.ve[i]), sizeof(Ve));
}

void layDSVe(DanhSachVe &dsVe, std::fstream &f) {
	f.read((char*) &(dsVe.soLuongVe), sizeof(int));
	f.read((char*) &(dsVe.n), sizeof(int));
	dsVe.ve = new Ve[dsVe.soLuongVe];
	for(int i = 0; i < dsVe.n; i++)
		f.read((char*) &(dsVe.ve[i]), sizeof(Ve));
}


/*************************************************************************************
 *														Xu ly danh sach chuyen bay														 *
 *************************************************************************************/


void luuDSChuyenBay(DanhSachChuyenBay &dsCB) {
	std::fstream f;
	f.open("danh_sach_chuyen_bay.txt", std::ios::out | std::ios::binary );
	if(f.fail()) {
		std::cout << "LOI FILE!\n"; return;
	}
	NodeChuyenBay *nodeChay = dsCB;
	int soVe;
	for(; nodeChay != NULL; nodeChay = nodeChay->next) {
		f.write((char*) &(nodeChay->chuyenBay), sizeof(ChuyenBay));
		luuDSVe(nodeChay->chuyenBay.dsVe, f);
	}
	f.close();
}

void layDSChuyenBay(DanhSachChuyenBay &dsCB) {
	std::fstream f;
	f.open("danh_sach_chuyen_bay.txt", std::ios::in | std::ios::binary);
	if(f.fail()) {
		std::cout << "LOI FILE!\n"; return;
	}

	ChuyenBay cb;
	while(f.read((char*) &cb, sizeof(ChuyenBay))) {
		layDSVe(cb.dsVe, f);
		capNhatTrangThaiHoanTat(cb);
		themChuyenBay(newNodeChuyenBay(cb), dsCB);
	}
	f.close();
}

/*************************************************************************************
 *															Xu ly danh sach hanh khach													 *
 *************************************************************************************/

void TRY(DanhSachHanhKhach dsHK, std::fstream &f) {
	if(dsHK != NULL) {
		TRY(dsHK->trai, f);
		f.write((char*)&(dsHK->hanhKhach), sizeof(HanhKhach));
		TRY(dsHK->phai, f);
	}
}

void luuDSHK(DanhSachHanhKhach &dsHK) {
	std::fstream f;
	f.open("danh_sach_hanh_khach.txt", std::ios::out | std::ios::binary);
	if(f.fail()) {
		std::cout << "LOI FILE!\n"; return;
	}
	TRY(dsHK, f);
	f.close();
}

void layDSHK(DanhSachHanhKhach &dsHK, HashTableCustomer &table) {
	std::fstream f;
	f.open("danh_sach_hanh_khach.txt", std::ios::in | std::ios::binary);
	if(f.fail()) {
		std::cout << "LOI FILE!\n"; return;
	}
	HanhKhach hk;
	while(f.read((char*)&hk, sizeof(HanhKhach)))
		themHanhKhach(dsHK, newNodeHanhKhach(hk), table);
	f.close();	
}
