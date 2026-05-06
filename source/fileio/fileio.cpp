#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "fileio.h"
#include "../sinhvien/sinhvien.h"

// -----------------------
// chuoiInHoa()
//  Chuc nang: Chuyen chuoi ASCII sang in hoa (dung cho MSSV, ten khoa ASCII)
void chuoiInHoa(char* dest, const char* src, int size) {
    int i;
    for (i = 0; i < size - 1 && src[i] != '\0'; i++) {
        dest[i] = (char)toupper((unsigned char)src[i]);
    }
    dest[i] = '\0';
}

// -----------------------
// replacePlaceholder()
//  Chuc nang: Thay the tat ca chuoi placeholder thanh repl trong noi dung html
void replacePlaceholder(char* html, const char* placeholder, const char* repl) {
    char buffer[16384]; // Bo dem tam thoi, 16KB la du cho HTML don gian
    char* insert_point = &buffer[0];
    const char* tmp = html;
    size_t needle_len = strlen(placeholder);
    size_t repl_len = strlen(repl);
    const char* p;

    // Neu khong tim thay placeholder thi tra ve
    if (!strstr(html, placeholder)) return;

    while (1) {
        p = strstr(tmp, placeholder);

        if (p == NULL) {
            strcpy(insert_point, tmp);
            break;
        }

        memcpy(insert_point, tmp, p - tmp);
        insert_point += p - tmp;

        memcpy(insert_point, repl, repl_len);
        insert_point += repl_len;

        tmp = p + needle_len;
    }

    strcpy(html, buffer);
}

// =================== HAM PUBLIC ===================

void loadDefaultConfig(Config* cfg) {
    cfg->showEmail     = 1;
    cfg->showNgaySinh  = 1;
    cfg->showSoThich   = 1;
    cfg->showMoTa      = 1;
    cfg->showHinhAnh   = 1;

    strncpy(cfg->mssvSinhVienThucHien, "25810013", MAX_MSSV - 2);
    cfg->mssvSinhVienThucHien[MAX_MSSV - 1] = '\0';
    strncpy(cfg->tenSinhVienThucHien,  "KHUU NHAT TIN", MAX_TEN - 1);
    strncpy(cfg->namHoc,               "TH2026", 9);
}

