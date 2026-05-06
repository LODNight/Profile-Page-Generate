#pragma once
#ifndef CHUCNANG_H
#define CHUCNANG_H

#include "../sinhvien/sinhvien.h"
#include "../fileio/fileio.h"

// Hien thi menu chinh
void hienThiMenu();

// 1. Chuc nang xem thong tin profile (Theo MSSV hoac All)
void chucNangXemProfile();

// 2. Chuc nang tuy chon an/hien config
void chucNangCauHinh(Config* cfg);

// 3. Chuc nang tao HTML
void chucNangTaoHTML(const Config* cfg);

// Ham gop dung de chay nguyen vong lap menu
void runChucNang();

#endif
