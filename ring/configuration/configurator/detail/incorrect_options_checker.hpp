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

#ifndef CF_DETAIL_INCORRECT_OPTIONS_CHECKER_HPP
#define CF_DETAIL_INCORRECT_OPTIONS_CHECKER_HPP

#include "option.hpp"

/// \namespace cf
/// \brief Main namespace of library.
namespace cf {

/// \namespace cf::detail
/// \brief Details of realization.
namespace detail {

/// \class incorrect_options_checker
/// \brief Incorrect options checker.
///
/// Checks existence of incorrect (unregistered) options.
class incorrect_options_checker {
public:
    incorrect_options_checker( const options& _registered_options
                               , const std::string& _sections_separator ) :
            registered_options( _registered_options )
            , sections_separator( _sections_separator ) {}
private:
    const options& registered_options;
    const std::string& sections_separator;
public:
    void operator()( const pure_options& factual_obtained_options ) {
        BOOST_FOREACH ( const pure_option& option, factual_obtained_options ) {
            const std::string name = option.name;
            option_const_it it = std::find( registered_options.begin()
                                            , registered_options.end()
                                            , name );
            if ( registered_options.end() == it ) {
                store_incorrect_option( name );
            } else {}
        }

        notify_about_incorrect_options_if_such_exists();
    }
private:
    str_storage incorrect_options;
private:
    void store_incorrect_option( const std::string& option_name ) {
        incorrect_options += option_name;
    }

    void notify_about_incorrect_options_if_such_exists() const {
        if ( incorrect_options.empty() ) {
            return;
        } else {}
        
        std::string what_happened = "Incorrect option detected in configuration file:\n"; 
        if ( incorrect_options.size() > 1 ) {
            boost::replace_all( what_happened, "option", "options" );
        } else {}
        BOOST_FOREACH ( const std::string& option, incorrect_options ) {
            what_happened += "'" + prepare_full_name_for_log( option, sections_separator ) + "'\n";
        }
        boost::erase_last( what_happened, "\n" );
        notify( what_happened );
    }
};

} // namespace detail
} // namespace cf

#endif // CF_DETAIL_INCORRECT_OPTIONS_CHECKER_HPP
