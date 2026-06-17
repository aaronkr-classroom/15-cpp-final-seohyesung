#include <iostream>
#include "Student_info.h"
#include "Core.h"
#include "Grad.h"
#include "Intl.h" // 유학생 클래스 헤더 추가

using namespace std;

// 복사 생성자
Student_info::Student_info(const Student_info& s) : cp(0) {
    if (s.cp) cp = s.cp->clone();
}

// 대입 연산자
Student_info& Student_info::operator=(const Student_info& s) {
    if (&s != this) {
        delete cp;
        if (s.cp)
            cp = s.cp->clone();
        else
            cp = 0;
    }
    return *this;
}

// 객체 동적 할당 및 읽기 (U, G, I 판별)
istream& Student_info::read(istream& is) {
    delete cp; // 기존 객체 삭제
    cp = 0;

    char ch;
    is >> ch; // 학생 타입 문자 읽기

    if (ch == 'U') {
        cp = new Core(is);
    }
    else if (ch == 'G') {
        cp = new Grad(is);
    }
    else if (ch == 'I') {
        cp = new Intl(is); // 'I'일 때 Intl 객체 할당
    }
    else {
        cp = 0;
    }

    return is;
}

// 과제 점수를 Vec에 입력받는 헬퍼 함수
istream& read_hw(istream& in, Vec<double>& hw) {
    if (in) {
        hw.clear();
        double x;
        while (in >> x) {
            hw.push_back(x);
        }
        in.clear();
    }
    return in;
}