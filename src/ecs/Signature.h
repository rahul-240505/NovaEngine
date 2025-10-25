#pragma once
#include "Component.h"
#include <bitset>

// A Signature is a bitset (an array of bits) where each bit corresponds to
// a ComponentType. If the bit is set, the entity has that component.
using Signature = std::bitset<MAX_COMPONENTS>;