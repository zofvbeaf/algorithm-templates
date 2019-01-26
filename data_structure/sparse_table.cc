struct SparseTable {
public:
  SparseTable(int* data, int n) {
    int size_ = n;
    min_ = (int**)malloc(sizeof(int*)*size_);
    max_ = (int**)malloc(sizeof(int*)*size_);
    for(int i = 0; i < size_; ++i) {
      min_[i] = (int*)malloc(sizeof(int)*(int)ceil(log(size_)));
      max_[i] = (int*)malloc(sizeof(int)*(int)ceil(log(size_)));
      min_[i][0] = data[i];
      max_[i][0] = data[i];
    }
    for(int j = 1; (1<<j) <= size_; ++j) 
      for(int i = 0; i + (1<<j) - 1 < size_; ++i) {
        min_[i][j] = std::min(min_[i][j-1], min_[i + (1<<(j-1))][j-1]);
        max_[i][j] = std::max(max_[i][j-1], max_[i + (1<<(j-1))][j-1]);
      }
  }

  ~SparseTable() {  
    for(int i = 0; i < size_; ++i) {
      free(min_[i]);
      free(max_[i]);
    }
    free(min_);
    free(max_);
  }
  
  int Query(int l, int r) {
    int k = 0;
    while((1<<(k+1)) <= r-l+1) ++k;
    //return min(min_[l][k], min_[r-(1<<k)+1][k]);
    return max(max_[l][k], max_[r-(1<<k)+1][k]) - min(min_[l][k], min_[r-(1<<k)+1][k]);
  }

private:
  size_t size_;
  int** min_;
  int** max_;
};
