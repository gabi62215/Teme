

import java.util.*;

public class Dijkstra {
    /**
     * Class to implement Dijksta's algorithm with priority queue
     * dist is dictionary that holds cost from starting node to each other node
     * settled stores the visited nodes
     * graph is the actual map
     * algorithm taken and modified from geeksforgeeks.com
     */
    Map<String, Integer> dist;
    Map<String, String> passed_nodes;
    private Set<String> settled;
    private PriorityQueue<Street> pq;
    private int V; // Number of vertices
    Map<String, ArrayList<Street>> graph;

    public Dijkstra(int V) {
        passed_nodes = new HashMap<>();
        this.V = V;
        dist = new HashMap<>();
        settled = new HashSet<String>();
        pq = new PriorityQueue<Street>(V, Street::compareTo);
    }

    // Function for Dijkstra's Algorithm
    public void dijkstra(Map<String, ArrayList<Street>> graph, String src,Vehicle e) {
        this.graph = graph;

        for (String key : graph.keySet()) {
            dist.put(key, Integer.MAX_VALUE);
            passed_nodes.put(key, new String());
        }

        // Add source node to the priority queue
        pq.add(new Street(src, 0, -1));

        // Distance to the source is 0
        dist.put(src, 0);
        while (settled.size() != V) {

            // remove the minimum distance node
            // from the priority queue
            String u = null;
            if (!pq.isEmpty())
                u = pq.remove().getDestination();


            // adding the node whose distance is
            // finalized

            settled.add(u);

            if (u == null)
                return;
            e_Neighbours(u,e);

        }
    }

    // Function to process all the neighbours
    // of the passed node
    private void e_Neighbours(String u,Vehicle e) {
        int edgeDistance = -2;
        int newDistance = -1;

        // All the neighbors of v
        for (int i = 0; i < graph.get(u).size(); i++) {
            Street v = graph.get(u).get(i);


            // If current node hasn't already been processed
            if (!settled.contains(v.getDestination())) {

                edgeDistance = e.calculateCost(v);//add vehicle parameter and calculate cost for each street
                if(edgeDistance != -1) {//if the size is too big skip
                    newDistance = dist.get(u) + edgeDistance;

                    // If new distance is cheaper in cost
                    if (newDistance < dist.get(v.getDestination())) {
                        dist.put(v.getDestination(), newDistance);
                        passed_nodes.put(v.getDestination(), u);
                    }
                }

                // Add the current node to the queue
                pq.add(new Street(v.getDestination(), dist.get(v.getDestination()), -1));
            }


        }
    }
}
