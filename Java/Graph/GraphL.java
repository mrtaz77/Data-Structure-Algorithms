import MyListADT.LL;
import Queue.QueueLL;

import java.util.*;

class Edge{
    private int start;
    private int finish;
    private double weight;
    public Edge(int start, int finish, double weight){
        this.start = start;
        this.finish = finish;
        this.weight = weight;
    }

    public void setWeight(double weight) {
        this.weight = weight;
    }

    public double getWeight() {
        return weight;
    }

    public int getStart() {
        return start;
    }

    public int getFinish() {
        return finish;
    }

    @Override
    public String toString() {
        return "("+start+","+finish+")"+"("+weight+")";
    }
}

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
