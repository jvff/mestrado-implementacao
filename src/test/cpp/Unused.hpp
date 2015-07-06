#ifndef UNUSED_HPP
#define UNUSED_HPP

#define UNUSED(x) ((void)x)

template <typename Type>
void unused(const Type& arg) {
    UNUSED(arg);
}

template<typename Head, typename... Tail>
void unused(const Head& head, const Tail&... tail) {
    UNUSED(head);
    unused(tail...);
}

#endif
