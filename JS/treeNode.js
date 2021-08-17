import { stdout } from 'process';

class TreeNode {
  constructor(value){
    // Definindo o valor
    this.value = value

    // Definindo os filhos
    this.nodeDir = null
    this.nodeEsq = null
  }

  static addNewNode(root, newNode) {
    if (!root) return newNode
    else if (newNode.value < root.value) {
      root.nodeEsq = this.addNewNode(root.nodeEsq, newNode)
    }
    else {
      root.nodeDir = this.addNewNode(root.nodeDir, newNode)
    }

    return root
  }

  static searchValue(root, value) {
    if (!root) return null
    if (root.value === value) return root

    if (root.value > value)
      return this.searchValue(root.nodeEsq, value)
    return this.searchValue(root.nodeDir, value)
  }

  static countNodes(root) {
    if (!root) return 0
    return this.countNodes(root.nodeEsq) + 1 + this.countNodes(root.nodeDir)
  }

  static deleteData(root, value) {
    if(!root) return null;
    else if (value < root.value) {
      root.nodeEsq = this.deleteData(root.nodeEsq, value)
      return root
    }
    else if (value > root.value) {
      root.nodeDir = this.deleteData(root.nodeDir, value)
      return root
    }
    else {
      // 0 FILHOS
      if (!root.nodeDir && !root.nodeEsq) {
        root = null
        return root
      }

      // 1 FILHO
      if (!root.nodeEsq) {
        root = root.nodeDir;
        return root;
      }
      else if (!root.nodeDir) {
        root = root.nodeEsq;
        return root;
      }

      // 2 FILHOS
      var aux = this.#findMinNode(root.nodeDir)
      root.value = aux.value

      root.nodeDir = this.deleteData(root.nodeDir, aux.value)
      return root
    }
  }

  static printNodes(root) {
    if (root) {
      stdout.write(String(root.value))
      stdout.write('[')
      this.printNodes(root.nodeEsq)
      this.printNodes(root.nodeDir)
      stdout.write(']')
    }
  }

  static #findMinNode = function(root) {
    if (root.nodeEsq === null) return root
    else return (this.#findMinNode(root.nodeEsq))
  }
}

export default TreeNode
