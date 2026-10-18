#include <iostream>
#include <cstddef>

int** alloc(const std::size_t r, const std::size_t c)
{
  if (r == 0 || c == 0)
  {
    return nullptr;
  }
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

int** concat_rows(const int* const* lhs, std::size_t n1, std::size_t m1,
const int* const* rhs, std::size_t n2, std::size_t m2)
{
  std::size_t mr = (n1 > n2) ? n1 : n2;

  std::size_t* sz = new std::size_t[mr];
  for (std::size_t i = 0; i < mr; ++i)
  {
    std::size_t l1 = (i < n1) ? m1 : 0;
    std::size_t l2 = (i < n2) ? m2 : 0;
    sz[i] = l1 + l2;
  }

  int** res = alloc(mr, m1 + m2);
  if (res == nullptr)
  {
    delete[] sz;
    return nullptr;
  }

  for (std::size_t i = 0; i < mr; ++i)
  {
    std::size_t ci = 0;

    if (i < n1)
    {
      for (std::size_t j = 0; j < m1; ++j)
      {
        res[i][ci++] = lhs[i][j];
      }
    }

    if (i < n2)
    {
      for (std::size_t j = 0; j < m2; ++j)
      {
        res[i][ci++] = rhs[i][j];
      }
    }
  }

  delete[] sz;
  return res;
}

int main()
{
  std::size_t n1 = 0, m1 = 0;
  std::size_t n2 = 0, m2 = 0;

  if (!(std::cin >> n1 >> m1))
  {
    return 1;
  }

  int** lhs = alloc(n1, m1);
  if (lhs == nullptr)
  {
    return 2;
  }

  for (std::size_t i = 0; i < n1; ++i)
  {
    for (std::size_t j = 0; j < m1; ++j)
    {
      if (!(std::cin >> lhs[i][j]))
      {
        free_mat(lhs, n1);
	return 1;
      }
    }
  }

  if (!(std::cin >> n2 >> m2))
  {
    free_mat(lhs, n1);
    return 1;
  }

  int** rhs = alloc(n2, m2);
  if (rhs == nullptr)
  {
    free_mat(lhs, n1);
    return 2;
  }

  for (std::size_t i = 0; i < n2; ++i)
  {
    for (std::size_t j = 0; j < m2; ++j)
    {
      if (!(std::cin >> rhs[i][j]))
      {
	free_mat(lhs, n1);
	free_mat(rhs, n2);
	return 1;
      }
    }
  }

  int** res = concat_rows(lhs, n1, m1, rhs, n2, m2);
  if (res == nullptr)
  {
    free_mat(lhs, n1);
    free_mat(rhs, n2);
    return 2;
  }

  std::size_t mr = (n1 > n2) ? n1 : n2;
  for (std::size_t i = 0; i < mr; ++i)
  {
    std::size_t cl = ((i < n1) ? m1 : 0) + ((i < n2) ? m2 : 0);
    for (std::size_t j = 0; j < cl; ++j)
    {
      std::cout << res[i][j] << (j + 1 < cl ? " " : "");
    }
    std::cout << "\n";
  }

  free_mat(lhs, n1);
  free_mat(rhs, n2);
  free_mat(res, mr);

  return 0;
}
