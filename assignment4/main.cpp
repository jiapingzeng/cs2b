//=====================================================================================
// Name           : main.cpp
// Author         : Jiaping Zeng
// Date           : Summer 2018
// Version        : 1.0
// Program purpose: to keep track of customers’ SmartPhone message usages/charges
//                  and to provide account disconnect service
//
// Revisions history:
//     8/4: implemented templates for all classes
//     8/5: finished definitions for Message, TextMessage
//     8/8: finished definitions for VoiceMessage and MediaMessage
//     8/10: worked on but didn't finish definitions of SmartCarrierr
//=====================================================================================

#include <iostream>
#include <map>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

class Message {
private:
    string from_;
    string to_;
public:
    Message();
    Message(string from, string to);
    virtual ~Message();
    virtual double ComputeCharge() const = 0;
    bool operator==(const Message &other) const;
};

class TextMessage: public Message {
private:
    string message_;
    const double kChargePerMessage = 20.0;
public:
    TextMessage();
    TextMessage(string from, string to, string message);
    virtual ~TextMessage();
    string get_message() const;
    void set_message(string message);
    virtual double ComputeCharge() const;
    friend ostream &operator<<(ostream &os, const TextMessage &message);
};

class VoiceMessage: public Message {
private:
    int time_;
    const double kChargePerSecond = 1.5;
public:
    VoiceMessage();
    VoiceMessage(string from, string to, int time);
    ~VoiceMessage();
    int get_time() const;
    void set_time(int time);
    virtual double ComputeCharge() const;
    friend ostream &operator<<(ostream &os, const VoiceMessage &message);
};

class MediaMessage: public Message {
private:
    int size_;
    const double kChargePerMb = 10.0;
public:
    MediaMessage();
    MediaMessage(string from, string to, int size);
    ~MediaMessage();
    int get_size() const;
    void set_size(int size);
    virtual double ComputeCharge() const;
    friend ostream &operator<<(ostream &os, const MediaMessage &message);
};

class SmartCarrier {
private:
    string name_;
    map<string, vector<Message *>> accounts_;
public:
    SmartCarrier();
    SmartCarrier(string name);
    ~SmartCarrier();
    string get_name() const;
    void set_name(string name);
    map<string, vector<Message *>> * get_accounts() const;
    void Init();
    void StartService();
private:
    void Menu() const;
    int GetChoice() const;
    void ListAll() const;
    void SearchMessage() const;
    void EraseMessage();
    void DisconnectAccount();
    void StopService() const;
};

int main() {
    return 0;
}

//region class Message

Message::Message(): from_("0000000000"), to_("0000000000") {}

Message::Message(string from, string to): from_(from), to_(to) {}

Message::~Message() {
    cout << "Message destroyed" << endl;
}

bool Message::operator==(const Message &other) const {
    return from_ == other.from_ && to_ == other.to_;
}

//endregion

//region class TextMessage

TextMessage::TextMessage(): Message(), message_("never gonna give you up") {}

TextMessage::TextMessage(string from, string to, string message): Message(from, to), message_(message) {}

TextMessage::~TextMessage() {
    cout << "Text message destroyed" << endl;
}

string TextMessage::get_message() const {
    return message_;
}

void TextMessage::set_message(string message) {
    message_ = message;
}

double TextMessage::ComputeCharge() const {
    return kChargePerMessage;
}

ostream &operator<<(ostream &os, const TextMessage &message) {
    cout << message.message_ << endl;
    return os;
}

//endregion

//region class VoiceMessage

VoiceMessage::VoiceMessage(): Message(), time_(0) {}

VoiceMessage::VoiceMessage(string from, string to, int time): Message(from, to), time_(time) {}

VoiceMessage::~VoiceMessage() {
    cout << "Voice message destroyed" << endl;
}

int VoiceMessage::get_time() const {
    return time_;
}

void VoiceMessage::set_time(int time) {
    time_ = time;
}

double VoiceMessage::ComputeCharge() const {
    return kChargePerSecond * time_;
}

ostream &operator<<(ostream &os, const VoiceMessage &message) {
    cout << message.time_ << endl;
    return os;
}

//endregion

//region class MediaMessage

MediaMessage::MediaMessage(): size_(0) {}

MediaMessage::MediaMessage(string from, string to, int size): Message(from, to), size_(size) {}

MediaMessage::~MediaMessage() {
    cout << "Media message destroyed" << endl;
}

int MediaMessage::get_size() const {
    return size_;
}

void MediaMessage::set_size(int size) {
    size_ = size;
}

double MediaMessage::ComputeCharge() const {
    return kChargePerMb * size_;
}

ostream &operator<<(ostream &os, const MediaMessage &message) {
    cout << message.size_ << endl;
    return os;
}

//endregion

//region SmartCarrier

