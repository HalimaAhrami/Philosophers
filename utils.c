/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: h-el-ahr <h-el-ahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 04:59:17 by h-el-ahr          #+#    #+#             */
/*   Updated: 2025/08/02 09:46:56 by h-el-ahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int		i;
	long	r;

	i = 0;
	r = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	i = 0;
	while (str[i])
	{
		r = r * 10 + str[i] - 48;
		i++;
		if (r > 2147483647)
			return (-1);
	}
	return (r);
}

long long	t_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

void	ft_destroy(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->n_philo)
	{
		pthread_mutex_destroy(&info->forks[i]);
		pthread_mutex_destroy(&info->ph[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&info->dead_mutex);
	pthread_mutex_destroy(&info->print);
	free(info->forks);
	free(info->ph);
}

int	monito_died(t_info *info)
{
	int			i;
	int			done;

	(1) && (done = 0, i = 0);
	while (i < info->n_philo)
	{
		pthread_mutex_lock(&info->ph[i].meal_mutex);
		if ((t_ms() - info->ph[i].l_m) >= info->ph[i].time_to_die)
			return ((pthread_mutex_unlock(&info->ph[i].meal_mutex),
					pthread_mutex_lock(&info->dead_mutex), info->dead = 1,
					pthread_mutex_unlock(&info->dead_mutex),
					pthread_mutex_lock(&info->print),
					printf("%lld %d died\n", t_ms() - info->s_t, info->ph[i].id),
					pthread_mutex_unlock(&info->print), -1));
		if (info->n_eat != -1 && info->ph[i].meal >= info->n_eat)
			done++;
		pthread_mutex_unlock(&info->ph[i].meal_mutex);
		i++;
	}
	return (done);
}
