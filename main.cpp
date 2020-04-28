#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
using namespace std;
class  Number {
protected:
    vector <int> digits;
public:
    void insert() {
        digits.push_back(0);
    }
    void pop_back() {
        digits.pop_back();
    }
    pair<Number, Number> split() const {
        size_t sz = digits.size();
        if (sz % 2) {
            sz++;
        }
        vector <int> first;
        vector <int> secnd;
        for (size_t i = 0; i < sz / 2; i++) {
            first.push_back(digits[i]);
        }
        for (size_t i = sz / 2; i < digits.size(); i++) {
            secnd.push_back(digits[i]);
        }
        if (digits.size() % 2) {
            secnd.push_back(0);
        }
        return {secnd, first};
    }

    const int& operator[](size_t i) const {
        return digits[i];
    }
    int& operator[](size_t i) {
        return digits[i];
    }
    Number& operator += (const Number& obj) {
        if (digits.size() < obj.size()) {
            size_t diff = obj.size() - digits.size();
            for(size_t i = 0; i < diff; i++){
                digits.push_back(0);
            }
        }
        int vume = 0;
        int x = 0;
        for (size_t i = 0; i < obj.size(); i++) {
            x = (digits[i] + obj[i] + vume);
            vume = x / 10;
            digits[i] = (x) % 10;
        }
        for (size_t i = obj.size(); i < digits.size() && vume > 0; i++) {
            x = (digits[i] + vume);
            vume = x / 10;
            digits[i] = (x) % 10;
        }
        if (vume) {
            digits.push_back(vume);
        }
        return *this;
    }
    bool operator == (const Number& obj) {
        return digits == obj.digits;
    }
    Number& operator -= (const Number& obj) {
        int x = 0;
        int vume = 0;
        for (size_t i = 0; i < obj.size(); i++) {
            x = (digits[i] - obj[i] + vume);
            if (x < 0) {
                vume = -1;
            }
            else {
                vume = 0;
            }
            digits[i] = (x) % 10;
            if (digits[i] < 0) {
                digits[i] += 10;
            }
        }
        for (size_t i = obj.size(); i < digits.size() && vume < 0; i++) {
            x = (digits[i] + vume);
            if (x < 0) {
                vume = -1;
            }
            else {
                vume = 0;
            }
            digits[i] = (x) % 10;
            if (digits[i] < 0) {
                digits[i] += 10;
            }
        }
        return *this;
    }
    Number operator + (const Number& obj) const {
        Number _this(*this);
        _this += obj;
        return _this;
    }
    Number operator - (const Number& obj) const {
        Number _this(*this);
        _this -= obj;
        return _this;
    }
    Number& shift (size_t n) {
        for (size_t i = 0; i < n; i++) {
            digits.insert(digits.begin(), 0);
        }
        return  *this;
    }
    size_t size() const {
        return digits.size();
    }
    Number (vector <int> vec) {
        digits = vec;
    }

