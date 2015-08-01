#ifndef ABSTRACT_TEST_DATA_HPP
#define ABSTRACT_TEST_DATA_HPP

#include <initializer_list>

#include <gtest/gtest.h>

class AbstractTestData {
protected:
    enum class State { EMPTY, SETTING_UP, READY, CANCELLED };

    State state = State::EMPTY;

protected:
    void tryToRunTest() {
        if (state == State::SETTING_UP)
            finishSetUp();

        if (state == State::READY)
            runTest();
        else
            failTest();
    }

    virtual void finishSetUp() = 0;
    virtual void runTest() = 0;

    void cancelTestExecution() {
        state = State::CANCELLED;
    }

    bool stateIs(State expected) {
        if (state == expected)
            return true;
        else {
            cancelTestExecution();

            return false;
        }
    }

    bool stateIs(std::initializer_list<State> options) {
        for (State option : options) {
            if (state == option)
                return true;
        }

        cancelTestExecution();

        return false;
    }

private:
    void failTest() {
        FAIL() << "Test was incorrectly set-up";
    }
};

#endif
