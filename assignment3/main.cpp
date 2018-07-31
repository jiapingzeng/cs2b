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
    virtual int EarnPoints();
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
    Transaction transactions_[g_kArraySize];
    int array_count_;
public:
    Customer();
    Customer(string name, string card_number, double balance, int reward_points);
    ~Customer();
    void ReadTransactions(string path);
    void ReportAllTransactions();
    void ReportRewardSummary();
};

class DepartmentStoreTransaction: public Transaction {
private:
    string department_name_;
    int return_days_;
    const int kPointsPerDollar = 1.5;
public:
    DepartmentStoreTransaction();
    DepartmentStoreTransaction(string department_name, int return_days);
    virtual ~DepartmentStoreTransaction();
    virtual void Display();
    virtual int EarnPoints();
    string get_department_name();
    int get_return_days();
    void set_department_name(string department_name);
    void set_return_days(int return_days);
};

class BankingTransaction: public Transaction {
private:
    string type_;
    double fee_;
    const int kPointsPerDollar = 0;
public:
    BankingTransaction();
    BankingTransaction(string type, double fee);
    virtual ~BankingTransaction();
    virtual void Display();
    virtual int EarnPoints();
    string get_type();
    double get_fee();
    void set_type(string type);
    void set_fee(double fee);
};

class GroceryTransaction: public Transaction {
private:
    string store_name_;
    const int kPointsPerDollar = 2.5;
public:
    GroceryTransaction();
    GroceryTransaction(string store_name);
    virtual ~GroceryTransaction();
    virtual void Display();
    virtual void EarnPoints();
    string get_store_name();
    void set_store_name(string store_name);
};

int main() {
    // TODO: write revision history
    // TODO: const
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

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
        reward_points_(1000),
        array_count_(0) {
    for (int i = 0; i < g_kArraySize; ++i) {
        transactions_[i] = nullptr;
    }
}

Customer::Customer(string name, string card_number, double balance, int reward_points):
        name_(name),
        card_number_(card_number),
        balance_(balance),
        reward_points_(reward_points),
        array_count_(0) {
    for (int i = 0; i < g_kArraySize; ++i) {
        transactions_[i] = nullptr;
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

    string field;

    while (getline(ifs, field, '~')) {
        Transaction * transaction = nullptr;

        char transaction_type = field[0];

        getline(ifs, field, '~');
        string date = field;

        getline(ifs, field, '~');
        int id = atoi(field.c_str());

        getline(ifs, field, '~');
        double amount = atof(field.c_str());

        switch (transaction_type) {
            case 'B':
                getline(ifs, field, '~');
                string type = field;
                getline(ifs, field, '~');
                double fee = atof(field.c_str());
                transaction = new BankingTransaction(date, id, amount,
                        type, fee);
                break;
            case 'D':
                getline(ifs, field, '~');
                string department_name = field;
                getline(ifs, field, '~');
                int return_days = atoi(field.c_str());
                transaction = new DepartmentStoreTransaction(date, id, amount,
                        department_name, return_days);
                break;
            case 'G':
                getline(ifs, field, '~');
                string store_name = field;
                transaction = new GroceryTransaction(date, id, amount,
                        store_name);
                break;
        }

        if (transaction) {
            transactions_[array_count_++] = transaction;
        } else {
            cout << "Error occurred when processing data file" << endl;
            exit(-1);
        }
    }
}

//endregion

//region class DepartmentStoreTransaction definitions

DepartmentStoreTransaction::DepartmentStoreTransaction():
        Transaction(),
        department_name_("Nameless department"),
        return_days_(0) {}

DepartmentStoreTransaction::DepartmentStoreTransaction(string date, int id, double amount,
                                                       string department_name, int return_days):
        Transaction(date, id, amount),
        department_name_(department_name),
        return_days_(return_days) {}

DepartmentStoreTransaction::~DepartmentStoreTransaction() {
    cout << "Department store transaction destroyed" << endl;
}

void DepartmentStoreTransaction::Display() {
    cout << "Department store transaction" << endl;
}

int DepartmentStoreTransaction::EarnPoints() {
    return floor(amount_ * kPointsPerDollar);
}

string DepartmentStoreTransaction::get_department_name() {
    return department_name_;
}

int DepartmentStoreTransaction::get_return_days() {
    return return_days_;
}

void DepartmentStoreTransaction::set_department_name(string department_name) {
    department_name_ = department_name;
}

void DepartmentStoreTransaction::set_return_days(int return_days) {
    return_days_ = return_days;
}

//endregion

//region class BankingTransaction definitions

BankingTransaction::BankingTransaction():
        Transaction(),
        type_("Look ma no fees"),
        fee_(0.0) {}

BankingTransaction::BankingTransaction(string date, int id, double amount,
                                       string type, double fee):
        Transaction(date, id, amount),
        type_(type),
        fee_(fee) {}

BankingTransaction::~BankingTransaction() {
    cout << "Banking transaction destroyed" << endl;
}

void BankingTransaction::Display() {
    cout << "Banking transaction" << endl;
}

int BankingTransaction::EarnPoints() {
    return floor(amount_ * kPointsPerDollar);
}

string BankingTransaction::get_type() {
    return type_;
}

double BankingTransaction::get_fee() {
    return fee_;
}

void BankingTransaction::set_type(string type) {
    type_ = type;
}

void BankingTransaction::set_fee(double fee) {
    fee_ = fee;
}

//endregion

//region class GroceryTransaction definitions

GroceryTransaction::GroceryTransaction():
        Transaction(),
        store_name_("A store has no name") {}

GroceryTransaction::GroceryTransaction(string date, int id, double amount,
                                       string store_name):
        Transaction(date, id, amount),
        store_name_(store_name) {}

GroceryTransaction::~GroceryTransaction() {
    cout << "Grocery transaction destroyed" << endl;
}

void GroceryTransaction::Display() {
    cout << "Grocery transaction" << endl;
}

int GroceryTransaction::EarnPoints() {
    return floor(amount_ * kPointsPerDollar);
}

string GroceryTransaction::get_store_name() {
    return store_name_;
}

void GroceryTransaction::set_store_name(string store_name) {
    store_name_ = store_name;
}

//endregion