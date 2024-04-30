# 二叉树的遍历

## **Profile**

二叉树根据访问左中右节点的不同次序,分别可以为 **前序遍历**（中，左， 右）  **中序遍历**（左，中，右） **后序遍历**（左， 右， 中）三种情况

```C++
//定义节点类
struct Node
    {
        int val_;
        Node* left_;
        Node* right_;

        Node(int val) : val_(val), left_(nullptr), right_(nullptr) {}
        ~Node()
        {
            left_ = nullptr;
            right_ = nullptr;
        }
    };
//访问节点
  void visit(Node *node){
    do_something();
  }
```



可以采用递归的方式进行遍历， 也可以显示地使用栈来进行遍历， 下面是对这两种遍历方式归纳

---

## **使用递归**

**使用递归遍历的时候，此时为图的DFS 的特殊情况， 可参见《算法第四版》中关于图的[Depth-first orders](https://algs4.cs.princeton.edu/42digraph/)的内容。**

- 使用递归的时候系统会帮我们维护一个函数调用栈， 二叉树中的每一个节点会三次位于系统栈的栈顶，第一次位于栈顶的时候是顶点入栈，第二次位于栈顶的时候是从左节点的递归调用返回， 第三次位于栈顶的时候是从栈的右节点返回。

- 当分别在顶点第一次， 第二次， 第三次位于栈顶的时候访问节点时，即为前序遍历， 中序遍历， 后序遍历 

```c++

  void order(Node *node){
      if(node == nullptr)
          return;
      //visit(node);   node第一次位于栈顶，若此时访问node即为前序遍历
      order(node->left);
      //visit(node);   node第二次位于栈顶， 若此时访问node即为中序遍历
      order(node->right);
      //visit(node);   node第三次位于栈顶， 若此时访问node即为后序遍历
  }
```

**可见使用递归的方式遍历写出的代码非常简洁， 并且前中后序遍历的方式非常统一， 仅仅是visit(node) 的位置不同而已**

---

## **显示使用栈**

**使用递归方法进行树的遍历时，每个节点的访问顺序都遵循相同的模式，代码结构会非常统一。而在使用迭代方法时，我们需要显式地管理节点的访问顺序，这将代码会显得更加复杂。而且更难理解。**

### **1. 迭代法前序遍历**：

前序遍历的顺序是先访问根节点，然后递归地访问左子树，最后递归地访问右子树。使用迭代法实现前序遍历的思路是：

- 创建一个栈来存储待访问的节点。
- 将根节点压入栈中。
- 循环执行以下步骤直到栈为空：
  - 弹出栈顶节点，访问它。
  - 如果该节点有右子节点，则将右子节点压入栈中。
  - 如果该节点有左子节点，则将左子节点压入栈中。

```c++
void pre_order(Node* root) 
        {
            if (root == nullptr)  return;
            std::stack<Node*> nodes;
            nodes.push(root);
            while (!nodes.empty()) {
                //前序遍历， 第一次入栈的时候访问；
                Node* current = nodes.top();
                nodes.pop();
                visit(current);
                //先压入右孩子，在压入左孩子
                if (current->right_)  nodes.push(current->right_);
                if (current->left_)     nodes.push(current->left_);
            }
        }
```



### **2. 迭代法中序遍历：**

中序遍历的顺序是先递归地访问左子树，然后访问根节点，最后递归地访问右子树。使用迭代法实现中序遍历的思路是：

- 创建一个栈来存储待访问的节点。
- 从根节点开始，将所有左子节点依次压入栈中，直到最左边的叶子节点。
- 循环执行以下步骤直到栈为空：
  - 弹出栈顶节点，访问它。
  - 如果该节点有右子节点，则将右子节点及其所有左子节点依次压入栈中。

```c++
void in_order(Node* root) 
        {
            if (root == nullptr)  return;
            std::stack<Node*> nodes;
            Node* current = root;
     
            while (current != nullptr || !nodes.empty()) {
                //将左子节点压入栈中
                while (current != nullptr) {
                    nodes.push(current);
                    current = current->left_;
                }
                current = nodes.top();
                nodes.pop();
                visit(current);
                current = current->right_;
            }
        }
```

### **3. 迭代法后序遍历：**

后序遍历的顺序是先递归地访问左子树，然后递归地访问右子树，最后访问根节点。使用迭代法实现后序遍历的思路是：

- 创建一个栈来存储待访问的节点。
- 使用两个指针 `current` 和 `last_visited`，分别表示当前节点和上次访问的节点。
- 从根节点开始，将所有左子节点依次压入栈中，直到最左边的叶子节点。
- 循环执行以下步骤直到栈为空：
  - 弹出栈顶节点，如果该节点的右子节点为空或者已经访问过，则访问该节点，否则将右子节点压入栈中。
  - 如果当前节点的右子节点为空或者已经访问过，说明可以访问当前节点了，否则将当前节点重新压入栈中，并将当前节点移动到其右子节点。

```c++
 void aft_order(Node* root) override
        {
            if (root == nullptr) return;
            std::stack <Node*> nodes;
            Node* last_visited = nullptr,   * current = root;

            while (current != nullptr || !nodes.empty()) {
                ////将左子节点压入栈中
                while (current != nullptr) {
                    nodes.push(current);
                    current = current->left_;
                }

                current = nodes.top();
                //如果栈顶节点没有右子节点或者右子节点被访问过
                if (current->right_ == nullptr ||  last_visited == current->right_ ) {
                    visit(current);
                    nodes.pop();
                    last_visited = current;
                    current = nullptr;
                }
                else   current = current->right_;
            }
        }
```

### **思考**

- 中序遍历以及后序遍历都没有 *nodes.push(cur->right_)* 操作， 为什么？



## 总结

- 迭代遍历二叉树的思想与代码都较为复杂， 但是对于理解前中后序遍历二叉树的过程有重要意义。
- 而递归遍历可以真正地解决实际问题
- 一些经典算法的思想与二叉树的递归遍历有着异曲同工之处：如
  	- 前序遍历 和 快速排序
  	- 后续遍历 和 归并排序，（同时后序遍历也是一种回溯算法， 可以做到从叶节点一直向上访问到根节点）

**综上所述：递归方法利用了函数调用栈来存储遍历过程中的状态信息，因此代码结构相对简单。而迭代法则需要显式地使用数据结构（如栈）来存储状态信息，这使得代码结构相对复杂。此外，迭代法还需要考虑节点的访问顺序和状态的管理，因此实现起来会更加繁琐。**

