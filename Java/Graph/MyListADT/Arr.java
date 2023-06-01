package MyListADT;

public class Arr <E>extends MyList<E>{
    //size Constant
    private static final int DEFAULT_SIZE = 10;

    //members
    private E [] elements;
    private int listSize;
    private int maxSize;
    private int curr;

    @SuppressWarnings("unchecked")
    //grow methods
    private void grow(){
        E[] temp = elements;
        elements = (E[]) new Object[maxSize*2];
        maxSize *= 2;
        if (listSize >= 0) System.arraycopy(temp, 0, elements, 0, listSize);
    }//O(n)
    private boolean needToGrow(){
        return   listSize == maxSize;
    }//O(1)

    @SuppressWarnings("unchecked")
    private void shrink(){
        E[] temp = elements;
        maxSize /= 2;
        if(maxSize == 0)maxSize = DEFAULT_SIZE;
        elements = (E[]) new Object[maxSize];
        if (listSize >= 0) System.arraycopy(temp, 0, elements, 0, listSize);
    }//O(n)

    private boolean needToShrink(){
        return listSize <= maxSize/2;
    }//O(1)


    @SuppressWarnings("unchecked")
    public Arr(){
        listSize = 0;
        maxSize = DEFAULT_SIZE;
        curr = 0;
        elements = (E[])new Object[maxSize];
    }

    @SuppressWarnings("unchecked")
    public Arr(int listSize, int maxSize, E[] items){
        this.listSize = listSize;
        this.maxSize = (maxSize == 0)?DEFAULT_SIZE:maxSize;
        curr = 0;
        elements = (E[])new Object[maxSize];
        if (listSize >= 0) System.arraycopy(items, 0, elements, 0, listSize);
    }



    @SuppressWarnings("unchecked")
    @Override
    public void clear() {
        maxSize = DEFAULT_SIZE;
        listSize = curr = 0;
        elements = (E[])new Object[DEFAULT_SIZE];
    }//O(1)

    @Override
    public void push(E item)throws IllegalArgumentException{
        if(item == null) throw new IllegalArgumentException();
        if(find(item) == -1){
            if(needToGrow())grow();
            for(int i = listSize; i>curr ; i--){
                elements[i] = elements[i-1];
            }
            elements[curr] = item;
            listSize++;
        }
    }//O(n)

    @Override
    public E erase() throws NullPointerException{
        if(listSize == 0)throw new NullPointerException();
        E temp = getValue();
        for(int i = curr; i<listSize-1;i++)elements[i] = elements[i+1];
        if(curr == listSize-1 && curr != 0)curr--;
        listSize--;
        if(needToShrink())shrink();
        return temp;
    }//O(n)

    @Override
    public void pushBack(E item)throws IllegalArgumentException{
        if(item == null)throw new IllegalArgumentException();
        if(find(item) == -1){
            if(needToGrow())grow();
            elements[listSize++] = item;
        }
    }//O(n)

    @Override
    public void setToBegin() {
        curr = 0;
    }//O(1)

    @Override
    public void setToEnd() {
        if(listSize != 0)curr = listSize-1;
        else curr = 0;
    }//O(1)

    @Override
    public void setToPos(int pos)throws ArrayIndexOutOfBoundsException{
        if(pos>=0 && pos<listSize)curr = pos;
        else throw new ArrayIndexOutOfBoundsException();
    }//O(1)

    @Override
    public void prev() {
        if(curr != 0)curr--;
    }//O(1)

    @Override
    public void next() {
        if(curr != listSize-1 && listSize != 0)curr++;
    }//O(1)

    @Override
    public int size() {
        return listSize;
    }//O(1)

    @Override
    public int currPos() {
        return curr;
    }//O(1)

    @Override
    public E getValue()throws NullPointerException{
        if(listSize != 0)return elements[curr];
        else throw new NullPointerException();
    }//O(1)

    @Override
    public int find(E item)throws IllegalArgumentException {
        if(item == null)throw new IllegalArgumentException();
        else for(int i = 0; i < listSize ; i++)if(elements[i] == item)return i;
        return -1;
    }//O(n)

    @Override
    public  String toString(){
        StringBuilder s = new StringBuilder("<");
        if(listSize != 0){
            for(int i = 0; i < listSize ; i++){
                if(i == currPos())s.append("| ");
                if(i == listSize-1)s.append(elements[i]);
                else s.append(elements[i]).append(" ");
            }
        }
        s.append(">");
        return String.valueOf(s);
    }//O(n)
}
