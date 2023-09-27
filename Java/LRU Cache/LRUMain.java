import java.io.*;

public class LRUMain {

    public static void main(String[] args) {

        final String INPUT_FILE = "lru_input.txt";
        final String OUTPUT_FILE = "lru_output.txt";

        try(BufferedReader reader = new BufferedReader(new FileReader(INPUT_FILE))){
            BufferedWriter writer = new BufferedWriter(new FileWriter(OUTPUT_FILE));

            int c,q,o,x,y;
            c = Integer.parseInt(reader.readLine());
            q = Integer.parseInt(reader.readLine());

            LRUCache<Integer,Integer> lruCache = new LRUCache<>(c);

            while(q > 0){
                String[] o_x_y = reader.readLine().split(" ");
                o = Integer.parseInt(o_x_y[0]);
                x = Integer.parseInt(o_x_y[1]);
                if(o == 2){
                    y = Integer.parseInt(o_x_y[2]);
                    lruCache.put(x,y);
                }
                else{
                    if(lruCache.get(x) == null)writer.write("-1\n");
                    else{
                        writer.write(lruCache.get(x)+"\n");
                    }
                }
                q--;
            }
            writer.close();
        }catch(Exception e) {
            System.out.println(e);
        }
    }
}
