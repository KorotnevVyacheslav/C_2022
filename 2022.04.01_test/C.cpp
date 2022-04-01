
int* compress(int** matrix, int n, int m) {
  int *ans = new int[n*3];
  for (int i = 0; i < n; i++) {
    int c = 0;
    for (int j = 0; j < m; j++) {
      if (matrix[i][j] != 0) {
        ans[i*3+c] = matrix[i][j];
        c++;

      }
    }
    if (c != 3) {
      for (int i = 0; i < n; i++){
        delete[] matrix[i];
      }
      delete[] matrix;
      delete[] ans;
      return nullptr;
    }
  }
  for (int i = 0; i < n; i++){
    delete[] matrix[i];
  }
  delete[] matrix;
  return ans;
}
