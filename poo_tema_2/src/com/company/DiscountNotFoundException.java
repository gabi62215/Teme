package com.company;

public class DiscountNotFoundException extends Exception {
    public DiscountNotFoundException(){
        super("can't find discount");
    }
}
