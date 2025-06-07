// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>
#include <iostream>

class TreeNode {
 public:
  char value;
  std::vector<TreeNode*> children;
  explicit TreeNode(char val);
  ~TreeNode();
};

class PMTree {
 private:
  std::vector<char> input;

 public:
  std::vector<TreeNode*> roots;
  explicit PMTree(const std::vector<char>& chars);
  ~PMTree();
  void buildTree(TreeNode* node, std::vector<char> remaining);
  void deleteSubtree(TreeNode* node);
  std::vector<char> getInput() const { return input; }
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);
#endif  // INCLUDE_TREE_H_
