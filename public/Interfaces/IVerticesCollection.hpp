#ifndef I_VERTICES_COLLECTION_HPP
#define I_VERTICES_COLLECTION_HPP

template <class T>
struct IVerticesCollection {
    virtual ~IVerticesCollection() = default;

    virtual void push(const T& vertex) = 0;

    virtual void clear() = 0;
};

#endif // I_VERTICES_COLLECTION_HPP
