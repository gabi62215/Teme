

public class Traffic  {
    /**
     *Class that describes the possible traffic jams
     */
    private final int cost;
    private final String name;

    public Traffic(int cost,String name) {
        this.name = name;
        this.cost = cost;
    }

    public int getCost() {
        return cost;
    }

    public String getName(){return name;}

}
