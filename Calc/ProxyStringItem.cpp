#include "ProxyStringItem.h"
#include "StringValue.h"

ProxyStringItem::ProxyStringItem(StringValue* value, size_t index) :
    stringValue(value),
    itemIndex(index) {}

double ProxyStringItem::asDouble() const {
    return stringValue->asDouble();
}

std::string ProxyStringItem::asString() const {
    return stringValue->asString();
}

std::unique_ptr<IValue> ProxyStringItem::copy() const {
    return std::make_unique<StringValue>(stringValue->asString());
}

IValue* ProxyStringItem::getPtr() {
    return stringValue;
}

void ProxyStringItem::setItemIndex(size_t index) {
    itemIndex = index;
}

IValue& ProxyStringItem::operator=(const std::unique_ptr<IValue>& newValue) {
    //stringValue->set(newValue, itemIndex);
    return *this;
}

IValue& ProxyStringItem::operator=(const std::unique_ptr<IValue>&& newValue) {
    //stringValue->set(newValue, itemIndex);
    return *this;
}