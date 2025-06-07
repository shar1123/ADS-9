// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <algorithm>
#include <functional>
#include  <vector>
#include  "tree.h"

TreeNode::TreeNode(char val) : value(val) {}

TreeNode::~TreeNode() {
  for (TreeNode* child : children)
    delete child;
  children.clear();
}

PMTree::PMTree(const std::vector<char>& chars) {
  input = chars;
  std::sort(input.begin(), input.end());
  for (size_t i = 0; i < input.size(); ++i) {
    std::vector<char> remaining = input;
    char rootChar = remaining[i];
    remaining.erase(remaining.begin() + i);
    TreeNode* root = new TreeNode(rootChar);
    roots.push_back(root);
    buildTree(root, remaining);
  }
}

PMTree::~PMTree() {
  for (TreeNode* root : roots)
    deleteSubtree(root);
  roots.clear();
}

void PMTree::buildTree(TreeNode* node, std::vector<char> remaining) {
  if (remaining.empty())
    return;
  for (size_t i = 0; i < remaining.size(); ++i) {
    std::vector<char> next = remaining;
    char val = next[i];
    next.erase(next.begin() + i);
    TreeNode* child = new TreeNode(val);
    node->children.push_back(child);
    buildTree(child, next);
  }
}

void PMTree::deleteSubtree(TreeNode* node) {
  if (!node)
    return;
  delete node;
}

void dfs(TreeNode* node, std::vector<char>& path,
        std::vector<std::vector<char>>& result) {
  path.push_back(node->value);
  if (node->children.empty()) {
    result.push_back(path);
  } else {
    for (TreeNode* child : node->children) {
      dfs(child, path, result);
    }
  }
  path.pop_back();
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
  std::vector<std::vector<char>> result;
  std::vector<char> path;
  for (TreeNode* root : tree.roots) {
    dfs(root, path, result);
  }
  return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  auto perms = getAllPerms(tree);
  if (num <= 0 || num > (int)perms.size())
    return {};
  return perms[num - 1];
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  std::vector<char> chars = tree.getInput();
  std::vector<char> output;
  int n = chars.size();
  if (num < 1)
    return {};
  int total = 1;
  for (int i = 2; i <= n; ++i)
    total *= i;
  if (num > total)
    return {};
  int target = num - 1;
  for (int k = n; k > 0; --k) {
    int f = 1;
    for (int j = 2; j < k; ++j)
      f *= j;
    int index = target / f;
    output.push_back(chars[index]);
    chars.erase(chars.begin() + index);
    target = target % f;
  }
  return output;
}
