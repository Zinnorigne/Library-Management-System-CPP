#include "Header.h"

Book::Book() : id(0), title(""), author(""), category(""), available(true), borrowCount(0) {}

Book::Book(int id, string title, string author, string category, bool available, int borrowCount)
    : id(id), title(title), author(author), category(category), available(available), borrowCount(borrowCount) {}

int Book::getId() const { return id; }
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
string Book::getCategory() const { return category; }
bool Book::isAvailable() const { return available; }
int Book::getBorrowCount() const { return borrowCount; }

void Book::setAvailable(bool status) { available = status; }
void Book::increaseBorrowCount() { borrowCount++; }

string Book::toFileLine() const {
    stringstream ss;
    ss << id << "|" << title << "|" << author << "|" << category << "|" << available << "|" << borrowCount;
    return ss.str();
}

void Book::display() const {
    cout << "ID: " << id
         << " | Title: " << title
         << " | Author: " << author
         << " | Category: " << category
         << " | Status: " << (available ? "Available" : "Borrowed")
         << " | Demand Score: " << borrowCount << endl;
}

Member::Member() : id(0), name(""), email(""), borrowedBooks(0) {}

Member::Member(int id, string name, string email, int borrowedBooks)
    : id(id), name(name), email(email), borrowedBooks(borrowedBooks) {}

int Member::getId() const { return id; }
string Member::getName() const { return name; }
string Member::getEmail() const { return email; }
int Member::getBorrowedBooks() const { return borrowedBooks; }

void Member::borrowOneBook() { borrowedBooks++; }
void Member::returnOneBook() { if (borrowedBooks > 0) borrowedBooks--; }

string Member::toFileLine() const {
    stringstream ss;
    ss << id << "|" << name << "|" << email << "|" << borrowedBooks;
    return ss.str();
}

void Member::display() const {
    cout << "ID: " << id
         << " | Name: " << name
         << " | Email: " << email
         << " | Books Borrowed: " << borrowedBooks << endl;
}

BorrowRecord::BorrowRecord() : bookId(0), memberId(0), action(""), dateTime("") {}

BorrowRecord::BorrowRecord(int bookId, int memberId, string action, string dateTime)
    : bookId(bookId), memberId(memberId), action(action), dateTime(dateTime) {}

int BorrowRecord::getBookId() const { return bookId; }
int BorrowRecord::getMemberId() const { return memberId; }
string BorrowRecord::getAction() const { return action; }
string BorrowRecord::getDateTime() const { return dateTime; }

string BorrowRecord::toFileLine() const {
    stringstream ss;
    ss << bookId << "|" << memberId << "|" << action << "|" << dateTime;
    return ss.str();
}

void BorrowRecord::display() const {
    cout << "Book ID: " << bookId
         << " | Member ID: " << memberId
         << " | Action: " << action
         << " | Time: " << dateTime << endl;
}

LibrarySystem::LibrarySystem(string bookFile, string memberFile, string recordFile)
    : bookFile(bookFile), memberFile(memberFile), recordFile(recordFile) {}

int LibrarySystem::findBookIndex(int bookId) const {
    for (int i = 0; i < (int)books.size(); i++) {
        if (books[i].getId() == bookId) return i;
    }
    return -1;
}

int LibrarySystem::findMemberIndex(int memberId) const {
    for (int i = 0; i < (int)members.size(); i++) {
        if (members[i].getId() == memberId) return i;
    }
    return -1;
}

string LibrarySystem::currentDateTime() const {
    time_t now = time(0);
    char* dt = ctime(&now);
    string result(dt);
    result.erase(remove(result.begin(), result.end(), '\n'), result.end());
    return result;
}

void LibrarySystem::loadBooks() {
    books.clear();
    ifstream file(bookFile.c_str());
    if (!file) return;

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, title, author, category, available, borrowCount;
        getline(ss, id, '|');
        getline(ss, title, '|');
        getline(ss, author, '|');
        getline(ss, category, '|');
        getline(ss, available, '|');
        getline(ss, borrowCount, '|');

        if (!id.empty()) {
            books.push_back(Book(atoi(id.c_str()), title, author, category,
                                 available == "1", atoi(borrowCount.c_str())));
        }
    }
}

