#include <stdlib.h>
#include <unistd.h>

#define SLASH       47
#define BACKSLASH   92
#define VERTICALBAR 124
#define DOLLAR      36
#define STAR        42
#define SPACE       32
        
void ft_putchar(char c)
{
  write(1, &c, 1);
}

void ft_putnchar(char c, int n)
{
  while (n > 0)
  {
    ft_putchar(c);
    n--;
  }
}

int calculate_space(int size)
{
  int base;
  int count;
  int space;

  base = 6;
  count = 1;
  space = 2;
  while (count < size)
  {
    space += base;
    if (count % 2 == 0)
      base += 2;
    else
      base++;
    count++;
  }
  return (space);
}

void  print_door(int *star_count, int size, int height)
{
  int i;
  int vb_count;
  int vb_n;
  
  vb_n = (size % 2 == 1) ? size : size - 1;
  i = 0;
  while (i < *star_count)
  {
    if (i == (*star_count - vb_n) / 2)
    {
      vb_count = 0;
      while (vb_count < vb_n)
      {
        if (vb_n >= 5 && vb_count == vb_n - 2 && height == size / 2 + 2)
          ft_putchar(DOLLAR);
        else
          ft_putchar(VERTICALBAR);
        vb_count++;
        i++;
      }
    }
    else
    {
      ft_putchar(STAR); 
      i++;
    }
  }
  *star_count = i;
}

void  print_floor(int floor, int size, int *star_count, int *space_count)
{
  int height;
  int door_indent;
  
  door_indent = (size % 2 == 1) ? 2 : 3;
  height = 0;
  while (height < floor + 3)
  {
    ft_putnchar(SPACE, *space_count);
    ft_putchar(SLASH);
    if (height < door_indent || floor < size - 1)
      ft_putnchar(STAR, *star_count);
    else
      print_door(star_count, size, height);
    ft_putchar(BACKSLASH);
    ft_putchar('\n');
    *star_count = *star_count + 2;
    *space_count = *space_count - 1;
    height++;
  }
}

void  sastantua(int size)
{
  int floor;
  int floor_space;
  int floor_stars;
  int space_count;
  int star_count;

  if (size <= 0)
    return;
  space_count = calculate_space(size);
  star_count = 1;
  floor_stars = 4;
  floor_space = 2;
  floor = 0;
  while (floor < size)
  {
    print_floor(floor, size, &star_count, &space_count);
    star_count += floor_stars;
    space_count -= floor_space;
    if (floor % 2 == 1 && size != 1)
    {
      floor_stars += 2;
      floor_space++;
    }
    floor++;
  }
}

int main(int argc, char *argv[])
{
  if (argc != 2)
    return (1);

  sastantua(atoi(argv[1]));
}
