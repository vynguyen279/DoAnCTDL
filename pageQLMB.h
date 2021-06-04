#pragma once
#include "reuse.h"

//====================PROTOTYPE==================
void drawPageQLMB(short **, Shape *, bool);
void drawUpdateMBFrame(short **, Shape *, Input *);
void drawDelMBFrame(short **, Shape *, Input *);
void getInputPageQLMB(Input &, short &, bool &);
void checkDelInvalidMB(Input *, bool &,DanhSachMayBay &,DanhSachChuyenBay &);
void checkAddInvalidMB(Input *, bool &,DanhSachMayBay &);
void checkUpdateInvalidMB(Input *, bool &, bool &,DanhSachMayBay &,DanhSachChuyenBay &);
void checkSaveInvalidMB(Input *, bool &);
void checkEventPageQLMB(short **, Shape *, Input *, Button *, Board &);
void checkHoverPageQLMB(short &, short, Shape *, short **);
void alertAddSuccess();
void alertUpdateSuccess();
void alertDelSuccess();
void addMB(Input *,DanhSachMayBay &);
void delMB(Input *,DanhSachMayBay &,DanhSachChuyenBay &);
void UpdateMB(Input *,DanhSachMayBay &);
void chuanHoaInputQLMB(Input &, short);
void outDSCB(Board &, int, int,DanhSachTam &);
void outDSMB(Board &, int, int,DanhSachMayBay &);
void getMBData(Input *,short, short **,DanhSachMayBay &);
void outNumOfBoardDSMB(int &, int &,DanhSachMayBay &);
//==========================================================


