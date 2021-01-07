#include "nightingale.h"

nightingale::nightingale(const std::string& identifier, const bool& sleep) : bird(identifier, sleep) {}

std::string nightingale::sing() const
{
    return "phew!phew!";
}
