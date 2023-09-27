import java.io.*;

public class HeapMain {
    private static final String INPUT_FILE = "input.txt";
    private static final String OUTPUT_FILE = "output.txt";

    public static void main(String[] args) {
        try (var reader = new BufferedReader(new FileReader(INPUT_FILE))) {
            var writer = new BufferedWriter(new FileWriter(OUTPUT_FILE));

            /*String[] k_x = reader.readLine().split(" ");
            int k = Integer.parseInt(k_x[0]);
            int x = Integer.parseInt(k_x[1]);

            Integer[] items = new Integer[k];
            String[] inputs = reader.readLine().split(" ");
            for (int i = 0; i < items.length; i++) items[i] = Integer.parseInt(inputs[i]);*/

            MinHeap<Integer> heap = new MinHeap<>();
            //MinHeap<Integer> heap = new MinHeap<>(items,x);

            while(true) {
                var input = reader.readLine();
                if (input == null) break;
                var f_p = input.split(" ");
                switch (f_p[0]){
                    case "FIN" -> {
                        if(heap.size() == 0)writer.write("Heap is empty"+"\n");
                        else{
                            int output = heap.FindMin();
                            writer.write("FindMin returned "+output+"\n");
                        }
                    }
                    case "EXT" -> {
                        if(heap.size() == 0)writer.write("Heap is empty"+"\n");
                        else{
                            int output = heap.ExtractMin();
                            writer.write("ExtractMin returned "+output+"\n");
                        }
                    }
                    case "INS" -> {
                        heap.Insert(Integer.parseInt(f_p[1]));
                        writer.write("INSERTED " + f_p[1]+"\n");
                    }
                    case "DEC" -> {
                        if(heap.find(Integer.parseInt(f_p[1])) == -1)writer.write(f_p[1]+" is absent in heap"+"\n");
                        else if(Integer.parseInt(f_p[2]) >= Integer.parseInt(f_p[1]))writer.write("New key must be lower than "+f_p[1]+"\n");
                        else {
                            heap.DecreaseKey(Integer.parseInt(f_p[1]),Integer.parseInt(f_p[2]));
                            writer.write(f_p[1]+" decreased to "+f_p[2]+"\n");
                        }
                    }
                    case "INC" -> {
                        if(heap.find(Integer.parseInt(f_p[1])) == -1)writer.write(f_p[1]+" is absent in heap"+"\n");
                        else if(Integer.parseInt(f_p[2]) <= Integer.parseInt(f_p[1]))writer.write("New key must be higher than "+f_p[1]+"\n");
                        else {
                            heap.IncreaseKey(Integer.parseInt(f_p[1]),Integer.parseInt(f_p[2]));
                            writer.write(f_p[1]+" increased to "+f_p[2]+"\n");
                        }
                    }
                    case "PRI" -> writer.write(heap.Print()+"\n");
                    case "DEL" ->{
                        if(heap.find(Integer.parseInt(f_p[1])) == -1)writer.write(f_p[1]+" is absent in heap"+"\n");
                        else{
                            heap.deleteKey(Integer.parseInt(f_p[1]));
                            writer.write(f_p[1]+" is deleted\n");
                        }
                    }
                    case "SORT" ->{
                        Integer[] a = new Integer[f_p.length-1];
                        for(int i=0; i<a.length; i++)a[i] = Integer.parseInt(f_p[i+1]);
                        heap.HeapSort(a);
                        writer.write("Sorting...\n");
                        for (Integer integer : a) writer.write(integer + " ");
                        writer.write("\n");
                    }
                    default -> writer.write("Invalid Operation"+"\n");
                }
            }
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
