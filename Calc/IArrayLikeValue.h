#pragma once

#include <memory>

class ObjectValue;
class StringValue;
class ArrayValue;
class IValue;

class IArrayLikeValue {
public:
    virtual std::unique_ptr<IValue> getValue(const IArrayLikeValue* value, const IValue* key) = 0;
    virtual std::unique_ptr<IValue> getValue(const ObjectValue*     value, const IValue* key) = 0;
    virtual std::unique_ptr<IValue> getValue(const StringValue*     value, const IValue* key) = 0;
    virtual std::unique_ptr<IValue> getValue(const ArrayValue*      value, const IValue* key) = 0;

    virtual std::unique_ptr<IValue>& getValueRef(const IArrayLikeValue* value, const IValue* key) = 0;
    virtual std::unique_ptr<IValue>& getValueRef(const ObjectValue*     value, const IValue* key) = 0;
    virtual std::unique_ptr<IValue>& getValueRef(const StringValue*     value, const IValue* key) = 0;
    virtual std::unique_ptr<IValue>& getValueRef(const ArrayValue*      value, const IValue* key) = 0;

public:
    IArrayLikeValue() = default;
    virtual ~IArrayLikeValue() = default;

    IArrayLikeValue(IArrayLikeValue&&) = default;
    IArrayLikeValue& operator=(IArrayLikeValue&&) = default;
};