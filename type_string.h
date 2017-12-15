#pragma once
#include <type_traits>
#include <utility>

namespace zpp 
{

/**
 * Represents a type string.
 */
template <typename CharType, CharType... Char>
struct type_string {};

namespace type_string_detail
{

/**
 * Makes the type string given the string via the String type, with the help of an index sequence.
 */
template <typename String, std::size_t... Indices>
constexpr auto make_type_string(std::index_sequence<Indices...>) noexcept
{
    return type_string<
        std::remove_cv_t<std::remove_reference_t<decltype(String::get()[0])>>,
        String::get()[Indices]...
    >();
}

/**
 * The function receives the String type, and returns a type string object.
 */
template <typename String>
constexpr auto make_type_string(String) noexcept
{
    return make_type_string<String>(std::make_index_sequence<
        std::extent_v<std::remove_reference_t<decltype(String::get())>> - 1
    >());    
}

/**
 * Returns an object of type string type representing the given string.
 */
#define ZPP_MAKE_TYPE_STRING(string) \
    ::zpp::type_string_detail::make_type_string( \
        []() { \
            struct _ { \
                static constexpr decltype(auto) get() { return (string); } \
            }; return _(); \
        }() \
    )

} // type_string_detail
} // zpp

