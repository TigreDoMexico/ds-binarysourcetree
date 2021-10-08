<?php

class TreeNode
{
  public ?int $value;
  public ?TreeNode $nodeDir;
  public ?TreeNode $nodeEsq;

  public function __construct(int $value)
  {
    $this->value = $value;

    $this->nodeDir = null;
    $this->nodeEsq = null;
  }

  public static function add(?TreeNode $root, TreeNode $newNode): TreeNode
  {
    if (is_null($root)) return $newNode;

    $newNode->value < $root->value ?
      $root->nodeEsq = self::add($root->nodeEsq, $newNode) :
      $root->nodeDir = self::add($root->nodeDir, $newNode);

    return $root;
  }

  public static function search(?TreeNode $root, int $value): ?TreeNode
  {
    if (is_null($root) || $root->value == $value) return $root;

    return
      $root->value > $value ?
        self::search($root->nodeEsq, $value) :
        self::search($root->nodeDir, $value);
  }

  public static function count(?TreeNode $root): int
  {
    return 
      is_null($root) ? 0 : 
      self::count($root->nodeEsq) + 1 + self::count($root->nodeDir);
  }

  public static function delete(?TreeNode $root, int $value)
  {
    if (is_null($root)) return $root;

    if ($root->value > $value)
    {
      $root->nodeEsq = self::delete($root->nodeEsq, $value);
      return $root;
    }

    if ($root->value < $value)
    {
      $root->nodeDir = self::delete($root->nodeDir, $value);
      return $root;
    }

    $childsCount = self::countChildsFromNode($root);

    if ($childsCount == 0)
    {
      $root = null;
      return $root;
    }

    if ($childsCount == 1)
    {
      $root = $root->nodeEsq ?? $root->nodeDir;
      return $root;
    }

    $aux = self::findMinRight($root->nodeDir);
    $root->value = $aux->value;

    $root->nodeDir = self::delete($root->nodeDir, $aux->value);

    return $root;
  }

  private static function countChildsFromNode(?TreeNode $node): int
  {
    $count = 0;

    if (!is_null($node->nodeEsq)) $count++;
    if (!is_null($node->nodeDir)) $count++;

    return $count;
  }

  private static function findMinRight(?TreeNode $node): ?TreeNode
  {
    if (is_null($node->nodeEsq)) return $node;

    return self::findMinRight($node->nodeEsq);
  }

  public static function print(?TreeNode $root): string
  {
    if (is_null($root)) return "";

    $treeString = $root->value;
    $treeString .= "[";
    $treeString .= self::print($root->nodeEsq);
    $treeString .= self::print($root->nodeDir);
    $treeString .= "]";
    
    return $treeString;
  }
}