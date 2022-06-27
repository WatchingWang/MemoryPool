//
//  main.cpp
//  MemoryPool
//
//  Created by Watching Wang on 2022/6/27.
//

#include <iostream>
#include "memory_pool.h"

int main(int argc, const char *argv[]) {
  MemoryPool<int> pool(3);
    auto a = pool.GetOne(5);
    auto b = pool.GetOne(6);
    auto c = pool.GetOne(7);

    std::cout<< *a<<std::endl;
    std::cout<< *b<<std::endl;
    std::cout<< *c <<std::endl;
    
    pool.RecycleOne(a);
    a= pool.GetOne(8);
    std::cout<< *a<<std::endl;
  std::cout << "Hello, World!\n";
  return 0;
}
