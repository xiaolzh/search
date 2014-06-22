// Configurator (C++ library for configuration file parsing)
// http://opensource.dshevchenko.biz/configurator
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

#ifndef CF_CONFIGURATOR_HPP
#define CF_CONFIGURATOR_HPP

#include "detail/option.hpp"
#include "detail/validators.hpp"
#include "detail/comments_remover.hpp"
#include "detail/pure_strings_obtainer.hpp"
#include "detail/pure_options_obtainer.hpp"
#include "detail/incorrect_options_checker.hpp"
#include "detail/necessary_options_checker.hpp"
#include "detail/semantic_checker.hpp"
#include "detail/options_repetition_handler.hpp"

#ifdef WITH_SINGLETON
#include "detail/singleton.hpp"
#endif

/// \namespace cf
/// \brief Main namespace of library.
namespace cf {

/// \class configurator
/// \brief Configurator.
///
/// Core class.
class configurator : boost::noncopyable {
public:
    configurator() :
            option_name_value_separator( "=" )
            , sections_separator( "::" )
            , case_sensitivity_for_names( false )
            , options_obtainer( option_name_value_separator
                                , sections_separator
                                , unique_names_of_sections
                                , case_sensitivity_for_names )
            , check_incorrect_options( registered_options, sections_separator )
            , check_necessary_options( registered_options, sections_separator )
            , check_all_options_values_semantic( registered_options, sections_separator )
            , handle_options_repetition( registered_options, sections_separator )
            , reparsing( false ) {}
private:
    std::string         option_name_value_separator;
    const std::string   sections_separator;
public:
    void set_name_value_separator( char new_separator ) {
        check_separator_validity( new_separator );
        option_name_value_separator = new_separator;
    }
private:
    void check_separator_validity( char new_separator ) const {
        const int ascii_code = new_separator;
        if ( ascii_code < 0x20 ) {
            notify( "Symbol (ASCII-code is "
                    + detail::to_str( new_separator )
                    + ") is not suitable for name-value separator!" );
        } else {}
    }
private:
    bool case_sensitivity_for_names;
public:
    configurator& set_case_sensitivity_for_names() {
        case_sensitivity_for_names = true;
        return *this;
    }
public:
    void use_canonical_one_line_comments() {
        remove_comments_from.use_canonical_one_line_comments();
    }
private:
    options registered_options;
    detail::str_set unique_names_of_sections;
public:
    configurator& in_section( const std::string& section_name ) {
        store_unique_section_name( section_name );
        if ( this_is_start_call() ) {
            current_section_path.clear();
        } else {}
        current_section_path += section_name + sections_separator;
        return *this;
    }
private:
    void store_unique_section_name( const std::string& section_name ) {
        std::string name = section_name;
        convert_name_depending_on_case_sensitivity( name );
        unique_names_of_sections.insert( name );
    }
public:
    configurator& in( const std::string& section_name ) {
        return in_section( section_name );
    }

    configurator& from_section( const std::string& section_name ) {
        return in_section( section_name );
    }
    
    configurator& from( const std::string& section_name ) {
        return from_section( section_name );
    }
public:
    option& add_option( const std::string& option_name ) {
        std::string full_name_of_option = option_name;
        convert_name_depending_on_case_sensitivity( full_name_of_option );
        registered_options.push_back( new option( full_name_of_option, sections_separator ) );
        return registered_options.back();
    }
    
    option& add( const std::string& option_name ) {
        return add_option( option_name );
    }

    option& add_option_here( const std::string& option_name ) {
        cut_current_section_path_if_necessary();
        std::string full_name_of_option = current_section_path + option_name;
        convert_name_depending_on_case_sensitivity( full_name_of_option );
        current_section_path += option_name;
        registered_options.push_back( new option( full_name_of_option, sections_separator ) );
        return registered_options.back();
    }

    option& add_here( const std::string& option_name ) {
        return add_option_here( option_name );
    }
private:
    void cut_current_section_path_if_necessary() {
        detail::string_it previous_option_name_begin =
                boost::find_last( current_section_path, sections_separator ).end();
        detail::string_it previous_option_name_end = current_section_path.end();
        current_section_path.erase( previous_option_name_begin
                                    , previous_option_name_end );
    }

    bool this_is_start_call() const {
        return !std::equal( sections_separator.begin()
                            , sections_separator.end()
                            , current_section_path.rbegin() );
    }

