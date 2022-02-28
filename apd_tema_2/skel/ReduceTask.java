import java.util.ArrayList;
import java.util.Hashtable;
import java.util.List;
import java.util.concurrent.Callable;

public class ReduceTask implements Callable<ReduceResult> {
    List<Result> results;
    String doc_name;
    Hashtable<Integer, Integer> dict;
    List<String> longest_words;

    public ReduceTask(List<Result> results, String doc_name) {
        this.results = results;
        this.doc_name = doc_name;
        dict = new Hashtable<>();
        longest_words = new ArrayList<>();
    }

    // splits path by "/" in order to get the document name
    public void strip_doc_name() {
        String []parts = doc_name.split("/");
        doc_name = parts[parts.length - 1];
    }

    // function to get the nth number of the fibonacci sequence
    public int fibo(int n) {
        int []f = new int[n + 2];

        f[0] = 0;
        f[1] = 1;

        for(int i = 2; i <= n; i++) {
            f[i] = f[i - 1] + f[i - 2];
        }

        return f[n];
    }

    // function that computes the rank by the formula
    public double get_rank() {
        double rank = 0;
        int i = 0;
        for(Integer key : dict.keySet()) {
            int fib = fibo(key + 1);
            int s = fib * dict.get(key);
            rank += s;
            i += dict.get(key);
        }
        rank = rank / i;
        return rank;
    }

    @Override
    public ReduceResult call() throws Exception {
        // iterate through each result of the map tasks
        for(Result result : results) {
            // "merge" hashmaps of each task result in order to get final hashmap of the document
            for(Integer key : result.dict.keySet()) {
                // key is the number of letters
                // if it exists then we add it the current_dict[key] value
                if(dict.containsKey(key)) {
                    dict.put(key,dict.get(key) + result.dict.get(key));
                }
                // if it doesn't exist we simply put the first value
                else {
                    dict.put(key,result.dict.get(key));
                }
            }

            // get the longest word and add all words of that length to a list
            for(String word : result.longest_words) {
                if(longest_words.size() != 0)
                    if(longest_words.get(0).length() < word.length())
                        longest_words.clear();
                if(!longest_words.contains(word))
                    longest_words.add(word);
            }
        }

        strip_doc_name();

        // return result of the task
        return new ReduceResult(doc_name,get_rank(),
                longest_words.get(0).length(),
                dict.get(longest_words.get(0).length()));
    }
}
