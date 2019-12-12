#ifndef C_U_MAP_V_COLLECTION_HPP
#define C_U_MAP_V_COLLECTION_HPP

#include <unordered_map>
#include <utility>

template <class T>
class CUMapVCollection : public IVerticesCollection<T> {
    using container_um_t = std::unordered_map<T, bool>;
    using value_type = T;
    using const_reference = const value_type&;
public:
    virtual ~CUMapVCollection() = default;

    virtual inline void push(const_reference vertex);

    virtual inline void clear();

    container_um_t& getCollection();
private:
    container_um_t _container;
};

template <class T>
inline void CUMapVCollection<T>::push(const_reference vertex) {
    _container[vertex] = false;
}

template <class T>
inline void CUMapVCollection<T>::clear() {
    _container.clear();
}

template <class T>
inline std::unordered_map<T, bool>& CUMapVCollection<T>::getCollection() {
    return _container;
}

#endif // C_U_MAP_V_COLLECTION_HPP