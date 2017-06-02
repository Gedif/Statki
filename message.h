#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
class Message{
public:
    Message();
    string getText() const;
    void setText(const string &value);

private:
    string text;

};


#endif // MESSAGE_H
