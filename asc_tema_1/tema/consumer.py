"""
This module represents the Consumer.

Computer Systems Architecture Course
Assignment 1
March 2021
"""

from threading import Thread
import time
import logging


class Consumer(Thread):
    """
    Class that represents a consumer.
    """

    def __init__(self, carts, marketplace, retry_wait_time, **kwargs):
        """
        Constructor.

        :type carts: List
        :param carts: a list of add and remove operations

        :type marketplace: Marketplace
        :param marketplace: a reference to the marketplace

        :type retry_wait_time: Time
        :param retry_wait_time: the number of seconds that a producer must wait
        until the Marketplace becomes available

        :type kwargs:
        :param kwargs: other arguments that are passed to the Thread's __init__()
        """
        Thread.__init__(self)
        self.name = kwargs["name"]
        self.carts = carts
        self.marketplace = marketplace
        self.retry_wait_time = retry_wait_time

    def run(self):
        # iterate through carts
        for cart in self.carts:
            my_id = self.marketplace.new_cart()

            # iterate through operations in cart
            for op in cart:

                # either remove or add quantity elements to/from cart
                if op["type"] == "add":
                    for i in range(op["quantity"]):
                        while True:
                            if self.marketplace.add_to_cart(my_id, op["product"]):
                                break
                            time.sleep(self.retry_wait_time)
                elif op["type"] == "remove":
                    for i in range(op["quantity"]):
                        self.marketplace.remove_from_cart(my_id, op["product"])

            # get list of products and print a message
            products = self.marketplace.place_order(my_id)
            for product in products:
                print("{0} bought {1}".format(self.name, product))
