/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:26:42 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 08:30:42 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../lex.h"

void	destroy_token(
			t_token *token)
{
	if (!token)
		return ;
	if (token->type == TYPE_WORD)
		free(token->content.word);
	free(token);
}
