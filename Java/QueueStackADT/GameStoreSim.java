

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;

public class GameStoreSim {
    private final int customerCount;
    private Customer consoleQ;
    private Customer consoleS;

    private boolean consoleQempty ;
    private boolean consoleSempty ;

    private final int activeTime;
    private final int queueSize;
    private final QueueLL<Customer> activeQ;
    private final StackLL<Customer> activeS;
    private QueueLL<Customer> departQ;

    public GameStoreSim(int customerCount, int activeTime,int queueSize){
        this.customerCount = customerCount;
        this.activeTime = activeTime;
        this.queueSize = queueSize;

        consoleQempty = true;
        consoleSempty = true;

        activeQ = new QueueLL<>();
        activeS = new StackLL<>();
        departQ = new QueueLL<>();
    }

    public void entryToActiveQ(Customer c){
        /*System.out.println("Entry of customer : "+c);
        System.out.println("ConsoleQ : "+consoleQ);
        System.out.println("ActiveQ : "+activeQ);
        System.out.println("DepartQ : "+departQ);*/
        //initial customer
        if(consoleQempty){
            //System.out.println("When consoleQ is empty");

            c.setDuration(Math.min(activeTime,c.duration()+c.arrival()));
            consoleQ = c;
            consoleQempty = false;

            /*System.out.println("Entry of customer : "+c);
            System.out.println("ConsoleQ : "+consoleQ);
            System.out.println("ActiveQ : "+activeQ);
            System.out.println("DepartQ : "+departQ);*/
        }
        //queue not full
        else if(activeQ.length() < queueSize || c.arrival() >= consoleQ.duration()){
            if(c.arrival() >= consoleQ.duration()){
                //System.out.println(c.arrival()+" >= "+consoleQ.duration());
                while(c.arrival() >= consoleQ.duration() && activeQ.length() != 0){
                    /*System.out.println("In while loop");
                    System.out.println(c.arrival()+" >= "+consoleQ.duration()+" && "+activeQ.length());*/
                    departQ.enqueue(consoleQ);
                    activeQ.frontValue().setDuration(Math.min(activeTime,activeQ.frontValue().duration()+consoleQ.duration()));
                    consoleQ = activeQ.dequeue();
                    /*System.out.println("Customer : "+c);
                    System.out.println("ConsoleQ : "+consoleQ);
                    System.out.println("ActiveQ : "+activeQ);
                    System.out.println("DepartQ : "+departQ);*/
                }
                if(activeQ.length() == 0 && c.arrival() >= consoleQ.duration()){
                    //System.out.println("When activeQ length is 0");
                    departQ.enqueue(consoleQ);
                    c.setDuration(Math.min(activeTime,c.duration()+c.arrival()));
                    consoleQ = c;
                }
                else{
                    //System.out.println("When activeQ is not empty");
                    activeQ.enqueue(c);
                }
            }
            else{
                //System.out.println("When queue is not empty only");
                activeQ.enqueue(c);
            }
            /*System.out.println("Customer : "+c);
            System.out.println("ConsoleQ : "+consoleQ);
            System.out.println("ActiveQ : "+activeQ);
            System.out.println("DepartQ : "+departQ);*/
        }
        //queue full
        else entryToActiveS(c);
    }

