/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:53:21 by lcosta-g          #+#    #+#             */
/*   Updated: 2025/05/04 12:46:09 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		export_print(char **env);
static int		export_var(t_hash_table *exported_vars, char **var,
					char *attr_ptr);
static void		handle_empty_value(t_hash_table *exported_vars, char **var,
					char *attr_ptr);
static t_bool	is_key_valid(char *key);
void			sort_env(char **map);
char			**get_key_and_value(char *arg);

int	b_export(char **args)
{
	int					exit_code;
	char				**env;
	static t_hash_table	*exported_vars;

	exit_code = 0;
	if (!exported_vars)
		exported_vars = env_to_map(map_to_env(get_shell()->env));
	env = map_to_env(exported_vars);
	sort_env(env);
	if (!args[1])
		export_print(env);
	else
	{
		while (*(++args))
		{
			exit_code |= export_var(exported_vars, get_key_and_value(*args),
					ft_strchr(*args, '='));
		}
	}
	return (exit_code);
}

static void	export_print(char **env)
{
	char	**var;

	if (env)
	{
		while (*env)
		{
			var = get_key_and_value(*env);
			if (!ft_strcmp(var[0], "_"))
			{
				env++;
				continue ;
			}
			if (!ft_strcmp(var[1], "\x12"))
				ft_printf("declare -x %s\n", var[0]);
			else
				ft_printf("declare -x %s=\"%s\"\n", var[0], var[1]);
			env++;
		}
	}
}

static int	export_var(t_hash_table *exported_vars, char **var, char *attr_ptr)
{
	int	exit_code;

	exit_code = 0;
	if (!is_key_valid(var[0]))
		exit_code = 1;
	else if (ft_map_search(exported_vars, var[0]))
	{
		ft_setenv(var[0], var[1], FALSE);
		ft_map_insert(exported_vars, var[0], var[1]);
	}
	else if (!var[1])
		handle_empty_value(exported_vars, var, attr_ptr);
	else
	{
		ft_setenv(var[0], var[1], FALSE);
		ft_map_insert(exported_vars, var[0], var[1]);
	}
	free(var);
	return (exit_code);
}

static void	handle_empty_value(t_hash_table *exported_vars, char **var,
		char *attr_ptr)
{
	char	*value;

	if (attr_ptr)
	{
		value = ft_strdup("");
		ft_setenv(var[0], value, FALSE);
	}
	else
		value = ft_strdup("\x12");
	ft_map_insert(exported_vars, var[0], value);
	free(value);
}

t_bool	is_key_valid(char *key)
{
	int		i;
	t_bool	is_valid;

	i = 0;
	is_valid = TRUE;
	if (!key || !*key)
		is_valid = FALSE;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		is_valid = FALSE;
	while (key[i] && key[i] != '=')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			is_valid = FALSE;
		i++;
	}
	if (!is_valid)
		ft_printf_fd(2,
			MINISHELL "export: `%s': " C_RED "not a valid identifier\n" C_RST,
			key);
	return (is_valid);
}
