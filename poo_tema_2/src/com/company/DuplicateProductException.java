package com.company;

public class DuplicateProductException extends Exception {
    public DuplicateProductException() {
        super("same id");
    }
}
