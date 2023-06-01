package Queue;

import MyListADT.Arr;

public class QueueArr<E> extends QueueADT<E> {
    private final Arr<E> queue;

    public QueueArr() {
        queue = new Arr<>();
    }

    public QueueArr(int length,int maxSize,E[] items){
        queue = new Arr<>(length,maxSize,items);
    }

    @Override
    public void clear() {
        queue.clear();
    }//O(1)

    @Override
    public void enqueue(E item)throws IllegalArgumentException{
        if(item == null)throw new IllegalArgumentException();
        queue.pushBack(item);
    }//O(1)

    @Override
    public E dequeue()throws NullPointerException {
        if(length() == 0)throw new NullPointerException();
        return queue.erase();
    }//O(n)

    @Override
    public E leaveQueue()throws NullPointerException {
        if(length() == 0)throw new NullPointerException();
        queue.setToEnd();
        E output = queue.erase();
        if(queue.size() != 0)queue.setToBegin();
        return output;
    }//O(1)

    @Override
    public int length() {
        return queue.size();
    }//O(1)

    @Override
    public E frontValue()throws NullPointerException {
        if(length() == 0)throw new NullPointerException();
        return queue.getValue();
    }//O(1)

    @Override
    public E rearValue() throws NullPointerException {
        if(length() == 0)throw new NullPointerException();
        queue.setToEnd();
        E output = queue.getValue();
        if(queue.size() != 1)queue.setToBegin();
        return output;
    }//O(1)

    @Override
    public String toString(){
        return queue.toString();
    }//O(n)
}
