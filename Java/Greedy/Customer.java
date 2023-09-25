public class Customer implements Comparable<Customer> {
    private int arrival;
    private int departure;

    public Customer(int arrival, int departure) {
        this.arrival = arrival;
        this.departure = departure;
    }

    public long arrival() {
        return arrival;
    }

    public Customer setArrival(int arrival) {
        this.arrival = arrival;
        return this;
    }

    public long departure() {
        return departure;
    }

    public Customer setDeparture(int departure) {
        this.departure = departure;
        return this;
    }


    @Override
    public int compareTo(Customer o) {
        if(this.departure != o.departure)return this.departure - o.departure;
        else return this.arrival - o.arrival;
    }

    @Override
    public String toString() {
        return "(" + arrival + "," + departure + ")";
    }
}
