import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.*;
import java.util.concurrent.Callable;

public class MapTask implements Callable<Result> {
    String doc_name;
    int offset;
    int dim;
    Integer max;
    String max_s;
    Integer letters;
    String current_word;
    Hashtable<Integer, Integer> dict;
    List<String> longest_words;

    public MapTask(String doc_name, int offset, int dim) {
        this.doc_name = doc_name;
        this.offset = offset;
        this.dim = dim;
        dict = new Hashtable<>();
        longest_words = new ArrayList<>();
        letters = 0;
        max = 0;
        max_s = "";
        current_word = "";
    }

    public boolean isLetterOrNumber(byte x) {
        char c = (char)x;
        return (c >= '0' && c <= '9') ||
                (c >= 'a' && c <= 'z') ||
                (c >= 'A' && c <= 'Z');
    }

    // checks if the current word is longer than the current max one
    // if it is equal to the current max one,add it to the list
    // if it is strictly longer,then clear list and then add it
    public void getMax() {
        if(letters > max) {
            max = letters;
            max_s = current_word;
        }

        if(letters.equals(max) && !longest_words.contains(current_word)) {
            if(longest_words.size() != 0)
                if(longest_words.get(0).length() < max)
                    longest_words.clear();
            longest_words.add(current_word);
        }
    }

    // if the current character is a separator and the # of letters is not 0,
    // then we have a new word and we must increment the # of words with that length
    // if the current character is not a separator,then we are in a word,so we increment
    // the # of letters and add the character to the current word
    public void incrementDict(byte character) {
        if (isLetterOrNumber(character)) {
            letters++;
            current_word = current_word + (char)character;
        }
        else {
            if(dict.containsKey(letters) && letters != 0) {
                dict.put(letters, dict.get(letters) + 1);
                getMax();
            }
            else if(letters != 0){
                dict.put(letters,1);
                getMax();
            }
            letters = 0;
            current_word = "";
        }
    }

    @Override
    public Result call() {
        // open file
        RandomAccessFile file = null;
        try {
            file = new RandomAccessFile(doc_name, "r");
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        // go to offset - 1 to find out if we are in the middle of a word
        if(offset != 0) {
            try {
                file.seek(offset - 1);
            } catch (IOException e) {
                System.out.println("Eroare la citire");
            }
        }

        // reads character
        byte character = 0;
        try {
            character = file.readByte();
        } catch (IOException e) {
            e.printStackTrace();
        }

        // if the character is a letter or a number then we are in the middle of a word
        // skip the said word and increment i
        int i = -1;
        boolean in_word = false;
        boolean end_of_file = false;
        while (isLetterOrNumber(character) &&
                offset != 0) {
            in_word = true;
            try {
                character = file.readByte();
                i++;
            } catch (IOException e) {
                end_of_file = true;
                break;
            }
        }

        // if we are not in the middle of a word then get to the next byte
        if(!in_word && offset != 0) {
            try {
                character = file.readByte();
                i++;
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        // if it is the beginning of the file set i to 0
        if(offset == 0)
            i = 0;

        // count # of letters/digits for each word and get list of the longest words
        if(!end_of_file) {
            while (true) {

                incrementDict(character);

                try {
                    character = file.readByte();
                    i++;
                } catch (IOException e) {
                    end_of_file = true;
                    break;
                }
                if ((!isLetterOrNumber(character) && i + 1 >= dim)) {
                    break;
                }
            }
        }

        // if the end of file is reached also add the last word
        if(end_of_file) {
            // change character value to " " so that incrementDict can count a new word
            character = 32;
        }
        incrementDict(character);

        return new Result(dict,longest_words,doc_name);
    }
}
