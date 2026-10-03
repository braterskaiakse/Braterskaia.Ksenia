#include <iostream>
#include <cstddef>

int** alloc(const std::size_t r, const std::size_t c)
{
  try
  {
    int** m = new int*[r];
    for (std::size_t i = 0; i < r; ++i)
    {
      m[i] = new int[c];
    }
    return m;
  }
  catch (...)
  {
    return nullptr;
  }
}

void free_mat(int** m, const std::size_t r)
{
  if (m == nullptr)
  {
    return;
  }
  for (std::size_t i = 0; i < r; ++i)
  {
    delete[] m[i];
  }
  delete[] m;
}

void input(int** m, const std::size_t r, const std::size_t c)
{
  for (std::size_t i = 0; i < r; ++i)
  {
    for (std::size_t j = 0; j < c; ++j)
    {
      std::cin >> m[i][j];
    }
  }
}

void print(int** m, const std::size_t r, const std::size_t c)
{
  for (std::size_t i = 0; i < r; ++i)
  {
    for (std::size_t j = 0; j < c; ++j)
    {
      std::cout << m[i][j];
      if (j + 1 < c)
      {
        std::cout << ' ';
      }
    }
    std::cout << '\n';
  }
}

int main()
{
  std::size_t r = 0;
  std::size_t c = 0;

  if (!(std::cin >> r >> c))
  {
    return 1;
  }

  int** m = alloc(r, c);
  if (m == nullptr)
  {
    return 2;
  }

  input(m, r, c);

  if (!std::cin)
  {
    free_mat(m, r);
    return 1;
  }

  int** t = alloc(c, r);
  if (t == nullptr)
  {
    free_mat(m, r);
    return 2;
  }

  for (std::size_t i = 0; i < r; ++i)
  {
    for (std::size_t j = 0; j < c; ++j)
    {
      t[j][i] = m[i][j];
    }
  }

  print(t, c, r);

  free_mat(m, r);
  free_mat(t, c);

  return 0;
}
