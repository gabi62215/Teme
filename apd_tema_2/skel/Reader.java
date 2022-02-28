import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Reader {
    File file;
    Scanner reader;
    int dim;

    public Reader(String file_name) {
        file = new File(file_name);
        try {
            reader = new Scanner(file);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    // read from file and return list of each document name
    // also get # of bytes for the map tasks
    public List<String> read() {
        List<String> files = new ArrayList<>();
        dim = Integer.parseInt(reader.nextLine());
        int nr_of_files = Integer.parseInt((reader.nextLine()));

        while(reader.hasNextLine()) {
            // add "../" in order to properly read the files
            String data = "../" + reader.nextLine();
            files.add(data);
        }

        return files;
    }
}
