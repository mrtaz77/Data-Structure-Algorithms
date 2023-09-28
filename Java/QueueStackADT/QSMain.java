
import java.io.*;

public class QSMain {
    private static final String INPUT_FILE = "input.txt";
    private static final String OUTPUT_FILE = "output.txt";

    public static void main(String[] args){
        try (BufferedReader reader = new BufferedReader(new FileReader(INPUT_FILE))){
            BufferedWriter writer = new BufferedWriter(new FileWriter(OUTPUT_FILE));

            var k_x = reader.readLine().split(" ");

            var k = Integer.parseInt(k_x[0]);
            var x = Integer.parseInt(k_x[1]);

            var qIt = new Integer[k];
            var input = reader.readLine().split(" ");
            for (int i = 0; i < qIt.length; i++) qIt[i] = Integer.parseInt(input[i]);

            //QueueArr<Integer> myQueue = new QueueArr<>(k,x, qIt);
            QueueLL<Integer> myQueue = new QueueLL<>(k,x,qIt);

            var m_y = reader.readLine().split(" ");

            var m = Integer.parseInt(m_y[0]);
            var y = Integer.parseInt(m_y[1]);

            var sIt = new Integer[m];
            input = reader.readLine().split(" ");
            for (int i = 0; i < sIt.length; i++) sIt[i] = Integer.parseInt(input[i]);

            StackArr<Integer> myStack = new StackArr<>(m,y,sIt);
            //StackLL<Integer> myStack = new StackLL<>(m,y,sIt);

            writer.write(myQueue+"\n");
            writer.write(myStack+"\n");

            var q = Integer.parseInt(reader.readLine());

            while (q > 0) {
                String[] f_p = reader.readLine().split(" ");
                var f = Integer.parseInt(f_p[0]);
                var p = Integer.parseInt(f_p[1]);

                switch (f){
                    case 1 :
                        myQueue.clear();
                        writer.write(myQueue+"\n-1\n");
                        break;
                    case 2 :
                        try{
                            myQueue.enqueue(p);
                        }catch(Exception e){
                            System.out.println(e);
                        }
                        writer.write(myQueue+"\n-1\n");
                        break;
                    case 3 :
                        if (myQueue.length() == 0)writer.write(myQueue+"\n-1\n");
                        else{
                            int output = myQueue.dequeue();
                            writer.write(myQueue+"\n"+output+"\n");
                        }
                        break;
                    case 4 :
                        writer.write(myQueue+"\n"+myQueue.length()+"\n");
                        break;
                    case 5 :
                        if (myQueue.length() == 0)writer.write(myQueue+"\n-1\n");
                        else{
                            int output = myQueue.frontValue();
                            writer.write(myQueue+"\n"+output+"\n");
                        }
                        break;
                    case 6:
                        if (myQueue.length() == 0)writer.write(myQueue+"\n-1\n");
                        else{
                            int output = myQueue.rearValue();
                            writer.write(myQueue+"\n"+output+"\n");
                        }
                        break;
                    case 7:
                        if (myQueue.length() == 0)writer.write(myQueue+"\n-1\n");
                        else{
                            int output = myQueue.leaveQueue();
                            writer.write(myQueue+"\n"+output+"\n");
                        }
                        break;
                    case 8 :
                        myStack.clear();
                        writer.write(myStack+"\n-1\n");
                        break;
                    case 9 :
                        try{
                            myStack.push(p);
                        }catch(Exception e){
                            System.out.println(e);
                        }
                        writer.write(myStack+"\n-1\n");
                        break;
                    case 10:
                        if(myStack.length() == 0)writer.write(myStack+"\n-1\n");
                        else{
                            int output = myStack.pop();
                            writer.write(myStack+"\n"+output+"\n");
                        }
                        break;
                    case 11:
                        writer.write(myStack+"\n"+myStack.length()+"\n");
                        break;
                    case 12:
                        if(myStack.length() == 0) writer.write(myStack+"\n-1\n");
                        else{
                            int output = myStack.topValue();
                            writer.write(myStack+"\n"+output+"\n");
                        }
                        break;
                    default:
                        System.out.println("Invalid Command");
                        break;
                }
                q--;
            }
            writer.close();
        } catch (IOException e) {
            System.out.println(e);
        }
    }
}
