/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: h-el-ahr <h-el-ahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 07:22:46 by h-el-ahr          #+#    #+#             */
/*   Updated: 2025/08/02 09:53:35 by h-el-ahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(char *s, t_info *info, int i)
{
	pthread_mutex_lock(&info->print);
	pthread_mutex_lock(&info->dead_mutex);
	if (info->dead)
	{
		pthread_mutex_unlock(&info->dead_mutex);
		pthread_mutex_unlock(&info->print);
		return ;
	}
	pthread_mutex_unlock(&info->dead_mutex);
	printf("%lld %d %s\n", t_ms() - info->s_t, i, s);
	pthread_mutex_unlock(&info->print);
}

int	ft_check(t_info *info)
{
	pthread_mutex_lock(&info->dead_mutex);
	if (info->dead)
		return ((pthread_mutex_unlock(&info->dead_mutex), 1));
	pthread_mutex_unlock(&info->dead_mutex);
	return (0);
}

void	ft_sleep(long n, t_info *info)
{
	long	start;

	start = t_ms();
	pthread_mutex_lock(&info->dead_mutex);
	while ((t_ms() - start) < n && !info->dead)
	{
		pthread_mutex_unlock(&info->dead_mutex);
		usleep(500);
		pthread_mutex_lock(&info->dead_mutex);
	}
	pthread_mutex_unlock(&info->dead_mutex);
}

static int	ft_life(t_philo *p, pthread_mutex_t *f, pthread_mutex_t *c)
{
	if (ft_check(p->info))
		return ((1));
	pthread_mutex_lock(f);
	if (ft_check(p->info))
		return (pthread_mutex_unlock(f), 1);
	ft_print("has taken a fork", p->info, p->id);
	pthread_mutex_lock(c);
	if (ft_check(p->info))
		return (pthread_mutex_unlock(c), pthread_mutex_unlock(f), 1);
	ft_print("has taken a fork", p->info, p->id);
	pthread_mutex_lock(&p->meal_mutex);
	p->meal++;
	p->l_m = t_ms();
	pthread_mutex_unlock(&p->meal_mutex);
	ft_print("is eating", p->info, p->id);
	ft_sleep(p->time_to_eat, p->info);
	pthread_mutex_unlock(c);
	pthread_mutex_unlock(f);
	ft_print("is sleeping", p->info, p->id);
	ft_sleep(p->time_to_sleep, p->info);
	if (ft_check(p->info))
		return (1);
	ft_print("is thinking", p->info, p->id);
	ft_sleep(p->time_to_think, p->info);
	return (0);
}

void	*life(void *arg)
{
	t_philo			*p;
	pthread_mutex_t	*f;
	pthread_mutex_t	*c;

	p = (t_philo *)arg;
	f = p->left_fork;
	c = p->right_fork;
	if (p->id == p->info->n_philo)
	{
		f = p->right_fork;
		c = p->left_fork;
	}
	if (p->id % 2 == 0)
		usleep(1000);
	if (p->info->n_philo == 1)
		return ((pthread_mutex_lock(f)
				, ft_print("has taken a fork", p->info, p->id),
				pthread_mutex_unlock(f), ft_sleep(p->time_to_die, p->info),
				ft_check(p->info), NULL));
	while (1)
	{
		if (ft_life(p, f, c))
			return (NULL);
	}
	return (NULL);
}
