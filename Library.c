#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book 
{
    int id;
    char title[50];
    char author[50];
};

// Function to add a book
void addBook() 
{
    struct Book book;
    FILE *file = fopen("library.txt", "a+");  // Create file if not exists

    if (file == NULL) 
    {
        printf("\nError opening file!\n");
        return;
    }

    printf("\nEnter Book ID: ");
    scanf("%d", &book.id);
    getchar();  // Consume newline character

    printf("Enter Book Title: ");
    fgets(book.title, sizeof(book.title), stdin);
    printf("Enter Author Name: ");
    fgets(book.author, sizeof(book.author), stdin);

    // Remove newline character from input
    book.title[strcspn(book.title, "\n")] = '\0';
    book.author[strcspn(book.author, "\n")] = '\0';

    fwrite(&book, sizeof(struct Book), 1, file);
    fclose(file);
    printf("\nBook added successfully!\n");
}

// Function to display all books
void displayBooks() 
{
    struct Book book;
    FILE *file = fopen("library.txt", "r");

    if (file == NULL) 
    {
        printf("\nNo books available!\n");
        return;
    }

    printf("\n--- Book List ---\n");
    int found = 0;
    while (fread(&book, sizeof(struct Book), 1, file)) 
    {
        printf("\nID: %d\nTitle: %s\nAuthor: %s\n", book.id, book.title, book.author);
        found = 1;
    }
    fclose(file);

    if (!found)
        printf("\nNo books available!\n");
}

// Function to search for a book
void searchBook() 
{
    struct Book book;
    char searchTitle[50];
    int found = 0;

    FILE *file = fopen("library.txt", "r");
    if (file == NULL) 
    {
        printf("\nNo books available!\n");
        return;
    }

    getchar(); // Consume newline
    printf("\nEnter Book Title to Search: ");
    fgets(searchTitle, sizeof(searchTitle), stdin);
    searchTitle[strcspn(searchTitle, "\n")] = '\0';

    while (fread(&book, sizeof(struct Book), 1, file)) 
    {
        if (strcmp(book.title, searchTitle) == 0) 
        {
            printf("\nBook Found!\nID: %d\nTitle: %s\nAuthor: %s\n", book.id, book.title, book.author);
            found = 1;
            break;
        }
    }
    fclose(file);

    if (!found) 
    {
        printf("\nBook Not Found!\n");
    }
}

// Function to delete a book
void deleteBook() 
{
    struct Book book;
    FILE *file = fopen("library.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL) 
    {
        printf("\nError opening file!\n");
        return;
    }

    int deleteId, found = 0;
    printf("\nEnter Book ID to Delete: ");
    scanf("%d", &deleteId);

    while (fread(&book, sizeof(struct Book), 1, file)) 
    {
        if (book.id != deleteId) 
        {
            fwrite(&book, sizeof(struct Book), 1, tempFile);
        } 
        else 
        {
            found = 1;
        }
    }
    fclose(file);
    fclose(tempFile);

    if (found) 
    {
        remove("library.txt");
        rename("temp.txt", "library.txt");
        printf("\nBook Deleted Successfully!\n");
    } 
    else 
    {
        remove("temp.txt");  // Do not overwrite original file
        printf("\nBook Not Found!\n");
    }
}

// Main menu
int main() 
{
    int choice;
    do {
        printf("\nLIBRARY MANAGEMENT SYSTEM\n");
        printf("1. Add Book\n2. Display Books\n3. Search Book\n4. Delete Book\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: deleteBook(); break;
            case 5: printf("\nExiting... Thank you!\n"); break;
            default: printf("\nInvalid choice! Try again.\n");
        }
    } while (choice != 5);

    return 0;
}
