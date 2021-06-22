#include "contact.h"
#include "address_book.h"
#include <boost/program_options.hpp>
namespace po = boost::program_options;

int main(int argc, char** argv) {
    string main_filename = "Address_Book.csv";
    address_book first_book(main_filename);
    string sub_string;

    po::options_description desc ("Allowed options");
    desc.add_options ()
        ("help,h", "print usage message")
        ("show,s", "show all contacts")
        ("filter,f", po::value(&sub_string), "filter by sub-string")
        ("new,n", "Add new record with interactive input")
        ("edit,e", "Edit record by unique id (3)")
        ("bday,b", "Let's find a birtday boys\\girls :)");
    po::variables_map vm;
    po::store (po::command_line_parser (argc, argv).options (desc).run (), vm);
    po::notify (vm);
    if (vm.count("show")){
        cout << endl << "Show all contacts" << endl;
        first_book.show_all();
    } else if (vm.count("filter")) {
        first_book.filter(sub_string);
    } else if (vm.count("new")) {
        first_book.add_contact();
        first_book.save();
    } else if (vm.count("edit")) {
        first_book.edit("3");
        first_book.save();
    } else if (vm.count("bday")) {
        first_book.find_bday();
    } else if(vm.count("help") || !vm.count("show") || !vm.count("filter") || !vm.count("new")
               || !vm.count("edit") || !vm.count("bday")) {
        cout << "USE: --show or -s to see all records in file;" << endl
             << "-- filter or -f to filter records using substring;" << endl
             << "--new or -n to add a record;" << endl
             << "--edit or -e to edit a record;" << endl
             << "--bday or -b to find a birthday person;" << endl;
    }
    return 0;
}
