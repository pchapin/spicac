/*! \file    sema.c
 *  \brief   Interface to a semaphore abstract type.
 *  \author  Peter Chapin <spicacality@kelseymountain.org>
 */

#ifndef SEMA_H
#define SEMA_H

#include <pthread.h>

// This is our semaphore type.
typedef struct {
    pthread_mutex_t lock;
    pthread_cond_t  non_zero;
    int             raw_count;
} semaphore_t;

void semaphore_init( semaphore_t *s, int initial_count );
void semaphore_destroy( semaphore_t *s );
void semaphore_up( semaphore_t *s );
void semaphore_down( semaphore_t *s );

#endif
