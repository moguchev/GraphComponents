#ifndef C_DSU_HPP
#define C_DSU_HPP

#include <functional>
#include <optional>
#include <unordered_map>

template <class T>
class CDSU {
    using parent_t = std::unordered_map<T, T>;
    using rank_t = std::unordered_map<T, size_t>;
    using value_type = T;
    using const_reference = const value_type&;
public:
    CDSU() = default;

    ~CDSU() = default;

    CDSU(const CDSU<T>& dsu);

    CDSU(CDSU<T>&& dsu);

    CDSU& operator=(const CDSU<T>& dsu) noexcept;

    CDSU& operator=(CDSU<T>&& dsu) noexcept;

    void makeSet(const_reference element);

    std::optional<value_type> findSet(const_reference element);

    void unionSets(const_reference first, const_reference second);

    std::unordered_map<T, std::list<T>> getSets();
private:
    parent_t _parent;
    rank_t _rank;
};

template<class T>
CDSU<T>::CDSU(const CDSU<T>& dsu) {
    this->_parent(dsu._parent);
    this->_rank(dsu._rank);
}

template<class T>
CDSU<T>::CDSU(CDSU<T>&& dsu) {
    this->_parent(std::move(dsu._parent));
    this->_rank(std::move(dsu._rank));
}

template<class T>
CDSU<T>& CDSU<T>::operator=(const CDSU<T>& dsu) noexcept {
    this->_parent = dsu._parent;
    this->_rank = dsu._rank;
    return *this;
}

template<class T>
CDSU<T>& CDSU<T>::operator=(CDSU<T>&& dsu) noexcept {
    this->_parent = std::move(dsu._parent);
    this->_rank = std::move(dsu._rank);
    return *this;
}

template<class T>
void CDSU<T>::makeSet(const_reference element) {
    if (_parent.find(element) == _parent.end()) {
        _parent[element] = element;
        _rank[element] = 0;
    }
}

template<class T>
std::optional<T> CDSU<T>::findSet(const_reference element) {
    if (_parent.find(element) == _parent.end()) {
        return std::nullopt;
    }
    if (element == _parent[element]) {
        return element;
    }
    return _parent[element] = findSet(_parent[element]).value();
}

template<class T>
void CDSU<T>::unionSets(const_reference first, const_reference second) {
    auto firstSet = findSet(first);
    auto secondSet = findSet(second);

    if (secondSet && firstSet) {
        if (firstSet.value() != secondSet.value()) {
            if (_rank[firstSet.value()] < _rank[secondSet.value()]) {
                std::swap(firstSet, secondSet);
            }
            _parent[secondSet.value()] = firstSet.value();
            if (_rank[firstSet.value()] == _rank[secondSet.value()]) {
                _rank[firstSet.value()] += 1;
            }
        }
    }
}

template <class T>
std::unordered_map<T, std::list<T>>  CDSU<T>::getSets() {
    std::unordered_map<T, std::list<T>> map;
    for (auto element : _parent) {
        auto set = findSet(element.first);
        map[set.value()].push_back(element.first);
    }

    return map;
}

#endif // C_DSU_HPP

