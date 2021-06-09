#pragma once

int probing(int x) {
	return PRIME * x;
}

int hash(char* s)
{
   int h = FIRSTH;
   while (*s) {
     h = (h * A) ^ (s[0] * B);
     s++;
   }
   h %= MAXHASH;
   if(h < 0) return -1 * h;
   return h;
}
<<<<<<< HEAD
=======

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
	while(stricmp(table[index].soHieu, soHieu) != 0)
		index = (index + probing(x++)) % MAXHASH;
	return index;
}

void quick_sort_so_hieu(HashTable table, int left, int right) {
	Item item = table[(left + right)/2];
	Item itemTmp;
	int i = left;
	int j = right;
	while(i <= j) {
		while(stricmp(table[i].soHieu, item.soHieu) == -1  || stricmp(table[i].soHieu, "") == 0) i++;
		while(stricmp(table[j].soHieu, item.soHieu) == 1 || stricmp(table[j].soHieu, "") == 0) j--;
		if(i <= j) {
			itemTmp = table[i];
			table[i] = table[j];
			table[j] = itemTmp;
			i++; j--;
		} 
	}
	while(i <= j) {
		if(left < j) quick_sort_so_hieu(table, left, j);
		if(right > i) quick_sort_so_hieu(table, i, right);
	}
}

void quick_sort(HashTable table, int left, int right) {
	Item item = table[(left + right)/2];
	Item itemTmp;
	int i = left;
	int j = right;
	while(i <= j) {
		while(table[i].soLanTH > item.soLanTH) i++;
		while(table[j].soLanTH < item.soLanTH) j--;
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
	initHashTable(table);
	dsMBToHashTable(dsMB, table);
	NodeChuyenBay* node = dsCB;
	for(; node != NULL; node = node->next) {
		if(node->chuyenBay.trangThai == 3) {
			table[searchItem(node->chuyenBay.soHieuMayBay, table)].soLanTH++;
		}
	}
	quick_sort(table, 0, MAXHASH - 1);
}
>>>>>>> abd78d59b6c4551c38855fe5079385bb1708d456
