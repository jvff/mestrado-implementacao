# Master's Project Implementation #

## Summary

This library contains the implementation of the Perception module that
is planned to be used by the autonomus vehicle project of the Autonomous
Mobility Laboratory (LMA, Laboratório de Mobilidade Autônoma) of the
Mechanical Engineering Faculty (FEM, Faculdade de Engenharia Mecânica)
at Unicamp (Universidade Estadual de Campinas).

The library is implemented with C++11. The Gradle build system is used
to compile the library.

## Dependencies

To compile the library, you will need Java to run the Gradle build
system. Gradle itself isn't needed, because the wrapper script should
download the appropriate version of it automatically.  You will also
need to have the Boost Format library installed.

To run the test cases, the following libraries are required:

- Boost::range
- Google Test
- [FakeIt](https://github.com/eranpeer/FakeIt)
- [mtrace_gtest](https://bitbucket.org/jvff/mtrace_gtest)
- [asserts](https://bitbucket.org/jvff/asserts)

You can set the path to the libraries and headers in the `build.gradle`
file.

## Compiling

The library is built with the following command:

    ./gradlew assemble

## Testing

You can run all of the built-in tests running the command

    ./gradlew test

## Contributing

Feel free to send feedback, questions, suggestions, fixes, bug reports,
or anything else you think can help this project.

If you provide code, my only request is to also provide test cases of
what is being done and/or what bugs were fixed (ie. a test that fails
without the new code and passes with the new code).

Personally, I develop using TDD, so I would recommend that. However,
feel free to add tests after development if you prefer. I might reorder
the commits to push the tests first though. Also keep the tests small.
I'd rather have a million small and focused tests than one that does the
same thing but makes it hard to isolate future problems.
