#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct  s_data
{
    int timetoeat;
    int timetodie;
    int timetosleep;
    int philonbr;
    int philomusteat;
    long long   start_time;
}
t_philo;

typedef struct  s_dataa
{
    int i;
    int mutex_idx;
    int thread_idx;
    long long last_meal;
    pthread_t id;
    pthread_mutex_t *mutex;
    pthread_mutex_t *mutex_print;
    t_philo *philo;
}
t_thread;

// utils
long        ft_atoi(const char *nptr);
long long	current_time(void);

// init and destroy
int     init_struct(t_philo **philo, t_thread **thread, int argc, char **argv);
int     init_mutex(t_thread **thread, t_philo **philo);
int     destroy_mutex(t_thread **thread, t_philo **philo);
int     ft_thread_create(t_thread **thread, t_philo **philo);

// routine and action
void    *routine(void *s);
char	*ft_action(int action);
int     philo_print(t_thread **thread, t_philo **philo, int i, int action);

#endif