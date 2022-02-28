// class that contains results from the reduce task
public class ReduceResult implements Comparable<ReduceResult> {
    String doc_name;
    double rank;
    int max_len;
    int max_n;

    public ReduceResult(String doc_name, double rank, int max_len, int max_n) {
        this.doc_name = doc_name;
        this.rank = rank;
        this.max_len = max_len;
        this.max_n = max_n;
    }

    // for sorting
    // it sorts by rank
    @Override
    public int compareTo(ReduceResult o) {
        if(rank > o.rank)
            return -1;
        if(rank < o.rank)
            return 1;

        return 0;
    }
}
