#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Book class to represent a book in the library
class Book {
    string isbn, title, author, edition, publication, genre;
    bool isIssued;

public:
    // Constructor to initialize a book object
    Book(string a, string b, string c, string d, string e, string f)
        : isbn(a), title(b), author(c), edition(d), publication(e), genre(f), isIssued(false) {}

    string getIsbn() { 
        return isbn; 
        
    }
    string getTitle() { 
        return title; 
        
    }
    string getAuthor() { 
        return author; 
        
    }
    string getEdition() { 
        return edition; 
        
    }
    string getPublication() { 
        return publication; 
        
    }
    string getGenre() { 
        return genre; 
        
    }
    bool getIsIssued() { 
        return isIssued; 
        
    }

    void issueBook() { 
        isIssued = true; 
        
    }
    void returnBook() { 
        isIssued = false; 
        
    }

    void displayBookInfo() {
        cout << "ISBN: " << isbn << "\nTitle: " << title << "\nAuthor: " << author
             << "\nEdition: " << edition << "\nPublication: " << publication
             << "\nGenre: " << genre << "\nIs Issued: " << (isIssued ? "Yes" : "No") << "\n" << endl;
    }
};

// Member class to represent a library member
class Member {
    int memberID;
    string name;
    vector<string> issuedBooks; // List of issued book ISBNs

public:
    // Constructor to initialize a member object
    Member(int id, string n) : memberID(id), name(n) {}

    int getMemberID() { return memberID; }
    string getName() { return name; }
    vector<string> getIssuedBooks() { return issuedBooks; }

    // Function to issue a book to the member
    void issueBook(string isbn) { issuedBooks.push_back(isbn); }

    // Function to return a book from the member
    void returnBook(string isbn) {
        auto it = find(issuedBooks.begin(), issuedBooks.end(), isbn);
        if (it != issuedBooks.end()) {
            issuedBooks.erase(it);
        }
    }

    // Function to display member information
    void displayMemberInfo() {
        cout << "Member ID: " << memberID << "\nName: " << name << "\nIssued Books: ";
        for (string book : issuedBooks) {
            cout << book << " ";
        }
        cout << "\n" << endl;
    }
};

// Library class to manage books and members
class Library {
    vector<Book> books; // List of books
    vector<Member> members; // List of members

public:
    // Function to add a book to the library
    void addBook(Book book) { books.push_back(book); }

    // Function to add a member to the library
    void addMember(Member member) { members.push_back(member); }

    // Function to issue a book to a member
    void issueBook(string isbn, int memberID) {
        for (Book &book : books) {
            if (book.getIsbn() == isbn && !book.getIsIssued()) {
                book.issueBook();
                for (Member &member : members) {
                    if (member.getMemberID() == memberID) {
                        member.issueBook(isbn);
                        cout << "Book issued successfully.\n";
                        return;
                    }
                }
            }
        }
        cout << "Book issue failed.\n";
    }

    // Function to return a book from a member
    void returnBook(string isbn, int memberID) {
        for (Book &book : books) {
            if (book.getIsbn() == isbn && book.getIsIssued()) {
                book.returnBook();
                for (Member &member : members) {
                    if (member.getMemberID() == memberID) {
                        member.returnBook(isbn);
                        cout << "Book returned successfully.\n";
                        return;
                    }
                }
            }
        }
        cout << "Book return failed.\n";
    }

    // Function to search books by title
    void searchBookByTitle(string title) {
        bool found = false;
        for (Book &book : books) {
            if (book.getTitle() == title) {
                book.displayBookInfo();
                found = true;
            }
        }
        if (!found) {
            cout << "Book not found.\n";
        }
    }

    // Function to search books by author
    void searchBookByAuthor(string author) {
        bool found = false;
        for (Book &book : books) {
            if (book.getAuthor() == author) {
                book.displayBookInfo();
                found = true;
            }
        }
        if (!found) {
            cout << "Book not found.\n";
        }
    }

    // Function to search books by genre
    void searchBookByGenre(string genre) {
        bool found = false;
        for (Book &book : books) {
            if (book.getGenre() == genre) {
                book.displayBookInfo();
                found = true;
            }
        }
        if (!found) {
            cout << "Book not found.\n";
        }
    }

    // Function to edit book information
    void editBook(string isbn) {
        for (Book &book : books) {
            if (book.getIsbn() == isbn) {
                string title, author, edition, publication, genre;
                cout << "Enter new Title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter new Author: ";
                getline(cin, author);
                cout << "Enter new Edition: ";
                getline(cin, edition);
                cout << "Enter new Publication: ";
                getline(cin, publication);
                cout << "Enter new Genre: ";
                getline(cin, genre);

                book = Book(isbn, title, author, edition, publication, genre);
                cout << "Book edited successfully!\n";
                return;
            }
        }
        cout << "Book not found.\n";
    }

    // Function to remove a book from the library
    void removeBook(string isbn) {
        auto it = remove_if(books.begin(), books.end(), [&](Book &book) { return book.getIsbn() == isbn; });
        if (it != books.end()) {
            books.erase(it, books.end());
            cout << "Book removed successfully.\n";
        } else {
            cout << "Book not found.\n";
        }
    }

