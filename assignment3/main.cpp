//=====================================================================================
// Name           : main.cpp
// Author         : Jiaping Zeng
// Date           : Summer 2018
// Version        : 1.0
// Program purpose: report a customer's credit card's monthly purchase transactions

// Revisions history:
//     7/23: implemented template for Transaction and Customer
//     7/24: implemented Transaction definitions and some Customer definitions
//     7/26: implemented the three specific transaction classes and ReadTransactions
//     7/27: implemented the two report functions in Customer
//     7/29: defined main method and tested existing classes
//     7/30: implemented ReportDuplicateTransactions
//     7/31: revised format for output
//=====================================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

const int g_kArraySize = 16;
const string line = string(60, '-');
const string hr = string(80, '-');

class Transaction {
protected:
    string date_;
    int id_;
    double amount_;
public:
    Transaction();
    Transaction(string date, int id, double amount);
    virtual ~Transaction();
    bool operator== (const Transaction & other) const;
    virtual void Display() const = 0;
    virtual int EarnPoints() const = 0;
    string get_date() const;
    int get_id() const;
    double get_amount() const;
    void set_date(string date);
    void set_id(int id);
    void set_amount(double amount);
};

class DepartmentStoreTransaction: public Transaction {
private:
    string department_name_;
    int return_days_;
    const double kPointsPerDollar = 1.5;
public:
    DepartmentStoreTransaction();
    DepartmentStoreTransaction(string date, int id, double amount,
                               string department_name, int return_days);
    virtual ~DepartmentStoreTransaction();
    virtual void Display() const;
    virtual int EarnPoints() const;
    string get_department_name() const;
    int get_return_days() const;
    void set_department_name(string department_name);
    void set_return_days(int return_days);
};

class BankingTransaction: public Transaction {
private:
    string type_;
    double fee_;
public:
    BankingTransaction();
    BankingTransaction(string date, int id, double amount,
                       string type, double fee);
    virtual ~BankingTransaction();
    virtual void Display() const;
    virtual int EarnPoints() const;
    string get_type() const;
    double get_fee() const;
    void set_type(string type);
    void set_fee(double fee);
};

class GroceryTransaction: public Transaction {
private:
    string store_name_;
    const double kPointsPerDollar = 2.5;
public:
    GroceryTransaction();
    GroceryTransaction(string date, int id, double amount,
                       string store_name);
    virtual ~GroceryTransaction();
    virtual void Display() const;
    virtual int EarnPoints() const;
    string get_store_name() const;
    void set_store_name(string store_name);
};

class Customer {
private:
    string name_;
    string card_number_;
    double balance_;
    int reward_points_;
    Transaction * transactions_[g_kArraySize];
    int array_count_;
public:
    Customer();
    Customer(string name, string card_number, double balance, int reward_points);
    ~Customer();
    void ReadTransactions(string path);
    void ReportAllTransactions() const;
    void ReportRewardSummary();
    void ReportDuplicateTransactions() const;
};

int main() {
    Customer * small_town_girl = new Customer("Robin Robinson", "2234098115363135", 20000.00, 500);

    cout << "Reading transactions: " << endl;
    small_town_girl->ReadTransactions("in.txt");
    cout << endl << "Finished reading transactions" << endl;
    cout << hr << endl;

    cout << "Generating report: " << endl << endl;
    small_town_girl->ReportAllTransactions();
    cout << endl << "Finished generating report" << endl;
    cout << hr << endl;

    cout << "Generating reward summary: " << endl << endl;
    small_town_girl->ReportRewardSummary();
    cout << endl << "Finished generating reward summary" << endl;
    cout << hr << endl;

    cout << "Testing == operator overloading: " << endl << endl;
    // Even though these two transactions are different, the current criteria
    // for transaction comparison is same date and amount, which these satisfy
    BankingTransaction trans1 = BankingTransaction("04/01/2018", 1234, 100.0, "ATM", 0.0);
    GroceryTransaction trans2 = GroceryTransaction("04/01/2018", 1234, 100.0, "Floormart");
    // same amount but different date as first two
    BankingTransaction trans3 = BankingTransaction("11/11/2011", 1234, 100.0, "CASH", 0.0);
    // same date but different amount as first two
    BankingTransaction trans4 = BankingTransaction("04/01/2018", 1234, 99.99, "CASH", 0.0);
    cout << "Transaction 1: ";
    trans1.Display();
    cout << "Transaction 2: ";
    trans2.Display();
    cout << "Transaction 3: ";
    trans3.Display();
    cout << "Transaction 4: ";
    trans4.Display();
    cout << "Comparing transactions (1 = true, 0 = false):" << endl;
    cout << "transactions 1 and 2: " << (trans1 == trans2) << endl;
    cout << "transactions 1 and 3: " << (trans1 == trans3) << endl;
    cout << "transactions 1 and 4: " << (trans1 == trans4) << endl;
    cout << endl << "Finished testing ==" << endl;
    cout << hr << endl;

    cout << "Generating duplicate transactions report: " << endl << endl;
    small_town_girl->ReportDuplicateTransactions();
    cout << endl << "Finished generating duplicate transactions report" << endl;
    cout << hr << endl;

    delete small_town_girl;
    return 0;
}