void LibrarySystem::loadMembers() {
    members.clear();
    ifstream file(memberFile.c_str());
    if (!file) return;

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, email, borrowedBooks;
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, email, '|');
        getline(ss, borrowedBooks, '|');

        if (!id.empty()) {
            members.push_back(Member(atoi(id.c_str()), name, email, atoi(borrowedBooks.c_str())));
        }
    }
}

void LibrarySystem::loadRecords() {
    records.clear();
    ifstream file(recordFile.c_str());
    if (!file) return;

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string bookId, memberId, action, dateTime;
        getline(ss, bookId, '|');
        getline(ss, memberId, '|');
        getline(ss, action, '|');
        getline(ss, dateTime, '|');

        if (!bookId.empty()) {
            records.push_back(BorrowRecord(atoi(bookId.c_str()), atoi(memberId.c_str()), action, dateTime));
        }
    }
}

void LibrarySystem::saveBooks() const {
    ofstream file(bookFile.c_str());
    for (int i = 0; i < (int)books.size(); i++) file << books[i].toFileLine() << endl;
}

void LibrarySystem::saveMembers() const {
    ofstream file(memberFile.c_str());
    for (int i = 0; i < (int)members.size(); i++) file << members[i].toFileLine() << endl;
}

void LibrarySystem::saveRecords() const {
    ofstream file(recordFile.c_str());
    for (int i = 0; i < (int)records.size(); i++) file << records[i].toFileLine() << endl;
}

void LibrarySystem::addBook() {
    int id;
    string title, author, category;
    cout << "Enter Book ID: "; cin >> id; cin.ignore();
    if (findBookIndex(id) != -1) throw runtime_error("Book ID already exists.");

    cout << "Enter Title: "; getline(cin, title);
    cout << "Enter Author: "; getline(cin, author);
    cout << "Enter Category: "; getline(cin, category);

    books.push_back(Book(id, title, author, category));
    saveBooks();
    cout << "Book added successfully.\n";
}

void LibrarySystem::addMember() {
    int id;
    string name, email;
    cout << "Enter Member ID: "; cin >> id; cin.ignore();
    if (findMemberIndex(id) != -1) throw runtime_error("Member ID already exists.");

    cout << "Enter Name: "; getline(cin, name);
    cout << "Enter Email: "; getline(cin, email);

    members.push_back(Member(id, name, email));
    saveMembers();
    cout << "Member added successfully.\n";
}

void LibrarySystem::showAllBooks() const {
    cout << "\n--- Smart Shelf: All Books ---\n";
    if (books.empty()) cout << "No books found.\n";
    for (int i = 0; i < (int)books.size(); i++) books[i].display();
}

void LibrarySystem::showAllMembers() const {
    cout << "\n--- Registered Members ---\n";
    if (members.empty()) cout << "No members found.\n";
    for (int i = 0; i < (int)members.size(); i++) members[i].display();
}

void LibrarySystem::searchBook() const {
    string key;
    cout << "Enter title / author / category keyword: ";
    cin.ignore();
    getline(cin, key);

    cout << "\n--- Search Result ---\n";
    bool found = false;
    for (int i = 0; i < (int)books.size(); i++) {
        string text = books[i].getTitle() + " " + books[i].getAuthor() + " " + books[i].getCategory();
        if (text.find(key) != string::npos) {
            books[i].display();
            found = true;
        }
    }
    if (!found) cout << "No matching book found.\n";
}

void LibrarySystem::borrowBook() {
    int bookId, memberId;
    cout << "Enter Book ID: "; cin >> bookId;
    cout << "Enter Member ID: "; cin >> memberId;

    int bIndex = findBookIndex(bookId);
    int mIndex = findMemberIndex(memberId);

    if (bIndex == -1) throw runtime_error("Book not found.");
    if (mIndex == -1) throw runtime_error("Member not found.");
    if (!books[bIndex].isAvailable()) throw runtime_error("Book is already borrowed.");

    books[bIndex].setAvailable(false);
    books[bIndex].increaseBorrowCount();
    members[mIndex].borrowOneBook();
    records.push_back(BorrowRecord(bookId, memberId, "BORROW", currentDateTime()));

    saveBooks(); saveMembers(); saveRecords();
    cout << "Book borrowed successfully. Smart shelf status updated.\n";
}

