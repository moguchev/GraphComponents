#ifndef C_COMPONENTS_VIA_LISTS_HPP
#define C_COMPONENTS_VIA_LISTS_HPP

#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include "IGraphComponents.hpp"


template <class T>
class CComponentsViaLists : public IGraphComponents<T> {
    using lists_t = std::list<std::list<T>>;
public:
    CComponentsViaLists() = default;

    virtual ~CComponentsViaLists() = default;

    virtual void print() override;

    virtual void printToFile(const std::string& filename) override;

    void push(std::list<T>&& componet);

private:
    void printOut(std::ostream& out);

    void sortBeforeOut();

    const char SPACE = ' ';
    lists_t _components;
};

template <class T>
void CComponentsViaLists<T>::print() {
    sortBeforeOut();
    printOut(std::cout);
}

template <class T>
void CComponentsViaLists<T>::printToFile(const std::string& filepath) {
    sortBeforeOut();
    std::ofstream out(filepath);
    if (out.is_open()) {
        printOut(out);
    }
    out.close();
}

template <class T>
void CComponentsViaLists<T>::push(std::list<T>&& component) {
    _components.push_back(std::move(component));
}

template <class T>
void CComponentsViaLists<T>::sortBeforeOut() {
    for (auto& c : _components) {
        c.sort(test::pred1);
    }
    _components.sort(test::pred2<T>);
}

template <class T>
void CComponentsViaLists<T>::printOut(std::ostream& out) {
    for (auto& c : _components) {
        for (const auto& v : c) {
            out << v << SPACE;
        }
        out << std::endl;
    }
}

#endif // C_COMPONENTS_VIA_LISTS_HPP