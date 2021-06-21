#include "address_book.h"

address_book::address_book(string filename):
  contact_list_file(filename)
{}

void address_book::load(){
    ifstream input_info;
    backup();
    input_info.open(contact_list_file);
    if(!input_info.is_open()) {
        cerr << "Can't load contacts." << endl;
        exit(0);
    }
    string record;
    while(getline(input_info, record)){
        istringstream s(record);
        string field;
        vector <string> contact_fields;
        while (getline(s, field,',')){
            contact_fields.push_back(field);
        }
        all_contacts.push_back(contact(contact_fields[0], contact_fields[1], contact_fields[2], contact_fields[3], contact_fields[4], contact_fields[5])); //ну такое себе =(
    }
    if(all_contacts.empty()) cout << "No records exist. Wanna add some? :)" << endl;

    input_info.close();
}

void address_book::add_contact(){
    string temp_fname, temp_lname, temp_bd, temp_pnumb, temp_email;
    cout << "Please, enter your first and last name: " << endl;
    cin >> temp_fname >> temp_lname;
    cout << "Enter your birtdate: " << endl; cin >> temp_bd;
    cout << "Enter your phone number: " << endl; cin >> temp_pnumb;
    cout << "Enter your email: " << endl; cin >> temp_email;
    string t_id = to_string(all_contacts.size());
    all_contacts.push_back(contact(t_id, temp_fname, temp_lname, temp_bd, temp_pnumb, temp_email));
}

void address_book::add_contact(string temp_fname, string temp_lname, string temp_bd, string temp_pnumb, string temp_email){
    string t_id = to_string(all_contacts.size());
    all_contacts.push_back(contact(t_id, temp_fname, temp_lname, temp_bd, temp_pnumb, temp_email));
}

void address_book::save(){
    cout << "Do you want to save changes? (yes\\no)" << endl;
    string answ;
    cin >> answ;
    if (answ == "yes") {
        ofstream output_info;
        output_info.open(contact_list_file);
        if(!output_info.is_open()){
            cerr << "Can't open file. Your changes could not be saved!" << endl;
            restore_from_bp();
            exit(0);
        };

        for (index = all_contacts.begin(); index != all_contacts.end(); ++index){
            output_info << index->get_id() << ',';
            output_info << index->get_fname() << ',';
            output_info << index->get_lname() << ',';
            output_info << index->get_bd() << ',';
            output_info << index->get_phnumb() << ',';
            output_info << index->get_email() << '\n';
        }
        output_info.close();
        remove(backup_temp_file.c_str());
    }
    else if (answ == "no") restore_from_bp();
}

void address_book::show_all() {
    for (index = all_contacts.begin(); index != all_contacts.end(); ++index){
        cout << index->get_id() << '\t';
        cout << index->get_fname() << '\t';
        cout << index->get_lname() << '\t';
        cout << index->get_bd() << '\t';
        cout << index->get_phnumb() << '\t';
        cout << index->get_email() << endl;
    }
}

void address_book::edit(string uniq_id){
    string edit;
    index = find_if (all_contacts.begin(), all_contacts.end(), [&](contact& record){return record.get_id() == uniq_id;});
    cout << index->get_fname() << endl;

    contact changes = (*index);

    cout << index->get_fname() << "   >  "; getline( cin, edit );
    if (!edit.empty()) changes.set_fname(edit);

    cout << index->get_lname() << "   >  "; getline( cin, edit );
    if (!edit.empty()) changes.set_lname(edit);

    cout << index->get_bd() << "   >  "; getline( cin, edit );
    if (!edit.empty()) changes.set_bd(edit);

    cout << index->get_phnumb() << "   >  "; getline( cin, edit );
    if (!edit.empty()) changes.set_phnumb(edit);

    cout << index->get_email() << "   >  "; getline( cin, edit );
    if (!edit.empty()) changes.set_email(edit);

    cout << "Let's check this record: " << endl;
    cout << changes.get_id() << '\t';
    cout << changes.get_fname() << '\t';
    cout << changes.get_lname() << '\t';
    cout << changes.get_bd() << '\t';
    cout << changes.get_phnumb() << '\t';
    cout << changes.get_email() << endl;

    cout << "Accept? (yes\\no)" << endl;
    edit.clear();
    while(edit.empty()){
        getline( cin, edit);
        if (edit == "yes") (*index) = changes;
        else if (edit != "no") edit.clear();
    }
}

void address_book::filter(string key_substr){
    index = all_contacts.begin();
    while (index < all_contacts.end()) {
        index = find_if (index, all_contacts.end(), [&](contact& record){ return
                record.get_fname().find(key_substr) != string::npos ||
                record.get_lname().find(key_substr) != string::npos ||
                record.get_bd().find(key_substr) != string::npos ||
                record.get_phnumb().find(key_substr) != string::npos ||
                record.get_email().find(key_substr) != string::npos; });
        cout << endl << index->get_fname() << '\t' << index->get_lname() << '\t' <<
                index->get_bd() << '\t' << index->get_phnumb() << '\t' <<
                index->get_email() << endl;
        ++index;
    }
}

void address_book::find_bday(){
    time_t t = std::time(0);
    tm* now = std::localtime(&t);
    string today = to_string(now->tm_mday) + ".0" + to_string(now->tm_mon + 1);
    //std::cout << today << std::endl;
    index = all_contacts.begin();
    while (index < all_contacts.end()) {
        index = find_if (all_contacts.begin(), all_contacts.end(), [&](contact& record){return record.get_bd() == today;});
        cout << endl << index->get_fname() << '\t' << index->get_lname() << '\t' <<
                index->get_bd() << '\t' << index->get_phnumb() << '\t' << index->get_email() << endl;
        ++index;
    }
}

void address_book::backup(){
    backup_temp_file = "temp.csv";
    ifstream  main_file(contact_list_file, std::ios::binary);
    ofstream  backup_file(backup_temp_file,   std::ios::binary);
    backup_file << main_file.rdbuf();

    main_file.close();
    backup_file.close();
}

void address_book::restore_from_bp(){
    fstream backup_file;
    backup_file.open(backup_temp_file);
    if(!backup_file.is_open()) cerr << "Can't load backup file. We have a problem(((" << endl;
    else {
        if (remove(contact_list_file.c_str()) == 0) {
            int result = rename(backup_temp_file.c_str() , contact_list_file.c_str());
            if (result == 0) cout << "Your old data successfully restored"  << endl;
            else cerr << "Error restoring data" << endl;
        }
        else cerr << "We have a BIG problem! O_o" << endl;
    }
}
