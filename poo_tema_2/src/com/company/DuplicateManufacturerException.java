package com.company;

public class DuplicateManufacturerException extends Exception {
    public DuplicateManufacturerException() {
        super("same manufacturer");
    }
}
