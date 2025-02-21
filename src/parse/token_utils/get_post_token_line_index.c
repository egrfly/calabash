/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_post_token_line_index.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:16:23 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/20 23:17:05 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lex/lex.h"

int	get_post_token_line_index(t_token *token)
{
	return (token->end_line_index + 1);
}
