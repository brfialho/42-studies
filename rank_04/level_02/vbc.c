/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 19:07:33 by brfialho          #+#    #+#             */
/*   Updated: 2026/09/03 18:49:50 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node {
    enum {
        ADD,
        MULTI,
        VAL
    }   type;
    int val;
    struct node *l;
    struct node *r;
}   node;

// node *n(**s);

node    *new_node(node n)
{
    node *ret = calloc(1, sizeof(n));
    if (!ret)
        return (NULL);
    *ret = n;
    return (ret);
}

void    destroy_tree(node *n)
{
    if (!n)
        return ;
    if (n->type != VAL)
    {
        destroy_tree(n->l);
        destroy_tree(n->r);
    }
    free(n);
}

void    unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of input\n");
}

int accept(char **s, char c)
{
    if (**s==c)
    {
        (*s)++;
        return (1);
    }
    return (0);
}

int expect(char **s, char c)
{
    if (accept(s, c))
        return (1);
    unexpected(**s);
    return (0);
}

int get_prec(char c, int p_level)
{
    if (isdigit(c))
        return (2 + 3 * p_level);
    if (c == '*')
        return (1 + 3 * p_level);
    if (c == '+')
        return (0 + 3 * p_level);
    return 1000000;
}

int get_lowest_prec(char *s)
{
    int cl_pl = 0;
    int currnt_low = 0;
    int parenthesis_level = 0;

    int i = -1;
    while (s[++i])
    {
        parenthesis_level += (s[i] == '(') + (-1 * (s[i] == ')'));
        if (get_prec(s[i], parenthesis_level) <= get_prec(s[currnt_low], cl_pl))
        {
            cl_pl = parenthesis_level;
            currnt_low = i;
        }
        printf("%s\n c:%c, cl:%d gp:%d pl:%d\n", s, s[i], currnt_low, get_prec(s[i], parenthesis_level), parenthesis_level);
    }
    printf("\n\n");
    if (isdigit(s[currnt_low]))
        return -1;
    return currnt_low;
}

node    *parse_expr(char *s)
{
    node	*ret;

    if (*s) 
    {
        destroy_tree(ret);
        return (NULL);
    }
    return (ret);
}

int eval_tree(node *tree)
{
    switch (tree->type)
    {
        case ADD:
            return (eval_tree(tree->l) + eval_tree(tree->r));
        case MULTI:
            return (eval_tree(tree->l) * eval_tree(tree->r));
        case VAL:
            return (tree->val);
    }
}

int main(int argc, char **argv)
{
    // if (argc != 2)
    //     return (1);
    // node *tree = parse_expr(argv[1]);
    // if (!tree)
    //     return (1);
    // printf("%d\n", eval_tree(tree));
    // destroy_tree(tree);
    // printf("%d:%c %s\n", get_lowest_prec("1+2"), "1+2"[get_lowest_prec("1+2")], "1+2");
    // printf("%d:%c %s\n", get_lowest_prec("1"), "1"[ get_lowest_prec("1")], "1");
    // printf("%d:%c %s\n", get_lowest_prec("1+2*3"), "1+2*3"[ get_lowest_prec("1+2*3")], "1+2*3");
    // printf("%d:%c %s\n", get_lowest_prec("(1+2)*3"), "(1+2)*3"[get_lowest_prec("(1+2)*3")], "(1+2)*3");
    // printf("%d:%c %s\n", get_lowest_prec("1*3"), "1*3"[ get_lowest_prec("1*3")], "1*3");
    // printf("%d:%c %s\n", get_lowest_prec("(1*2)+3"), "(1*2)+3"[get_lowest_prec("(1*2)+3")], "(1*2)+3");
    printf("%d:%c %s\n", get_lowest_prec("((1+2)*3*4+5+(6))"), "((1+2)*3*4+5+(6))"[get_lowest_prec("((1+2)*3*4+5+(6))")], "((1+2)*3*4+5+(6))");
}
