 ;

abstract class StackADT<E> {
    public abstract void clear();

    public abstract void push(E item);
    public abstract E pop();

    public abstract int length();

    public abstract E topValue();

    public abstract void insert(E item,int offset);

    public abstract E remove(int offset);
}
