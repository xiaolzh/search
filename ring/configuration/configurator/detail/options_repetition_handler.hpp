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

#ifndef CF_DETAIL_OPTIONS_REPETITION_HANDLER_HPP
#define CF_DETAIL_OPTIONS_REPETITION_HANDLER_HPP

#include "misc.hpp"

#include <boost/filesystem/fstream.hpp>

/// \namespace cf
/// \brief Main namespace of library.
namespace cf {

/// \namespace cf::detail
/// \brief Details of realization.
namespace detail {

namespace fs = boost::filesystem;

/// \class options_repetition_handler
/// \brief Options repetition handler.
///
/// Handle repetition of factual obtained option,
/// with corresponding checks.
class options_repetition_handler {
public:
    options_repetition_handler( const options&       _registered_options
                                , const std::string& _sections_separator ) :
            registered_options( _registered_options )
            , sections_separator( _sections_separator ) {}
private:
    const options& registered_options;
    const std::string& sections_separator;
public:
    void operator()( pure_options& factual_obtained_options ) const {
        std::sort( factual_obtained_options.begin(), factual_obtained_options.end() );
        pure_options unique_options = retrieve_unique_options_from( factual_obtained_options );

        if ( no_repetition( unique_options, factual_obtained_options ) ) {
            return;
        } else {}

        BOOST_FOREACH ( const pure_option& unique_option, unique_options ) {
            const std::string name = unique_option.name;
            pure_option_it first_repeating = std::find( factual_obtained_options.begin()
                                                        , factual_obtained_options.end()
                                                        , name );
            if ( factual_obtained_options.end() != first_repeating ) {
                size_t how_many_times_it_repeats = (size_t)std::count( factual_obtained_options.begin()
                                                                        , factual_obtained_options.end()
                                                                        , name );
                if ( 1 == how_many_times_it_repeats ) {
                    continue;
                } else {}

                check_multi_values_allowance( *first_repeating );

                std::string values_buffer;

                for ( pure_option_it it = first_repeating;
                      it != first_repeating + how_many_times_it_repeats;
                      ++it ) {
                    values_buffer += it->value + " ";
                    it->value.clear();
                }

                first_repeating->value = values_buffer;
            } else {}
        }
        
        remove_empty_options_from( factual_obtained_options );
    }
private:
    pure_options retrieve_unique_options_from( const pure_options& factual_obtained_options ) const {
        pure_options unique_options( factual_obtained_options.size() );
        pure_option_it repeating_end = std::unique_copy( factual_obtained_options.begin()
                                                         , factual_obtained_options.end()
                                                         , unique_options.begin() );
        unique_options.erase( repeating_end, unique_options.end() );
        return unique_options;
    }
    
    bool no_repetition( const pure_options& unique_options, const pure_options& factual_obtained_options ) const {
        return unique_options.size() == factual_obtained_options.size();
    }

    void check_multi_values_allowance( const pure_option& factual_obtained_option ) const {
        const std::string name = factual_obtained_option.name;
        option_const_it it = std::find( registered_options.begin()
                                        , registered_options.end()
                                        , name );
        if ( registered_options.end() != it ) {
            if ( !it->multi_values_allowed ) {
                notify( "Option '" + prepare_full_name_for_log( name, sections_separator )
                        + "' has multiple values, but it not allowed to have multiply values!" );
            } else {}
        } else {}
    } 

    void remove_empty_options_from( pure_options& factual_obtained_options ) const {
        factual_obtained_options.erase( std::remove_if( factual_obtained_options.begin()
                                                        , factual_obtained_options.end()
                                                        , boost::mem_fn( &pure_option::empty ) )
				                        , factual_obtained_options.end() );
    }
};

} // namespace detail
} // namespace cf

#endif // CF_DETAIL_OPTIONS_REPETITION_HANDLER_HPP
