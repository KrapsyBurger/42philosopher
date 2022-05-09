#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include "ft_printf.h"
#include <pthread.h>

typedef struct  s_data
{
    int timetoeat;
    int timetodie;
    int timetosleep;
    int philonbr;
    int philomusteat;
    pthread_t       *tabid;
    pthread_mutex_t *mutex;
    pthread_t a;
}
t_philoinfo;

typedef struct  s_dataa
{
    int i;
    int b;
    pthread_t id;
    pthread_mutex_t *mutex;
    int nb;
}
t_data;

long	ft_atoi(const char *nptr);

#endif