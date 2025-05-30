#include "minishell.h"

void	free_tokens(t_token *head)
{
    t_token	*tmp;

    while (head)
    {
        tmp = head;
        head = head->next;
        if (tmp->value)
            free(tmp->value); // Libérer la chaîne de caractères
        free(tmp); // Libérer le token lui-même
    }
}

void	free_env(t_env *env)
{
    t_env	*tmp;

    while (env)
    {
        tmp = env;
        env = env->next;
        if (tmp->key)
            free(tmp->key); // Libérer la clé
        if (tmp->value)
            free(tmp->value); // Libérer la valeur
        free(tmp); // Libérer le nœud de l'environnement
    }
}
