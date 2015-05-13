#ifndef UNUSED_HPP
#define UNUSED_HPP

#define UNUSED(x) ((void)x)

template <typename Type>
void unused(Type arg) {
    UNUSED(arg);
}

template<typename Head, typename... Tail>
void unused(Head head, Tail... tail) {
    UNUSED(head);
    unused(tail...);
}

#endif
