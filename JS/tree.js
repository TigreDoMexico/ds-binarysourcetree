import TreeNode from './treeNode.js'

class Tree {
  #root

  constructor () {
    this.#root = null
  }

  addValue (value) {
    var newNode = new TreeNode(value)
    this.#root = TreeNode.addNewNode(this.#root, newNode)
  }

  searchValue(value) {
    var result = TreeNode.searchValue(this.#root, value)

    if (result) console.log('VALOR ENCONTRADO:', result.value)
    else console.log('VALOR NÃO ENCONTRADO')
  }

  deleteValue(value) {
    this.#root = TreeNode.deleteData(this.#root, value)
  }

  print() {
    console.log('ÁRVORE')
    TreeNode.print2DTree(this.#root)
    console.log('')
  }

  numberOfNodesInTree() {
    return TreeNode.countNodes(this.#root)
  }
}

export default Tree
