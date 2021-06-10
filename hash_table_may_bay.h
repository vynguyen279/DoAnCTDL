#pragma once
#include "configure.h"
#include "chuyen_bay.h"
#include "hash_table.h"

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

void printHashTable(HashTable table, DanhSachMayBay &dsMB) {
	for(int i = 0; i < dsMB.n; i++)
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

bool sortSoHieu1(Item item, Item pivot) {
	return (strcmp(item.soHieu, pivot.soHieu) == -1 || item.soLanTH > pivot.soLanTH);
}

bool sortSoHieu2(Item item, Item pivot) {
	return (strcmp(item.soHieu, pivot.soHieu) == 1 || item.soLanTH < pivot.soLanTH);
}

bool sortSoLanTHCB1(Item item, Item pivot) {
	return item.soLanTH > pivot.soLanTH;
}

bool sortSoLanTHCB2(Item item, Item pivot) {
	return item.soLanTH < pivot.soLanTH;
}

void my_sort(HashTable &table, int left, int right, bool (*condiFunct1) (Item, Item), bool (*condiFunct2) (Item, Item)) {
	Item pivot = table[(left + right)/2];
	Item itemTmp;
	int i = left;
	int j = right;
	while( i <= j ) {
		while(condiFunct1(table[i], pivot)) i++;
		while(condiFunct2(table[j], pivot)) j--;
		if(i <= j) {
			itemTmp = table[i];
			table[i] = table[j];
			table[j] = itemTmp;
			i++; j--;
		}
	}
	if(left < j) my_sort(table, left, j, condiFunct1, condiFunct2);
	if(i < right) my_sort(table, i, right, condiFunct1, condiFunct2);
}

void thongKeMBThucHienCB(HashTable &table, DanhSachChuyenBay &dsCB, DanhSachMayBay &dsMB) {
	dsMBToHashTable(dsMB, table);
	NodeChuyenBay* node = dsCB;
	for(; node != NULL; node = node->next)
		if(node->chuyenBay.trangThai == HOANTAT)
			table[searchItem(node->chuyenBay.soHieuMayBay, table)].soLanTH++;
	my_sort(table, 0, MAXHASH - 1, sortSoLanTHCB1, sortSoLanTHCB2);
	my_sort(table, 0, dsMB.n - 1, sortSoHieu1, sortSoHieu2);
}

