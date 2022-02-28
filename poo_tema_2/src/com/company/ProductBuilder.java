package com.company;

public class ProductBuilder implements Builder {
    private Product product;

    public ProductBuilder() {
        product = new Product();
    }


    @Override
    public void setId(java.lang.String id) {
        product.setId(id);
    }

    @Override
    public void setName(java.lang.String name) {
        product.setName(name);
    }

    @Override
    public void setManufacturer(String name) {
        Manufacturer a = new Manufacturer(name);
        product.setManufacturer(a);
    }

    @Override
    public void setPrice(double price) {
        product.setPrice(price);
    }

    @Override
    public void setQuantity(int quantity) {
        product.setQuantity(quantity);
    }

    public Product getProduct() {
        return product;
    }
}
