package com.company;

public class CurrencyNotFoundException extends Exception {
    public CurrencyNotFoundException() {
        super("can't find currency");
    }
}
