/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_with_status_lifecycle.h                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:06:52 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/26 15:15:44 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_WITH_STATUS_LIFECYCLE_H
# define TOKENS_WITH_STATUS_LIFECYCLE_H

# include "../lex.h"

t_tokens_with_status	*create_tokens_with_status(void);
void					destroy_tokens_with_status(
							t_tokens_with_status *tokens_with_status);

#endif
