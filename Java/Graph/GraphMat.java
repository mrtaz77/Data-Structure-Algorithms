import MyListADT.LL;
import Queue.QueueLL;

import java.util.*;

public class GraphMat{
    private final double [][] adjMat;
    private int numEdge;
    private final int [] vis;

    public GraphMat(int n){
        vis = new int[n];
        adjMat = new double[n][n];
        Arrays.stream(adjMat).forEach(a -> Arrays.fill(a, Double.POSITIVE_INFINITY));
        numEdge = 0;
    }

    public int numVertices() {return vis.length;}
    public int numEdges() {return numEdge;}

    public int first(int vertex) {
        for(int i = 0; i < vis.length ; i++)
            if(adjMat[vertex][i] != 0)return i;
        return vis.length;
    }

    public int next(int u,int v) {
        for(int i = v+1; i < vis.length ; i++)
            if(adjMat[u][i] != 0)return i;
        return vis.length;
    }

    public void setEdge(int from,int to,double weight)throws IllegalArgumentException{
        if(weight == 0)throw new IllegalArgumentException();
        if(adjMat[from][to] == 0)numEdge++;
        adjMat[from][to] = weight;
    }

    public void rmEdge(int from,int to){
        if(adjMat[from][to] != 0)numEdge--;
        adjMat[from][to] = 0;
    }

    public boolean isEdge(int from,int to){return adjMat[from][to] != Double.POSITIVE_INFINITY;}

    public void setvis(int vertex,int val){vis[vertex] = val;}
    public int getvis(int vertex){return vis[vertex];}

    public double getEdge(int from,int to){return adjMat[from][to];}

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for(int i = 0;i < vis.length;i++){
            sb.append(i).append(" -> ");
            for(int j = 0;j < adjMat[i].length;j++){
                if(isEdge(i,j)) sb.append(j).append(" ");
            }
            sb.append("\n");
        }
        return sb.toString();
    }

    public String BFS(int start,boolean reset){
        QueueLL<Integer> q = new QueueLL<>();
        StringBuilder vert = new StringBuilder("{");
        StringBuilder edge = new StringBuilder("{");
        StringBuilder bfs = new StringBuilder();

        q.enqueue(start);
        setvis(start,1);

        while(q.length() != 0){
            int v = q.dequeue();
            vert.append(v).append(",");
            StringBuilder temp = new StringBuilder();
            for(int w = first(v); w < numVertices(); w = next(v,w)){
                if(getvis(w) == 0) {
                    temp.append(w).append(",");
                    edge.append("(").append(v).append(",").append(w).append("),");
                    setvis(w, 1);
                    q.enqueue(w);
                }
            }
            if(temp.length() != 0){
                temp.setCharAt(temp.length() - 1, '\n');
                bfs.append(v).append(" -> ").append(temp);
            }
        }
        if(vert.length() != 1)vert.deleteCharAt(vert.length() - 1);
        if(edge.length() != 1)edge.deleteCharAt(edge.length() - 1);
        vert.append("}");
        edge.append("}");
        if(reset)Arrays.fill(vis,0);
        return bfs+"V : "+vert+"\nE : "+edge+"\n";
    }

    public String BFSAll(){
        StringBuilder bfs = new StringBuilder();
        for(int i = 0 ;i < vis.length;i++){
            if(getvis(i) == 0)bfs.append(BFS(i,false));
        }
        Arrays.fill(vis,0);
        return bfs +"\n";
    }

    public String DFS(int start,boolean reset){
        LL<Integer> set = new LL<>();
        LL<Integer> u = new LL<>();
        LL<Integer> v = new LL<>();

        DFSHelper(start,set,u,v);

        StringBuilder dfs = new StringBuilder();
        StringBuilder vert = new StringBuilder("{");
        while(u.size() > 0){
            int m = u.getValue();
            int n = v.getValue();
            dfs.append(m).append(" -> ").append(n).append(",");
            u.erase();
            v.erase();
            for(int i=0;i<u.size();i++){
                u.setToPos(i);
                v.setToPos(i);
                if(u.getValue() == m){
                    n = v.erase();
                    dfs.append(n).append(",");
                    u.erase();
                }
            }
            u.setToBegin();
            v.setToBegin();
            dfs.setCharAt(dfs.length() - 1, '\n');
        }
        while(set.size() > 0)vert.append(set.erase()).append(",");
        vert.setCharAt(vert.length() - 1, '}');
        vert.append("\n");
        if(reset)Arrays.fill(vis,0);
        return dfs +"V : "+vert;
    }

    private void DFSHelper(int start, LL<Integer> set,LL<Integer> u,LL<Integer> v) {
        setvis(start,1);
        set.pushBack(start);
        for(int w = first(start); w < numVertices(); w = next(start,w)){
            if(getvis(w) == 0){
                u.pushBack(start);
                v.pushBack(w);
                DFSHelper(w,set,u,v);
            }
        }
    }

    public boolean checkCycle(){
        boolean[] array = new boolean[vis.length];
        Arrays.fill(vis,0);
        for(int i = 0; i < array.length; i++){
            if(cycleHelper(i, array))return true;
        }
        return false;
    }

    private boolean cycleHelper(int i, boolean[] array) {
        if(array[i])return true;
        if(getvis(i) == 1)return false;

        setvis(i,1);
        array[i] = true;

        for(int w = first(i); w < numVertices(); w = next(i,w)){
            if(cycleHelper(w, array))return true;
        }
        array[i] = false;
        return false;
    }

    LL<Edge> MSTPrim(int start){
        MinHeap<Edge> minheap = new MinHeap<Edge>();
        LL<Edge> mst = new LL<>();

        minheap.Insert(new Edge(-1,start,0));

        while(minheap.size() > 0){
            Edge e = minheap.ExtractMin();
            int v = e.getFinish();
            if(getvis(v) == 0){
                setvis(v, 1);
                if(e.getStart() != -1)mst.pushBack(e);
                for(int w = first(v); w < numVertices(); w = next(v,w)){
                    if(getvis(w) == 0){
                        minheap.Insert(new Edge(v,w,adjMat[v][w]));
                    }
                }
            }
        }
        Arrays.fill(vis,0);
        return mst;
    }
}