#include <algorithm>
#include <vector> // Vec.h 대신 기본 vector 헤더 사용
#include "Intl.h"

using std::istream;
using std::min;
using std::vector; // vector 사용 명시

// Core 클래스의 homework 타입(vector)에 맞춰서 선언 수정
extern istream& read_hw(istream&, vector<double>&);

Intl::Intl() : toeic(0) {}

Intl::Intl(istream& is) { read(is); }

double Intl::grade() const {
    return min(Core::grade(), toeic);
}

istream& Intl::read(istream& in) {
    read_common(in);
    in >> toeic;           // 토익 점수 읽기
    read_hw(in, homework); // 과제 점수 읽기 (이제 타입이 완벽히 일치함)
    return in;
}