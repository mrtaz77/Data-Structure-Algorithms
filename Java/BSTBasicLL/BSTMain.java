package BSTBasicLL;

import java.io.*;

public class BSTMain {
    private static final String INPUT_FILE = "input.txt";
    private static final String OUTPUT_FILE = "output.txt";

    public static void main(String[] args) {
        try(BufferedReader reader = new BufferedReader(new FileReader(INPUT_FILE))){
            BufferedWriter writer = new BufferedWriter(new FileWriter(OUTPUT_FILE));

            BST<Integer> tree = new BST<>();
            BSTNode<Integer> root = null;

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
                        switch (f_p[1]) {
                            case "In" :
                                writer.write(tree.inOrder(root) + "\n");
                                break;
                            case "Pre" :
                                writer.write(tree.preOrder(root) + "\n");
                                break;
                            case "Post" :
                                writer.write(tree.postOrder(root) + "\n");
                                break;
                            case "Level":
                                writer.write(tree.levelOrder(root) + "\n");
                                break;
                            default :
                                writer.write("Invalid Operation" + "\n");
                                break;
                        }
                        break;
                    case "F":
                        if(tree.find(root, Integer.parseInt(f_p[1])))writer.write( "True\n");
                        else writer.write( "False\n");
                        break;
                    case "MaxH":
                        writer.write(tree.maxHeight(root)+"\n");
                        break;
                    case "H":
                        if(tree.find(root, Integer.parseInt(f_p[1])))writer.write(tree.height(root, Integer.parseInt(f_p[1]))+"\n");
                        else writer.write("Invalid Operation\n");
                        break;
                    case "Print":
                        writer.write(tree.print2D(root,3,10)+"\n");
                        break;
                    case "Full":
                        writer.write(tree.isFull(root)+"\n");
                        break;
                    case "Complete":
                        writer.write(tree.isComplete(root)+"\n");
                        break;
                    case "InS":
                        if(!tree.find(root, Integer.parseInt(f_p[1])))writer.write("Invalid Operation\n");
                        else writer.write(tree.inSuccessor(root,Integer.parseInt(f_p[1]))+"\n");
                        break;
                    case "InP":
                        if(!tree.find(root, Integer.parseInt(f_p[1])))writer.write("Invalid Operation\n");
                        else writer.write(tree.inPredecessor(root,Integer.parseInt(f_p[1]))+"\n");
                        break;
                }
            }
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
