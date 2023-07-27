import java.io.*;
import java.math.BigDecimal;
import java.math.RoundingMode;
public class AVLMain {
    private static final String INPUT_FILE = "in.txt";
    private static final String OUTPUT_FILE = "out.txt";
    private static final String REPORT_FILE = "report_avl.txt";

    private static BigDecimal reportUtil(long time) {
        BigDecimal nanosOperation = BigDecimal.valueOf(time);
        BigDecimal millisOperation = nanosOperation.divide(BigDecimal.valueOf(1_000_000), 8, RoundingMode.HALF_UP);
        return millisOperation;
    }

    public static void main(String[] args) {
        try(BufferedReader in = new BufferedReader(new FileReader(INPUT_FILE))){
            BufferedWriter out = new BufferedWriter(new FileWriter(OUTPUT_FILE));
            BufferedWriter report = new BufferedWriter(new FileWriter(REPORT_FILE));

            AVL<Integer> tree = new AVL<>();
            AVLNode<Integer> root = null;
            long insertTime = 0;
            long deleteTime = 0;
            long searchTime = 0;
            long travTime = 0;
            long totalTime = 0;
            long start,end;
            
            while(true){
                var input = in.readLine();
                if(input == null)break;
                var f_p = input.split(" ");
                switch (f_p[0]) {
                    case "I": {
                        start = System.nanoTime();
                        root = tree.insert(root, Integer.parseInt(f_p[1]));
                        end = System.nanoTime();
                        insertTime += (end-start);
                        out.write(tree.show(root) + "\n");
                        break;
                    }
                    case "D": {
                        start = System.nanoTime();
                        root = tree.delete(root, Integer.parseInt(f_p[1]));
                        end = System.nanoTime();
                        deleteTime += (end-start);
                        out.write(tree.show(root) + "\n");
                        break;
                    }
                    case "T":
                        start = System.nanoTime();
                        String inO = tree.inOrder(root);
                        end = System.nanoTime();
                        travTime += (end-start);
                        out.write(inO + "\n");
                        break;
                    case "F":
                        start = System.nanoTime();
                        boolean found = tree.find(root, Integer.parseInt(f_p[1]));
                        end = System.nanoTime();
                        searchTime += (end-start);
                        if(found)out.write( "found\n");
                        else out.write( "not found\n");
                        break;
                }
            }
            totalTime += insertTime+searchTime+deleteTime+travTime;

            report.write("operation time(ms)\n");
            report.write("insert "+reportUtil(insertTime)+"\n");
            report.write("delete "+reportUtil(deleteTime)+"\n");
            report.write("search "+reportUtil(searchTime)+"\n");
            report.write("trav "+reportUtil(travTime)+"\n");
            report.write("total "+reportUtil(totalTime)+"\n");
            
            out.close();
            report.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

