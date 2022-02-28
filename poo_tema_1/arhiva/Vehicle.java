

public abstract class Vehicle {
    /**
     *Class that is the father of specified vehicles(Bike,Car,Truck,Motorcycle)
     */
    private String type;

    public Vehicle(String type) {
        this.type = type;
    }

    public Vehicle(){

    }

    public abstract int calculateCost(Street s);
}
