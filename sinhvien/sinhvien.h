#pragma once

#ifndef SINHVIEN_H
#define SINHVIEN_H

// =================== STUDENT.H ===================
// Mo ta: Khai bao struct SinhVien va cac ham xu ly
// Bao gom: doc/ghi file CSV, in du lieu, tim kiem
// =================================================

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// -------------------- Hang so --------------------
#define MAX_SV          100     // so luong sinh vien toi da
#define MAX_MSSV        11      // MSSV toi da 10 ky tu + '\0'
#define MAX_TEN         31      // ten toi da 30 ky tu + '\0'
#define MAX_KHOA        31      // ten khoa toi da 30 ky tu + '\0'
#define MAX_NGAYSINH    11      // dd/mm/yyyy + '\0'
#define MAX_HINHANH     256     // duong dan file anh
#define MAX_MOTA        1001    // mo ta ban than toi da 1000 ky tu + '\0'
#define MAX_SOTHICH     10      // so luong so thich toi da
#define MAX_SOTHICH_LEN 101     // do dai moi so thich toi da 100 ky tu + '\0'

// -------------------- Struct SinhVien --------------------
typedef struct SinhVien {
    char mssv[MAX_MSSV];                        // Ma so sinh vien
    char hoTen[MAX_TEN];                        // Ho va ten
    char khoa[MAX_KHOA];                        // Ten khoa
    int  khoaNam;                               // Nam tuyen sinh (khoa)
    char ngaySinh[MAX_NGAYSINH];               // Ngay sinh (dd/mm/yyyy)
    char hinhAnh[MAX_HINHANH];                 // Duong dan toi file anh
    char moTa[MAX_MOTA];                       // Mo ta ban than
    char soThich[MAX_SOTHICH][MAX_SOTHICH_LEN]; // Danh sach so thich
    int  soLuongSoThich;                        // So luong so thich thuc te
} SinhVien;

// -------------------- Bien toan cuc --------------------
extern SinhVien dsSV[MAX_SV];
extern int tongSoSV;

// -------------------- Xu ly File --------------------
int  docCSV(const char* tenFile);
void ghiCSV(const char* tenFile);

// -------------------- In du lieu --------------------
void inThongTinToanBoSinhVien();
void inThongTinSinhVien(int i);

// -------------------- Tim kiem --------------------
int  timSinhVienTheoMSSV(const char* mssv);

#endif
