# 红黑树

### 前置知识

可以学习[2-3树](https://algs4.cs.princeton.edu/33balanced/)的知识作为红黑树的铺垫

2-3树可以使得树形完美平衡，但若是直接定义2节点， 3节点， 4节点。代码会很难实现

### 红黑树

红黑树可以看作2-3树的一种变体

红黑树的链接（可以简单地理解为边）分为红链接和黑链接，与红链接关联的两个节点可以看作一个3节点，如下图， 而黑链接则是一个普通节点

![Encoding a 3-node in a red-black BST](https://algs4.cs.princeton.edu/33balanced/images/redblack-encoding.png)

由于每一个节点最多只有一条边与其关联，可以指向该节点的链接的颜色作为该节点的成员变量， 规定空节点的链接是黑色，即a->color_ == Color::RED;

定义红节点：如果指向该节点的链接是红链接，则该节点是红节点，空节点是黑节点

```c++
		bool isRed(Node* node)
        {
            if (node == nullptr)
                return false;
            return node->col_ == Color::RED;
        }
```

规定：红链接只能是左链接（==这样规定仅仅是为了减少讨论的情况与方便具体实现，在一些其它的实现里，红链接也可以是右链接。 而实际上我们的实现里，在某些时刻下，树中也是存在右红链接的，只是在最终会被调整为右链接==）

### 红黑树的插入

- 新插入的结点是红节点：==想想2-3树的插入？==

- 三种基础操作：右红链接左旋， 左红链接右旋， 颜色反转 （这三个操作都只会改变树的一个局部的形状）

```c++
 		void flipColors(Node* node)
        {
            node->col_ = Color::RED;
            node->left_->col_ = Color::BLACK;
            node->right_->col_ = Color::BLACK;
        }
        //右红链接左旋: 更新链接， 更新颜色， 更新N_
        Node* rotateLeft(Node* node)
        {
            Node* right = node->right_;
            node->right_ = right->left_;
            right->left_ = node;

            right->col_ = node->col_;
            node->col_ = Color::RED;

            right->N_ = node->N_;
            node->N_ = size(node->left_) + size(node->right_) + 1;
            return right;
        }
        //左红链接右旋
        Node* rotateRight(Node* node)
        {
            Node* left = node->left_;
            left->right_ = node;
            node->left_ = left->right_;

            left->col_ = node->col_;
            node->col_ = Color::RED;

            left->N_ = node->N_;
            node->N_ = size(node->left_) + size(node->right_) + 1;
            return left;
        }
```

- 实现思路：找到插入位置后，直接插入节点，再自下向上调整树形

	- 自下向上：后序遍历

	- 调整树形：由上述三种基础操作实现

		- 根节点为黑色

		- 将红链接沿树向上传递， （由<font color=blue>flipColors</font> 实现）

- 不同的插入情形对树形的改变不同：参考《**算法第四版**》==P239==页
	- 插入新键最大 
	- 插入新建最小
	- 插入新建介于3节点之间
- 代码实现：

```c++
Node* update(Node* node, K key, V val)
        {
            if (node == nullptr)
                return new Node(key, val, Color::RED);
            if (key == node->key_)
                node->val_ = val;
            else if (comparef_(key, node->key_))
                node->left_ = update(node->left_, key, val);
            else
                node->right_ = update(node->right_, key, val);
            node->N_ = 1 + size(node->left_) + size(node->right_);
			//调整树形
            //三行代码解决了插入后所有树形的情况
    
    		//插入新键介于3节点之间，左旋后转换为插入新键最小的情形
            if (isRed(node->right_) && !isRed(node->left_)) node = rotateLeft(node);
    		//插入新键最小，右旋后转换为插入新键最大的情形
            if (isRed(node->left_) && isRed(node->left_->left_)) node =  rotateRight(node);
    		//插入新键最大
            if (isRed(node->left_) && isRed(node->right_))   flipColors(node);

            return node;
        }
```

==*编码技巧：使用&&的短路机制避免了对nullptr的解引用==*
