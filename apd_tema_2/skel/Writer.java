import java.io.FileWriter;
import java.io.IOException;
import java.util.Collections;
import java.util.List;

public class Writer {
    List<ReduceResult> results;
    String file_name;

    public Writer(List<ReduceResult> results, String  file_name) {
        this.results = results;
        this. file_name =  file_name;
    }

    // write the output to the specified file
    public void write() {
        // create file
        FileWriter file = null;
        try {
            file = new FileWriter(file_name);
        } catch (IOException e) {
            e.printStackTrace();
        }

        // sort and write the results
        Collections.sort(results);
        for(ReduceResult result : results) {
            String rank = String.format("%.2f",result.rank);
            try {
                file.write(result.doc_name + "," + rank + "," + result.max_len + "," + result.max_n + "\n");
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        try {
            file.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
