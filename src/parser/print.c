#include "minishell.h"
#include "parser.h"
#include "exec.h"


void	print_indent(int level)
{
	for (int i = 0; i < level; i++)
		printf("  ");
}

const char *tree_type_str(t_tree_type type)
{
	switch (type)
	{
		case TREE_CMD: return "COMMAND";
		case TREE_PIPE: return "PIPE";
		case TREE_AND: return "AND";
		case TREE_OR: return "OR";
		case TREE_SUBSHELL: return "SUBSHELL";
		case TREE_REDIR_IN: return "REDIR_IN";
		case TREE_REDIR_OUT: return "REDIR_OUT";
		case TREE_REDIR_OUT_APP: return "REDIR_APPEND";
		case TREE_REDIR_HDOC: return "HEREDOC";
		default: return "UNKNOWN";
	}
}

void	print_tokens(t_token_list *tokens)
{
	while (tokens)
	{
		printf("'%s' ", tokens->token.full_content);
		tokens = tokens->next;
	}
}

void	print_token_list(t_token_list *list)
{
	while (list)
	{
		ft_printf("[%i, '%s']", list->token.type, list->token.full_content);
		if (list->next)
			ft_printf(" -> ");
		list = list->next;
	}
	ft_printf("\n");
}

void	print_tree(t_exec_tree *tree, int level)
{
	if (!tree)
		return;

	// Primeiro printa a direita (que aparece em cima no terminal)
	print_tree(tree->right, level + 1);

	// Indentação proporcional ao nível
	for (int i = 0; i < level; i++)
		printf("        ");

	// Print do nó atual
	printf("[%s]", tree_type_str(tree->type));

	if (tree->type == TREE_CMD && tree->command)
	{
		printf(" - ");
		print_tokens(tree->command);
	}
	else if ((tree->type >= TREE_REDIR_IN && tree->type <= TREE_REDIR_HDOC) && tree->file)
	{
		printf(" - redirect: ");
		print_tokens(tree->file);
	}

	printf("\n");

	// Depois printa a esquerda (que aparece embaixo no terminal)
	if (tree->type == TREE_SUBSHELL)
		print_tree(tree->subshell, level + 1);
	else
		print_tree(tree->left, level + 1);
}
