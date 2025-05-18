# Supermarket Product Restocking Simulator

## Description

This project simulates the restocking process of a supermarket's inventory using concurrent programming with threads in C. The focus is on the merchandise arrival area, where trucks unload boxes that are temporarily stored before being moved to the stock by employees.

---

## Problem Description

- The supermarket sells various products: food items, cleaning supplies, hygiene products, and household goods.
- Only one truck can unload at the merchandise arrival area at a time.
- Each truck delivers a varying number of boxes (e.g., 4 boxes of soda, 1 box of chocolate, etc.). All boxes have the same size.
- Boxes are placed in the loading area, which has a maximum capacity of **B** boxes.
- If a truck wants to deliver an order containing **C** boxes, it must unload the boxes one by one, respecting the loading area capacity.
- The truck can only leave after unloading all boxes in the order.
- There are **F** employees responsible for removing boxes from the loading area and placing them in the stock, one box at a time.
- Only one person (either an employee or the truck) can access the loading area at any given time.

---

## Objective

Create a concurrent program that simulates the arrival and stocking of **N** boxes:

- One thread simulates the arrival of trucks and their deliveries (each delivery up to **C** boxes).
- **F** threads simulate the employees transporting boxes from the loading area to the stock.
- The program receives input parameters via command line.

---

## Command Line Arguments

./market N B C F T L


- **N** (1 < N < 100): Minimum number of boxes to be delivered.
- **B** (1 < B < 10): Maximum capacity of the loading area (number of boxes).
- **C** (1 < C < 5): Maximum boxes per order/truck.
- **F** (1 < F < 3): Number of employees.
- **T** (1 < T < 20): Maximum interval (seconds) between truck arrivals.
- **L** (1 < L < 15): Maximum time (seconds) for an employee to transport one box to the stock.

---

## How It Works

- Truck arrivals are random within the interval **T**.
- The number of boxes per order is random, up to **C**.
- After unloading an order, a message shows the truck number and how many boxes were placed in the loading area.
- Employees remove boxes one by one and transport them to the stock, simulating transportation time with a random delay up to **L** seconds.
- Messages indicate when each employee transports a box to the stock.
- When more than **N** boxes are delivered, truck arrivals stop.
- The program ends only after all boxes are in the stock.

---

## Example Usage

./market 20 5 4 2 12 10


---

## Sample Output

Created thread simulating truck arrivals
Truck 1, will deliver 4 box(es) to the loading area
Truck 1, unloaded 2 box(es) in the loading area
Created thread simulating employee Bilguêiti
Employee Bilguêiti, transported one box to the stock
Employee Bilguêiti, transported one box to the stock
Created thread simulating employee Torvalino
Truck 1, unloaded 2 box(es) in the loading area
Employee Bilguêiti, transported one box to the stock
Employee Bilguêiti, transported one box to the stock
Truck 2, will deliver 3 box(es) to the loading area
Truck 2, unloaded 2 box(es) in the loading area
Employee Bilguêiti, transported one box to the stock
Truck 2, unloaded 1 box(es) in the loading area
Employee Torvalino, transported one box to the stock
Employee Bilguêiti, transported one box to the stock
Truck thread finished
Employee Torvalino finished working
Employee Bilguêiti finished working


---

## Notes

- The program will not run if the arguments are incorrect and will display a usage message.
- Access to the loading area is exclusive to avoid conflicts between threads.
