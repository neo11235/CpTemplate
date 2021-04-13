struct HASH{
  size_t operator()(const int&x)const{
    return hash<long long>()((1ll*x*10001419)%1000004207ll);
  }
};
