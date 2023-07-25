import java.io.*;
public class AVLMain {
    private static final String INPUT_FILE = "input.txt";
    private static final String OUTPUT_FILE = "output.txt";

    public static void main(String[] args) {
        try(BufferedReader reader = new BufferedReader(new FileReader(INPUT_FILE))){
            BufferedWriter writer = new BufferedWriter(new FileWriter(OUTPUT_FILE));

            AVL<Integer> tree = new AVL<>();
            AVLNode<Integer> root = null;

            while(true){
                var input = reader.readLine();
                if(input == null)break;
                var f_p = input.split(" ");
                switch (f_p[0]) {
                    case "I": {
                        root = tree.insert(root, Integer.parseInt(f_p[1]));
                        writer.write(tree.show(root) + "\n");
                        break;
                    }
                    case "D": {
                        root = tree.delete(root, Integer.parseInt(f_p[1]));
                        writer.write(tree.show(root) + "\n");
                        break;
                    }
                    case "T":
                        writer.write(tree.inOrder(root) + "\n");
                        break;
                    case "F":
                        if(tree.find(root, Integer.parseInt(f_p[1])))writer.write( "found\n");
                        else writer.write( "not found\n");
                        break;
                }
            }
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

