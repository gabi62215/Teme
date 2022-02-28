

import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Graph {
    /**
     *Dictionary works as an adjacency list for the graph
     */
    private Map<String, ArrayList<Street>> graph;
    private int number_of_nodes;

    public Graph(){
        graph = new HashMap<>();
        number_of_nodes = 0;
    }



    public Map<String, ArrayList<Street>> getGraph() {
        return graph;
    }
    /**
     *Adds a new node to the graph
     */
    public void addNode(String node){

        graph.put(node, new ArrayList<>());
        number_of_nodes++;
    }
    /**
    *Adds both nodes if they don't already exist and add street to the list of streets
     */

    public void addStreet(String start,String end,int cost,int size){
        if(!graph.containsKey(start)){
            addNode(start);
            number_of_nodes++;
        }


        if(!graph.containsKey(end)) {
            addNode(end);
            number_of_nodes++;
        }
        Street street = new Street(end,cost,size);

        graph.get(start).add(street);
    }



    public int getNumber_of_nodes(){return number_of_nodes;}

    /**
    *Searches for the street with the given start and end and adds a traffic instance to the list
     */
    public void addRestriction(String type,String start,String end,int cost){
        Traffic restriction = new Traffic(cost,type);

        for(int i = 0; i < graph.get(start).size(); i++){
            if(end.equals(graph.get(start).get(i).getDestination()))
                graph.get(start).get(i).getTraffic_jams().add(restriction);
        }
    }

    /**
     *
     * @param l list of lines from the map.in file
     * @return number of streets
     * splits each line by " " and reads nodes,cost and size for the street
     */
    public int readGraph(List l){
        String[] command = ((String)l.get(0)).split(" ",0);
        int number_of_streets = Integer.parseInt(command[0]);//turn first read number of streets in an integer
        int j;
        for(j = 1; j <= number_of_streets; j++){
            command = ((String)l.get(j)).split(" ",0);
            int cost = Integer.parseInt(command[2]);
            int size = Integer.parseInt(command[3]);
            addStreet(command[0],command[1],cost,size);
        }

        //returns number of streets
        return number_of_streets;
    }

    /**
     *
     * @param vehicle that runs on the map
     * @param start starting point
     * @param end destination
     */
    public Dijkstra drive(String vehicle, String start, String end){
        Vehicle e = null;
        if(vehicle.equals("b")){
            e = new Bike(vehicle);
        }
        if(vehicle.equals("a")){
            e = new Car(vehicle);
        }
        if(vehicle.equals("m")){
            e = new Motorcycle(vehicle);
        }
        if(vehicle.equals("c")){
            e = new Truck(vehicle);
        }

        Dijkstra dpq = new Dijkstra(this.number_of_nodes);
        dpq.dijkstra(this.graph,start,e);
        return dpq;


    }

}
