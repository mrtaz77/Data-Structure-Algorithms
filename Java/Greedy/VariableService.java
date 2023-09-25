import java.util.*;

class VarCustomer{
    int arrival;
    int departure;

    public VarCustomer(int arrival, int departure) {
        this.arrival = arrival;
        this.departure = departure;
    }

    @Override
    public String toString(){
        return "("+arrival+","+departure+")";
    }
}

public class VariableService {
    public static void main(String[] args) {
        Scanner scn = new Scanner(System.in);
        int n = scn.nextInt();
        int []arr = new int[n];
        int []dept = new int[n];
        for (int i = 0; i < n; i++){
            arr[i] = scn.nextInt();
            dept[i] = scn.nextInt();
        }
        Arrays.sort(arr);
        Arrays.sort(dept);

        int count = 1,ans = 1;
        int i = 1,j = 0;
        while (i < n && j < n){
            if(arr[i] < dept[j]){
                count++;
                i++;
            }
            else{
                count--;
                j++;
            }
            ans = Math.max(ans,count);
        }
        System.out.println(ans);
    }
}
