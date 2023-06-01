package Queue;

abstract class QueueADT<E> {
    public abstract void clear();

    public abstract void enqueue(E item);

    public abstract E dequeue();
    public abstract E leaveQueue();

    public abstract int length();

    public abstract E frontValue();
    public abstract E rearValue();
}
