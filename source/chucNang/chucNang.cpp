#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "chucNang.h"
#include "../sinhvien/sinhvien.h"
#include "../fileio/fileio.h"

// -----------------------
// hienThiMenu()
//  Chuc nang: In ra menu chinh
void hienThiMenu() {
    printf("\n");
    printf("================= MENU CHINH =================\n");
    printf("1. Xem thong tin Profile\n");
    printf("2. Cho phep tuy chon an/hien cac truong config\n");
    printf("3. Tao HTML\n");
    printf("0. Thoat chuong trinh\n");
    printf("==============================================\n");
    printf("Nhap lua chon cua ban: ");
}

// -----------------------
// chucNangXemProfile()
//  Chuc nang: Xem chi tiet profile (theo MSSV hoac xem tat ca)
void chucNangXemProfile() {
    char input[MAX_MSSV];
    printf("\n--- Xem thong tin Profile ---\n");
    printf("Nhap MSSV can xem (hoac nhap 'All' de xem tat ca): ");
    
    scanf("%s", input);

    if (strcmp(input, "All") == 0 || strcmp(input, "all") == 0) {
        // Hien thi tat ca
        inThongTinToanBoSinhVien();
    } else {
        int vitri = timSinhVienTheoMSSV(input);
        if (vitri >= 0) {
            inThongTinSinhVien(vitri);
        } else {
            printf(">>> Khong tim thay sinh vien co MSSV: %s <<<\n", input);
        }
    }
}

// -----------------------
// chucNangCauHinh()
//  Chuc nang: Bat/tat config (Email, Ngay Sinh, So Thich, Mo Ta, Hinh Anh)
void chucNangCauHinh(Config* cfg) {
    int choice = -1;
    while (choice != 0) {
        printf("\n--- Tuy chon an/hien Config ---\n");
        printf("1. Hien thi Email     (Hien tai: %s)\n", cfg->showEmail ? "BAT" : "TAT");
        printf("2. Hien thi Ngay Sinh (Hien tai: %s)\n", cfg->showNgaySinh ? "BAT" : "TAT");
        printf("3. Hien thi So Thich  (Hien tai: %s)\n", cfg->showSoThich ? "BAT" : "TAT");
        printf("4. Hien thi Mo Ta     (Hien tai: %s)\n", cfg->showMoTa ? "BAT" : "TAT");
        printf("5. Hien thi Hinh Anh  (Hien tai: %s)\n", cfg->showHinhAnh ? "BAT" : "TAT");
        printf("0. Quay lai menu chinh\n");
        printf("Chon thong tin can chuyen doi trang thai (0-5): ");
        if (scanf("%d", &choice) != 1) {
            
            while(getchar() != '\n');
            choice = -1;
            continue;
        }

        switch (choice) {
            case 1: cfg->showEmail = !cfg->showEmail; break;
            case 2: cfg->showNgaySinh = !cfg->showNgaySinh; break;
            case 3: cfg->showSoThich = !cfg->showSoThich; break;
            case 4: cfg->showMoTa = !cfg->showMoTa; break;
            case 5: cfg->showHinhAnh = !cfg->showHinhAnh; break;
            case 0: break;
            default: printf("Lựa chọn không hợp lệ!\n");
        }
    }
}

// -----------------------
// chucNangTaoHTML()
//  Chuc nang: Xuat html voi cau hinh hien tai
void chucNangTaoHTML(const Config* cfg) {
    printf("\n--- Tao HTML ---\n");

    generateAllHTML(dsSV, tongSoSV, cfg, "Websites/output/");
}

// -----------------------
// runChucNang()
//  Chuc nang: Vong lap chinh cua menu
void runChucNang() {
    Config cfg;
    int luaChon = -1;

    // Khoi tao cau hinh mac dinh
    loadDefaultConfig(&cfg);

    // Doc du lieu ban dau
    printf(">>> Dang doc du lieu tu file CSV... <<<\n");
    int soLuong = docCSV("data/students.csv");
    if (soLuong <= 0) {
        printf(">>> LOI: Khong co du lieu de xu ly, chuong trinh se thoat <<<\n");
        return;
    }

    // Vong lap menu
    while (luaChon != 0) {
        hienThiMenu();
        if (scanf("%d", &luaChon) != 1) {
            while(getchar() != '\n'); 
            luaChon = -1;
            continue;
        }

        switch (luaChon) {
            case 1:
                chucNangXemProfile();
                break;
            case 2:
                chucNangCauHinh(&cfg);
                break;
            case 3:
                chucNangTaoHTML(&cfg);
                break;
            case 0:
                printf("\nCam on ban da su dung chuong trinh. Tam biet!\n");
                break;
            default:
                printf("\n>>> Lua chon khong hop le, vui long nhap lai! <<<\n");
                break;
        }
    }
}
