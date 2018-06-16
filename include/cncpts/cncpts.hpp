#ifndef CNCPTS_CNCPTS_HPP_INCLUDED
#define CNCPTS_CNCPTS_HPP_INCLUDED

#include <type_traits>

namespace cncpts {

    namespace _ {

        template<typename... T>
        using VoidType = void;

        struct NoneSuch {
            NoneSuch(NoneSuch const&) = delete;
            NoneSuch& operator=(NoneSuch const&) = delete;
            ~NoneSuch() = delete;
        };

        template<
            typename Default,
            typename VoidTest,
            template <typename...> class Test,
            typename... Args>
        struct DetectResult {
            using value = std::false_type;
            using type = Default;
        };

        template<
            typename Default,
            template <typename...> class Test,
            typename... Args>
        struct DetectResult<Default, VoidType<Test<Args...>>, Test, Args...> {
            using value = std::true_type;
            using type = Test<Args...>;
        };
    }

    template<template <typename...> class T, typename... Args>
    using DetectedType = 
        typename _::DetectResult<_::NoneSuch, void, T, Args...>::type;

    template<template <typename...> class T, typename... Args>
    using DetectedValue = 
        typename _::DetectResult<_::NoneSuch, void, T, Args...>::value;

    template<typename Same, template <typename...> class T, typename... Args>
    using DetectedExact =
        typename std::is_same<Same, DetectedType<T, Args...>>::type;

    template<typename To, template <typename...> class T, typename... Args>
    using DetectedConvertible =
        typename std::is_convertible<DetectedType<T, Args...>, To>::type;
}

#endif //CNCPTS_CNCPTS_HPP_INCLUDED
