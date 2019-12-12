#ifndef C_COMPONENTS_VIA_DSU_HPP
#define C_COMPONENTS_VIA_DSU_HPP

#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>
#include "CDSU.hpp"
#include "IGraphComponents.hpp"


template <class T>
class CComponentsViaDSU : public IGraphComponents<T> {
public:
    CComponentsViaDSU() = default;

    explicit CComponentsViaDSU(const CDSU<T>& dsu);

    explicit CComponentsViaDSU(CDSU<T>&& dsu);

    virtual ~CComponentsViaDSU() = default;

    virtual void print() override;

    virtual void printToFile(const std::string& filename) override;

private:
    void printOut(std::ostream& out);

    void sortBeforeOut();

    const char SPACE = ' ';

    CDSU<T> _components;

    std::vector<std::list<T>> _componentsForOut;
};

template <class T>
CComponentsViaDSU<T>::CComponentsViaDSU(const CDSU<T>& dsu) {
    _components = dsu;
}

template <class T>
CComponentsViaDSU<T>::CComponentsViaDSU(CDSU<T>&& dsu) {
    _components = std::move(dsu);
}

template <class T>
void CComponentsViaDSU<T>::sortBeforeOut() {
    _componentsForOut.clear();
    std::unordered_map<T, std::list<T>> components = _components.getSets();
    for (auto& c : components) {
        if (std::is_same<T, std::string>::value) {
            c.second.sort(test::pred1);
        } else {
            c.second.sort();
        }
        _componentsForOut.push_back(c.second);
    }

    std::sort(_componentsForOut.begin(), _componentsForOut.end(), test::pred2<T>);
}

template <class T>
void CComponentsViaDSU<T>::print() {
    sortBeforeOut();
    printOut(std::cout);
}

template <class T>
void CComponentsViaDSU<T>::printToFile(const std::string& filepath) {
    sortBeforeOut();
    std::ofstream out(filepath);
    if (out.is_open()) {
        printOut(out);
    }
    out.close();
}

template <class T>
void CComponentsViaDSU<T>::printOut(std::ostream& out) {
    for (auto& c : _componentsForOut) {
        for (const auto& v : c) {
            out << v << SPACE;
        }
        out << std::endl;
    }
}
#endif // C_COMPONENTS_VIA_DSU_HPP