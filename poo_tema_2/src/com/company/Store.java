package com.company;

import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

import static com.company.Discount.DiscountType.PERCENTAGE_DISCOUNT;

public class Store {
    private String name = "Magazin";
    private Currency current_currency = new Currency("EUR","€",1.0);
    private ArrayList<Currency> currencies = new ArrayList<>();
    private ArrayList<Product> products = new ArrayList<>();
    private ArrayList<Manufacturer> manufacturers = new ArrayList<>();
    private ArrayList<Discount> discounts = new ArrayList<>();

    private static Store instance = new Store();

    private Store() {
        this.currencies.add(new Currency("EUR","€",1.0));
    }

    public static Store getInstance(){
        return instance;
    }

    public void addProduct(Product e) {
        for(int i = 0; i < products.size(); i++){
            if(products.get(i).getId().equals(e.getId())) {
                return;
                //throw new DuplicateProductException();
            }
        }

        this.products.add(e);


    }

    public void addManufacturer(Manufacturer e)  {
        for(int i = 0; i < manufacturers.size(); i++){
            if(manufacturers.get(i).getName().equals(e.getName()))
                manufacturers.get(i).incCountProducts();
        }

        manufacturers.add(e);
    }

    void changeCurrency(Currency e) throws CurrencyNotFoundException{
        this.current_currency = e;
        for(int i = 0; i < products.size(); i++)
            products.get(i).setPrice(products.get(i).getPrice() * e.getParity());
    }

    void applyDiscount(Discount.DiscountType x,double value) throws NegativePriceException,DiscountNotFoundException{
        int pp = -1;
        for(int i = 0; i < discounts.size(); i++){
            if(discounts.get(i).getValue() == value && discounts.get(i).getDiscountType() == x)
                pp = i;
        }
        if(pp == -1)
            throw new DiscountNotFoundException();
        discounts.get(pp).setAsAppliedNow();
        if(discounts.get(pp).getDiscountType() == PERCENTAGE_DISCOUNT) {

            for (int i = 0; i < products.size(); i++) {
                double new_price = products.get(i).getPrice() - products.get(i).getPrice() * discounts.get(pp).getValue() / 100;
                if(new_price < 0)
                    throw new NegativePriceException();
                products.get(i).setPrice(new_price);
                products.get(i).setDiscount(discounts.get(pp));
            }
        }
        else {
            for(int i = 0; i < products.size(); i++) {
                double new_price = products.get(i).getPrice() - discounts.get(pp).getValue();
                if(new_price < 0)
                    throw new NegativePriceException();
                products.get(i).setPrice(new_price);
                products.get(i).setDiscount(discounts.get(pp));
            }
        }

    }

    ArrayList<Product> getProductsbyManufacturer(Manufacturer e){
        ArrayList<Product> l = new ArrayList<>();
        for(int i = 0; i < products.size(); i++) {
            if(products.get(i).getManufacturer().getName().equals(e.getName()))
                l.add(products.get(i));
        }

        return l;
    }

    ArrayList<Product> getProductsById(String[] ids){
        ArrayList<Product> list = new ArrayList<>();

        for(int i = 1; i < ids.length; i++)
            for(int j = 0; j < products.size(); j++)
                if(products.get(j).getId().equals(ids[i]))
                    list.add(products.get(i));

        return list;

    }

    double calculateCost(ArrayList<Product> x){
        double sum = 0;
        for(int i = 0; i < x.size(); i++){
            sum += x.get(i).getPrice();
        }

        return sum;
    }

    void calculateTotal(String[] ids,FileWriter my_writer) throws IOException {
        ArrayList<Product> x = getProductsById(ids);
        my_writer.write(Double.toString(calculateCost(x)));
        my_writer.write("\n");
    }

    void listCurrencies(FileWriter myWritter) throws IOException {
        for(int i = 0; i < currencies.size(); i++){
            myWritter.write(currencies.get(i).toString());
            myWritter.write("\n");
        }
    }

    public String getName() {
        return name;
    }

    public Currency getCurrency() {
        return current_currency;
    }

    public ArrayList<Product> getProducts() {
        return products;
    }

    public ArrayList<Manufacturer> getManufacturers() {
        return manufacturers;
    }

    public ArrayList<Currency> getCurrencies(){
        return currencies;
    }

    public void setCurrent_currency(String currency) throws CurrencyNotFoundException {
        for(int i = 0; i < currencies.size(); i++){
            if(currencies.get(i).getName().equals(currency)) {
                this.current_currency = currencies.get(i);
                changeCurrency(currencies.get(i));

                return;
            }
        }

        throw new CurrencyNotFoundException();
    }

    public void updateParity(String currency,double parity) throws CurrencyNotFoundException {
        for(int i = 0; i < currencies.size(); i++){
            if(currencies.get(i).getName().equals(currency)) {
                currencies.get(i).setParity(parity);
                return;
            }
        }

        throw new CurrencyNotFoundException();
    }

    public void listProducts(FileWriter my_writer) throws IOException {
        for(int i = 0; i < products.size(); i++) {
            products.get(i).printProduct(current_currency);
            my_writer.write(products.get(i).printProduct(current_currency));
            my_writer.write("\n");
        }

    }

    public void showProduct(String id,FileWriter my_writer) throws IOException {
        for(int i = 0; i < products.size(); i++){
            if(products.get(i).getId().equals(id)){
                my_writer.write(products.get(i).printProduct(current_currency));
            }
        }
    }

    public void listManufacturers(FileWriter my_writer) throws IOException {
        for(int i = 0; i < manufacturers.size(); i++) {
            my_writer.write(manufacturers.get(i).getName());
            my_writer.write("\n");
        }
    }

    public void listProductsByManufacturarer(String manufacturer,FileWriter my_writer) throws IOException {
        for(int i = 0; i < products.size(); i++)
            if(products.get(i).getManufacturer().getName().equals(manufacturer)) {
                my_writer.write(products.get(i).printProduct(current_currency));
                my_writer.write("\n");
            }

    }

    public void listDiscounts(FileWriter my_writer) throws IOException {
        for(int i = 0; i < discounts.size(); i++){
            my_writer.write(discounts.get(i).toString());
            my_writer.write("\n");
        }
    }

    public ArrayList<Discount> getDiscounts() {
        return discounts;
    }
}
