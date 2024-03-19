#include <stdio.h>     
#include <string.h>    

#define MAX_NAME_LENGTH 50   // Dinh nghia do dai toi da cua ten ruou
#define MAX_TYPE_LENGTH 20   // Dinh nghia do dai toi da cua loai ruou
#define FILE_NAME "wines.txt"   // Ten file luu tru thong tin ve ruou

// Dinh nghia cau truc du lieu cho moi loai ruou
struct Wine {
    char name[MAX_NAME_LENGTH];   // Ten ruou
    char type[MAX_TYPE_LENGTH];   // Loai ruou
    int year;                      // Nam san xuat
    float price;                   // Gia
};

// Ham de them mot loai ruou moi vao file
void addWineToFile(struct Wine wine) {
    FILE *file = fopen(FILE_NAME, "a");   // Mo file o che do ghi tiep
    if (file == NULL) {                   // Kiem tra viec mo file co thanh cong khong
        printf("Khong the mo file.\n");   // Thong bao loi neu khong the mo file
        return;
    }
    fprintf(file, "%s;%s;%d;%.2f\n", wine.name, wine.type, wine.year, wine.price);   // Ghi thong tin cua ruou vao file
    fclose(file);   // Dong file sau khi ghi xong
}

// Ham de hien thi tat ca cac loai ruou trong file
void displayAllWines() {
    FILE *file = fopen(FILE_NAME, "r");   // Mo file o che do doc
    if (file == NULL) {                    // Kiem tra viec mo file co thanh cong khong
        printf("Khong the mo file.\n");    // Thong bao loi neu khong the mo file
        return;
    }
    struct Wine wine;   // Khai bao bien wine co kieu du lieu la struct Wine
    printf("Danh sach cac loai ruou:\n");   // In ra thong diep
    printf("Ten\t\tLoai\tNam\tGia\n");     // In ra tieu de cua cac cot
    while (fscanf(file, "%[^;];%[^;];%d;%f\n", wine.name, wine.type, &wine.year, &wine.price) != EOF) {
        // Doc thong tin cua ruou tu file va in ra man hinh cho den khi het file
        printf("%s\t\t%s\t%d\t%.2f\n", wine.name, wine.type, wine.year, wine.price);
    }
    fclose(file);   // Dong file sau khi doc xong
}

// Ham de tim kiem va hien thi thong tin ve mot loai ruou cu the
void searchWine(char name[]) {
    FILE *file = fopen(FILE_NAME, "r");   // Mo file o che do doc
    if (file == NULL) {                    // Kiem tra viec mo file co thanh cong khong
        printf("Khong the mo file.\n");    // Thong bao loi neu khong the mo file
        return;
    }
    struct Wine wine;   // Khai bao bien wine co kieu du lieu la struct Wine
    int found = 0;      // Bien co de kiem tra xem ruou co duoc tim thay khong
    while (fscanf(file, "%[^;];%[^;];%d;%f\n", wine.name, wine.type, &wine.year, &wine.price) != EOF) {
        // Doc thong tin cua ruou tu file cho den khi het file
        if (strcmp(wine.name, name) == 0) {   // So sanh ten ruou voi ten can tim
            printf("Thong tin ve ruou %s:\n", name);   // In ra thong diep
            printf("Ten: %s\n", wine.name);            // In ra thong tin ten ruou
            printf("Loai: %s\n", wine.type);           // In ra thong tin loai ruou
            printf("Nam: %d\n", wine.year);            // In ra thong tin nam san xuat
            printf("Gia: %.2f\n", wine.price);         // In ra thong tin gia
            found = 1;   // Dat bien co bang 1 de biet ruou da duoc tim thay
            break;      // Thoat khoi vong lap
        }
    }
    if (!found) {    // Neu khong tim thay ruou trong file
        printf("Khong tim thay thong tin ve ruou %s.\n", name);   // In ra thong diep
    }
    fclose(file);   // Dong file sau khi doc xong
}

// Ham de xoa mot loai ruou khoi file
void deleteWine(char name[]) {
    FILE *file = fopen(FILE_NAME, "r");   // Mo file o che do doc
    if (file == NULL) {                   // Kiem tra viec mo file co thanh cong khong
        printf("Khong the mo file.\n");   // Thong bao loi neu khong the mo file
        return;
    }
    FILE *tempFile = fopen("temp.txt", "w");   // Mo file tam thoi o che do ghi
    if (tempFile == NULL) {                     // Kiem tra viec mo file tam co thanh cong khong
        printf("Khong the tao file tam thoi.\n");   // Thong bao loi neu khong the tao file tam
        fclose(file);   // Dong file goc
        return;
    }
    struct Wine wine;   // Khai bao bien wine co kieu du lieu la struct Wine
    int found = 0;      // Bien co de kiem tra xem ruou can xoa co ton tai khong
    while (fscanf(file, "%[^;];%[^;];%d;%f\n", wine.name, wine.type, &wine.year, &wine.price) != EOF) {
        // Doc thong tin cua ruou tu file cho den khi het file
        if (strcmp(wine.name, name) != 0) {   // Neu ten ruou khong trung khop voi ten can xoa
            fprintf(tempFile, "%s;%s;%d;%.2f\n", wine.name, wine.type, wine.year, wine.price);
            // Ghi thong tin cua ruou vao file tam thoi
        } else {
            found = 1;   // Dat bien co bang 1 de biet ruou da duoc tim thay va xoa
        }
    }
    fclose(file);   // Dong file goc sau khi doc xong
    fclose(tempFile);   // Dong file tam thoi sau khi ghi xong
    remove(FILE_NAME);   // Xoa file goc
    rename("temp.txt", FILE_NAME);   // Doi ten file tam thanh ten file goc
    if (found) {   // Neu ruou da duoc tim thay va xoa
        printf("Da xoa ruou %s khoi danh sach.\n", name);   // In ra thong diep
    } else {
        printf("Khong tim thay ruou %s trong danh sach.\n", name);   // In ra thong diep
    }
}

int main() {
    int choice;   // Bien lua chon
    struct Wine wine;   // Bien cau truc de luu thong tin ve ruou
    char wineName[MAX_NAME_LENGTH];   // Mang de luu ten cua ruou can tim/xoa

    while (1) {
        printf("\nChuong trinh quan ly ruou\n");   // In ra thong diep
        printf("1. Them ruou\n");    // In ra lua chon
        printf("2. Hien thi tat ca cac loai ruou\n");   // In ra lua chon
        printf("3. Tim kiem ruou\n");   // In ra lua chon
        printf("4. Xoa ruou\n");   // In ra lua chon
        printf("5. Thoat\n");   // In ra lua chon
        printf("Nhap lua chon cua ban: ");   // In ra thong diep
        scanf("%d", &choice);   // Nhap lua chon tu nguoi dung

        switch (choice) {   // Xu ly lua chon cua nguoi dung
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
