/*!
 * \file    BitFile_tests.c
 * \brief   Test suite for BitFile
 * \author  Peter Chapin <spicacality@kelseymountain.org>
 */

#include "environ.h"
#include <stdio.h>
#include "BitFile.h"

#define CLEAR_SCREEN printf("\033[2J")

#define FALSE 0
#define TRUE  1

void wait( void )
{
    printf( "ENTER to continue..." );
    while ( getchar( ) != '\n' ) /* Null */ ;
    printf( "\n" );
}


void test_open( void )
{
    FILE    *raw;
    BitFile  input;
    BitFile  output;
    int      result;
    int      ch;

    CLEAR_SCREEN;
    printf( "Ready to test open_bit( ) and close_bit( )... "); wait( );

    printf( "Attempting to open a non-existant file for reading: " );
    result = open_bit( &input, "IN.BIT", Bit_In );
    printf( "Returned %d: %s\n", result, (result == FALSE) ? "Ok" : "FAILED" );

    printf( "Attempting to close the above file: " );
    result = close_bit( &input );
    printf( "Returned %d: %s\n", result, (result == FALSE) ? "Ok" : "FAILED" );

    printf( "Attempting to open a non-existant file for writing: " );
    result = open_bit( &output, "OUT.BIT", Bit_Out);
    printf( "Returned %d: %s\n", result, (result == TRUE) ? "Ok" : "FAILED" );

    printf( "Attempting to close the above file: " );
    result = close_bit( &output );
    printf( "Returned %d: %s\n", result, (result == TRUE) ? "Ok" : "FAILED" );

    if( ( raw = fopen( "OUT.BIT", "rb" ) ) == NULL ) {
        printf( "FAILED: The output file does not exist!\n" );
    }
    else {
        printf( "Ok: The output file exists.\n" );
        if( ( ch = getc( raw ) ) != EOF )
            printf( "FAILED: The output file is not empty! It contains: 0x%02X\n", ch );
        else
            printf( "Ok: The output file is empty.\n" );
        fclose( raw );
    }
    
    remove( "OUT.BIT" );    
    wait( );
}


void test_get( void )
{
    FILE    *raw;
    BitFile  data;
    int      a_bit;

    CLEAR_SCREEN;
    printf( "Ready to test get_bit( )... " ); wait( );

    raw = fopen( "IN.BIT", "wb" );
    putc( 0x33, raw ); putc( 0xCC, raw );
    fclose( raw );

    open_bit( &data, "IN.BIT", Bit_In );
    printf( "Reading a file containing one 0x33 byte and one 0xCC byte:\n" );
    while( ( a_bit = get_bit( &data ) ) != EOF ) {
        printf( "%d ", a_bit );
    }
    printf( "EOF\n" );

    printf( "Attempting to read the file again: " );
    a_bit = get_bit( &data );
    printf( "Result %d: %s\n", a_bit, (a_bit == EOF) ? "Ok" : "FAILED" );

    close_bit( &data );
    remove( "IN.BIT" );
    wait( );
}


void Test_Put(void)
{
    FILE      *raw;
    int        ch;
    BitFile    data;
    static int the_bits[] = { 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1 };
           int count;

    CLEAR_SCREEN;
    printf( "Ready to test put_bit( )... " ); wait( );

    open_bit( &data, "OUT.BIT", Bit_Out );
    printf( "Writing the sequence: 1 1 0 0 1 0 1 0, 1 1 1 1\n" );
    for( count = 0; count < 12; count++ ) {
        printf( "%s ", (put_bit( &data, the_bits[count]) == TRUE) ? "Ok" : "FAILED" );
    }
    close_bit( &data );
    printf( "\n" );

    raw = fopen( "OUT.BIT", "rb" );
    printf( "The file contains:\n" );
    while( ( ch = getc( raw ) ) != EOF ) {
        printf( "Wrote: 0x%02X\n", ch );
    }
    
    fclose( raw );
    remove( "OUT.BIT" );
    wait( );
}


void test_read( void )
{
    FILE    *raw;
    int      array[2];
    BitFile  data;
    int      result;

    CLEAR_SCREEN;
    printf( "Ready to test read_bit_header( )... " ); wait( );

    raw = fopen( "IN.BIT", "wb" );
    putc( 0x12, raw ); putc( 0x34, raw ), putc( 0x56, raw ), putc( 0x78, raw ); putc( 0x9A, raw );
    fclose( raw );

    open_bit( &data, "IN.BIT", Bit_In );
    printf( "Reading a file containing 0x3412, 0x7856, and 0x9A\n" );
    result = read_bit_header( &data, array, sizeof(array) );
    printf( "0x%04X, 0x%04X; Result %d: %s\n", array[0], array[1], result, (result == 4) ? "Ok" : "FAILED" );

    printf( "Using get_bit( ) to get the remaining bits\n" );
    while( ( result = get_bit( &data ) ) != EOF ) {
      printf( "%d ", result );
    }
    printf( "\n" );

    printf( "Attempting to read the file again with read_bit_header( ): " );
    result = read_bit_header( &data, array, sizeof(array) );
    printf( "Result %d: %s\n", result, (result == 0) ? "Ok" : "FAILED" );

    printf( "Attempting to read the file again with get_bit( ): " );
    result = get_bit( &data );
    printf( "Result %d: %s\n", result, (result == EOF) ? "Ok" : "FAILED" );

    close_bit( &data );
    remove( "IN.BIT" );
    wait( );
}


void test_write( void )
{
    FILE      *raw;
    int        ch;
    BitFile    data;
    static int array[] = { 0x1234, 0x5678 };
    int        result;

    CLEAR_SCREEN;
    printf( "Ready to test write_bit_header( )... " ); wait( );

    open_bit( &data, "OUT.BIT", Bit_Out );
    printf( "Writing a file containing 0x1234 and 0x5678\n" );
    result = write_bit_header( &data, array, sizeof(array) );
    printf( "Result %d: %s\n", result, (result == 4) ? "Ok" : "FAILED" );
    printf( "Writing 0, 0, 1, 1 into the file with put_bit( ): " );
    if( put_bit( &data, 0 ) == FALSE ||
        put_bit( &data, 0 ) == FALSE ||
        put_bit( &data, 1 ) == FALSE ||
        put_bit( &data, 1 ) == FALSE) { printf( "FAILED\n" ); }
    else { printf( "Ok\n" ); }
    close_bit( &data );

    raw = fopen( "OUT.BIT", "rb" );
    printf( "The file contains:\n" );
    while( ( ch = getc( raw ) ) != EOF ) {
        printf( "0x%02X\n", ch );
    }
    
    fclose( raw );
    remove( "OUT.BIT" );
    wait( );
}


int bitfile_tests( void )
{
    test_open( );
    test_get( );
    test_put( );
    test_read( );
    test_write( );
    return 0;
}
