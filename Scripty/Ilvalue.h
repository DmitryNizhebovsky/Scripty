#pragma once

#include "Scope.h"

class Ilvalue: public NonCopyable {
public:
	Ilvalue() = default;
	virtual Value& getRef(Scope& scope) = 0;
	virtual ~Ilvalue() = default;
};