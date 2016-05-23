#ifndef TEMPLATE_AT_HPP
#define TEMPLATE_AT_HPP

template <int index, template <typename> class Head,
        template <typename> class... Tail>
struct TemplateAt {
    template <typename T>
    using Type = typename TemplateAt<index - 1, Tail...>::template Type<T>;
};

template <template <typename> class Head, template <typename> class... Tail>
struct TemplateAt<0, Head, Tail...> {
    template <typename T>
    using Type = Head<T>;
};

#endif
