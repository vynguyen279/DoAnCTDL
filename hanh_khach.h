#pragma once
#include "configure.h"

struct HanhKhach{
	char CMND[MAXCMND];
	char ho[MAXHO];
	char ten[MAXTEN];
	// 1 la nam, 0 la nu
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


