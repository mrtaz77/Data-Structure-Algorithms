public class Customer {
    private int arrival;
    private int duration;

    public Customer(int arrival , int duration) {
        this.arrival = arrival;
        this.duration = duration;
    }

    public int arrival() {
        return arrival;
    }

    public Customer setArrival(int arrival) {
        this.arrival = arrival;
        return this;
    }

    public int duration() {
        return duration;
    }

    public void setDuration(int duration) {
        this.duration = duration;
    }

    @Override
    public String toString(){
        return "("+arrival+" "+duration+")";
    }


}
