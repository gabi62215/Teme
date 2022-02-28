package com.company;

public class Manufacturer {
    private String name;
    private int countProducts;

    public Manufacturer() {
    }

    public Manufacturer(String name) {
        this.name = name;
        this.countProducts = 0;
    }

    public String getName() {
        return name;
    }

    public int getCountProducts() {
        return countProducts;
    }

    public void incCountProducts() {
        this.countProducts++;
    }

}
