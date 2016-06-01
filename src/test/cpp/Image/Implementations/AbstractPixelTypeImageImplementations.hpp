#ifndef ABSTRACT_PIXEL_TYPE_IMAGE_IMPLEMENTATIONS_HPP
#define ABSTRACT_PIXEL_TYPE_IMAGE_IMPLEMENTATIONS_HPP

#include <string>
#include <type_traits>
#include <vector>

#include "PixelTypeName.hpp"
#include "ImplementationNameFor.hpp"
#include "TemplateAt.hpp"

template <typename PixelType, template <typename> class... Implementations>
class AbstractPixelTypeImageImplementations {
private:
    template <int index, int numberOfImplementations>
    using EnableForValidImplementation =
            typename std::enable_if<index < numberOfImplementations>::type;

    template <int index, int numberOfImplementations>
    using EnableForInvalidImplementation =
            typename std::enable_if<index >= numberOfImplementations>::type;

public:
    template <int index>
    using ImplementationAt =
            typename TemplateAt<index, Implementations...>
                    ::template Type<PixelType>;

    static constexpr unsigned int getNumberOfImplementations() {
        return countImplementations<Implementations...>();
    }

    static std::vector<std::string> getImplementationNames() {
        auto names = std::vector<std::string>();

        addImplementationNames<Implementations...>(names);

        return names;
    }

private:
    template <template <typename> class Implementation,
            template <typename> class NextImplementation,
            template <typename> class... RemainingImplementations>
    static constexpr unsigned int countImplementations() {
        return 1 + countImplementations<NextImplementation,
                RemainingImplementations...>();
    }

    template <template <typename> class LastImplementation>
    static constexpr unsigned int countImplementations() {
        return 1;
    }

    template <template <typename> class LastImplementation>
    static void addImplementationNames(std::vector<std::string>& names) {
        addImplementationName<LastImplementation>(names);
    }

    template <template <typename> class Implementation,
            template <typename> class NextImplementation,
            template <typename> class... RemainingImplementations>
    static void addImplementationNames(std::vector<std::string>& names) {
        addImplementationName<Implementation>(names);

        addImplementationNames<NextImplementation, RemainingImplementations...>
                (names);
    }

    template <template <typename> class Implementation>
    static void addImplementationName(std::vector<std::string>& names) {
        using ImplementationName = ImplementationNameFor<Implementation>;

        auto pixelType = PixelTypeName<PixelType>::name;

        names.push_back(ImplementationName::getNameUsing(pixelType));
    }
};

#endif
