// stringcase.hpp
//
// Copyright (c) 2009 Michael Thomas Greer
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt

#pragma once
#ifndef STRINGCASE_HPP
#define STRINGCASE_HPP

#include <algorithm>
#include <cctype>
#include <functional>
#include <string>

template <typename CharType, typename TraitsType, typename AllocType>
std::basic_string <CharType, TraitsType, AllocType>
uppercase( const std::basic_string <CharType, TraitsType, AllocType> & s )
  {
  std::basic_string <CharType, TraitsType, AllocType> result( s.length(), '\0' );
  std::transform(
    s.begin(),
    s.end(),
    result.begin(),
    std::ptr_fun <int, int> ( std::toupper )
    );
  return result;
  }

template <typename CharType, typename TraitsType, typename AllocType>
std::basic_string <CharType, TraitsType, AllocType>
lowercase( const std::basic_string <CharType, TraitsType, AllocType> & s )
  {
  std::basic_string <CharType, TraitsType, AllocType> result( s.length(), '\0' );
  std::transform(
    s.begin(),
    s.end(),
    result.begin(),
    std::ptr_fun <int, int> ( std::tolower )
    );
  return result;
  }

template <typename CharType, typename TraitsType, typename AllocType>
std::basic_string <CharType, TraitsType, AllocType>
titlecase( const std::basic_string <CharType, TraitsType, AllocType> & s )
  {
  std::basic_string <CharType, TraitsType, AllocType> result = lowercase( s );
  typename std::basic_string <CharType, TraitsType, AllocType> ::iterator iter = result.begin();
  while (iter != result.end())
    {
    *iter = toupper( *iter );
    iter = std::find_if( iter, result.end(), std::not1( std::ptr_fun <int, int> ( std::isalpha ) ) );
    iter = std::find_if( iter, result.end(),            std::ptr_fun <int, int> ( std::isalpha )   );
    }
  return result;
  }

#endif
