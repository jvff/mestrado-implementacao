#include "AreaOpeningImplementationTest.hpp"

TEST_F(AreaOpeningImplementationTest, classTemplateExists) {
    AssertThat<ImplementationClass>::isClassOrStruct();
}

TEST_F(AreaOpeningImplementationTest, isFilterImplementation) {
    using ParentImplementation = FilterImplementation<SourceImageType,
            DestinationImageType>;

    AssertThat<ImplementationClass>::isSubClass(Of<ParentImplementation>());
}

TEST_F(AreaOpeningImplementationTest, isConstructibleWithParameters) {
    using AreaSizeParameter = unsigned int;
    using SourceImageParameter = const Image<SourcePixelType>&;
    using DestinationImageParameter = DestinationImageType&;

    AssertThat<ImplementationClass>::isConstructible(With<AreaSizeParameter,
            SourceImageParameter, DestinationImageParameter>());
}

TEST_F(AreaOpeningImplementationTest, bigPlateauIsntCleared) {
    TestData<unsigned char>()
        .setDimensions(6, 6)
        .setMaximumPeakSize(9)
        .setBackground(102)
        .drawSquare(1, 1, 4, 167);
}

TEST_F(AreaOpeningImplementationTest, smallPlateauIsCleared) {
    TestData<unsigned char>()
        .setDimensions(6, 6)
        .setMaximumPeakSize(12)
        .setBackground(13)
        .drawSquare(1, 1, 2, 201);
}

TEST_F(AreaOpeningImplementationTest, twoSmallPlateausAreCleared) {
    TestData<unsigned char>()
        .setDimensions(10, 9)
        .setMaximumPeakSize(11)
        .setBackground(148)
        .drawSquare(1, 1, 2, 252)
        .drawSquare(4, 2, 3, 251);
}
