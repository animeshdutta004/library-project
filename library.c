#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100

struct Book {
    int id;
    char title[50];
    char author[50];
    int is_available;
};

struct Library {
    struct Book books[MAX_BOOKS];
    int num_books;
};

void add_book(struct Library* library, int id, const char* title, const char* author);
void borrow_book(struct Library* library, int id);
void return_book(struct Library* library, int id);
void print_inventory(const struct Library* library);

int main() {
    struct Library library;
    library.num_books = 0;

    add_book(&library, 1, "The Great Gatsby", "F. Scott Fitzgerald");
    add_book(&library, 2, "To Kill a Mockingbird", "Harper Lee");
    add_book(&library, 3, "1984", "George Orwell");
    add_book(&library, 4, "Pride and Prejudice", "Jane Austen");

    borrow_book(&library, 2);
    borrow_book(&library, 4);

    return_book(&library, 2);

    print_inventory(&library);

    return 0;
}

void add_book(struct Library* library, int id, const char* title, const char* author) {
    if (library->num_books >= MAX_BOOKS) {
        printf("Error: Library is full.\n");
        return;
    }

    struct Book book;
    book.id = id;
    strcpy(book.title, title);
    strcpy(book.author, author);
    book.is_available = 1;

    library->books[library->num_books++] = book;

    printf("Added book with ID %d: '%s' by %s.\n", id, title, author);
}

void borrow_book(struct Library* library, int id) {
    int found_book = 0;

    for (int i = 0; i < library->num_books; i++) {
        if (library->books[i].id == id) {
            if (library->books[i].is_available) {
                library->books[i].is_available = 0;
                printf("Borrowed book with ID %d: '%s' by %s.\n", id, library->books[i].title, library->books[i].author);
            } else {
                printf("Error: Book with ID %d is already checked out.\n", id);
            }
            found_book = 1;
            break;
        }
    }

    if (!found_book) {
        printf("Error: Book with ID %d not found.\n", id);
    }
}

void return_book(struct Library* library, int id) {
    int found_book = 0;

    for (int i = 0; i < library->num_books; i++) {
        if (library->books[i].id == id) {
            if (!library->books[i].is_available) {
                library->books[i].is_available = 1;
                printf("Returned book with ID %d: '%s' by %s.\n", id, library->books[i].title, library->books[i].author);
            } else {
                printf("Error: Book with ID %d is already returned.\n", id);
            }
            found_book = 1;
            break;
        }
    }

    if (!found_book) {
        printf("Error: Book with ID %d not found.\n", id);
    }
}

void print_inventory(const struct Library* library) {
    printf("Library Inventory");
}
