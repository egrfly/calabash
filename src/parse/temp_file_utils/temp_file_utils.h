/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_file_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:34:42 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 16:26:17 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMP_FILE_UTILS_H
# define TEMP_FILE_UTILS_H

# include "ft_list.h"
# include "../parse.h"

bool	make_temp_file(
			char *temp_file_path,
			t_syntax_tree *syntax_tree,
			t_list *tokens);

#endif
