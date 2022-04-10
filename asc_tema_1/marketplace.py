"""
This module represents the Marketplace.

Computer Systems Architecture Course
Assignment 1
March 2021
"""

import logging
from logging.handlers import RotatingFileHandler
import time
from threading import Lock

logging.basicConfig(
    handlers=[RotatingFileHandler('./my_log.log', maxBytes=100000, backupCount=10)],
    level=logging.DEBUG,
    format="[%(asctime)s] %(levelname)s %(message)s",
    datefmt='%Y-%m-%dT%H:%M:%S')
logging.Formatter.converter = time.gmtime

class Cart:

    def __init__(self):
        self.items = []

    # add product and producer id
    def add(self, item, id_prod):
        self.items.append((item, id_prod))

    # return product and producer id after removing them
    def remove(self, item):
        for x in self.items:
            if x[0] == item:
                aux = x
                self.items.remove(x)
                return aux

    # return list of products
    def buy(self):
        aux = []

        for x in self.items:
            aux.append(x[0])

        self.items.clear()
        return aux


class Buffer:

    def __init__(self, size):
        self.size = size
        self.list = []

    # tries to add product to list,fails if the buffer is full
    def add(self, item):

        if self.size == len(self.list):
            return False

        self.list.append(item)
        return True

    # tries to remove product,if it exists
    def remove(self, item):

        if item in self.list:
            self.list.remove(item)
            return True
        else:
            return False



class Marketplace:
    """
    Class that represents the Marketplace. It's the central part of the implementation.
    The producers and consumers use its methods concurrently.
    """

    def __init__(self, queue_size_per_producer):
        """
        Constructor

        :type queue_size_per_producer: Int
        :param queue_size_per_producer: the maximum size of a queue associated with each producer
        """
        self.queue_size_per_producer = queue_size_per_producer
        self.buffers = {}

        self.available_id_prod = 0
        self.mutex_prod = Lock()

        self.available_id_cart = 0
        self.mutex_cart = Lock()

        self.carts = {}

        self.logger = logging.getLogger('logger')

        self.logger.info("ceva")

    def register_producer(self):
        """
        Returns an id for the producer that calls this.
        """

        # get id by incrementing current producer id
        with self.mutex_prod:
            self.buffers[self.available_id_prod] = Buffer(
                self.queue_size_per_producer)

            self.available_id_prod = self.available_id_prod + 1
            return self.available_id_prod - 1

        self.logger.info("ceva")

    def publish(self, producer_id, product):
        """
        Adds the product provided by the producer to the marketplace

        :type producer_id: String
        :param producer_id: producer id

        :type product: Product
        :param product: the Product that will be published in the Marketplace

        :returns True or False. If the caller receives False, it should wait and then try again.
        """
        return self.buffers[producer_id].add(product)

    def new_cart(self):
        """
        Creates a new cart for the consumer

        :returns an int representing the cart_id
        """

        # get id by incrementing current cart id
        with self.mutex_cart:
            self.carts[self.available_id_cart] = Cart()

            self.available_id_cart = self.available_id_cart + 1
            return self.available_id_cart - 1

    def add_to_cart(self, cart_id, product):
        """
        Adds a product to the given cart. The method returns

        :type cart_id: Int
        :param cart_id: id cart

        :type product: Product
        :param product: the product to add to cart

        :returns True or False. If the caller receives False, it should wait and then try again
        """

        # search for product in each producer buffer
        # if it is found add it to cart and return True,otherwise return False
        # alse save producer id in case the product will be removed
        for key in self.buffers:
            if self.buffers[key].remove(product):
                self.carts[cart_id].add(product, key)
                return True

        return False

    def remove_from_cart(self, cart_id, product):
        """
        Removes a product from cart.

        :type cart_id: Int
        :param cart_id: id cart

        :type product: Product
        :param product: the product to remove from cart
        """

        # extract id from product in cart and add it back to producer buffer
        aux = self.carts[cart_id].remove(product)
        self.buffers[aux[1]].add(product)

        return aux[0]

    def place_order(self, cart_id):
        """
        Return a list with all the products in the cart.

        :type cart_id: Int
        :param cart_id: id cart
        """
        return self.carts[cart_id].buy()
