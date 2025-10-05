/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: h-el-ahr <h-el-ahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 04:58:45 by h-el-ahr          #+#    #+#             */
/*   Updated: 2025/08/02 10:09:49 by h-el-ahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*monitor(void *arg)
{
	t_info		*info;
	int			done;

	info = (t_info *)arg;
	while (1)
	{
		done = monito_died(info);
		if (done == -1)
			return ((NULL));
		if (info->n_eat != -1 && done >= info->n_philo)
			return ((pthread_mutex_lock(&info->dead_mutex), info->dead = 1,
					pthread_mutex_unlock(&info->dead_mutex), NULL));
		usleep(100);
	}
	return (NULL);
}

static int	ft_manag(t_info *info)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	while (i < info->n_philo)
	{
		if (pthread_create(&info->ph[i].t_id, NULL, life, &info->ph[i]) != 0)
			return ((write(2, "error\n", 6), 1));
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor, info) != 0)
		return ((write(2, "error\n", 6), 1));
	i = 0;
	while (i < info->n_philo)
	{
		if (pthread_join(info->ph[i].t_id, NULL) != 0)
			return ((write(2, "error\n", 6), 1));
		i++;
	}
	if (pthread_join(monitor_thread, NULL))
		return ((write(2, "error\n", 6), 1));
	return (0);
}

static void	ft_init_time_to_think(t_info *info, int i)
{
	if (info->n_philo % 2)
	{
		if (info->ph[0].time_to_eat > info->ph[0].time_to_sleep)
			info->ph[i].time_to_think = info->ph[i].time_to_eat
				+ info->ph[0].time_to_sleep;
		else if (info->ph[0].time_to_eat < info->ph[0].time_to_sleep)
			info->ph[i].time_to_think = 0;
		else
			info->ph[i].time_to_think = info->ph[i].time_to_eat;
	}
	else
		info->ph[i].time_to_think = 0;
}

static int	ft_init(char **av, t_info *info)
{
	int	i;

	info->ph = malloc(sizeof(t_philo) * info->n_philo);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->n_philo);
	if (info->ph == NULL || !info->forks)
		return ((write(2, "error\n", 6), 1));
	if (pthread_mutex_init(&info->dead_mutex, NULL) != 0
		|| pthread_mutex_init(&info->print, NULL) != 0)
		return ((write(2, "error\n", 6), 1));
	(1) && (info->dead = 0, i = 0, info->s_t = t_ms());
	while (i < info->n_philo)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0
			|| pthread_mutex_init(&info->ph[i].meal_mutex, NULL) != 0)
			return ((write(2, "error\n", 6), 1));
		info->ph[i].left_fork = &info->forks[i];
		info->ph[i].right_fork = &info->forks[(i + 1) % info->n_philo];
		(1) && (info->ph[i].id = i + 1, info->ph[i].l_m = info->s_t);
		info->ph[i].time_to_die = ft_atoi(av[2]);
		info->ph[i].time_to_eat = ft_atoi(av[3]);
		info->ph[i].time_to_sleep = ft_atoi(av[4]);
		ft_init_time_to_think(info, i);
		(1) && (info->ph[i].info = info, info->ph[i++].meal = 0);
	}
	return (0);
}

int	main(int ac, char **av)
{
	int		i;
	t_info	info;

	i = 1;
	if ((ac != 5 && ac != 6) || ft_atoi(av[1]) <= 0)
		return (1);
	while (i < ac)
	{
		if (ft_atoi(av[i]) == -1 || !av[i][0])
			return ((write(2, "error\n", 6), 1));
		i++;
	}
	if (ac == 6)
		info.n_eat = ft_atoi(av[5]);
	else
		info.n_eat = -1;
	info.n_philo = ft_atoi(av[1]);
	if (ft_init(av, &info))
		return ((ft_destroy(&info), 1));
	if (ft_manag(&info) == 1)
		return ((ft_destroy(&info), 1));
	ft_destroy(&info);
	return (0);
}