SmartCarrier::SmartCarrier(): name_("Unnamed carrier") {}

SmartCarrier::SmartCarrier(string name): name_(name) {}

SmartCarrier::~SmartCarrier() {
    map<string, vector<Message *>>::const_iterator map_iter;
    for (map_iter = accounts_.begin(); map_iter != accounts_.end(); ++map_iter) {
        vector<Message *> messages = map_iter->second;
        vector<Message *>::iterator iter;
        for (iter = messages.begin(); iter != messages.end(); ++iter) {
            Message* message = *iter;
            messages.erase(iter);
            delete message;
        }
        messages.clear();
    }
    accounts_.clear();
}

string SmartCarrier::get_name() const {
    return name_;
}

void SmartCarrier::set_name(string name) {
    name_ = name;
}

map<string, vector<Message *>>* SmartCarrier::get_accounts() const {
    return &accounts_;
}

void SmartCarrier::Init() {
    Message* text1 = new TextMessage("650-267-1289", "650-345-9001", "Hello there");
    Message* voice1 = new VoiceMessage ("650-267-1289", "408-111-2222", 120);
    Message* media1 = new MediaMessage ("310-777-8888", "650-267-1289", 25);
    accounts_["650-267-1289"].push_back(text1);
    accounts_["650-267-1289"].push_back(voice1);
    accounts_["650-267-1289"].push_back(media1);

    Message* text2 = new TextMessage("650-267-1289", "650-345-9001", "Did you");
    Message* text3 = new TextMessage("650-267-1289", "650-345-9001", "hear");
    Message* text4 = new TextMessage("650-267-1289", "650-345-9001", "about the tragedy of darth plagueis the wise?");
    Message* voice2 = new VoiceMessage ("650-267-1289", "408-111-2222", 53);
    Message* voice3 = new VoiceMessage ("650-267-1289", "408-111-2222", 351);
    Message* voice4 = new VoiceMessage ("650-267-1289", "408-111-2222", 109);
    Message* media2 = new MediaMessage ("310-777-8888", "650-267-1289", 10);
    Message* media3 = new MediaMessage ("310-777-8888", "650-267-1289", 200);
    Message* media4 = new MediaMessage ("310-777-8888", "650-267-1289", 104);
    Message* media5 = new MediaMessage ("310-777-8888", "650-267-1289", 412);
    accounts_["408-235-1500"].push_back(text2);
    accounts_["408-235-1500"].push_back(text3);
    accounts_["408-235-1500"].push_back(text4);
    accounts_["408-235-1500"].push_back(voice2);
    accounts_["408-235-1500"].push_back(voice3);
    accounts_["408-235-1500"].push_back(voice4);
    accounts_["408-235-1500"].push_back(media2);
    accounts_["408-235-1500"].push_back(media3);
    accounts_["408-235-1500"].push_back(media4);
    accounts_["408-235-1500"].push_back(media5);

    Message* text5 = new TextMessage("650-781-7900", "650-345-9001", "Hello there");
    Message* text6 = new TextMessage("650-781-7900", "650-345-9001", "Hello there");
    Message* media6 = new MediaMessage ("650-781-7900", "650-267-1289", 25);
    Message* media7 = new MediaMessage ("650-781-7900", "650-267-1289", 25);
    Message* media8 = new MediaMessage ("650-781-7900", "650-267-1289", 25);
    accounts_["650-781-7900"].push_back(text5);
    accounts_["650-781-7900"].push_back(text6);
    accounts_["650-781-7900"].push_back(media6);
    accounts_["650-781-7900"].push_back(media7);
    accounts_["650-781-7900"].push_back(media8);
}

void SmartCarrier::StartService() {
    while (true) {
        Menu();
        int selection = GetChoice();
        switch (selection) {
            case 1:
                ListAll();
                break;
            case 2:
                SearchMessage();
                break;
            case 3:
                EraseMessage();
                break;
            case 4:
                DisconnectAccount();
                break;
            case 5:
                cout << "Stopping service..." << endl;
                return;
            default:
                cout << "Invalid option. Please try again." << endl << endl;
        }
    }
}

void SmartCarrier::Menu() const {
    cout << "Welcome to " << name_ << "!" << endl;
    cout << "Please select an option from below:" << endl;
    cout << "1. List all" << endl;
    cout << "2. Search message" << endl;
    cout << "3. Erase message" << endl;
    cout << "4. Disconnect account" << endl;
    cout << "5. Stop service" << endl << endl;
    cout << "Your choice: " << endl;
}

int SmartCarrier::GetChoice() const {
    int selection;
    cin >> selection;
    return selection;
}

