#pragma once
#include "configure.h"
#include "chuyen_bay.h"
#include "hash_table.h"

#include <stdlib.h>
#include <ctime>

struct Item {
	char soHieu[MAXSOHIEU];
	int soLanTH = -1;
};

typedef Item HashTable[MAXHASH];

Item newItem(char *soHieu) {
	Item item;
	strcpy(item.soHieu, soHieu);
	item.soLanTH = 0;
	return item;
}

void insertHashTable(HashTable table, char* soHieu) {
	int index = hash(soHieu);
	int x = 0;
	while(table[index].soLanTH != -1)
		index = (index + probing(x++)) % MAXHASH;
	table[index] = newItem(soHieu);
}

void printHashTable(HashTable table) {
	for(int i = 0; i < MAXHASH; i++)
		if(table[i].soLanTH != -1)
			std::cout << "So hieu: " << table[i].soHieu << " - index: " << i << " - so lan th: " << table[i].soLanTH << std::endl;
}

void dsMBToHashTable(DanhSachMayBay &dsMB, HashTable table) {
	for(int i = 0; i < dsMB.n; i++)
		insertHashTable(table, dsMB.mayBay[i]->soHieuMayBay);
}

int searchItem(char* soHieu, HashTable table) {
	int index = hash(soHieu);
	int x = 0;
	while(strcmp(table[index].soHieu, soHieu) != 0)
		index = (index + probing(x++)) % MAXHASH;
	return index;
}

void quick_sort_so_hieu(HashTable table, int left, int right) {
	Item pivot = table[(left + right)/2];
	Item itemTmp;
	int i = left;
	int j = right;
	while(i <= j) {
		while(strcmp(table[i].soHieu, pivot.soHieu) == -1 || table[i].soLanTH > pivot.soLanTH) i++;
		while(strcmp(table[j].soHieu, pivot.soHieu) == 1 || table[j].soLanTH < pivot.soLanTH) j--;
		if(i <= j) {
			itemTmp = table[i];
			table[i] = table[j];
			table[j] = itemTmp;
			i++; j--;
		}
	}
	if(left < j) quick_sort_so_hieu(table, left, j);
	if(right > i) quick_sort_so_hieu(table, i, right);
}

void quick_sort(HashTable table, int left, int right) {
	int pivot = table[(left + right)/2].soLanTH;
	Item itemTmp;
	int i = left;
	int j = right;
	while(i <= j) {
		while(table[i].soLanTH > pivot) i++;
		while(table[j].soLanTH < pivot) j--;
		if(i <= j) {
			itemTmp = table[i];
			table[i] = table[j];
			table[j] = itemTmp;
			i++; j--;
		}
	}
	if(left < j) quick_sort(table, left, j);
	if(right > i) quick_sort(table, i, right);
}

void thongKeMBThucHienCB(HashTable &table, DanhSachChuyenBay &dsCB, DanhSachMayBay &dsMB) {
	dsMBToHashTable(dsMB, table);
	NodeChuyenBay* node = dsCB;
	srand(time(NULL));
	for(; node != NULL; node = node->next)
		if(node->chuyenBay.trangThai == 3)
			table[searchItem(node->chuyenBay.soHieuMayBay, table)].soLanTH++;
	quick_sort(table, 0, MAXHASH - 1);
	quick_sort_so_hieu(table, 0, dsMB.n - 1);
}

