package Queue;

import MyListADT.LL;

public class QueueLL<E> extends QueueADT<E> {
    private final LL<E> queue;

    public QueueLL() {
        queue = new LL<>();
    }

    public QueueLL(int listSize,int maxSize,E[] items){
        queue = new LL<>(listSize,maxSize,items);
    }

    @Override
    public void clear() {
        queue.clear();
    }

    @Override
    public void enqueue(E item)throws IllegalArgumentException{
        if(item == null)throw new IllegalArgumentException();
        queue.pushBack(item);
    }//O(1)

    @Override
    public E dequeue()throws NullPointerException{
        if(length() == 0)throw new NullPointerException();
        return queue.erase();
    }//O(1)

    @Override
    public E leaveQueue()throws NullPointerException{
        if(length() == 0)throw new NullPointerException();
        queue.setToEnd();
        E output = queue.erase();
        if(length() > 1)queue.setToBegin();
        return output;
    }//O(n)

    @Override
    public int length() {
        return queue.size();
    }//O(1)

    @Override
    public E frontValue()throws NullPointerException{
        if(length() == 0)throw new NullPointerException();
        return queue.getValue();
    }//O(1)

    @Override
    public E rearValue()throws NullPointerException{
        if(length() == 0)throw new NullPointerException();
        queue.setToEnd();
        E output = queue.getValue();
        if(length() > 1)queue.setToBegin();
        return output;
    }//O(n)

    @Override
    public String toString(){
        return queue.toString();
    }//O(n)
}
