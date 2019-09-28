#pragma once

template<typename CheckType, typename InstanceType>
bool InstanceOf(InstanceType* instance) {
	return (dynamic_cast<CheckType*>(instance) != nullptr);
}