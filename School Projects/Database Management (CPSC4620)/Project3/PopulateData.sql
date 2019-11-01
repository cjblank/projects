/*Topping table*/
INSERT INTO TOPPING
VALUES ('Pepperoni', 1.25, 0.2, 100, 2, 2.75, 3.5, 4.5);

INSERT INTO TOPPING
VALUES ('Sausage', 1.25, 0.15, 100, 2.5, 3, 3.5, 4.25);

INSERT INTO TOPPING
VALUES ('Ham', 1.5, 0.15, 78, 2, 2.5, 3.25, 4);

INSERT INTO TOPPING
VALUES ('Chicken', 1.75, 0.25, 56, 1.5, 2, 2.25, 3);

INSERT INTO TOPPING
VALUES ('Green Pepper', 0.5, 0.02, 79, 1, 1.5, 2, 2.5);

INSERT INTO TOPPING
VALUES ('Onion', 0.5, 0.02, 85, 1, 1.5, 2, 2.75);

INSERT INTO TOPPING
VALUES ('Roma tomato', 0.75, 0.03, 86, 2, 3, 3.5, 4.5);

INSERT INTO TOPPING
VALUES ('Mushrooms', 0.75, 0.1, 52, 1.5, 2, 2.5, 3);

INSERT INTO TOPPING
VALUES ('Black Olives', 0.6, 0.1, 39, 0.75, 1, 1.5, 2);

INSERT INTO TOPPING
VALUES ('Pineapple', 1, 0.25, 15, 1, 1.25, 1.75, 2);

INSERT INTO TOPPING
VALUES ('Jalapenos', 0.5, 0.05, 64, 0.5, 0.75, 1.25, 1.75);

INSERT INTO TOPPING
VALUES ('Banana Peppers', 0.5, 0.05, 36, 0.6, 1, 1.3, 1.75);

INSERT INTO TOPPING
VALUES ('Regular Cheese', 1.5, 0.12, 250, 2, 3.5, 5, 7);

INSERT INTO TOPPING
VALUES ('Four Cheese Blend', 2, 0.15, 150, 2, 3.5, 5, 7);

INSERT INTO TOPPING
VALUES ('Feta Cheese', 2, 0.18, 75, 1.75, 3, 4, 5.5);

INSERT INTO TOPPING
VALUES ('Goat Cheese', 2, 0.2, 54, 1.6, 2.75, 4, 5.5);

INSERT INTO TOPPING
VALUES ('Bacon', 1.5, 0.25, 89, 1, 1.5, 2, 3);

INSERT INTO DISCOUNT
VALUES (1, 'employee', 'percent off', 15);

INSERT INTO DISCOUNT
VALUES (2, 'Lunch Special Medium', 'dollar off', 1);

INSERT INTO DISCOUNT
VALUES (3, 'Lunch Special Large', 'dollar off', 2);

INSERT INTO DISCOUNT
VALUES (4, 'Specialty Pizza', 'dollar off', 1.5);

INSERT INTO DISCOUNT
VALUES (5, 'Gameday special', 'percent off', 20);


/*BASE_PRICE table*/
INSERT INTO BASE_PRICE
VALUES (1, 'small', 'Thin', 3, 0.5);

INSERT INTO BASE_PRICE
VALUES (2, 'small', 'Original', 3, 0.75);

INSERT INTO BASE_PRICE
VALUES (3, 'small', 'Pan', 3.5, 1);

INSERT INTO BASE_PRICE
VALUES (4, 'small', 'Gluten-Free', 4, 2);

INSERT INTO BASE_PRICE
VALUES (5, 'medium', 'Thin', 5, 1);

INSERT INTO BASE_PRICE
VALUES (6, 'medium', 'Original', 5, 1.5);

INSERT INTO BASE_PRICE
VALUES (7, 'medium', 'Pan', 6, 2.25);

INSERT INTO BASE_PRICE
VALUES (8, 'medium', 'Gluten-Free', 6.25, 3);

INSERT INTO BASE_PRICE
VALUES (9, 'large', 'Thin', 8, 1.25);

INSERT INTO BASE_PRICE
VALUES (10, 'large', 'Original', 8, 2);

INSERT INTO BASE_PRICE
VALUES (11, 'large', 'Pan', 9, 3);

INSERT INTO BASE_PRICE
VALUES (12, 'large', 'Gluten-Free', 9.5, 4);

INSERT INTO BASE_PRICE
VALUES (13, 'X-large', 'Thin', 10, 2);

