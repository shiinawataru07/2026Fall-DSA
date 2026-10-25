class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
inorder = input()
postorder = input()
def buildTree(instart, inend, poststart, postend):
    if instart > inend or poststart > postend:
        return None
    root_val = postorder[postend]
    root = TreeNode(root_val)
    root_index = inorder.index(root_val)
    left_tree_size = root_index - instart
    root.left = buildTree(instart, root_index - 1, poststart, poststart + left_tree_size - 1)
    root.right = buildTree(root_index + 1, inend, poststart + left_tree_size, postend - 1)
    return root
root = buildTree(0, len(inorder) - 1, 0, len(postorder) - 1)
def preorder_traversal(node):
    if node:
        print(node.val, end='')
        preorder_traversal(node.left)
        preorder_traversal(node.right)
preorder_traversal(root)