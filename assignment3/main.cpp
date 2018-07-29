//=====================================================================================
// Name           : main.cpp
// Author         : Jiaping Zeng
// Date           : Summer 2018
// Version        : 1.0
// Program purpose:

// Revisions history:
//=====================================================================================

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int g_kArraySize = 16;

class Transaction {
protected:
    string date_;
    int id_;
    double amount_;
public:
    Transaction();
    Transaction(string date, int id, double amount);
    virtual ~Transaction();
    bool operator== (Transaction other);
    virtual void Display();
    virtual void EarnPoints();
    string get_date() const;
    int get_id() const;
    double get_amount() const;
    void set_date(string date);
    void set_id(int id);
    void set_amount(double amount);
};

class Customer {
private:
    string name_;
    string card_number_;
    double balance_;
    int reward_points_;
    Transaction transactions[g_kArraySize];
public:
    Customer();
    Customer(string name, string card_number, double balance, int reward_points);
    ~Customer();
    void ReadTransactions(string path);
    void ReportAllTransactions();
    void ReportRewardSummary();
};

int main() {
    // TODO: write revision history
    // TODO: const
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

class DepartmentStoreTransaction: public Transaction {

};

class BankingTransaction: public Transaction {

};

class GroceryTranscation: public Transaction {

};

// region class Transaction definitions

Transaction::Transaction(): date_("01/01/2000"), id_(0), amount_(0.0) {}

Transaction::Transaction(string date, int id, double amount): date_(date), id_(id), amount_(amount) {}

Transaction::~Transaction() {
    cout << "Transaction " << id_ << " destroyed"    << endl;
}

bool Transaction::operator==(Transaction other) {
    return date_ == other.get_date() && amount_ == other.get_amount();
}

string Transaction::get_date() const { return date_; }

int Transaction::get_id() const { return id_; }

double Transaction::get_amount() const { return amount_; }

void Transaction::set_date(string date) { date_ = date; }

void Transaction::set_id(int id) { id_ = id; }

void Transaction::set_amount(double amount) { amount_ = amount; }

//endregion

//region class Customer definitions

Customer::Customer():
        name_("Mr. No name"),
        card_number_("0000000000000000"),
        balance_(0.0),
        reward_points_(1000) {
    for (int i = 0; i < g_kArraySize; ++i) {
        transactions[i] = nullptr;
    }
}

Customer::Customer(string name, string card_number, double balance, int reward_points):
        name_(name),
        card_number_(card_number),
        balance_(balance),
        reward_points_(reward_points) {
    for (int i = 0; i < g_kArraySize; ++i) {
        transactions[i] = nullptr;
    }
}

Customer::~Customer() {
    for (int i = 0; i < g_kArraySize; ++i) {
        delete transactions[i];
    }
}

void Customer::ReadTransactions(string path) {
    cout << "Reading transactions..." << endl;
    ifstream ifs (path);
    if (!ifs) {
        cout << "Error opening file" << endl;
        exit(-1);
    }
    char transaction_type;
    string date;
    int id = 0;
    double amount;
    string field;
    while (getline(ifs, field, '~')) {
        transaction_type = field[0];

        getline(ifs, field, '~');
        date = field;

        getline(ifs, field, '~');
        id = atoi(field.c_str());

        getline(ifs, field, '~');
        amount = atof(field.c_str());

        switch (transaction_type) {
            case 'D':
            case 'd':

        }
    }
}

//endregion