void LibrarySystem::returnBook() {
    int bookId, memberId;
    cout << "Enter Book ID: "; cin >> bookId;
    cout << "Enter Member ID: "; cin >> memberId;

    int bIndex = findBookIndex(bookId);
    int mIndex = findMemberIndex(memberId);

    if (bIndex == -1) throw runtime_error("Book not found.");
    if (mIndex == -1) throw runtime_error("Member not found.");
    if (books[bIndex].isAvailable()) throw runtime_error("This book is already in the library.");

    books[bIndex].setAvailable(true);
    members[mIndex].returnOneBook();
    records.push_back(BorrowRecord(bookId, memberId, "RETURN", currentDateTime()));

    saveBooks(); saveMembers(); saveRecords();
    cout << "Book returned successfully.\n";
}

void LibrarySystem::showHistory() const {
    cout << "\n--- Borrow / Return History ---\n";
    if (records.empty()) cout << "No transaction history found.\n";
    for (int i = 0; i < (int)records.size(); i++) records[i].display();
}

void SmartRecommender::recommendByCategory(const vector<Book>& books, const string& category) {
    cout << "\n--- AI Librarian Recommendation for " << category << " ---\n";
    bool found = false;
    for (int i = 0; i < (int)books.size(); i++) {
        if (books[i].getCategory() == category && books[i].isAvailable()) {
            books[i].display();
            found = true;
        }
    }
    if (!found) cout << "No available recommendation in this category.\n";
}

void SmartRecommender::showTrendingBooks(vector<Book> books) {
    sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
        return a.getBorrowCount() > b.getBorrowCount();
    });

    cout << "\n--- Predictive Demand: Trending Books ---\n";
    int limit = min(3, (int)books.size());
    for (int i = 0; i < limit; i++) books[i].display();
}

void LibrarySystem::smartRecommendation() const {
    int choice;
    cout << "\n1. Recommend by Category\n2. Show Trending Books\nChoose: ";
    cin >> choice;

    if (choice == 1) {
        string category;
        cout << "Enter category: ";
        cin.ignore();
        getline(cin, category);
        SmartRecommender::recommendByCategory(books, category);
    } else if (choice == 2) {
        SmartRecommender::showTrendingBooks(books);
    } else {
        cout << "Invalid choice.\n";
    }
}

void LibrarySystem::analyticsDashboard() const {
    int availableCount = 0, borrowedCount = 0;
    for (int i = 0; i < (int)books.size(); i++) {
        if (books[i].isAvailable()) availableCount++;
        else borrowedCount++;
    }

    cout << "\n========== NEO LIBRARY ANALYTICS DASHBOARD ==========" << endl;
    cout << "Total Books       : " << books.size() << endl;
    cout << "Available Books   : " << availableCount << endl;
    cout << "Borrowed Books    : " << borrowedCount << endl;
    cout << "Total Members     : " << members.size() << endl;
    cout << "Total Transactions: " << records.size() << endl;
    cout << "=====================================================" << endl;
}

void LibrarySystem::run() {
    loadBooks();
    loadMembers();
    loadRecords();

    int choice;
    do {
        cout << "\n\n====== NEO LIBRARY : FUTURE LIBRARY SYSTEM ======" << endl;
        cout << "1. Add Book\n";
        cout << "2. Add Member\n";
        cout << "3. Show All Books\n";
        cout << "4. Show All Members\n";
        cout << "5. Search Book\n";
        cout << "6. Borrow Book\n";
        cout << "7. Return Book\n";
        cout << "8. Borrow/Return History\n";
        cout << "9. Smart Recommendation\n";
        cout << "10. Analytics Dashboard\n";
        cout << "0. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        try {
            switch (choice) {
                case 1: addBook(); break;
                case 2: addMember(); break;
                case 3: showAllBooks(); break;
                case 4: showAllMembers(); break;
                case 5: searchBook(); break;
                case 6: borrowBook(); break;
                case 7: returnBook(); break;
                case 8: showHistory(); break;
                case 9: smartRecommendation(); break;
                case 10: analyticsDashboard(); break;
                case 0: cout << "System closed. Data saved.\n"; break;
                default: cout << "Invalid menu choice.\n";
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    } while (choice != 0);
}

