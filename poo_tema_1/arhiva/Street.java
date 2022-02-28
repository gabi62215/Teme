

import java.util.ArrayList;
import java.util.Comparator;


public class Street implements Comparable {
    /**
     * Class to describe a street
     * traffic_jams is a list of Traffic instances that are part of the street and change its cost
     */
    private String destination;
    private int cost;
    private int size;
    private ArrayList<Traffic> traffic_jams;

    public Street(String destination, int cost, int size) {
        this.destination = destination;
        this.cost = cost;
        this.size = size;
        this.traffic_jams = new ArrayList<>();
    }

    public Street() {
    }

    public String getDestination() {
        return destination;
    }

    public int getCost() {
        return cost;
    }

    public int getSize() {
        return size;
    }

    public ArrayList<Traffic> getTraffic_jams() {
        return traffic_jams;
    }

    /**
     * Function to check if graph is read corectly
     */
    public void printStreet() {
        System.out.print(destination + " costul:" + cost);
        for (int i = 0; i < traffic_jams.size(); i++) {
            System.out.print(" " + traffic_jams.get(i).getName() + " " + traffic_jams.get(i).getCost());
        }
        System.out.println();
    }


    /**
     * compare function for priority queue
     *
     * @param o
     * @return
     */
    @Override
    public int compareTo(Object o) {
        return getCost() - ((Street) o).getCost();
    }
}
