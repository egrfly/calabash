/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_token_as_unsupported.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 05:58:52 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/09 19:07:53 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../../lex/lex.h"

void	mark_token_as_unsupported(
			t_token *token)
{
	token->is_supported = false;
}
