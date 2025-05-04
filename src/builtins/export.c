/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:53:21 by lcosta-g          #+#    #+#             */
/*   Updated: 2025/05/04 00:09:37 by lcosta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		sort_env(char **map);
static t_bool	is_key_valid(char *key);
static void		export_print(char **env);
static int		export_var(t_hash_table *exported_vars, char **var,
					char *equal_ptr);
static char		**get_key_and_value(char *arg);

// TODO no env, as variáveis sem valor declaradas com =
// TODO tem que ser exibidas assim: NAME=
int	b_export(char **args)
{
	int					exit_code;
	char				**env;
	static t_hash_table	*exported_vars;

	// * 1. inicializar as variaveis
	exit_code = 0;
	if (!exported_vars)
		exported_vars = init_exported_vars(map_to_env(get_minishell()->env));
	env = map_to_env(exported_vars);
	sort_env(env);
	if (!args[1]) // * 2. export sem parâmetro
		export_print(env);
	else // * 3. export com parâmetro
	{
		while (*(++args))
		{
			export_var(exported_vars, get_key_and_value(*args), ft_strchr(*args,
					'='));
		}
	}
	return (exit_code);
}

static int	export_var(t_hash_table *exported_vars, char **var, char *equal_ptr)
{
	char	*value;
	int		exit_code;

	exit_code = 0;
	if (!is_key_valid(var[0])) // * 4. export com nome inválido
		exit_code = 1;
	else if (ft_get_exported_var(exported_vars, var[0]))
	// *5. export com variável já existente
	{
		ft_setenv(var[0], var[1], FALSE);
		ft_add_exported_var(exported_vars, var[0], var[1], FALSE);
	}
	else if (!var[1]) // * 6. export com variável não existente e sem valor
	{
		// * 7. export sem valor e com =
		if (equal_ptr)
		{
			value = ft_strdup("");
			ft_setenv(var[0], value, FALSE);
			ft_add_exported_var(exported_vars, var[0], value, FALSE);
		}
		else // * 8. export sem valor e sem =
		{
			value = ft_strdup("\x11");
			ft_add_exported_var(exported_vars, var[0], value, FALSE);
		}
		free(value);
	}
	else // * 9. com argumento com valor
	{
		ft_setenv(var[0], var[1], FALSE);
		ft_add_exported_var(exported_vars, var[0], var[1], FALSE);
	}
	free(var);
	return (exit_code);
}

static char	**get_key_and_value(char *arg)
{
	char	*ptr;
	char	**var;

	var = ft_calloc(2, sizeof(char *));
	if (!var)
		return (NULL);
	ptr = ft_strchr(arg, '=');
	if (ptr)
	{
		var[0] = ft_substr(arg, 0, ptr - arg);
		var[1] = ft_strdup(ptr + 1);
	}
	else
	{
		var[0] = ft_strdup(arg);
		var[1] = NULL;
	}
	return (var);
}

static void	export_print(char **env)
{
	char	**var;

	while (*env)
	{
		var = get_key_and_value(*env);
		if (!var || !ft_strcmp(var[0], "_"))
			break ;
		if (!ft_strcmp(var[1], "\x11"))
			ft_printf("declare -x %s\n", var[0]);
		else
			ft_printf("declare -x %s=\"%s\"\n", var[0], var[1]);
		env++;
	}
}

static void	sort_env(char **map)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (map[i])
	{
		j = i + 1;
		while (map[j])
		{
			if (ft_strcmp(map[i], map[j]) > 0)
			{
				temp = map[i];
				map[i] = map[j];
				map[j] = temp;
			}
			j++;
		}
		i++;
	}
}

static t_bool	is_key_valid(char *key)
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
			MINISHELL "export: " C_RED "not a valid identifier\n" C_RST);
	return (is_valid);
}
