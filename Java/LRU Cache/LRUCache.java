public class LRUCache<K,V> {
    private final int capacity;
    private final Arr<K> keyList;
    private final Arr<V> valueList;

    private void moveToHead(int pos){
        //Arr implementation : O(1)
        //LL implementation : O(n)
        keyList.setToPos(pos);
        valueList.setToPos(pos);

        //Both implementation : O(n)
        K key = keyList.erase();
        V value = valueList.erase();

        //Both implementation : O(1)
        keyList.setToBegin();
        valueList.setToBegin();

        //Arr implementation : O(n)
        //LL implementation : O(1)
        //However as maximum size of array remains same no extra space needs to be allocated for array based implementation
        keyList.push(key);
        valueList.push(value);
    }//O(n)

    public LRUCache(int capacity){
        keyList = new Arr<>();
        valueList = new Arr<>();
        this.capacity = capacity;
    }

    public V get(K key){
        int pos = keyList.find(key); //Both implementations : O(n)
        if(pos == -1)return null;
        else{
            moveToHead(pos); //Both implementations : O(n)
            return valueList.getValue(); //Both implementations : O(1)
        }
    }//O(n) for both implementations

    public void put(K key,V value){
        int pos = keyList.find(key); //Both implementations : O(n)
        if(pos == -1){
            if(keyList.size() == capacity){
                //Arr implementation : O(1)
                //LL implementation : O(n)
                keyList.setToEnd();
                valueList.setToEnd();

                //Arr implementation : Always O(1) because erase occurs at tail
                //LL implementation : Always O(n) because erase occurs at tail
                keyList.erase();
                valueList.erase();

                //Both implementations : O(1)
                keyList.setToBegin();
                valueList.setToBegin();
            }
            keyList.push(key);
            valueList.push(value);
        }
        else{
            moveToHead(pos);//Both implementations : O(n)

            //Arr implementation : Always O(n) because erase occurs at head
            //LL implementation : Always O(1) because erase occurs at head
            valueList.erase();

            //Arr implementation : O(n)
            //LL implementation : O(1)
            valueList.push(value);
        }
    }//O(n)
}
