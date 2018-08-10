//=====================================================================================
// Name           : main.cpp
// Author         : Jiaping Zeng
// Date           : Summer 2018
// Version        : 1.0
// Program purpose: An inventory management system for an electronic store

// Revisions history:
//     7/20: Implemented InventorySystem, InventoryItem and Product classes
//     7/21: Implemented main method and revised output format
//=====================================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

typedef enum { pcNew, pcUsed, pcRefurbished, pcDefective } T_ProductCondition;

string ConditionToString(T_ProductCondition condition) {
    switch (condition) {
        case pcNew: return "New";
        case pcUsed: return "Used";
        case pcRefurbished: return "Refurbished";
        case pcDefective: return "Defective";
        default: return "New";
    }
}

char ConditionToChar(T_ProductCondition condition) {
    return ConditionToString(condition)[0];
}

class InventoryItem {
protected:
    string name_; // name of item
    int quantity_; // quantity of item
public:
    // constructors/destructor
    InventoryItem();
    InventoryItem(string name, int quantity);
    virtual ~InventoryItem();
    // accessors
    string get_name() const;
    int get_quantity() const;
    // mutators
    void set_name(string name);
    void set_quantity(int quantity);
    // other functions
    virtual void Display() const;
};

class Product: public InventoryItem {
private:
    int id_;
    double price_;
    T_ProductCondition condition_;
public:
    // constructors/destructor
    Product();
    Product(string name, int quantity, double price, T_ProductCondition condition);
    virtual ~Product();
    // accessors
    int get_id() const;
    double get_price() const;
    T_ProductCondition get_condition() const;
    // mutators
    void set_id(int id);
    void set_price(double price);
    void set_condition(T_ProductCondition condition);
    // other functions
    virtual void Display() const;
};

class InventorySystem {
private:
    string name_;
    int id_;
    InventoryItem * items_[512] = {NULL};
    int item_count_;
public:
    // constructors/destructor
    InventorySystem();
    InventorySystem(string name, int id);
    ~InventorySystem();
    // accessors
    string get_name() const;
    int get_id() const;
    int get_item_count() const;
    // mutators
    void set_name(string name);
    void set_id(int id);
    void set_item_count(int item_count);
    // other functions
    void BuildInventory(string path);
    void ShowInventory() const;
    void ShowDefectInventory() const;
    void Terminate(string path) const;
    InventoryItem* SearchInventory(int id) const;
    void Discontinue(int id);
};

int main() {
    const string hr = "\n-------------------------\n";
    const string infile = "in.txt";
    const string outfile = "out.txt";

    InventorySystem * is = new InventorySystem("f", 12345);

    cout << hr << "Building inventory: " << endl << endl;
    is->BuildInventory(infile);
    cout << "Finished building inventory" << endl;

    cout << hr << "Showing inventory: " << endl << endl;
    is->ShowInventory();
    cout << "Finished showing inventory " << endl;

    cout << hr << "Showing defect inventory: " << endl << endl;
    is->ShowDefectInventory();
    cout << "Finished showing defect inventory" << endl;

    cout << hr << "Searching/Discontinuing product: " << endl << endl;
    bool exit = false;
    while (!exit) {
        cout << "Enter an ID to discontinue that product, "
                << "or enter -1 to exit: " << endl;
        int input;
        cin >> input;
        cout << endl;
        switch (input) {
            case -1:
                exit = true;
                break;
            default:
                is->Discontinue(input);
        }
    }
    cout << "Finished discontinuing product" << endl;

    cout << hr << "Exporting inventory: " << endl << endl;
    is->Terminate(outfile);
    cout << "Finished exporting inventory" << endl;

    cout << hr << endl;
    delete is;
    return 0;
}

// --------------------------------------------------
// class InventoryItem definitions

InventoryItem::InventoryItem():
        name_("Unknown item"),
        quantity_(0) {}

InventoryItem::InventoryItem(string name, int quantity):
        name_(name),
        quantity_(quantity) {}

InventoryItem::~InventoryItem() {
    cout << "InventoryItem " << name_
         <<  " with " << quantity_
         << " items destroyed" << endl << endl;
}

string InventoryItem::get_name() const { return name_; }

int InventoryItem::get_quantity() const { return quantity_; }

void InventoryItem::set_name(string name) { name_ = name; }

void InventoryItem::set_quantity(int quantity) { quantity_ = quantity; }

void InventoryItem::Display() const {
    cout << "Name: " << name_ << endl;
    cout << "Quantity: " << quantity_ << endl;
}

