#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex

void print_block (int n, char c) {
  for (int i=0; i<n; ++i) { std::cout << c; }
  std::cout << '\n';
}

int main ()
{
  std::thread th1 (print_block,50,'*');
  std::thread th2 (print_block,50,'$');

  th1.join();
  th2.join();

  return 0;
}
