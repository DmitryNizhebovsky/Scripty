#pragma once

#include "Scope.h"

class Ilvalue: public NonCopyable {
public:
	Ilvalue() = default;
	virtual std::unique_ptr<IValue>& getRef(Scope& scope) = 0;
	virtual ~Ilvalue() = default;
};