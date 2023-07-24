package Java.AVLTree;

public class AVLNode<E extends Comparable<? super E>> {
    private E element;
    private AVLNode<E> left;
    private AVLNode<E> right;

    public AVLNode(){
        left = right = null;
    }

    public AVLNode(E element){
        this.element = element;
        left = right = null;
    }

    public E element() {
        return element;
    }

    public AVLNode<E> setElement(E element) {
        this.element = element;
        return this;
    }

    public AVLNode<E> left() {
        return left;
    }

    public AVLNode<E> setLeft(AVLNode<E> left) {
        this.left = left;
        return this;
    }

    public AVLNode<E> right() {
        return right;
    }

    public AVLNode<E> setRight(AVLNode<E> right) {
        this.right = right;
        return this;
    }
}
