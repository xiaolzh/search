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

#ifndef CF_DETAIL_OPTION_HPP
#define CF_DETAIL_OPTION_HPP

#include "misc.hpp"

#include <boost/ptr_container/ptr_vector.hpp>

/// \namespace cf
/// \brief Main namespace of library.
namespace cf {

/// \namespace cf::detail
/// \brief Details of realization.
namespace detail {

/// \class option
/// \brief One option.
///
/// Presents functionality of one configuration option.
class option {
public:    
    explicit option( const std::string& full_name, const std::string& _sections_separator ) :
            sections_separator( _sections_separator )
            , name( full_name )
            , value()
            , semantic( no_semantic )
            , is_necessary( false )
            , multi_values_allowed( false ) {}
private:
    const std::string& sections_separator;
public:
    std::string name;
    std::string value;
    value_semantic semantic;
    bool is_necessary;
    bool multi_values_allowed;
public:
    bool operator==( const std::string& full_name ) const {
        return full_name == name;
    }
private:
    std::string default_value_reserve;
public:
    void use_default_value_reserve() {
        if ( !default_value_reserve.empty() ) {
            value = default_value_reserve;
        } else {}
    }
public:
    template< typename ValueType >
    option& default_value( const ValueType& _value ) {
        check_option_necessity();
        try {
            value = boost::lexical_cast< std::string >( _value );
            default_value_reserve = value;
        } catch ( const std::exception& /* exc */ ) {
            notify( "Default value for option '" + name + "' cannot be stringified!" );
        }
        return *this;
    }
private:
    void check_option_necessity() const {
        if ( is_necessary ) {
            notify( "Option '"
                    + prepare_full_name_for_log( name, sections_separator )
                    + "' registered as necessary, so it cannot have default_value!" );
        } else {}
    }
public:
    option& default_value( const std::string& _value ) {
        value.assign( _value.begin(), _value.end() );
        return *this;
    }
public:
    option& necessary() {
        check_default_value_existence();
        is_necessary = true;
        return *this;
    }
private:
    void check_default_value_existence() const {
        if ( !value.empty() ) {
            notify( "Option '"
                    + prepare_full_name_for_log( name, sections_separator )
                    + "' already have default value '" + value + "', "
                    + "so it cannot be necessary!" );
        } else {}
    }
public:
    option& check_semantic( const value_semantic& _semantic ) {
        semantic = _semantic;
        return *this;
    }

    bool semantic_defined() const {
        return no_semantic != semantic;
    }
public:
    option& allow_multi_values() {
        multi_values_allowed = true;
        return *this;
    }
public:
    bool already_has_default_value() const {
        return !value.empty();
    }

    bool it_is_necessary() const {
        return is_necessary;
    }

    bool empty() const {
        return value.empty();
    }
};

/// \struct pure_option
/// \brief 
///
/// Presents pure option obtained from configuration file.
struct pure_option {
    pure_option() {}
    pure_option( const std::string& _name, const std::string& _value ) :
            name( _name ), value( _value ) {}
public:
    std::string name;
    std::string value;
public:
    bool empty() const {
        return value.empty();
    }

    bool operator==( const std::string& _name ) const {
        return _name == name;
    }

    bool operator==( const pure_option& another ) const {
        return another.name == name;
    }
};

inline bool operator<( const pure_option& left, const pure_option& right ) {
    return left.name < right.name;
}

} // namespace detail

typedef detail::option              option;

typedef boost::ptr_vector< option > options;
typedef options::iterator           option_it;
typedef options::const_iterator     option_const_it;

typedef detail::pure_option         pure_option;
typedef std::vector< pure_option >  pure_options;
typedef pure_options::iterator      pure_option_it;

} // namespace cf

#endif // CF_DETAIL_OPTION_HPP
