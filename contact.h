#ifndef CONTACT_H
#define CONTACT_H

#include <iostream>
using namespace std;

class contact
{
public:
    contact(string id = "none", string f_name = "noname",
            string l_name = "noname", string bday = "none",
            string p_numb = "none", string email = "none");
    contact(const contact &c);
    contact& operator= (const contact &c);
    string get_id() {return id;}
    string get_fname() {return first_name;}
    string get_lname() {return last_name;}
    string get_bd() {return birthday;}
    string get_phnumb() {return phone_number;}
    string get_email() {return email;}
    void set_fname(string edited_name) {first_name = edited_name;}
    void set_lname(string edited_name) {last_name = edited_name;}
    void set_bd(string edited_bd) {birthday = edited_bd;}
    void set_phnumb(string edited_phnumb) {phone_number = edited_phnumb;}
    void set_email(string edited_email) {email = edited_email;}

private:
    string id;
    string first_name;
    string last_name;
    string birthday;
    string phone_number;
    string email;
};

#endif // CONTACT_H
