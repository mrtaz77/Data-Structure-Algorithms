import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

class Job implements Comparable<Job>{
    private int id;
    private int deadline;
    private int profit;

    public Job(){
        id = 0;
        deadline = profit = 0;
    }

    public Job(int id, int deadline, int profit) {
        this.id = id;
        this.deadline = deadline;
        this.profit = profit;
    }

    public int id() {
        return id;
    }

    public Job setId(int id) {
        this.id = id;
        return this;
    }

    public int deadline() {
        return deadline;
    }

    public Job setDeadline(int deadline) {
        this.deadline = deadline;
        return this;
    }

    public int profit() {
        return profit;
    }

    public Job setProfit(int profit) {
        this.profit = profit;
        return this;
    }

    @Override
    public int compareTo(Job o) {
        if(o.profit == profit)return deadline - o.deadline;
        return o.profit - profit;
    }

    @Override
    public String toString() {return "("+id+","+profit+","+deadline+")";}
}
public class DeadProfit {
    public final static String INPUT_FILE = "jdp_input.txt";
    public final static String OUTPUT_FILE = "jdp_output.txt";
    public static void main(String[] args) {
        try(BufferedReader reader = new BufferedReader(new FileReader(INPUT_FILE))){
            BufferedWriter writer = new BufferedWriter(new FileWriter(OUTPUT_FILE));

            int n = Integer.parseInt(reader.readLine());
            MinHeap<Job> jobs = new MinHeap<>();
            List<Job> job_s = new ArrayList<>();

            for (int i = 0; i < n; i++){
                var id_p_d = reader.readLine().split(" ");
                jobs.Insert(new Job(i,Integer.parseInt(id_p_d[0]),Integer.parseInt(id_p_d[1])));
                job_s.add(new Job(i,Integer.parseInt(id_p_d[0]),Integer.parseInt(id_p_d[1])));
            }

            var mark = new boolean[n];

            Collections.sort(job_s);

            var opt = new Job[n];
            int count = 0;
            int profit = 0;
            while(jobs.size() > 0){
                var job = jobs.ExtractMin();
                for(int j = job.deadline()-1; j >= 0;j--) {
                    if (opt[j] == null) {
                        opt[j] = job;
                        mark[job.id()] = true;
                        count++;
                        profit += job.profit() ;
                        break;
                    }
                }
            }


            writer.write(count+"\n"+profit+"\n");

            for(int i = 0;i < mark.length;i++){
                if(mark[i])writer.write((i+1)+" ");
            }
            writer.write("\n");

            for (int i = 0; i < opt.length; i++) {
                if(opt[i] == null)continue;
                writer.write(i+" : "+(opt[i].id()+1) + "\n");
            }

            writer.close();
        }catch(Exception e){
            e.printStackTrace();
        }
    }
}
