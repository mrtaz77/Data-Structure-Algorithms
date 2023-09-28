
import MyListADT.Arr;

public class StackArr<E>  extends StackADT<E>{
    private final Arr<E> stack;

    public StackArr(){
        stack = new Arr<>();
    }

    public StackArr(int length,int maxSize,E [] items){
        stack = new Arr<>(length,maxSize,items);
        if(length != 1)stack.setToEnd();
    }

    @Override
    public void clear() {
        stack.clear();
    }//O(1)

    @Override
    public void push(E item)throws IllegalArgumentException{
        if(item == null)throw new IllegalArgumentException();
        stack.pushBack(item);
        if(length() > 1)stack.setToEnd();
    }//O(1)

    @Override
    public E pop()throws NullPointerException{
        if(length() == 0)throw new IllegalArgumentException();
        return stack.erase();
    }//O(1)

    @Override
    public int length() {
        return stack.size();
    }//O(1)

    @Override
    public E topValue()throws NullPointerException {
        if(length() == 0)throw new NullPointerException();
        return stack.getValue();
    }//O(1)

    @Override
    public void insert(E item, int offset) throws IllegalArgumentException{
        if(offset > length()-1 || offset < 0)throw new IllegalArgumentException();

        StackArr<E> end = new StackArr<>();

        for(int i = 0;i<=offset;i++)end.push(pop());

        push(item);
        while(end.length() != 0)push(end.pop());
    }

    @Override
    public E remove(int offset) throws IllegalArgumentException{
        if(offset > length()-1 || offset < 0)throw new IllegalArgumentException();

        StackArr<E> end = new StackArr<>();

        for(int i = 0;i<offset;i++)end.push(pop());

        E output = pop();
        while(end.length() != 0)push(end.pop());
        return output;
    }

    @Override
    public String toString(){
        return stack.toString();
    }//O(n)
}
