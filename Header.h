#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <stdexcept>

using namespace std;

class Book {
private:
    int id;
    string title;
    string author;
    string category;
    bool available;
    int borrowCount;

public:
    Book();
    Book(int id, string title, string author, string category, bool available = true, int borrowCount = 0);

    int getId() const;
    string getTitle() const;
    string getAuthor() const;
    string getCategory() const;
    bool isAvailable() const;
    int getBorrowCount() const;

    void setAvailable(bool status);
    void increaseBorrowCount();
    string toFileLine() const;
    void display() const;
};

class Member {
private:
    int id;
    string name;
    string email;
    int borrowedBooks;

public:
    Member();
    Member(int id, string name, string email, int borrowedBooks = 0);

    int getId() const;
    string getName() const;
    string getEmail() const;
    int getBorrowedBooks() const;

    void borrowOneBook();
    void returnOneBook();
    string toFileLine() const;
    void display() const;
};

class BorrowRecord {
private:
    int bookId;
    int memberId;
    string action;
    string dateTime;

public:
    BorrowRecord();
    BorrowRecord(int bookId, int memberId, string action, string dateTime);

    int getBookId() const;
    int getMemberId() const;
    string getAction() const;
    string getDateTime() const;
    string toFileLine() const;
    void display() const;
};

class SmartRecommender {
public:
    static void recommendByCategory(const vector<Book>& books, const string& category);
    static void showTrendingBooks(vector<Book> books);
};

class LibrarySystem {
private:
    vector<Book> books;
    vector<Member> members;
    vector<BorrowRecord> records;

    string bookFile;
    string memberFile;
    string recordFile;

    int findBookIndex(int bookId) const;
    int findMemberIndex(int memberId) const;
    string currentDateTime() const;

public:
    LibrarySystem(string bookFile, string memberFile, string recordFile);

    void loadBooks();
    void loadMembers();
    void loadRecords();
    void saveBooks() const;
    void saveMembers() const;
    void saveRecords() const;

    void addBook();
    void addMember();
    void showAllBooks() const;
    void showAllMembers() const;
    void searchBook() const;
    void borrowBook();
    void returnBook();
    void showHistory() const;
    void smartRecommendation() const;
    void analyticsDashboard() const;
    void run();
};

#endif

