// Copyright 2022 NNTU-CS
#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include "tree.h"

void printVec(const std::vector<char>& vec) {
  for (char c : vec)
    std::cout << c;
  std::cout << "\n";
}

int main() {
  std::vector<char> in = { '1', '2', '3', '4', '5' };
  PMTree tree(in);

  auto start = std::chrono::high_resolution_clock::now();
  auto all = getAllPerms(tree);
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "getAllPerms: " << all.size() << " perms, time: "
      << std::chrono::duration<double>(end - start).count() << "s\n";

  int n = all.size();
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(1, n);

  int randomIndex = dist(gen);

  start = std::chrono::high_resolution_clock::now();
  auto perm1 = getPerm1(tree, randomIndex);
  end = std::chrono::high_resolution_clock::now();
  std::cout << "getPerm1 #" << randomIndex << ": ";
  printVec(perm1);
  std::cout << "Time: " << std::chrono::duration<double>(end - start).count()
      << "s\n";

  start = std::chrono::high_resolution_clock::now();
  auto perm2 = getPerm2(tree, randomIndex);
  end = std::chrono::high_resolution_clock::now();
  std::cout << "getPerm2 #" << randomIndex << ": ";
  printVec(perm2);
  std::cout << "Time: " << std::chrono::duration<double>(end - start).count()
      << "s\n";

  return 0;
}
