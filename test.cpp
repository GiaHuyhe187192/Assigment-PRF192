#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_TYPE_LENGTH 20
#define FILE_NAME "wines.txt"

// Ð?nh nghia c?u trúc d? li?u cho m?i lo?i ru?u
struct Wine {
    char name[MAX_NAME_LENGTH];
    char type[MAX_TYPE_LENGTH];
    int year;
    float price;
};

// Hàm d? thêm m?t lo?i ru?u m?i vào file
void addWineToFile(struct Wine wine) {
    FILE *file = fopen(FILE_NAME, "a");
    if (file == NULL) {
        printf("Khong the mo file.\n");
        return;
    }
    fprintf(file, "%s;%s;%d;%.2f\n", wine.name, wine.type, wine.year, wine.price);
    fclose(file);
}

// Hàm d? hi?n th? t?t c? các lo?i ru?u trong file
void displayAllWines() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Khong the mo file.\n");
        return;
    }
    struct Wine wine;
    printf("Danh sach cac loai ruou:\n");
    printf("Ten\t\tLoai\tNam\tGia\n");
    while (fscanf(file, "%[^;];%[^;];%d;%f\n", wine.name, wine.type, &wine.year, &wine.price) != EOF) {
        printf("%s\t\t%s\t%d\t%.2f\n", wine.name, wine.type, wine.year, wine.price);
    }
    fclose(file);
}

// Hàm d? tìm ki?m và hi?n th? thông tin v? m?t lo?i ru?u c? th?
void searchWine(char name[]) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Khong the mo file.\n");
        return;
    }
    struct Wine wine;
    int found = 0;
    while (fscanf(file, "%[^;];%[^;];%d;%f\n", wine.name, wine.type, &wine.year, &wine.price) != EOF) {
        if (strcmp(wine.name, name) == 0) {
            printf("Thong tin ve ruou %s:\n", name);
            printf("Ten: %s\n", wine.name);
            printf("Loai: %s\n", wine.type);
            printf("Nam: %d\n", wine.year);
            printf("Gia: %.2f\n", wine.price);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Khong tim thay thong tin ve ruou %s.\n", name);
    }
    fclose(file);
}

// Hàm d? xóa m?t lo?i ru?u kh?i file
void deleteWine(char name[]) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Khong the mo file.\n");
        return;
    }
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Khong the tao file tam thoi.\n");
        fclose(file);
        return;
    }
    struct Wine wine;
    int found = 0;
    while (fscanf(file, "%[^;];%[^;];%d;%f\n", wine.name, wine.type, &wine.year, &wine.price) != EOF) {
        if (strcmp(wine.name, name) != 0) {
            fprintf(tempFile, "%s;%s;%d;%.2f\n", wine.name, wine.type, wine.year, wine.price);
        } else {
            found = 1;
        }
    }
    fclose(file);
    fclose(tempFile);
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);
    if (found) {
        printf("Da xoa ruou %s khoi danh sach.\n", name);
    } else {
        printf("Khong tim thay ruou %s trong danh sach.\n", name);
    }
}

int main() {
    int choice;
    struct Wine wine;
    char wineName[MAX_NAME_LENGTH];

    while (1) {
        printf("\nChuong trinh quan ly ruou\n");
        printf("1. Them ruou\n");
        printf("2. Hien thi tat ca cac loai ruou\n");
        printf("3. Tim kiem ruou\n");
        printf("4. Xoa ruou\n");
        printf("5. Thoat\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nhap ten ruou: ");
                scanf(" %[^\n]s", wine.name);
                printf("Nhap loai ruou: ");
                scanf(" %[^\n]s", wine.type);
                printf("Nhap nam: ");
                scanf("%d", &wine.year);
                printf("Nhap gia: ");
                scanf("%f", &wine.price);
                addWineToFile(wine);
                break;
            case 2:
                displayAllWines();
                break;
            case 3:
                printf("Nhap ten ruou can tim: ");
                scanf(" %[^\n]s", wineName);
                searchWine(wineName);
                break;
            case 4:
                printf("Nhap ten ruou can xoa: ");
                scanf(" %[^\n]s", wineName);
                deleteWine(wineName);
                break;
            case 5:
                printf("Thoat khoi chuong trinh.\n");
                exit(0);
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    }

    return 0;
}
