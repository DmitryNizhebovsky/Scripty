#pragma once
#include "IVisitor.h"
#include "NonCopyable.h"

class INode : public NonCopyable {
public:
	INode() = default;
	virtual void accept(IVisitor* visitor) = 0;
	virtual void innerAccept(IVisitor* visitor) = 0;
	virtual ~INode() = default;
};