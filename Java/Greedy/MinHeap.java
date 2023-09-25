public class MinHeap<E extends Comparable<? super E>> {
    private static final int DEFAULT_HEAP_SIZE = 10;
    private E[]heap;
    private int size;
    private int n;

    private boolean needToGrow(){return n == size;}
    private boolean needToShrink(){return n<= size/2 && n > 1;}

    @SuppressWarnings("unchecked")
    private void grow(){
        E[]temp = heap;
        heap = (E[])new Comparable[2*size];
        size *= 2;
        System.arraycopy(temp, 0, heap, 0, n);
    }

    @SuppressWarnings("unchecked")
    private void shrink(){
        E[] temp = heap;
        heap = (E[])new Comparable[size/2];
        size /= 2;
        System.arraycopy(temp, 0, heap, 0, n);
    }

    private void swap(int i,int j){
        E temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }


    @SuppressWarnings("unchecked")
    public MinHeap(){
        n = 0;
        size = DEFAULT_HEAP_SIZE;
        heap = (E[])new Comparable[size];
    }

    @SuppressWarnings("unchecked")
    public MinHeap(E[] items, int size){
        n = items.length;
        this.size = size == 0 ? DEFAULT_HEAP_SIZE:size;
        heap = (E[])new Comparable[size];
        System.arraycopy(items,0,heap,0,n);
        buildHeap();
    }

    private void buildHeap() {
        for(int i = n/2 -1; i >= 0;i--)siftDown(i);
    }

    public boolean isLeaf(int pos){return pos >= n/2 && pos<n;}
    public int parent(int pos)throws IllegalArgumentException{
        if(pos == 0)throw new IllegalArgumentException("Root has no parent");
        return (pos-1)/2;
    }
    public int left(int pos){return 2*pos+1;}
    public int right(int pos){return 2*pos+2;}
    public int size(){return n;}

    public E FindMin()throws NullPointerException{
        if(n == 0)throw new NullPointerException("Heap is empty");
        return heap[0];
    }

    public E ExtractMin()throws NullPointerException{
        if(n == 0)throw new NullPointerException("Heap is empty");
        E min = heap[0];
        swap(0,--n);
        heap[n] = null;
        if(n != 0)siftDown(0);
        if(needToShrink())shrink();
        return min;
    }

    public void deleteKey(E key)throws IllegalArgumentException{
        if(key == null)throw new IllegalArgumentException();
        int pos = find(key);
        if(pos != -1){
            if(pos == n-1){
                heap[pos] = null;
                n--;
            }
            else{
                swap(pos,--n);
                heap[n] = null;
                if(n != 1){
                    if(pos != 0)siftUp(pos);
                    siftDown(pos);
                }
            }
        }
        if(needToShrink())shrink();
    }

    private void siftDown(int pos) {
        while(!isLeaf(pos)){
            int lc = left(pos);
            if(lc < n-1 && heap[lc].compareTo(heap[lc+1]) > 0)lc++;
            if(heap[pos].compareTo(heap[lc]) <= 0)return;
            swap(pos,lc);
            pos = lc;
        }
    }

    public void Insert(E key)throws IllegalArgumentException{
        if(key == null)throw new IllegalArgumentException();
        if(needToGrow())grow();
        heap[n++] = key;
        if(n != 1)siftUp(n-1);
    }

    private void siftUp(int pos) {
        while(pos != 0 && heap[pos].compareTo(heap[parent(pos)]) < 0){
            swap(pos,parent(pos));
            pos = parent(pos);
        }
    }

    public int find(E key)throws NullPointerException{
        if(key == null)throw new NullPointerException();
        for(int pos = 0;pos < n;pos++)if(heap[pos].compareTo(key) == 0)return pos;
        return -1;
    }

    public void DecreaseKey(E prevKey,E newKey)throws IllegalArgumentException{
        if(prevKey == null || newKey == null)throw new IllegalArgumentException();
        if(newKey.compareTo(prevKey) > 0)throw new IllegalArgumentException();
        int pos = find(prevKey);
        if(pos != -1){
            heap[pos] = newKey;
            if(pos != 0)siftUp(pos);
        }
    }

    public void IncreaseKey(E prevKey,E newKey)throws IllegalArgumentException {
        if (prevKey == null || newKey == null) throw new IllegalArgumentException();
        if (newKey.compareTo(prevKey) < 0) throw new IllegalArgumentException();
        int pos = find(prevKey);
        if (pos != -1) {
            heap[pos] = newKey;
            if(!isLeaf(pos))siftDown(pos);
        }
    }

    public int height(int pos) {
        if (pos >= n) return 0;
        if( left(pos) >= n)return 1 + height(right(pos));
        else return 1 + height(left(pos));
    }

    public String printLevel(int pos, int level) {
        if (pos >= n) return "";
        if (level==0) {
            return heap[pos]+" ";
        }
        return printLevel(left(pos), level - 1) + printLevel(right(pos), level - 1);
    }


    public String Print(){
        StringBuilder sb = new StringBuilder();
        sb.append("Printing the binary heap ...\n- - - - - - - - - - - - - - - - - - - -\n");
        if(n != 0){
            int leftHeight = height(left(0));
            int rightHeight = height(right(0));
            int height = Math.max(leftHeight,rightHeight);
            for(int i=0 ; i<= height;i++){
                sb.append("Level ").append(i).append(": ");
                sb.append(printLevel(0,i));
                sb.append("\n");
            }
        }
        sb.append("- - - - - - - - - - - - - - - - - - - -");
        return sb.toString();
    }

    public void HeapSort(E[] items){
        MinHeap<E> h = new MinHeap<>(items,items.length);
        for(int i = 0; i < items.length; i++){
            items[i] = h.ExtractMin();
        }
    }
}
