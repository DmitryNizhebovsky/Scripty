#pragma once

#include "IFunction.h"
#include "NumberValue.h"
#include "UserFunctionDefine.h"
#include <cmath>
#include <string>
#include <vector>
#include <iostream>

class SinFunction : public UserFunctionDefine {
public:
    SinFunction() : UserFunctionDefine("sin", { "x" }, nullptr, true) {};

    virtual Value eval(Scope& scope, std::vector<Value>&& args) override {
        return std::make_unique<NumberValue>(sin(args[0]->asDouble()));
    }
};

class CosFunction : public UserFunctionDefine {
public:
    CosFunction() : UserFunctionDefine("cos", { "x" }, nullptr, true) {};

    virtual Value eval(Scope& scope, std::vector<Value>&& args) override {
        return std::make_unique<NumberValue>(cos(args[0]->asDouble()));
    }
};

class SqrtFunction : public UserFunctionDefine {
public:
    SqrtFunction() : UserFunctionDefine("sqrt", { "x" }, nullptr, true) {};

    virtual Value eval(Scope& scope, std::vector<Value>&& args) override {
        return std::make_unique<NumberValue>(sqrt(args[0]->asDouble()));
    }
};

class InputFunction : public UserFunctionDefine {
public:
    InputFunction() : UserFunctionDefine("input", { }, nullptr, false) {};

    virtual Value eval(Scope& scope, std::vector<Value>&& args) override {
        if (args.size() > 0) {
            std::string message = args[0]->asString();
            std::cout << message;
        }

        std::string input = "";

        getline(std::cin, input);

        return std::make_unique<StringValue>(input);
    }

    virtual size_t InputFunction::getMaxArgsCount() const override {
        return 1;
    }
};

class PrintFunction : public UserFunctionDefine {
public:
    PrintFunction() : UserFunctionDefine("print", { }, nullptr, false) {};

    virtual Value eval(Scope& scope, std::vector<Value>&& args) override {
        for (auto& arg : args) {
            std::cout << arg->asString();
        }

        return std::make_unique<NumberValue>(0.0);
    }

    virtual size_t PrintFunction::getMaxArgsCount() const override {
        return std::numeric_limits<size_t>::max();
    }
};

class PrintLnFunction : public UserFunctionDefine {
public:
    PrintLnFunction() : UserFunctionDefine("println", { }, nullptr, false) {};

    virtual Value eval(Scope& scope, std::vector<Value>&& args) override {
        for (auto& arg : args) {
            std::cout << arg->asString();
        }

        std::cout << std::endl;

        return std::make_unique<NumberValue>(0.0);
    }

    virtual size_t PrintLnFunction::getMaxArgsCount() const override {
        return std::numeric_limits<size_t>::max();
    }
};