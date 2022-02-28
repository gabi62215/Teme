import java.util.Hashtable;
import java.util.List;

// class that contains results from the map task
public class Result {
    Hashtable<Integer, Integer> dict;
    List<String> longest_words;
    String doc_name;

    public Result(Hashtable<Integer, Integer> dict, List<String> longest_words, String doc_name) {
        this.dict = dict;
        this.longest_words = longest_words;
        this.doc_name = doc_name;
    }
}
