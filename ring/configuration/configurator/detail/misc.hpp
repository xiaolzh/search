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

#ifndef CF_DETAIL_MISC_HPP
#define CF_DETAIL_MISC_HPP

#include "types.hpp"

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/operations.hpp>

/// \namespace cf
/// \brief Main namespace of library.
namespace cf {

inline void notify( const std::string& notification ) {
    const std::string what_happened = "[Configurator] " + notification;
    throw std::runtime_error( what_happened );
}

/// \enum value_semantic 
/// \brief Value semantic types (for check).
enum value_semantic {
    no_semantic			/*!< Default value. */
	, path				/*!< Path semantics check. */
	, ipv4				/*!< IPv4 semantics check. */
    , ipv6              /*!< IPv6 semantics check. */
    , ip                /*!< IP semantics check. */
    , email             /*!< E-mail semantics check. */
    , size              /*!< Size semantics check. */
    , time_period       /*!< Time period semantics check. */
    , exp_record        /*!< Exponential record semantics check. */
};

/// \namespace cf::detail
/// \brief Details of realization.
namespace detail {

inline std::string sections_separator_for_log() { return " > "; }

template< typename T >
inline std::string to_str( const T& t ) {
    std::string as_string; 
    try {
        as_string = boost::lexical_cast< std::string >( t );
    } catch ( const std::exception& /* exc */ ) {
        notify( "Value cannot be present as std::string!" );
    }
    return as_string;
}

template
<
    typename STLContainer
    , typename Element
>
inline void delete_element( STLContainer& cont, const Element& element ) {
    cont.erase( std::remove( cont.begin(), cont.end(), element )
				, cont.end() );
}

inline void notify_without_prefix( const std::string& notification ) {
    throw std::runtime_error( notification );
}

inline void pure_check_path_existence( const std::string& _path ) {
    boost::filesystem::path path( _path );
    
    const std::string full_path_name = path.string();
    const std::string path_name      = path.parent_path().string();
    const std::string file_name      = path.filename();

    if ( boost::filesystem::exists( path_name ) ) {
        if ( !boost::filesystem::exists( full_path_name ) ) {
            notify_without_prefix( "directory '" + path_name + "' exists, but there is no file '" + file_name + "'!" );
        } else {}
    } else {
        notify_without_prefix( "directory '" + path_name + "' not exists!" );
    }	
}

inline std::string prepare_full_name_for_log( const std::string& full_name_of_option
                                              , const std::string& sections_separator ) {
    std::string s( full_name_of_option.begin(), full_name_of_option.end() );
    boost::replace_all( s, sections_separator, sections_separator_for_log() );
    string_const_it last_separator_end = boost::find_last( s, sections_separator_for_log() ).end();
    if ( s.end() == last_separator_end ) {
        boost::erase_last( s, sections_separator_for_log() );
    } else {}
    return s;
}

} // namespace detail
} // namespace cf

#endif // CF_DETAIL_MISC_HPP
