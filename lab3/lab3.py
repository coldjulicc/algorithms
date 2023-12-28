class BinNode:
    def __init__(self, data):
        self.data = data
        self.height = 1
        self.left = None
        self.right = None

def insert_node(root, data):
    if root is None:
        return BinNode(data)
    if data < root.data:
        root.left = insert_node(root.left, data)
    else:
        root.right = insert_node(root.right, data)
    return root

def inorder_traversal(node, result):
    if node:
        inorder_traversal(node.left, result)
        result.append(node.data)
        inorder_traversal(node.right, result)

def sorted_nodes(root):
    result = []
    inorder_traversal(root, result)
    return result

def print_inorder(node):
    if node is None:
        return
    print_inorder(node.left)
    print(node.data, end=" ")
    print_inorder(node.right)

def construct_tree(expression):
    stack = []
    root = None
    for c in expression:
        if c == '(':
            new_node = BinNode(None)
            if root is None:
                root = new_node
            else:
                top = stack[-1]
                if top.left is None:
                    top.left = new_node
                else:
                    top.right = new_node
            stack.append(new_node)
        elif c == ')':
            stack.pop()
        else:
            if c.isdigit():
                if stack[-1].data is None:
                    stack[-1].data = int(c)
                else:
                    stack[-1].data = stack[-1].data * 10 + int(c)
    return root

class Node:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None
        self.height = 1

class AVLTree:
    def __init__(self):
        self.root = None

    def BintoAVL(self, arr):
        if len(arr) == 0:
            return None
        mid = len(arr) // 2
        root = Node(arr[mid])
        root.left = self.BintoAVL(arr[:mid])
        root.right = self.BintoAVL(arr[mid+1:])
        root.height = 1 + max(self.height(root.left), self.height(root.right))
        return root

    def search(self, key):
        return self._search(self.root, key)

    def _search(self, node, key):
        if node is None:
            return False
        if key == node.key:
            return True
        elif key < node.key:
            return self._search(node.left, key)
        else:
            return self._search(node.right, key)

    def insert(self, key):
        if self.root is None:
            self.root = Node(key)
        else:
            self._insert(key, self.root)

    def _insert(self, key, node):
        if key < node.key:
            if node.left:
                self._insert(key, node.left)
            else:
                node.left = Node(key)
        else:
            if node.right:
                self._insert(key, node.right)
            else:
                node.right = Node(key)
        node.height = 1 + max(self.height(node.left), self.height(node.right))
        self._balance(node)

    def deleteNode(self, key):
        self.root = self._delete(key, self.root)

    def _delete(self, key, node):
        if node is None:
            return node
        elif key < node.key:
            node.left = self._delete(key, node.left)
        elif key > node.key:
            node.right = self._delete(key, node.right)
        else:
            if node.left is None and node.right is None:
                node = None
            elif node.left is None:
                node = node.right
            elif node.right is None:
                node = node.left
            else:
                min_node = self.find_min(node.right)
                node.key = min_node.key
                node.right = self._delete(min_node.key, node.right)
        if node is None:
            return node
        node.height = 1 + max(self.height(node.left), self.height(node.right))
        self._balance(node)
        return node

    def _balance(self, node):
        balance_factor = self.height(node.left) - self.height(node.right)
        if balance_factor > 1:
            if self.height(node.left.left) >= self.height(node.left.right):
                node = self.rotate_right(node)
            else:
                node.left = self.rotate_left(node.left)
                node = self.rotate_right(node)
        elif balance_factor < -1:
            if self.height(node.right.right) >= self.height(node.right.left):
                node = self.rotate_left(node)
            else:
                node.right = self.rotate_right(node.right)
                node = self.rotate_left(node)

    def rotate_right(self, z):
        y = z.left
        T3 = y.right
        y.right = z
        z.left = T3
        z.height = 1 + max(self.height(z.left), self.height(z.right))
        y.height = 1 + max(self.height(y.left), self.height(y.right))
        return y

    def rotate_left(self, z):
        y = z.right
        T2 = y.left
        y.left = z
        z.right = T2
        z.height = 1 + max(self.height(z.left), self.height(z.right))
        y.height = 1 + max(self.height(y.left), self.height(y.right))
        return y

    def height(self, node):
        if node is None:
            return 0
        return node.height

    def find_min(self, node):
        if node.left:
            return self.find_min(node.left)
        return node

    def width_first_traversal(self):
        if self.root is None:
            return
        queue = []
        queue.append(self.root)
        while queue:
            node = queue.pop(0)
            print(node.key, end=" ")
            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)

    def depth_first_preorder(self):
        stack = []
        stack.append(self.root)
        while stack:
            node = stack.pop()
            print(node.key, end=" ")
            if node.right:
                stack.append(node.right)
            if node.left:
                stack.append(node.left)

    def depth_first_inorder(self, root):
        stack = []
        current = root
        done = False
        while not done:
            if current is not None:
                stack.append(current)
                current = current.left
            else:
                if stack:
                    current = stack.pop()
                    print(current.key, end=" ")
                    current = current.right
                else:
                    done = True

    def depth_first_postorder(self):
        stack1 = []
        stack2 = []
        stack1.append(self.root)
        while stack1:
            node = stack1.pop()
            stack2.append(node)
            if node.left:
                stack1.append(node.left)
            if node.right:
                stack1.append(node.right)
        while stack2:
            node = stack2.pop()
            print(node.key, end=" ")

b_root = BinNode(8)
insert_node(b_root, 1)
insert_node(b_root, 3)
insert_node(b_root, 6)
insert_node(b_root, 2)
print("Binary tree:")
print_inorder(b_root)
print()
expression = "(8 (9 (5)) (1))"
tree = construct_tree(expression)
print("Expression:")
print_inorder(tree)
print()
avl_from_bin = AVLTree()
avl_from_bin.root = avl_from_bin.BintoAVL(sorted_nodes(b_root))
print("AVL from Binary:")
avl_from_bin.depth_first_preorder()
print()
avl_tree = AVLTree()
avl_tree.insert(9)
avl_tree.insert(5)
avl_tree.insert(10)
avl_tree.insert(6)
avl_tree.insert(11)
avl_tree.insert(2)
print("Original AVL Tree:")
avl_tree.depth_first_preorder()
print()
avl_tree.deleteNode(10)
print("AVL Tree after deleting node 10:")
avl_tree.depth_first_preorder()
print()
print("AVL Tree width traversal:")
avl_tree.width_first_traversal()
print()
print("AVL Tree depth preorder traversal:")
avl_tree.depth_first_preorder()
print()
print("AVL Tree depth inorder traversal:")
avl_tree.depth_first_inorder(avl_tree.root)
print()
print("AVL Tree depth postorder traversal:")
avl_tree.depth_first_postorder()
print()


