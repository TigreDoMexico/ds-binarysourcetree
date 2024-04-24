package tree

type TreeNode struct {
	value int
	dir *TreeNode
	esq *TreeNode
}

func AddNode(root *TreeNode, newNode *TreeNode) *TreeNode {
	if root == nil {
		return newNode
	}

	if newNode.value < root.value {
		root.esq = AddNode(root.esq, newNode)
	}
	else {
		root.dir = AddNode(root.dir, newNode)
	}

	return root
}

func AddNode(root *TreeNode, newNode *TreeNode) *TreeNode {
	if root == nil {
		return newNode
	}

	if newNode.value < root.value {
		root.esq = AddNode(root.esq, newNode)
	}
	else {
		root.dir = AddNode(root.dir, newNode)
	}
	return root
}

func SearchValue(root *TreeNode, value int) *TreeNode {
	switch {
	case root == nil:
		return nil
	case root.value == value:
		return root
	case root.value > value:
		return SearchValue(root.esq, value)
	default:
		return SearchValue(root.dir, value)
	}
}

func CountNodes(root *TreeNode) int {
	if root == nil { return 0 }

	return CountNodes(root.esq) + 1 + CountNodes(root.dir)
}