/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:26:16 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/22 15:00:52 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAR_UTILS_H
# define VAR_UTILS_H

# include <stdbool.h>
# include <stdlib.h>
# include "ft_list.h"

# define NOT_EXPORTED_PREFIX "*"

typedef enum e_export_mode
{
	EXPORTED,
	UNCHANGED_OR_EXPORTED,
	UNCHANGED_OR_NOT_EXPORTED,
	NOT_EXPORTED,
}	t_export_mode;

bool	vars_have_same_name(
			char *first_var,
			char *second_var);
bool	vars_have_same_name_n(
			char *first_var,
			size_t n,
			char *second_var);
char	*get_var_value(
			char *var_name,
			t_list *vars);
char	*get_var_value_n(
			char *var_name,
			size_t n,
			t_list *vars);
t_list	*get_exported_vars(
			t_list *vars);
bool	upsert_var(
			char *var,
			t_list *vars,
			t_export_mode mode);
void	remove_var(
			char *var_name,
			t_list *vars);

#endif
