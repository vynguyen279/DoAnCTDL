#pragma once
#include "hanh_khach.h"
#include "hash_table.h"

typedef HanhKhach *HashTableCustomer[MAXHASHCUSTOMER];

void initHashTableCustomer(HashTableCustomer &table) {
	for(int i = 0;  i < MAXHASHCUSTOMER; i++) table[i] = NULL;
}

void insertHashTableCustomer(HashTableCustomer &table, HanhKhach* hk) {
	int index = hash(hk->CMND);
	int x = 0;
	while(table[index] != NULL)
		index = (index + probing(x++)) % MAXHASHCUSTOMER;
	table[index] = hk;
}

int searchItemCustomer(char* CMND, HashTableCustomer &table) {
	int index = hash(CMND);
	int x = 0;
	while(table[index] != NULL && strcmp(table[index]->CMND, CMND) != 0) 
		index = (index + probing(x++)) % MAXHASHCUSTOMER;
	return index;
}

void printHashTableCustomer(DanhSachVe &dsVe, HashTableCustomer &table) {
	for(int i = 0; i < dsVe.n; i++) {
		std::cout << "SO VE: " << dsVe.ve[i].soVe << std::endl;
		table[searchItemCustomer(dsVe.ve[i].CMND, table)]->toString();
		std::cout << std::endl;
	}
	
}

