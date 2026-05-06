#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "sinhvien.h"

// -------------------- Bien toan cuc --------------------
SinhVien dsSV[MAX_SV];
int tongSoSV = 0;


// -----------------------
// docCSV()
//  Chuc nang: Doc danh sach sinh vien tu file CSV (phan cach boi '|')
//  Tham so: tenFile - duong dan toi file CSV
//  Return: so luong sinh vien doc duoc (int), -1 neu khong mo duoc file
int docCSV(const char* tenFile) {
    FILE* fp = fopen(tenFile, "r");
    if (!fp) {
        printf(">>> LOI: Khong the mo file [%s] <<<\n", tenFile);
        return -1;
    }

    tongSoSV = 0;
    char dong[2048];

    while (fgets(dong, sizeof(dong), fp) != NULL && tongSoSV < MAX_SV) {

        // Bo qua dong trong (chi co '\n' hoac space)
        if (strlen(dong) <= 2) continue;

        // Xoa ky tu xuong dong o cuoi
        dong[strcspn(dong, "\r\n")] = '\0';

        SinhVien sv;
        sv.soLuongSoThich = 0;

        char* token;

        // --- MSSV ---
        token = strtok(dong, "|");
        if (!token) continue;
        strncpy(sv.mssv, token, MAX_MSSV - 1);
        sv.mssv[MAX_MSSV - 1] = '\0';

        // --- Ho ten ---
        token = strtok(NULL, "|");
        if (!token) continue;
        strncpy(sv.hoTen, token, MAX_TEN - 1);
        sv.hoTen[MAX_TEN - 1] = '\0';

        // --- Khoa ---
        token = strtok(NULL, "|");
        if (!token) continue;
        strncpy(sv.khoa, token, MAX_KHOA - 1);
        sv.khoa[MAX_KHOA - 1] = '\0';

        // --- Nam khoa (so nguyen) ---
        token = strtok(NULL, "|");
        if (!token) continue;
        sv.khoaNam = atoi(token);

        // --- Ngay sinh ---
        token = strtok(NULL, "|");
        if (!token) continue;
        strncpy(sv.ngaySinh, token, MAX_NGAYSINH - 1);
        sv.ngaySinh[MAX_NGAYSINH - 1] = '\0';

        // --- Hinh anh ---
        token = strtok(NULL, "|");
        if (!token) continue;
        strncpy(sv.hinhAnh, token, MAX_HINHANH - 1);
        sv.hinhAnh[MAX_HINHANH - 1] = '\0';

        // --- Mo ta ---
        token = strtok(NULL, "|");
        if (!token) continue;
        strncpy(sv.moTa, token, MAX_MOTA - 1);
        sv.moTa[MAX_MOTA - 1] = '\0';

        // --- So thich (co the khong co hoac co nhieu) ---
        // Moi so thich la 1 token tiep theo, doc den het dong
        token = strtok(NULL, "|");
        while (token != NULL && sv.soLuongSoThich < MAX_SOTHICH) {
            strncpy(sv.soThich[sv.soLuongSoThich], token, MAX_SOTHICH_LEN - 1);
            sv.soThich[sv.soLuongSoThich][MAX_SOTHICH_LEN - 1] = '\0';
            sv.soLuongSoThich++;
            token = strtok(NULL, "|");
        }

        // Luu vao mang toan cuc
        dsSV[tongSoSV++] = sv;
    }

    fclose(fp);
    printf(">>> Doc file [%s] thanh cong: %d sinh vien <<<\n", tenFile, tongSoSV);
    return tongSoSV;
}


// -----------------------
// ghiCSV()
//  Chuc nang: Ghi danh sach sinh vien hien tai ra file CSV
//  Tham so: tenFile - duong dan toi file CSV can ghi
//  Return: void
void ghiCSV(const char* tenFile) {
    FILE* fp = fopen(tenFile, "w");
    if (!fp) {
        printf(">>> LOI: Khong the ghi file [%s] <<<\n", tenFile);
        return;
    }

    for (int i = 0; i < tongSoSV; i++) {
        // Ghi cac truong co dinh
        fprintf(fp, "%s|%s|%s|%d|%s|%s|%s",
            dsSV[i].mssv,
            dsSV[i].hoTen,
            dsSV[i].khoa,
            dsSV[i].khoaNam,
            dsSV[i].ngaySinh,
            dsSV[i].hinhAnh,
            dsSV[i].moTa
        );

        // Ghi tung so thich (co the khong co)
        for (int j = 0; j < dsSV[i].soLuongSoThich; j++) {
            fprintf(fp, "|%s", dsSV[i].soThich[j]);
        }

        fprintf(fp, "\n");
    }

    fclose(fp);
    printf(">>> Ghi file [%s] thanh cong <<<\n", tenFile);
}


// -----------------------
// inThongTinSinhVien()
//  Chuc nang: In thong tin chi tiet cua mot sinh vien (theo hang doc)
//  Tham so: i - vi tri sinh vien trong mang dsSV
//  Return: void
void inThongTinSinhVien(int i) {
    printf("\n------------------------------------------\n");
    printf("  MSSV:       | %s\n",  dsSV[i].mssv);
    printf("  Ho ten:     | %s\n",  dsSV[i].hoTen);
    printf("  Khoa:       | %s\n",  dsSV[i].khoa);
    printf("  Nam khoa:   | %d\n",  dsSV[i].khoaNam);
    printf("  Ngay sinh:  | %s\n",  dsSV[i].ngaySinh);
    printf("  Hinh anh:   | %s\n",  dsSV[i].hinhAnh);
    printf("  Mo ta:      | %s\n",  dsSV[i].moTa);

    if (dsSV[i].soLuongSoThich > 0) {
        printf("  So thich:   |");
        for (int j = 0; j < dsSV[i].soLuongSoThich; j++) {
            printf(" [%s]", dsSV[i].soThich[j]);
        }
        printf("\n");
    } else {
        printf("  So thich:   | (khong co)\n");
    }
    printf("------------------------------------------\n");
}


// -----------------------
// inThongTinToanBoSinhVien()
//  Chuc nang: In danh sach toan bo sinh vien dang co trong he thong
//  Tham so: null
//  Return: void
void inThongTinToanBoSinhVien() {
    printf("\n======== DANH SACH SINH VIEN ========\n");

    if (tongSoSV == 0) {
        printf(">>> Chua co sinh vien nao trong danh sach <<<\n");
        return;
    }

    printf("%-10s | %-25s | %-25s | %-4s | %-10s\n",
        "MSSV", "Ho ten", "Khoa", "Khoa", "Ngay sinh");
    printf("-----------------------------------------------------------------------------------\n");

    for (int i = 0; i < tongSoSV; i++) {
        printf("%-10s | %-25s | %-25s | %-4d | %-10s\n",
            dsSV[i].mssv,
            dsSV[i].hoTen,
            dsSV[i].khoa,
            dsSV[i].khoaNam,
            dsSV[i].ngaySinh
        );
    }

    printf("-----------------------------------------------------------------------------------\n");
    printf("Tong cong: %d sinh vien\n", tongSoSV);
}


// -----------------------
// timSinhVienTheoMSSV()
//  Chuc nang: Tim sinh vien theo MSSV
//  Tham so: mssv - chuoi MSSV can tim
//  Return: vi tri sinh vien trong mang (int), -1 neu khong tim thay
int timSinhVienTheoMSSV(const char* mssv) {
    for (int i = 0; i < tongSoSV; i++) {
        if (strcmp(dsSV[i].mssv, mssv) == 0)
            return i;
    }
    return -1;
}
