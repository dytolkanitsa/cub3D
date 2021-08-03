int check_nl_corner(t_lst *lst, t_map map)
{
	int	i;
	int	j;

	i = 0;
	while (map.map[i] != NULL)
	{
		j = 0;
		while (ft_check(map.map[i][j], " 01NSWE"))
			j++;
		j = j - 1;
		printf("%d\n", j);
		while(map.map[i][j])
		{
			printf("%c\n", map.map[i][j]);
			if ((!map.map[i][j + 1] || map.map[i][j + 1] == ' ') && (map.map[i + 1][j] && map.map[i + 1][j] != '1'))
			{
				lst->error = BAD_MAP;
				return (1); // плохо
			}
			else 
				break ;
			j++;
		}
		i++;
	}
	return (0);
}

int	check_nr_corner(t_lst *lst, t_map map)
{
	int	i;
	int	j;

	i = 0;
	while (map.map[i] != NULL)
	{
		j = 0;
		while (map.map[i][j] == ' ')
			j++;
		while(map.map[i][j])
		{
			printf("%c\n", map.map[i][j]);
			if ((!map.map[i][j - 1] || map.map[i][j - 1] == ' ') && map.map[i + 1][j] != '1')
			{
				lst->error = BAD_MAP;
				return (1); // плохо
			}
			else 
				break ;
			j++;
		}
		i++;
	}
	return (0);
}