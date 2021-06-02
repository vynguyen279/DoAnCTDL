#pragma once
#include <cstring>
#include "configure.h"

struct HanhKhach{
	char CMND[MAXCMND];
	char ho[MAXHO];
	char ten[MAXTEN];
	bool phai;
	// Ham test
	void toString() {
		std::cout << "CMND: " << CMND << std::endl;
		std::cout << "Ho: " << ho << " - Ten: " << ten << std::endl;
		std::cout << "Phai: " << phai << std::endl;
	}
};

struct NodeHanhKhach {
	HanhKhach hanhKhach;
	NodeHanhKhach *trai = NULL;
	NodeHanhKhach *phai = NULL;
};

// root
typedef NodeHanhKhach* DanhSachHanhKhach;

HanhKhach newHanhKhach(char* CMND, char* ho, char* ten, bool phai) {
	HanhKhach newHanhKhach;
	strcpy(newHanhKhach.CMND, CMND);
	strcpy(newHanhKhach.ho, ho);
	strcpy(newHanhKhach.ten, ten);
	newHanhKhach.phai = phai;
	return newHanhKhach;
}

NodeHanhKhach* newNodeHanhKhach(HanhKhach hanhKhach) {
	NodeHanhKhach* newNodeHanhKhach = new NodeHanhKhach;
	newNodeHanhKhach->hanhKhach = hanhKhach;
	return newNodeHanhKhach;
}

void xuatDSHK(DanhSachHanhKhach dsHK) {
	if(dsHK != NULL) {
		xuatDSHK(dsHK->trai);
		dsHK->hanhKhach.toString();
		xuatDSHK(dsHK->phai);
	}	
}

void themHanhKhach(DanhSachHanhKhach &dsHK, HanhKhach hanhKhach) {
	if(dsHK == NULL) {
		dsHK = newNodeHanhKhach(hanhKhach);
		return;
	} 
	NodeHanhKhach* nodeChay = dsHK;
	NodeHanhKhach* nodeTruoc = NULL;
	while(nodeChay != NULL) {
		nodeTruoc = nodeChay;
		if(strcmp(nodeChay->hanhKhach.CMND, hanhKhach.CMND) == 1) 
			nodeChay = nodeChay->trai;
		else if (strcmp(nodeChay->hanhKhach.CMND, hanhKhach.CMND) == -1)
			nodeChay = nodeChay->phai;
	}
	if(strcmp(nodeTruoc->hanhKhach.CMND, hanhKhach.CMND) == 1)
		nodeTruoc->trai = newNodeHanhKhach(hanhKhach);
	else if(strcmp(nodeTruoc->hanhKhach.CMND, hanhKhach.CMND) == -1)
		nodeTruoc->phai = newNodeHanhKhach(hanhKhach);
}

void xoaGoc(DanhSachHanhKhach &dsHK) {
	if(dsHK == NULL) return;
	
	NodeHanhKhach* nodeXoa = NULL;
	// Xoa node root khong co con
	if(dsHK->trai == NULL && dsHK->phai == NULL) {
		delete dsHK;
		dsHK = NULL;
	} 
	// Xoa node root co 1 con
	else if(dsHK->trai == NULL || dsHK->phai == NULL){
		nodeXoa = dsHK;
		if(dsHK->trai == NULL) dsHK = dsHK->phai;
		else if(dsHK->phai == NULL) dsHK = dsHK->trai;
		delete nodeXoa;
	} 
	// Xoa node root co 2 con
	else if(dsHK->trai != NULL && dsHK->phai != NULL) {
		NodeHanhKhach* nodeTruoc = dsHK;
		NodeHanhKhach* nodeXoa = dsHK->phai;
		// Tim node trai nhat o ben phai
		while(nodeXoa->trai != NULL) {
			nodeTruoc = nodeXoa;
			nodeXoa = nodeXoa->trai;
		}
		// Doi gia tri giua node trai nhat cua nhanh ben phai
		// voi gia tri cua node root
		dsHK->hanhKhach = nodeXoa->hanhKhach;
		// Kiem tra co node trai nhat ben phai hay khong?
		// Truong hop khong co node trai nhat ben phai (chi co node phai)
		if(nodeTruoc == dsHK) {
			// Node phai khong co con phai
			if(nodeXoa->phai == NULL) nodeTruoc->phai = NULL;
			// Node phai co con phai
			else if(nodeXoa->phai != NULL) nodeTruoc->phai = nodeXoa->phai;
		} 
		// Truong hop co node trai nhat ben phai
		else if(nodeTruoc != dsHK) {
			// Node trai nhat khong co con phai
			if(nodeXoa->phai == NULL) nodeTruoc->trai = NULL;
			// Node trai nhat co con phai
			else if(nodeXoa->phai != NULL) nodeTruoc->trai = nodeXoa->phai;
		}
		delete nodeXoa;
	}
}