// region class Transaction definitions

Transaction::Transaction():
        date_("01/01/2000"),
        id_(0),
        amount_(0.0) {}

Transaction::Transaction(string date, int id, double amount):
        date_(date),
        id_(id),
        amount_(amount) {}

Transaction::~Transaction() {
    cout << "Transaction " << id_ << " destroyed" << endl;
}

bool Transaction::operator==(const Transaction & other) const {
    return date_ == other.get_date() && amount_ == other.get_amount();
}

string Transaction::get_date() const {
    return date_;
}

int Transaction::get_id() const {
    return id_;
}

double Transaction::get_amount() const {
    return amount_;
}

void Transaction::set_date(string date) {
    date_ = date;
}

void Transaction::set_id(int id) {
    id_ = id;
}

void Transaction::set_amount(double amount) {
    amount_ = amount;
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

void DepartmentStoreTransaction::Display() const {
    cout << left;
    cout << setw(12) << date_;
    cout << setw(20) << "Department Store";
    cout << setw(30) << department_name_ + ", return in " + to_string(return_days_) + " days";
    cout << "$" << amount_ << endl;
}

int DepartmentStoreTransaction::EarnPoints() const {
    return static_cast<int>(floor(amount_ * kPointsPerDollar));
}

string DepartmentStoreTransaction::get_department_name() const {
    return department_name_;
}

int DepartmentStoreTransaction::get_return_days() const {
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

void BankingTransaction::Display() const {
    cout << left;
    cout << setw(12) << date_;
    cout << setw(20) << "Banking";
    cout << setw(30) << type_ + " withdraw";
    cout << "$" << amount_ << endl;
}

int BankingTransaction::EarnPoints() const {
    return 0;
}

string BankingTransaction::get_type() const {
    return type_;
}

double BankingTransaction::get_fee() const {
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

void GroceryTransaction::Display() const {
    cout << left;
    cout << setw(12) << date_;
    cout << setw(20) << "Grocery";
    cout << setw(30) << store_name_;
    cout << "$" << amount_ << endl;
}

int GroceryTransaction::EarnPoints() const {
    return static_cast<int>(floor(amount_ * kPointsPerDollar));
}

string GroceryTransaction::get_store_name() const {
    return store_name_;
}

void GroceryTransaction::set_store_name(string store_name) {
    store_name_ = store_name;
}

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
        delete transactions_[i];
    }
}

void Customer::ReadTransactions(string path) {
    ifstream ifs (path);
    if (!ifs) {
        cout << "Error opening file" << endl;
        exit(-1);
    }
    string field;
    while (getline(ifs, field, '~')) {
        Transaction * trans = nullptr;
        // get transaction type
        char trans_type = field[0];
        // get date of transaction
        getline(ifs, field, '~');
        string date = field;
        // get transaction id
        getline(ifs, field, '~');
        int id = atoi(field.c_str());
        // get amount
        getline(ifs, field, '~');
        double amount = atof(field.c_str());
        // get transaction specific data
        switch (trans_type) {
            case 'B': {
                getline(ifs, field, '~');
                string type = field;
                getline(ifs, field, '\n');
                double fee = atof(field.c_str());
                trans = new BankingTransaction(date, id, amount,
                                               type, fee);
                break;
            }
            case 'D': {
                getline(ifs, field, '~');
                string department_name = field;
                getline(ifs, field, '\n');
                int return_days = atoi(field.c_str());
                trans = new DepartmentStoreTransaction(date, id, amount,
                                                       department_name, return_days);
                break;
            }
            case 'G': {
                getline(ifs, field, '\n');
                string store_name = field;
                trans = new GroceryTransaction(date, id, amount,
                                               store_name);
                break;
            }
        }
        // append transaction to array
        if (trans) {
            balance_ -= trans->get_amount();
            transactions_[array_count_++] = trans;
        } else {
            cout << "Error occurred when processing data file" << endl;
            exit(-1);
        }
    }
    ifs.close();
}

void Customer::ReportAllTransactions() const {
    cout << left;
    cout << setprecision(2) << fixed;
    cout << "Transactions Listings" << endl;
    Transaction * trans = nullptr;
    BankingTransaction * bank_trans = nullptr;
    DepartmentStoreTransaction * dprt_trans = nullptr;
    GroceryTransaction * groc_trans = nullptr;
    double total_fee = 0.0;
    int bank_count = 0;
    int dprt_count = 0;
    int groc_count = 0;
    double bank_total = 0.0;
    double dprt_total = 0.0;
    double groc_total = 0.0;
    for (int i = 0; i < array_count_; ++i) {
        trans = transactions_[i];
        trans->Display();
        if ((bank_trans = dynamic_cast<BankingTransaction *>(trans))) {
            bank_count++;
            bank_total += bank_trans->get_amount();
            total_fee += bank_trans->get_fee();
        } else if ((dprt_trans = dynamic_cast<DepartmentStoreTransaction *>(trans))) {
            dprt_count++;
            dprt_total += dprt_trans->get_amount();
        } else if ((groc_trans = dynamic_cast<GroceryTransaction *>(trans))) {
            groc_count++;
            groc_total += groc_trans->get_amount();
        }
    }
    int kColWidth = 20;
    cout << line << endl;
    cout << setw(kColWidth) << "Total fee charge: " << "$" << total_fee << endl;
    cout << setw(kColWidth) << "Total balance: " << "$" << balance_ << endl;
    cout << endl << "Transaction Summary" << endl;
    cout << setw(kColWidth) << "Transaction type";
    cout << setw(kColWidth) << "Transaction count";
    cout << "Total purchase" << endl;
    cout << setw(kColWidth) << "Department Store";
    cout << setw(kColWidth) << dprt_count;
    cout << "$" << dprt_total << endl;
    cout << setw(kColWidth) << "Banking";
    cout << setw(kColWidth) << bank_count;
    cout << "$" << bank_total << endl;
    cout << setw(kColWidth) << "Grocery";
    cout << setw(kColWidth) << groc_count;
    cout << "$" << groc_total << endl;
    cout << line << endl;
    cout << string(2 * kColWidth, ' ') << "$";
    cout << dprt_total + bank_total + groc_total << endl;
}

void Customer::ReportRewardSummary() {
    const int kColWidth = 30;
    cout << left;
    cout << "Reward Summary for " << name_ << " " << card_number_.substr(12) << endl;
    cout << setw(kColWidth) << "Previous points balance" << reward_points_ << endl;
    Transaction * trans = nullptr;
    DepartmentStoreTransaction * dprt_trans = nullptr;
    GroceryTransaction * groc_trans = nullptr;
    int dprt_reward = 0;
    int groc_reward = 0;
    for (int i = 0; i < array_count_; ++i) {
        trans = transactions_[i];
        if ((dprt_trans = dynamic_cast<DepartmentStoreTransaction *>(trans))) {
            dprt_reward += dprt_trans->EarnPoints();
        } else if ((groc_trans = dynamic_cast<GroceryTransaction *>(trans))) {
            groc_reward += groc_trans->EarnPoints();
        }
    }
    cout << left << setw(kColWidth) << "+ Department store purchases: " << dprt_reward << endl;
    cout << setw(kColWidth) << "+ Grocery purchases: " << groc_reward << endl;
    cout << line << endl;
    reward_points_ += dprt_reward + groc_reward;
    cout << setw(kColWidth) << "= Total points available" << reward_points_ << endl;
}

void Customer::ReportDuplicateTransactions() const {
    int kCOlWidth = 20;
    cout << "Duplicate Transaction Report" << endl;
    cout << setw(kCOlWidth) << "Transaction type";
    cout << setw(kCOlWidth) << "Date";
    cout << setw(kCOlWidth) << "Amount";
    cout << "Transaction ID" << endl;
    for (int i = 0; i < array_count_; ++i) {
        Transaction * trans = transactions_[i];
        for (int j = i + 1; j < array_count_; ++j) {
            Transaction * other_trans = transactions_[j];
            if (trans->get_id() != other_trans->get_id() // ensure transactions have different ids
                && *trans == *other_trans) {             // check if they have same date & amount
                string trans_type = "";
                // eliminated transactions with different date & amount,
                // now try casting the two transactions to the same types
                if (dynamic_cast<BankingTransaction *>(trans)
                    && dynamic_cast<BankingTransaction *>(other_trans)) {
                    trans_type = "Banking";
                } else if (dynamic_cast<GroceryTransaction *>(trans)
                           && dynamic_cast<GroceryTransaction *>(other_trans)) {
                    trans_type = "Grocery";
                } else if (dynamic_cast<DepartmentStoreTransaction *>(trans)
                           && dynamic_cast<DepartmentStoreTransaction *>(other_trans)) {
                    trans_type = "Department Store";
                }
                if (trans_type != "") {
                    cout << setw(kCOlWidth) << trans_type;
                    cout << setw(kCOlWidth) << trans->get_date();
                    cout << "$" << setw(kCOlWidth - 1) << trans->get_amount();
                    cout << trans->get_id() << endl;
                    cout << setw(kCOlWidth) << trans_type;
                    cout << setw(kCOlWidth) << other_trans->get_date();
                    cout << "$" << setw(kCOlWidth - 1) << other_trans->get_amount();
                    cout << other_trans->get_id() << endl;
                }
            }
        }
    }
}

//endregion