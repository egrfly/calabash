/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:19:40 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 19:57:27 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_UTILS_H
# define LIST_UTILS_H

# include "ft_list.h"

t_list	*get_list_from_values(
			char **values);
char	**get_values_from_list(
			t_list *list);
char	*get_line_starting_with(
			t_list *list, char *starting_with, char *delim_char);

#endif
