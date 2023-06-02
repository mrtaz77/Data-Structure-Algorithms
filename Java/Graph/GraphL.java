import MyListADT.LL;
import Queue.QueueLL;

import java.util.*;

public class GraphL {
    private  LL<Edge> adjLl [] ;
    private int numEdge;
    private final int [] vis;

    @SuppressWarnings("unchecked")
    public GraphL(int numVertex){
        adjLl = (LL<Edge>[])new LL[numVertex];
        vis = new int[numVertex];
        numEdge = 0;
    }

    public int numVertices() {return vis.length;}
    public int numEdges() {return numEdge;}

    public void addEdge(int start, int finish, double weight){
        adjLl[start].pushBack(new Edge(finish, start, weight));
        numEdge++;
    }

    public int first(int vertex) {
        if(adjLl[vertex].size()!= 0){
            adjLl[vertex].setToBegin();
            return adjLl[vertex].getValue().getFinish();
        }
        return vis.length;
    }
}
