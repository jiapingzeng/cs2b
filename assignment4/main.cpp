//=====================================================================================
// Name           : main.cpp
// Author         : Jiaping Zeng
// Date           : Summer 2018
// Version        : 1.0
// Program purpose: to keep track of customers’ SmartPhone message usages/charges
//                  and to provide account disconnect service
//
// Revisions history:
//     8/4: implemented templates for all classes and definitions for Message,
//          TextMessage, VoiceMessage and MediaMessage
//=====================================================================================

#include <iostream>
#include <map>
#include <vector>
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
    friend ostream &operator<<(ostream &os, const TextMessage &message) const;
};

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

ostream &operator<<(ostream &os, const TextMessage &message) const {
    cout << message.message_ << endl;
    return os;
}

//endregion

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
    friend ostream &operator<<(ostream &os, const VoiceMessage &message) const;
};

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

ostream &operator<<(ostream &os, const VoiceMessage &message) const {
    cout << message.time_ << endl;
    return os;
}

//endregion

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
    friend ostream &operator<<(ostream &os, const MediaMessage &message) const;
};

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

ostream &operator<<(ostream &os, const MediaMessage &message) const {
    cout << message.size_ << endl;
    return os;
}

//endregion

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
    void StartService() const;
private:
    void Menu() const;
    void GetChoice() const;
    void ListAll() const;
    void SearchMessage() const;
    void EraseMessage();
    void DisconnectAccount(string number);
    void StopService() const;
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}