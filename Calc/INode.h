#pragma once
#include "IVisitor.h"

class INode {
public:
	INode() = default;
	virtual void accept(IVisitor* visitor) = 0;
	virtual void innerAccept(IVisitor* visitor) = 0;
	virtual ~INode() = default;

private:
	INode(const INode&) = delete;
	INode& operator=(const INode&) = delete;
};