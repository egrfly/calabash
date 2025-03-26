/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:37:05 by aistok            #+#    #+#             */
/*   Updated: 2025/03/26 04:42:18 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include <stdlib.h>
# include "ft_list.h"
# include "../../interface/interface.h"

# define DOLLAR_PREFIX 1
# define EOF_STR 1

typedef struct s_var_and_value
{
	char	*var_name;
	size_t	var_name_len;
	size_t	var_name_start_pos;
	bool	var_name_was_malloced;
	char	*var_value;
	size_t	var_value_len;
	bool	var_value_was_malloced;
}	t_var_and_value;

typedef enum e_string_types
{
	STR,
	NEW_STR,
}	t_string_types;

typedef enum e_quote_types
{
	QUOTE_ANY,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}	t_quote_types;

void	destroy_var_and_value(void *var_and_value);
char	*expand_vars_to_values(
			char *str,
			t_list *vars_and_values);
t_list	*get_all_vars_and_values_outside_quotes(
			char *str,
			t_program_vars *program_vars,
			t_quote_types quote_type);
size_t	get_next_var_name(
			char *str,
			size_t position,
			char **var_name);
bool	insert_next_var_and_value(
			t_list *all_vars_and_values,
			char *str,
			size_t i,
			t_program_vars *program_vars);
bool	is_quote(
			char c,
			t_quote_types quote_type);
char	*remove_quotes(char *str);
char	*ft_strjoin2(
			const char *str1,
			const char *str2,
			const char *separator);

#endif
