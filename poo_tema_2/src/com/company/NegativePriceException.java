package com.company;

public class NegativePriceException extends Exception{
    public NegativePriceException(){
        super("Negative price");
    }
}
