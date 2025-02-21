/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:21:25 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/18 18:27:31 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_UTILS_H
# define REDIRECTION_UTILS_H

# include "../parse.h"

t_redirection	*get_or_create_redirection(
					t_syntax_tree *syntax_tree);
bool			redirection_has_all_parts_already(
					t_redirection *redirection);

#endif
