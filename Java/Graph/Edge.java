public class Edge implements Comparable<Edge>{
    private int start;
    private int finish;
    private double weight;
    public Edge(int start, int finish, double weight){
        this.start = start;
        this.finish = finish;
        this.weight = weight;
    }

    public void setWeight(double weight) {
        this.weight = weight;
    }

    public double getWeight() {
        return weight;
    }

    public int getStart() {
        return start;
    }

    public int getFinish() {
        return finish;
    }

    @Override
    public String toString() {
        return "("+start+","+finish+")"+"("+weight+")";
    }

    @Override
    public int compareTo(Edge e) {
        return Double.compare(this.getWeight(),e.getWeight());
    }
}