void generateHTML(const SinhVien* sv, const Config* cfg, const char* outputDir) {
    FILE* tplFile;
    char html[16384] = {0};
    char tenHoa[MAX_TEN];
    char khoaHoa[MAX_KHOA];
    char khoaNamStr[10];
    char hinhAnhBlock[512] = "";
    char emailPhoneBlock[256] = "";
    char emailInfoBlock[256] = "";
    char ngaySinhBlock[256] = "";
    char soThichBlock[2048] = "";
    char moTaBlock[1024] = "";
    char tenFile[512];
    FILE* out;
    int i;

    // Doc noi dung tu template.html
    tplFile = fopen("Websites/template.html", "r");
    if (!tplFile) {
        printf(">>> LOI: Khong the doc file Websites/template.html <<<\n");
        return;
    }

    // Doc chuoi HTML (template thuc te chi khoang 2-3KB)
    fread(html, 1, sizeof(html) - 1, tplFile);
    fclose(tplFile);

    // Chuan bi cac gia tri de replace
    chuoiInHoa(tenHoa, sv->hoTen, MAX_TEN);
    chuoiInHoa(khoaHoa, sv->khoa, MAX_KHOA);
    snprintf(khoaNamStr, sizeof(khoaNamStr), "%d", sv->khoaNam);

    // Xay dung cac block html (theo config)
    if (cfg->showHinhAnh) {
        snprintf(hinhAnhBlock, sizeof(hinhAnhBlock),
            "          <div class=\"Personal_HinhcanhanKhung\">\n"
            "            <img src=\"../images/%s.jpg\" class=\"Personal_Hinhcanhan\"\n"
            "                 alt=\"Hinh %s\" />\n"
            "          </div>", sv->mssv, sv->hoTen);
    }

    if (cfg->showEmail) {
        snprintf(emailPhoneBlock, sizeof(emailPhoneBlock),
            "            <div class=\"Personal_Phone\">\n"
            "              Email: %s@student.hcmus.edu.vn\n"
            "            </div>", sv->mssv);
            
        snprintf(emailInfoBlock, sizeof(emailInfoBlock),
            "              <li>Email: %s@student.hcmus.edu.vn</li>", sv->mssv);
    }

    if (cfg->showNgaySinh) {
        snprintf(ngaySinhBlock, sizeof(ngaySinhBlock),
            "              <li>Ngay sinh: %s</li>", sv->ngaySinh);
    }

    if (cfg->showSoThich && sv->soLuongSoThich > 0) {
        strcat(soThichBlock, "          <div class=\"InfoGroup\">So thich</div>\n");
        strcat(soThichBlock, "          <div class=\"MainContain_Center\">\n");
        strcat(soThichBlock, "            <ul class=\"TextInList\">\n");
        for (i = 0; i < sv->soLuongSoThich; i++) {
            char li[256];
            snprintf(li, sizeof(li), "              <li>%s</li>\n", sv->soThich[i]);
            strcat(soThichBlock, li);
        }
        strcat(soThichBlock, "            </ul>\n");
        strcat(soThichBlock, "          </div>\n");
    }

    if (cfg->showMoTa) {
        snprintf(moTaBlock, sizeof(moTaBlock),
            "          <div class=\"InfoGroup\">Mo ta ban than</div>\n"
            "          <div class=\"MainContain_Center\">\n"
            "            <p class=\"TextInList\" style=\"padding-bottom:25px;\">%s</p>\n"
            "          </div>\n", sv->moTa);
    }

    // Thay the tung the trong template
    replacePlaceholder(html, "{{hoTen}}", sv->hoTen);
    replacePlaceholder(html, "{{hoTenHoa}}", tenHoa);
    replacePlaceholder(html, "{{mssv}}", sv->mssv);
    replacePlaceholder(html, "{{khoa}}", sv->khoa);
    replacePlaceholder(html, "{{khoaHoa}}", khoaHoa);
    replacePlaceholder(html, "{{khoaNam}}", khoaNamStr);

    replacePlaceholder(html, "{{hinhAnhBlock}}", hinhAnhBlock);
    replacePlaceholder(html, "{{emailPhoneBlock}}", emailPhoneBlock);
    replacePlaceholder(html, "{{emailInfoBlock}}", emailInfoBlock);
    replacePlaceholder(html, "{{ngaySinhBlock}}", ngaySinhBlock);
    replacePlaceholder(html, "{{soThichBlock}}", soThichBlock);
    replacePlaceholder(html, "{{moTaBlock}}", moTaBlock);

    replacePlaceholder(html, "{{namHoc}}", cfg->namHoc);
    replacePlaceholder(html, "{{mssvSinhVienThucHien}}", cfg->mssvSinhVienThucHien);
    replacePlaceholder(html, "{{tenSinhVienThucHien}}", cfg->tenSinhVienThucHien);

    // Ghi ra file MSSV.html
    snprintf(tenFile, sizeof(tenFile), "%s%s.html", outputDir, sv->mssv);

    out = fopen(tenFile, "w");
    if (!out) {
        printf(">>> LOI: Khong the tao file [%s] <<<\n", tenFile);
        return;
    }
    fprintf(out, "%s", html);
    fclose(out);
    
    printf("  [OK] Sinh file: %s tu template\n", tenFile);
}

void generateAllHTML(SinhVien arr[], int soLuong, const Config* cfg, const char* outputDir) {
    int i;
    printf("\n>>> Bat dau sinh %d file HTML vao [%s] <<<\n", soLuong, outputDir);

    for (i = 0; i < soLuong; i++) {
        generateHTML(&arr[i], cfg, outputDir);
    }

    printf(">>> Hoan thanh! Da sinh %d file HTML <<<\n", soLuong);
}