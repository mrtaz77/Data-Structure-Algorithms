package MyListADT;

public class Node<E> {
    private E element;
    private Node<E> next;

    //freelist support
    private static Node freelist = null;

    //Constructors
    Node(E element, Node<E> nextValue) {
        this.element = element;
        this.next = nextValue;
    }

    public Node(Node<E> nextValue) {
        this.next = nextValue;
    }

    //Getter and Setter
    public E getElement() {
        return element;
    }

    public E setElement(E element) {
        this.element = element;
        return this.element;
    }

    public Node<E> getNext() {
        return next;
    }

    public Node<E> setNext(Node<E> nextValue) {
        this.next = nextValue;
        return this.next;
    }

    @SuppressWarnings("unchecked")
    public static <E> Node<E> get(E item, Node<E> nextValue) {
        if (freelist == null) return new Node<>(item, nextValue);
        Node<E> temp = freelist;
        freelist = freelist.getNext();
        temp.setElement(item);
        temp.setNext(nextValue);
        return temp;
    }

    @SuppressWarnings("unchecked")
    public void release() {
        element = null;
        next = freelist;
        freelist = this;
    }
}