    public void entryToActiveS(Customer c){
        /*System.out.println("Entry of customer in stack : "+c);
        System.out.println("ConsoleS : "+consoleS);
        System.out.println("ActiveS : "+activeS);
        System.out.println("DepartQ : "+departQ);*/
        //initial customer
        if(consoleSempty){
            //System.out.println("When consoleS is empty");
            c.setDuration(Math.min(activeTime,c.duration()+c.arrival()));
            consoleS = c;
            consoleSempty = false;
            /*System.out.println("ConsoleS : "+consoleS);
            System.out.println("ActiveS : "+activeS);
            System.out.println("DepartQ : "+departQ);*/
        }
        //stack not full
        else if(c.arrival() > consoleS.duration()){
            if(activeS.length() != 0){
                while(activeS.length() != 0 && c.arrival() > consoleS.duration()){
                    departQ.enqueue(consoleS);
                    activeS.topValue().setDuration(Math.min(activeTime,consoleS.duration()+activeS.topValue().duration()));
                    consoleS = activeS.pop();
                }
                if(activeS.length() == 0 && c.arrival() >= consoleS.duration()){
                    departQ.enqueue(consoleS);
                    c.setDuration(Math.min(activeTime,c.duration()+c.arrival()));
                    consoleS = c;
                }
                else{
                    activeS.push(c);
                }
            }
            else{
                departQ.enqueue(consoleS);
                c.setDuration(Math.min(activeTime,c.duration()+c.arrival()));
                consoleS = c;
            }
        }
        else if(c.arrival() == consoleS.duration()){
            departQ.enqueue(consoleS);
            c.setDuration(Math.min(activeTime,c.duration()+c.arrival()));
            consoleS = c;
        }
        //stack entry
        else{
            activeS.push(c);
        }
    }

    public void closeStore(){
        var customers = new Customer[customerCount];
        int index = 0;

        System.out.println("========Closing Store===========");
        System.out.println(consoleQ+"\n"+consoleS);
        System.out.println(activeQ);
        System.out.println(activeS);
        System.out.println(departQ);

        if(!consoleQempty){
            customers[index++] = consoleQ;
            while(activeQ.length() != 0){
                if(consoleQ.duration() == activeTime || consoleQ.duration() == -1){
                    activeQ.frontValue().setDuration(-1);
                }
                else{
                    activeQ.frontValue().setDuration(Math.min(activeTime,consoleQ.duration()+activeQ.frontValue().duration()));
                }
                consoleQ = activeQ.dequeue();
                customers[index++] = consoleQ;
            }
        }
        if(!consoleSempty){
            customers[index++] = consoleS;
            while(activeS.length() != 0){
                if(consoleS.duration() == activeTime || consoleS.duration() == -1){
                    activeS.topValue().setDuration(-1);
                }
                else{
                    activeS.topValue().setDuration(Math.min(activeTime,consoleS.duration()+activeS.topValue().duration()));
                }
                consoleS = activeS.pop();
                customers[index++] = consoleS;
            }
        }

        while(departQ.length() != 0)customers[index++] = departQ.dequeue();

        for(int i = 0 ; i < customerCount-1;i++){
            for(int j = i + 1; j<customerCount;j++){
                if(customers[i].arrival() > customers[j].arrival()){
                    Customer temp = customers[i];
                    customers[i] = customers[j];
                    customers[j] = temp;
                }
            }
        }


        //System.out.println(Arrays.toString(customers));
        departQ = new QueueLL<>(customerCount,customerCount,customers);
    }

    public String departureLog(){
        StringBuilder sb = new StringBuilder();

        for(int i = 1; i <= customerCount; i++){
            if(departQ.frontValue().duration() != -1)
                sb.append(i).append(" > ").append(departQ.frontValue().duration()).append("\n");
            else sb.append(i).append(" > c\n");
            departQ.dequeue();
        }
        return sb.toString();
    }

    public static void main(String[] args) {
        final String INPUT_FILE = "game_store_input.txt";
        final String OUTPUT_FILE = "game_store_output.txt";

        try (BufferedReader reader = new BufferedReader(new FileReader(INPUT_FILE))){
            BufferedWriter writer =new BufferedWriter(new FileWriter(OUTPUT_FILE));

            var n_c = reader.readLine().split(" ");
            var n = Integer.parseInt(n_c[0]);
            var c = Integer.parseInt(n_c[1]);

            GameStoreSim store = new GameStoreSim(n,c,3);

            for(int i = 0 ; i < n ; i++){
                var a_d = reader.readLine().split(" ");
                var a = Integer.parseInt(a_d[0]);
                var d = Integer.parseInt(a_d[1]);
                store.entryToActiveQ(new Customer(a,d));
            }

            store.closeStore();
            writer.write(store.departureLog());

            writer.close();
        }catch (Exception e){
            e.printStackTrace();
            System.out.println(e);
        }
    }
}