void xoaNodeKhongPhaiGoc(DanhSachHanhKhach &dsHK, char* CMND) {
	
		NodeHanhKhach* nodeChay = dsHK;
		NodeHanhKhach* nodeTruoc = NULL;
		
		// Tim node co so CMND can xoa
		while(nodeChay != NULL && strcmp(nodeChay->hanhKhach.CMND, CMND) != 0) {
			nodeTruoc = nodeChay;
			if(strcmp(nodeChay->hanhKhach.CMND, CMND) == 1) nodeChay = nodeChay->trai;
			else if(strcmp(nodeChay->hanhKhach.CMND, CMND) == -1) nodeChay = nodeChay->phai;
		}
		
		if(nodeChay == NULL) {
			std::cout << "Khong tim thay hanh khach can xoa!\n";
			return;
		}
		
		// Xoa node khong co con
		if(nodeChay->trai == NULL && nodeChay->phai == NULL) {
			// Kiem tra xoa node trai hay node phai cua node truoc
			// Xoa node trai cua node truoc
			if(strcmp(nodeTruoc->hanhKhach.CMND, nodeChay->hanhKhach.CMND) == 1) {
				nodeTruoc->trai = NULL;
			}
			// Xoa node phai cua node truoc
			else if(strcmp(nodeTruoc->hanhKhach.CMND, nodeChay->hanhKhach.CMND) == -1) {
				nodeTruoc->phai = NULL;
			}
			delete nodeChay;
		} 
		// Xoa node co 1 con trai hoac 1 con phai
		else if(nodeChay->trai == NULL || nodeChay->phai == NULL) {
			// Xoa 1 con trai cua node truoc
			if(nodeChay->trai != NULL) {
				// Kiem tra xoa node trai hay node phai cua node truoc
				// Xoa node ben trai node truoc
				if(strcmp(nodeTruoc->hanhKhach.CMND, nodeChay->hanhKhach.CMND) == 1) {
					nodeTruoc->trai = nodeChay->trai;
				}
				// Xoa node ben phai node truoc 
				else if(strcmp(nodeTruoc->hanhKhach.CMND, nodeChay->hanhKhach.CMND) == -1) {
					nodeTruoc->phai = nodeChay->trai;
				}
			}
			// Xoa 1 con phai cua node truoc
			else if(nodeChay->phai != NULL) {
				// Kiem tra xoa node trai hay node phai cua node truoc
				// Xoa node ben trai cua node truoc
				if(strcmp(nodeTruoc->hanhKhach.CMND, nodeChay->hanhKhach.CMND) == 1) {
					nodeTruoc->trai = nodeChay->phai;
				} 
				// Xoa node ben phai cua node truoc
				else if(strcmp(nodeTruoc->hanhKhach.CMND, nodeChay->hanhKhach.CMND) == -1) {
					nodeTruoc->phai = nodeChay->phai;
				}
			}
			delete nodeChay;
		} 
		// Xoa node co 2 con
		else if(nodeChay->trai != NULL && nodeChay->phai != NULL) {
			NodeHanhKhach* nodeTruocXoa = nodeChay;
			NodeHanhKhach* nodeCanXoa = nodeChay->phai;
			// Tim node trai nhat cua nhanh phai
			while(nodeCanXoa->trai != NULL) {
				nodeTruocXoa = nodeCanXoa;
				nodeCanXoa = nodeCanXoa->trai;
			}
			// Doi gia tri cua node trai nhat ben nhanh phai
			// voi gia tri cua nodeChay (luu dia chi node can xoa)
			nodeChay->hanhKhach = nodeCanXoa->hanhKhach;
			// Neu node phai cua nodeChay (node can xoa) khong co node trai
			if(nodeChay == nodeTruocXoa) {
				// Node phai cua nodeChay khong co node phai
				if(nodeCanXoa->phai == NULL) nodeTruocXoa->phai = NULL;
				// Node phai cua nodeChay co node phai
				else if(nodeCanXoa->phai != NULL) nodeTruocXoa->phai = nodeCanXoa->phai;
			} 
			// Node phai cua nodeChay(node can xoa) co node trai nhat
			else if(nodeChay != nodeTruocXoa) {
				// Node trai nhat khong co node phai
				if(nodeCanXoa->phai == NULL) nodeTruocXoa->trai = NULL;
				// Node trai nhat co node phai
				else if(nodeCanXoa->phai != NULL) nodeTruocXoa->trai = nodeCanXoa->phai;
			}
			delete nodeCanXoa;
		}
}

