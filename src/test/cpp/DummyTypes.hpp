#ifndef DUMMY_TYPES_HPP
#define DUMMY_TYPES_HPP

template <int discriminator>
struct DummyTypes {
    int value;
};

template <int discriminator>
bool operator==(const DummyTypes<discriminator>& lhs,
        const DummyTypes<discriminator>& rhs) {
    return lhs.value == rhs.value;
}

template <int discriminator>
bool operator!=(const DummyTypes<discriminator>& lhs,
        const DummyTypes<discriminator>& rhs) {
    return lhs.value != rhs.value;
}

typedef DummyTypes<0> DummyType;

#endif
