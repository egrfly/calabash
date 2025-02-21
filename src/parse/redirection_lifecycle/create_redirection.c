/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:15:43 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/18 18:16:48 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include "../parse.h"

t_redirection	*create_redirection(void)
{
	t_redirection	*redirection;

	redirection = ft_calloc(sizeof(t_redirection), 1);
	return (redirection);
}
