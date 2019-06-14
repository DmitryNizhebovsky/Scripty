#pragma once

#include "Scope.h"

class Ilvalue {
public:
	Ilvalue() = default;
	virtual std::unique_ptr<IValue>& getRef(Scope& scope) = 0;
	virtual ~Ilvalue() = default;

private:
	Ilvalue(const Ilvalue&) = delete;
	Ilvalue& operator=(const Ilvalue&) = delete;
};