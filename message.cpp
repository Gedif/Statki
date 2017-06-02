#include "Message.h"

Message::Message(){

    setText("Text domyslny");
}
String Message::getText() const
{
    return text;
}

void Message::setText(const String &value)
{
    text = value;
}