    ~Number(){
    }
};
ostream& operator << (ostream& cout_, const Number& _num) {
    for (size_t i = _num.size() - 1; i > 0; --i) {
        cout_ <<_num[i];
    }
    cout_ <<_num[0];
    return cout_;
}
class Multiplicator {
public:
    static Number Ran_domizer (size_t k) {
        vector<int> randomed;
        random_device randomizer;
        knuth_b generator(randomizer());
        uniform_int_distribution<> distrib(0, 9);
        for (size_t i = 0; i < k; i++) {
            randomed.push_back(distrib(generator));
        }
        return {randomed};
    }
    static Number column_mult (const Number& A, const Number& B) {
        Number sum {{0}};
        for (size_t i = 0; i < A.size(); i++) {
            for (size_t j = 0; j < B.size(); ++j) {
                int res = A[i] * B[j];
                vector <int> number;
                number.push_back(res % 10);
                number.push_back(res / 10);
                Number a = Number{number};
                sum += a.shift(i+j);
            }
        }
        for (size_t i = sum.size() - 1; i > 0; --i) {
            if (sum[i] == 0) {
                sum.pop_back();
            }
            else {
                break;
            }
        }
        return sum;
    }
    static Number dvd_n_concq (const Number& copied_A, const Number& copied_B) {
        Number A(copied_A);
        Number B(copied_B);
        if (A.size() == 1 || B.size() == 1) {
            return Multiplicator :: column_mult(A, B);
        }
        if (A.size() < B.size()) {
            for (size_t i = A.size(); i < B.size(); i++) {
                A.insert();
            }
        }
        if (A.size() > B.size()) {
            for (size_t i = B.size(); i < A.size(); i++) {
                B.insert();
            }
        }
        if (A.size() % 2 == 1) {
            A.insert();
            B.insert();
        }
        pair<Number, Number> splitted_pair_A = A.split();
        pair<Number, Number> splitted_pair_B = B.split();
        Number sum = dvd_n_concq(splitted_pair_A.first, splitted_pair_B.first).shift(A.size()) + (dvd_n_concq(splitted_pair_A.first, splitted_pair_B.second) + dvd_n_concq(splitted_pair_A.second, splitted_pair_B.first)).shift(A.size() / 2) + dvd_n_concq(splitted_pair_A.second, splitted_pair_B.second);
        for (size_t i = sum.size() - 1; i > 0; --i) {
            if (sum[i] == 0) {
                sum.pop_back();
            }
            else {
                break;
            }
        }
        return sum;
    }
    static Number Karatsuba (const Number& copied_A, const Number& copied_B) {
        Number A(copied_A);
        Number B(copied_B);
        if (A.size() == 1 || B.size() == 1) {
            return Multiplicator :: column_mult(A, B);
        }
        if (A.size() < B.size()) {
            for (size_t i = A.size(); i < B.size(); i++) {
                A.insert();
            }
        }
        if (A.size() > B.size()) {
            for (size_t i = B.size(); i < A.size(); i++) {
                B.insert();
            }
        }
        if (A.size() % 2 == 1) {
            A.insert();
            B.insert();
        }
        pair<Number, Number> splitted_pair_A = A.split();
        pair<Number, Number> splitted_pair_B = B.split();
        Number fir_mult = Karatsuba(splitted_pair_A.first, splitted_pair_B.first);
        Number sec_mult = Karatsuba(splitted_pair_A.second, splitted_pair_B.second);
        Number sum = Number (fir_mult).shift(A.size()) + (Karatsuba((splitted_pair_A.first + splitted_pair_A.second), (splitted_pair_B.first + splitted_pair_B.second)) - fir_mult - sec_mult).shift(A.size() / 2) + sec_mult;
        for (size_t i = sum.size() - 1; i > 0; --i) {
            if (sum[i] == 0) {
                sum.pop_back();
            }
            else {
                break;
            }
        }
        return sum;
    }
};
void duration(size_t start, size_t end, size_t step,ofstream &output) {
    for (size_t i = start; i <= end; i += step) {
        double column_time = 0;
        double dnq_time = 0;
        double karatsuba_time = 0;
        for (size_t j = 0; j < 3; j++) {
            Number A = Multiplicator::Ran_domizer(i);
            Number B = Multiplicator::Ran_domizer(i);
            auto start = chrono::system_clock::now();
            Number rez1 = Multiplicator::column_mult(A, B);
            auto end = chrono::system_clock::now();
            chrono::duration<double> time_ = end - start;
            column_time += time_.count();

            start = chrono::system_clock::now();
            Number rez2 = Multiplicator::dvd_n_concq(A, B);
            end = chrono::system_clock::now();
            time_ = end - start;
            dnq_time += time_.count();

            start = chrono::system_clock::now();
            Number rez3 = Multiplicator::Karatsuba(A, B);
            end = chrono::system_clock::now();
            time_ = end - start;
            karatsuba_time += time_.count();
        }
        output << i << "," <<  column_time / 3 << "," << dnq_time / 3 << "," << karatsuba_time / 3 << endl;
    }
}
int main() {
    size_t start = 1;
    size_t end = 100;
    size_t step = 50;
    ofstream output("project.results");
    output << "size" << "," << "grade school" << "," << "div_n_conq" << "," << "Karatsuba" << endl;
    duration(1,250,10,output);
    duration(251,1052,100,output);
    output.close();
    return  0;
}