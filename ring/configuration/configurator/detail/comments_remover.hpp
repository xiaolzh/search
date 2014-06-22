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

#ifndef CF_DETAIL_COMMENTS_REMOVER_HPP
#define CF_DETAIL_COMMENTS_REMOVER_HPP

#include "misc.hpp"

#include <boost/foreach.hpp>
#include <boost/mem_fn.hpp>
#include <boost/assign.hpp>

#include <iostream>

/// \namespace cf
/// \brief Main namespace of library.
namespace cf {

/// \namespace cf::detail
/// \brief Details of realization.
namespace detail {

using namespace boost::assign;

/// \class comments_remover
/// \brief Comments remover.
///
/// Removes one-line comments and multi-line comments.
class comments_remover {
public:
    comments_remover() :
            one_line_comment_sign( "//" )
            , multi_line_comment_begin_sign( "/*" )
            , multi_line_comment_end_sign( "*/" ) {}
private:
    std::string       one_line_comment_sign;
    const std::string multi_line_comment_begin_sign;
    const std::string multi_line_comment_end_sign;
public:
    void use_canonical_one_line_comments() {
        one_line_comment_sign = "#";
    }
public:
    void operator()( str_storage& obtained_strings ) const {
        remove_one_line_comments_from( obtained_strings );
        remove_multi_line_comments_from( obtained_strings );
        remove_empty_strings_from( obtained_strings );
    }
private:
    void remove_one_line_comments_from( str_storage& obtained_strings ) const {
        BOOST_FOREACH ( std::string& s, obtained_strings ) {
            if ( one_line_comment_in_this( s ) ) {
                remove_one_line_comment_from_this( s );
            } else {}
        }
    }
    
    bool one_line_comment_in_this( const std::string& s ) const {
        return boost::contains( s, one_line_comment_sign );
    }

    void remove_one_line_comment_from_this( std::string& s ) const {
        s.erase( boost::find_first( s, one_line_comment_sign ).begin()
                 , s.end() );
    }
private:
    void remove_multi_line_comments_from( str_storage& obtained_strings ) const {
        align_multi_line_comments_in( obtained_strings ); 
        remove_aligned_multi_line_comments_from( obtained_strings );
    } 
    
    void align_multi_line_comments_in( str_storage& obtained_strings ) const {
        bool waiting_for_comment_closing = false; 
        str_it last_string;

        for ( str_it it = obtained_strings.begin(); obtained_strings.end() != it; ++it ) {
            std::string& s = *it;

            if ( waiting_for_comment_closing ) {
                if ( comment_closing_in_this( s ) ) {
                    waiting_for_comment_closing = false;
                } else {}
                *last_string += s;
                s.clear();
            } else {
                check_unopened_multi_line_comment_in( s );
                string_it begin_of_comment = boost::find_first( s, multi_line_comment_begin_sign ).begin();
                if ( s.end() != begin_of_comment ) {
                    if ( comment_closing_in_this( s ) ) {
                        remove_multi_line_comment_from_this( s, begin_of_comment );
                    } else {
                        waiting_for_comment_closing = true;
                        last_string = it;
                    }
                } else {}
            }
        }

        check_unclosed_multi_line_comment( waiting_for_comment_closing );
    }

    bool comment_closing_in_this( const std::string& s ) const {
        return boost::contains( s, multi_line_comment_end_sign );
    }

    void remove_aligned_multi_line_comments_from( str_storage& obtained_strings ) const {
        BOOST_FOREACH ( std::string& s, obtained_strings ) {
            string_it begin_of_comment = boost::find_first( s, multi_line_comment_begin_sign ).begin();
            if ( s.end() != begin_of_comment ) {
                remove_multi_line_comment_from_this( s, begin_of_comment ); 
            } else {}
        }
    }

    void remove_multi_line_comment_from_this( std::string& s, string_it begin_of_comment ) const {
        s.erase( begin_of_comment
                 , boost::find_first( s, multi_line_comment_end_sign ).end() );
    }
    
    void check_unopened_multi_line_comment_in( const std::string& s ) const {
        if ( !boost::contains( s, multi_line_comment_begin_sign ) 
             && boost::contains( s, multi_line_comment_end_sign ) ) {
            notify( "Unopened multi-line comment detected!" );
        } else {}
    }
    
    void check_unclosed_multi_line_comment( bool waiting_for_comment_closing ) const {
        if ( waiting_for_comment_closing ) {
            notify( "Unclosed multi-line comment detected!" );
        } else {}
    }
private:
    void remove_empty_strings_from( str_storage& obtained_strings ) const {
        obtained_strings.erase( std::remove_if( obtained_strings.begin()
                                                , obtained_strings.end()
                                                , boost::mem_fn( &std::string::empty ) )
				                , obtained_strings.end() );
    }
};

} // namespace detail
} // namespace cf

#endif // CF_DETAIL_COMMENTS_REMOVER_HPP
