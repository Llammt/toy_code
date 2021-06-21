#include "contact.h"
#include "address_book.h"

int main() {
    string main_filename = "Address_Book.csv";
    address_book first_book(main_filename);
    cout << "Loading contact list..." << endl;
    first_book.load();
    cout << endl << "Show all contacts" << endl;
    first_book.show_all();
    cout << endl << "Adding new record" << endl;
    first_book.add_contact();
    cout << endl << "Show all contacts" << endl;
    first_book.show_all();
    cout << endl << "Try to find a record using substring. Enter your substring: " << endl;
    string ss; getline( cin, ss);
    if (!ss.empty()) first_book.filter(ss);
    cout << "Edit record by id: " << endl;
    first_book.edit("0");
    cout << endl << "Let's find a birtday boys\\girls: " << endl;
    first_book.find_bday();
    cout << endl << "It's time for save all changes and exit" << endl;
    first_book.save();
    return 0;
}
