package com.company;

import java.time.LocalDateTime;

public class Discount {
    enum DiscountType{
        PERCENTAGE_DISCOUNT,
        FIXED_DISCOUNT
    }

    private String name;
    private DiscountType discountType;
    private double value;
    LocalDateTime lastDateApplied;

    public Discount(double value,DiscountType x,String name) {
        this.lastDateApplied = null;
        this.value = value;
        this.discountType = x;
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public DiscountType getDiscountType() {
        return discountType;
    }

    public double getValue() {
        return value;
    }

    public LocalDateTime getLastDateApplied() {
        return lastDateApplied;
    }

    void setAsAppliedNow(){
        this.lastDateApplied = LocalDateTime.now();
    }

    public String toString(){
        if(discountType == DiscountType.PERCENTAGE_DISCOUNT)
            return "PERCENTAGE_DISCOUNT" + " " + value + " " + name + " " + lastDateApplied;
        else
            return "FIXED_DISCOUNT" + " " + value + " " + name + " " + lastDateApplied;
    }
}
