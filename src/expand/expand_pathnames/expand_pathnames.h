/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_pathnames.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:14:32 by aistok            #+#    #+#             */
/*   Updated: 2025/03/29 19:40:41 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_PATHNAMES_H
# define EXPAND_PATHNAMES_H

# include "ft_list.h"
# include "../../lex/lex.h"

typedef struct s_match_checkpoint
{
	t_quote_mode	quote_mode_at_latest_star;
	char			*latest_star;
	char			*last_attempted_match_start;
}	t_match_checkpoint;

t_list	*get_expanded_pathnames(
			char *str);

#endif
