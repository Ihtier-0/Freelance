#pragma once

#include "bird.h"

// соловей
class nightingale :
    public bird
{
public:
    nightingale(const std::string& identifier,
        const bool& sleep);

    virtual std::string sing() const override;
private:

};