INSERT INTO BASE_PRICE
VALUES (14, 'X-large', 'Original', 10, 3);

INSERT INTO BASE_PRICE
VALUES (15, 'X-large', 'Pan', 11.5, 4.5);

INSERT INTO BASE_PRICE
VALUES (16, 'X-large', 'Gluten-Free', 12.5, 6);


/*Order 1*/
INSERT INTO ORDERS
VALUES (1);

INSERT INTO DINE_IN
VALUES (1, 14);

INSERT INTO PIZZA
VALUES(1, 13.50, 3.68, 'COMPLETE', '2019-03-05 12:03:00', 7, 1);

INSERT INTO HAS
VALUES(1, 'Regular Cheese', 1);

INSERT INTO HAS
VALUES(1, 'Pepperoni', 0);

INSERT INTO HAS
VALUES(1, 'Sausage', 0);

INSERT INTO DISC_APPLIED_TO_PIZZA
VALUES (1, 3);

INSERT INTO SEATNUM
VALUES (1, 1);

INSERT INTO SEATNUM
VALUES (1, 2);

INSERT INTO SEATNUM
VALUES (1, 3);

/*Order 2*/
INSERT INTO ORDERS
VALUES (2);

INSERT INTO DINE_IN
VALUES (2, 4);

INSERT INTO PIZZA
VALUES(2, 10.60, 3.23, 'COMPLETE', '2019-03-03 12:05:00', 9, 2);

INSERT INTO HAS
VALUES(2, 'Feta Cheese', 0);

INSERT INTO HAS
VALUES(2, 'Black Olives', 0);

INSERT INTO HAS
VALUES(2, 'Roma tomato', 0);

INSERT INTO HAS
VALUES(2, 'Mushrooms', 0);

INSERT INTO HAS
VALUES(2, 'Banana Peppers', 0);

INSERT INTO DISC_APPLIED_TO_PIZZA
VALUES (2, 2);

INSERT INTO DISC_APPLIED_TO_PIZZA
VALUES (2, 4);

INSERT INTO SEATNUM
VALUES (2, 1);


/*second pizza for this order*/
INSERT INTO ORDERS
VALUES (3);

INSERT INTO DINE_IN
VALUES (3, 4);

INSERT INTO PIZZA
VALUES(3, 6.75, 1.40, 'COMPLETE', '2019-03-03 12:05:00', 2, 3);

INSERT INTO HAS
VALUES(3, 'Regular Cheese', 0);

INSERT INTO HAS
VALUES(3, 'Chicken', 0);

INSERT INTO HAS
VALUES(3, 'Banana Peppers', 0);

INSERT INTO SEATNUM
VALUES (3, 2);


/*Order 3*/

INSERT INTO CUSTOMER
VALUES(1, 'Andrew Wilkes-Krier', '864-254-5861', NULL);

INSERT INTO ORDERS
VALUES (4);

INSERT INTO PICKUP
VALUES (4, 1);

INSERT INTO PIZZA
VALUES(4, 10.75, 3.30, 'COMPLETE', '2019-03-03 21:30:00', 10, 4);

INSERT INTO HAS
VALUES(4, 'Regular Cheese', 0);

INSERT INTO HAS
VALUES(4, 'Pepperoni', 0);

INSERT INTO PIZZA
VALUES(5, 10.75, 3.30, 'COMPLETE', '2019-03-03 21:30:00', 10, 4);

INSERT INTO HAS
VALUES(5, 'Regular Cheese', 0);

INSERT INTO HAS
VALUES(5, 'Pepperoni', 0);

INSERT INTO PIZZA
VALUES(6, 10.75, 3.30, 'COMPLETE', '2019-03-03 21:30:00', 10, 4);

INSERT INTO HAS
VALUES(6, 'Regular Cheese', 0);

INSERT INTO HAS
VALUES(6, 'Pepperoni', 0);

INSERT INTO PIZZA
VALUES(7, 10.75, 3.30, 'COMPLETE', '2019-03-03 21:30:00', 10, 4);

INSERT INTO HAS
VALUES(7, 'Regular Cheese', 0);

INSERT INTO HAS
VALUES(7, 'Pepperoni', 0);

INSERT INTO PIZZA
VALUES(8, 10.75, 3.30, 'COMPLETE', '2019-03-03 21:30:00', 10, 4);

INSERT INTO HAS
VALUES(8, 'Regular Cheese', 0);

INSERT INTO HAS
VALUES(8, 'Pepperoni', 0);

