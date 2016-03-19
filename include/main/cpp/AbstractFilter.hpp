#ifndef ABSTRACT_FILTER_HPP
#define ABSTRACT_FILTER_HPP

template <typename SourceImageType, typename DestinationImageType>
class AbstractFilter {
public:
    virtual ~AbstractFilter() {
    }

    DestinationImageType apply(const SourceImageType& sourceImage) {
        return createDestinationImage(sourceImage);
    }

protected:
    virtual DestinationImageType createDestinationImage(
            const SourceImageType& sourceImage) = 0;
};

#endif
