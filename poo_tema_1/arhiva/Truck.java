

public class Truck extends Vehicle {
    /**
     *Truck class with specified values for size and cost
     */
    private final int size;
    private final int cost;

    public Truck(String type) {
        super(type);
        this.size = 3;
        this.cost = 6;
    }

    public int getSize() {
        return size;
    }

    public int getCost() {
        return cost;
    }

    /**
     * @param s street to calculate cost for truck
     * @return  the cost or -1 if the size of the vehicle is bigger
     */
    @Override
    public int calculateCost(Street s) {
        //checks if the size of the vehicle is bigger than the size of the street,return -1 if so
        if(size > s.getSize())
            return -1;
        int cost = this.cost * s.getCost();
        //adds all traffic jams from the street to the cost
        for(int i = 0; i < s.getTraffic_jams().size(); i++){
            cost += s.getTraffic_jams().get(i).getCost();
        }

        return cost;

    }
}
