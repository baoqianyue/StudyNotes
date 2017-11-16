package binarytree;

import java.util.ArrayList;
import java.util.Stack;

public class BinaryTree {
    //根结点
    private TreeNode root = null;

    public BinaryTree() {
        root = new TreeNode(1, "A");
    }

    public class TreeNode {
        private int index;
        private String data;
        private TreeNode leftChild;
        private TreeNode rightChild;
        private TreeNode parent;

        public TreeNode(int index, String data) {
            this.index = index;
            this.data = data;
            this.leftChild = null;
            this.rightChild = null;
            this.parent = null;
        }
    }

    /**
     * 构建一颗二叉树
     * A
     * B      C
     * D     E       F
     */
    public void createBinaryTree() {
        TreeNode nodeB = new TreeNode(2, "B");
        TreeNode nodeC = new TreeNode(3, "C");
        TreeNode nodeD = new TreeNode(4, "D");
        TreeNode nodeE = new TreeNode(5, "E");
        TreeNode nodeF = new TreeNode(6, "F");
        root.leftChild = nodeB;
        root.rightChild = nodeC;
        nodeB.leftChild = nodeD;
        nodeB.rightChild = nodeE;
        nodeC.rightChild = nodeF;
    }


    /**
     * 通过前序遍历序列生成二叉树
     *          A
     *     B          C
     * D      E            F
     * 该序列为：ABD##E##C#F##
     */
    public void createBinaryTreePre(int size, ArrayList<String> data) {
        createBinaryTreeByPre(data.size(), data);
    }

    private TreeNode createBinaryTreeByPre(int size, ArrayList<String> data) {
        //获取集合中第一个结点
        //每次执行函数的时候都会对集合中第一个结点进行操作
        //所以我们要有remove操作
        String d = data.get(0);
        TreeNode node;
        int index = size - data.size();
        if (d.equals("#")) {
            node = null;
            //把#也要去掉
            data.remove(0);
            return node;
        }
        node = new TreeNode(index, d);
        if (index == 0) {
            //创建根结点
            root = node;
        }
        data.remove(0);
        node.leftChild = createBinaryTreeByPre(size, data);
        node.rightChild = createBinaryTreeByPre(size, data);

        return node;
    }


    /**
     * 求二叉树的高度
     */

    public int getHeight() {
        return getHeight(root);
    }

    private int getHeight(TreeNode root) {
        if (root == null) {
            return 0;
        } else {
            //分别递归求左右子树高度
            //返回值较大的一个为高度
            //我们可以这样考虑
            //假如我们现在这棵树只有一个根结点，那么当程序第一次进入到int i这一行的时候，会再一次调用这个函数，并且此时为空，就会返回0
            //所以返回到第一次调用处i = 0，然后开始进入int j这一行，结果是一样的，到最后一行return的时候就会返回0+1 = 1了
            int i = getHeight(root.leftChild);
            int j = getHeight(root.rightChild);
            return (i > j) ? i + 1 : j + 1;
        }
    }

    /**
     * 获取二叉树的结点数
     */
    public int getSize() {
        return getSize(root);
    }

    private int getSize(TreeNode root) {
        if (root == null) {
            return 0;
        } else {
            /**
             * 这个同样是递归函数
             * 假如现在这棵树仅有三个结点，为ABC：
             *     A
             *  B    C
             * 程序会第一次调用getSize()，这时相当于把B传进去了，程序会第二次调用getSize()，但是这时为空，所以返回为1，返回到第一次
             * 调用的地方，同样右边传入右结点C也调用了两次该函数，同样返回1，这样最终返回的时候就是3了。
             */
            return 1 + getSize(root.leftChild) + getSize(root.rightChild);
        }
    }

    /**
     * 前序遍历(递归)
     * 根左右
     */
    public void preOrder(TreeNode root) {
        if (root == null) {
            return;
        } else {
            System.out.println(root.data);
            preOrder(root.leftChild);
            preOrder(root.rightChild);
        }
    }

    /**
     * 中序遍历
     * 左根右
     */
    public void midOrder(TreeNode root) {
        if (root == null) {
            return;
        } else {
            midOrder(root.leftChild);
            System.out.println(root.data);
            midOrder(root.rightChild);
        }
    }

    /**
     * 后序遍历
     * 左右根
     */
    public void postOrder(TreeNode root) {
        if (root == null) {
            return;
        } else {
            postOrder(root.leftChild);
            postOrder(root.rightChild);
            System.out.println(root.data);
        }
    }

    /**
     * 非递归前序遍历
     */
    public void nonrecOrder(TreeNode root) {
        if (root == null) {
            return;
        } else {
            Stack<TreeNode> stack = new Stack<>();
            //我们需要把每个结点都压入栈中，因为每个结点都可以看作是一个子树的根结点
            //首先我们把最上面的根结点压栈
            stack.push(root);
            //当栈不为空的时候，我们进行其他操作
            while (!stack.empty()) {
                /**
                 * 因为是前序遍历，我们将子树的根结点弹出栈后，
                 * 要立马将该结点的左右儿子压入栈中，保证下次循环的条件
                 * 因为要先遍历左结点，所以在栈中，要让右儿子处于左儿子的下方
                 */
                TreeNode node = stack.pop();
                System.out.println(node.data);
                if (node.rightChild != null) {
                    stack.push(node.rightChild);
                }
                if (node.leftChild != null) {
                    stack.push(node.leftChild);
                }

            }
        }
    }


    public static void main(String[] args) {
        BinaryTree binaryTree = new BinaryTree();
//        binaryTree.createBinaryTree();
//        int height = binaryTree.getHeight();
//        System.out.println("the height is:" + height);
//        int size = binaryTree.getSize();
//        System.out.println("the size is:" + size);
//        System.out.println("递归前序遍历：");
//        binaryTree.preOrder(binaryTree.root);
//        System.out.println("非递归前序遍历：");
//        binaryTree.nonrecOrder(binaryTree.root);
        ArrayList<String> data = new ArrayList<>();
        String[] array = new String[]{"A", "B", "D", "#", "#", "E", "#", "#", "C", "#", "F", "#", "#"};
        for (String string : array) {
            data.add(string);
        }
        TreeNode root = binaryTree.createBinaryTreeByPre(data.size(), data);
        binaryTree.preOrder(root);
    }


}
