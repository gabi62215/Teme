package com.company;

public class Currency {
    private String name;
    private String symbol;
    private double parity;

    public Currency(String name, String symbol, double parity) {
        this.name = name;
        this.symbol = symbol;
        this.parity = parity;
    }

    public Currency() {
    }

    public String getName() {
        return name;
    }

    public String getSymbol() {
        return symbol;
    }

    public double getParity() {
        return parity;
    }

    public void setParity(double parity) {
        this.parity = parity;
    }

    public String toString(){
        return this.name + " " + this.getParity();
    }


}
