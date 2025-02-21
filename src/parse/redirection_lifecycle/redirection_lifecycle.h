/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_lifecycle.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:27:54 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/18 18:19:54 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_LIFECYCLE_H
# define REDIRECTION_LIFECYCLE_H

# include "../parse.h"

t_redirection	*create_redirection(void);
void			destroy_redirection(t_redirection *redirection);

#endif
