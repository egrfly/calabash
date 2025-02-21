/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_node_type_from_token.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:41:13 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/20 19:55:27 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "../../lex/lex.h"
#include "../parse.h"

static t_syntax_tree_node_value_type	get_node_type_from_operator_token(
											t_token *token)
{
	if (token->content.operator == OPENING_PARENTHESIS
		|| token->content.operator == CLOSING_PARENTHESIS)
		return (SUBSHELL);
	if (token->content.operator == BAR)
		return (PIPE);
	if (token->content.operator == BAR_AMPERSAND)
		return (PIPE_BOTH);
	if (token->content.operator == BAR_BAR)
		return (OR);
	if (token->content.operator == AMPERSAND_AMPERSAND)
		return (AND);
	if (token->content.operator == AMPERSAND)
		return (BACKGROUND);
	return (0);
}

static t_syntax_tree_node_value_type	get_node_type_from_word_token(
											t_token *token)
{
	if (!ft_strcmp(token->content.word, "!"))
		return (NEGATION);
	if (!ft_strcmp(token->content.word, "time"))
		return (TIME_COMMAND);
	if (!ft_strcmp(token->content.word, "coproc"))
		return (COPROCESS);
	if (!ft_strcmp(token->content.word, "{")
		|| !ft_strcmp(token->content.word, "}")
		|| !ft_strcmp(token->content.word, "do")
		|| !ft_strcmp(token->content.word, "done"))
		return (GROUP);
	if (!ft_strcmp(token->content.word, "while"))
		return (WHILE_COMMAND);
	if (!ft_strcmp(token->content.word, "until"))
		return (UNTIL_COMMAND);
	if (!ft_strcmp(token->content.word, "if"))
		return (IF_COMMAND);
	if (!ft_strcmp(token->content.word, "for"))
		return (FOR_COMMAND);
	if (!ft_strcmp(token->content.word, "select"))
		return (SELECT_COMMAND);
	if (!ft_strcmp(token->content.word, "case"))
		return (CASE_COMMAND);
	return (0);
}

t_syntax_tree_node_value_type	get_node_type_from_token(
									t_token *token)
{
	if (token->type == OPERATOR)
		return (get_node_type_from_operator_token(token));
	if (token->type == WORD)
		return (get_node_type_from_word_token(token));
	return (0);
}
