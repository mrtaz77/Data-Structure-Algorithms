abstract class MyList<E> {
    //modifiers
     abstract void clear();
     abstract void push(E item);
     abstract E erase();
     abstract void pushBack(E item);

    //iterators
     abstract void setToBegin();
     abstract void setToEnd();
     abstract void setToPos(int pos);
     abstract void prev();
     abstract void next();

    //member accessors
     abstract int size();
     abstract int currPos();

    //element accessors
     abstract E getValue();
     abstract int find(E item);
}
