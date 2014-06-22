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

#ifndef CF_DETAIL_SEMANTIC_CHECKER_HPP
#define CF_DETAIL_SEMANTIC_CHECKER_HPP

#include "option.hpp"
#include "validators.hpp"

#include <boost/function.hpp>
#include <boost/bind.hpp>

#include <map>

/// \namespace cf
/// \brief Main namespace of library.
namespace cf {

/// \namespace cf::detail
/// \brief Details of realization.
namespace detail {

/// \class semantic_checker
/// \brief Semantic's checker.
///
/// Checks semantic of option's values,
/// if it defined.
class semantic_checker {
    typedef boost::function< void ( const std::string& /* arg */
                                    , const std::string& /* option name */ ) >
            check_func;

    typedef std::map
                < 
                    const value_semantic
                    , const check_func
                >
            checkers;
public:
    semantic_checker( options& _registered_options
                      , const std::string& _sections_separator ) :
            registered_options( _registered_options )
            , sections_separator( _sections_separator )
            , check_size_validity( registered_options, sections_separator )
            , check_time_period_validity( registered_options, sections_separator )
            , check_exp_record_validity( registered_options, sections_separator ) {
        insert( semantic_checkers )( path,  check_path_existence )
                                   ( ipv4,  check_ipv4_validity )
                                   ( ipv6,  check_ipv6_validity )
                                   ( ip,    check_ip_validity )
                                   ( email, check_email_validity )
                                   ( size,  boost::bind( &size_validator::check
                                                         , &check_size_validity
                                                         , _1
                                                         , _2 ) )
                                   ( time_period, boost::bind( &time_period_validator::check
                                                               , &check_time_period_validity
                                                               , _1
                                                               , _2 ) )
                                   ( exp_record, boost::bind( &exp_record_validator::check
                                                               , &check_exp_record_validity
                                                               , _1
                                                               , _2 ) )
                                   ;
    }
private:
    options&                registered_options;
    const std::string&      sections_separator;
    size_validator          check_size_validity;
    time_period_validator   check_time_period_validity;
    exp_record_validator    check_exp_record_validity;
    checkers                semantic_checkers;
public:
    void operator()() {
        BOOST_FOREACH ( option& registered_option, registered_options ) {
            if ( !registered_options.empty() 
                 && registered_option.semantic_defined() ) {
                const std::string& value = registered_option.value;
                const std::string name = prepare_full_name_for_log( registered_option.name
                                                                    , sections_separator );
                semantic_checkers.at( registered_option.semantic )( value, name );
            } else {}
        }
    }
};

} // namespace detail
} // namespace cf

#endif // CF_DETAIL_SEMANTIC_CHECKER_HPP
