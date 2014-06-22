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

#ifndef CF_DETAIL_PURE_STRINGS_OBTAINER_HPP
#define CF_DETAIL_PURE_STRINGS_OBTAINER_HPP

#include "misc.hpp"

#include <boost/filesystem/fstream.hpp>

/// \namespace cf
/// \brief Main namespace of library.
namespace cf {

/// \namespace cf::detail
/// \brief Details of realization.
namespace detail {

namespace fs = boost::filesystem;

/// \class pure_strings_obtainer
/// \brief Configuration's file strings obtainer.
///
/// Obtains pure strings from configuration file.
class pure_strings_obtainer {
private:
    fs::path path_to_configuration_file;
public:
    str_storage operator()( const std::string& _path_to_configuration_file ) {
        path_to_configuration_file = _path_to_configuration_file;
        return obtained_strings();
    }

    std::string stored_path() const {
        return path_to_configuration_file.string();
    } 
private:
    str_storage obtained_strings() const {
        fs::ifstream configuration_file;
        open_file( configuration_file );
        return obtained_strings_from( configuration_file );
    }

    void open_file( fs::ifstream& configuration_file ) const {
        configuration_file.open( path_to_configuration_file );
        if ( !configuration_file.good() ) {
            notify( "Cannot open configuration file '" + path_to_configuration_file.string()
                    + "', probably you have not permissions..." );
        } else {}
    }
    
    str_storage obtained_strings_from( fs::ifstream& configuration_file ) const {
        str_storage strings;
        std::string s;
        while ( std::getline( configuration_file, s ) ) {
            boost::trim( s );
            if ( !s.empty() ) {
                strings += s;
            } else {}
        }
        return strings;
    } 
};

} // namespace detail
} // namespace cf

#endif // CF_DETAIL_PURE_STRINGS_OBTAINER_HPP
