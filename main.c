#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 4

int	map[SIZE][SIZE];
int	view[SIZE * 4];

int	parse_args(int argc, char **argv)
{
	int		i;
	int		index;
	char	*arg;

	if (argc != 2)
	{
		write(1, "Error: bad argment number...\n", 30);
		return (1);
	}
	arg = argv[1];
	i = 0;
	index = 0;
	while (arg[i])
	{
		if ('1' <= arg[i] && arg[i] <= (SIZE + '0') && ((i < ((SIZE * 4) * 2 - 2) && arg[i + 1] == ' ') 
		|| i == ((SIZE * 4) * 2 - 2)))
			view[index++] = arg[i] - '0';
		i++;
	}
	if (i != ((SIZE * 4) * 2 - 1) || index != (SIZE * 4))
	{
		write(1, "Error: Bad argment...\n", 23);
		return (1);
	}
	return (0);
}

int count_visible_boxes(int *place, int size)
{
    int max_height;
    int count;
    int i;

	max_height = 0;
	count = 0;
    i = 0;
    while (i < size)
    {
        if (place[i] > max_height)
        {
            max_height = place[i];
            count++;
        }
        i++;
    }
    return count;
}

int valid_up(void)
{
    int line[SIZE];
    int i;
    int j;

    i = 0;
    while (i < SIZE)
    {
        j = 0;
        while (j < SIZE)
        {
            line[j] = map[j][i];
            j++;
        }
        if (count_visible_boxes(line, SIZE) != view[i])
            return (0);
        i++;
    }
    return (1);
}

int valid_down(void)
{
    int line[SIZE];
    int i;
    int j;

    i = 0;
    while (i < SIZE)
    {
        j = 0;
        while (j < SIZE)
        {
            line[j] = map[SIZE - 1 - j][i];
            j++;
        }
        if (count_visible_boxes(line, SIZE) != view[SIZE + i])
            return (0);
        i++;
    }
    return (1);
}

int valid_left(void)
{
    int i;

    i = 0;
    while (i < SIZE)
    {
        if (count_visible_boxes(map[i], SIZE) != view[2 * SIZE + i])
            return (0);
        i++;
    }
    return (1);
}

int valid_right(void)
{
    int line[SIZE];
    int i;
    int j;

    i = 0;
    while (i < SIZE)
    {
        j = 0;
        while (j < SIZE)
        {
            line[j] = map[i][SIZE - 1 - j];
            j++;
        }
        if (count_visible_boxes(line, SIZE) != view[3 * SIZE + i])
            return (0);
        i++;
    }
    return (1);
}

int is_valid(void)
{
    return valid_up() && valid_down() && valid_left() && valid_right();
}

int is_valid_in_row(int row, int height)
{
    int i;

    i = 0;
    while (i < SIZE)
    {
        if (map[row][i] == height)
        {
            return (0);
        }
        i++;
    }
    return (1);
}

int is_valid_in_col(int col, int height)
{
    int i;

    i = 0;
    while (i < SIZE)
    {
        if (map[i][col] == height)
        {
            return (0);
        }
        i++;
    }
    return (1);
}

int try_height(int row, int col, int height)
{
    if (is_valid_in_row(row, height) && is_valid_in_col(col, height))
    {
        map[row][col] = height;
        return (1);
    }
    return (0);
}

int solve(int row, int col)
{
    int height;
    
    if (row == SIZE)
        return is_valid();
    if (col == SIZE)
        return solve(row + 1, 0);
    height = 1;
    while (height <= SIZE)
    {
        if (try_height(row, col, height))
        {
            if (solve(row, col + 1))
                return (1);
            map[row][col] = 0;
        }
        height++;
    }
    return (0);
}

void    print_map(void)
{
    int i;
    int j;
    char c;

    i = 0;
    while (i < SIZE)
    {
        j = 0;
        while (j < SIZE)
        {
            c = map[i][j] + '0';
            write(1, &c, 1);
            if (j < SIZE - 1)
            {
                write(1, " ", 1);
            }
            j++;
        }
        write(1, "\n", 1);
        i++;
    }
}

int	main(int argc, char **argv)
{
	int	i;
	int	j;

	if (parse_args(argc, argv))
		return (1);
	i = 0;
	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE)
		{
			map[i][j] = 0;
			j++;
		}
		i++;
	}
	if (solve(0, 0))
		print_map();
	else
		write(1, "Error\n", 7);
	return (0);
}
