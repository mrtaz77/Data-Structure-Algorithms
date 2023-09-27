class Node<E> {
    private E element;
    private Node<E> next;

    //freelist support
    private static Node freelist = null;

    //Constructors
    Node(E element, Node<E> nextValue) {
        this.element = element;
        this.next = nextValue;
    }
    Node(Node<E> nextValue) {
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
        if(freelist == null)return new Node<>(item,nextValue);
        Node<E> temp = freelist;
        freelist = freelist.getNext();
        temp.setElement(item);
        temp.setNext(nextValue);
        return temp;
    }

    @SuppressWarnings("unchecked")
    public void release(){
        element = null;
        next = freelist;
        freelist = this;
    }
}


public class LL<E> extends MyList<E>{
    private Node<E> curr;
    private Node<E> head;
    private Node<E> tail;
    private int listSize;

    public LL(){
        curr = head = tail = new Node<>(null);
        listSize = 0;
    }
    public LL(int listSize,int maxSize, E[] items){
        curr = head = tail = new Node<>(null);
        for(int i = 0; i < listSize ; i++)pushBack(items[i]);
    }

    @Override
    public void clear() {
        if(listSize != 0){
            head.getNext().release();
            curr = head = tail = new Node<>(null);
            listSize = 0;
        }
    }//O(1)

    @Override
    public void push(E item)throws IllegalArgumentException{
        if(item == null) throw new IllegalArgumentException();
        else{
            curr.setNext(Node.get(item,curr.getNext()));
            if(tail == curr)tail = curr.getNext();//when list is empty,tail and curr both have the same reference
            listSize++;
        }
    }//O(1)

    @Override
    public E erase()throws NullPointerException{
        if(listSize == 0)throw new NullPointerException();
        E output = curr.getNext().getElement();
        if(tail == curr.getNext())tail = curr;
        Node<E> temp = curr.getNext();
        curr.setNext(curr.getNext().getNext());
        temp.release();
        listSize--;
        if(tail == curr)prev();
        return output;
    }//O(n)

    @Override
    public void pushBack(E item)throws IllegalArgumentException{
        if(item == null)throw new IllegalArgumentException();
        else{
            tail = tail.setNext(Node.get(item,null));
            listSize++;
        }
    }//O(1)

    @Override
    public void setToBegin() {
        curr = head;
    }//O(1)

    @Override
    public void setToEnd() {
        if(curr.getNext() != null)while(curr.getNext() != tail)curr = curr.getNext();
    }//O(n)

    @Override
    public void setToPos(int pos)throws IllegalArgumentException{
        if(pos < 0 || pos>=listSize) throw new IllegalArgumentException();
        curr = head;
        for(int i=0; i<pos; i++)curr = curr.getNext();
    }//O(n)

    @Override
    public void prev() {
        if(curr != head){
            Node<E> temp = head;
            while(temp.getNext() != curr)temp = temp.getNext();
            curr = temp;
        }
    }//O(n)

    @Override
    public void next() {
        if(curr.getNext() != tail && listSize != 0){
            curr = curr.getNext();
        }
    }//O(1)

    @Override
    public int size() {
        return listSize;
    }//O(1)

    @Override
    public int currPos() {
        int currPos = 0;
        Node<E> temp = head;
        while(temp != curr){
            temp = temp .getNext();
            currPos++;
        }
        return currPos;
    }//O(n)

    @Override
    public E getValue()throws NullPointerException{
        if(listSize == 0)throw new NullPointerException();
        return curr.getNext().getElement();
    }//O(1)

    @Override
    public int find(E item)throws IllegalArgumentException{
        if(item == null) throw new IllegalArgumentException();
        else{
            int pos = 0;
            Node<E> temp = head;
            while(pos<listSize){
                if(temp.getNext().getElement() == item)return pos;
                pos++;
                temp = temp.getNext();
            }
        }
        return -1;
    }//O(n)

    @Override
    public String toString(){
        StringBuilder s = new StringBuilder("<");
        if(listSize != 0){
            for(Node<E>itr = head;itr.getNext() != null; itr = itr.getNext()){
                if(itr == curr)s.append("| ");
                if(itr.getNext() != tail)s.append(itr.getNext().getElement()).append(" ");
                else s.append(itr.getNext().getElement());
            }
        }
        s.append(">");
        return String.valueOf(s);
    }//O(n)
}
