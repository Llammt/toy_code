#include "contact.h"

contact::contact(string uniq_id, string f_name, string l_name, string bday, string p_numb, string email):
  id(uniq_id),
  first_name(f_name),
  last_name(l_name),
  birthday(bday),
  phone_number(p_numb),
  email(email)
{}

contact::contact(const contact &c):
  id(c.id),
  first_name(c.first_name),
  last_name(c.last_name),
  birthday(c.birthday),
  phone_number(c.phone_number),
  email(c.email)
{}

contact& contact::operator= (const contact &c){
    id = c.id;
    first_name = c.first_name;
    last_name = c.last_name;
    birthday = c.birthday;
    phone_number = c.phone_number;
    email = c.email;

    return *this;
}
