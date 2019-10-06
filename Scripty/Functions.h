#pragma once

#include "IFunction.h"
#include "NumberValue.h"
#include <cmath>
#include <string>
#include <iostream>

class SinFunction : public IFunction {
public:
	Value eval(Scope& scope, const std::vector<Value>&& args) override {
		return std::make_unique<NumberValue>(sin(args[0]->asDouble()));
	};

	IFunction* get() override {
		return this;
	};
};

class CosFunction : public IFunction {
public:
	Value eval(Scope& scope, const std::vector<Value>&& args) override {
		return std::make_unique<NumberValue>(cos(args[0]->asDouble()));
	};

	IFunction* get() override {
		return this;
	};
};

class SqrtFunction : public IFunction {
public:
	Value eval(Scope& scope, const std::vector<Value>&& args) override {
		return std::make_unique<NumberValue>(sqrt(args[0]->asDouble()));
	};

	IFunction* get() override {
		return this;
	};
};

class PrintLnFunction : public IFunction {
public:
	Value eval(Scope& scope, const std::vector<Value>&& args) override {
		for (auto& arg : args) {
			std::cout << arg->asString();
		}

	    std::cout << std::endl;

		return std::make_unique<NumberValue>(0.0);
	};

	IFunction* get() override {
		return this;
	};
};

class InputFunction : public IFunction {
public:
    Value eval(Scope& scope, const std::vector<Value>&& args) override {
        if (args.size() > 0) {
            std::string message = args[0]->asString();
            std::cout << message;
        }

        std::string input = "";

        getline(std::cin, input);

        return std::make_unique<StringValue>(input);
    };

    IFunction* get() override {
        return this;
    };
};

class PrintFunction : public IFunction {
public:
	Value eval(Scope& scope, const std::vector<Value>&& args) override {
        for (auto& arg : args) {
            std::cout << arg->asString();
        }

		return std::make_unique<NumberValue>(0.0);
	};

	IFunction* get() override {
		return this;
	};
};