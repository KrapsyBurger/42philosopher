#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include "ft_printf.h"


typedef struct  s_data
{
    int i;
    int num;
    pthread_mutex_t mutex;
}
t_data;

#endif