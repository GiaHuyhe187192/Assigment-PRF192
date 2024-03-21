#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100
#define FILENAME "shoes.txt"

struct Shoe {
    char brand[MAX_SIZE];
    int size;
    int quantity;
    float price; 
};


void createShoe();
void readShoes();
void updateShoe();
void deleteShoe();

int main() {
    int choice;

    do {
        printf("\n========= Shoe Management System =========\n");
        printf("1. Create a new shoe\n");
        printf("2. View all shoes\n");
        printf("3. Update shoe information\n");
        printf("4. Delete a shoe\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createShoe();
                break;
            case 2:
                readShoes();
                break;
            case 3:
                updateShoe();
                break;
            case 4:
                deleteShoe();
                break;
            case 5:
                printf("Exiting the program. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    } while (choice != 5);

    return 0;
}


void createShoe() {
    struct Shoe newShoe;
    FILE *file = fopen(FILENAME, "a");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("\nEnter shoe brand: ");
    scanf("%s", newShoe.brand);

    printf("Enter shoe size: ");
    scanf("%d", &newShoe.size);

    printf("Enter shoe quantity: ");
    scanf("%d", &newShoe.quantity);

    printf("Enter shoe price: ");
    scanf("%f", &newShoe.price);

    fprintf(file, "%s %d %d %.2f\n", newShoe.brand, newShoe.size, newShoe.quantity, newShoe.price);

    fclose(file);

    printf("Shoe added successfully.\n");
}



void readShoes() {
    struct Shoe shoe;
    FILE *file = fopen(FILENAME, "r");

    if (file == NULL) {
        printf("No shoes found.\n");
        return;
    }

    printf("\n==================== All Shoes ====================\n");
    printf("| %-20s | %-5s | %-8s | %-6s | %-8s |\n", "Brand", "Size", "Quantity", "Price", "Total");
    printf("|----------------------|-------|----------|--------|----------|\n");
    float total = 0.0;
    while (fscanf(file, "%s %d %d %f", shoe.brand, &shoe.size, &shoe.quantity, &shoe.price) != EOF) {
        float shoeTotal = shoe.quantity * shoe.price;
        total += shoeTotal;
        printf("| %-20s | %-5d | %-8d | $%-5.0f | $%-7.0f |\n", shoe.brand, shoe.size, shoe.quantity, shoe.price, shoeTotal);
    }
    printf("|=================================================|\n");
    fclose(file);
   
}


// Function to update shoe information
void updateShoe() {
    char brand[MAX_SIZE];
    printf("\nEnter the brand of the shoe to update: ");
    scanf("%s", brand);

    struct Shoe shoe;
    FILE *file = fopen(FILENAME, "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL) {
        printf("No shoes found.\n");
        return;
    }

    int found = 0;
    while (fscanf(file, "%s %d %d %f", shoe.brand, &shoe.size, &shoe.quantity, &shoe.price) != EOF) {
        if (strcmp(brand, shoe.brand) == 0) {
            found = 1;
            printf("Enter new size: ");
            scanf("%d", &shoe.size);
            printf("Enter new quantity: ");
            scanf("%d", &shoe.quantity);
            printf("Enter new price: ");
            scanf("%f", &shoe.price);
        }
        fprintf(tempFile, "%s %d %d %.2f\n", shoe.brand, shoe.size, shoe.quantity, shoe.price);
    }

    fclose(file);
    fclose(tempFile);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (!found) {
        printf("Shoe not found.\n");
    } else {
        printf("Shoe information updated successfully.\n");
    }
}


void deleteShoe() {
    char brand[MAX_SIZE];
    printf("\nEnter the brand of the shoe to delete: ");
    scanf("%s", brand);

    struct Shoe shoe;
    FILE *file = fopen(FILENAME, "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL) {
        printf("No shoes found.\n");
        return;
    }

    int found = 0;
    while (fscanf(file, "%s %d %d %f", shoe.brand, &shoe.size, &shoe.quantity, &shoe.price) != EOF) {
        if (strcmp(brand, shoe.brand) != 0) {
            fprintf(tempFile, "%s %d %d %.2f\n", shoe.brand, shoe.size, shoe.quantity, shoe.price);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (!found) {
        printf("Shoe not found.\n");
    } else {
        printf("Shoe deleted successfully.\n");
    }
}

