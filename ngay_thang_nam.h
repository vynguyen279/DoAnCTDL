#pragma once
#include <ctime>
#include <stdio.h>
#include "configure.h"

struct NgayThangNam{
	int ngay, thang, nam, gio, phut;
	// Ham test
	void toString() {
		printf("%d%c%d%c%d%c%d%c%d",ngay,'/',thang,'/',nam,' ', gio, ':', phut);
	}
};

NgayThangNam newNgayThangNam(int ngay, int thang, int nam, int gio, int phut) {
	NgayThangNam dt;
	dt.nam = nam;
	dt.thang = thang;
	dt.ngay = ngay;
	dt.gio = gio;
	dt.phut = phut;
	return dt;
}

NgayThangNam layNgayGioHeThong() {
	time_t now = time(0);
	tm* gmtm = gmtime(&now);
	gmtm->tm_hour += 7;
	gmtm->tm_mon += 1;
	gmtm->tm_year += 1900;
	NgayThangNam dt = newNgayThangNam(gmtm->tm_mday, gmtm->tm_mon, gmtm->tm_year, gmtm->tm_hour, gmtm->tm_min);
	return dt;
}

NgayThangNam newNgayThangNam(int ngay, int thang, int nam) {
	NgayThangNam dt = layNgayGioHeThong();
	dt.ngay = ngay;
	dt.thang = thang;
	dt.nam = nam;
	return dt;
}

bool ktDt2LonHonDt(NgayThangNam dt, NgayThangNam dt2) {
	if(dt2.nam > dt.nam) {
		return true;
	} else if(dt2.nam == dt.nam) {
		if(dt2.thang > dt.thang) {
			return true;
		} else if(dt2.thang == dt.thang) {
			if(dt2.ngay > dt.ngay) {
				return true;
			} else if(dt2.ngay == dt.ngay) {
				if(dt2.gio > dt.gio) {
					return true;
				} else if(dt2.gio == dt.gio) {
					if(dt2.phut >= dt.phut) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool ktTuongLai(NgayThangNam dt) {
	NgayThangNam dtNow = layNgayGioHeThong();
	if(dtNow.nam > dt.nam) {
		return false;
	} else if(dtNow.nam == dt.nam) {
		if(dtNow.thang > dt.thang) {
			return false;
		} else if(dtNow.thang == dt.thang) {
			if(dtNow.ngay > dt.ngay) {
				return false;
			} else if(dtNow.ngay == dt.ngay) {
				if(dtNow.gio > dt.gio)
					return false;
				else if(dtNow.gio == dt.gio) {
					if(dtNow.phut > dt.phut) {
						return false;
					}
				}
			}
		}
	} 
	return true;
} 
/*
	Ham tra ve true khi dt2 lon hon hoac bang dt DIST h
*/
bool ktDt2LonHonDISTGioDt(NgayThangNam dt, NgayThangNam dt2) {
	if(dt2.nam - dt.nam > 0) {
		return true;
	} else if(dt2.nam == dt.nam){
		if(dt2.thang - dt.thang > 0) {
			return true;
		} else if(dt2.thang == dt.thang){
			if((dt2.ngay - dt.ngay) * 24 + dt2.gio - dt.gio >= DIST) {
				return true;
			}		
		}
	}
	return false;
}

/*
	Mot chuyen bay hoan tat khi dtNow lon hon hoac bang dt DIST h
*/

bool ktHoanTat(NgayThangNam dt) {
	NgayThangNam dtNow = layNgayGioHeThong();
	if(dtNow.nam - dt.nam > 0) {
		return true;
	} else if(dtNow.nam == dt.nam){
		if(dtNow.thang - dt.thang > 0) {
			return true;
		} else if(dtNow.thang == dt.thang) {
			if((dtNow.ngay - dt.ngay) * 24 + dtNow.gio - dt.gio >= DIST)
				return true;
		}
	}
	return false;
}

bool ktCungNgayThangNam(NgayThangNam dt1, NgayThangNam dt2) {
	return dt1.nam == dt2.nam && dt1.thang == dt2.thang && dt1.ngay == dt2.ngay;
}

void dinhDangNgayThangNam(char* res, NgayThangNam dt) {
	char phut[5], gio[5],ngay[5],thang[5],nam[5],ngayGio[25];
	itoa(dt.phut, phut, 10);
	itoa(dt.gio, gio, 10);
	itoa(dt.ngay, ngay, 10);
	itoa(dt.thang, thang, 10);
	itoa(dt.nam, nam, 10);
	if(strlen(ngay)==1)  {
		strcpy(ngayGio,"0");
		strcat(ngayGio,ngay);
	}
	else	strcpy(ngayGio,ngay);
	strcat(ngayGio,"/");
	if(strlen(thang) == 1) strcat(ngayGio,"0");
	strcat(ngayGio,thang);
	strcat(ngayGio,"/");
	strcat(ngayGio,nam);
	strcat(ngayGio," - ");
	if(strlen(gio) == 1) strcat(ngayGio,"0");
	strcat(ngayGio,gio);
	strcat(ngayGio,":");
	if(strlen(phut) == 1) strcat(ngayGio,"0");
	strcat(ngayGio,phut);
	
	strcpy(res, ngayGio);
}
