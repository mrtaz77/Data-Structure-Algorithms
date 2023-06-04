import java.io.*;
import MyListADT.*;

public class GraphMST {
    private static final String INPUT_FILE = "input.txt";
    private static final String OUTPUT_FILE = "output.txt";
    public static void main(String[] args) {
        try(BufferedReader reader = new BufferedReader(new FileReader(INPUT_FILE))){
            BufferedWriter writer = new BufferedWriter(new FileWriter(OUTPUT_FILE));

            String[]n_m = reader.readLine().split(" ");
            int n = Integer.parseInt(n_m[0]);
            int m = Integer.parseInt(n_m[1]);

            GraphMat g = new GraphMat(n);
            GraphMat help = new GraphMat(n);
            for (int i = 0; i < m;i++){
                String[] u_v = reader.readLine().split(" ");
                int u = Integer.parseInt(u_v[0]);
                int v = Integer.parseInt(u_v[1]);
                Double w = Double.parseDouble(u_v[2]);
                g.setEdge(u,v,w);   
                help.setEdge(u, v, Math.min(g.getEdge(u, v),g.getEdge(v, u)));
                help.setEdge(v, u, Math.min(g.getEdge(v, u),g.getEdge(u, v)));

            }
            System.out.println(g);
            System.out.println(help);
            int start = Integer.parseInt(reader.readLine());
            writer.write("MST (Prim + Minheap): \n");
            LL<Edge> edges_of_mst = help.MSTPrim(start);
            double weight = 0;
            while (edges_of_mst.size() != 0){
                Edge e = edges_of_mst.erase();
                if(g.getEdge(e.getStart(), e.getFinish()) == e.getWeight())writer.write(e+"\n");
                else{
                    writer.write(e.getFinish()+" -> "+e.getStart()+" ("+g.getEdge(e.getFinish(), e.getStart())+")"+"\n");
                }
                weight += e.getWeight();
            }
            writer.write("MST (Prim + Minheap) cost: "+weight);
            writer.close();
        }catch(Exception e){
            e.printStackTrace();
        }
    }
}
