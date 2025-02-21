/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_has_all_parts_already.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:19:53 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/18 17:20:56 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../parse.h"

bool	redirection_has_all_parts_already(
			t_redirection *redirection)
{
	return (redirection->right_type != NO_REDIRECTION_RIGHT_CONTENT);
}
