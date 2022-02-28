



import java.io.PrintWriter;
import java.util.Stack;

public class WriteFile {
    /**
     *
     * @param dpq information for each node and its cost from the source node
     * @param source starting point
     * @param destination end point
     * @param my_file file to write in
     */
    public static void write(Dijkstra dpq, String source, String destination, PrintWriter my_file) {

        //if the cost is MAX_VALUE then the vehicle can't get from source to destination
        if (!(dpq.dist.get(destination) == Integer.MAX_VALUE)) {
            Stack<String> drum = new Stack<>();
            String str = destination;
            while (!str.equals(source)) {
                str = dpq.passed_nodes.get(str);
                drum.push(str);
            }

            while (!drum.empty())
                my_file.write(drum.pop() + " ");

            my_file.write(destination + " " + dpq.dist.get(destination));
            my_file.write("\n");
        } else {
            my_file.write(source + " " + destination + " null");
            my_file.write("\n");
        }


    }


}
