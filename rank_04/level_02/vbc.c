/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 19:07:33 by brfialho          #+#    #+#             */
/*   Updated: 2026/09/04 15:49:07 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <unistd.h>
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
        // printf("%s\n c:%c, cl:%d gp:%d pl:%d\n", s, s[i], currnt_low, get_prec(s[i], parenthesis_level), parenthesis_level);
    }
    // printf("\n\n");
    if (isdigit(s[currnt_low]))
        return -1;
    return currnt_low;
}

int get_value(char *s)
{
    while (*s && (*s == '(' || *s == ')'))
        s++;
    return (*s -'0');
}



int validate_three(node *root)
{
    if (root == NULL)
        return (0);
    if (root->type != VAL && (!root->l || !root->r))
        return (root->type + 3); // since ADD is zero
    return (0);
}

node *build_three(char *s)
{
    int     low_prec;

    // printf("%d:%c %s\n", get_lowest_prec(s), s[get_lowest_prec(s)], s);
    low_prec = get_lowest_prec(s);
    if (low_prec == -1)
        return new_node((node){VAL, get_value(s), NULL, NULL});
    if (s[low_prec] == '+' || s[low_prec] == '*')
    {
        int signal = (s[low_prec] == '*');
        s[low_prec] = 0;
        return new_node((node){signal, 0, build_three(s), build_three(s + low_prec + 1)});
    }
    return NULL;
}

int validate_parenthesis(char *s)
{
    int p_level = 0;
    int i = -1;;
    int last_open = 0;

    while (s[++i])
    {
        if (s[i] == '(')
        {
            last_open = i;
            p_level++;
        }
        if (s[i] == ')')
            p_level--;
        if (p_level < 0)
            return (i);
    }
    if (p_level > 0)
        return (last_open);
    return (0);
}

int validate_chars(char *s)
{
    int i = -1;

    while (s[++i])
        if (!(s[i] == '+'
        || s[i] == '*'
        || s[i] == '('
        || s[i] == ')'
        || isdigit(s[i])))
        return i;
    return 0;
}

void    destroy_bad_three(node *n)
{
    if (!n)
        return ;
    if (n->l)
        destroy_bad_three(n->l);
    if (n->r)
        destroy_bad_three(n->r);
    free(n);
}

node    *parse_expr(char *s)
{
    node    *ret;
    int     err;

    if ((err = validate_parenthesis(s)) || (err = validate_chars(s)))
        return (printf("Unexpected token '%c'\n", s[err]), NULL);

    ret = build_three(s);
    if ((err = validate_three(ret)))
    {
        printf("Unexpected token '%c'\n", (int)(err - 3) ? '*' : '+');
        destroy_bad_three(ret);
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
    if (argc != 2)
        return (1);
    node *tree = parse_expr(argv[1]);
    if (!tree)
        return (1);
    printf("%d\n", eval_tree(tree));
    destroy_tree(tree);
    // char *s = "2*4+9+3+2*1+5+1+6+6*1*1+8*0+0+5+0*4*9*5*8+9*7+5*1+3+1+4*5*7*3+0*3+4*8+8+8+4*0*5*3+5+4+5*7+9+6*6+7+9*2*6*9+2+1*3*7*1*1*5+1+2+7+4+3*4*2+0+4*4*2*2+6+7*5+9+0+8*4+6*7+5+4*4+2+5*5+1+6+3*5*9*9+7*4*3+7+4*9+3+0+1*8+1+2*9*4*5*1+0*1*9+5*3*5+9*6+5*4+5+5*8*6*4*9*2+0+0+1*5*3+6*8*0+0+2*3+7*5*6+8+6*6+9+3+7+0*0+5+2*8+2*7*2+3+9*1*4*8*7*9+2*0+1*6*4*2+8*8*3*1+8+2*4+8*3+8*3+9*5+2*3+9*5*6*4+3*6*6+7+4*8+0+2+9*8*0*6*8*1*2*7+0*5+6*5+0*2+7+2+3+8*7+6+1*3+5+4*5*4*6*1+4*7+9*0+4+9*8+7+5+6+2+6+1+1+1*6*0*9+7+6*2+4*4+1*6*2*9+3+0+0*1*8+4+6*2+6+2*7+7+0*9+6+2*1+6*5*2*3*5*2*6*4+2*9*2*4*5*2*2*3+8+8*3*2*3+0*5+9*6+8+3*1+6*9+8+9*2*0+2";
    // printf("%d:%c %s\n", get_lowest_prec(s), s[get_lowest_prec(s)], s);
    // printf("%d:%c %s\n", get_lowest_prec("1+2"), "1+2"[get_lowest_prec("1+2")], "1+2");
    // printf("%d:%c %s\n", get_lowest_prec("1"), "1"[ get_lowest_prec("1")], "1");
    // printf("%d:%c %s\n", get_lowest_prec("1+2*3"), "1+2*3"[ get_lowest_prec("1+2*3")], "1+2*3");
    // printf("%d:%c %s\n", get_lowest_prec("(1+2)*3"), "(1+2)*3"[get_lowest_prec("(1+2)*3")], "(1+2)*3");
    // printf("%d:%c %s\n", get_lowest_prec("1*3"), "1*3"[ get_lowest_prec("1*3")], "1*3");
    // printf("%d:%c %s\n", get_lowest_prec("(1*2)+3"), "(1*2)+3"[get_lowest_prec("(1*2)+3")], "(1*2)+3");
    // printf("%d:%c %s\n", get_lowest_prec("((1+2)*3*4+5+(6))"), "((1+2)*3*4+5+(6))"[get_lowest_prec("((1+2)*3*4+5+(6))")], "((1+2)*3*4+5+(6))");
}
