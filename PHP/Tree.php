<?php

require "./TreeNode.php";

class Tree
{
  private ?TreeNode $root;

  public function __construct()
  {
    $this->root = null;
  }

  public function addValue(int $value)
  {
    $newNode = new TreeNode($value);
    $this->root = TreeNode::add($this->root, $newNode);
  }

  public function searchValue($value)
  {
    $result = TreeNode::search($this->root, $value);

    if ($result) {
      echo "Valor encontrado: ". $result->value. "\n";
    }
    
    echo "Valor não encontrado\n";
  }

  public function deleteValue($value)
  {
    $this->root = TreeNode::delete($this->root, $value);
  }

  public function print()
  {
    echo "Árvore\n";
    echo TreeNode::print($this->root). "\n";
    echo "\n";
  }

  public function numberOfNodesInTree()
  {
    return TreeNode::count($this->root);
  }
}