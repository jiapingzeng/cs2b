#include <iostream>
#include <string>
using namespace std;

const int g_array_size = 8;

class Movie {
private:
    string name_; // name of movie
    int seats_; // number of seats available
    int price_; // price of ticket
public:
    // constructors/destructor
    Movie();
    Movie(string name, int seats, int price);
    ~Movie();
    // accessors
    string get_name();
    int get_seats();
    int get_price();
    // mutators
    void set_name(string name);
    void set_seats(int seats);
    void set_price(int price);
    // other functions
    int PurchaseTicket(int num);
    void Display();
};

class MovieTicketMaster {
private:
    string name_; // name of theater
    string location_; // location of theater
    Movie movies_[g_array_size]; // movies playing at theater
public:
    // constructors/destructor
    MovieTicketMaster();
    MovieTicketMaster(string name, string location);
    ~MovieTicketMaster();
    // other functions
    void Init();
    void Run();
    void Menu();
    void ViewMovies();
    void SearchMovie();
    Movie * FindMovie(string name);
    void PurchaseTicket();
};

int main() {
    MovieTicketMaster * p_theater = NULL;
    p_theater = new MovieTicketMaster("Century Cinema 16", "Mountain View");
    p_theater->Init();
    p_theater->Run();
    delete p_theater;
    return 0;
}

// class Movie definitions:

// constructors/destructor

Movie::Movie(): name_("Unknown movie"), seats_(100), price_(10) {};

Movie::Movie(string name, int seats, int price): name_(name), seats_(seats), price_(price) {}

Movie::~Movie() {
    cout << "Movie <" << name_ << "> is no longer showing ..." << endl;
}

// accessors

string Movie::get_name() {
    return name_;
}

int Movie::get_seats() {
    return seats_;
}

int Movie::get_price() {
    return price_;
}

// mutators

void Movie::set_name(string name) {
    name_ = name;
}

void Movie::set_seats(int seats) {
    seats_ = seats;
}

void Movie::set_price(int price) {
    price_ = price;
}

// other functions

int Movie::PurchaseTicket(int num) {
    if (num > seats_) return -1;
    seats_ -= num;
    return num * price_;
}

void Movie::Display() {
    cout << "Movie name: " << name_ << endl;
    cout << "Seats available: " << seats_ << endl;
    cout << "Ticket price: $" << price_ << endl;
}


// class MovieTicketMaster definitions

// constructors/destructor

MovieTicketMaster::MovieTicketMaster(): name_("Unknown movie theater"),
                                        location_("Middle of nowhere") {}

MovieTicketMaster::MovieTicketMaster(string name, string location): name_(name),
                                                                    location_(location) {}

MovieTicketMaster::~MovieTicketMaster() {
    cout << "Theater <" << name_ << "> at <" << location_<< "> has been closed ..." << endl;
}

void MovieTicketMaster::Init() {
    string movie_names[g_array_size] = {
            "Black Mass", "The Visit", "Mission: Impossible - Rogue Nation",
            "Straight Outta Compton", "No Escape", "Maze Runner: Scorch Trials",
            "Everest", "War Room",
    };
    int number_of_seats[g_array_size] = {
            410, 360, 460, 450, 380, 380, 440, 230
    };
    int ticket_prices[g_array_size] = {
            15, 19, 11, 14, 20, 16, 18, 8
    };
    Movie * p_movie = NULL;
    p_movie = movies_;
    string * p_movie_name = NULL;
    p_movie_name = movie_names;
    int * p_number_of_seats = NULL;
    p_number_of_seats = number_of_seats;
    int * p_ticket_price = NULL;
    p_ticket_price = ticket_prices;
    while (p_movie < &movies_[g_array_size]) {
        p_movie->set_name(*p_movie_name);
        p_movie->set_seats(*p_number_of_seats);
        p_movie->set_price(*p_ticket_price);
        p_movie++;
        p_movie_name++;
        p_number_of_seats++;
        p_ticket_price++;
    }
}

void MovieTicketMaster::Run() {
    while (true) {
        Menu();
        int selection;
        cin >> selection;
        cout << endl;
        switch (selection) {
            case 1:
                ViewMovies();
                break;
            case 2:
                SearchMovie();
                break;
            case 3:
                PurchaseTicket();
                break;
            case 4:
                cout << "Exiting Movie Ticket Master ..." << endl;
                return;
            default:
                cout << "Invalid option. Please try again." << endl << endl;
        }
    }
}

void MovieTicketMaster::Menu() {
    cout << endl << "MOVIE TICKET MASTER" << endl;
    cout << "Theater: " << name_ << " at " << location_ << endl;
    cout << "Looking for something groovy? Come watch a movie!" << endl << endl;
    cout << "Please select an option from below:" << endl;
    cout << "1. View all movies" << endl;
    cout << "2. Search a movie" << endl;
    cout << "3. Purchase a ticket" << endl;
    cout << "4. Quit" << endl << endl;
    cout << "Your choice: " << endl;
}

void MovieTicketMaster::ViewMovies() {
    for (Movie * p_movie = movies_; p_movie < &movies_[g_array_size]; p_movie++) {
        cout << endl;
        p_movie->Display();
    }
}

void MovieTicketMaster::SearchMovie() {
    cout << "Please enter a movie name: " << endl;
    string input;
    cin.ignore(256, '\n');
    getline(cin, input);
    Movie * result = FindMovie(input);
    if (result) {
        cout << endl << "Movie found: " << endl;
        result->Display();
    } else {
        cout << "Movie not found" << endl;
    }
}

Movie * MovieTicketMaster::FindMovie(string name) {
    for (Movie * p_movie = movies_; p_movie < &movies_[g_array_size]; p_movie++) {
        if (p_movie->get_name() == name) return p_movie;
    }
    return NULL;
}

void MovieTicketMaster::PurchaseTicket() {
    cout << "Please enter a movie name: " << endl;
    string input;
    cin.ignore(256, '\n');
    getline(cin, input);
    Movie * result = FindMovie(input);
    if (!result) {
        cout << "Movie not found" << endl;
        return;
    }
    int num;
    cout << "Please enter the number of tickets you'd like to purchase: " << endl;
    cin >> num;
    int price = result->PurchaseTicket(num);
    if (price > 0) {
        cout << "The total cost is $" << price << ", please." << endl;
    } else {
        cout << "The show has been sold out or not enough tickets available per your request." << endl;
    }
}