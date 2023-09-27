import java.io.*;

public class Main {
    private static final String INPUT_FILE = "list_input.txt";
    private static final String OUTPUT_FILE = "list_output.txt";
    public static void main(String[] args) {
        int k,x,q,f,p;
        try (BufferedReader reader = new BufferedReader(new FileReader(INPUT_FILE))) {
            BufferedWriter writer = new BufferedWriter(new FileWriter(OUTPUT_FILE));

            String[] k_x = reader.readLine().split(" ");
            k = Integer.parseInt(k_x[0]);
            x = Integer.parseInt(k_x[1]);

            Integer[] items = new Integer[k];
            String[] input = reader.readLine().split(" ");
            for (int i = 0; i < items.length; i++) items[i] = Integer.parseInt(input[i]);

            LL<Integer> myList = new LL<>(k,x,items);
            //Arr<Integer> myList = new Arr<>(k, x, items);

            writer.write(myList + "\n");

            q = Integer.parseInt(reader.readLine());

            while (q > 0) {
                String[] f_p = reader.readLine().split(" ");
                f = Integer.parseInt(f_p[0]);
                p = Integer.parseInt(f_p[1]);
                switch (f) {
                    case 1 :
                        writer.write(myList + "\n" + myList.size() + "\n");
                    break;
                    case 2 : {
                        try {
                            myList.push(p);
                        } catch (Exception e) {
                            System.out.println(e);
                        }
                        writer.write(myList + "\n-1\n");
                    }
                    break;
                    case 3 : {
                        try {
                            myList.pushBack(p);
                        } catch (Exception e) {
                            System.out.println(e);
                        }
                        writer.write(myList + "\n-1\n");
                    }
                    break;
                    case 4 : {
                        if(myList.size() == 0)writer.write(myList + "\n-1\n");
                        else{
                            try {
                                int output = myList.erase();
                                writer.write(myList + "\n" + output + "\n");
                            } catch (Exception e) {
                                System.out.println(e);
                            }
                        }
                    }
                    break;
                    case 5 : {
                        myList.setToBegin();
                        writer.write(myList + "\n-1\n");
                    }
                    break;
                    case 6 : {
                        myList.setToEnd();
                        writer.write(myList + "\n-1\n");
                    }
                    break;
                    case 7 : {
                        myList.prev();
                        writer.write(myList + "\n-1\n");
                    }
                    break;
                    case 8 : {
                        myList.next();
                        writer.write(myList + "\n-1\n");
                    }
                    break;
                    case 9 :
                        writer.write(myList + "\n" + myList.currPos() + "\n");
                    break;
                    case 10 : {
                        if(p>=0 && p<myList.size()){
                            try {
                                myList.setToPos(p);
                            } catch (Exception e) {
                                System.out.println(e);
                            }
                        }
                        writer.write(myList + "\n-1\n");
                    }
                    break;
                    case 11 : {
                        if(myList.size() != 0){
                            try {
                                writer.write(myList + "\n" + myList.getValue() + "\n");
                            } catch (Exception e) {
                                System.out.println(e);
                            }
                        }
                        else writer.write(myList + "\n-1\n");
                    }
                    break;
                    case 12 : {
                        try {
                            writer.write(myList + "\n" + myList.find(p) + "\n");
                        } catch (Exception e) {
                            System.out.println(e);
                        }
                    }
                    break;
                    case 13 : {
                        myList.clear();
                        writer.write(myList + "\n-1\n");
                    }
                    break;
                    default :
                        System.out.println("Invalid Command");
                    break;
                }
                q--;
            }
            writer.close();
        } catch (IOException e) {
            System.out.println(e + " while input");
        }
    }
}