    void convert_name_depending_on_case_sensitivity( std::string& full_name_of_option ) const {
        if ( !case_sensitivity_for_names ) {
            boost::to_lower( full_name_of_option );
        } else {}
    }
private:
    std::string                         current_section_path;
    detail::comments_remover            remove_comments_from;
    detail::pure_strings_obtainer       obtain_pure_strings;
    detail::pure_options_obtainer       options_obtainer;
    detail::incorrect_options_checker   check_incorrect_options;
    detail::necessary_options_checker   check_necessary_options;
    detail::semantic_checker            check_all_options_values_semantic;
    detail::options_repetition_handler  handle_options_repetition;
public:
    void parse( const std::string& path_to_configuration_file ) {
        check_registered_options_existence();
        check_configuration_file_existence( path_to_configuration_file );
        detail::str_storage obtained_strings = obtain_pure_strings( path_to_configuration_file );
        check_actual_data_existence( obtained_strings );
        remove_comments_from( obtained_strings );
        pure_options factual_obtained_options = options_obtainer( obtained_strings );
        prepare_registered_options_depending_on_case_sensitivity();
        prepare_pure_options_depending_on_case_sensitivity( factual_obtained_options );
        check_incorrect_options( factual_obtained_options );
        check_necessary_options( factual_obtained_options );
        handle_options_repetition( factual_obtained_options );
        store_obtained_values( factual_obtained_options );
        check_all_options_values_semantic();
        current_section_path.clear();
    }
private:
    bool reparsing;

    struct reparsing_flag_switch {
        explicit reparsing_flag_switch( bool& _reparsing ) :
                reparsing( _reparsing ) {
            reparsing = true;
        }
        ~reparsing_flag_switch() {
            reparsing = false;
        }
    private:
        bool& reparsing;
    };
public:
    void reparse( const std::string& new_path_to_configuration_file ) {
        reparsing_flag_switch s( reparsing );
        parse( new_path_to_configuration_file );
    }

    void reparse() {
        reparsing_flag_switch s( reparsing );
        const std::string previous_path_to_configuration_file = obtain_pure_strings.stored_path();
        parse( previous_path_to_configuration_file );
    }
private:
    void check_registered_options_existence() const {
        if ( registered_options.empty() ) {
            notify( "Cannot parse configuration file, because no one option registered!" );
        } else {}
    }

    void check_configuration_file_existence( const std::string& path_to_configuration_file ) const {
        try {
            detail::pure_check_path_existence( path_to_configuration_file );
        } catch ( const std::exception& exc ) {
            notify( std::string( "Invalid path to configuration file: " ) + exc.what() );
        }
    }
    
    void check_actual_data_existence( detail::str_storage& obtained_strings ) const {
        if ( at_least_one_option_has_default_value() ) {
            return;
        } else {} 
        
        if ( obtained_strings.empty() ) {
            notify( "No actual data in configuration file, is file empty?" );
        } else {} 
    }

    bool at_least_one_option_has_default_value() const {
        option_const_it it = std::find_if( registered_options.begin()
                                           , registered_options.end()
                                           , boost::mem_fn( &option::already_has_default_value ) );
        return registered_options.end() != it;
    }

    void prepare_registered_options_depending_on_case_sensitivity() {
        if ( !case_sensitivity_for_names ) {
            BOOST_FOREACH ( option& option, registered_options ) {
                boost::to_lower( option.name );
            }
        } else {}
    }

    void prepare_pure_options_depending_on_case_sensitivity( pure_options& factual_obtained_options ) {
        if ( !case_sensitivity_for_names ) {
            BOOST_FOREACH ( pure_option& option, factual_obtained_options ) {
                boost::to_lower( option.name );
            }
        } else {}
    }

    void store_obtained_values( const pure_options& factual_obtained_options ) {
        BOOST_FOREACH ( const pure_option& option, factual_obtained_options ) {
            option_it it = std::find( registered_options.begin()
                                      , registered_options.end()
                                      , option.name );
            if ( registered_options.end() != it ) {
                it->value = option.value;
            } else {}
        }

        if ( reparsing ) {
            use_default_value_reserves( factual_obtained_options );
        } else {}
    }
    
    void use_default_value_reserves( const pure_options& factual_obtained_options ) {
        // Not implemented yet.
    }
public:
    std::string get_value( const std::string& name_of_option ) {
        std::string full_name_of_option = name_of_option;
        convert_name_depending_on_case_sensitivity( full_name_of_option );
        option_const_it it = std::find( registered_options.begin()
                                        , registered_options.end()
                                        , full_name_of_option );
        std::string value;
        if ( registered_options.end() != it ) {
            check_factual_obtaining_of( *it, full_name_of_option );
            value = it->value;
        } else {
            notify( "You request a value of option '"
                    + detail::prepare_full_name_for_log( full_name_of_option, sections_separator )
                    + "', but such option not registered!" );
        }
        return value;
    }

    std::string get( const std::string& name_of_option ) {
        return get_value( name_of_option );
    }
private:
    void check_factual_obtaining_of( const option& registered_option
                                     , const std::string& full_name_of_option ) {
        if ( registered_option.value.empty() ) {
            notify( "You request a value of option '"
                    + detail::prepare_full_name_for_log( full_name_of_option, sections_separator )
                    + "' and such option was registered, but it missed in configuration file!" );
        } else {}
    }
public:
    template< typename ValueType >
    ValueType get_value( const std::string& name_of_option ) {
        std::string value_as_string = get_value( name_of_option );
        ValueType value;
        try {
            value = boost::lexical_cast< ValueType >( value_as_string );
        } catch ( const std::exception& /* exc */ ) {
            notify( "Value '" + value_as_string + "' of option '" + name_of_option
                    + "' cannot be cast to <" + get_type_identifier< ValueType >() + ">!" );
        }
        return value;
    }
    
