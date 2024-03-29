/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:15:57 by aabourri          #+#    #+#             */
/*   Updated: 2023/12/11 15:51:48 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_builtin.h"

t_array	ms_env_dup(char **envp)
{
	size_t	i;
	char	*str;
	t_array	array;

	i = 0;
	array = ms_array_init();
	while (envp[i] != NULL)
	{
		str = ft_strdup(envp[i]);
		if (str)
			ms_array_append(&array, str);
		i += 1;
	}
	return (array);
}

static char	**ms_envdup(char **envp, size_t len)
{
	size_t	i;
	t_array	dup;

	i = 0;
	dup = ms_array_init();
	if (!dup.items)
		return (NULL);
	while (i < len - 1)
	{
		if (envp[i] && envp[i][0])
			ms_array_append(&dup, ft_strdup(envp[i]));
		i += 1;
	}
	ms_array_append(&dup, NULL);
	return (dup.items);
}

void	ms_export_print(t_array env, int *fd)
{
	char	**dup;
	size_t	i;

	i = 0;
	dup = ms_envdup(env.items, env.len);
	if (!dup)
		return ;
	dup = ms_env_sort(dup);
	while (dup && dup[i])
	{
		ft_putendl_fd(dup[i], fd[MS_STDOUT]);
		i += 1;
	}
	ft_free(dup);
}

int	ms_env(t_data *data)
{
	size_t	i;
	t_array	env;

	i = 0;
	env = *data->env;
	while (i < env.len)
	{
		if (env.items[i] && ft_strchr(env.items[i], '='))
			ft_putendl_fd(env.items[i], data->fd[MS_STDOUT]);
		i += 1;
	}
	return (0);
}
