#ifndef DUMMY_TYPES_HPP
#define DUMMY_TYPES_HPP

template <int discriminator>
struct DummyTypes {
    int value;
};

#define OPERATOR(op) \
template <int discriminator> \
bool operator op(const DummyTypes<discriminator>& lhs, \
        const DummyTypes<discriminator>& rhs) { \
    return lhs.value op rhs.value; \
}

OPERATOR(==)
OPERATOR(!=)
OPERATOR(>=)

#undef OPERATOR

typedef DummyTypes<0> DummyType;

#endif
