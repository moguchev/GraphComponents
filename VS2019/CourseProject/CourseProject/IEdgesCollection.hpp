#ifndef I_EDGES_COLLECTION_HPP
#define I_EDGES_COLLECTION_HPP

template <class T>
struct IEdgesCollection {
    virtual ~IEdgesCollection() = default;

    virtual void push(const T& vertex1, const T& vertex2) = 0;

    virtual void clear() = 0;
};

#endif // I_EDGES_COLLECTION_HPP
