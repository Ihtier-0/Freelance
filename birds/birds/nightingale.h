#pragma once

#include "bird.h"

// �������
class nightingale :
    public bird
{
public:
    nightingale(const std::string& identifier,
        const bool& sleep);

    virtual std::string sing() const override;
private:

};

