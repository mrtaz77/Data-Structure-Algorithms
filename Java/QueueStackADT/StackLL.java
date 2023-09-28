
import MyListADT.LL;

public class StackLL<E> extends StackADT<E>{
    private final LL<E> stack;

    public StackLL(){
        stack = new LL<>();
    }

    public StackLL(int length,int maxSize,E[] items){
        stack = new LL<>();
        for(E item : items)stack.push(item);
    }

    @Override
    public void clear() {
        stack.clear();
    }//O(1)

    @Override
    public void push(E item)throws IllegalArgumentException{
        if(item == null)throw new IllegalArgumentException();
        stack.push(item);
    }//O(1)

    @Override
    public E pop()throws NullPointerException {
        if(length() == 0)throw new NullPointerException();
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
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("<");
        stack.setToEnd();
        for(int i = 0; i<length() ; i++){
            if(i == length()-1){
                sb.append("| ").append(stack.getValue());
            }
            else sb.append(stack.getValue()).append(" ");
            stack.prev();
        }
        sb.append(">");
        return sb.toString();
    }

    @Override
    public void insert(E item, int offset) throws IllegalArgumentException{
        if(offset > length()-1 || offset < 0)throw new IllegalArgumentException();

        StackLL<E> end = new StackLL<>();

        for(int i = 0;i<=offset;i++)end.push(pop());

        push(item);
        while(end.length() != 0)push(end.pop());
    }

    @Override
    public E remove(int offset) throws IllegalArgumentException{
        if(offset > length()-1 || offset < 0)throw new IllegalArgumentException();

        StackLL<E> end = new StackLL<>();

        for(int i = 0;i<offset;i++)end.push(pop());

        E output = pop();
        while(end.length() != 0)push(end.pop());
        return output;
    }
}
