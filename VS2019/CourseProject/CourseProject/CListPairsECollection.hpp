#ifndef C_LIST_PAIRS_E_COLLECTION_HPP
#define C_LIST_PAIRS_E_COLLECTION_HPP

#include <list>
#include <vector>
#include "IEdgesCollection.hpp"

template <class T>
class CListPairsECollection : public IEdgesCollection<T> {
    using value_type = T;
    using const_reference = const value_type&;
    using collection_t = std::list<std::pair<value_type, value_type>>;
    using const_collection_ref = 
        const std::list<std::pair<value_type, value_type>>&;
public:
    virtual ~CListPairsECollection() = default;

    virtual inline void push(const_reference vertex1, const_reference vertex2) override;

    virtual inline void clear() override;

    collection_t& getCollection();
private:
    collection_t _collection;
};

template <class T>
inline void CListPairsECollection<T>::push(const_reference vertex1, const_reference vertex2) {
    _collection.emplace_back(vertex1, vertex2);
};

template <class T>
inline void CListPairsECollection<T>::clear() {
    _collection.clear();
}

template <class T>
inline std::list<std::pair<T, T>>& 
    CListPairsECollection<T>::getCollection() {
    return _collection;
}

#endif // C_LIST_PAIRS_E_COLLECTION_HPP