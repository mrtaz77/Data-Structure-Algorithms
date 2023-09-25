import java.io.BufferedWriter;
import java.io.FileWriter;
import java.util.Random;
import java.util.Scanner;
public class TestCaseGen {
    public static void main(String[] args) {

        final String OUTPUT_FILE = "input.txt";
        var scanner = new Scanner(System.in);

        try(var writer = new BufferedWriter(new FileWriter(OUTPUT_FILE))){
            System.out.print("Customers : ");
            var n = scanner.nextInt();
            writer.write(n+"\n");

            System.out.print("Start : ");
            var start = scanner.nextInt();
            System.out.print("End : ");
            var end = scanner.nextInt();

            var rand = new Random();
            for(int i = 0; i < n; i++){
                var s = (rand.nextInt(end+1))%(end - start +1)+start;
                var e = (rand.nextInt(end+1))%(end - start +1)+start;
                while(e <= s) e = (rand.nextInt(end+1))%(end - start +1)+start;
                writer.write(s + " " + e + "\n");
            }
        }catch(Exception e){e.printStackTrace();}
    }
}
