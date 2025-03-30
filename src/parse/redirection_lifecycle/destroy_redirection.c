/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:27:43 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/30 02:16:47 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../parse.h"

void	destroy_redirection(
			t_redirection *redirection)
{
	if (redirection->left_type == REDIRECTION_LEFT_REDIRECTION_WORD)
		free(redirection->left_content.redirection_word);
	if (redirection->right_type == REDIRECTION_RIGHT_WORD)
		free(redirection->right_content.word);
	free(redirection);
}
