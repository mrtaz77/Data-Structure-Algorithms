package Stack;

abstract class StackADT<E> {
    public abstract void clear();

    public abstract void push(E item);
    public abstract E pop();

    public abstract int length();

    public abstract E topValue();
}
