import java.io.*;

public class IntervalScheduler {
    public final static String INPUT_FILE = "input.txt";
    public final static String OUTPUT_FILE = "output.txt";
    public static void main(String[] args) {
        try(BufferedReader reader = new BufferedReader(new FileReader(INPUT_FILE))){
            BufferedWriter writer = new BufferedWriter(new FileWriter(OUTPUT_FILE));

            MinHeap<Customer> minHeap = new MinHeap<>();
            int n = Integer.parseInt(reader.readLine());


            for(int i = 0; i < n; i++){
                var a_d = reader.readLine().split(" ");
                if(Integer.parseInt(a_d[0]) <= Integer.parseInt(a_d[1]))minHeap.Insert(new Customer(Integer.parseInt(a_d[0]),Integer.parseInt(a_d[1])));
            }

            //System.out.println(minHeap.Print());

            Customer c = minHeap.ExtractMin();
            var service = new StringBuilder(c.arrival()+" "+c.departure()+"\n");
            int served = 1;

            while(minHeap.size() > 0){
                if(c.departure() > minHeap.FindMin().arrival()){
                    minHeap.ExtractMin();
                }
                else{
                    c = minHeap.ExtractMin();
                    service.append(c.arrival()).append(" ").append(c.departure()).append("\n");
                    served++;
                }
            }
            writer.write(served+"\n"+service);
            writer.close();
        }catch(Exception e){
            e.printStackTrace();
        }
    }
}
