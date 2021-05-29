#include <iostream>
#include <vector>
#include <cmath>

template<typename T>
class Polynomial {
private:
    std::vector<T> pol;

    void normalize(std::vector<T>& a) const {
        for (auto it = a.rbegin(); it != a.rend(); it++) {
            if (*it == T(0)) {
                a.pop_back();
            } else {
                return;
            }
        }
    }

public:
    Polynomial() = default;
    Polynomial(std::vector<T>& _pol) {
        pol = _pol;
        normalize(pol);
    }
    template <typename It>
    Polynomial(It first, It last) {
        pol = std::vector<T>(first, last);
        normalize(pol);
    }
    Polynomial(T _pol) {
        pol = std::vector<T>(1, _pol);
        normalize(pol);
    }
    bool operator==(const Polynomial& a) const {
        return pol == a.pol;
    }
    bool operator!=(const Polynomial& a) const {
        return pol != a.pol;
    }
    int Degree() const {
        if (pol.size() == 0 || (pol.size() == 1 && pol[0] == T{0})) {
            return -1;
        }
        return pol.size() - 1;
    }
    const Polynomial operator+(const Polynomial& a) const {
        std::vector<T> res(std::max(pol.size(), a.pol.size()), T());
        if (pol.size() <= a.pol.size()) {
            for (size_t i = 0; i < pol.size(); ++i) {
                res[i] += pol[i] + a.pol[i];
            }
            for (size_t i = pol.size(); i < a.pol.size(); ++i) {
                res[i] += a.pol[i];
            }
        } else {
            for (size_t i = 0; i < a.pol.size(); ++i) {
                res[i] += pol[i] + a.pol[i];
            }
            for (size_t i = a.pol.size(); i < pol.size(); ++i) {
                res[i] += pol[i];
            }
        }
        normalize(res);
        return Polynomial(res);
    }
    const Polynomial operator-(const Polynomial& a) const {
        std::vector<T> res(std::max(pol.size(), a.pol.size()), T());
        if (pol.size() <= a.pol.size()) {
            for (size_t i = 0; i < pol.size(); ++i) {
                res[i] += pol[i] - a.pol[i];
            }
            for (size_t i = pol.size(); i < a.pol.size(); ++i) {
                res[i] -= a.pol[i];
            }
        } else {
            for (size_t i = 0; i < a.pol.size(); ++i) {
                res[i] += pol[i] - a.pol[i];
            }
            for (size_t i = a.pol.size(); i < pol.size(); ++i) {
                res[i] += pol[i];
            }
        }
        normalize(res);
        return Polynomial(res);
    }
    const Polynomial operator*(const Polynomial& a) const {
        std::vector<T> res(pol.size() + a.pol.size());
        for (size_t i = 0; i < pol.size(); i++) {
            for (size_t j = 0; j < a.pol.size(); j++) {
                res[i + j] += pol[i] * a.pol[j];
            }
        }
        normalize(res);
        return Polynomial(res);
    }
    const T operator() (const T& x) const {
        T ans = {0};
        T xx = x;
        for (size_t i = 0; i < pol.size(); i++) {
            if (i == 0) {
                ans += pol[i];
            } else {
                ans += pol[i] * xx;
                xx = xx * x;
            }
        }
        return ans;
    }
    Polynomial& operator+=(const Polynomial& a) {
        *this = (*this + a);
        return *this;
    }
    Polynomial& operator*=(const Polynomial& a) {
        *this = (*this * a);
        return *this;
    }
    Polynomial& operator-=(const Polynomial& a) {
        *this = (*this - a);
        return *this;
    }
    const T operator[] (int i) const {
        if (i <= Degree()) {
            return pol[i];
        } else {
            return T(0);
        }
    }
    auto begin() const {
        return pol.begin();
    }
    auto end() const {
        return pol.end();
    }
};
