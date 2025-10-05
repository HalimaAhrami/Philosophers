/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: h-el-ahr <h-el-ahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 04:59:00 by h-el-ahr          #+#    #+#             */
/*   Updated: 2025/08/02 09:53:16 by h-el-ahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_philo
{
	int				id;
	pthread_t		t_id;
	long long		l_m;
	pthread_mutex_t	meal_mutex;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_info	*info;
}	t_philo;

typedef struct s_info
{
	int				n_philo;
	t_philo			*ph;
	int				n_eat;
	pthread_mutex_t	*forks;
	long long		s_t;
	int				dead;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	print;

}	t_info;

int			ft_atoi(char *str);
long long	t_ms(void);
void		ft_destroy(t_info *info);
void		*life(void *arg);
int			monito_died(t_info *info);
void		ft_sleep(long n, t_info *info);
void		ft_print(char *s, t_info *p, int i);
int			ft_check(t_info *info);

#endif
