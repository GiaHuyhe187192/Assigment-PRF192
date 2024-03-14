#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

#define MAXN 100
#define MAXL 50

void saveToFile(char wine[][MAXL], int quantity[], int n);
void loadFromFile(char wine[][MAXL], int quantity[], int *n);
void updateFile(char wine[][MAXL], int quantity[], int n);

void addWine(char wines[], char wine[][MAXL], int quantity[], int quantities, int *pn);
void removeWine(char wine[][MAXL], int quantity[], int pos, int *pn, int *total);
int search(char wines[], char wine[][MAXL], int n);

void printList(char wine[][MAXL], int quantity[], int n, int total);
int getUserChoice();
int getUpChoice();
int checkNumb();
int checkChar(char s[]);
char* lTrim(char s[]);
char* rTrim(char s[]);
char* trim(char s[]);
char* nameStr (char s[]);

int main() {
    char wine[MAXN][MAXL];
    int quantity[MAXN];
    int n = 0;
    int total = 0;

   
    loadFromFile(wine, quantity, &n);

    int userChoice, outMenu = 0;
    do {
        userChoice = getUserChoice();
        switch(userChoice) {
            case 1:
               
                {
                    int checkCh;
                    char wines[MAXL];
                    int quantities;
                    printf("\nNhap thong tin ve loai ruou:\n");
                    printf("Ten loai ruou: ");
                    do {
                        scanf("%[^\n]", wines);
                        fflush(stdin);
                        checkCh = checkChar(wines);
                        if (checkCh == 0)
                            printf("Loi! Khong co ky tu de nhan dang! Nhap ten loai ruou lai: ");
                    } while (checkCh == 0);

                    printf("So luong cua loai ruou: ");
                    do {
                        quantities = checkNumb();
                        if (quantities == 0)
                            printf("Loi! Chi so nguyen duoc chap nhan! Nhap so luong lai: ");
                    } while (quantities == 0);
                    total += quantities;
                    if (total <= MAXN) {
                        nameStr(wines);
                        addWine(wines, wine, quantity, quantities, &n);
                        printf("\nDa them!!\n");
                    } else {
                        printf("\nThat bai! Ke ruou khong du cho de them loai ruou nay!\n");
                        total -= quantities;
                    }
                }
                break;
            case 2:
                
                if (n == 0)
                    printf("\nKe ruou dang trong!\n");
                else
                    printList(wine, quantity, n, total);
                break;
            case 3:
                
                if (n == 0)
                    printf("\nKe ruou dang trong!\n");
                else {
                    char wines[MAXL];
                    int pos;
                    printf("\nNhap ten loai ruou ban muon tim: ");
                    scanf(" %[^\n]", wines); 
                    fflush(stdin);
                    nameStr(wines);
                    pos = search(wines, wine, n);
                    if (pos < 0)
                        printf("\nLoai ruou nay khong ton tai!\n");
                    else
                        printf("\nTim thay!\nSo luong cua loai ruou %s la: %d\n", wine[pos], quantity[pos]);
                }
                break;
            case 4:
               
                if (n == 0)
                    printf("\nKe ruou dang trong!\n");
                else {
                    char wines[MAXL];
                    int pos;
                    printf("\nNhap ten loai ruou ban muon cap nhat: ");
                    scanf(" %[^\n]", wines);
                    fflush(stdin);
                    nameStr(wines);
                    pos = search(wines, wine, n);
                    if (pos < 0)
                        printf("\nLoai ruou nay khong ton tai!\n");
                    else {
                        printf("\nTim thay!\n");
                        int updateChoice;
                        int leave = 0;
                        do {
                            updateChoice = getUpChoice();
                            switch (updateChoice) {
                                case 1:
                                    {
                                        int checkCh;
                                        char winess[MAXL];
                                        printf("\nNhap ten moi cho loai ruou: ");
                                        do {
                                            scanf(" %[^\n]", winess);
                                            fflush(stdin);
                                            checkCh = checkChar(winess);
                                            if (checkCh == 0)
                                                printf("Loi! Khong co ky tu de nhan dang! Nhap ten lai: ");
                                        } while (checkCh == 0);
                                        nameStr(winess);
                                        strcpy(wine[pos], winess);
                                        printf("\nDa cap nhat thanh cong!\n");
                                        break;
                                    }
                                case 2:
                                    {
                                        int cache = quantity[pos];
                                        total -= quantity[pos];
                                        int quantitiess;
                                        printf("\nNhap so luong moi cho loai ruou: ");
                                        do {
                                            quantitiess = checkNumb();
                                            if (quantitiess == 0)
                                                printf("Loi! Chi so nguyen duoc chap nhan! Nhap so luong lai: ");
                                        } while (quantitiess == 0);
                                        total += quantitiess;
                                        if (total <= MAXN) {
                                            quantity[pos] = quantitiess;
                                            printf("\nDa cap nhat thanh cong!\n");
                                        } else {
                                            printf("\nThat bai! Ke ruou khong du cho de them loai ruou nay!\n");
                                            total -= quantitiess;
                                            total += cache;
                                        }
                                        break;
                                    }
                                case 3:
                                    leave = 1;
                                    break;
                                default:
                                    printf("Lua chon khong hop le! Vui long nhap lai lua chon cua ban!\n");
                            }
                        } while (leave == 0);
                        printf("\nDa cap nhat!\n");
                    }
                }
                break;
            case 5:
                
                if (n == 0)
                    printf("\nKe ruou dang trong!\n");
                else {
                    char wines[MAXL];
                    int pos;
                    printf("\nNhap ten loai ruou ban muon xoa: ");
                    scanf(" %[^\n]", wines);
                    fflush(stdin);
                    nameStr(wines);
                    pos = search(wines, wine, n);
                    if (pos < 0)
                        printf("\nLoai ruou nay khong ton tai!\n");
                    else
                        removeWine(wine, quantity, pos, &n, &total);
                }
                break;
            case 6:
                outMenu = 1; 
                break;
            default:
                printf("\nLua chon khong hop le!\n");
        }
    } while (!outMenu);

    
    saveToFile(wine, quantity, n);
    printf("\nTam biet! Hen gap lai!\n");
    return 0;
}

