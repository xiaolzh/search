// Configurator (C++ library for configuration file parsing)
// http://opensource.dshevchenko.biz/configurator
//
// Copyright (C) Denis Shevchenko, 2010.
// for @ dshevchenko.biz
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// See http://www.opensource.org/licenses/mit-license.php

#ifndef CF_DETAIL_TYPES_HPP
#define CF_DETAIL_TYPES_HPP

#include <vector>
#include <set>
#include <sstream>

/// \namespace cf
/// \brief Main namespace of library.
namespace cf {

/// \namespace cf::detail
/// \brief Details of realization.
namespace detail {

typedef std::string::iterator       string_it;
typedef std::string::const_iterator string_const_it;

typedef std::vector< std::string >  str_storage;
typedef str_storage::iterator       str_it;
typedef str_storage::const_iterator str_const_it;
typedef std::vector< str_it >       iterators_to_strings;

typedef std::set< std::string >     str_set;
typedef str_set::iterator           str_unique_it;
typedef str_set::const_iterator     str_unique_const_it;

typedef std::ostringstream          o_stream;

} // namespace detail
} // namespace cf

#endif // CF_DETAIL_TYPES_HPP
