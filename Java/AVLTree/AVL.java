import java.util.LinkedList;
import java.util.Queue;

public class AVL<E extends Comparable<? super E>>{
    private final AVLNode<E> root;

    private AVLNode<E> rightRot(AVLNode<E> root){
        AVLNode<E> prevRoot = root;
        AVLNode<E> newRoot = root.left();
        AVLNode<E> newRootRight = root.left().right();
        prevRoot = prevRoot.setLeft(newRootRight);
        newRoot = newRoot.setRight(prevRoot);
        root = newRoot;
        return root;
    }

    private AVLNode<E> leftRightRot(AVLNode<E> root){
        root = root.setLeft(leftRot(root.left()));
        return rightRot(root);
    }

    private AVLNode<E> leftRot(AVLNode<E> root) {
        AVLNode<E> prevRoot = root;
        AVLNode<E> newRoot = root.right();
        AVLNode<E> newRootLeft = root.right().left();
        
        prevRoot = prevRoot.setRight(newRootLeft);
        newRoot = newRoot.setLeft(prevRoot);
        root = newRoot;
        return root;
    }

    private AVLNode<E> rightLeftRot(AVLNode<E> root) {
        root = root.setRight(rightRot(root.right()));
        return leftRot(root);
    }

    private AVLNode<E> balance(AVLNode<E> root){
        if(root == null)return null;
        int leftH = maxHeight(root.left());
        int rightH = maxHeight(root.right());
        if(Math.abs(leftH - rightH) <= 1)return root;
        else{
            if (leftH > rightH + 1){
                int leftleftH = maxHeight(root.left().left());
                int leftrightH = maxHeight(root.left().right());
                if(leftleftH >= leftrightH)return rightRot(root);
                else return leftRightRot(root);
            }
            else{
                int rightleftH = maxHeight(root.right().left());
                int rightrightH = maxHeight(root.right().right());
                if(rightrightH >= rightleftH)return leftRot(root);
                else return rightLeftRot(root);
            }
        }
    }

    public AVL(){
        root = new AVLNode<>();
    }

    public AVL(E element) {
        root = new AVLNode<>(element);
    }

    public boolean isLeaf(AVLNode<E> root, E element) {
        if(root == null)return false;
        if(element.compareTo(root.element()) == 0)return root.left() == null && root.right() == null;
        else if(element.compareTo(root.element()) < 0)return isLeaf(root.left(), element);
        else return isLeaf(root.right(),element);
    }

    public int maxHeight(AVLNode<E> root){
        if(root == null)return -1;
        else return 1+Math.max(maxHeight(root.left()), maxHeight(root.right()));
    }

    public int height(AVLNode<E> root, E element){
        if(root == null)return -1;
        else if (element.compareTo(root.element()) == 0)return  0;
        else if(element.compareTo(root.element()) < 0)return height(root.left(), element)+1;
        else return height(root.right(),element)+1;
    }

    public String inOrder(AVLNode<E> root){
        if(root == null)return "";
        else {
            String s = root.element().toString()+" ";
            return inOrder(root.left())+s+inOrder(root.right());
        }
    }

    public String preOrder(AVLNode<E> root){
        if(root == null)return "";
        else {
            String s = root.element().toString()+" ";
            return s+preOrder(root.left())+preOrder(root.right());
        }
    }

    public String postOrder(AVLNode<E> root){
        if(root == null)return "";
        else {
            String s = root.element().toString()+" ";
            return postOrder(root.left())+postOrder(root.right())+s;
        }
    }

    public String levelOrder(AVLNode<E> root){
        if(root == null)return "";
        else{
            StringBuilder s = new StringBuilder();
            Queue<AVLNode<E>> queue = new LinkedList<>();
            queue.add(root);
            while(!queue.isEmpty()){
                AVLNode<E> temp = queue.poll();//remove throws exception
                s.append(temp.element()).append(" ");
                if(temp.left() != null) queue.add(temp.left());
                if(temp.right() != null) queue.add(temp.right());
            }
            return s.toString();
        }
    }

    public String show(AVLNode<E> root){
        if(root == null)return "";
        else {
            String s = root.element().toString();
            if(root.left() != null || root.right() != null)return s+"("+show(root.left())+","+show(root.right())+")";
            else return s;
        }
    }

    public AVLNode<E> insert(AVLNode<E> root, E element) {
        if(root == null)return new AVLNode<>(element);
        else if(element.compareTo(root.element()) < 0)root.setLeft(insert(root.left(), element));
        else root.setRight(insert(root.right(),element));
        root = balance(root);
        return root;
    }

    public boolean find(AVLNode<E> root, E element) {
        if(root == null)return false;
        else if(element.compareTo(root.element()) == 0)return true;
        else if(element.compareTo(root.element()) < 0)return find(root.left(), element);
        else return find(root.right(),element);
    }
    
    public AVLNode<E> delete(AVLNode<E> root, E element){
        if(root == null)return null;
        else if(element.compareTo(root.element()) < 0)root.setLeft(delete(root.left(), element));
        else if(element.compareTo(root.element()) > 0)root.setRight(delete(root.right(), element));
        else{
            if(root.left() == null && root.right() == null)root = null;
            //isLeaf() method prevents following operations from ever happening
            else if(root.left() == null)root = root.right();
            else if(root.right() == null)root = root.left();
            else{
                //finding inorder successor
                AVLNode<E> inSuccessor = root.right();
                while(inSuccessor.left() != null)inSuccessor = inSuccessor.left();

                root.setElement(inSuccessor.element());
                root = root.setRight(delete(root.right(),inSuccessor.element()));
            }
        }
        root = balance(root);
        return root;
    }
}
