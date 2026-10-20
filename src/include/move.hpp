#pragma once

template<typename T>
struct remove_reference { using type = T; };

template<typename T>
struct remove_reference<T&> { using type = T; };

template<typename T>
struct remove_reference<T&&> { using type = T; };

template<typename T>
using remove_reference_t = typename remove_reference<T>::type;

template<typename T>
constexpr auto move(T&& obj) noexcept 
    -> remove_reference_t<T>&&
{
    return static_cast<remove_reference_t<T>&&>(obj);
}
