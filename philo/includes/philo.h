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
    int i;
    int num;
    pthread_t       *tabid;
    pthread_mutex_t mutex;
}
t_data;

long	ft_atoi(const char *nptr);

#endif