    // Function to remove a member from the library
    void removeMember(int memberID) {
        auto it = remove_if(members.begin(), members.end(), [&](Member &member) { return member.getMemberID() == memberID; });
        if (it != members.end()) {
            members.erase(it, members.end());
            cout << "Member removed successfully.\n";
        } else {
            cout << "Member not found.\n";
        }
    }

    // Function to display all books in the library
    void displayAllBooks() {
        for (Book &book : books) {
            book.displayBookInfo();
        }
        if (books.empty()) {
            cout << "No books available.\n";
        }
    }

    // Function to display all members in the library
    void displayAllMembers() {
        for (Member &member : members) {
            member.displayMemberInfo();
        }
        if (members.empty()) {
            cout << "No members available.\n";
        }
    }

    // Function to display all books issued by a specific member
    void displayIssuedBooks(int memberID) {
        for (Member &member : members) {
            if (member.getMemberID() == memberID) {
                member.displayMemberInfo();
                return;
            }
        }
        cout << "Member not found.\n";
    }
};

// Function to display the menu options
void displayMenu() {
    cout << "\nLIBRARY MANAGEMENT SYSTEM \n\n";
    cout << "[1] ADD BOOK \n";
    cout << "[2] ADD MEMBER \n";
    cout << "[3] ISSUE BOOK \n";
    cout << "[4] RETURN BOOK \n";
    cout << "[5] SEARCH BOOK BY TITLE \n";
    cout << "[6] SEARCH BOOK BY AUTHOR \n";
    cout << "[7] SEARCH BOOK BY GENRE \n";
    cout << "[8] EDIT BOOK \n";
    cout << "[9] REMOVE BOOK \n";
    cout << "[10] REMOVE MEMBER \n";
    cout << "[11] DISPLAY ALL BOOKS \n";
    cout << "[12] DISPLAY ALL MEMBERS \n";
    cout << "[13] DISPLAY ISSUED BOOKS \n";
    cout << "[14] QUIT \n";
    cout << "\nENTER CHOICE: ";
}

int main() {
    Library library;

    // Sample books and members
    library.addBook(Book("1111", "The Great Gatsby", "F. Scott Fitzgerald", "1st", "Scribner", "Novel"));
    library.addBook(Book("2222", "To Kill a Mockingbird", "Harper Lee", "1st", "J.B. Lippincott & Co.", "Novel"));
    library.addMember(Member(1, "Marc Samuel"));
    library.addMember(Member(2, "Esperancia Petit-Frère"));

    int choice, memberID;
    string isbn;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                string isbn, title, author, edition, publication, genre;
                cout << "Enter ISBN: ";
                cin >> isbn;
                cout << "Enter Title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter Author: ";
                getline(cin, author);
                cout << "Enter Edition: ";
                getline(cin, edition);
                cout << "Enter Publication: ";
                getline(cin, publication);
                cout << "Enter Genre: ";
                getline(cin, genre);
                library.addBook(Book(isbn, title, author, edition, publication, genre));
                cout << "Book added successfully!\n";
            } break;

            case 2: {
                int memberID;
                string name;
                cout << "Enter Member ID: ";
                cin >> memberID;
                cout << "Enter Name: ";
                cin.ignore();
                getline(cin, name);
                library.addMember(Member(memberID, name));
                cout << "Member added successfully!\n";
            } break;

            case 3:
                cout << "Enter ISBN of the book to issue: ";
                cin >> isbn;
                cout << "Enter Member ID: ";
                cin >> memberID;
                library.issueBook(isbn, memberID);
                break;

            case 4:
                cout << "Enter ISBN of the book to return: ";
                cin >> isbn;
                cout << "Enter Member ID: ";
                cin >> memberID;
                library.returnBook(isbn, memberID);
                break;

            case 5: {
                string title;
                cout << "Enter title of the book: ";
                cin.ignore();
                getline(cin, title);
                library.searchBookByTitle(title);
            } break;

            case 6: {
                string author;
                cout << "Enter author of the book: ";
                cin.ignore();
                getline(cin, author);
                library.searchBookByAuthor(author);
            } break;

            case 7: {
                string genre;
                cout << "Enter genre of the book: ";
                cin.ignore();
                getline(cin, genre);
                library.searchBookByGenre(genre);
            } break;

            case 8:
                cout << "Enter ISBN of the book to edit: ";
                cin >> isbn;
                library.editBook(isbn);
                break;

            case 9:
                cout << "Enter ISBN of the book to remove: ";
                cin >> isbn;
                library.removeBook(isbn);
                break;

            case 10:
                cout << "Enter Member ID to remove: ";
                cin >> memberID;
                library.removeMember(memberID);
                break;

            case 11:
                library.displayAllBooks();
                break;

            case 12:
                library.displayAllMembers();
                break;

            case 13:
                cout << "Enter Member ID to display issued books: ";
                cin >> memberID;
                library.displayIssuedBooks(memberID);
                break;

            case 14:
                cout << "Exiting Library Management System. Goodbye!\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
