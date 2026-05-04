#pragma once

#ifndef FILEIO_H
#define FILEIO_H

// =================== FILEIO.H ===================
// Mo ta: Khai bao struct Config va cac ham sinh file HTML
// Bao gom: cau hinh hien thi, sinh 1 file, sinh toan bo
// =================================================

#include "../sinhvien/sinhvien.h"

// -------------------- Struct Config --------------------
// Mo ta: Kiem soat truong nao duoc hien thi tren trang profile
typedef struct Config {
    int showEmail;      // 1: hien thi email,     0: an
    int showNgaySinh;   // 1: hien thi ngay sinh, 0: an
    int showSoThich;    // 1: hien thi so thich,  0: an
    int showMoTa;       // 1: hien thi mo ta,     0: an
    int showHinhAnh;    // 1: hien thi hinh anh,  0: an

    // Thong tin footer
    char mssvSinhVienThucHien[MAX_MSSV];
    char tenSinhVienThucHien[MAX_TEN];
    char namHoc[10];
} Config;

// Chuyen chuoi ASCII sang in hoa (dung cho MSSV, ten khoa ASCII)
void chuoiInHoa(char* dest, const char* src, int size);

// Thay the tat ca chuoi placeholder thanh repl trong noi dung html
void replacePlaceholder(char* html, const char* placeholder, const char* repl);

// Cau hinh mac dinh
void loadDefaultConfig(Config* cfg);

// Sinh 1 file HTML cho 1 sinh vien
void generateHTML(const SinhVien* sv, const Config* cfg, const char* outputDir);

// Sinh toan bo file HTML cho ca danh sach
void generateAllHTML(SinhVien arr[], int soLuong, const Config* cfg, const char* outputDir);

#endif