void xoaHanhKhach(DanhSachHanhKhach &dsHK, char* CMND) {
		
	if(dsHK == NULL) {
		std::cout << "DANH SACH RONG!\n";
		return;
	}
	if(strcmp(dsHK->hanhKhach.CMND, CMND) == 0) {
		xoaGoc(dsHK);
	} else {
		xoaNodeKhongPhaiGoc(dsHK, CMND); 
	}
}

HanhKhach* timKiemHanhKhach(DanhSachHanhKhach &dsHK, char* CMND) {
	NodeHanhKhach* nodeChay = dsHK;
	if(nodeChay == NULL) {
		std::cout << "DANH SACH HANH KHACH RONG!\n";
		return NULL;
	}

	while(nodeChay != NULL && strcmp(nodeChay->hanhKhach.CMND, CMND) != 0) {
		if(strcmp(nodeChay->hanhKhach.CMND, CMND) == 1)
			nodeChay = nodeChay->trai;
		else if(strcmp(nodeChay->hanhKhach.CMND, CMND) == -1)
			nodeChay = nodeChay->phai;
	}
	if(nodeChay != NULL) {
		return &(nodeChay->hanhKhach);
	}
	std::cout << "KHONG TON TAI HANH KHACH VOI SO CMND: " << CMND << std::endl;
	return NULL;
}

void capNhapHanhKhach(HanhKhach *hkCapNhat) {
	char ho[MAXHO];
	char ten[MAXTEN];
	bool phai;
	std::cout << "HO: "; gets(ho);
	std::cout << "TEN: "; gets(ten);
	fflush(stdin);
	std::cout << "PHAI: "; std::cin >> phai;
	strcpy(hkCapNhat->ho, ho);
	strcpy(hkCapNhat->ten, ten);
	hkCapNhat->phai = phai;
}

void clearDSHK(DanhSachHanhKhach &dsHK) {
	NodeHanhKhach *nodeChay = dsHK;
	while(nodeChay != NULL) {
		xoaGoc(dsHK);
		nodeChay = dsHK;
	}
}
/////////////////////////////////////////////////////////////

struct HanhKhachThongKe{
	HanhKhach hk;
	int soVe;
};

struct ListHanhKhachThongKe{
	HanhKhachThongKe *hanhKhachTK;
	int soLuong = 0;
};

HanhKhachThongKe newHanhKhachThongKe(HanhKhach hk, int soVe) {
	HanhKhachThongKe hkTK;
	hkTK.hk = hk;
	hkTK.soVe = soVe;
	return hkTK;
}

void themVaoListHKTK(HanhKhachThongKe hktk, ListHanhKhachThongKe &list) {
	list.hanhKhachTK[list.soLuong++] = hktk;
}

void xuatListHKTK(ListHanhKhachThongKe &list) {
	for(int i = 0; i < list.soLuong; i++) {
		std::cout << "SO VE: " << list.hanhKhachTK[i].soVe << std::endl;
		list.hanhKhachTK[i].hk.toString();
	}
}

void clearListHKTK(ListHanhKhachThongKe &list) {
	delete[] list.hanhKhachTK;
}
