
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.List;

public class Main {
    /**
     * reads map.in and writes in map.out
     */

    public static void main(String[] args) {
        List l = ReadFile.readFileInList("map.in");

        Graph map = new Graph();
        int number_of_streets = map.readGraph(l);

        try {
            PrintWriter my_file = new PrintWriter("map.out");
            String[] command = ((String) l.get(0)).split(" ", 0);
            /*
            initialize i to skip de reading of the graph

            */
            int cost;
            for (int i = number_of_streets + 1; i < l.size(); i++) {
                //splits each line by space to get the command and parameters
                command = ((String) l.get(i)).split(" ", 0);
                if (command[0].equals("drive")) {
                    Dijkstra dpq = null;
                    dpq = map.drive(command[1], command[2], command[3]);
                    WriteFile.write(dpq,command[2],command[3],my_file);

                } else {
                    cost = Integer.parseInt(command[3]);
                    map.addRestriction(command[0], command[1], command[2], cost);
                }

            }

            my_file.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }


    }
}