    template< typename ValueType >
    ValueType get( const std::string& name_of_option ) {
        return get_value< ValueType >( name_of_option );
    }

    template< typename ValueType >
    configurator& get_value( const std::string& name_of_option, ValueType& value ) {
        value = get_value< ValueType >( name_of_option );
        return *this;
    }

    template< typename ValueType >
    configurator& get( const std::string& name_of_option, ValueType& value ) {
        return get_value( name_of_option, value );
    }
public:
    std::string get_value_from_here( const std::string& name_of_option ) {
        cut_current_section_path_if_necessary();
        std::string full_name_of_option = current_section_path + name_of_option;
        current_section_path += name_of_option;
        convert_name_depending_on_case_sensitivity( full_name_of_option );
        option_const_it it = std::find( registered_options.begin()
                                        , registered_options.end()
                                        , full_name_of_option );
        std::string value;
        if ( registered_options.end() != it ) {
            check_factual_obtaining_of( *it, full_name_of_option );
            value = it->value;
        } else {
            notify( "You request a value of option '"
                    + detail::prepare_full_name_for_log( full_name_of_option, sections_separator )
                    + "', but such option not registered!" );
        }
        return value;
    }
    
    std::string get_from_here( const std::string& name_of_option ) {
        return get_value_from_here( name_of_option );
    }

    template< typename ValueType >
    ValueType get_value_from_here( const std::string& name_of_option ) {
        std::string value_as_string = get_value_from_here( name_of_option );
        ValueType value;
        try {
            value = boost::lexical_cast< ValueType >( value_as_string );
        } catch ( const std::exception& /* exc */ ) {
            const std::string full_name_of_option = current_section_path;
            notify( "Value '" + value_as_string + "' of option '"
                    + detail::prepare_full_name_for_log( full_name_of_option, sections_separator )
                    + "' cannot be cast to <" + get_type_identifier< ValueType >() + ">!" );
        }
        return value;
    }
    
    template< typename ValueType >
    ValueType get_from_here( const std::string& name_of_option ) {
        return get_value_from_here< ValueType >( name_of_option );
    }

    template< typename ValueType >
    configurator& get_value_from_here( const std::string& name_of_option, ValueType& value ) {
        value = get_value_from_here< ValueType >( name_of_option );
        return *this;
    }

    template< typename ValueType >
    configurator& get_from_here( const std::string& name_of_option, ValueType& value ) {
        return get_value_from_here( name_of_option, value );
    }
private:
    template< typename ArgType >
    std::string get_type_identifier() const {
        std::string identifier;
        
        if      ( typeid( ArgType ) == typeid( bool ) )                { identifier = "bool"; }
        else if ( typeid( ArgType ) == typeid( char ) )                { identifier = "char"; }
        else if ( typeid( ArgType ) == typeid( signed char ) )         { identifier = "signed char"; }
        else if ( typeid( ArgType ) == typeid( unsigned char ) )       { identifier = "unsigned char"; }
        else if ( typeid( ArgType ) == typeid( int ) )                 { identifier = "int"; }
        else if ( typeid( ArgType ) == typeid( signed int ) )          { identifier = "signed int"; }
        else if ( typeid( ArgType ) == typeid( unsigned int ) )        { identifier = "unsigned int"; }
        else if ( typeid( ArgType ) == typeid( short int ) )           { identifier = "short int"; }
        else if ( typeid( ArgType ) == typeid( long int ) )            { identifier = "long int"; }
        else if ( typeid( ArgType ) == typeid( unsigned long int ) )   { identifier = "unsigned long int"; }
        else if ( typeid( ArgType ) == typeid( unsigned short int ) )  { identifier = "unsigned short int"; }
        else if ( typeid( ArgType ) == typeid( signed long int ) )     { identifier = "signed long int"; }
        else if ( typeid( ArgType ) == typeid( signed short int ) )    { identifier = "signed short int"; }
        else if ( typeid( ArgType ) == typeid( float ) )               { identifier = "float"; }
        else if ( typeid( ArgType ) == typeid( double ) )              { identifier = "double"; }
        else if ( typeid( ArgType ) == typeid( long double ) )         { identifier = "long double"; }
        else if ( typeid( ArgType ) == typeid( std::string ) )         { identifier = "std::string"; }
        else                                                           { identifier = "unknown"; }

        return identifier;
    }
};

#ifdef WITH_SINGLETON
/// \class single_configurator
/// \brief
///
///
class single_configurator :
        public configurator
        , public detail::singleton< single_configurator > {
private:
    single_configurator() {}
    single_configurator( const single_configurator& another ) {}
    ~single_configurator() {}
    single_configurator& operator=( const single_configurator& another ) {
        return *this; 
    }
    friend class detail::singleton< single_configurator >;
public:
    void parse( const std::string& path_to_configuration_file ) {
        configurator::parse( path_to_configuration_file );
    }
};
#endif

} // namespace cf

#endif // CF_CONFIGURATOR_HPP
