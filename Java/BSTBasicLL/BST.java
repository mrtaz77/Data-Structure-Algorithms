package BSTBasicLL;

import java.util.LinkedList;
import java.util.Queue;

public class BST<E extends Comparable<? super E>> {
    private final BSTNode<E> root;

    public BST(){
        root = new BSTNode<>();
    }

    public BST(E element) {
        root = new BSTNode<>(element);
    }

    public BSTNode<E> insert(BSTNode<E> root, E element) {
        if(root == null)return new BSTNode<>(element);
        else if(element.compareTo(root.element()) < 0)root.setLeft(insert(root.left(), element));
        else root.setRight(insert(root.right(),element));
        return root;
    }

    public boolean find(BSTNode<E> root, E element) {
        if(root == null)return false;
        else if(element.compareTo(root.element()) == 0)return true;
        else if(element.compareTo(root.element()) < 0)return find(root.left(), element);
        else return find(root.right(),element);
    }


    public boolean isLeaf(BSTNode<E> root, E element) {
        if(root == null)return false;
        if(element.compareTo(root.element()) == 0)return root.left() == null && root.right() == null;
        else if(element.compareTo(root.element()) < 0)return isLeaf(root.left(), element);
        else return isLeaf(root.right(),element);
    }

    public BSTNode<E> delete(BSTNode<E> root, E element){
        if(root == null)return null;
        else if(element.compareTo(root.element()) < 0)root.setLeft(delete(root.left(), element));
        else if(element.compareTo(root.element()) > 0)root.setRight(delete(root.right(), element));
        else{
            if(root.left() == null && root.right() == null)return null;
            //isLeaf() method prevents following operations from ever happening
            else if(root.left() == null)return root.right();
            else if(root.right() == null)return root.left();
            else{
                //finding inorder successor
                BSTNode<E> inSuccessor = root.right();
                while(inSuccessor.left() != null)inSuccessor = inSuccessor.left();

                root.setElement(inSuccessor.element());
                root.setRight(delete(root.right(),inSuccessor.element()));
            }
        }
        return root;
    }

    public int maxHeight(BSTNode<E> root){
        if(root == null)return 0;
        else return 1+Math.max(maxHeight(root.left()), maxHeight(root.right()));
    }

    public int height(BSTNode<E> root, E element){
        if(root == null)return -1;
        else if (element.compareTo(root.element()) == 0)return  0;
        else if(element.compareTo(root.element()) < 0)return height(root.left(), element)+1;
        else return height(root.right(),element)+1;
    }

    public String inOrder(BSTNode<E> root){
        if(root == null)return "";
        else {
            String s = root.element().toString()+" ";
            return inOrder(root.left())+s+inOrder(root.right());
        }
    }

    public String preOrder(BSTNode<E> root){
        if(root == null)return "";
        else {
            String s = root.element().toString()+" ";
            return s+preOrder(root.left())+preOrder(root.right());
        }
    }

    public String postOrder(BSTNode<E> root){
        if(root == null)return "";
        else {
            String s = root.element().toString()+" ";
            return postOrder(root.left())+postOrder(root.right())+s;
        }
    }

    public String levelOrder(BSTNode<E> root){
        if(root == null)return "";
        else{
            StringBuilder s = new StringBuilder();
            Queue<BSTNode<E>> queue = new LinkedList<>();
            queue.add(root);
            while(!queue.isEmpty()){
                BSTNode<E> temp = queue.poll();//remove throws exception
                s.append(temp.element()).append(" ");
                if(temp.left() != null) queue.add(temp.left());
                if(temp.right() != null) queue.add(temp.right());
            }
            return s.toString();
        }
    }

    public String show(BSTNode<E> root){
        if(root == null)return "";
        else {
            String s = root.element().toString();
            if(root.left() != null || root.right() != null)return s+"("+show(root.left())+")("+show(root.right())+")";
            else return s;
        }
    }

    public String print2D(BSTNode<E> root, int space, int SPACE){
        if(root == null)return "";
        else{
            StringBuilder s = new StringBuilder();
            space += SPACE;
            s.append(print2D(root.right(), space, SPACE));
            s.append("-".repeat(Math.max(0, space - SPACE)));
            s.append(root.element()).append("\n\n");
            s.append(print2D(root.left(), space, SPACE));
            return s.toString();
        }
    }

    public boolean isFull(BSTNode<E> root){
        if(root == null)return true;
        else if(root.left() != null && root.right() == null)return false;
        else if(root.left() == null && root.right() != null)return false;
        else return isFull(root.left()) && isFull(root.right());
    }

    public boolean isComplete(BSTNode<E> root){
        if(root != null){
            boolean flag = false;
            Queue<BSTNode<E>> queue = new LinkedList<>();
            queue.add(root);
            while(!queue.isEmpty()){
                BSTNode<E> temp = queue.poll();
                //if a node is null , all nodes must be null after that
                if(temp == null)flag = true;
                else{
                    if(flag)return false;
                    queue.add(temp.left());
                    queue.add(temp.right());
                }
            }
        }
        // If we reach here, then the tree is complete Binary Tree
        return true;
    }

    public E inSuccessor(BSTNode<E> root,E element){
        if(root == null || !find(root,element))return null;
        else{
            BSTNode<E> itr = root;
            while(itr.element().compareTo(element) != 0){
                if(element.compareTo(itr.element()) < 0)itr = itr.left();
                else itr = itr.right();
            }

            if(itr.right() != null){
                BSTNode<E> successor = itr.right();
                while(successor.left() != null) successor = successor.left();
                return successor.element();
            }

            else{
                BSTNode<E> successor = null;
                BSTNode<E> ancestor = root;

                while(ancestor != itr){
                    if(itr.element().compareTo(ancestor.element()) < 0){
                        successor = ancestor;
                        ancestor = ancestor.left();
                    }
                    else ancestor = ancestor.right();
                }
                if(successor == null)return null;
                else return successor.element();
            }
        }
    }

    public E inPredecessor(BSTNode<E> root, E element){
        if(root == null || !find(root,element))return null;
        else{
            BSTNode<E> itr = root;
            while(itr.element().compareTo(element) != 0){
                if(element.compareTo(itr.element()) < 0)itr = itr.left();
                else itr = itr.right();
            }

            if(itr.left() != null){
                BSTNode<E> inSuccessor = itr.left();
                while(inSuccessor.left() != null)inSuccessor = inSuccessor.right();
                return inSuccessor.element();
            }

            else{
                BSTNode<E> predecessor = null;
                BSTNode<E> ancestor = root;

                while(ancestor != itr){
                    if(itr.element().compareTo(ancestor.element()) > 0){
                        predecessor = ancestor;
                        ancestor = ancestor.right();
                    }
                    else ancestor = ancestor.left();
                }
                if(predecessor == null)return null;
                else return predecessor.element();
            }
        }
    }

}
