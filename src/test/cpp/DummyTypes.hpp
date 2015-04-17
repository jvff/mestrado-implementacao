#ifndef DUMMY_TYPES_HPP
#define DUMMY_TYPES_HPP

template <int discriminator>
struct DummyTypes {
    int value;
};

typedef DummyTypes<0> DummyType;

#endif
