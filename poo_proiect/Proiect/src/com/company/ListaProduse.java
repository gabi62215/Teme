package com.company;

import java.util.LinkedList;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 * implementarea unei liste care stegre si adauga elemente in functie de niste conditii
 * asemanatoare cu laboratorul 11
 */

public class ListaProduse {
    static final int CAPACITATE = 20;
    private LinkedList<Produs> list = new LinkedList<>();
    Lock lock = new ReentrantLock();

    Condition neVid = lock.newCondition();
    Condition nePlin = lock.newCondition();

    public ListaProduse() {
    }

    public LinkedList<Produs> getList() {
        return list;
    }

    void adauga(Produs x){
        lock.lock();
        try{
            while(list.size() == CAPACITATE) {
                nePlin.await();

            }
            list.add(x);
            neVid.signal();
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
        finally {
            lock.unlock();
        }
    }

    void sterge(int poz){
        lock.lock();
        try{
            while(list.isEmpty())
                neVid.await();

            list.remove(poz);
            nePlin.signal();
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
        finally {
            lock.unlock();
        }

    }

    void stergeDupaId(int id){
        for(int i = 0; i < list.size(); i++){
            if(list.get(i).getId() == id) {
                sterge(i);
                break;
            }
        }
    }
}