INSERT INTO PIZZA
VALUES(9, 10.75, 3.30, 'COMPLETE', '2019-03-03 21:30:00', 10, 4);

INSERT INTO HAS
VALUES(9, 'Regular Cheese', 0);

INSERT INTO HAS
VALUES(9, 'Pepperoni', 0);


/*Order 4*/
INSERT INTO ORDERS
VALUES(5);

UPDATE CUSTOMER
SET Address = "115 Party Blvd, Anderson SC 29621"
WHERE Cust_ID = 1;

INSERT INTO DELIVERY
VALUES(5, 1);

INSERT INTO PIZZA
VALUES(10, 14.50, 5.59, 'COMPLETE', '2019-03-05 19:11:00', 14, 5);

INSERT INTO HAS
VALUES(10, 'Four Cheese Blend', 0);

INSERT INTO HAS
VALUES(10, 'Pepperoni', 0);

INSERT INTO HAS
VALUES(10, 'Sausage', 0);

INSERT INTO PIZZA
VALUES(11, 17.00, 5.59, 'COMPLETE', '2019-03-05 19:11:00', 14, 5);

INSERT INTO HAS
VALUES(11, 'Four Cheese Blend', 0);

INSERT INTO HAS
VALUES(11, 'Ham', 1);

INSERT INTO HAS
VALUES(11, 'Pineapple', 1);

INSERT INTO DISC_APPLIED_TO_PIZZA
VALUES (11, 4);

INSERT INTO PIZZA
VALUES(12, 14.00, 5.68, 'COMPLETE', '2019-03-05 19:11:00', 14, 5);

INSERT INTO HAS
VALUES(12, 'Four Cheese Blend', 0);

INSERT INTO HAS
VALUES(12, 'Jalapenos', 0);

INSERT INTO HAS
VALUES(12, 'Bacon', 0);

INSERT INTO DISC_APPLIED_TO_OR
VALUES (5, 5);


/*Order 5*/
INSERT INTO CUSTOMER
VALUES(2, 'Matt Engers', '864-474-9953', NULL);

INSERT INTO ORDERS
VALUES (6);

INSERT INTO PICKUP
VALUES(6, 2);

INSERT INTO PIZZA
VALUES(13, 16.85, 7.85, 'COMPLETE', '2019-03-02 17:30:00', 16, 6);

INSERT INTO HAS
VALUES(13, 'Goat Cheese', 0);

INSERT INTO HAS
VALUES(13, 'Green Pepper', 0);

INSERT INTO HAS
VALUES(13, 'Onion', 0);

INSERT INTO HAS
VALUES(13, 'Roma tomato', 0);

INSERT INTO HAS
VALUES(13, 'Mushrooms', 0);

INSERT INTO HAS
VALUES(13, 'Black Olives', 0);

INSERT INTO DISC_APPLIED_TO_PIZZA
VALUES (13, 4);

/*Order 6*/
INSERT INTO CUSTOMER
VALUES(3, 'Frank Turner', '864-232-8944', '6745 Wessex St Anderson SC 29621');

INSERT INTO ORDERS
VALUES(7);

INSERT INTO DELIVERY
VALUES (7, 3);

INSERT INTO PIZZA
VALUES(14, 13.25, 3.20, 'COMPLETE', '2019-03-02 18:17:00', 9, 7);

INSERT INTO HAS
VALUES(14, 'Four Cheese Blend', 0);

INSERT INTO HAS
VALUES(14, 'Chicken', 0);

INSERT INTO HAS
VALUES(14, 'Green Pepper', 0);

INSERT INTO HAS
VALUES(14, 'Onion', 0);

INSERT INTO HAS
VALUES(14, 'Mushrooms', 0);


/*Order 7*/
INSERT INTO CUSTOMER
VALUES(4, 'Milo Auckerman', '864-878-5679', '8879 Suburban Home, Anderson, SC 29621');

INSERT INTO ORDERS
VALUES(8);

INSERT INTO PIZZA
VALUES(15, 12.00, 3.75, 'COMPLETE', '2019-03-06 19:22:00', 9, 8);

INSERT INTO HAS
VALUES(15, 'Four Cheese Blend', 1);

INSERT INTO PIZZA
VALUES(16, 12.00, 2.55, 'COMPLETE', '2019-03-06 19:22:00', 9, 8);

INSERT INTO HAS
VALUES(16, 'Regular Cheese', 0);

INSERT INTO HAS
VALUES(16, 'Pepperoni', 1);

INSERT INTO DISC_APPLIED_TO_OR
VALUES (8, 1);
