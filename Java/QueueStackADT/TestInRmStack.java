
import java.io.InputStreamReader;
import java.util.Scanner;

public class TestInRmStack {
    public static void main(String[] args) {
        Scanner scn = new Scanner(new InputStreamReader(System.in));

        var k = scn.nextInt();
        var x = scn.nextInt();

        Integer[] a = new Integer[k];

        for (int i = 0; i < k;i++)a[i] = scn.nextInt();

        StackArr<Integer> arr = new StackArr<>(k,x,a);
        StackLL<Integer> ll = new StackLL<>(k,x,a);

        int t = scn.nextInt();

        while (t > 0) {
            int option = scn.nextInt();
            if(option == 1){
                var p = scn.nextInt();
                var offset = scn.nextInt();

                arr.insert(p,offset);
                ll.insert(p,offset);

                System.out.println(arr);
                System.out.println(ll);
            }
            if(option == 2){
                var p =scn.nextInt();

                arr.remove(p);
                ll.remove(p);

                System.out.println(arr);
                System.out.println(ll);
            }
            t--;
        }
    }
}