// --------------------------------------------------
// class Product definitions

Product::Product():
        InventoryItem(),
        id_(0),
        price_(0.0),
        condition_(pcNew) {}

Product::Product(string name, int quantity, double price, T_ProductCondition condition):
        InventoryItem(name, quantity),
        id_(rand() % 10000),
        price_(price),
        condition_(condition) {}

Product::~Product() {
    cout << "Product " << id_
         << ", price = " << price_
         << ", condition = " << ConditionToString(condition_)
         << " destroyed" << endl;
}

int Product::get_id() const { return id_; }

double Product::get_price() const { return price_; }

T_ProductCondition Product::get_condition() const { return condition_; }

void Product::set_id(int id) { id_ = id; }

void Product::set_price(double price) { price_ = price; }

void Product::set_condition(T_ProductCondition condition) { condition_ = condition; }

void Product::Display() const {
    InventoryItem::Display();
    cout << "ID: " << id_ << endl;
    cout << "Price: " << price_<< endl;
    cout << "Condition: " << ConditionToString(condition_) << endl;
}

// --------------------------------------------------
// class InventorySystem definitions

InventorySystem::InventorySystem():
        name_("Unknown store"),
        id_(0),
        item_count_(0) {
    srand((int)time(NULL));
}

InventorySystem::InventorySystem(string name, int id):
        name_(name),
        id_(id),
        item_count_(0) {
    srand((int)time(NULL));
}

InventorySystem::~InventorySystem() {
    for (int i = 0; i < item_count_; ++i) {
        delete items_[i];
    }
}

string InventorySystem::get_name() const { return name_; }

int InventorySystem::get_id() const { return id_; }

int InventorySystem::get_item_count() const { return item_count_; }

void InventorySystem::set_name(string name) { name_ = name; }

void InventorySystem::set_id(int id) { id_ = id; }

void InventorySystem::set_item_count(int item_count) { item_count_ = item_count; }

void InventorySystem::BuildInventory(string path) {
    cout << "Building inventory..." << endl;
    ifstream ifs (path);
    if (!ifs) {
        cout << "Error opening file" << endl;
        exit(-1);
    }
    string name;
    int quantity = 0;
    double price = 0.0;
    T_ProductCondition condition = pcNew;
    string field;
    while (getline(ifs, field, ';')) {
        // get name
        name = field;
        // get quantity
        getline(ifs, field, ';');
        quantity = atoi(field.c_str());
        // get price
        getline(ifs, field, ';');
        price = atof(field.c_str());
        // get condition
        getline(ifs, field, '\n');
        if (field == "N") { condition = pcNew; }
        else if (field == "R") { condition = pcRefurbished; }
        else if (field == "U") { condition = pcUsed; }
        else if (field == "D") { condition = pcDefective; }
        items_[item_count_++] = new Product(name, quantity, price, condition);
    }
    ifs.close();
}

void InventorySystem::ShowInventory() const {
    for (int i = 0; i < item_count_; ++i) {
        items_[i]->Display();
        cout << endl;
    }
}

void InventorySystem::ShowDefectInventory() const {
    for (int i = 0; i < item_count_; ++i) {
        Product * product = static_cast<Product *>(items_[i]);
        if (product && product->get_condition() == pcDefective) {
            product->Display();
            cout << endl;
        }
    }
}

void InventorySystem::Terminate(string path) const {
    ofstream ofs (path);
    for (int i = 0; i < item_count_; ++i) {
        Product * product = static_cast<Product *>(items_[i]);
        if (product) {
            ofs << product->get_name() << ';';
            ofs << product->get_quantity() << ';';
            ofs << product->get_price() << ';';
            ofs << ConditionToChar(product->get_condition()) << endl;
        }
    }
    ofs.close();
}

InventoryItem* InventorySystem::SearchInventory(int id) const {
    for (int i = 0; i < item_count_; ++i) {
        Product * product = static_cast<Product *>(items_[i]);
        if (product->get_id() == id) return product;
    }
    return NULL;
}

void InventorySystem::Discontinue(int id) {
    InventoryItem * ii = SearchInventory(id);
    if (ii) {
        item_count_--;
        for (int i = 0; i < item_count_; ++i) {
            if (items_[i] == ii) {
                items_[i] = items_[i+1];
                items_[i+1] = ii;
            }
        }
        items_[item_count_] = NULL;
        delete ii;
    } else {
        cout << "Product with ID " << id << " not found" << endl << endl;
    }
}