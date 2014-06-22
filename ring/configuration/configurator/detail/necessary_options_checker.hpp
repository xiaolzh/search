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

#ifndef CF_DETAIL_NECESSARY_OPTIONS_CHECKER_HPP
#define CF_DETAIL_NECESSARY_OPTIONS_CHECKER_HPP

#include "option.hpp"

/// \namespace cf
/// \brief Main namespace of library.
namespace cf {

/// \namespace cf::detail
/// \brief Details of realization.
namespace detail {

/// \class necessary_options_checker 
/// \brief Necessary options checker.
///
/// Checks existence of all options defined as necessary.
class necessary_options_checker {
public:
    necessary_options_checker( const options& _registered_options
                               , const std::string& _sections_separator ) :
            registered_options( _registered_options )
            , sections_separator( _sections_separator ) {}
private:
    const options& registered_options;
    const std::string& sections_separator;
public:
    void operator()( const pure_options& factual_obtained_options ) const {
        str_storage names_that_should_be = collect_names_of_necessary_options();  
        remove_names_of_inputed_necessary_options( factual_obtained_options, names_that_should_be );
        if ( !names_that_should_be.empty() ) {
            notify_about_missing_of_necessary_options( names_that_should_be );	
        } else {}
    }
private:
    str_storage collect_names_of_necessary_options() const {
        str_storage names;
    	BOOST_FOREACH ( const option& registered_option, registered_options ) {
            if ( registered_option.is_necessary ) {
            	names += registered_option.name;
            } else {}
        }
        return names;
    }
    
    void remove_names_of_inputed_necessary_options( const pure_options& factual_obtained_options
                                                    , str_storage&      names_that_should_be ) const {
        BOOST_FOREACH ( const pure_option& obtained_option, factual_obtained_options ) {
            delete_element( names_that_should_be, obtained_option.name );
        }
    }

    void notify_about_missing_of_necessary_options( const str_storage& names_that_should_be ) const {
        std::string what_happened = "Option ";
        
        BOOST_FOREACH ( const std::string& name, names_that_should_be ) {
        	what_happened += "'" + prepare_full_name_for_log( name, sections_separator ) + "', ";
        }
        boost::erase_last( what_happened, ", " );
        
        if ( 1 == names_that_should_be.size() ) {
            what_happened += " is defined as necessary, but it missed!";
        } else {
            boost::replace_first( what_happened, "Option", "Options" );
            what_happened += " are defined as necessary, but they missed!";
        }

        notify( what_happened );
    }
};

} // namespace detail
} // namespace cf

#endif // CF_DETAIL_NECESSARY_OPTIONS_CHECKER_HPP
