#include "Header.h"

int main() {
    LibrarySystem system("data/books.txt", "data/members.txt", "data/records.txt");
    system.run();
    return 0;
}

