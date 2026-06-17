#pragma once
#ifndef INTL_H
#define INTL_H

#include <iostream>
#include "Core.h"

class Intl : public Core {
public:
    Intl();
    Intl(std::istream& is);
    double grade() const;
    std::istream& read(std::istream&);

protected:
    Intl* clone() const { return new Intl(*this); }

private:
    double toeic; // thesis 대신 toeic 변수 사용
};

#endif