void SmartCarrier::ListAll() const {
    cout << setw(15) << "Phone number";
    cout << setw(15) << "Total messages";
    cout << setw(8) << "Text";
    cout << setw(8) << "Voice";
    cout << setw(8) << "Media";
    cout << setw(15) << "Total charges";
    map<string, vector<Message *>>::const_iterator map_iter;
    for (map_iter = accounts_.begin(); map_iter != accounts_.end(); ++map_iter) {
        cout << setw(15) << map_iter->first;
        vector<Message *> messages = map_iter->second;
        vector<Message *>::iterator iter;
        TextMessage * text = nullptr;
        VoiceMessage * voice = nullptr;
        MediaMessage * media = nullptr;
        int text_count = 0;
        int voice_count = 0;
        int media_count = 0;
        double total_charge = 0;
        for (iter = messages.begin(); iter != messages.end(); ++iter) {
            Message* message = *iter;
            if ((text = dynamic_cast<TextMessage*>(message))) {
                text_count++;
                total_charge += text->ComputeCharge();
            } else if ((voice = dynamic_cast<VoiceMessage*>(message))) {
                voice_count++;
                total_charge += voice->ComputeCharge();
            } else if ((media = dynamic_cast<MediaMessage*>(message))) {
                media_count++;
                total_charge += media->ComputeCharge();
            }
        }
        cout << setw(15) << text_count + voice_count + media_count;
        cout << setw(8) << text_count;
        cout << setw(8) << voice_count;
        cout << setw(8) << media_count;
        cout << setw(15) << total_charge;
    }
}

void SmartCarrier::SearchMessage() const {
    string number = "";
    string type = "";
    string from = "";
    string to = "";
    vector<Message*> account;
    try {
        if (accounts_.find(number) != accounts_.end()) {
            vector<Message *>::iterator iter;
            for (iter = account.begin(); iter != account.end(); ++iter) {
                Message *message = *iter;
                bool type_match = false;
                if (type == "Text") {
                    type_match = bool(dynamic_cast<TextMessage *>(message));
                } else if (type == "Voice") {
                    type_match = bool(dynamic_cast<VoiceMessage *>(message));
                } else if (type == "Media") {
                    type_match = bool(dynamic_cast<MediaMessage *>(message));
                }
                Message *test = new TextMessage(from, to, "");
                if (type_match and test == message) {
                    cout << message << endl;
                    return;
                }
            }
            throw runtime_error("message not found");
        } else {
            throw runtime_error("account not found");
        }
    } catch (exception e) {
        cout << e.what() << endl;
        return;
    }
}

void SmartCarrier::EraseMessage() {
    string number = "";
    string type = "";
    string from = "";
    string to = "";
    vector<Message*> account;
    try {
        if (accounts_.find(number) != accounts_.end()) {
            vector<Message *>::iterator iter;
            for (iter = account.begin(); iter != account.end(); ++iter) {
                Message *message = *iter;
                bool type_match = false;
                if (type == "Text") {
                    type_match = bool(dynamic_cast<TextMessage *>(message));
                } else if (type == "Voice") {
                    type_match = bool(dynamic_cast<VoiceMessage *>(message));
                } else if (type == "Media") {
                    type_match = bool(dynamic_cast<MediaMessage *>(message));
                }
                Message *test = new TextMessage(from, to, "");
                if (type_match and test == message) {
                    account.erase(iter);
                    delete message;
                    return;
                }
            }
            throw runtime_error("message not found");
        } else {
            throw runtime_error("account not found");
        }
    } catch (exception e) {
        cout << e.what() << endl;
        return;
    }
}

void SmartCarrier::DisconnectAccount() {
    string number = "";
    try {
        if (accounts_.find(number) != accounts_.end()) {
            accounts_.erase(number);
        }
        throw runtime_error("account not found");
    } catch (exception e) {
        cout << e.what() << endl;
    }
}

void SmartCarrier::StopService() const {
    ofstream ofs ("out.txt");
    ListAll();
    map<string, vector<Message *>>::const_iterator map_iter;
    for (map_iter = accounts_.begin(); map_iter != accounts_.end(); ++map_iter) {
        vector<Message *> messages = map_iter->second;
        vector<Message *>::iterator iter;
        TextMessage * text = nullptr;
        VoiceMessage * voice = nullptr;
        MediaMessage * media = nullptr;
        for (iter = messages.begin(); iter != messages.end(); ++iter) {
            ofs << map_iter->first << ",";
            Message* message = *iter;
            if ((text = dynamic_cast<TextMessage*>(message))) {
                ofs << "Text" << ",";
                ofs << text->ComputeCharge();
            } else if ((voice = dynamic_cast<VoiceMessage*>(message))) {
                ofs << "Voice" << ",";
                ofs << voice->ComputeCharge();
            } else if ((media = dynamic_cast<MediaMessage*>(message))) {
                ofs << "Media" << ",";
                ofs << media->ComputeCharge();
            }
            ofs << endl;
        }
    }
}

//endregion