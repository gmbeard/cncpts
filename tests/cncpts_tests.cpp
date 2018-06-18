#include "cncpts/cncpts.hpp"
#include <iostream>
#include <forward_list>
#include <vector>

namespace ops {
    template<typename T>
    using RandomAccess = decltype(std::declval<T>() + static_cast<size_t>(0));
}

namespace traits {
    namespace adl {
        using std::begin;

        template<typename T>
        using ConstIterator = decltype(begin(std::declval<T const&>()));
    }

    template<typename T>
    using ConstIterator = adl::ConstIterator<T>;

    template<typename T>
    using ValueType = 
        typename std::remove_reference<decltype(*std::declval<T>())>::type;
}

template<typename T>
constexpr bool IsRandomAccess =
    cncpts::All<
        cncpts::DetectedValue<
            ops::RandomAccess,
            cncpts::DetectedType<traits::ConstIterator, T>>,
        cncpts::DetectedExact<
            int const,
            traits::ValueType,
            cncpts::DetectedType<traits::ConstIterator, T>>
    >::value;
        
auto main(int, char const**) -> int {

    using IntList = std::forward_list<int>;
    using IntVector = std::vector<int>;

    static_assert(
        IsRandomAccess<IntVector>,
        "type should have a random access, const_iterator"
    );

    static_assert(
        !IsRandomAccess<IntList>,
        "type shouldn't have a random access, const_iterator"
    );

    return 0;
}

