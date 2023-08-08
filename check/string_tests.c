/*!
 * \file    string_tests.c
 * \brief   String testing functions.
 * \author  Peter Chapin <spicacality@kelseymountain.org>
 */

#include <CUnit/CUnit.h>
#include <string.h>

#include "str.h"
#include "string_tests.h"

void str_construction( void )
{
    string s1;
    int    error_code;

    error_code = string_construct( &s1 );
    CU_ASSERT( error_code == 0 );

    // The tests below need improvement. They should carefully exercise both the cases where a
    // reallocation is done and where it is not done by each of the various copy and append
    // functions. Also testing should verify that no memory leaks occur during these operations
    // (using valgrind?)

    string_copy_char_p( &s1, "Hello" );
    CU_ASSERT( strcmp( string_get_char_p( &s1 ), "Hello" ) == 0 );

    string_append_char_p( &s1, "World" );
    CU_ASSERT( strcmp( string_get_char_p( &s1 ), "HelloWorld" ) == 0 );

    string_append_char( &s1, '!' );
    CU_ASSERT( strcmp( string_get_char_p( &s1 ), "HelloWorld!" ) == 0 );

    string_destroy( &s1 );
}


void str_prepend( void )
{
    string s1;

    string_construct( &s1 );
    string_copy_char_p( &s1, "Hello" );
    string_prepend_char_p( &s1, "World" );
    CU_ASSERT( strcmp( string_get_char_p( &s1 ), "WorldHello" ) == 0 );

    // Similarly to str_construction this test needs to explore a lot more boundary conditions
    // in all the prepending functions.

    string_prepend_char( &s1, '!' );
    CU_ASSERT( strcmp( string_get_char_p( &s1 ), "!WorldHello" ) == 0 );

    string_destroy( &s1 );
}


void str_at( void )
{
    string s1;

    string_construct( &s1 );
    string_copy_char_p( &s1, "Hello" );
    string_put_char_at( &s1, 'x', 0 );
    CU_ASSERT( strcmp( string_get_char_p( &s1 ), "xello" ) == 0 );
    CU_ASSERT( string_get_char_at( &s1, 0 ) == 'x' );

    string_destroy( &s1 );
}
