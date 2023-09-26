import java.util.Scanner;

public class InversionCount {
    private static int[] inversion(int[] a,int start,int end){
        //System.out.println("In inversion with start("+start+") and end("+end+")");
        if(end == start)return null;
        if(end == start+1){
            if(a[start] > a[end]){
                var base = new int[2];
                base[0] = a[start];
                base[1] = a[end];

                a[start] = base[1];
                a[end] = base[0];

                //System.out.println("Base : " + Arrays.toString(base));
                return base;
            }
        }
        else{
            int mid = (start+end)/2;

            var left = inversion(a,start,mid);
            //System.out.println("Left : " + Arrays.toString(left));

            var right = inversion(a,mid+1,end);
            //System.out.println("Right : " + Arrays.toString(right));

            var across = mergeInversion(a,start, end);

            var combine = new int[ (left != null ? left.length:0)+(right != null ? right.length:0)+ across.length];
            int j = 0;



            for (int i = 0; i < (left != null ? left.length:0); i++){
                combine[j++] = left[i];
            }
            /*System.out.println("j : "+j);
            System.out.println("Func Combine left : "+Arrays.toString(combine));*/
            for (int k : across) {
                combine[j++] = k;
            }
            /*System.out.println("j : "+j);
            System.out.println("Func Combine middle : "+Arrays.toString(combine));*/
            for (int i = 0; i < (right != null ? right.length:0); i++){
                combine[j++] = right[i];
            }
            /*System.out.println("j : "+j);
            System.out.println("Func Combine right : "+Arrays.toString(combine));
            System.out.println("Array : "+Arrays.toString(a));*/
            return combine;
        }
        return null;
    }

    private static int[] mergeInversion(int[] a, int start, int end) {
        //System.out.println("In merge inversion with start("+start+") and end("+end+")");
        var mid = (start+end)/2;
        var merge = new int[2*(end-mid)*(mid-start+1)];
        var sort = new int[end-start+1];
        int i = 0,s = 0, p1 = start , p2 = mid+1;
        var count = 0;
        while(p1 <= mid && p2 <= end){
            if(a[p1] <= a[p2])sort[s++] = a[p1++];
            else{
                sort[s++] = a[p2];
                int j = p1;
                count += mid-p1+1;//O(nlog n) for finding number of inversions
                while(j <= mid){
                    merge[i++] = a[j++];
                    merge[i++] = a[p2];
                }
                p2++;
            }
        }
        if(p1 > mid)for(int j = p2; j <= end; j++)sort[s++] = a[j];
        else for(int j = p1; j <= mid; j++)sort[s++] = a[j];
        //System.out.println("Count : "+count);
        var ans = new int[count*2];
        System.arraycopy(merge,0, ans,0,count*2);
        //System.out.println("Merge : " + Arrays.toString(merge));
        //System.out.println("Ans : " + Arrays.toString(ans));
        System.arraycopy(sort,0,a,start,sort.length);
        //System.out.println("Array : " + Arrays.toString(a));
        return ans;
    }

    public static void main(String[] args) {
        var scn = new Scanner(System.in);
        var n = scn.nextInt();
        var arr = new int[n];

        for (int i = 0; i < n; i++)arr[i] = scn.nextInt();

        var soln = inversion(arr,0,arr.length-1);

        if(soln == null || soln.length == 0) System.out.println(0);
        else{
            System.out.print(soln.length/2+"\nThe inverted pairs are : ");
            for(int i = 0; i < soln.length;i+=2){
                if(i == soln.length-2) System.out.print("("+soln[i]+","+soln[i+1]+").");
                else{
                    System.out.print("("+soln[i]+","+soln[i+1]+"),");
                }
            }
        }

    }
}
