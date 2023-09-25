import java.util.*;

class WaitCustomer implements Comparable<WaitCustomer>{
    int serial;
    int service;
    public WaitCustomer(int serial, int service) {
        this.serial = serial;
        this.service = service;
    }

    @Override
    public int compareTo(WaitCustomer o) {
        return service-o.service;
    }
}

public class WaitingQ {
    public static void main(String[] args) {
        List<WaitCustomer> q = new ArrayList<>();
        Scanner scn = new Scanner(System.in);

        int n = scn.nextInt();

        for(int i = 0; i < n; i++)q.add(new WaitCustomer(i+1,scn.nextInt()));

        Collections.sort(q);

        double avg = 0;
        var wait = new int[n];
        wait[0] = 0;

        for(int i = 0; i < n; i++){
            System.out.print(q.get(i).serial+" ");
            if(i > 0){
                wait[i] = wait[i-1] + q.get(i-1).service;
            }
        }
        for(int i = 0; i < n; i++)avg += wait[i];

        System.out.println();
        System.out.println(Arrays.toString(wait));
        System.out.println("Minimum average waiting time : "+avg/n);

    }
}
