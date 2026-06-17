// main.cpp
#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Core.h"
#include "Grad.h"
#include "Intl.h"       // ★ 유학생 클래스 헤더 추가
#include "Vec.h"
#include "Student_info.h"
#include "median.h"

using namespace std;

int main() {
    vector<Core*> students; // 객체의 포인터를 저장하는 컨테이너
    Core* record = nullptr;
    char ch;
    string::size_type maxlen = 0;

    // 1. 데이터 읽고 저장하기
    while (cin >> ch) {
        if (cin.eof()) break;  // 입력 종료 확인

        // 입력값이 U, G, I 중 하나인지 확인
        if (ch != 'U' && ch != 'G' && ch != 'I') {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // 각 타입에 맞는 객체 생성
        if (ch == 'U')
            record = new Core;
        else if (ch == 'G')
            record = new Grad;
        else
            record = new Intl; // ★ 유학생(I) 객체 할당

        record->read(cin); // 데이터를 읽어 들임

        maxlen = max(maxlen, record->getName().size());
        students.push_back(record);
    }

    // 2. 학생 이름순으로 정렬
    sort(students.begin(), students.end(), compare_Core_ptrs);

    // 3. 타입 구분 마크와 이름, 점수 출력
    for (vector<Core*>::size_type i = 0; i != students.size(); i++) {

        // 타입 확인 후 출력 (다형성 활용)
        if (dynamic_cast<Intl*>(students[i])) {
            cout << "(I) ";
        }
        else if (dynamic_cast<Grad*>(students[i])) {
            cout << "(G) ";
        }
        else {
            cout << "(U) ";
        }

        // 이름 출력 (정렬 간격 맞춤)
        cout << students[i]->getName()
            << string(maxlen + 1 - students[i]->getName().size(), ' ');

        // 점수 출력
        try {
            double final_grade = students[i]->grade();
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade
                << setprecision(prec) << endl;
        }
        catch (domain_error e) {
            cout << e.what() << endl; // 예외 메시지 출력
        }

        delete students[i]; // 메모리 해제
    }

    return 0;
}