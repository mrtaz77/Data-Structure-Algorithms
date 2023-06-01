import java.io.*;

public class GraphMain {
    private static final String INPUT_FILE = "input.txt";
    private static final String OUTPUT_FILE = "output.txt";
    public static void main(String[] args) {
        try(BufferedReader reader = new BufferedReader(new FileReader(INPUT_FILE))){
            BufferedWriter writer = new BufferedWriter(new FileWriter(OUTPUT_FILE));

            String[]n_m = reader.readLine().split(" ");
            int n = Integer.parseInt(n_m[0]);
            int m = Integer.parseInt(n_m[1]);

            GraphMat g = new GraphMat(n);
            for (int i = 0; i < m;i++){
                String[] u_v = reader.readLine().split(" ");
                int u = Integer.parseInt(u_v[0]);
                int v = Integer.parseInt(u_v[1]);
                g.setEdge(u,v,1);
            }
            System.out.println(g);
            int start = Integer.parseInt(reader.readLine());
            writer.write("BFS tree: \n"+g.BFS(start,true)+"\n");
            writer.write("DFS tree: \n"+g.DFS(start,true)+"\n");
            writer.write("BFS tree: \n"+g.BFSAll());
            writer.write("Cycle : "+g.checkCycle()+"\n");
            writer.close();
        }catch(Exception e){
            e.printStackTrace();
        }
    }
}
