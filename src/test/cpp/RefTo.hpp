#ifndef REF_TO_HPP
#define REF_TO_HPP

#include "fakeit.hpp"

template <typename T>
struct RefToMatcherCreator : public fakeit::TypedMatcherCreator<T> {
private:
    const T& expected;

public:
    RefToMatcherCreator(const T& arg) : expected(arg) {
    }

    virtual fakeit::TypedMatcher<T>* createMatcher() const override {
        return new Matcher(expected);
    }

    struct Matcher : public fakeit::TypedMatcher<T> {
    private:
        const T& expected;

    public:
        Matcher(const T& arg) : expected(arg) {
        }

        virtual bool matches(const T& actual) const override {
            return &actual == &expected;
        }

        virtual std::string format() const override {
            return fakeit::Formatter<T>::format(this->expected);
        }
    };
};

template <typename T>
RefToMatcherCreator<T> RefTo(const T& arg) {
    return RefToMatcherCreator<T>(arg);
}

#endif