void saveToFile(char wine[][MAXL], int quantity[], int n) {
    FILE *file = fopen("wine_data.txt", "w");
    if (file == NULL) {
        printf("Khong the mo tep tin de luu du lieu.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%s %d\n", wine[i], quantity[i]);
    }

    fclose(file);
}

void loadFromFile(char wine[][MAXL], int quantity[], int *n) {
    FILE *file = fopen("wine_data.txt", "r");
    if (file == NULL) {
        printf("Khong the mo tep tin de doc du lieu.\n");
        return;
    }

    *n = 0;
    while (fscanf(file, "%s %d", wine[*n], &quantity[*n]) == 2) {
        (*n)++;
    }

    fclose(file);
}

void updateFile(char wine[][MAXL], int quantity[], int n) {
    FILE *file = fopen("wine_data.txt", "w");
    if (file == NULL) {
        printf("Khong the mo tep tin de cap nhat du lieu.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%s %d\n", wine[i], quantity[i]);
    }

    fclose(file);
}

void addWine(char wines[], char wine[][MAXL], int quantity[], int quantities, int *pn) {
    strcpy(wine[*pn], wines);
    quantity[*pn] = quantities;
    (*pn)++;
}

void removeWine(char wine[][MAXL], int quantity[], int pos, int *pn, int *total) {
    (*total) -= quantity[pos];
    for (int i = pos + 1; i < (*pn); i++) {
        strcpy(wine[i-1], wine[i]);
        quantity[i-1] = quantity[i];
    }
    (*pn)--;
    printf("\nLoai ruou nay da duoc xoa khoi ke ruou thanh cong!\n");
}

int search(char wines[], char wine[][MAXL], int n) {
    for (int i = 0; i < n; i++) {
        if (strcmp(wines, wine[i]) == 0)
            return i;
    }
    return -1;
}

void printList(char wine[][MAXL], int quantity[], int n, int total) {
    printf("\n--Tat ca loai ruou trong ke--\n");
    for (int i = 0; i < n; i++) {
        printf("\nTen: %s\n", wine[i]);
        printf("So luong: %d\n", quantity[i]);
    }
    printf("\nTong so loai ruou trong ke hien tai: %d\n", total);
}

int getUserChoice() {
    int choice;
    printf("\n============= Chuong trinh quan ly ruou ==================");
    printf("\n| 1. Them thong tin loai ruou");
    printf("\n| 2. In ra tat ca loai ruou");
    printf("\n| 3. Tim kiem loai ruou");
    printf("\n| 4. Cap nhat thong tin loai ruou");
    printf("\n| 5. Xoa loai ruou");
    printf("\n| 6. Thoat chuong trinh");
    printf("\n=============================================\n");
    printf("\nNhap lua chon cua ban: ");
    do {
        choice = checkNumb();
        if (choice == 0)
            printf("Lua chon khong hop le! Vui long nhap lai: ");
    } while (choice == 0);
    return choice;
}

int getUpChoice() {
    int choices;
    printf("\nChon phan ban muon cap nhat\n");
    printf(">>Bam 1 - De cap nhat ten loai ruou\n");
    printf(">>Bam 2 - De cap nhat so luong loai ruou\n");
    printf(">>Bam 3 - Thoat khoi chuong trinh cap nhat thong tin loai ruou'\n");
    printf("\nNhap lua chon cua ban: ");
    do {
        choices = checkNumb();
        if (choices == 0)
            printf("Lua chon khong hop le! Vui long nhap lai: ");
    } while (choices == 0);
    return choices;
}

int checkNumb() {
    int num;
    char term;
    scanf("%d%c", &num, &term);
    fflush(stdin);
    if(term != '\n')
        return 0;
    else
        return num;
}

int checkChar(char s[]) {
    int length = strlen(s);
    int check, space = 0, enter = 0;
    for (int i = 0; i <= length; i++)
        if (s[i] == ' ')
            space++;
    if ((length == 1) && (s[length] == '\0'))
        enter = 1;
    if (space == length || enter == 1)
        return check = 0;
    else
        return check = 1;
}

char* lTrim(char s[]) {
    int i = 0;
    while (s[i] == ' ') i++;
    if (i > 0) strcpy(&s[0], &s[i]);
    return s;
}

char* rTrim(char s[]) {
    int i = strlen(s)-1;
    while (s[i] == ' ') i--;
    s[i+1] = '\0';
    return s;
}

char* trim(char s[]) {
    rTrim(lTrim(s));
    char *ptr = strstr(s, "  ");
    while (ptr != NULL) {
        strcpy(ptr, ptr+1);
        ptr = strstr(s, "  ");
    }
    return s;
}

char* nameStr (char s[]) {
    trim(s);
    strlwr(s);
    int L = strlen(s);
    for (int i = 0; i < L; i++)
        if (i == 0 || (i > 0 && s[i-1] == ' '))
            s[i] = toupper(s[i]);
    return s;
}

