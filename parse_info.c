#include "includes/cub3D.h"

int static	if_if(char *str)
{
	int	i;

	i = 0;
	return (str[i] == ' ' || str[i] == '\t'
		|| str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r');
}

int	ft_atoi(char *str)
{
	int	sign;
	int	nbr;
	int	num;

	sign = 1;
	nbr = 0;
	num = 19;
	while (if_if(str))
		str++;
	if (*str == '-')
	{
		sign = -sign;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (!num--)
			return ((1 + sign) / (-2));
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	return (nbr * sign);
}

int	static	ft_check1(const char *s, char c)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != 0)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

int static	ft_check_lengh(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != 0 && str[i] != c)
		i++;
	return (i);
}

void static	*ft_free_everything(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

char static	**ft_writestr(char **str, char const *s, int countstr, char c)
{
	int		str_pos;
	int		n;
	int		n_elem;

	n = 0;
	str_pos = 0;
	n_elem = 0;
	while (n < countstr)
	{
		while (s[str_pos] == c)
			str_pos++;
		str[n] = (char *)malloc(ft_check_lengh((char *)s + str_pos, c) + 1);
		if (str == 0)
			ft_free_everything(str);
		while (s[str_pos] != c && s[str_pos] != 0)
			str[n][n_elem++] = s[str_pos++];
		str[n][n_elem] = 0;
		n_elem = 0;
		str_pos++;
		n++;
	}
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		countstr;
	char	**str;

	if (!s)
		return (0);
	countstr = ft_check1((char *)s, c);
	str = (char **)malloc((countstr + 1) * sizeof(char *));
	if (str == 0)
		return (0);
	if (countstr == 0)
	{
		str[0] = (char *)malloc(1);
		if (str == NULL)
			ft_free_everything(str);
		str[0] = 0;
		return (str);
	}
	str = ft_writestr(str, s, countstr, c);
	str[countstr] = 0;
	return (str);
}

char static	ft_check(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s, const char *set)
{
	char	*str;
	size_t	start;
	size_t	end;
	int		i;

	if (!s || !set)
		return (NULL);
	start = 0;
	i = 0;
	end = ft_strlen(s);
	while (s[start] != '\0' && ft_check(s[start], set))
		start++;
	while (end > start && ft_check(s[end - 1], set))
		end--;
	if (start == 0 && end == ft_strlen(s))
		return (ft_strdup(s));
	str = (char *)malloc(sizeof(char) * (end - start + 1));
	if (str == NULL)
		return (NULL);
	while (end > start)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

int	ft_strncmp(const char *str1, const char *str2, size_t num)
{
	unsigned long int	i;

	i = 0;
	while ((i < num) && (str1[i] != '\0' || str2[i] != '\0'))
	{
		if (str1[i] > str2[i] || str1[i] < str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}

// 
// int	make_rgb_colour(int red, int green, int blue)
// {
// 	return (red << 16 | green << 8 | blue);
// }

int	get_colour(char *line)
{
	char **temp;
	int	red;
	int	green;
	int	blue;
	// int	res;

	temp = ft_split(line, ',');
	if (ft_splitlen(temp) > 3)
		return (1); // надо вызывать функцию ошибок
	red = ft_atoi(temp[0]);
	green = ft_atoi(temp[1]);
	blue = ft_atoi(temp[2]);
	free(temp);
	if (red > 255 || red < 0 || green > 255 || green < 0 || blue > 255 || blue < 0)
		return (1); // вызвать функцию ошибок
	// res = make_rgb_colour(red, green, blue);
// то, что ниже, это кодирование отдельных компонентов RGB в целочисленное значение с помощью битового сдвига
	return (red << 16 | green << 8 | blue);
}

void	get_path(char *line, t_paths *path)
{
	if (ft_strncmp("NO ", line, 3) == 0)
		path->north_path = ft_strtrim(line + 3, " ");
	else if (ft_strncmp("SO ", line, 3) == 0)
		path->south_path = ft_strtrim(line + 3, " ");
	else if (ft_strncmp("WE ", line, 3) == 0)
		path->west_path = ft_strtrim(line + 3, " ");
	else if (ft_strncmp("EA ", line, 3) == 0)
		path->east_path = ft_strtrim(line + 3, " ");
	else if (ft_strncmp("F ", line, 2) == 0)
		path->floor_colour = get_colour(line + 2);
	else if (ft_strncmp("C ", line, 2) == 0)
		path->celling_colour = get_colour(line + 2);
}

void	parse_info(t_lst *lst, t_paths *path)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		get_path(lst->str, path);
		lst = lst->next;
		i++;
	}
	printf("%s\n", path->north_path);
	printf("%s\n", path->south_path);
	printf("%s\n", path->west_path);
	printf("%s\n", path->east_path);
	printf("%d\n", path->floor_colour);
	printf("%d\n", path->celling_colour);
}