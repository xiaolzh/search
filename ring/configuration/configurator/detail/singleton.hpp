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

#ifndef CF_DETAIL_SINGLETON_HPP
#define CF_DETAIL_SINGLETON_HPP

#include <boost/thread.hpp>
#include <boost/noncopyable.hpp>

#include <cstdlib>

/// \namespace cf
/// \brief Main namespace of library.
namespace cf {

/// \namespace cf::detail
/// \brief Details of realization.
namespace detail {

/// \class singleton
/// \brief Realization of 'Singleton' pattern.
///
/// Based on 'Singleton Alexandrescu'.
template< typename T >
class singleton : boost::noncopyable {
public:
    static boost::mutex mutex;
private:
    static T* t;
public: 
    static T& inst() {
        if ( 0 == t ) {
            boost::mutex::scoped_lock lock( mutex );
            if ( 0 == t ) {  
                t = new T();
                ::atexit( destroy );
            } else {}
        } else {}
        return *t;
    }
private:
    static void destroy() {
        boost::mutex::scoped_lock lock( mutex );
        delete t;
        t = 0;
    }
};

template< typename T >
boost::mutex singleton< T >::mutex;

template< typename T >
T* singleton< T >::t = 0;

} // namespace detail
} // namespace cf

#endif // CF_DETAIL_SINGLETON_HPP
