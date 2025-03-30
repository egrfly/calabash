/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_program_vars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:10:43 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/30 00:37:51 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_list.h"
#include "ft_stdio.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include "../../main.h"
#include "../../execute/var_utils/var_utils.h"
#include "../interface.h"
#include "../list_utils/list_utils.h"
#include "../program_property_utils/program_property_utils.h"
#include "./program_vars_lifecycle.h"

#define SHLVL_MAX 999

static bool	add_new_shlvl(
				t_list *vars)
{
	int		shlvl;
	char	*new_shlvl_str;
	char	*new_shlvl_var;

	if (get_var_value("SHLVL", vars)
		&& ft_strtoi(get_var_value("SHLVL", vars), &shlvl)
		&& shlvl < INT_MAX)
	{
		shlvl = ft_min(ft_max(shlvl + 1, 0), SHLVL_MAX);
		new_shlvl_str = ft_itostr(shlvl);
		if (!new_shlvl_str)
			return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
					get_program_name()), false);
		new_shlvl_var = ft_strjoin("SHLVL=", new_shlvl_str);
		free(new_shlvl_str);
		if (!new_shlvl_var)
			return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
					get_program_name()), false);
		if (!upsert_var(new_shlvl_var, vars, EXPORTED))
			return (free(new_shlvl_var), false);
		free(new_shlvl_var);
	}
	else if (!upsert_var("SHLVL=1", vars, EXPORTED))
		return (false);
	return (true);
}

static bool	add_pwd(
				t_list *vars)
{
	char	*current_dir;
	char	*pwd_var;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
				get_program_name()), false);
	pwd_var = ft_strjoin("PWD=", current_dir);
	free(current_dir);
	if (!pwd_var)
		return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
				get_program_name()), false);
	if (!upsert_var(pwd_var, vars, EXPORTED))
		return (free(pwd_var), false);
	free(pwd_var);
	return (true);
}

bool	init_program_vars(
			t_program_vars *program_vars,
			int argc,
			char **argv,
			char **envp)
{
	program_vars->vars = get_list_from_values(envp);
	if (!program_vars->vars)
		return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
				get_program_name()), false);
	if (!add_new_shlvl(program_vars->vars) || !add_pwd(program_vars->vars))
		return (ft_list_destroy(program_vars->vars, free), false);
	program_vars->argc = argc;
	program_vars->argv = argv;
	program_vars->active_pipelines = ft_list_init();
	program_vars->active_redirections = ft_list_init();
	if (!program_vars->active_pipelines || !program_vars->active_redirections)
		return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
				get_program_name()),
			ft_list_destroy(program_vars->vars, free),
			ft_list_destroy(program_vars->active_pipelines, NULL),
			ft_list_destroy(program_vars->active_redirections, NULL),
			false);
	program_vars->should_exit = false;
	program_vars->last_exit_status = SUCCESS;
	return (true);
}
