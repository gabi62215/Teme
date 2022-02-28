import java.io.*;
import java.util.*;
import java.util.concurrent.*;

public class Tema2 {
    public static void main(String[] args) {
        if (args.length < 3) {
            System.err.println("Usage: Tema2 <workers> <in_file> <out_file>");
            return;
        }

        ExecutorService executor = Executors.newFixedThreadPool(Integer.parseInt(args[0]));
        Reader reader = new Reader(args[1]);
        List<String> files = reader.read();
        List<MapTask> map_tasks = new ArrayList<>();

        // split each file in multiple map tasks,by setting the offset and the dim
        for(int i = 0; i < files.size(); i++) {
            long size = new File(files.get(i)).length();
            for(int offset = 0; offset < size; offset += reader.dim) {
                map_tasks.add(new MapTask(files.get(i),offset, reader.dim));
            }
        }

        // add tasks to the pool
        List<Future<Result>> resultList = null;
        try {
            resultList = executor.invokeAll(map_tasks);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // create hashmap
        // the keys are the names of the documents
        // the hashmap contains a list of results(from the map task) grouped by the document name
        Hashtable<String, List<Result>> map_results = new Hashtable<>();
        for(int i = 0; i < resultList.size(); i++) {
            Future<Result> future = resultList.get(i);
            try {
                Result result = future.get();
                // if key exists add result to the list
                if(map_results.containsKey(result.doc_name)) {
                    map_results.get(result.doc_name).add(result);
                }
                // if key doesn't exist initialize list with the key
                else {
                    map_results.put(result.doc_name,new ArrayList<>());
                    map_results.get(result.doc_name).add(result);
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            } catch (ExecutionException e) {
                e.printStackTrace();
            }
        }

        // create reduce tasks for each file
        // pass list of results by file name
        List<ReduceTask> reduce_tasks = new ArrayList<>();
        for(String key : map_results.keySet()) {
            reduce_tasks.add(new ReduceTask(map_results.get(key),key));
        }

        // add reduce tasks to the pool
        List<Future<ReduceResult>> reduce_results = null;
        try {
            reduce_results = executor.invokeAll(reduce_tasks);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        executor.shutdown();

        // create list of final results
        List<ReduceResult> final_results = new ArrayList<>();
        for(int i = 0; i < reduce_results.size(); i++) {
            Future<ReduceResult> future = reduce_results.get(i);
            try {
                ReduceResult result = future.get();
                final_results.add(result);
            } catch (InterruptedException e) {
                e.printStackTrace();
            } catch (ExecutionException e) {
                e.printStackTrace();
            }
        }

        // pass above list to the writer so it can write to the specified file
        Writer writer = new Writer(final_results,args[2]);
        writer.write();
    }
}
