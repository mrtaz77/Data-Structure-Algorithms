
public class BSTNode<E extends Comparable<? super E>> {
    private E element;
    private BSTNode<E> left;
    private BSTNode<E> right;

    public BSTNode(){
        left = right = null;
    }

    public BSTNode(E element){
        this.element = element;
        left = right = null;
    }

    public E element() {
        return element;
    }

    public BSTNode<E> setElement(E element) {
        this.element = element;
        return this;
    }

    public BSTNode<E> left() {
        return left;
    }

    public BSTNode<E> setLeft(BSTNode<E> left) {
        this.left = left;
        return this;
    }

    public BSTNode<E> right() {
        return right;
    }

    public BSTNode<E> setRight(BSTNode<E> right) {
        this.right = right;
        return this;
    }
}
