#ifndef I_GRAPH_COMPONENTS_HPP
#define I_GRAPH_COMPONENTS_HPP

#include <functional>
#include <string>


template <class T>
struct IGraphComponents {
    virtual ~IGraphComponents() = default;

    virtual void print() = 0;

    virtual void printToFile(const std::string& filename) = 0;
};

namespace test {
    std::function<bool(const std::string& x, const std::string& y)> pred1 =
        [](const std::string& x, const std::string& y) {
        auto dx = std::atof(x.c_str());
        auto dy = std::atof(y.c_str());
        if (dx == 0.0 && dy == 0.0) {
            return x < y;
        } else {
            return dx < dy;
        }
    };

    template <class T>
    std::function<bool(const std::list<T>& x, const std::list<T>& y)> pred2 =
        [](const std::list<T>& x, const std::list<T>& y) {
        if (x.size() > 0 && y.size() > 0) {
            if (std::is_same<T, std::string>::value) {
                return pred1(x.front(), y.front());
            } else {
                return x.front() < y.front();
            }
        } else {
            return y.size() > 0;
        }
    };
} // test

#endif // I_GRAPH_COMPONENTS_HPP
