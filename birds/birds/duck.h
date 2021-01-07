#pragma once

#include "bird.h"

class duck :
    public bird
{
public:
    duck(const std::string& identifier,
        const bool& sleep);

    virtual std::string sing() const override;
private:

};

