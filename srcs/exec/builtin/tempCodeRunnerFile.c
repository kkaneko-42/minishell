static char	**get_exec_envp(t_envp *envp)
{
	int		argc;
	char	**exec_envp;
	t_list	*p_args;
	size_t	i;

	
	exec_envp = (char **)ft_xmalloc(sizeof(char *) * (argc + 2));
	exec_envp[0] = (char *)ft_xmalloc(sizeof(char) * (ft_strlen(input->name) + 1));
	ft_memmove(exec_args[0], input->name, ft_strlen(input->name));
	p_args = input->args;
	i = 1;
	while (p_args != NULL)
	{
		exec_args[i] = (char *)ft_xmalloc(sizeof(char) * (ft_strlen(p_args->content) + 1));
		ft_memmove(exec_args[i], p_args->content, ft_strlen(p_args->content));
		exec_args[i][ft_strlen(p_args->content)] = '\0';
		p_args = p_args->next;
		++i;
	}
	exec_args[argc + 1] = NULL;
	return (exec_args);
}