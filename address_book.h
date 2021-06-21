#ifndef ADDRESS_BOOK_H
#define ADDRESS_BOOK_H

#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <ctime>
#include<stdio.h>
#include <cstdio>
#include "contact.h"

class address_book
{
public:
    address_book(string filename);
    void load();
    void add_contact();
    void add_contact(string f_name, string l_name = "noname",
                     string bday = "none", string p_numb = "none",
                     string email = "none");
    void save();
    void show_all();
    void edit(string uniq_id);
    void filter(string key_substr);
    void find_bday();

private:
    vector <contact> all_contacts;
    vector <contact>::iterator index;
    string contact_list_file;
    string backup_temp_file;

    void backup();
    void restore_from_bp();
};

#endif // ADDRESS_BOOK_H
